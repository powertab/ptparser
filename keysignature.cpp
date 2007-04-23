/////////////////////////////////////////////////////////////////////////////
// Name:            keysignature.cpp
// Purpose:         Stores and renders a key signature
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "keysignature.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Default constants
const wxByte       KeySignature::DEFAULT_DATA              = 0;

/// Default Constructor
KeySignature::KeySignature() : 
    m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Dec 10, 2004
}

/// Primary Constructor
/// @param keyType major or minor (see keyTypes enum in .h for values)
/// @param keyAccidentals type and number of accidentals (4 sharps, 2 flats, etc.; see keyAccidentals enum in .h for values)
KeySignature::KeySignature(wxByte keyType, wxByte keyAccidentals) :
    m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Dec 10, 2004
    SetKey(keyType, keyAccidentals);
}
    
/// Copy Constructor
KeySignature::KeySignature(const KeySignature& keySignature) :
    m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Dec 10, 2004
    *this = keySignature;
}

/// Destructor
KeySignature::~KeySignature()
{
    //------Last Checked------//
    // - Dec 10, 2004
}

/// Assignment Operator
const KeySignature& KeySignature::operator=(const KeySignature& keySignature)
{
    //------Last Checked------//
    // - Dec 10, 2004

    // Check for assignment to self
    if (this != &keySignature)
        m_data = keySignature.m_data;
    return (*this);
}

/// Equality operator
bool KeySignature::operator==(const KeySignature& keySignature) const
{
    //------Last Checked------//
    // - Dec 10, 2004
    return (m_data == keySignature.m_data);
}

/// Inequality operator
bool KeySignature::operator!=(const KeySignature& keySignature) const
{
    //------Last Checked------//
    // - Dec 10, 2004
    return (!operator==(keySignature));
}

// Serialize Functions
/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool KeySignature::DoSerialize(PowerTabOutputStream& stream)
{
    //------Last Checked------//
    // - Dec 10, 2004
    stream << m_data;
    wxCHECK(stream.CheckState(), false);
    
    return (stream.CheckState());
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool KeySignature::DoDeserialize(PowerTabInputStream& stream,
    wxWord WXUNUSED(version))
{
    //------Last Checked------//
    // - Apr 22, 2007
    stream >> m_data;
    wxCHECK(stream.CheckState(), false);
    
    return (stream.CheckState());
}

// Key Functions
/// Sets the key type and accidentals
/// @param keyType major or minor (see keyTypes enum in .h for values)
/// @param keyAccidentals type and number of accidentals (4 sharps, 2 flats, etc.; see keyAccidentals enum in .h for values)
bool KeySignature::SetKey(wxByte keyType, wxByte keyAccidentals)
{
    //------Last Checked------//
    // - Dec 11, 2004
    if (!SetKeyType(keyType))
        return (false);
    if (!SetKeyAccidentals(keyAccidentals))
        return (false);
    return (true);
}

/// Gets the key type and accidentals
/// @param keyType major or minor (see keyTypes enum in .h for values)
/// @param keyAccidentals type and number of accidentals (4 sharps, 2 flats, etc.; see keyAccidentals enum in .h for values)
void KeySignature::GetKey(wxByte& keyType, wxByte& keyAccidentals) const
{
    //------Last Checked------//
    // - Dec 11, 2004
    keyType = GetKeyType();
    keyAccidentals = GetKeyAccidentals();

    // Cancellations store the key of the cancelled type, but we know that the cancellations will always
    // occur on C Major/A Minor so set the key to 0
    if (IsCancellation())
        keyAccidentals = 0;
}

/// Gets the key type and accidentals required to draw the key signature
/// @param keyType major or minor (see keyTypes enum in .h for values)
/// @param keyAccidentals type and number of accidentals (4 sharps, 2 flats, etc.; see keyAccidentals enum in .h for values)
/// @return True if the key is a cancellation, false if not
bool KeySignature::GetDrawKey(wxByte& keyType, wxByte& keyAccidentals) const
{
    //------Last Checked------//
    // - Dec 11, 2004
    keyType = GetKeyType();
    keyAccidentals = (wxByte)(m_data & keyAccidentalsMask);
    return (IsCancellation());
}

// Key Type Functions
/// Sets the key type
/// @param keyType Key type to set (see keyType enum in .h for values)
/// @return True if the key type was set, false if not
bool KeySignature::SetKeyType(wxByte keyType)
{
    //------Last Checked------//
    // - Dec 11, 2004
    wxCHECK(IsValidKeyType(keyType), false);
    m_data &= ~keyTypeMask;
    m_data |= (keyType << 6);
    return (true);
}

// Key Accidentals Functions
/// Sets the type and number of accidentals in the key signature (4 sharps, 2 flats, etc.)
/// @param keyAccidentals Type and number of accidentals to set
/// @return True if the key accidentals was set, false if not
bool KeySignature::SetKeyAccidentals(wxByte keyAccidentals)
{
    //------Last Checked------//
    // - Dec 11, 2004
    wxCHECK(IsValidKeyAccidentals(keyAccidentals), false);
    m_data &= ~keyAccidentalsMask;
    m_data |= keyAccidentals;    
    return (true);
}

/// Gets the type and number of accidentals in the key signature (4 sharps, 2 flats, etc.)
/// @return Type and number of accidentals in the key signature (see keyAccidentals enum in .h for values)
wxByte KeySignature::GetKeyAccidentals() const
{
    //------Last Checked------//
    // - Dec 10, 2004
    wxByte returnValue = (wxByte)(m_data & keyAccidentalsMask);
    
    // Cancellations store the key of the cancelled type, but we know that the cancellations will always
    // occur on C Major/A Minor so set the key to 0
    if (IsCancellation())
        returnValue = 0;
    return (returnValue);
}

// Operations
/// Gets a text representation of the key signature
/// @return A text representation of the key signature
wxString KeySignature::GetText() const
{
    //------Last Checked------//
    // - Apr 25, 2006
    wxString returnValue;

    if (HasOneSharp())
        returnValue = "#";
    else if (HasTwoSharps())
        returnValue = "##";
    else if (HasThreeSharps())
        returnValue = "###";
    else if (HasFourSharps())
        returnValue = "####";
    else if (HasFiveSharps())
        returnValue = "#####";
    else if (HasSixSharps())
        returnValue = "######";
    else if (HasSevenSharps())
        returnValue = "#######";
    else if (HasOneFlat())
        returnValue = "b";
    else if (HasTwoFlats())
        returnValue = "bb";
    else if (HasThreeFlats())
        returnValue = "bbb";
    else if (HasFourFlats())
        returnValue = "bbbb";
    else if (HasFiveFlats())
        returnValue = "bbbbb";
    else if (HasSixFlats())
        returnValue = "bbbbbb";
    else if (HasSevenFlats())
        returnValue = "bbbbbbb";

    if (IsMinorKey())
        returnValue += "m";

    return (returnValue);
}
