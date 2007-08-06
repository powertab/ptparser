/////////////////////////////////////////////////////////////////////////////
// Name:            guitartestsuite.cpp
// Purpose:         Performs unit testing on the Guitar class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 8, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "guitartestsuite.h"
#include "guitar.h"

#include "powertabfileheader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(GuitarTestSuite, TestSuite)

/// Default Constructor
GuitarTestSuite::GuitarTestSuite()
{
    //------Last Checked------//
    // - Dec 8, 2004
}

/// Destructor
GuitarTestSuite::~GuitarTestSuite()
{
    //------Last Checked------//
    // - Dec 8, 2004
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t GuitarTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Dec 8, 2004
    return (834);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool GuitarTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Dec 8, 2004
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseCreation())
        return (false);
    if (!TestCaseOperator())
        return (false);
    if (!TestCaseSerialize())
        return (false);
    if (!TestCaseNumber())
        return (false);
    if (!TestCasePreset())
        return (false);
    if (!TestCaseInitialVolume())
        return (false);
    if (!TestCaseDescription())
        return (false);
    if (!TestCaseReverb())
        return (false);
    if (!TestCaseChorus())
        return (false);
    if (!TestCaseTremolo())
        return (false);
    if (!TestCasePhaser())
        return (false);    
    if (!TestCaseCapo())
        return (false);
    if (!TestCaseTuning())
        return (false);
    return (true);
}

// Test Case Functions
/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool GuitarTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Dec 8, 2004
    
    // TEST CASE: Default constructor
    {
        Guitar guitar;
        TEST(wxT("Default Constructor"), 
            (guitar.GetNumber() == Guitar::DEFAULT_NUMBER) &&
            (guitar.GetDescription() == Guitar::DEFAULT_DESCRIPTION) &&
            (guitar.GetPreset() == Guitar::DEFAULT_PRESET) &&
            (guitar.GetInitialVolume() == Guitar::DEFAULT_INITIAL_VOLUME) &&
            (guitar.GetPan() == Guitar::DEFAULT_PAN) &&
            (guitar.GetReverb() == Guitar::DEFAULT_REVERB) &&
            (guitar.GetChorus() == Guitar::DEFAULT_CHORUS) &&
            (guitar.GetTremolo() == Guitar::DEFAULT_TREMOLO) &&
            (guitar.GetPhaser() == Guitar::DEFAULT_PHASER) &&
            (guitar.GetCapo() == Guitar::DEFAULT_CAPO)
        );        
    }
    
    // TEST CASE: Primary constructor
    {
        Guitar guitar(1, wxT("Test"), 2, 3, 4, 5, 6, 7, 8, 9);
        TEST(wxT("Primary Constructor"), 
            (guitar.GetNumber() == 1) &&
            (guitar.GetDescription() == wxT("Test")) &&
            (guitar.GetPreset() == 2) &&
            (guitar.GetInitialVolume() == 3) &&
            (guitar.GetPan() == 4) &&
            (guitar.GetReverb() == 5) &&
            (guitar.GetChorus() == 6) &&
            (guitar.GetTremolo() == 7) &&
            (guitar.GetPhaser() == 8) &&
            (guitar.GetCapo() == 9)
        );
    }
    
    // TEST CASE: Copy constructor
    {
        Guitar guitar(1, wxT("Test"), 2, 3, 4, 5, 6, 7, 8, 9);
        Guitar guitar2(guitar);
        TEST(wxT("Copy Constructor"), 
            (guitar2.GetNumber() == 1) &&
            (guitar2.GetDescription() == wxT("Test")) &&
            (guitar2.GetPreset() == 2) &&
            (guitar2.GetInitialVolume() == 3) &&
            (guitar2.GetPan() == 4) &&
            (guitar2.GetReverb() == 5) &&
            (guitar2.GetChorus() == 6) &&
            (guitar2.GetTremolo() == 7) &&
            (guitar2.GetPhaser() == 8) &&
            (guitar2.GetCapo() == 9)
        );
    }

    return (true);
}

/// Tests the Creation Functions
bool GuitarTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 12, 2005
    Guitar guitar(1, wxT("Test"), 2, 3, 4, 5, 6, 7, 8, 9);
    Guitar* clone = (Guitar*)guitar.CloneObject();    
    TEST(wxT("CloneObject"),
        (*clone == guitar)
    );
    delete clone;
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool GuitarTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Dec 8, 2004
    
    // TEST CASE: Operator =
    {
        Guitar guitar(1, wxT("Test"), 2, 3, 4, 5, 6, 7, 8, 9);
        Guitar guitar2 = guitar;
        TEST(wxT("Operator="), 
            (guitar2.GetNumber() == 1) &&
            (guitar2.GetDescription() == wxT("Test")) &&
            (guitar2.GetPreset() == 2) &&
            (guitar2.GetInitialVolume() == 3) &&
            (guitar2.GetPan() == 4) &&
            (guitar2.GetReverb() == 5) &&
            (guitar2.GetChorus() == 6) &&
            (guitar2.GetTremolo() == 7) &&
            (guitar2.GetPhaser() == 8) &&
            (guitar2.GetCapo() == 9)
        );
            
        // TEST CASE: Self assignment
        {
            Guitar guitar(1, wxT("Test"), 2, 3, 4, 5, 6, 7, 8, 9);
            guitar = guitar;
            TEST(wxT("Operator= (self-assignment)"), 
                (guitar.GetNumber() == 1) &&
                (guitar.GetDescription() == wxT("Test")) &&
                (guitar.GetPreset() == 2) &&
                (guitar.GetInitialVolume() == 3) &&
                (guitar.GetPan() == 4) &&
                (guitar.GetReverb() == 5) &&
                (guitar.GetChorus() == 6) &&
                (guitar.GetTremolo() == 7) &&
                (guitar.GetPhaser() == 8) &&
                (guitar.GetCapo() == 9)
            );
        }
    }

    // TEST CASE: Operator==
    {
        Guitar guitar(1, wxT("Test"), 2, 3, 4, 5, 6, 7, 8, 9);
        Guitar guitar2(1, wxT("Test"), 2, 3, 4, 5, 6, 7, 8, 9);
        Guitar guitar3(2, wxT("Test"), 2, 3, 4, 5, 6, 7, 8, 9);
        Guitar guitar4(1, wxT("Test2"), 2, 3, 4, 5, 6, 7, 8, 9);
        Guitar guitar5(1, wxT("Test"), 3, 3, 4, 5, 6, 7, 8, 9);
        Guitar guitar6(1, wxT("Test"), 2, 4, 4, 5, 6, 7, 8, 9);
        Guitar guitar7(1, wxT("Test"), 2, 3, 5, 5, 6, 7, 8, 9);
        Guitar guitar8(1, wxT("Test"), 2, 3, 4, 6, 6, 7, 8, 9);
        Guitar guitar9(1, wxT("Test"), 2, 3, 4, 5, 7, 7, 8, 9);
        Guitar guitar10(1, wxT("Test"), 2, 3, 4, 5, 6, 8, 8, 9);
        Guitar guitar11(1, wxT("Test"), 2, 3, 4, 5, 6, 7, 9, 9);
        Guitar guitar12(1, wxT("Test"), 2, 3, 4, 5, 6, 7, 8, 10);
        
        // TEST CASE: guitar == guitar
        TEST(wxT("Operator== - guitar == guitar"), (guitar == guitar2));
        TEST(wxT("Operator== - guitar != guitar"), !(guitar == guitar3));
        TEST(wxT("Operator== - guitar != guitar 2"), !(guitar == guitar4));
        TEST(wxT("Operator== - guitar != guitar 3"), !(guitar == guitar5));
        TEST(wxT("Operator== - guitar != guitar 4"), !(guitar == guitar6));
        TEST(wxT("Operator== - guitar != guitar 5"), !(guitar == guitar7));
        TEST(wxT("Operator== - guitar != guitar 6"), !(guitar == guitar8));
        TEST(wxT("Operator== - guitar != guitar 7"), !(guitar == guitar9));
        TEST(wxT("Operator== - guitar != guitar 8"), !(guitar == guitar10));
        TEST(wxT("Operator== - guitar != guitar 9"), !(guitar == guitar11));
        TEST(wxT("Operator== - guitar != guitar 10"), !(guitar == guitar12));
    }

    // TEST CASE: Operator!=
    {
        Guitar guitar(1, wxT("Test"), 2, 3, 4, 5, 6, 7, 8, 9);
        Guitar guitar2(1, wxT("Test"), 2, 3, 4, 5, 6, 7, 8, 9);
        Guitar guitar3(2, wxT("Test"), 2, 3, 4, 5, 6, 7, 8, 9);
        Guitar guitar4(1, wxT("Test2"), 2, 3, 4, 5, 6, 7, 8, 9);
        Guitar guitar5(1, wxT("Test"), 3, 3, 4, 5, 6, 7, 8, 9);
        Guitar guitar6(1, wxT("Test"), 2, 4, 4, 5, 6, 7, 8, 9);
        Guitar guitar7(1, wxT("Test"), 2, 3, 5, 5, 6, 7, 8, 9);
        Guitar guitar8(1, wxT("Test"), 2, 3, 4, 6, 6, 7, 8, 9);
        Guitar guitar9(1, wxT("Test"), 2, 3, 4, 5, 7, 7, 8, 9);
        Guitar guitar10(1, wxT("Test"), 2, 3, 4, 5, 6, 8, 8, 9);
        Guitar guitar11(1, wxT("Test"), 2, 3, 4, 5, 6, 7, 9, 9);
        Guitar guitar12(1, wxT("Test"), 2, 3, 4, 5, 6, 7, 8, 10);

        // TEST CASE: guitar == guitar
        TEST(wxT("Operator!= - guitar == guitar"), !(guitar != guitar2));
        TEST(wxT("Operator!= - guitar != guitar"), (guitar != guitar3));
        TEST(wxT("Operator!= - guitar != guitar 2"), (guitar != guitar4));
        TEST(wxT("Operator!= - guitar != guitar 3"), (guitar != guitar5));
        TEST(wxT("Operator!= - guitar != guitar 4"), (guitar != guitar6));
        TEST(wxT("Operator!= - guitar != guitar 5"), (guitar != guitar7));
        TEST(wxT("Operator!= - guitar != guitar 6"), (guitar != guitar8));
        TEST(wxT("Operator!= - guitar != guitar 7"), (guitar != guitar9));
        TEST(wxT("Operator!= - guitar != guitar 8"), (guitar != guitar10));
        TEST(wxT("Operator!= - guitar != guitar 9"), (guitar != guitar11));
        TEST(wxT("Operator!= - guitar != guitar 10"), (guitar != guitar12));
    }
    
    return (true);
}

/// Tests Serialization
/// @return True if all tests were executed, false if not
bool GuitarTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Dec 8, 2004
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    Guitar guitarOut(1, wxT("Test"), 2, 3, 4, 5, 6, 7, 8, 9);
    guitarOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        Guitar guitarIn;
        guitarIn.Deserialize(streamIn, PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((guitarIn == guitarOut) 
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the Number Functions
/// @return True if all tests were executed, false if not
bool GuitarTestSuite::TestCaseNumber()
{
    //------Last Checked------//
    // - Dec 9, 2004
    Guitar guitar;
    guitar.SetNumber(2);
    TEST(wxT("SetNumber"), (guitar.GetNumber() == 2));
    return (true);
}

/// Tests the Preset Functions
/// @return True if all tests were executed, false if not
bool GuitarTestSuite::TestCasePreset()
{   
    //------Last Checked------//
    // - Dec 9, 2004
    Guitar guitar;
    wxByte i = Guitar::MIN_PRESET;
    for (; i <= (Guitar::MAX_PRESET + 1); i++)
    {
        TEST(wxString::Format(wxT("SetPreset - %d"), i),
            (guitar.SetPreset(i) == (i <= Guitar::MAX_PRESET)) &&
            ((i == (Guitar::MAX_PRESET + 1)) ? 1 : (guitar.GetPreset() == i)));
    }
    return (true);
}

/// Tests the Initial Volume Functions
/// @return True if all tests were executed, false if not
bool GuitarTestSuite::TestCaseInitialVolume()
{
    //------Last Checked------//
    // - Dec 9, 2004
    Guitar guitar;
    wxByte i = Guitar::MIN_INITIAL_VOLUME;
    for (; i <= (Guitar::MAX_INITIAL_VOLUME + 1); i++)
    {
        TEST(wxString::Format(wxT("SetInitialVolume - %d"), i),
            (guitar.SetInitialVolume(i) == (i <= Guitar::MAX_INITIAL_VOLUME)) &&
            ((i == (Guitar::MAX_INITIAL_VOLUME + 1)) ? 1 :
            (guitar.GetInitialVolume() == i)));
    }

    return (true);
}

/// Tests the Description Functions
/// @return True if all tests were executed, false if not
bool GuitarTestSuite::TestCaseDescription()
{
    //------Last Checked------//
    // - Dec 8, 2004
    Guitar guitar;
    TEST(wxT("SetDescription - NULL"), !guitar.SetDescription(NULL));
    TEST(wxT("SetDescription - valid"), (guitar.SetDescription(wxT("Test")) &&
        guitar.GetDescription() == wxT("Test")));
    return (true);
}

/// Tests the Reverb Functions
/// @return True if all tests were executed, false if not
bool GuitarTestSuite::TestCaseReverb()
{
    //------Last Checked------//
    // - Dec 9, 2004
    Guitar guitar;
    wxByte i = Guitar::MIN_REVERB;
    for (; i <= (Guitar::MAX_REVERB + 1); i++)
    {
        TEST(wxString::Format(wxT("SetReverb - %d"), i),
        (guitar.SetReverb(i) == (i <= Guitar::MAX_REVERB)) &&
        ((i == (Guitar::MAX_REVERB + 1)) ? 1 : (guitar.GetReverb() == i)));
    }
    return (true);
}

/// Tests the Chorus Functions
/// @return True if all tests were executed, false if not
bool GuitarTestSuite::TestCaseChorus()
{
    //------Last Checked------//
    // - Dec 9, 2004
    Guitar guitar;
    wxByte i = Guitar::MIN_CHORUS;
    for (; i <= (Guitar::MAX_CHORUS + 1); i++)
    {
        TEST(wxString::Format(wxT("SetChorus - %d"), i),
            (guitar.SetChorus(i) == (i <= Guitar::MAX_CHORUS)) &&
            ((i == (Guitar::MAX_CHORUS + 1)) ? 1 : (guitar.GetChorus() == i)));
    }
    return (true);
}

/// Tests the Tremolo Functions
/// @return True if all tests were executed, false if not
bool GuitarTestSuite::TestCaseTremolo()
{
    //------Last Checked------//
    // - Dec 9, 2004
    Guitar guitar;
    wxByte i = Guitar::MIN_TREMOLO;
    for (; i <= (Guitar::MAX_TREMOLO + 1); i++)
    {
        TEST(wxString::Format(wxT("SetTremolo - %d"), i),
            (guitar.SetTremolo(i) == (i <= Guitar::MAX_TREMOLO)) &&
            ((i == (Guitar::MAX_TREMOLO + 1)) ? 1 : (guitar.GetTremolo() == i)));
    }
    return (true);
}

/// Tests the Phaser Functions
/// @return True if all tests were executed, false if not
bool GuitarTestSuite::TestCasePhaser()
{
    //------Last Checked------//
    // - Dec 9, 2004
    Guitar guitar;
    wxByte i = Guitar::MIN_PHASER;
    for (; i <= (Guitar::MAX_PHASER + 1); i++)
    {
        TEST(wxString::Format(wxT("SetPhaser - %d"), i),
            (guitar.SetPhaser(i) == (i <= Guitar::MAX_PHASER)) &&
            ((i == (Guitar::MAX_PHASER + 1)) ? 1 : (guitar.GetPhaser() == i)));
    }
    return (true);
}

/// Test the Capo functions
/// @return True if all tests were executed, false if not
bool GuitarTestSuite::TestCaseCapo()
{
    //------Last Checked------//
    // - Dec 9, 2004
    Guitar guitar;
    
    // TEST CASE: SetCapo
    {
        wxByte i = Guitar::MIN_CAPO;
        for (; i <= (Guitar::MAX_CAPO + 1); i++)
        {
            TEST(wxString::Format(wxT("SetCapo - %d"), i),
                (guitar.SetCapo(i) == (i <= Guitar::MAX_CAPO)) &&
                ((i == (Guitar::MAX_CAPO + 1)) ? 1 : (guitar.GetCapo() == i)));
        }
    }
    
    // TEST CASE: UsesCapo
    {
        wxByte i = Guitar::MIN_CAPO;
        for (; i <= Guitar::MAX_CAPO; i++)
        {
            guitar.SetCapo(i);
            TEST(wxString::Format(wxT("UsesCapo - %d"), i),
                (guitar.UsesCapo() == (i != Guitar::MIN_CAPO)));
        }
    }
    return (true);
}

/// Tests the Tuning Functions
/// @return True if all tests were executed, false if not
bool GuitarTestSuite::TestCaseTuning()
{
    //------Last Checked------//
    // - Dec 8, 2004
    const Tuning tuning(wxT("Test"), -1, true, MIDI_NOTE_E4, MIDI_NOTE_B3,
        MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
    Guitar guitar;
    guitar.SetTuning(tuning);
    TEST(wxT("SetTuning"), (guitar.SetTuning(tuning) &&
        (guitar.GetTuning() == tuning)));
    return (true);
}
