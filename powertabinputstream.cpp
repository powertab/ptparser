/////////////////////////////////////////////////////////////////////////////
// Name:            powertabinputstream.cpp
// Purpose:         Input stream used to deserialize MFC based Power Tab data
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 19, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "powertabinputstream.h"

// Constructor/Destructor
/// Primary Constructor
PowerTabInputStream::PowerTabInputStream(wxInputStream& stream) :
    wxDataInputStream(stream), m_mapsInitialized(false), m_mapCount(0), m_lastPowerTabError(POWERTABSTREAM_NO_ERROR)
{
    //------Last Checked------//
    // - Dec 21, 2004
}

/// Destructor
PowerTabInputStream::~PowerTabInputStream()
{
    //------Last Checked------//
    // - Dec 21, 2004
}

// Read Functions
/// Reads a count value in MFC format from the stream
/// @return The count value
wxUint32 PowerTabInputStream::ReadCount()
{
    //------Last Checked------//
    // - Dec 30, 2004
    wxUint32 returnValue = 0;

    wxWord wordCount = 0;
	*this >> wordCount;
	wxCHECK(CheckState(), 0);
	
	// 16-bit count
	if (wordCount != 0xffff)
		returnValue = wordCount;
    // 32-bit count
    else
    {
        *this >> returnValue;
        wxCHECK(CheckState(), 0);
    }

    return (returnValue);
}

/// Reads ANSI based text from the stream
/// @param length Length of text to read
/// @param text Holds the text that was read
/// @return True if text was read, false if not
bool PowerTabInputStream::ReadAnsiText(wxUint32 length, wxString& text)
{
    //------Last Checked------//
    // - Dec 24, 2004
    
    text.Clear();
    
	// Allocate a buffer for the text (+1 for the terminator)
	char* buffer = new char [length + 1];

    // Read the text, 1 letter at a time
    // TODO: Update this to read chunks in wxWidgets 2.5
    wxUint32 i = 0;
    for (; i < length; i++)
    {
        char* x = buffer + i;
        *x = Read8();
        if (!CheckState())
        {
            delete [] buffer;
            return (false);
        }
    }
    
    *(buffer + length) = '\0';
    text = buffer;

    delete [] buffer;
            
    return (true);
}

/// Loads an Microsoft based (MFC) string from the stream and copies the text to a wxString object
/// @param string wxString object to copy the text to
/// @return True if the string was read, false if not
bool PowerTabInputStream::ReadMFCString(wxString& string)
{
    //------Last Checked------//
    // - Dec 27, 2004

    // initialize the return value
    string = wxT("");

    // Get the length of the string and the size of each character
    wxUint32 charSize = 1;  // 1 = char, 2 = wchar_t
    wxUint32 length = ReadMFCStringLength(charSize);
    
    // Make sure we have length
    if (length > 0)
    {
        // ANSI text
        if (charSize == sizeof(char))
            ReadAnsiText(length, string);
        // Unicode text (not supported since all Power Tab text is ANSI)
        else
            wxCHECK(true, false);
    }

    return (CheckState());
}

/// Reads a Win32 format COLORREF type from the stream
/// @param color Color 
/// @return True if the color was read, false if not
bool PowerTabInputStream::ReadWin32ColorRef(wxColor& color)
{
    //------Last Checked------//
    // - Dec 27, 2004
    color = wxColor(0,0,0);

    wxUint32 colorref = 0;
    *this >> colorref;
    wxCHECK(CheckState(), false);
        
    color.Set(LOBYTE(LOWORD(colorref)), HIBYTE(LOWORD(colorref)), LOBYTE(HIWORD(colorref)));
    
    return (true);
}

/// Loads a Microsoft CRect object from the stream and copies its values to a wxRect object
/// @param rect wxRect object to copy the CRect values to
/// @return True if the rect was read, false if not
bool PowerTabInputStream::ReadMFCRect(wxRect& rect)
{
    //------Last Checked------//
    // - Dec 27, 2004

    rect = wxRect(0,0,0,0);

    wxInt32 left = 0, top = 0, right = 0, bottom = 0;
	*this >> left >> top >> right >> bottom;
	wxCHECK(CheckState(), false);
	
	rect.SetLeft(left);
	rect.SetTop(top);
	rect.SetRight(right);
	rect.SetBottom(bottom);
	   
    return (CheckState());
}

/// Reads a Power Tab object from the stream
/// @param version File version
/// @return True if the object was read, NULL if not
PowerTabObject* PowerTabInputStream::ReadObject(wxWord version)
{
    //------Last Checked------//
    // - Dec 21, 2004
    
	// read the object's class information
	wxString classId = wxT("");
	wxUint32 objectTag = 0;
	ReadClassInformation(version, classId, objectTag);

	// if the classId is empty, then the object has already
	// been loaded
	PowerTabObject* object = NULL;
	if (classId.IsEmpty())
	{
		if (objectTag > (wxUint32)(m_loadArray.GetCount() - 1))
		{
		    // tag is too large for the number of objects read so far
		    m_lastPowerTabError = POWERTABSTREAM_BAD_INDEX;
            return NULL;
		}

        // get a pointer to the object
        object = (PowerTabObject*)m_loadArray[objectTag];
	}
	else
	{
		// allocate a new object based on the class just acquired
		object = PowerTabObject::CreateObject(classId);
		if (object == NULL)
		{
		    m_lastPowerTabError = POWERTABSTREAM_BAD_CLASS;
		    return (NULL);
		}

        // Add to mapping array BEFORE de-serializing
        MapObject(object);
		
		// Serialize the object with the schema number set in the archive
		object->Deserialize(*this, version);
		if (!CheckState())
		{
		    delete object;
		    return (NULL);
	    }
	}

    return (object);
}

/// Reads a Power Tab object's class information from the stream
/// @param version File version
/// @param classId Holds the class id return value
/// @param objectTag Holds the object tag return value
/// @return True if the class information was written, false if not
bool PowerTabInputStream::ReadClassInformation(wxWord version, wxString& classId, wxUint32& objectTag)
{
    //------Last Checked------//
    // - Dec 21, 2004
    classId.Clear();
    objectTag = 0;
    
	// make sure m_loadArray is initialized
	MapObject(NULL);

	// read object tag - if prefixed by BIG_OBJECT_TAG then double word tag follows
	wxUint32 obTag = 0;
	wxWord wordTag = 0;
	*this >> wordTag;
	
	if (wordTag == BIG_OBJECT_TAG)
		*this >> obTag;
	else
		obTag = ((wordTag & CLASS_TAG) << 16) | (wordTag & ~CLASS_TAG);

	// check for object tag (throw exception if expecting class tag)
	if (!(obTag & BIG_CLASS_TAG))
	{
		objectTag = obTag;
		return (true);
	}

    // Object is a new class
	if (wordTag == NEW_CLASS_TAG)
	{
	    // new object follows a new class id
	    // read the class information for the object
	    PowerTabObject::ReadMFCClassInformation(*this, version, classId);
	    
	    // map both the class id and the id of the class id for quick lookup
	    wxUint32 classIdId = 0;
	    if (m_classIdHashMap.find(classId) == m_classIdHashMap.end())
	    {
	        classIdId = m_classIdHashMap.size() + 1;
	        m_classIdHashMap[classId] = classIdId;
	        m_classIdIdHashMap[classIdId] = classId;
	    }
	    
		if (!CheckCount())
		{
		    m_lastPowerTabError = POWERTABSTREAM_BAD_CLASS;
		    return (false);
	    }
		m_loadArray.Insert((void*)classIdId, m_mapCount++);
	}
	else
	{
		// existing class index in obTag followed by new object
		wxUint32 classIndex = (obTag & ~BIG_CLASS_TAG);
		if ((classIndex == 0) || (classIndex > (wxUint32)(m_loadArray.GetCount() - 1)))
		{
		    m_lastPowerTabError = POWERTABSTREAM_BAD_INDEX;
		    return (false);
        }
        
        // get the id for the class id for the class index
        // and make sure it has been mapped
        wxUint32 classIdId = (wxUint32)m_loadArray[classIndex];
        if (m_classIdIdHashMap.find(classIdId) == m_classIdIdHashMap.end())
        {
            m_lastPowerTabError = POWERTABSTREAM_BAD_INDEX;
            return (false);
        }
        classId = m_classIdIdHashMap[classIdId];
   }

	// store obTag for later examination
	objectTag = obTag;

    return (true);
}

/// Reads the length of a Microsoft based (MFC) string from a data input stream. Also determines
/// the character size of the text (ANSI or Unicode)
/// @param charSize Size of each character in the string; 1 - ANSI, 2 - Unicode
/// @return The length of the string, in characters
wxUint32 PowerTabInputStream::ReadMFCStringLength(wxUint32& charSize)
{
    wxByte byteLength = 0;
    wxWord wordLength = 0;
    wxUint32 doubleWordLength = 0;
    
    // Assume ANSI characters
    charSize = sizeof(char);

    // First, try to read a one-byte length
    *this >> byteLength;
    wxCHECK(CheckState(), 0);
    
    if (byteLength < BYTE_PLACEHOLDER)
        return (byteLength);

    // Try a two-byte length
    *this >> wordLength;
    wxCHECK(CheckState(), 0);

    // Unicode string
    if (wordLength == UNICODE_MARKER)
    {
        // Update the character size
        charSize = sizeof(wchar_t);

        // Start over at 1-byte length
        *this >> byteLength;
        wxCHECK(CheckState(), 0);
        
        if (byteLength < BYTE_PLACEHOLDER)
            return (byteLength);

        // Two-byte length
        *this >> wordLength;
        wxCHECK(CheckState(), 0);
        
        // Fall through to continue on same branch as ANSI string
    }
    if (wordLength < WORD_PLACEHOLDER)
        return (wordLength);

    // 4-byte length
    *this >> doubleWordLength;
    wxCHECK(CheckState(), 0);
    
    return (doubleWordLength);
}

// Error Checking Functions
/// Gets the error message associated with the last error that occurred in the stream
/// @return The error message associated with the last error that occurred in the stream
wxString PowerTabInputStream::GetLastErrorMessage()
{
    //------Last Checked------//
    // - Dec 21, 2004
    wxString returnValue = wxT("");
    
    if (CheckState())
        returnValue = wxT("No error");
    else if (m_input->GetLastError() == wxSTREAM_EOF)
        returnValue = wxT("End of file reached");
    else if (m_input->GetLastError() == wxSTREAM_WRITE_ERROR)
        returnValue = wxT("Generic write error");
    else if (m_input->GetLastError() == wxSTREAM_READ_ERROR)
        returnValue = wxT("Generic read error");
    else if (m_lastPowerTabError == POWERTABSTREAM_INVALID_MARKER)
        returnValue = wxT("Invalid file marker");
    else if (m_lastPowerTabError == POWERTABSTREAM_INVALID_FILE_VERSION)
        returnValue = wxT("Invalid file version");
    else if (m_lastPowerTabError == POWERTABSTREAM_INVALID_FILE_TYPE)
        returnValue = wxT("Invalid file type");
    else if (m_lastPowerTabError == POWERTABSTREAM_BAD_INDEX)
        returnValue = wxT("Bad index");
    else if (m_lastPowerTabError == POWERTABSTREAM_BAD_CLASS)
        returnValue = wxT("Bad class");
    else if (m_lastPowerTabError == POWERTABSTREAM_BAD_SCHEMA)
        returnValue = wxT("Bad schema");

    return (returnValue);
}

/// Validates the internal map count (checks for overflow)
/// @return True if the map count is valid, false if not
bool PowerTabInputStream::CheckCount()
{
    //------Last Checked------//
    // - Dec 21, 2004
    bool returnValue = (m_mapCount < MAX_MAP_COUNT);
    if (!returnValue)
        m_lastPowerTabError = POWERTABSTREAM_BAD_INDEX;
    return (returnValue);
}

// Operations
/// Maps a Power Tab object to its object index
/// @param object Power Tab object to map
/// @return True if the object was mapped, false if not
bool PowerTabInputStream::MapObject(const PowerTabObject* object)
{
    //------Last Checked------//
    // - Dec 20, 2004
    
    // Initialize the internal maps
    if (!m_mapsInitialized)
    {
        m_mapsInitialized = true;
        m_loadArray.Insert(NULL_TAG, 0);
        m_mapCount = 1;
    }
    
    // Map the object
    if (object != NULL)
    {
        if (!CheckCount())
            return (false);
        m_loadArray.Insert((void*)object, m_mapCount++);
    }
    
    return (true);
}
