/////////////////////////////////////////////////////////////////////////////
// Name:            rehearsalsign.h
// Purpose:         Stores and renders Rehearsal Sign symbols
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __REHEARSALSIGN_H__
#define __REHEARSALSIGN_H__

/// Stores and renders Rehearsal Sign symbols
class RehearsalSign : public PowerTabObject
{
// Constants
public:
    // Default constants
    static const wxInt8         DEFAULT_LETTER;             ///< Default value for the letter member variable
    static const wxChar*        DEFAULT_DESCRIPTION;        ///< Default value for the description member variable

    enum flags
    {
        notSet = (wxInt8)0x7f           ///< Marker used to indicate the rehearsal sign is not set (not used)
    };

protected:
    wxInt8      m_letter;               ///< The letter used to uniquely identify the rehearsal sign (i.e. A, B, F, etc. - must be a capital letter)
    wxString    m_description;          ///< A description that indicates the passage the rehearsal sign is marking (i.e. Chorus, Intro, etc.)

public:
    // Construction/Destruction
    RehearsalSign();
    RehearsalSign(wxInt8 letter, const wxChar* description);
    RehearsalSign(const RehearsalSign& rehearsalSign);
    ~RehearsalSign();
    
    // Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                     
        {return (new RehearsalSign(*this));}
    
    // Operators
    const RehearsalSign& operator=(const RehearsalSign& rehearsalSign);
    bool operator==(const RehearsalSign& rehearsalSign) const;
    bool operator!=(const RehearsalSign& rehearsalSign) const;

    // MFC Class Functions
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const                        
        {return (wxT("CRehearsalSign2"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const                        
        {return ((wxWord)1);}
    
    // Serialization Functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

public:
    // Letter Functions
    /// Determines if a letter is valid
    /// @param letter The letter to validate
    /// @return True if the letter is valid, false if not
    static bool IsValidLetter(wxInt8 letter)                
        {return (((letter >= 'A') && (letter <= 'Z')) || (letter == notSet));}
    bool SetLetter(wxInt8 letter);
    /// Gets the letter used to uniquely identify the rehearsal sign
    /// @return The letter used to uniquely identify the rehearsal sign
    wxInt8 GetLetter() const
        {return (m_letter);}

    // Description functions
    /// Sets the rehearsal sign description
    /// @param description Description to set
    /// @return True if the description was set, false if not
    bool SetDescription(const wxChar* description)
        {wxCHECK(description != NULL, false); m_description = description; return (true);}
    /// Gets the rehearsal sign description
    /// @return The rehearsal sign description
    wxString GetDescription() const
        {return (m_description);}

    // Operations
    /// Determines if a RehearsalSign object is set (in use)
    /// @return True if the RehearsalSign object is set, false if not
    bool IsSet() const                                      
        {return (GetLetter() != notSet);}
    /// Clears the rehearsal sign letter and description, and sets to not set
    void Clear()                                            
        {SetLetter(notSet); SetDescription(wxT(""));}
    wxString GetFormattedText() const;
};

#endif
