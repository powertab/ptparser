/////////////////////////////////////////////////////////////////////////////
// Name:            powertaboutputstream.h
// Purpose:         Output stream used to serialize MFC based Power Tab data
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 20, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __POWERTABOUTPUTSTREAM_H__
#define __POWERTABOUTPUTSTREAM_H__

class PowerTabObject;
WX_DECLARE_STRING_HASH_MAP(wxUint32, ClassInfoHashMap);
WX_DECLARE_VOIDPTR_HASH_MAP(void*, ObjectHashMap);

/// Output stream used to serialize MFC based Power Tab data
class PowerTabOutputStream :
    public wxDataOutputStream
{
// Member Variables
protected:
    bool                    m_mapsInitialized;                  ///< Determines whether or not the maps have been initialized
    ClassInfoHashMap        m_classInfoHashMap;                 ///< Map of class Ids to object index
    ObjectHashMap           m_objectHashMap;                    ///< Map of object pointers to object index
    wxUint32                m_mapCount;                         ///< Internal count of mapped objects
    PowerTabStreamError     m_lastPowerTabError;                ///< Last Power Tab specific error

// Constructor/Destructor
public:
    PowerTabOutputStream(wxOutputStream& stream);
    ~PowerTabOutputStream();

// Write Functions
    bool WriteCount(wxUint32 count);
    bool WriteAnsiText(const wxString& text);
    bool WriteMFCString(const wxString& string);
    bool WriteWin32ColorRef(wxColor color);
    bool WriteMFCRect(const wxRect& rect);
    bool WriteObject(PowerTabObject* object);
protected:
    bool WriteClassInformation(const PowerTabObject* object);
    bool WriteMFCStringLength(wxUint32 length, bool unicode);
    
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
    off_t TellO() const        
        {wxCHECK(m_output != NULL, 0); return (m_output->TellO());}
};

#endif
