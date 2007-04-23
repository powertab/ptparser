/////////////////////////////////////////////////////////////////////////////
// Name:            systemsymbol.cpp
// Purpose:         Base class for symbols residing on a system scope
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 13, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "systemsymbol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Default constants
const wxWord        SystemSymbol::DEFAULT_SYSTEM            = 0;
const wxByte        SystemSymbol::DEFAULT_POSITION          = 0;
const wxUint32      SystemSymbol::DEFAULT_DATA              = 0;

// System Constants
const wxUint32      SystemSymbol::MIN_SYSTEM                = 0;
const wxUint32      SystemSymbol::MAX_SYSTEM                = 65535;

// Position Constants
const wxUint32      SystemSymbol::MIN_POSITION              = 0;
const wxUint32      SystemSymbol::MAX_POSITION              = 255;

// Constructor/Destructor
/// Default Constructor
SystemSymbol::SystemSymbol() : 
    m_system(DEFAULT_SYSTEM), m_position(DEFAULT_POSITION), m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Jan 13, 2005
}

/// Primary Constructor
/// @param system Zero-based index of the system where the system symbol is anchored
/// @param position Zero-based index of the position within the system where the system symbol is anchored
/// @param data Data used by the symbol (the data format is dependant upon the derived class)
SystemSymbol::SystemSymbol(wxUint32 system, wxUint32 position, wxUint32 data) :
    m_system(DEFAULT_SYSTEM), m_position(DEFAULT_POSITION), m_data(data)
{
    //------Last Checked------//
    // - Jan 13, 2005
    wxASSERT(IsValidSystem(system));
    wxASSERT(IsValidPosition(position));
    SetSystem(system);
    SetPosition(position);    
}

/// Copy Constructor
SystemSymbol::SystemSymbol(const SystemSymbol& systemSymbol) :
    m_system(DEFAULT_SYSTEM), m_position(DEFAULT_POSITION), m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Jan 13, 2005
    *this = systemSymbol;
}

/// Destructor
SystemSymbol::~SystemSymbol()
{
    //------Last Checked------//
    // - Jan 13, 2005
}

/// Assignment Operator
const SystemSymbol& SystemSymbol::operator=(const SystemSymbol& systemSymbol)
{
    //------Last Checked------//
    // - Jan 13, 2005

    // Check for assignment to self
    if (this != &systemSymbol)
    {
        m_system = systemSymbol.m_system;
        m_position = systemSymbol.m_position;
        m_data = systemSymbol.m_data;
    }
    return (*this);
}

/// Equality Operator
bool SystemSymbol::operator==(const SystemSymbol& systemSymbol) const
{
    //------Last Checked------//
    // - Jan 12, 2005
    return (
        (m_system == systemSymbol.m_system) &&
        (m_position == systemSymbol.m_position) &&
        (m_data == systemSymbol.m_data)
    );
}

/// Inequality Operator
bool SystemSymbol::operator!=(const SystemSymbol& systemSymbol) const
{
    //------Last Checked------//
    // - Jan 12, 2005
    return (!operator==(systemSymbol));
}

// Serialize Functions
/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool SystemSymbol::DoSerialize(PowerTabOutputStream& stream)
{
    //------Last Checked------//
    // - Jan 13, 2005
    stream << m_system << m_position << m_data;
    wxCHECK(stream.CheckState(), false);
    return (stream.CheckState());
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool SystemSymbol::DoDeserialize(PowerTabInputStream& stream,
    wxWord WXUNUSED(version))
{
    //------Last Checked------//
    // - Apr 22, 2007
    stream >> m_system >> m_position >> m_data;
    wxCHECK(stream.CheckState(), false);
    return (stream.CheckState());
}
