/////////////////////////////////////////////////////////////////////////////
// Name:            dynamic.cpp
// Purpose:         Stores and renders a dynamic
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 13, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "dynamic.h"

#include "powertabfileheader.h"         // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Default constants
const wxWord        Dynamic::DEFAULT_SYSTEM                     = 0;
const wxByte        Dynamic::DEFAULT_STAFF                      = 0;
const wxByte        Dynamic::DEFAULT_POSITION                   = 0;
const wxWord        Dynamic::DEFAULT_DATA                       = MAKEWORD(DEFAULT_RHYTHM_SLASH_VOLUME, DEFAULT_STAFF_VOLUME);
const wxByte        Dynamic::DEFAULT_STAFF_VOLUME               = Dynamic::fff;
const wxByte        Dynamic::DEFAULT_RHYTHM_SLASH_VOLUME        = 0;
    
// System Constants
const wxUint32      Dynamic::MIN_SYSTEM                 = 0;
const wxUint32      Dynamic::MAX_SYSTEM                 = 65535;

// Staff Constants
const wxUint32      Dynamic::MIN_STAFF                  = 0;
const wxUint32      Dynamic::MAX_STAFF                  = 2;

// Position Constants
const wxUint32      Dynamic::MIN_POSITION               = 0;
const wxUint32      Dynamic::MAX_POSITION               = 255;

// Constructor/Destructor
/// Default Constructor
Dynamic::Dynamic() :
    m_system(DEFAULT_SYSTEM), m_staff(DEFAULT_STAFF),
    m_position(DEFAULT_POSITION), m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Jan 12, 2005
}

/// Primary Constructor
/// @param system Zero-based index of the system where the dynamic is anchored
/// @param staff Zero-based index of the staff where the dynamic is anchored
/// @param position Zero-based index of the position within the system where the
/// dynamic is anchored
/// @param staffVolume Staff volume to set (see volumeLevels enum)
/// @param rhythmSlashVolume Rhythm slash volume to set (see volumeLevels enum)
Dynamic::Dynamic(wxUint32 system, wxUint32 staff, wxUint32 position,
    wxByte staffVolume, wxByte rhythmSlashVolume) : m_system(DEFAULT_SYSTEM),
    m_staff(DEFAULT_STAFF), m_position(DEFAULT_POSITION), m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Jan 12, 2005
    wxASSERT(IsValidSystem(system));
    wxASSERT(IsValidStaff(staff));
    wxASSERT(IsValidPosition(position));
    SetSystem(system);
    SetStaff(staff);
    SetPosition(position);
    SetStaffVolume(staffVolume);
    SetRhythmSlashVolume(rhythmSlashVolume);
}

/// Copy Constructor
Dynamic::Dynamic(const Dynamic& dynamic) :
    m_system(DEFAULT_SYSTEM), m_staff(DEFAULT_STAFF),
    m_position(DEFAULT_POSITION), m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Jan 12, 2005
    *this = dynamic;
}

/// Destructor
Dynamic::~Dynamic()
{
    //------Last Checked------//
    // - Jan 12, 2005
}

/// Assignment Operator
const Dynamic& Dynamic::operator=(const Dynamic& dynamic)
{
    //------Last Checked------//
    // - Jan 12, 2005

    // Check for assignment to self
    if (this != &dynamic)
    {
        m_system = dynamic.m_system;
        m_staff = dynamic.m_staff;
        m_position = dynamic.m_position;
        m_data = dynamic.m_data;
    }
    return (*this);
}

/// Equality Operator
bool Dynamic::operator==(const Dynamic& dynamic) const
{
    //------Last Checked------//
    // - Jan 12, 2005
    return (
        (m_system == dynamic.m_system) &&
        (m_staff == dynamic.m_staff) &&
        (m_position == dynamic.m_position) &&
        (m_data == dynamic.m_data)
    );
}

/// Inequality Operator
bool Dynamic::operator!=(const Dynamic& dynamic) const
{
    //------Last Checked------//
    // - Jan 12, 2005
    return (!operator==(dynamic));
}

/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool Dynamic::DoSerialize(PowerTabOutputStream& stream)
{
    //------Last Checked------//
    // - Jan 12, 2005
    stream << m_system << m_staff << m_position << m_data;
    wxCHECK(stream.CheckState(), false);
   
    return (stream.CheckState());
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool Dynamic::DoDeserialize(PowerTabInputStream& stream, wxWord version)
{
    //------Last Checked------//
    // - Jan 12, 2005
    
    // Version 1.0 and 1.0.2 (only staff volume was stored)
    if (version == PowerTabFileHeader::FILEVERSION_1_0 ||
        version == PowerTabFileHeader::FILEVERSION_1_0_2)
    {
        wxByte staffVolume;
        stream >> m_system >> m_staff >> m_position >> staffVolume;
        wxCHECK(stream.CheckState(), false);
        
        m_data = MAKEWORD(notSet, staffVolume);
    }
    // Latest version
    else
    {
        stream >> m_system >> m_staff >> m_position >> m_data;
        wxCHECK(stream.CheckState(), false);
    }
            
    return (stream.CheckState());
}

// Volume Functions
/// Sets the volume
/// @param rhythmSlashes True to set the rhythm slash volume, false to set the
/// staff volume
/// @param volume Volume to set
/// @return True if the volume was set, false if not
bool Dynamic::SetVolume(bool rhythmSlashes, wxByte volume)
{
    //------Last Checked------//
    // - Jan 12, 2005
    wxCHECK(IsValidVolume(volume), false);
    
    if (rhythmSlashes)
        m_data = MAKEWORD(volume, GetStaffVolume());
    else
        m_data = MAKEWORD(GetRhythmSlashVolume(), volume);
        
    return (true);
}

/// Gets the volume
/// @param rhythmSlashes True to get the rhythm slash volume, false to get the
/// staff volume
/// @return The volume
wxByte Dynamic::GetVolume(bool rhythmSlashes) const
{
    //------Last Checked------//
    // - Jan 12, 2005
    if (rhythmSlashes)
        return (LOBYTE(m_data));
    return (HIBYTE(m_data));
}

/// Determines if the volume is set
/// @param rhythmSlashes True to test if the rhythm slash volume is set, false
/// to test if the staff volume is set
/// @return True if the volume is set, false if not
bool Dynamic::IsVolumeSet(bool rhythmSlashes) const
{
    //------Last Checked------//
    // - Jan 13, 2005
    wxByte volume = ((rhythmSlashes) ? GetRhythmSlashVolume() :
        GetStaffVolume());
    return (volume != notSet);
}

// Operations
/// Returns a text representation of the dynamic volume level (i.e. mf, ppp,
/// etc.)
/// @param rhythmSlashes If true, gets the rhythm slash volume level text,
/// otherwise the staff volume level text
/// @return A text representation of the volume level
wxString Dynamic::GetText(bool rhythmSlashes) const
{
    //------Last Checked------//
    // - Jan 13, 2005
    // Get the appropriate volume level
    wxByte volume = GetVolume(rhythmSlashes);

    if (volume == Dynamic::off)
        return (wxT("off"));
    else if (volume <= Dynamic::ppp)
        return (wxT("ppp"));
    else if (volume <= Dynamic::pp)
        return (wxT("pp"));
    else if (volume <= Dynamic::p)
        return (wxT("p"));
    else if (volume <= Dynamic::mp)
        return (wxT("mp"));
    else if (volume <= Dynamic::mf)
        return (wxT("mf"));
    else if (volume <= Dynamic::f)
        return (wxT("f"));
    else if (volume <= Dynamic::ff)
        return (wxT("ff"));
    
    return (wxT("fff"));
}
