/////////////////////////////////////////////////////////////////////////////
// Name:            generalmidi.cpp
// Purpose:         General MIDI macros, constants and functions
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 9, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "generalmidi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// MIDI Channel Functions
/// Determines if a MIDI channel is valid
/// @param MIDI channel to validate
/// @return True if the MIDI channel is valid, false if not
bool wxIsValidMidiChannel(wxByte channel)
{
    //------Last Checked------//
    // - Dec 9, 2004
    return (channel <= LAST_MIDI_CHANNEL);
}

bool wxIsValidMidiChannelVolume(wxByte volume)
{
    //------Last Checked------//
    // - Dec 9, 2004
    return (volume <= MAX_MIDI_CHANNEL_VOLUME);
}

/// Determines if a MIDI channel effect level is valid
/// @param level MIDI channel effect level to validate
/// @return True if the MIDI channel effect level is valid, false if not
bool wxIsValidMidiChannelEffectLevel(wxByte level)
{
    //------Last Checked------//
    // - Dec 9, 2004
    return (level <= MAX_MIDI_CHANNEL_EFFECT_LEVEL);
}

// MIDI Note Functions
/// Determines if a MIDI note value is valid
/// @param note MIDI note to validate
/// @return True if the MIDI note value is valid, false if not
bool wxIsValidMidiNote(wxByte note)
{
    //------Last Checked------//
    // - Dec 9, 2004
    return (note <= MAX_MIDI_NOTE);
}

/// Gets the text representation of a MIDI note
/// @param note MIDI note to get the text representation for
/// @param sharps True to get the sharp representation of the note, false to get
/// the flat representation of the note
/// @return A text representation of the MIDI note
wxString wxGetMidiNoteText(wxByte note, bool sharps)
{
    //------Last Checked------//
    // - Dec 14, 2004
    wxCHECK(wxIsValidMidiNote(note), wxT(""));
    wxByte pitch = wxGetMidiNotePitch(note);
    
    const wxChar* notes[12];
    
    if (sharps)
    {
        notes[0] = wxT("C");
        notes[1] = wxT("C#");
        notes[2] = wxT("D");
        notes[3] = wxT("D#");
        notes[4] = wxT("E");
        notes[5] = wxT("F");
        notes[6] = wxT("F#");
        notes[7] = wxT("G");
        notes[8] = wxT("G#");
        notes[9] = wxT("A");
        notes[10] = wxT("A#");
        notes[11] = wxT("B");
    }
	else
	{
	    notes[0] = wxT("C");
        notes[1] = wxT("Db");
        notes[2] = wxT("D");
        notes[3] = wxT("Eb");
        notes[4] = wxT("E");
        notes[5] = wxT("F");
        notes[6] = wxT("Gb");
        notes[7] = wxT("G");
        notes[8] = wxT("Ab");
        notes[9] = wxT("A");
        notes[10] = wxT("Bb");
        notes[11] = wxT("B");
    }
    
    return (notes[pitch]);
}

/// Offsets a MIDI note by an offset
/// @param note MIDI note to offset
/// @param offset Amount to offset the note
/// @return The offset note
wxByte wxOffsetMidiNote(wxByte note, wxInt8 offset)
{
    //------Last Checked------//
    // - Dec 14, 2004
    wxInt32 temp = note + offset;
    
    if (temp < MIN_MIDI_NOTE)
        temp = MIN_MIDI_NOTE;
    else if (temp > MAX_MIDI_NOTE)
        temp = MAX_MIDI_NOTE;
        
    return ((wxByte)(temp));
}

/// Determines if a MIDI note key is valid
/// @param key MIDI note key to validate
/// @return True if the MIDI note key is valid, false if not
bool wxIsValidMidiNoteKey(wxByte key)
{
    //------Last Checked------//
    // - Dec 9, 2004
    return (key <= MAX_MIDI_NOTE_KEY);
}

/// Gets the pitch value for a MIDI note
/// @param note MIDI note to get the pitch value for
/// @return The pitch value for the MIDI note
wxByte wxGetMidiNotePitch(wxByte note)
{
    //------Last Checked------//
    // - Dec 9, 2004
    return (note % 12);
}

/// Gets the octave value for a MIDI note
/// @param note MIDI note to get the octave value for
/// @return The octave value for the MIDI note
wxInt32 wxGetMidiNoteOctave(wxByte note)
{
    //------Last Checked------//
    // - Dec 9, 2004
    return ((note / 12) - 1);
}

/// Determines if a MIDI note volume is valid
/// @param volume MIDI note volume to validate
/// @return True if the MIDI note volume is valid, false if not
bool wxIsValidMidiNoteVolume(wxByte volume)
{
    //------Last Checked------//
    // - Dec 9, 2004
    return (volume <= MAX_MIDI_NOTE_VOLUME);
}

// MIDI Preset Functions
/// Determines if a MIDI preset is valid
/// @param preset MIDI preset to validate
/// @return True if the MIDI preset is valid, false if not
bool wxIsValidMidiPreset(wxByte preset)
{
    //------Last Checked------//
    // - Dec 9, 2004
    return (preset <= LAST_MIDI_PRESET);
}

// MIDI Percussion Preset Functions
/// Determines if a MIDI percussion preset is valid
/// @param preset MIDI percussion preset to validate
/// @return True if the MIDI percussion preset is valid, false if not
bool wxIsValidMidiPercussionPreset(wxByte preset)
{
    //------Last Checked------//
    // - Dec 9, 2004
    return (preset <= LAST_MIDI_PERCUSSION_PRESET);
}
