/////////////////////////////////////////////////////////////////////////////
// Name:            staff.cpp
// Purpose:         Stores and renders a staff
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 16, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "staff.h"

#include "powertabfileheader.h"             // Needed for file version constants
#include "tuning.h"                         // Needed for IsValidStringCount

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Default Constants
const wxByte Staff::DEFAULT_DATA                                        = (wxByte)((DEFAULT_CLEF << 4) | DEFAULT_TABLATURE_STAFF_TYPE);
const wxByte Staff::DEFAULT_CLEF                                        = TREBLE_CLEF;
const wxByte Staff::DEFAULT_TABLATURE_STAFF_TYPE                        = 6;
const wxByte Staff::DEFAULT_STANDARD_NOTATION_STAFF_ABOVE_SPACING       = 9;
const wxByte Staff::DEFAULT_STANDARD_NOTATION_STAFF_BELOW_SPACING       = 9;
const wxByte Staff::DEFAULT_SYMBOL_SPACING                              = 0;
const wxByte Staff::DEFAULT_TABLATURE_STAFF_BELOW_SPACING               = 0;
    
// Clef Constants
const wxByte Staff::TREBLE_CLEF                         = 0;
const wxByte Staff::BASS_CLEF                           = 1;

// Tablature Staff Type Constants
// Note: If these values change, update the Tuning constants for string count
const wxByte Staff::MIN_TABLATURE_STAFF_TYPE            = 3;
const wxByte Staff::MAX_TABLATURE_STAFF_TYPE            = 7;

/// Default Constructor
Staff::Staff() :
    m_data(DEFAULT_DATA), m_standardNotationStaffAboveSpacing(DEFAULT_STANDARD_NOTATION_STAFF_ABOVE_SPACING),
    m_standardNotationStaffBelowSpacing(DEFAULT_STANDARD_NOTATION_STAFF_BELOW_SPACING),
    m_symbolSpacing(DEFAULT_SYMBOL_SPACING), m_tablatureStaffBelowSpacing(DEFAULT_TABLATURE_STAFF_BELOW_SPACING)
{
    //------Last Checked------//
    // - Jan 5, 2005
}

/// Primary Constructor
/// @param tablatureStaffType The type of tablature staff to set (number of strings)
/// @param clef Type of clef to set (see CLEF constants)
Staff::Staff(wxByte tablatureStaffType, wxByte clef) :
    m_data(DEFAULT_DATA), m_standardNotationStaffAboveSpacing(DEFAULT_STANDARD_NOTATION_STAFF_ABOVE_SPACING),
    m_standardNotationStaffBelowSpacing(DEFAULT_STANDARD_NOTATION_STAFF_BELOW_SPACING),
    m_symbolSpacing(DEFAULT_SYMBOL_SPACING), m_tablatureStaffBelowSpacing(DEFAULT_TABLATURE_STAFF_BELOW_SPACING)
{
    //------Last Checked------//
    // - Jan 5, 2005
    SetClef(clef);
    SetTablatureStaffType(tablatureStaffType);
}

/// Copy Constructor
Staff::Staff(const Staff& staff) :
    m_data(DEFAULT_DATA), m_standardNotationStaffAboveSpacing(DEFAULT_STANDARD_NOTATION_STAFF_ABOVE_SPACING),
    m_standardNotationStaffBelowSpacing(DEFAULT_STANDARD_NOTATION_STAFF_BELOW_SPACING),
    m_symbolSpacing(DEFAULT_SYMBOL_SPACING), m_tablatureStaffBelowSpacing(DEFAULT_TABLATURE_STAFF_BELOW_SPACING)
{
    //------Last Checked------//
    // - Jan 5, 2005
    *this = staff;
}

/// Destructor
Staff::~Staff()
{
    //------Last Checked------//
    // - Jan 5, 2005
    m_positionArray[0].DeleteContents();
    m_positionArray[1].DeleteContents();
}

/// Assignment Operator
const Staff& Staff::operator=(const Staff& staff)
{
    //------Last Checked------//
    // - Jan 5, 2005
    
    // Check for assignment to self
    if (this != &staff)
    {
	    m_data = staff.m_data;
	    m_standardNotationStaffAboveSpacing = staff.m_standardNotationStaffAboveSpacing;
	    m_standardNotationStaffBelowSpacing = staff.m_standardNotationStaffBelowSpacing;
	    m_symbolSpacing = staff.m_symbolSpacing;
	    m_tablatureStaffBelowSpacing = staff.m_tablatureStaffBelowSpacing;

        m_positionArray[0].Copy(staff.m_positionArray[0]);
        m_positionArray[1].Copy(staff.m_positionArray[1]);        
    }
	return (*this);
}

/// Equality Operator
bool Staff::operator==(const Staff& staff) const
{
    //------Last Checked------//
    // - Jan 5, 2005
    return (
        (m_data == staff.m_data) &&
        (m_standardNotationStaffAboveSpacing == staff.m_standardNotationStaffAboveSpacing) &&
        (m_standardNotationStaffBelowSpacing == staff.m_standardNotationStaffBelowSpacing) &&
        (m_symbolSpacing == staff.m_symbolSpacing) &&
        (m_tablatureStaffBelowSpacing == staff.m_tablatureStaffBelowSpacing) &&
        (m_positionArray[0].Equals(staff.m_positionArray[0])) &&
        (m_positionArray[1].Equals(staff.m_positionArray[1]))
    );
}

/// Inequality Operator
bool Staff::operator!=(const Staff& staff) const
{
    //------Last Checked------//
    // - Jan 5, 2005
    return (!operator==(staff));
}

// Serialize Functions
/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool Staff::DoSerialize(PowerTabOutputStream& stream)
{
    //------Last Checked------//
    // - Jan 5, 2005
    stream << m_data << m_standardNotationStaffAboveSpacing << m_standardNotationStaffBelowSpacing << m_symbolSpacing << m_tablatureStaffBelowSpacing;
    wxCHECK(stream.CheckState(), false);
    
    m_positionArray[0].Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_positionArray[1].Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    return (stream.CheckState());
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool Staff::DoDeserialize(PowerTabInputStream& stream, wxWord version)
{
    //------Last Checked------//
    // - Jan 5, 2005
    
    // Version 1.0 and 1.0.2, music/tab staff type stored in separate variables
	if (version == PowerTabFileHeader::FILEVERSION_1_0 || version == PowerTabFileHeader::FILEVERSION_1_0_2)
	{
		wxByte clef, tablatureStaffType;
		stream >> clef >> tablatureStaffType >> m_standardNotationStaffAboveSpacing >> m_standardNotationStaffBelowSpacing >> m_symbolSpacing >> m_tablatureStaffBelowSpacing;
		wxCHECK(stream.CheckState(), false);

        SetClef(clef);
		SetTablatureStaffType(tablatureStaffType);
		
		m_positionArray[0].Deserialize(stream, version);
		wxCHECK(stream.CheckState(), false);
		
        m_positionArray[1].Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
	}
	// Version 1.5 and up
	else
	{
		stream >> m_data >> m_standardNotationStaffAboveSpacing >> m_standardNotationStaffBelowSpacing >> m_symbolSpacing >> m_tablatureStaffBelowSpacing;
		wxCHECK(stream.CheckState(), false);
		
        m_positionArray[0].Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        m_positionArray[1].Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
    }

    return (stream.CheckState());
}
    
/// Sets the clef used on the standard notation staff
/// @param clef Clef to set
/// @return True if the clef was set, false if not
bool Staff::SetClef(wxByte clef)
{
    //------Last Checked------//
    // - Jan 5, 2005
    wxCHECK(clef <= 1, false);
    
	m_data &= ~clefMask;
	m_data |= (wxByte)(clef << 4);
	
	return (true);
}

/// Sets the tablature staff type
/// @param type Tablature staff type to set
/// @return True if the tablature staff type was set, false if not
bool Staff::SetTablatureStaffType(wxByte type)
{
    //------Last Checked------//
    // - Jan 5, 2005
    wxCHECK(Tuning::IsValidStringCount(type), false);
    
    m_data &= ~tablatureStaffTypeMask;
	m_data |= type;
	
	return (true);
}
