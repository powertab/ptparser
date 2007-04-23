/////////////////////////////////////////////////////////////////////////////
// Name:            guitarin.cpp
// Purpose:         Stores and renders guitar in symbols
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 16, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "guitarin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Default constants
const wxWord        GuitarIn::DEFAULT_SYSTEM                = 0;
const wxByte        GuitarIn::DEFAULT_STAFF                 = 0;
const wxByte        GuitarIn::DEFAULT_POSITION              = 0;
const wxWord        GuitarIn::DEFAULT_DATA                  = 0;
    
// System Constants
const wxUint32      GuitarIn::MIN_SYSTEM                    = 0;
const wxUint32      GuitarIn::MAX_SYSTEM                    = 65535;

// Staff Constants
const wxUint32      GuitarIn::MIN_STAFF                     = 0;
const wxUint32      GuitarIn::MAX_STAFF                     = 2;

// Position Constants
const wxUint32      GuitarIn::MIN_POSITION                  = 0;
const wxUint32      GuitarIn::MAX_POSITION                  = 255;

/// Default Constructor
GuitarIn::GuitarIn() :
    m_system(DEFAULT_SYSTEM), m_staff(DEFAULT_STAFF), m_position(DEFAULT_POSITION), m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Jan 25, 2005
}

/// Primary Constructor
/// @param system Zero-based index of the system where the guitar in is anchored
/// @param staff Zero-based inded of the staff within the system where the guitar in is anchored
/// @param position Zero-based index of the position within the system where the guitar in is anchored
/// @param staffGuitars A bit map representing the guitars to set on the staff (bit 1 = guitar 0, bit 2 = guitar 1, etc.)
/// @param rhythmSlashGuitars A bit map representing the guitars to set for the rhythm slashes (bit 1 = guitar 0, bit 2 = guitar 1, etc.)
GuitarIn::GuitarIn(wxUint32 system, wxUint32 staff, wxUint32 position, wxByte staffGuitars, wxByte rhythmSlashGuitars) :
    m_system(DEFAULT_SYSTEM), m_staff(DEFAULT_STAFF), m_position(DEFAULT_POSITION), m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Jan 25, 2005
    wxASSERT(IsValidSystem(system));
    wxASSERT(IsValidStaff(staff));
    wxASSERT(IsValidPosition(position));
    SetSystem(system);
    SetStaff(staff);
    SetPosition(position);
    SetStaffGuitars(staffGuitars);
    SetRhythmSlashGuitars(rhythmSlashGuitars);
}

/// Copy Constructor
GuitarIn::GuitarIn(const GuitarIn& guitarIn) :
    m_system(DEFAULT_SYSTEM), m_staff(DEFAULT_STAFF), m_position(DEFAULT_POSITION), m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Dec 16, 2004
    *this = guitarIn;
}

/// Destructor
GuitarIn::~GuitarIn()
{
    //------Last Checked------//
    // - Dec 16, 2004
}

/// Assignment Operator
const GuitarIn& GuitarIn::operator=(const GuitarIn& guitarIn)
{
    //------Last Checked------//
    // - Jan 25, 2005
    
    // Check for assignment to self
    if (this != &guitarIn)
    {
        m_system = guitarIn.m_system;
        m_staff = guitarIn.m_staff;
        m_position = guitarIn.m_position;
        m_data = guitarIn.m_data;
    }
    return (*this);
}

/// Equality Operator
bool GuitarIn::operator==(const GuitarIn& guitarIn) const
{
    //------Last Checked------//
    // - Jan 25, 2005
    return (
        (m_system == guitarIn.m_system) &&
        (m_staff == guitarIn.m_staff) &&
        (m_position == guitarIn.m_position) &&
        (m_data == guitarIn.m_data)
    );    
}

/// Inequality Operator
bool GuitarIn::operator!=(const GuitarIn& guitarIn) const
{
    //------Last Checked------//
    // - Jan 5, 2005
    return (!operator==(guitarIn));
}

// Serialize Functions
/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool GuitarIn::DoSerialize(PowerTabOutputStream& stream)
{
    //------Last Checked------//
    // - Jan 25, 2005
    stream << m_system << m_staff << m_position << m_data;
    wxCHECK(stream.CheckState(), false);
    
    return (stream.CheckState());
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool GuitarIn::DoDeserialize(PowerTabInputStream& stream,
    wxWord WXUNUSED(version))
{
    //------Last Checked------//
    // - Apr 22, 2007
    stream >> m_system >> m_staff >> m_position >> m_data;
    wxCHECK(stream.CheckState(), false);
    
    return (stream.CheckState());
}

// Guitars Functions
/// Sets the guitars
/// @param rhythmSlashes True to set the rhythm slash guitars, false to set the staff guitars
/// @param guitars A bit map representing the guitars to set (bit 1 = guitar 0, bit 2 = guitar 1, etc.)
/// @return True if the guitars was set, false if not
bool GuitarIn::SetGuitars(bool rhythmSlashes, wxByte guitars)
{
    //------Last Checked------//
    // - Jan 25, 2005   
    if (rhythmSlashes)
        m_data = MAKEWORD(guitars, GetStaffGuitars());
    else
        m_data = MAKEWORD(GetRhythmSlashGuitars(), guitars);
        
    return (true);
}

/// Gets the guitars
/// @param rhythmSlashes True to get the rhythm slash guitars, false to get the staff guitars
/// @return A bit map representing the guitars (bit map where bit 1 = guitar 0, bit 2 = guitar 1, etc.)
wxByte GuitarIn::GetGuitars(bool rhythmSlashes) const
{
    //------Last Checked------//
    // - Jan 25, 2005
    if (rhythmSlashes)
        return (LOBYTE(m_data));
    return (HIBYTE(m_data));
}

/// Determines if the guitars is set
/// @param rhythmSlashes True to test if the rhythm slash guitars are set, false to test if the staff guitars are set
/// @return True if the guitars is set, false if not
bool GuitarIn::HasGuitarsSet(bool rhythmSlashes) const
{
    //------Last Checked------//
    // - Jan 25, 2005
    wxByte guitars = ((rhythmSlashes) ? GetRhythmSlashGuitars() : GetStaffGuitars());
    return (guitars != 0);
}

// Operations
/// Returns a text representation of the guitar in (i.e. Gtr I, II)
/// @param rhythmSlashes If true, gets the rhythm slash guitars text, otherwise the staff guitars text
/// @return A text representation of the guitars
wxString GuitarIn::GetText(bool rhythmSlashes) const
{
    //------Last Checked------//
    // - Jan 25, 2005
    wxByte guitars = GetGuitars(rhythmSlashes);

    if (guitars == 0)
        return wxT("");

    wxString returnValue;
    wxString romanNumerals;
    
    // Loop through, add guitars as we go - there are only 7 guitars    
    wxByte mask = 1;
    wxUint32 guitarCount = 0;
    wxUint32 guitarNumber = 1;
    for (;; mask *= 2, guitarNumber++)
    {
        // Guitar is set
        if ((guitars & mask) == mask)
        {
            // Add a comma if we already have a numeral
            if (!romanNumerals.IsEmpty())
                romanNumerals += wxT(", ");
            
            // Add the roman numeral
            romanNumerals += wxArabicToRoman(guitarNumber, true);
            guitarCount++;
        }
        
        // block overflow
        if (mask == 64)
            break;
    }

    // Add the symbol Gtr before
    if (guitarCount == 1)
        returnValue = wxString::Format(_T("Gtr %s"), romanNumerals.c_str());
    else
        returnValue = wxString::Format(_T("Gtrs %s"), romanNumerals.c_str());

    return (returnValue);
}
