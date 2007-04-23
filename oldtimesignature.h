/////////////////////////////////////////////////////////////////////////////
// Name:            oldtimesignature.h
// Purpose:         Used to retrieve time signatures in older file versions
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 29, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __OLDTIMESIGNATURE_H__
#define __OLDTIMESIGNATURE_H__

class TimeSignature;

/// Used to retrieve time signatures in older file versions
class OldTimeSignature : public PowerTabObject
{
friend class OldTimeSignatureTestSuite;

// Constants
public:
    static const wxWord         DEFAULT_SYSTEM;             ///< Default value for the system member variable
    static const wxByte         DEFAULT_POSITION;           ///< Default value for the position member variable
    static const wxUint32       DEFAULT_DATA;               ///< Default value for the data member variable
    
public:
    wxWord      m_system;                       ///< Zero based index of the system the time signature is anchored to
    wxByte      m_position;                     ///< Zero based index of the position within the system where the symbol is anchored
    wxUint32    m_data;                         ///< Time signature related data
    
public:
    // Constructor/Destructor
    OldTimeSignature();
    ~OldTimeSignature();
    
    // Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const         
        {return (new OldTimeSignature(*this));}
    
    // Construction Functions
    bool ConstructTimeSignature(TimeSignature& timeSignature) const;
    
    // Operators
    const OldTimeSignature& operator=(const OldTimeSignature& oldTimeSignature);
    bool operator==(const OldTimeSignature& oldTimeSignature) const;
    bool operator!=(const OldTimeSignature& oldTimeSignature) const;
    
    // MFC Class Functions
    /// Gets the MFC class id associated with the object
    /// @return The MFC class id associated with the object
    wxString GetMFCClassId() const              
        {return (wxString::Format(wxT("%s-%d"), GetMFCClassName().c_str(), GetMFCClassSchema()));}
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const            
        {return (wxT("CTimeSignature"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const            
        {return ((wxWord)1);}
          
    // Serialization Functions
protected:  
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);
};

// Array Declarations
WX_DEFINE_POWERTABARRAY(OldTimeSignature*, OldTimeSignatureArray);

#endif
