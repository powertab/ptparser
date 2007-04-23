/////////////////////////////////////////////////////////////////////////////
// Name:            barline.cpp
// Purpose:         Stores and renders barlines
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 4, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "barline.h"

#include "powertabfileheader.h"         // Needed for FILE_VERSION constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Default Constants
const wxByte Barline::DEFAULT_POSITION      = 0;
const wxByte Barline::DEFAULT_DATA          = (wxByte)(bar << 5);

// Repeat Count Constants
const wxByte Barline::MIN_REPEAT_COUNT      = 2;
const wxByte Barline::MAX_REPEAT_COUNT      = 24;
    
// Constructor/Destructor
/// Default Constructor
Barline::Barline() : 
    m_position(DEFAULT_POSITION), m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Jan 4, 2005
}

/// Primary Constructor
/// @param position Zero-based index of the position within the system where the barline is anchored
/// @param type The type of barline (see barTypes enum)
/// @param repeatCount The repeat count to set (if type is a repeat end, use 0 for other types)
Barline::Barline(wxUint32 position, wxByte type, wxByte repeatCount) : 
    m_position(DEFAULT_POSITION), m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Jan 4, 2005
    SetPosition(position);
    SetType(type);
    SetRepeatCount(repeatCount);
}

/// Copy Constructor
Barline::Barline(const Barline& barline) :
    m_position(DEFAULT_POSITION), m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Jan 4, 2005
    *this = barline;
}

/// Destructor
Barline::~Barline()
{
    //------Last Checked------//
    // - Jan 4, 2005
}

/// Assignment Operator
const Barline& Barline::operator=(const Barline& barline)
{
    //------Last Checked------//
    // - Jan 4, 2005
    
    // Check for assignment to self
    if (this != &barline)
    {
        m_position = barline.m_position;
        m_data = barline.m_data;
        m_keySignature = barline.m_keySignature;
        m_timeSignature = barline.m_timeSignature;
        m_rehearsalSign = barline.m_rehearsalSign;
    }
    return (*this);
}

/// Equality Operator
bool Barline::operator==(const Barline& barline) const
{
    //------Last Checked------//
    // - Jan 4, 2005
    return (
        (m_position == barline.m_position) &&
        (m_data == barline.m_data) &&
        (m_keySignature == barline.m_keySignature) &&
        (m_timeSignature == barline.m_timeSignature) &&
        (m_rehearsalSign == barline.m_rehearsalSign)
    );
}

/// Inequality Operator
bool Barline::operator!=(const Barline& barline) const
{
    //------Last Checked------//
    // - Jan 4, 2005
    return (!operator==(barline));
}

// Serialize Functions
/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool Barline::DoSerialize(PowerTabOutputStream& stream)
{
    //------Last Checked------//
    // - Jan 4, 2005
    stream << m_position << m_data;
    wxCHECK(stream.CheckState(), false);
    
    m_keySignature.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_timeSignature.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_rehearsalSign.Serialize(stream);
    wxCHECK(stream.CheckState(), false);

    return (true);
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool Barline::DoDeserialize(PowerTabInputStream& stream, wxWord version)
{
    //------Last Checked------//
    // - Jan 4, 2005
    
    // Version 1.0/1.0.2 (key was stored in word)
    if (version == PowerTabFileHeader::FILEVERSION_1_0 || version == PowerTabFileHeader::FILEVERSION_1_0_2)
    {
        wxWord symbol;
        stream >> m_position >> symbol;
        wxCHECK(stream.CheckState(), false);

        wxByte temp = HIBYTE(symbol);
        wxByte keyType = (wxByte)((temp >> 4) & 0xf);
        wxByte keyAccidentals = (wxByte)(temp & 0xf);

        // Key signature was set
        if (keyType > 0)
        {
            // Set the key to be shown
            m_keySignature.Show();

            // Cancellation
            if (keyType > 2)
                m_keySignature.SetCancellation();

            keyType = (wxByte)(((keyType % 2) == 1) ? KeySignature::majorKey : KeySignature::minorKey);

            m_keySignature.SetKey(keyType, keyAccidentals);
        }
        
        // Update the bar data (stored in low byte of symbol)
        m_data = LOBYTE(symbol);
    }
    // CASE: Version 1.5 and up
    else
    {        
        stream >> m_position >> m_data;
        wxCHECK(stream.CheckState(), false);
        
        m_keySignature.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        m_timeSignature.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        m_rehearsalSign.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
    }
    
    return (true);
}

// Barline Data Functions
/// Sets the barline data
/// @param type The type to set
/// @param repeatCount The repeat count to set
/// @return True if the data was set, false if not
bool Barline::SetBarlineData(wxByte type, wxByte repeatCount)
{
    //------Last Checked------//
    // - Jan 4, 2005
    if (!SetType(type))
        return (false);
    if (!SetRepeatCount(repeatCount))
        return (false);
    return (true);
}

/// Gets the barline data
/// @param type Holds the type return value
/// @param repeatCount Holds the repeat count return value
void Barline::GetBarlineData(wxByte& type, wxByte& repeatCount) const
{
    //------Last Checked------//
    // - Jan 4, 2005
    type = GetType();
    repeatCount = (wxByte)GetRepeatCount();
}
    
// Type Functions
/// Sets the type of bar
/// @param type Type of bar to set
/// @return True if the bar type was set, false if not
bool Barline::SetType(wxByte type)
{
    //------Last Checked------//
    // - Jan 4, 2005
    wxCHECK(IsValidType(type), false);
    
    m_data &= ~typeMask;
    m_data |= (wxByte)(type << 5);
    
    return (true);
}

// Repeat Count Functions
/// Sets the repeat count for a repeat ending bar
/// @param repeatCount Repeat count to set
/// @return True if the repeat count was set, false if not
bool Barline::SetRepeatCount(wxUint32 repeatCount)
{
    //------Last Checked------//
    // - Jan 4, 2005
    wxCHECK(IsValidRepeatCount(repeatCount), false);
    
    m_data &= ~repeatCountMask;
    m_data |= (wxByte)repeatCount;
    
    return (true);
}
