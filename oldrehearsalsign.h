/////////////////////////////////////////////////////////////////////////////
// Name:            oldrehearsalsign.h
// Purpose:         Used to retrieve rehearsal signs in older file versions
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 27, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __OLDREHEARSALSIGN_H__
#define __OLDREHEARSALSIGN_H__

class RehearsalSign;

/// Used to retrieve rehearsal signs in older file versions
class OldRehearsalSign : public PowerTabObject
{
friend class OldRehearsalSignTestSuite;

// Constants
public:
    static const wxWord         DEFAULT_SYSTEM;             ///< Default value for the system member variable
    static const wxByte         DEFAULT_POSITION;           ///< Default value for the position member variable
    static const wxUint32       DEFAULT_DATA;               ///< Default value for the data member variable
    static const wxInt8         DEFAULT_LETTER;             ///< Default value for the letter member variable
    static const wxChar*        DEFAULT_DESCRIPTION;        ///< Default value for the description member variable
    
public:
    wxWord          m_system;               ///< Zero based index of the system the rehearsal sign is anchored to
    wxByte          m_position;             ///< Zero based index of the position within the system where the rehearsal sign is anchored
    wxUint32        m_data;                 ///< Unused data
    wxInt8          m_letter;               ///< The letter used to uniquely identify the rehearsal sign (i.e. A, B, F, etc. - must be a capital letter)
    wxString        m_description;          ///< A description that indicates the passage the rehearsal sign is marking (i.e. Chorus, Intro, etc.)
    
public:
    // Constructor/Destructor
    OldRehearsalSign();
    ~OldRehearsalSign();
    
    // Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const         
        {return (new OldRehearsalSign(*this));}
    
    // Construction Functions
    bool ConstructRehearsalSign(RehearsalSign& rehearsalSign) const;
    
    // Operators
    const OldRehearsalSign& operator=(const OldRehearsalSign& oldRehearsalSign);
    bool operator==(const OldRehearsalSign& oldRehearsalSign) const;
    bool operator!=(const OldRehearsalSign& oldRehearsalSign) const;
    
    // MFC Class Functions
    /// Gets the MFC class id associated with the object
    /// @return The MFC class id associated with the object
    wxString GetMFCClassId() const              
        {return (wxString::Format(wxT("%s-%d"), GetMFCClassName().c_str(), GetMFCClassSchema()));}
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const            
        {return (wxT("CRehearsalSign"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const            
        {return ((wxWord)1);}
    
    // Serialization Functions
protected:
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);
};

// Array Declarations
WX_DEFINE_POWERTABARRAY(OldRehearsalSign*, OldRehearsalSignArray);

#endif
