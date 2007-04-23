/////////////////////////////////////////////////////////////////////////////
// Name:            tuningtestsuite.cpp
// Purpose:         Performs unit testing on the Tuning class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 9, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "tuningtestsuite.h"

#include "tuning.h"
#include "powertabfileheader.h"         // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(TuningTestSuite, TestSuite)

/// Default Constructor
TuningTestSuite::TuningTestSuite()
{
    //------Last Checked------//
    // - Dec 9, 2004
}

/// Destructor
TuningTestSuite::~TuningTestSuite()
{
    //------Last Checked------//
    // - Dec 9, 2004
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t TuningTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Dec 15, 2004
    return (292);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool TuningTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Dec 15, 2004
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseCreation())
        return (false);
    if (!TestCaseOperator())
        return (false);
    if (!TestCaseSerialize())
        return (false);
    if (!TestCaseTuning())
        return (false);
    if (!TestCaseName())
        return (false);
    if (!TestCaseMusicNotationOffset())
        return (false);
    if (!TestCaseSharps())
        return (false);
    if (!TestCaseString())
        return (false);
    if (!TestCaseNote())
        return (false);
    if (!TestCaseOperations())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool TuningTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Dec 15, 2004
    
    // TEST CASE: Default Constructor
    {
        Tuning tuning;
        TEST(wxT("Default Constructor"),
            (tuning.GetName() == Tuning::DEFAULT_NAME) &&
            (tuning.GetMusicNotationOffset() == 0) &&
            (!tuning.UsesSharps()) &&
            (tuning.GetStringCount() == 0)
        );
    }
    
    // TEST CASE: Primary Constructor
    {
        Tuning tuning(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        TEST(wxT("Primary Constructor"),
            (tuning.GetName() == wxT("Test")) &&
            (tuning.GetMusicNotationOffset() == -2) &&
            (tuning.UsesSharps()) &&
            (tuning.IsSameTuning(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2))
        );
    }
    
    // TEST CASE: Copy Constructor
    {
        Tuning tuning(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning2(tuning);
        TEST(wxT("Copy Constructor"),
            (tuning2.GetName() == wxT("Test")) &&
            (tuning2.GetMusicNotationOffset() == -2) &&
            (tuning2.UsesSharps()) &&
            (tuning2.IsSameTuning(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2))
        );
    }
    
    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool TuningTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 12, 2005
    Tuning tuning(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
    Tuning* clone = (Tuning*)tuning.CloneObject();    
    TEST(wxT("CloneObject"),
        (*clone == tuning)
    );
    delete clone;
    return (true);
}

/// Tests an Operators
/// @return True if all tests were executed, false if not
bool TuningTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Dec 15, 2004
    
    // TEST CASE: Operator=
    {
        Tuning tuning(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning2 = tuning;
        TEST(wxT("Operator="),
            (tuning2 == tuning)
        );
        
        // TEST CASE: Operator= (self-assignment)
        tuning = tuning;
        TEST(wxT("Operator= (self-assignment)"),
            (tuning == tuning)
        );
    }
    
    // TEST CASE: Operator==
    {
        Tuning tuning(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning2(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning3(wxT("Name2"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning4(wxT("Test"), -1, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning5(wxT("Test"), -2, false, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning6(wxT("Test"), -2, true, MIDI_NOTE_F4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning7(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_C3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning8(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_A3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning9(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_E3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning10(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_B2, MIDI_NOTE_E2);
        Tuning tuning11(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_F2);
        Tuning tuning12(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3);
        Tuning tuning13(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3);
        Tuning tuning14(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2);
        Tuning tuning15(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2, MIDI_NOTE_A1);        
        
        TEST(wxT("Operator== - tuning == tuning"), (tuning == tuning2));
        TEST(wxT("Operator== - tuning != tuning"), !(tuning == tuning3));
        TEST(wxT("Operator== - tuning != tuning 2"), !(tuning == tuning4));
        TEST(wxT("Operator== - tuning != tuning 3"), !(tuning == tuning5));
        TEST(wxT("Operator== - tuning != tuning 4"), !(tuning == tuning6));
        TEST(wxT("Operator== - tuning != tuning 5"), !(tuning == tuning7));
        TEST(wxT("Operator== - tuning != tuning 6"), !(tuning == tuning8));
        TEST(wxT("Operator== - tuning != tuning 7"), !(tuning == tuning9));
        TEST(wxT("Operator== - tuning != tuning 8"), !(tuning == tuning10));
        TEST(wxT("Operator== - tuning != tuning 9"), !(tuning == tuning11));
        TEST(wxT("Operator== - tuning != tuning 10"), !(tuning == tuning12));
        TEST(wxT("Operator== - tuning != tuning 11"), !(tuning == tuning13));
        TEST(wxT("Operator== - tuning != tuning 12"), !(tuning == tuning14));
        TEST(wxT("Operator== - tuning != tuning 13"), !(tuning == tuning15));
    }
    
    // TEST CASE: Operator!=
    {
        Tuning tuning(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning2(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning3(wxT("Name2"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning4(wxT("Test"), -1, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning5(wxT("Test"), -2, false, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning6(wxT("Test"), -2, true, MIDI_NOTE_F4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning7(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_C3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning8(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_A3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning9(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_E3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning10(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_B2, MIDI_NOTE_E2);
        Tuning tuning11(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_F2);
        Tuning tuning12(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3);
        Tuning tuning13(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3);
        Tuning tuning14(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2);
        Tuning tuning15(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2, MIDI_NOTE_A1);        
        
        TEST(wxT("Operator!= - tuning == tuning"), !(tuning != tuning2));
        TEST(wxT("Operator!= - tuning != tuning"), (tuning != tuning3));
        TEST(wxT("Operator!= - tuning != tuning 2"), (tuning != tuning4));
        TEST(wxT("Operator!= - tuning != tuning 3"), (tuning != tuning5));
        TEST(wxT("Operator!= - tuning != tuning 4"), (tuning != tuning6));
        TEST(wxT("Operator!= - tuning != tuning 5"), (tuning != tuning7));
        TEST(wxT("Operator!= - tuning != tuning 6"), (tuning != tuning8));
        TEST(wxT("Operator!= - tuning != tuning 7"), (tuning != tuning9));
        TEST(wxT("Operator!= - tuning != tuning 8"), (tuning != tuning10));
        TEST(wxT("Operator!= - tuning != tuning 9"), (tuning != tuning11));
        TEST(wxT("Operator!= - tuning != tuning 10"), (tuning != tuning12));
        TEST(wxT("Operator!= - tuning != tuning 11"), (tuning != tuning13));
        TEST(wxT("Operator!= - tuning != tuning 12"), (tuning != tuning14));
        TEST(wxT("Operator!= - tuning != tuning 13"), (tuning != tuning15));
    }
    
    return (true);
}

/// Tests Serialization
/// @return True if all tests were executed, false if not
bool TuningTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Dec 9, 2004
    
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    Tuning tuningOut(wxT("Test"), -1, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
    tuningOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        Tuning tuningIn;
        tuningIn.Deserialize(streamIn, PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((tuningIn == tuningOut) 
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
       
    return (true);
}

/// Tests the Tuning Functions
/// @return True if all tests were executed, false if not
bool TuningTestSuite::TestCaseTuning()
{
    //------Last Checked------//
    // - Dec 15, 2004

    // TEST CASE: SetTuning
    {
        Tuning tuning;
        TEST(wxT("SetTuning - invalid name"), !tuning.SetTuning(NULL, -1, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2));
        TEST(wxT("SetTuning - invalid music notation offset"), !tuning.SetTuning(wxT("Test"), Tuning::MIN_MUSIC_NOTATION_OFFSET - 1, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2));
        TEST(wxT("SetTuning - invalid note1"), !tuning.SetTuning(wxT("Test"), Tuning::MIN_MUSIC_NOTATION_OFFSET, true, 192, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2));
        TEST(wxT("SetTuning - invalid note2"), !tuning.SetTuning(wxT("Test"), Tuning::MIN_MUSIC_NOTATION_OFFSET, true, MIDI_NOTE_E4, 192, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2));
        TEST(wxT("SetTuning - invalid note3"), !tuning.SetTuning(wxT("Test"), Tuning::MIN_MUSIC_NOTATION_OFFSET, true, MIDI_NOTE_E4, MIDI_NOTE_B3, 192, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2));
        TEST(wxT("SetTuning - invalid note4"), !tuning.SetTuning(wxT("Test"), Tuning::MIN_MUSIC_NOTATION_OFFSET, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, 192, MIDI_NOTE_A2, MIDI_NOTE_E2));
        TEST(wxT("SetTuning - invalid note5"), !tuning.SetTuning(wxT("Test"), Tuning::MIN_MUSIC_NOTATION_OFFSET, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, 192, MIDI_NOTE_E2));
        TEST(wxT("SetTuning - invalid note6"), !tuning.SetTuning(wxT("Test"), Tuning::MIN_MUSIC_NOTATION_OFFSET, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, 192));
        TEST(wxT("SetTuning - invalid note7"), !tuning.SetTuning(wxT("Test"), Tuning::MIN_MUSIC_NOTATION_OFFSET, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2, 192));        
        TEST(wxT("SetTuning - valid"), tuning.SetTuning(wxT("Test"), Tuning::MIN_MUSIC_NOTATION_OFFSET, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2));
    }

    // TEST CASE: SetTuningFromString
    {
        Tuning tuning;
        TEST(wxT("SetTuningFromString - NULL string"), !tuning.SetTuningFromString(NULL));
        
        // (Name,Sharps,MusicNotationOffset,Note1,...,Note7)
        TEST(wxT("SetTuningFromString - valid string"),
            tuning.SetTuningFromString(wxT("Name,1,-2,64,59,55,50,45,40")) &&
            (tuning.GetName() == wxT("Name")) &&
            (tuning.UsesSharps()) &&
            (tuning.GetMusicNotationOffset() == -2) &&
            (tuning.IsSameTuning(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2))
        );
    }
    
    // TEST CASE: IsSameTuning(Tuning)
    {
        Tuning tuning(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning2(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning3(wxT("Test"), -2, true, MIDI_NOTE_F4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning4(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_C3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning5(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_A3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning6(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_E3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning7(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_B2, MIDI_NOTE_E2);
        Tuning tuning8(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_F2);
        Tuning tuning9(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3);
        Tuning tuning10(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3);
        Tuning tuning11(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2);
        Tuning tuning12(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2, MIDI_NOTE_A1);
        
        TEST(wxT("IsSameTuning - tuning == tuning"), tuning.IsSameTuning(tuning2));
        TEST(wxT("IsSameTuning - tuning != tuning"), !tuning.IsSameTuning(tuning3));
        TEST(wxT("IsSameTuning - tuning != tuning 2"), !tuning.IsSameTuning(tuning4));
        TEST(wxT("IsSameTuning - tuning != tuning 3"), !tuning.IsSameTuning(tuning5));
        TEST(wxT("IsSameTuning - tuning != tuning 4"), !tuning.IsSameTuning(tuning6));
        TEST(wxT("IsSameTuning - tuning != tuning 5"), !tuning.IsSameTuning(tuning7));
        TEST(wxT("IsSameTuning - tuning != tuning 6"), !tuning.IsSameTuning(tuning8));
        TEST(wxT("IsSameTuning - tuning != tuning 7"), !tuning.IsSameTuning(tuning9));
        TEST(wxT("IsSameTuning - tuning != tuning 8"), !tuning.IsSameTuning(tuning10));
        TEST(wxT("IsSameTuning - tuning != tuning 9"), !tuning.IsSameTuning(tuning11));
        TEST(wxT("IsSameTuning - tuning != tuning 10"), !tuning.IsSameTuning(tuning12));
    }

    // TEST CASE: IsSameTuning(wxByte,wxByte,wxByte,wxByte,wxByte,wxByte,wxByte)
    {
        Tuning tuning(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3);
        Tuning tuning2(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3);
        Tuning tuning3(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2);
        Tuning tuning4(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        Tuning tuning5(wxT("Test"), -2, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2, MIDI_NOTE_A1);
        
        TEST(wxT("IsSameTuning - 3 string tuning"), tuning.IsSameTuning(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3));
        TEST(wxT("IsSameTuning - 4 string tuning"), tuning2.IsSameTuning(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3));
        TEST(wxT("IsSameTuning - 5 string tuning"), tuning3.IsSameTuning(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2));
        TEST(wxT("IsSameTuning - 6 string tuning"), tuning4.IsSameTuning(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2));
        TEST(wxT("IsSameTuning - 7 string tuning"), tuning5.IsSameTuning(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2, MIDI_NOTE_A1));
    }
    
    return (true);
}

/// Tests the Name Functions
/// @return True if all tests were executed, false if not
bool TuningTestSuite::TestCaseName()
{
    //------Last Checked------//
    // - Dec 9, 2004
    Tuning tuning;
    TEST(wxT("SetName - NULL"), !tuning.SetName(NULL));
    TEST(wxT("SetName - valid"), ((tuning.SetName(wxT("Test")) && (tuning.GetName() == wxT("Test")))));
    return (true);
}

/// Tests the Music Notation Offset Functions
/// @return True if all tests were executed, false if not
bool TuningTestSuite::TestCaseMusicNotationOffset()
{
    //------Last Checked------//
    // - Dec 14, 2004
    
    // TEST CASE: IsValidMusicNotationOffset
    {
        wxInt8 i = Tuning::MIN_MUSIC_NOTATION_OFFSET - 1;
        for (; i <= (Tuning::MAX_MUSIC_NOTATION_OFFSET + 1); i++)
        {
            TEST(wxString::Format(wxT("IsValidMusicNotationOffset - %d"), i), 
                (Tuning::IsValidMusicNotationOffset(i) == (i >= Tuning::MIN_MUSIC_NOTATION_OFFSET && i <= Tuning::MAX_MUSIC_NOTATION_OFFSET))
            );
        }
    }
    
    Tuning tuning;
    wxInt8 i = Tuning::MIN_MUSIC_NOTATION_OFFSET - 1;
    for (; i <= (Tuning::MAX_MUSIC_NOTATION_OFFSET + 1); i++)
    {
        TEST(wxString::Format(wxT("SetMusicNotationOffset - %d"), i), 
            (tuning.SetMusicNotationOffset(i) == (i >= Tuning::MIN_MUSIC_NOTATION_OFFSET && i <= Tuning::MAX_MUSIC_NOTATION_OFFSET)) &&
            ((i < Tuning::MIN_MUSIC_NOTATION_OFFSET || i > Tuning::MAX_MUSIC_NOTATION_OFFSET) ? 1 : (tuning.GetMusicNotationOffset() == i))
        );
    }
    
    return (true);
}

/// Tests the Sharps Functions
/// @return True if all tests were executed, false if not
bool TuningTestSuite::TestCaseSharps()
{
    //------Last Checked------//
    // - Dec 15, 2004
    Tuning tuning;
    tuning.SetSharps();
    TEST(wxT("SetSharps - true"), (tuning.UsesSharps()));
    tuning.SetSharps(false);
    TEST(wxT("SetSharps - false"), (!tuning.UsesSharps()));
    return (true);
}

/// Tests the String Functions
/// @return True if all tests were executed, false if not
bool TuningTestSuite::TestCaseString()
{
    //------Last Checked------//
    // - Dec 15, 2004
    Tuning tuning(wxT("Test"), -1, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
    const size_t stringCount = tuning.GetStringCount();
    wxUint32 i = 0;
    for (; i <= (stringCount + 1); i++)
        TEST(wxString::Format(wxT("IsValidString - %d"), i), (tuning.IsValidString(i) == ((i >= 0) && (i < stringCount))));
            
    return (true);
}

/// Tests the Note Functions
/// @return True if all tests were executed, false if not
bool TuningTestSuite::TestCaseNote()
{
    //------Last Checked------//
    // - Dec 15, 2004
    
    // TEST CASE: SetNote
    {
        Tuning tuning(wxT("Test"), -1, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);    
    
        TEST(wxT("SetNote - invalid string"), !tuning.SetNote(6, MIDI_NOTE_G5));
        TEST(wxT("SetNote - invalid note"), !tuning.SetNote(0, 192));
    
        wxUint32 i = 0;
        wxUint32 stringCount = tuning.GetStringCount();
        for (; i < stringCount; i++)
        {
            bool set = tuning.SetNote(i, MIDI_NOTE_G5);
            TEST(wxString::Format(wxT("SetNote - string %d"), i),
                (set && tuning.GetNote(i) == MIDI_NOTE_G5)
            );
        }
        TEST(wxT("GetNote - invalid string"), tuning.GetNote(6) == MIDI_NOTE_MIDDLE_C);
    }

    // TEST CASE: GetNoteText
    {
        Tuning tuning(wxT("Test"), -1, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        TEST(wxT("GetNoteText - invalid string"), (tuning.GetNoteText(6) == wxT("")));
        
        const wxChar* expectedResults[6];
        expectedResults[0] = wxT("E");
        expectedResults[1] = wxT("B");
        expectedResults[2] = wxT("G");
        expectedResults[3] = wxT("D");
        expectedResults[4] = wxT("A");
        expectedResults[5] = wxT("E");
        
        wxUint32 i = 0;
        wxUint32 stringCount = tuning.GetStringCount();
        for (; i < stringCount; i++)
            TEST(wxT("GetNoteText - string %d"), (tuning.GetNoteText(i) == expectedResults[i]));
    }
    
    // TEST CASE: IsOpenStringNote
    {
        Tuning tuning(wxT("Test"), -1, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        wxByte note = MIN_MIDI_NOTE;
        for (; note <= MAX_MIDI_NOTE; note++)
        {
            TEST(wxString::Format(wxT("IsOpenStringNote - %d"), note), 
                tuning.IsOpenStringNote(note) == (
                (note == MIDI_NOTE_E4) ||
                (note == MIDI_NOTE_B3) ||
                (note == MIDI_NOTE_G3) ||
                (note == MIDI_NOTE_D3) ||
                (note == MIDI_NOTE_A2) ||
                (note == MIDI_NOTE_E2))
            );  
        }
    }
    
    // TEST CASE: GetNoteRange
    {
        Tuning tuning(wxT("Test"), -1, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
        wxSize range = tuning.GetNoteRange(0);
        TEST(wxT("GetNoteRange"), ((range.GetX() == MIDI_NOTE_E2) && (range.GetY() == MIDI_NOTE_E4 + 24))); 
    }
    
    // TEST CASE: AddTuningNotes
    {
        Tuning tuning;        
        TEST(wxT("AddTuningNotes - invalid note1"), !tuning.AddTuningNotes(192, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2, MIDI_NOTE_A2));
        TEST(wxT("AddTuningNotes - invalid note2"), !tuning.AddTuningNotes(MIDI_NOTE_E4, 192, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2, MIDI_NOTE_A2));
        TEST(wxT("AddTuningNotes - invalid note3"), !tuning.AddTuningNotes(MIDI_NOTE_E4, MIDI_NOTE_B3, 192, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2, MIDI_NOTE_A2));
        TEST(wxT("AddTuningNotes - invalid note4"), !tuning.AddTuningNotes(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, 192, MIDI_NOTE_A2, MIDI_NOTE_E2, MIDI_NOTE_A2));
        TEST(wxT("AddTuningNotes - invalid note5"), !tuning.AddTuningNotes(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, 192, MIDI_NOTE_E2, MIDI_NOTE_A2));
        TEST(wxT("AddTuningNotes - invalid note6"), !tuning.AddTuningNotes(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, 192, MIDI_NOTE_A2));
        TEST(wxT("AddTuningNotes - invalid note7"), !tuning.AddTuningNotes(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2, 192));
                
        TEST(wxT("AddTuningNotes - 3 string tuning"), 
            tuning.AddTuningNotes(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, Tuning::notUsed, Tuning::notUsed, Tuning::notUsed, Tuning::notUsed) &&
            tuning.IsSameTuning(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3)
        );
        TEST(wxT("AddTuningNotes - 4 string tuning"), 
            tuning.AddTuningNotes(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, Tuning::notUsed, Tuning::notUsed, Tuning::notUsed) &&
            tuning.IsSameTuning(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3)
        );  
        TEST(wxT("AddTuningNotes - 5 string tuning"), 
            tuning.AddTuningNotes(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, Tuning::notUsed, Tuning::notUsed) &&
            tuning.IsSameTuning(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2)
        );
        TEST(wxT("AddTuningNotes - 6 string tuning"), 
            tuning.AddTuningNotes(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2, Tuning::notUsed) &&
            tuning.IsSameTuning(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2)
        );
        TEST(wxT("AddTuningNotes - 7 string tuning"), 
            tuning.AddTuningNotes(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2, MIDI_NOTE_A1) &&
            tuning.IsSameTuning(MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2, MIDI_NOTE_A1)
        );
    }
    
    return (true);
}

/// Test the Operations
/// @return True if all tests were executed, false if not
bool TuningTestSuite::TestCaseOperations()
{
    //------Last Checked------//
    // - Dec 15, 2004
    Tuning tuning;
    Tuning tuning2(wxT("Test"), 0, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3);
    Tuning tuning3(wxT("Test"), 0, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3);
    Tuning tuning4(wxT("Test"), 0, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2);
    Tuning tuning5(wxT("Test"), 0, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2);
    Tuning tuning6(wxT("Test"), 0, true, MIDI_NOTE_E4, MIDI_NOTE_B3, MIDI_NOTE_G3, MIDI_NOTE_D3, MIDI_NOTE_A2, MIDI_NOTE_E2, MIDI_NOTE_A1);
        
    TEST(wxT("IsValid - false"), !tuning.IsValid());
    TEST(wxT("IsValid - 3 string tuning"), tuning2.IsValid());
    TEST(wxT("IsValid - 4 string tuning"), tuning3.IsValid());
    TEST(wxT("IsValid - 5 string tuning"), tuning4.IsValid());
    TEST(wxT("IsValid - 6 string tuning"), tuning5.IsValid());
    TEST(wxT("IsValid - 7 string tuning"), tuning6.IsValid());
        
    return (true);
}
