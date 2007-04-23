/////////////////////////////////////////////////////////////////////////////
// Name:            powertabinputstream.h
// Purpose:         Input stream used to deserialize MFC based Power Tab data
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 19, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __POWERTABINPUTSTREAM_H__
#define __POWERTABINPUTSTREAM_H__

class PowerTabObject;
WX_DECLARE_STRING_HASH_MAP(wxUint32, ClassIdHashMap);
WX_DECLARE_HASH_MAP(wxUint32, wxString, wxIntegerHash, wxIntegerEqual, ClassIdIdHashMap);

/// Input stream used to deserialize MFC based Power Tab data
class PowerTabInputStream :
    public wxDataInputStream
{
friend class PowerTabFileHeader;
friend class PowerTabObject;

protected:
    bool                        m_mapsInitialized;              ///< Determines whether or not the maps have been initialized
    wxUint32                    m_mapCount;                     ///< Internal count of mapped objects
    PowerTabStreamError         m_lastPowerTabError;            ///< Last Power Tab specific error
    ClassIdHashMap              m_classIdHashMap;               ///< Map of class Ids to the id of the class id
    ClassIdIdHashMap            m_classIdIdHashMap;             ///< Map of Id of the class Id to the class id (opposite of above map)
    wxArrayPtrVoid              m_loadArray;                    ///< Array of pointers to loaded objects and tags
    
public:
    // Constructor/Destructor
    PowerTabInputStream(wxInputStream& stream);
    ~PowerTabInputStream();

    // Read Functions
    wxUint32 ReadCount();
    bool ReadAnsiText(wxUint32 length, wxString& text);
    bool ReadMFCString(wxString& string);
    bool ReadWin32ColorRef(wxColor& color);
    bool ReadMFCRect(wxRect& rect);
    PowerTabObject* ReadObject(wxWord version);
protected:
    bool ReadClassInformation(wxWord version, wxString& classId, wxUint32& objectTag);
    wxUint32 ReadMFCStringLength(wxUint32& charSize);
    
    // Error Checking Functions
public:
    /// Checks the current state of the stream
    /// @return True if the stream is OK, false if an error has occurred
    bool CheckState()                                           
        {return (IsOk() && (m_lastPowerTabError == POWERTABSTREAM_NO_ERROR));}
    wxString GetLastErrorMessage();

protected:
    bool CheckCount();
    
    // Operations
    bool MapObject(const PowerTabObject* object);

public:    
    /// Gets the current stream position, in bytes
    /// @return The current stream position, in bytes
    off_t TellI() const        
        {wxCHECK(m_input != NULL, 0); return (m_input->TellI());}
};

#endif
