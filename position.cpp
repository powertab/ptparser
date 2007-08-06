/////////////////////////////////////////////////////////////////////////////
// Name:            position.cpp
// Purpose:         Stores and renders a position (a group of notes, or a rest)
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 17, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "position.h"

#include "powertabfileheader.h"     // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Constants
// Default Constants
const wxByte    Position::DEFAULT_POSITION                              = 0;
const wxByte    Position::DEFAULT_BEAMING                               = 0;
const wxUint32  Position::DEFAULT_DATA                                  = (wxUint32)(DEFAULT_DURATION_TYPE << 24);
const wxByte    Position::DEFAULT_DURATION_TYPE                         = 8;

// Position Constants
const wxUint32  Position::MIN_POSITION                                  = 0;
const wxUint32  Position::MAX_POSITION                                  = 255;

// Irregular Grouping Constants
const wxByte    Position::MIN_IRREGULAR_GROUPING_NOTES_PLAYED           = 2;
const wxByte    Position::MAX_IRREGULAR_GROUPING_NOTES_PLAYED           = 16;
const wxByte    Position::MIN_IRREGULAR_GROUPING_NOTES_PLAYED_OVER      = 2;
const wxByte    Position::MAX_IRREGULAR_GROUPING_NOTES_PLAYED_OVER      = 8;

const wxByte    Position::MAX_VOLUME_SWELL_DURATION                     = 8;

const wxByte    Position::MAX_TREMOLO_BAR_DURATION                      = 8;
const wxByte    Position::MAX_TREMOLO_BAR_PITCH                         = 28;

// Multibar Rest Constants
const wxByte    Position::MIN_MULTIBAR_REST_MEASURE_COUNT               = 2;
const wxByte    Position::MAX_MULTIBAR_REST_MEASURE_COUNT               = 255;
    
/// Default Constructor
Position::Position() :
    m_position(DEFAULT_POSITION), m_beaming(DEFAULT_BEAMING),
    m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Jan 18, 2005
	ClearComplexSymbolArrayContents();
}

/// Primary Constructor
/// @param position Zero-based index within the system where the position is
/// anchored
/// @param durationType Duration type to set (1 = whole, 2 = half, 4 = quarter,
/// 8 = 8th, 16 = 16th, 32 = 32nd, 64 = 64th)
/// @param dotCount Number of duration dots to set
Position::Position(wxUint32 position, wxByte durationType, wxByte dotCount) :
    m_position(position), m_beaming(DEFAULT_BEAMING), m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Jan 18, 2005
    wxASSERT(IsValidPosition(position));
	wxASSERT(IsValidDurationType(durationType));
	   
    SetDurationType(durationType);
    if (dotCount == 1)
        SetDotted();
    else if (dotCount == 2)
        SetDoubleDotted();

	ClearComplexSymbolArrayContents();
}

/// Copy Constructor
Position::Position(const Position& position) :
    m_position(DEFAULT_POSITION), m_beaming(DEFAULT_BEAMING),
    m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Dec 17, 2004
    *this = position;
}

/// Destructor
Position::~Position()
{
    //------Last Checked------//
    // - Jan 18, 2005
	ClearComplexSymbolArrayContents();
	m_noteArray.DeleteContents();
}

/// Assignment Operator
const Position& Position::operator=(const Position& position)
{
    //------Last Checked------//
    // - Jan 18, 2005
    
    // Check for assignment to self
    if (this != &position)
    {
	    m_position = position.m_position;
	    m_beaming = position.m_beaming;
	    m_data = position.m_data;
    	
        size_t i = 0;
	    for (; i < MAX_POSITION_COMPLEX_SYMBOLS; i++)
		    m_complexSymbolArray[i] = position.m_complexSymbolArray[i];

	    m_noteArray.Copy(position.m_noteArray);
    }
	return (*this);
}

/// Equality Operator
bool Position::operator==(const Position& position) const
{
    //------Last Checked------//
    // - Jan 19, 2005
    
    wxArrayInt thisComplexSymbolArray;
    wxArrayInt thatComplexSymbolArray;
    
	wxUint32 i = 0;
	for (; i < MAX_POSITION_COMPLEX_SYMBOLS; i++)
	{
	    thisComplexSymbolArray.Add(m_complexSymbolArray[i]);
	    thatComplexSymbolArray.Add(position.m_complexSymbolArray[i]);
	}
	
	thisComplexSymbolArray.Sort(wxCompareIntegers);
	thatComplexSymbolArray.Sort(wxCompareIntegers);

    i = 0;
	for (; i < MAX_POSITION_COMPLEX_SYMBOLS; i++)
	{
	    if (thisComplexSymbolArray[i] != thatComplexSymbolArray[i])
	        return (false);
	}
	
	return (
	    (m_position == position.m_position) &&
	    (m_beaming == position.m_beaming) &&
	    (m_data == position.m_data) &&
	    (m_noteArray.Equals(position.m_noteArray))
    );
}

/// Inequality Operator
bool Position::operator!=(const Position& position) const
{
    //------Last Checked------//
    // - Dec 17, 2004
	return (!operator==(position));
}

// Serialization Functions
/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool Position::DoSerialize(PowerTabOutputStream& stream)
{
    //------Last Checked------//
    // - Jan 17, 2005
    stream << m_position << m_beaming << m_data;
    wxCHECK(stream.CheckState(), false);
    
	wxByte complexCount = GetComplexSymbolCount();
	stream << complexCount;
	wxCHECK(stream.CheckState(), false);

	size_t i = 0;
	for (; i < complexCount; i++)
	{
		stream << m_complexSymbolArray[i];
		wxCHECK(stream.CheckState(), false);
    }
		
    m_noteArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    return (stream.CheckState());
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool Position::DoDeserialize(PowerTabInputStream& stream, wxWord version)
{
    //------Last Checked------//
    // - Jan 17, 2005
    
    // Version 1.0/1.0.2 beaming updated
	if (version == PowerTabFileHeader::FILEVERSION_1_0 ||
        version == PowerTabFileHeader::FILEVERSION_1_0_2)
	{
		stream >> m_position >> m_beaming >> m_data;
		wxCHECK(stream.CheckState(), false);
		
		// All we have to do is move the irregular flags to the duration
        // variable, the document will be rebeamed in the CDocument::Serialize()
		if ((m_beaming & 0x2000) == 0x2000)
			m_data |= irregularGroupingStart;
		if ((m_beaming & 0x4000) == 0x4000)
			m_data |= irregularGroupingMiddle;
		if ((m_beaming & 0x8000) == 0x8000)
			m_data |= irregularGroupingEnd;

		wxByte complexCount;
		stream >> complexCount;
		wxCHECK(stream.CheckState(), false);

		// Read the symbols
		size_t i = 0;
		for (; i < complexCount; i++)
		{
			stream >> m_complexSymbolArray[i];
			wxCHECK(stream.CheckState(), false);
	    }
			
	    m_noteArray.Deserialize(stream, version);
	    wxCHECK(stream.CheckState(), false);
	}
	// Version 1.5 and up
	else
	{
		stream >> m_position >> m_beaming >> m_data;
		wxCHECK(stream.CheckState(), false);

		wxByte complexCount;
		stream >> complexCount;
		wxCHECK(stream.CheckState(), false);

		// Read the symbols
		size_t i = 0;
		for (; i < complexCount; i++)
		{
			stream >> m_complexSymbolArray[i];
			wxCHECK(stream.CheckState(), false);
	    }
			
	    m_noteArray.Deserialize(stream, version);
	    wxCHECK(stream.CheckState(), false);
	}
    
    return (stream.CheckState());
}

// Duration Type Functions
/// Sets the duration type
/// @param durationType Duration type to set (1 = whole, 2 = half, 4 = quarter,
/// 8 = 8th, 16 = 16th, 32 = 32nd, 64 = 64th)
/// @return True if the duration type was set, false if not
bool Position::SetDurationType(wxByte durationType)
{
    //------Last Checked------//
    // - Jan 18, 2005
    wxCHECK(IsValidDurationType(durationType), false);

    // Duration type is stored in power of two format
    m_data &= ~durationTypeMask;                	
	m_data |= (wxUint32)(durationType << 24);
	
	return (true);
}

/// Gets the duration type (1 = whole, 2 = half, 4 = quarter, 8 = 8th,
/// 16 = 16th)
/// @return The duration type
wxByte Position::GetDurationType() const
{
    //------Last Checked------//
    // - Jan 18, 2005
	return ((wxByte)((m_data & durationTypeMask) >> 24));
}

// Irregular Grouping Functions
/// Sets the irregular grouping timing
/// @param notesPlayed Number of notes played
/// @param notesPlayedOver Number of notes played over
/// @return True if the irregular grouping timing was set, false if not
bool Position::SetIrregularGroupingTiming(wxByte notesPlayed,
    wxByte notesPlayedOver)
{
    //------Last Checked------//
    // - Jan 18, 2005
    wxCHECK(IsValidIrregularGroupingTiming(notesPlayed, notesPlayedOver),
        false);

	// Values are stored as 1-15 and 1-7
	notesPlayed--;
	notesPlayedOver--;

    m_beaming &= ~irregularGroupingTimingMask;
    
    m_beaming |= (wxWord)(notesPlayed << 3);
    m_beaming |= (wxWord)notesPlayedOver;
	
	return (true);
}

/// Gets the irregular grouping timing
/// @param notesPlayed Top value for the irregular grouping timing
/// @param notesPlayedOver Bottom value for the irregular grouping timing
/// @return True if the irregular grouping was set, false if not
void Position::GetIrregularGroupingTiming(wxByte& notesPlayed,
    wxByte& notesPlayedOver) const
{
    //------Last Checked------//
    // - Jan 18, 2005
    
	// Values are stored as 1-15 and 1-7, but there is no 1 value
	notesPlayed = 
        (wxByte)(((m_beaming & irregularGroupingNotesPlayedMask) >> 3) + 1);
	notesPlayedOver = 
        (wxByte)((m_beaming & irregularGroupingNotesPlayedOverMask) + 1);
}

/// Determines if the position has an irregular grouping timing
/// @return True if the position has an irregular grouping timing, false if not
bool Position::HasIrregularGroupingTiming() const
{
    //------Last Checked------//
    // - Jan 20, 2005
    wxByte notesPlayed = 0;
    wxByte notesPlayedOver = 0;
    GetIrregularGroupingTiming(notesPlayed, notesPlayedOver);
    return (!((notesPlayed == 1) && (notesPlayedOver == 1)));
}

/// Clears the irregular grouping timing
/// @return True if the irregular grouping was cleared, false if not
bool Position::ClearIrregularGroupingTiming()
{   
    //------Last Checked------//
    // - Jan 20, 2005
    m_beaming &= ~irregularGroupingTimingMask;
    return (true);
}

// Previous Beam Duration Functions
/// Sets the duration type of the previous rhythm slash in the beam group (cache
/// only)
/// @param durationType Duration type to set (0 = not beamed, 8 = 8th,
/// 16 = 16th, 32 = 32nd, 64 = 64th)
/// @return True if the duration type was set, false if not
bool Position::SetPreviousBeamDurationType(wxByte durationType)
{
    //------Last Checked------//
    // - Jan 18, 2005
    wxCHECK(IsValidPreviousBeamDurationType(durationType), false);
    
    // Clear the current duration type
    m_beaming &= ~previousBeamDurationTypeMask;

    wxWord flag = 0;
    
    if (durationType == 8)
        flag = previousBeamDuration8th;        
    else if (durationType == 16)
        flag = previousBeamDuration16th;
    else if (durationType == 32)
        flag = previousBeamDuration32nd;
    else if (durationType == 64)
        flag = previousBeamDuration64th;

    m_beaming |= (wxWord)(flag << 7);
    
    return (true);
}

/// Gets the duration type of the previous rhythm slash in the beam group
/// @return The duration type of the previous rhythm slash in the beam group
/// (0 = not beamed, 8 = 8th, 16 = 16th)
wxByte Position::GetPreviousBeamDurationType() const
{
    //------Last Checked------//
    // - Jan 18, 2005
     
    wxByte flag = (wxByte)((m_beaming & previousBeamDurationTypeMask) >> 7);
    if (flag == previousBeamDuration8th)
        return (8);
    else if (flag == previousBeamDuration16th)
        return (16);
    else if (flag == previousBeamDuration32nd)
        return (32);
    else if (flag == previousBeamDuration64th)
        return (64);

    return (0);
}

// Beaming Functions
/// Sets a beaming flag
/// @param flag Flag to set
/// @return True if teh beaming flag was set, false if not
bool Position::SetBeamingFlag(wxWord flag)
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
        
// Data Flag Functions
/// Sets a data flag
/// @param flag Flag to set
/// @return True if the flag was set, false if not
bool Position::SetDataFlag(wxUint32 flag)
{
    //------Last Checked------//
    // - Jan 7, 2005
    wxCHECK(IsValidDataFlag(flag), false);
    
    // Mutually exclusive operations
    if ((flag & dottedMask) != 0)
        ClearDataFlag(dottedMask);
    
    if ((flag & vibratoMask) != 0)
        ClearDataFlag(vibratoMask);
    
    if ((flag & arpeggioMask) != 0)
        ClearDataFlag(arpeggioMask);
            
    if ((flag & pickStrokeMask) != 0)
        ClearDataFlag(pickStrokeMask);
    
    if ((flag & accentMask) != 0)
        ClearDataFlag(accentMask);
        
    if ((flag & tripletFeelMask) != 0)
        ClearDataFlag(tripletFeelMask);
    
    m_data |= flag;
    
    return (true);
}

// Volume Swell Functions
/// Sets (adds or updates) a volume swell
/// @param startVolume Starting volume of the swell
/// @param endVolume Ending volume of the swell
/// @param duration Duration of the swell  (0 = occurs over position, 1 and up
/// = occurs over next n positions)
/// @return True if the volume swell was added or updated
bool Position::SetVolumeSwell(wxByte startVolume, wxByte endVolume,
    wxByte duration)
{
    //------Last Checked------//
    // - Jan 19, 2005
    wxCHECK(IsValidVolumeSwell(startVolume, endVolume, duration), false);
    
    // Construct the symbol data, then add it to the array
    wxUint32 symbolData = MAKELONG(MAKEWORD(endVolume, startVolume),
        MAKEWORD(duration, volumeSwell));
    return (AddComplexSymbol(symbolData));	
}

/// Gets the volume swell data (if any)
/// @param startVolume Holds the start volume return value
/// @param endVolume Holds the end volume return value
/// @param duration Holds the duration return value
/// @return True if the data was returned, false if not
bool Position::GetVolumeSwell(wxByte& startVolume, wxByte& endVolume,
    wxByte& duration) const
{
    //------Last Checked------//
    // - Jan 19, 2005
    
    startVolume = 0;
    endVolume = 0;
    duration = 0;
    
    // Get the index of the volume swell
    wxUint32 index = FindComplexSymbol(volumeSwell);
    if (index == (wxUint32)-1)
        return (false);
    
    // Get the individual pieces that make up the volume swell
    wxUint32 symbolData = m_complexSymbolArray[index];
    startVolume = HIBYTE(LOWORD(symbolData));
	endVolume = LOBYTE(LOWORD(symbolData));
	duration = LOBYTE(HIWORD(symbolData));
	
    return (true);
}

/// Determines if the position has a volume swell
/// @return True if the position has a volume swell, false if not
bool Position::HasVolumeSwell() const
{
    //------Last Checked------//
    // - Jan 19, 2005
    return (FindComplexSymbol(volumeSwell) != (wxUint32)-1);
}

/// Removes a volume swell from the position
/// @return True if the volume swell was removed, false if not
bool Position::ClearVolumeSwell()
{
    //------Last Checked------//
    // - Jan 19, 2005
    return (RemoveComplexSymbol(volumeSwell));
}

// Tremolo Bar Functions
/// Sets (adds or updates) a tremolo bar
/// @param type Type of tremolo bar (see tremoloBarTypes enum for values)
/// @param duration Duration of the tremolo bar (0 = occurs over position, 1
/// and up = occurs over next n positions)
/// @param pitch Pitch of the tremolo bar
/// @return True if the tremolo bar was added or updated
bool Position::SetTremoloBar(wxByte type, wxByte duration, wxByte pitch)
{
    //------Last Checked------//
    // - Jan 19, 2005
    wxCHECK(IsValidTremoloBar(type, duration, pitch), false);
    
    // Construct the symbol data, then add it to the array
    wxUint32 symbolData = MAKELONG(MAKEWORD(pitch, duration),
        MAKEWORD(type, tremoloBar));
    return (AddComplexSymbol(symbolData));	
}

/// Gets the tremolo bar data (if any)
/// @param type Holds the type return value
/// @param duration Holds the duration return value
/// @param pitch Holds the pitch return value
/// @return True if the data was returned, false if not
bool Position::GetTremoloBar(wxByte& type, wxByte& duration,
    wxByte& pitch) const
{
    //------Last Checked------//
    // - Jan 19, 2005
    
    type = 0;
    duration = 0;
    pitch = 0;
    
    // Get the index of the tremolo bar
    wxUint32 index = FindComplexSymbol(tremoloBar);
    if (index == (wxUint32)-1)
        return (false);
    
    // Get the individual pieces that make up the tremolo bar
    wxUint32 symbolData = m_complexSymbolArray[index];
    type = LOBYTE(HIWORD(symbolData));
	duration = HIBYTE(LOWORD(symbolData));
	pitch = LOBYTE(LOWORD(symbolData));
	
    return (true);
}

/// Determines if the position has a tremolo bar
/// @return True if the position has a tremolo bar, false if not
bool Position::HasTremoloBar() const
{
    //------Last Checked------//
    // - Jan 19, 2005
    return (FindComplexSymbol(tremoloBar) != (wxUint32)-1);
}

/// Removes a tremolo bar from the position
/// @return True if the tremolo bar was removed, false if not
bool Position::ClearTremoloBar()
{
    //------Last Checked------//
    // - Jan 19, 2005
    return (RemoveComplexSymbol(tremoloBar));
}

// Multibar Rest Functions
/// Sets (adds or updates) a multibar rest
/// @param measureCount Number of measures to rest for
/// @return True if the multibar rest was added or updated
bool Position::SetMultibarRest(wxByte measureCount)
{
    //------Last Checked------//
    // - Jan 19, 2005
    wxCHECK(IsValidMultibarRest(measureCount), false);
    
    // Construct the symbol data, then add it to the array
    wxUint32 symbolData = MAKELONG(MAKEWORD(measureCount, 0),
        MAKEWORD(0, multibarRest));
    return (AddComplexSymbol(symbolData));	
}

/// Gets the multibar rest data (if any)
/// @param measureCount Holds the measure count return value
/// @return True if the data was returned, false if not
bool Position::GetMultibarRest(wxByte& measureCount) const
{
    //------Last Checked------//
    // - Jan 19, 2005

    measureCount = 0;    
    
    // Get the index of the multibar rest
    wxUint32 index = FindComplexSymbol(multibarRest);
    if (index == (wxUint32)-1)
        return (false);
    
    // Get the individual pieces that make up the multibar rest
    wxUint32 symbolData = m_complexSymbolArray[index];
	measureCount = LOBYTE(LOWORD(symbolData));
	
    return (true);
}

/// Determines if the position has a multibar rest
/// @return True if the position has a multibar rest, false if not
bool Position::HasMultibarRest() const
{
    //------Last Checked------//
    // - Jan 19, 2005
    return (FindComplexSymbol(multibarRest) != (wxUint32)-1);
}

/// Removes a multibar rest from the position
/// @return True if the multibar rest was removed, false if not
bool Position::ClearMultibarRest()
{
    //------Last Checked------//
    // - Jan 19, 2005
    return (RemoveComplexSymbol(multibarRest));
}

// Complex Symbol Array Functions
/// Adds a complex symbol to the complex symbol array
/// @param symbolData Data that makes up the symbol
/// @return True if the symbol was added or updated, false if not
bool Position::AddComplexSymbol(wxUint32 symbolData)
{   
    //------Last Checked------//
    // - Jan 19, 2005
    
    // Get and validate the symbol type
	wxByte type = HIBYTE(HIWORD(symbolData));
	wxCHECK(IsValidComplexSymbolType(type), false);

    bool returnValue = false;
    
    // Get the index in the complex array where the symbol is stored
    wxUint32 index = FindComplexSymbol(type);

	// Found symbol in the array, update the symbol data
	if (index != (wxUint32)-1)
    {
		m_complexSymbolArray[index] = symbolData;
		returnValue = true;
    }
    // Symbol was not found in the array, find the first free array slot and
    // insert there
	else
	{
	    wxUint32 i = 0;
		for (; i < MAX_POSITION_COMPLEX_SYMBOLS; i++)
		{
			if (m_complexSymbolArray[i] == notUsed)
			{
				m_complexSymbolArray[i] = symbolData;
				returnValue = true;
				break;
			}
		}
	}
	
	return (returnValue);
}

/// Gets the number of complex symbols used by the position
/// @return The number of complex symbols used by the position
size_t Position::GetComplexSymbolCount() const
{
    //------Last Checked------//
    // - Jan 19, 2005
    size_t returnValue = 0;
    size_t i = 0;
	for (; i < MAX_POSITION_COMPLEX_SYMBOLS; i++)
	{
	    // Slot is not used; break out
		if (m_complexSymbolArray[i] == notUsed)
			break;
	    returnValue++;
	}
	return (returnValue);
}

/// Gets the index of a given complex symbol type in the complex symbol array
/// @param type Type of symbol to find
/// @return Index within the array where the symbol was found, or -1 if not
/// found
wxUint32 Position::FindComplexSymbol(wxByte type) const
{
    //------Last Checked------//
    // - Jan 19, 2005
	wxUint32 returnValue = (wxUint32)-1;

    wxUint32 i = 0;
	for (; i < MAX_POSITION_COMPLEX_SYMBOLS; i++)
	{
	    // Found the symbol type; break out
	    if (HIBYTE(HIWORD(m_complexSymbolArray[i])) == type)
	    {
	        returnValue = i;
		    break;
	    }
	}

	return (returnValue);
}

/// Removes a complex symbol from the complex symbol array
/// @param type Type of symbol to remove
/// @return True if the symbol was removed, false if not
bool Position::RemoveComplexSymbol(wxByte type)
{
    //------Last Checked------//
    // - Jan 19, 2005
    bool returnValue = false;
    
    wxUint32 i = 0;
	for (; i < MAX_POSITION_COMPLEX_SYMBOLS; i++)
	{
	    if (HIBYTE(HIWORD(m_complexSymbolArray[i])) == type)
		{
			m_complexSymbolArray[i] = notUsed;
			returnValue = true;
			break;
		}
	}
	
	return (returnValue);
}

/// Clears the contents of the symbol array (sets all elements to "not used")
void Position::ClearComplexSymbolArrayContents()
{
    //------Last Checked------//
    // - Jan 19, 2005   
    wxUint32 i = 0;
    for (; i < MAX_POSITION_COMPLEX_SYMBOLS; i++)
        m_complexSymbolArray[i] = notUsed;
}
