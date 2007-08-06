/////////////////////////////////////////////////////////////////////////////
// Name:            rhythmslash.cpp
// Purpose:         Stores and renders a rhythm slash
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 17, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "rhythmslash.h"

#include <math.h>       // Needed for pow

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Default Constants
const wxByte    RhythmSlash::DEFAULT_POSITION                   = 0;
const wxByte    RhythmSlash::DEFAULT_BEAMING                    = 0;
const wxUint32  RhythmSlash::DEFAULT_DATA                       = (wxUint32)(DEFAULT_DURATION_TYPE << 21);
const wxByte    RhythmSlash::DEFAULT_DURATION_TYPE              = 3;    // 8th in power of 2 form

// Position Constants
const wxUint32  RhythmSlash::MIN_POSITION                       = 0;
const wxUint32  RhythmSlash::MAX_POSITION                       = 255;
    
// Single Note String Number Constants
const wxByte    RhythmSlash::MIN_SINGLE_NOTE_STRING_NUMBER      = 1;
const wxByte    RhythmSlash::MAX_SINGLE_NOTE_STRING_NUMBER      = 7;

// Single Note Fret Number Constants
const wxByte    RhythmSlash::MIN_SINGLE_NOTE_FRET_NUMBER        = 0;
const wxByte    RhythmSlash::MAX_SINGLE_NOTE_FRET_NUMBER        = 24;

/// Default Constructor
RhythmSlash::RhythmSlash() :
    m_position(DEFAULT_POSITION), m_beaming(DEFAULT_BEAMING),
    m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Jan 7, 2005
}

/// Primary Constructor
/// @param position Zero-based index within the system where the rhythm slash is
/// anchored
/// @param durationType Duration type to set (1 = whole, 2 = half, 4 = quarter,
/// 8 = 8th, 16 = 16th, 32 = 32nd, 64 = 64th)
/// @param dotCount Number of duration dots to set
RhythmSlash::RhythmSlash(wxUint32 position, wxByte durationType,
    wxByte dotCount) : m_position(position), m_beaming(DEFAULT_BEAMING),
    m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Jan 7, 2005
    wxASSERT(IsValidPosition(position));
    
    SetDurationType(durationType);    
    if (dotCount == 1)
        SetDotted();
    else if (dotCount == 2)
        SetDoubleDotted();
}

/// Copy Constructor
RhythmSlash::RhythmSlash(const RhythmSlash& rhythmSlash) :
    m_position(DEFAULT_POSITION), m_beaming(DEFAULT_BEAMING),
    m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Dec 17, 2004
    *this = rhythmSlash;
}

/// Destructor
RhythmSlash::~RhythmSlash()
{
    //------Last Checked------//
    // - Dec 17, 2004
}

/// Assignment Operator
const RhythmSlash& RhythmSlash::operator=(const RhythmSlash& rhythmSlash)
{
    //------Last Checked------//
    // - Jan 6, 2005
    
    // Check for assignment to self
    if (this != &rhythmSlash)
    {
        m_position = rhythmSlash.m_position;
        m_beaming = rhythmSlash.m_beaming;
        m_data = rhythmSlash.m_data;
    }
    return (*this);
}

/// Equality Operator
bool RhythmSlash::operator==(const RhythmSlash& rhythmSlash) const
{
    //------Last Checked------//
    // - Jan 6, 2005
    return (
        (m_position == rhythmSlash.m_position) &&
        (m_beaming == rhythmSlash.m_beaming) &&
        (m_data == rhythmSlash.m_data)
    );  
}

/// Inequality Operator
bool RhythmSlash::operator!=(const RhythmSlash& rhythmSlash) const
{
    //------Last Checked------//
    // - Jan 7, 2005
    return (!operator==(rhythmSlash));
}

// Serialization functions
/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool RhythmSlash::DoSerialize(PowerTabOutputStream& stream)
{
    //------Last Checked------//
    // - Dec 17, 2004
    stream << m_position << m_beaming << m_data;
    wxCHECK(stream.CheckState(), false);
    return (stream.CheckState());
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool RhythmSlash::DoDeserialize(PowerTabInputStream& stream,
    wxWord WXUNUSED(version))
{
    //------Last Checked------//
    // - Apr 22, 2007
    stream >> m_position >> m_beaming >> m_data;
    wxCHECK(stream.CheckState(), false);
    return (stream.CheckState());
}

// Duration Type Functions
/// Sets the duration type
/// @param durationType Duration type to set (1 = whole, 2 = half, 4 = quarter,
/// 8 = 8th, 16 = 16th)
/// @return True if the duration type was set, false if not
bool RhythmSlash::SetDurationType(wxByte durationType)
{
    //------Last Checked------//
    // - Jan 6, 2005
    wxCHECK(IsValidDurationType(durationType), false);

    // Duration type is stored in power of two format
    m_data &= ~durationTypeMask;
    
    if (durationType == 1)
        durationType = 0;
    else if (durationType == 2)
        durationType = 1;
    else if (durationType == 4)
        durationType = 2;
    else if (durationType == 8)
        durationType = 3;
    else if (durationType == 16)
        durationType = 4;
                	
	m_data |= (wxUint32)(durationType << 21);
	
	return (true);
}

/// Gets the duration type (1 = whole, 2 = half, 4 = quarter, 8 = 8th,
/// 16 = 16th)
/// @return The duration type
wxByte RhythmSlash::GetDurationType() const
{
    //------Last Checked------//
    // - Jan 6, 2005
	wxUint32 temp = ((m_data & durationTypeMask) >> 21);
	// Duration type is stored in power of two form
	return ((wxByte)(pow((double)2, (double)temp)));
}

// Previous Beam Duration Functions
/// Sets the duration type of the previous rhythm slash in the beam group
/// (cache only)
/// @param durationType Duration type to set (0 = not beamed, 8 = 8th,
/// 16 = 16th)
/// @return True if the duration type was set, false if not
bool RhythmSlash::SetPreviousBeamDurationType(wxByte durationType)
{
    //------Last Checked------//
    // - Jan 7, 2005
    wxCHECK(IsValidPreviousBeamDurationType(durationType), false);
    
    // Clear the current duration type
    m_beaming &= ~previousBeamDurationTypeMask;

    if (durationType == 8)
        m_beaming |= previousBeamDuration8th;        
    else if (durationType == 16)
        m_beaming |= previousBeamDuration16th;

    return (true);
}

/// Gets the duration type of the previous rhythm slash in the beam group
/// @return The duration type of the previous rhythm slash in the beam group
/// (0 = not beamed, 8 = 8th, 16 = 16th)
wxByte RhythmSlash::GetPreviousBeamDurationType() const
{
    //------Last Checked------//
    // - Jan 7, 2005
    
    if ((m_beaming & previousBeamDuration8th) == previousBeamDuration8th)
        return (8);
    else if ((m_beaming & previousBeamDuration16th) == previousBeamDuration16th)
        return (16);
    return (0);
}

// Beaming Functions
/// Sets a beaming flag
/// @param flag Flag to set
/// @return True if teh beaming flag was set, false if not
bool RhythmSlash::SetBeamingFlag(wxByte flag)
{
    //------Last Checked------//
    // - Jan 7, 2005
    wxCHECK(IsValidBeamingFlag(flag), false);
    
    // Mutually exclusive operations
    if ((flag & beamStart) == beamStart)
    {
        ClearBeamingFlag(beamEnd);
        flag &= ~beamEnd;
    }
    else if ((flag & beamEnd) == beamEnd)
        ClearBeamingFlag(beamStart);
    
    m_beaming |= flag;
    
    return (true);
}

// Triplet Flag Functions
/// Sets a triplet flag
/// @param flag Flag to set
/// @return True if the triplet flag was set, false if not
bool RhythmSlash::SetTripletFlag(wxByte flag)
{
    //------Last Checked------//
    // - Jan 6, 2005
    wxCHECK(IsValidTripletFlag(flag), false);
    
    // Clear any current triplet flags
    ClearTripletFlag(tripletMask);
       
    // Mutually exclusive operations
    if ((flag & tripletStart) == tripletStart)
        flag = tripletStart;
    else if ((flag & tripletMiddle) == tripletMiddle)
        flag = tripletMiddle;
    else if ((flag & tripletEnd) == tripletEnd)
        flag = tripletEnd;
    
    m_beaming |= flag;
    
    return (true);
}

// Data Flag Functions
/// Sets a data flag
/// @param flag Flag to set
/// @return True if the flag was set, false if not
bool RhythmSlash::SetDataFlag(wxUint32 flag)
{
    //------Last Checked------//
    // - Jan 7, 2005
    wxCHECK(IsValidDataFlag(flag), false);
    
    // Mutually exclusive operations
    if ((flag & dottedMask) != 0)
        ClearDataFlag(dottedMask);
    
    if ((flag & pickStrokeMask) != 0)
        ClearDataFlag(pickStrokeMask);
    
    if ((flag & arpeggioMask) != 0)
        ClearDataFlag(arpeggioMask);
   
    if ((flag & tripletFeelMask) != 0)
        ClearDataFlag(tripletFeelMask);
    
    if ((flag & accentMask) != 0)
        ClearDataFlag(accentMask);
   
    if ((flag & slideIntoMask) != 0)
        ClearDataFlag(slideIntoMask);
   
    if ((flag & slideOutOfMask) != 0)
        ClearDataFlag(slideOutOfMask);
 
    m_data |= flag;
    
    return (true);
}

// Single Note Data Functions
/// Sets the single note data
/// @param stringNumber String number the note is played on
/// @param fretNumber Fret number the note is played on
/// @return True if the single note data was set, false if not
bool RhythmSlash::SetSingleNoteData(wxByte stringNumber, wxByte fretNumber)
{
    //------Last Checked------//
    // - Jan 6, 2005
    wxCHECK(IsValidStringNumber(stringNumber), false);
    wxCHECK(IsValidFretNumber(fretNumber), false);

    if (!SetDataFlag(singleNote))
        return (false);
    
    m_data &= ~singleNoteDataMask;
    m_data |= (wxUint32)(stringNumber << 24);
    m_data |= (wxUint32)(fretNumber << 27);
    
    return (true);
}

/// Gets the single note data (string number + fret number)
/// @param stringNumber Holds the string number return value
/// @param fretNumber Holds the fret number return value
void RhythmSlash::GetSingleNoteData(wxByte& stringNumber,
    wxByte& fretNumber) const
{
    //------Last Checked------//
    // - Jan 6, 2005
    stringNumber = (wxByte)((m_data & stringNumberMask) >> 24);
    fretNumber = (wxByte)((m_data & fretNumberMask) >> 27);
}

/// Clears the single note data
/// @return True if the single note data was cleared, false if not
bool RhythmSlash::ClearSingleNoteData()
{
    //------Last Checked------//
    // - Jan 7, 2005
    if (!ClearDataFlag(singleNote))
        return (false);
    
    m_data &= ~singleNoteDataMask;
    
    return (true);
}
