/////////////////////////////////////////////////////////////////////////////
// Name:            generalmiditestsuite.cpp
// Purpose:         Performs unit testing on the General MIDI functions
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 9, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "generalmiditestsuite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(GeneralMidiTestSuite, TestSuite)

// Constructor/Destructor
/// Default Constructor
GeneralMidiTestSuite::GeneralMidiTestSuite()
{
    //------Last Checked------//
    // - Dec 9, 2004
}

/// Destructor
GeneralMidiTestSuite::~GeneralMidiTestSuite()
{
    //------Last Checked------//
    // - Dec 9, 2004
}

/// Gets the total number of tests in the test suite
size_t GeneralMidiTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Dec 9, 2004
    return (983);
}

/// Executes all test cases in the test suite
bool GeneralMidiTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Dec 9, 2004
    
    if (!TestCaseMidiChannel())
        return (false);
    if (!TestCaseMidiNote())
        return (false);
    if (!TestCaseMidiPreset())
        return (false);
    if (!TestCaseMidiPercussionPreset())
        return (false);
    return (true);
}

// Test Case Functions
bool GeneralMidiTestSuite::TestCaseMidiChannel()
{
    //------Last Checked------//
    // - Dec 9, 2004
    
    // TEST CASE: wxIsValidMidiChannel
    {
        wxByte i = FIRST_MIDI_CHANNEL;
        for (; i <= (LAST_MIDI_CHANNEL + 1); i++)
            TEST(wxString::Format(wxT("wxIsValidMidiChannel - %d"), i), (wxIsValidMidiChannel(i) == (i <= LAST_MIDI_CHANNEL)));
    }
    
    // TEST CASE: wxIsValidMidiChannelVolume
    {
        wxByte i = MIN_MIDI_CHANNEL_VOLUME;
        for (; i <= (MAX_MIDI_CHANNEL_VOLUME + 1); i++)
            TEST(wxString::Format(wxT("wxIsValidMidiChannelVolume - %d"), i), (wxIsValidMidiChannelVolume(i) == (i <= MAX_MIDI_CHANNEL_VOLUME)));
    }
    
    // TEST CASE: wxIsValidMidiChannelEffectLevel
    {
        wxByte i = MIN_MIDI_CHANNEL_EFFECT_LEVEL;
        for (; i <= (MAX_MIDI_CHANNEL_EFFECT_LEVEL + 1); i++)
            TEST(wxString::Format(wxT("wxIsValidMidiChannelEffectLevel - %d"), i), (wxIsValidMidiChannelEffectLevel(i) == (i <= MAX_MIDI_CHANNEL_EFFECT_LEVEL)));
    }
    return (true);
}

bool GeneralMidiTestSuite::TestCaseMidiNote()
{
    //------Last Checked------//
    // - Dec 9, 2004
    
    // TEST CASE: wxIsValidMidiNote
    {
        wxByte i = MIN_MIDI_NOTE;
        for (; i <= (MAX_MIDI_NOTE + 1); i++)
            TEST(wxString::Format(wxT("wxIsValidMidiNote - %d"), i), (wxIsValidMidiNote(i) == (i <= MAX_MIDI_NOTE)));
    }
    
    // TEST CASE: wxIsValidMidiNoteKey
    {
        wxByte i = MIN_MIDI_NOTE_KEY;
        for (; i <= (MAX_MIDI_NOTE_KEY + 1); i++)
            TEST(wxString::Format(wxT("wxIsValidMidiNoteKey - %d"), i), (wxIsValidMidiNoteKey(i) == (i <= MAX_MIDI_NOTE_KEY)));
    }

    // TEST CASE: wxGetMidiNotePitch
    {
        wxByte i = MIN_MIDI_NOTE;
        for (; i <= MAX_MIDI_NOTE; i++)
            TEST(wxString::Format(wxT("wxGetMidiNotePitch - %d"), i), (wxGetMidiNotePitch(i) == (i % 12)));    
    }
       
    // TEST CASE: wxGetMidiNoteOctave
    {
        wxByte i = MIN_MIDI_NOTE;
        for (; i <= MAX_MIDI_NOTE; i++)
            TEST(wxString::Format(wxT("wxGetMidiNoteOctave - %d"), i), (wxGetMidiNoteOctave(i) == ((i / 12) - 1)));
    }

    // TEST CASE: wxOffsetMidiNote
    {
        TEST(wxT("wxOffsetMidiNote - underflow"), (wxOffsetMidiNote(MIN_MIDI_NOTE, -1) == MIN_MIDI_NOTE));
        TEST(wxT("wxOffsetMidiNote - positive offset"), (wxOffsetMidiNote(MIN_MIDI_NOTE, 12) == (MIN_MIDI_NOTE + 12)));
        TEST(wxT("wxOffsetMidiNote - negative offset"), (wxOffsetMidiNote(MAX_MIDI_NOTE, -12) == (MAX_MIDI_NOTE - 12)));
        TEST(wxT("wxOffsetMidiNote - overflow"), (wxOffsetMidiNote(MAX_MIDI_NOTE, 1) == MAX_MIDI_NOTE));
    }
    
    // TEST CASE: wxIsValidMidiNoteVolume
    {
        wxByte i = MIN_MIDI_NOTE_VOLUME;
        for (; i <= (MAX_MIDI_NOTE_VOLUME + 1); i++)
            TEST(wxString::Format(wxT("wxIsValidMidiNoteVolume - %d"), i), (wxIsValidMidiNoteVolume(i) == (i <= MAX_MIDI_NOTE_VOLUME)));
    }

    return (true);
}

bool GeneralMidiTestSuite::TestCaseMidiPreset()
{
    //------Last Checked------//
    // - Dec 9, 2004
    
    // TEST CASE: wxIsValidMidiPreset
    {
        wxByte i = FIRST_MIDI_PRESET;
        for (; i <= (LAST_MIDI_PRESET + 1); i++)
            TEST(wxString::Format(wxT("wxIsValidMidiPreset - %d"), i), (wxIsValidMidiPreset(i) == (i <= LAST_MIDI_PRESET)));
    }
    return (true);
}

bool GeneralMidiTestSuite::TestCaseMidiPercussionPreset()
{
    //------Last Checked------//
    // - Dec 9, 2004
    
    // TEST CASE: wxIsValidMidiPercussionPreset
    {
        wxByte i = FIRST_MIDI_PERCUSSION_PRESET;
        for (; i <= (LAST_MIDI_PERCUSSION_PRESET + 1); i++)
            TEST(wxString::Format(wxT("wxIsValidMidiPercussionPreset - %d"), i), (wxIsValidMidiPercussionPreset(i) == (i <= LAST_MIDI_PERCUSSION_PRESET)));
    }
    return (true);
}
