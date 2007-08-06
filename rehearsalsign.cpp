/////////////////////////////////////////////////////////////////////////////
// Name:            rehearsalsign.cpp
// Purpose:         Stores and renders Rehearsal Sign symbols
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "rehearsalsign.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Default constants
const wxInt8    RehearsalSign::DEFAULT_LETTER           = RehearsalSign::notSet;
const wxChar*   RehearsalSign::DEFAULT_DESCRIPTION      = wxT("");

/// Default Constructor
RehearsalSign::RehearsalSign() :
    m_letter(DEFAULT_LETTER), m_description(DEFAULT_DESCRIPTION)
{
    //------Last Checked------//
    // - Dec 10, 2004
}

/// Primary Constructor
/// @param letter Unique letter identifying the rehearsal sign
/// @param description Description for the rehearsal sign (i.e. Intro)
RehearsalSign::RehearsalSign(wxInt8 letter, const wxChar* description) :
    m_letter(letter), m_description(description)
{
    //------Last Checked------//
    // - Dec 10, 2004
    wxASSERT(IsValidLetter(letter));
    wxASSERT(description != NULL);
}

/// Copy Constructor
RehearsalSign::RehearsalSign(const RehearsalSign& rehearsalSign) :
    m_letter(DEFAULT_LETTER), m_description(DEFAULT_DESCRIPTION)
{
    //------Last Checked------//
    // - Dec 10, 2004
    *this = rehearsalSign;
}

/// Destructor
RehearsalSign::~RehearsalSign()
{
    //------Last Checked------//
    // - Dec 10, 2004
}

/// Assignment Operator
const RehearsalSign& RehearsalSign::operator=(
    const RehearsalSign& rehearsalSign)
{
    //------Last Checked------//
    // - Dec 10, 2004

    // Check for assignment to self
    if (this != &rehearsalSign)
    {
        m_letter = rehearsalSign.m_letter;
        m_description = rehearsalSign.m_description;
    }
    return (*this);
}

/// Equality Operator
bool RehearsalSign::operator==(const RehearsalSign& rehearsalSign) const
{
    //------Last Checked------//
    // - Dec 10, 2004
    return ((m_letter == rehearsalSign.m_letter) &&
        (m_description == rehearsalSign.m_description));
}

/// Inequality Operator
bool RehearsalSign::operator!=(const RehearsalSign& rehearsalSign) const
{
    //------Last Checked------//
    // - Dec 10, 2004
    return (!operator==(rehearsalSign));
}

// Serialize Functions
/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool RehearsalSign::DoSerialize(PowerTabOutputStream& stream)
{
    //------Last Checked------//
    // - Dec 10, 2004
    stream << m_letter;
    wxCHECK(stream.CheckState(), false);
    
    stream.WriteMFCString(m_description);
    wxCHECK(stream.CheckState(), false);
    
    return (stream.CheckState());
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool RehearsalSign::DoDeserialize(PowerTabInputStream& stream,
    wxWord WXUNUSED(version))
{
    //------Last Checked------//
    // - Apr 22, 2007
    stream >> m_letter;
    wxCHECK(stream.CheckState(), false);
    
    stream.ReadMFCString(m_description);
    wxCHECK(stream.CheckState(), false);
    
    return (stream.CheckState());
}

// Letter Functions
/// Sets the letter used by the rehearsal sign
/// @param letter Letter to set
bool RehearsalSign::SetLetter(wxInt8 letter)
{
    //------Last Checked------//
    // - Dec 10, 2004
    wxCHECK(IsValidLetter(letter), false);
    m_letter = letter;

    // If the rehearsal sign is being unset, clear the description
    if (letter == notSet)
        m_description.Clear();
    return (true);
}

// Operations
/// Gets a formatted text representation of the rehearsal sign (combines the
/// letter and the description)
/// @return The formatted text representation of the rehearsal sign
wxString RehearsalSign::GetFormattedText() const
{
    //------Last Checked------//
    // - Dec 10, 2004
    return (wxString::Format(wxT("%c -- %s"), GetLetter(),
        GetDescription().c_str()));
}
