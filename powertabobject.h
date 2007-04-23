/////////////////////////////////////////////////////////////////////////////
// Name:            powertabobject.h
// Purpose:         Provides support for polymorphic reading/writing of Power Tab objects
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 18, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __POWERTABOBJECT_H__
#define __POWERTABOBJECT_H__

class PowerTabOutputStream;
class PowerTabInputStream;

/// Provides support for polymorphic reading/writing of Power Tab objects
class PowerTabObject
{
public:
    // Constructor/Destructor
    PowerTabObject();
    virtual ~PowerTabObject();
    
    // Creation Functions
    static PowerTabObject* CreateObject(const wxString& classId);
    virtual PowerTabObject* CloneObject() const = 0;
    
    // MFC Class Functions
    /// Gets the MFC class id associated with the object
    /// @return The MFC class id associated with the object
    virtual wxString GetMFCClassId() const                                                      
        {return (wxString::Format(wxT("%s-%d"), GetMFCClassName().c_str(), GetMFCClassSchema()));}
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    virtual wxString GetMFCClassName() const        
        {return (wxT(""));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    virtual wxWord GetMFCClassSchema() const        
        {return ((wxWord)0);}
    bool WriteMFCClassInformation(wxOutputStream& stream) const;
    bool WriteMFCClassInformation(PowerTabOutputStream& stream) const;
    static bool ReadMFCClassInformation(wxInputStream& stream, wxWord version, wxString& classId);
    static bool ReadMFCClassInformation(PowerTabInputStream& stream, wxWord version, wxString& classId);
    
    // Serialization Functions
    bool Serialize(wxOutputStream& stream);
    bool Serialize(PowerTabOutputStream& stream);
    bool Deserialize(wxInputStream& stream, wxWord version);
    bool Deserialize(PowerTabInputStream& stream, wxWord version);
    
    // Note: DoSerialize/DoDeserialize are needed because of name function hiding problem
    // (see wxWidgets Programmer Style Guide - Avoid Overloaded Virtual Functions topic)
protected:
    /// Performs serialization for the class
    /// @param stream Power Tab output stream to serialize to
    /// @return True if the object was serialized, false if not
    virtual bool DoSerialize(PowerTabOutputStream& WXUNUSED(stream))
        {wxASSERT(false); return (false);}
    /// Performs deserialization for the class
    /// @param stream Power Tab input stream to deserialize from
    /// @param version File version
    /// @return True if the object was deserialized, false if not
    virtual bool DoDeserialize(PowerTabInputStream& WXUNUSED(stream),
        wxWord WXUNUSED(version))
        {wxASSERT(false); return (false);}
};

#endif
