/////////////////////////////////////////////////////////////////////////////
// Name:            tuning.cpp
// Purpose:         Stores a tuning used by a stringed instrument
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 14, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "tuning.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const wxChar*       Tuning::DEFAULT_NAME                    = wxT("");
const wxByte        Tuning::DEFAULT_DATA                    = 0;
const wxInt8        Tuning::MIN_MUSIC_NOTATION_OFFSET       = -12;
const wxInt8        Tuning::MAX_MUSIC_NOTATION_OFFSET       = 12;
const wxUint32      Tuning::MIN_STRING_COUNT                = 3;
const wxUint32      Tuning::MAX_STRING_COUNT                = 7;
    
// Constructors/Destructors
/// Default Constructor
Tuning::Tuning() :
    m_name(DEFAULT_NAME), m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Dec 14, 2004
}

/// Primary Constructor
/// @param name Tuning name (Standard, Dropped-D, Open G, etc.)
/// @param musicNotationOffset Offset used when drawing notes on the music staff, in semi-tones
/// @param sharps Display the tuning notes using sharps as opposed to flats
/// @param note1 MIDI note value for the 1st string in the tuning (for standard guitar tuning, this is the high E string)
/// @param note2 MIDI note value for the 2nd string in the tuning
/// @param note3 MIDI note value for the 3rd string in the tuning
/// @param note4 MIDI note value for the 4th string in the tuning
/// @param note5 MIDI note value for the 5th string in the tuning
/// @param note6 MIDI note value for the 6th string in the tuning
/// @param note7 MIDI note value for the 7th string in the tuning
Tuning::Tuning(const wxChar* name, wxInt8 musicNotationOffset, bool sharps, wxByte note1, wxByte note2, wxByte note3, wxByte note4, wxByte note5, wxByte note6, wxByte note7) :
    m_name(name), m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Dec 14, 2004
    wxASSERT(name != NULL);
    wxASSERT(IsValidMusicNotationOffset(musicNotationOffset));
    
    SetSharps(sharps);
    SetMusicNotationOffset(musicNotationOffset);
    AddTuningNotes(note1, note2, note3, note4, note5, note6, note7);
}

/// Copy Constructor
Tuning::Tuning(const Tuning& tuning) :
    m_name(DEFAULT_NAME), m_data(DEFAULT_DATA)
{
    //------Last Checked------//
    // - Dec 7, 2004
    *this = tuning;
}

/// Destructor
Tuning::~Tuning()
{
    //------Last Checked------//
    // - Dec 9, 2004
}

// Operators
/// Assignment operator
const Tuning& Tuning::operator=(const Tuning& tuning)
{
    //------Last Checked------//
    // - Dec 14, 2004
    
    // Check for assignment to self
    if (this != &tuning)
    {
        m_name = tuning.m_name;
        m_data = tuning.m_data;
        DeleteNoteArrayContents();
        size_t i = 0;
        size_t count = tuning.m_noteArray.GetCount();
        for (; i < count; i++)
            m_noteArray.Add(tuning.m_noteArray[i]);
    }
    return (*this);
}

/// Equality operator
bool Tuning::operator==(const Tuning& tuning) const
{
    //------Last Checked------//
    // - Dec 14, 2004
        
    size_t thisStringCount = GetStringCount();
    size_t otherStringCount = tuning.GetStringCount();
    
    // Tunings have a differing number of strings
    if (thisStringCount != otherStringCount)
        return (false);

    // Check each string for matching notes
    size_t i = 0;
    for (; i < thisStringCount; i++)
    {
        if (m_noteArray[i] != tuning.m_noteArray[i])
            return (false);
    }

    return (
        (m_name == tuning.m_name) &&
        (m_data == tuning.m_data)
    );
}

/// Inequality Operator
bool Tuning::operator!=(const Tuning& tuning) const
{
    //------Last Checked------//
    // - Dec 7, 2004
    return (!operator==(tuning));
}

// Serialize Functions
/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool Tuning::DoSerialize(PowerTabOutputStream& stream)
{
    //------Last Checked------//
    // - Dec 14, 2004
    stream.WriteMFCString(m_name);
    wxCHECK(stream.CheckState(), false);
    
    stream << m_data;
    wxCHECK(stream.CheckState(), false);

    // Write the string count as a byte
    size_t stringCount = GetStringCount();
    stream << (wxByte)stringCount;
    wxCHECK(stream.CheckState(), false);

    // Write each note
    size_t i = 0;
    for (; i < stringCount; i++)
    {
        stream << m_noteArray[i];
        wxCHECK(stream.CheckState(), false);
    }
    return (stream.CheckState());
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool Tuning::DoDeserialize(PowerTabInputStream& stream,
    wxWord WXUNUSED(version))
{
    //------Last Checked------//
    // - Apr 22, 2007
    stream.ReadMFCString(m_name);
    wxCHECK(stream.CheckState(), false);
    
    stream >> m_data;
    wxCHECK(stream.CheckState(), false);

    DeleteNoteArrayContents();

    // Get number of notes, then the notes themselves
    wxByte stringCount = 0;
    stream >> stringCount;
    wxCHECK(stream.CheckState(), false);
    
    size_t i = 0;
    for (; i < stringCount; i++)
    {
        wxByte note;
        stream >> note;
        wxCHECK(stream.CheckState(), false);
        m_noteArray.Add(note);
    }
    return (stream.CheckState());
}

// Tuning Functions
/// Sets the contents of the Tuning object
/// @param name Tuning name (Standard, Dropped-D, Open G, etc.)
/// @param musicNotationOffset Offset used when drawing notes on the music staff, in semi-tones
/// @param sharps Display the tuning notes using sharps as opposed to flats
/// @param note1 MIDI note value for the 1st string in the tuning (for standard guitar tuning, this is the high E string)
/// @param note2 MIDI note value for the 2nd string in the tuning
/// @param note3 MIDI note value for the 3rd string in the tuning
/// @param note4 MIDI note value for the 4th string in the tuning
/// @param note5 MIDI note value for the 5th string in the tuning
/// @param note6 MIDI note value for the 6th string in the tuning
/// @param note7 MIDI note value for the 7th string in the tuning
/// @return True if the tuning was set, false if not
bool Tuning::SetTuning(const wxChar* name, wxInt8 musicNotationOffset, bool sharps, wxByte note1, wxByte note2, wxByte note3, wxByte note4, wxByte note5, wxByte note6, wxByte note7)
{
    //------Last Checked------//
    // - Dec 14, 2004
    if (!SetName(name))
        return (false);
    SetSharps(sharps);
    if (!SetMusicNotationOffset(musicNotationOffset))
        return (false);
    return (AddTuningNotes(note1, note2, note3, note4, note5, note6, note7));
}

/// Sets the contents of a tuning using a comma delimited string
/// @param string Comma delimited string containing the tuning settings (Name,Sharps,MusicNotationOffset,Note1,...,Note7)
/// @return True if the tuning was updated, false if not
bool Tuning::SetTuningFromString(const wxChar* string)
{
    //------Last Checked------//
    // - Dec 14, 2004
    wxCHECK(string != NULL, false);
   
    // Get the tuning name
    wxString name;
    wxExtractSubString(name, string, 0, wxT(','));
    if (!SetName(name))
        return (false);
    
    wxString temp;

    // Get the sharps setting
    wxExtractSubString(temp, string, 1, wxT(','));
    wxByte sharps = (wxByte)(wxAtoi(temp));
    if (sharps != 1)
        sharps = 0;
    SetSharps((sharps != 0));

    // Get the music notation offset
    wxExtractSubString(temp, string, 2, wxT(','));
    wxInt8 musicNotationOffset = (wxInt8)(wxAtoi(temp));
    if (!SetMusicNotationOffset(musicNotationOffset))
        return (false);

    // Get the notes
    wxByte notes[MAX_STRING_COUNT];
    size_t i = 0;
    for (; i < MAX_STRING_COUNT; i++)
        notes[i] = notUsed;

    i = 3;
    for (; i < 10; i++)
    {
        if (!wxExtractSubString(temp, string, i, wxT(',')))
            break;
        notes[i - 3] = (wxByte)(wxAtoi(temp));
    }

    return (AddTuningNotes(notes[0], notes[1], notes[2], notes[3], notes[4], notes[5], notes[6]));
}

/// Determines if the tuning notes are the same as that of another Tuning object
/// @param tuning Tuning object to compare with
/// @return True if the tunings have the same notes, false if not
bool Tuning::IsSameTuning(const Tuning& tuning) const
{
    //------Last Checked------//
    // - Dec 14, 2004
    
    size_t thisStringCount = GetStringCount();
    size_t otherStringCount = tuning.GetStringCount();
    
    // Tunings have a different number of strings
    if (thisStringCount != otherStringCount)
        return (false);

    // Check each string for matching notes
    size_t i = 0;
    for (; i < thisStringCount; i++)
    {
        if (m_noteArray[i] != tuning.m_noteArray[i])
            return (false);
    }

    return (true);
}

/// Determines if the tuning notes are the same
/// @param note1 MIDI note value for the 1st string in the tuning (for standard guitar tuning, this is the high E string)
/// @param note2 MIDI note value for the 2nd string in the tuning
/// @param note3 MIDI note value for the 3rd string in the tuning
/// @param note4 MIDI note value for the 4th string in the tuning
/// @param note5 MIDI note value for the 5th string in the tuning
/// @param note6 MIDI note value for the 6th string in the tuning
/// @param note7 MIDI note value for the 7th string in the tuning
/// @return True if all of the tuning notes match, false if not
bool Tuning::IsSameTuning(wxByte note1, wxByte note2, wxByte note3, wxByte note4, wxByte note5, wxByte note6, wxByte note7) const
{
    //------Last Checked------//
    // - Dec 15, 2004
    Tuning temp;
    temp.AddTuningNotes(note1, note2, note3, note4, note5, note6, note7);
    return (IsSameTuning(temp));
}

// Sharps Functions
/// Sets the tuning to use sharps when displaying the tuning notes (i.e. C# vs Db)
/// @param set True uses use sharps, false uses flats
void Tuning::SetSharps(bool set)
{
    //------Last Checked------//
    // - Dec 14, 2004
    m_data &= ~sharpsMask;
    if (set)
        m_data |= sharpsMask;
}

// Music Notation Offset Functions
/// Sets the music notation offset
/// @param musicNotationOffset Music notation offset to set, in semi-tones
/// @return True if the music notation offset was set, false if not
bool Tuning::SetMusicNotationOffset(wxInt8 musicNotationOffset)
{
    //------Last Checked------//
    // - Dec 14, 2004
    wxCHECK(IsValidMusicNotationOffset(musicNotationOffset), false);
    
    // Clear the current music notation offset
    m_data &= ~musicNotationOffsetMask;
    
    // Set the sign bit if the offset is negative
    if (musicNotationOffset < 0)
        m_data |= musicNotationOffsetSignMask;

    // Set the music notation offset value
    m_data |= (wxByte)(abs(musicNotationOffset) << 1);
   
    return (true);
}

/// Gets the music notation offset
/// @return The music notation offset, in semi-tones
wxInt8 Tuning::GetMusicNotationOffset() const
{
    //------Last Checked------//
    // - Dec 14, 2004
    wxInt8 returnValue = (wxInt8)((m_data & musicNotationOffsetValueMask) >> 1);

    // If the sign is set, the value is negative
    if ((m_data & musicNotationOffsetSignMask) == musicNotationOffsetSignMask)
        returnValue = -returnValue;

    return (returnValue);
}

// Note Functions
/// Sets the MIDI note value for an existing string in the tuning
/// @param string String to set the note for
/// @param note MIDI note to set
/// @return True if the note was set, false if not
bool Tuning::SetNote(wxUint32 string, wxByte note)
{
    //------Last Checked------//
    // - Dec 14, 2004
    wxCHECK(IsValidString(string), false);
    wxCHECK(wxIsValidMidiNote(note), false);
    m_noteArray[string] = note;
    return (true);
}

/// Gets the note for assigned to a string
/// @param string String to get the note for
/// @param includeMusicNotationOffset Include the music notation offset in the note pitch
/// @return The MIDI note assigned to the string
wxByte Tuning::GetNote(wxUint32 string, bool includeMusicNotationOffset) const
{
    //------Last Checked------//
    // - Dec 14, 2004
    wxCHECK(IsValidString(string), MIDI_NOTE_MIDDLE_C);

    wxByte returnValue = m_noteArray[string];

    // Include the music notation offset
    if (includeMusicNotationOffset)
        returnValue = wxOffsetMidiNote(returnValue, GetMusicNotationOffset());

    return (returnValue);
}

/// Gets the text representation of a note (i.e. C#, Eb)
/// @param string String of the note to get the text representation of
/// @return A text representation of the note
wxString Tuning::GetNoteText(wxUint32 string) const
{
    //------Last Checked------//
    // - Dec 14, 2004
    wxCHECK(IsValidString(string), wxT(""));
    return (wxGetMidiNoteText(m_noteArray[string], UsesSharps()));
}

/// Determines if a note is a note that can be played as an open string
/// @param note Note to test
/// @return True if the note can be played as an open string, false if not
bool Tuning::IsOpenStringNote(wxByte note) const
{
    //------Last Checked------//
    // - Dec 14, 2004
    wxInt32 i = 0;
    wxInt32 nCount = GetStringCount();
    for (; i < nCount; i++)
    {
        if (m_noteArray[i] != notUsed)
        {
            // Note matches a tuning note; it's an open string note
            if (m_noteArray[i] == note)
                return (true);
        }
    }
    return (false);
}

/// Gets the MIDI note range for the tuning (lowest possible playable note + highest possible playable note)
/// @param capo Capo value to apply to the tuning
/// @return .cx - contains the lowest possible note, .cy - contains the highest possible note
wxSize Tuning::GetNoteRange(wxByte capo) const
{
    //------Last Checked------//
    // - Apr 22, 2007
    wxSize returnValue(notUsed, 0);

    // Loop through each tuning note and get the minimum and maximum notes for the string
    size_t i = 0;
    size_t stringCount = GetStringCount();
    for (; i < stringCount; i++)
    {
        if (m_noteArray[i] != notUsed)
        {
            returnValue.x = std::min(returnValue.x, m_noteArray[i] + capo);
            returnValue.y = std::max(returnValue.y, m_noteArray[i] + capo + 24);       // Assume guitar has 24 frets
        }
    }
    return (returnValue);
}

/// Sets the tuning notes for the tuning
/// @param note1 MIDI note value for the 1st string in the tuning (for standard guitar tuning, this is the high E string)
/// @param note2 MIDI note value for the 2nd string in the tuning
/// @param note3 MIDI note value for the 3rd string in the tuning
/// @param note4 MIDI note value for the 4th string in the tuning
/// @param note5 MIDI note value for the 5th string in the tuning
/// @param note6 MIDI note value for the 6th string in the tuning
/// @param note7 MIDI note value for the 7th string in the tuning
/// @return True if the tuning notes were set, false if not
bool Tuning::AddTuningNotes(wxByte note1, wxByte note2, wxByte note3, wxByte note4, wxByte note5, wxByte note6, wxByte note7)
{
    //------Last Checked------//
    // - Dec 14, 2004    
    wxCHECK(wxIsValidMidiNote(note1), false);
    wxCHECK(wxIsValidMidiNote(note2), false);
    wxCHECK(wxIsValidMidiNote(note3), false);
    wxCHECK(wxIsValidMidiNote(note4) || (note4 == notUsed), false);
    wxCHECK(wxIsValidMidiNote(note5) || (note5 == notUsed), false);
    wxCHECK(wxIsValidMidiNote(note6) || (note6 == notUsed), false);
    wxCHECK(wxIsValidMidiNote(note7) || (note7 == notUsed), false);
    
    DeleteNoteArrayContents();
    
    m_noteArray.Add(note1);
    m_noteArray.Add(note2);
    m_noteArray.Add(note3);
    
    if (note4 == notUsed)
        return (true);
    m_noteArray.Add(note4);
   
    if (note5 == notUsed)
        return (true);
    m_noteArray.Add(note5);
 
    if (note6 == notUsed)
        return (true);
    m_noteArray.Add(note6);   
    
    if (note7 == notUsed)
        return (true);
    m_noteArray.Add(note7);
    
    return (true);
}

/// Deletes the contents (and frees the memory) of the note array
void Tuning::DeleteNoteArrayContents()
{
    //------Last Checked------//
    // - Jan 11, 2005
    m_noteArray.Clear();
}

// Operations
/// Gets a full string representation of the tuning from low to high (i.e. E A D G B E)
/// @return A full string representation of the tuning from low to high
wxString Tuning::GetSpelling() const
{
    //------Last Checked------//
    // - Dec 14, 2004
    wxString returnValue;
    
    size_t stringCount = GetStringCount();

    // Go from lowest to highest string
    size_t i = stringCount;
    for (; i > 0; i--)
    {
        if (i != stringCount)
           returnValue += wxT(" ");
        returnValue += wxString::Format(wxT("%s"), GetNoteText(i - 1).c_str());
    }

    return (returnValue);
}
