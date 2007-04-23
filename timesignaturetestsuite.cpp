/////////////////////////////////////////////////////////////////////////////
// Name:            timesignaturetestsuite.cpp
// Purpose:         Performs unit testing on the TimeSignature class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 13, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "timesignaturetestsuite.h"

#include "timesignature.h"
#include "powertabfileheader.h"             // Needed for file header constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(TimeSignatureTestSuite, TestSuite)

/// Default Constructor
TimeSignatureTestSuite::TimeSignatureTestSuite()
{
    //------Last Checked------//
    // - Dec 10, 2004
}

/// Destructor
TimeSignatureTestSuite::~TimeSignatureTestSuite()
{
    //------Last Checked------//
    // - Dec 10, 2004
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t TimeSignatureTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Dec 13, 2004
    return (146);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool TimeSignatureTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Dec 13, 2004
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseCreation())
        return (false);
    if (!TestCaseOperator())
        return (false);
    if (!TestCaseSerialize())
        return (false);
    if (!TestCaseMeter())
        return (false);
    if (!TestCaseBeatsPerMeasure())
        return (false);
    if (!TestCaseBeatAmount())
        return (false);
    if (!TestCaseBeamingPattern())
        return (false);
    if (!TestCaseShow())
        return (false);
    if (!TestCasePulses())
        return (false);
    if (!TestCaseFlag())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool TimeSignatureTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Dec 13, 2004
    
    // TEST CASE: Default Constructor
    {
        TimeSignature timeSignature;
        TEST(wxT("Default Constructor"),
            (timeSignature.GetBeatsPerMeasure() == 4) &&
            (timeSignature.GetBeatAmount() == 4) &&
            (timeSignature.GetPulses() == TimeSignature::DEFAULT_PULSES)
        );
    }
    
    // TEST CASE: Primary Constructor
    {
        TimeSignature timeSignature(12,8);
        TEST(wxT("Copy Constructor"),
            (timeSignature.GetBeatsPerMeasure() == 12) &&
            (timeSignature.GetBeatAmount() == 8) &&
            (timeSignature.GetPulses() == 4)
        );
    }
    
    // TEST CASE: Copy Constructor
    {
        TimeSignature timeSignature(12,8);
        TimeSignature timeSignature2(timeSignature);
        TEST(wxT("Copy Constructor"),
            (timeSignature2.GetBeatsPerMeasure() == 12) &&
            (timeSignature2.GetBeatAmount() == 8) &&
            (timeSignature2.GetPulses() == 4)
        );
    }
    
    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool TimeSignatureTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 12, 2005
    TimeSignature timeSignature(12,8);
    TimeSignature* clone = (TimeSignature*)timeSignature.CloneObject();    
    TEST(wxT("CloneObject"),
        (*clone == timeSignature)
    );
    delete clone;
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool TimeSignatureTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Dec 13, 2004
    
    // TEST CASE: Operator=
    {
        TimeSignature timeSignature(12,8);
        TimeSignature timeSignature2 = timeSignature;
        TEST(wxT("Operator="),
            (timeSignature2.GetBeatsPerMeasure() == 12) &&
            (timeSignature2.GetBeatAmount() == 8) &&
            (timeSignature2.GetPulses() == 4)
        );
        
        // TEST CASE: Operator= (self-assignment)
        timeSignature = timeSignature;
        TEST(wxT("Operator= (self-assignment)"),
            (timeSignature == timeSignature)
        );
    }
    
    // TEST CASE: Operator==
    {
        TimeSignature timeSignature(12,8);
        TimeSignature timeSignature2(12,8);
        TimeSignature timeSignature3(11,8);
        TimeSignature timeSignature4(12,16);
        TimeSignature timeSignature5(12,8);
        timeSignature5.SetBeamingPattern(5,3);
        TimeSignature timeSignature6(12,8);
        timeSignature6.SetCutTime();
        TimeSignature timeSignature7(12,8);
        timeSignature7.SetCommonTime();
        TimeSignature timeSignature8(12,8);
        timeSignature8.Show();
        
        TEST(wxT("Operator== - timeSignature == timeSignature"), (timeSignature == timeSignature2));
        TEST(wxT("Operator== - timeSignature != timeSignature"), !(timeSignature == timeSignature3));
        TEST(wxT("Operator== - timeSignature != timeSignature 2"), !(timeSignature == timeSignature4));
        TEST(wxT("Operator== - timeSignature != timeSignature 3"), !(timeSignature == timeSignature5));
        TEST(wxT("Operator== - timeSignature != timeSignature 4"), !(timeSignature == timeSignature6));
        TEST(wxT("Operator== - timeSignature != timeSignature 5"), !(timeSignature == timeSignature7));
        TEST(wxT("Operator== - timeSignature != timeSignature 6"), !(timeSignature == timeSignature8));
    }
    
    return (true);
}

/// Tests Serialization
/// @return True if all tests were executed, false if not
bool TimeSignatureTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Jan 12, 2005
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    TimeSignature timeSignatureOut(12,8);
    timeSignatureOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        TimeSignature timeSignatureIn;
        timeSignatureIn.Deserialize(streamIn, PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((timeSignatureIn == timeSignatureOut) 
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the Meter Functions
/// @return True if all tests were executed, false if not
bool TimeSignatureTestSuite::TestCaseMeter()
{
    //------Last Checked------//
    // - Dec 13, 2004
    TimeSignature timeSignature;
    TEST(wxT("SetMeter - invalid beatsPerMeasure"), (!timeSignature.SetMeter(0,4)));
    TEST(wxT("SetMeter - invalid beatsAmount"), (!timeSignature.SetMeter(4,0)));
    
    // TEST CASE: IsSameMeter
    {
        TimeSignature timeSignature(4,4);
        TimeSignature timeSignature2(4,4);
        TimeSignature timeSignature3(11,4);
        TimeSignature timeSignature4(11,8);
        TimeSignature timeSignature5;
        timeSignature5.SetCutTime();
        TimeSignature timeSignature6;
        timeSignature6.SetCommonTime();
        TEST(wxT("IsSameMeter - true"), timeSignature.IsSameMeter(timeSignature2));
        TEST(wxT("IsSameMeter - false"), !timeSignature.IsSameMeter(timeSignature3));
        TEST(wxT("IsSameMeter - false"), !timeSignature.IsSameMeter(timeSignature4));
        TEST(wxT("IsSameMeter - false"), !timeSignature.IsSameMeter(timeSignature5));
        TEST(wxT("IsSameMeter - true"), timeSignature.IsSameMeter(timeSignature6));
    }
    
    // TEST CASE: SetCutTime
    {
        TimeSignature timeSignature;
        timeSignature.SetCutTime();
        TEST(wxT("SetCutTime"), (timeSignature.IsCutTime()));
    }
    
    // TEST CASE: SetCommonTime
    {
        TimeSignature timeSignature;
        timeSignature.SetCommonTime();
        TEST(wxT("SetCommonTime"), (timeSignature.IsCommonTime()));
    }
    
    // TEST CASE: IsCompoundTime
    {
        const int testValueCount = 10;
        TimeSignature testValues[testValueCount];
        testValues[0] = TimeSignature(6,4);
        testValues[1] = TimeSignature(6,8);
        testValues[2] = TimeSignature(6,16);
        testValues[3] = TimeSignature(9,4);
        testValues[4] = TimeSignature(9,8);
        testValues[5] = TimeSignature(9,16);
        testValues[6] = TimeSignature(12,4);
        testValues[7] = TimeSignature(12,8);
        testValues[8] = TimeSignature(12,16);
        testValues[9] = TimeSignature(4,4);

        int i = 0;
        for (; i < testValueCount; i++)
            TEST(wxString::Format(wxT("IsCompoundTime - %s"), testValues[i].GetText(TimeSignature::textFull).c_str()), (testValues[i].IsCompoundTime() == (i < 9)));
    }
    
    // TEST CASE: IsQuadrupleTime
    {
        const int testValueCount = 7;
        TimeSignature testValues[testValueCount];
        testValues[0] = TimeSignature(4,4);
        testValues[1] = TimeSignature(4,2);
        testValues[2] = TimeSignature(4,8);
        testValues[3] = TimeSignature(12,4);
        testValues[4] = TimeSignature(12,8);
        testValues[5] = TimeSignature(12,16);
        testValues[6] = TimeSignature(5,4);

        int i = 0;
        for (; i < testValueCount; i++)
            TEST(wxString::Format(wxT("IsQuadrupleTime - %s"), testValues[i].GetText(TimeSignature::textFull).c_str()), (testValues[i].IsQuadrupleTime() == (i < 6)));
    }
    
    return (true);
}

/// Tests the Beats Per Measure Functions
/// @return True if all tests were executed, false if not
bool TimeSignatureTestSuite::TestCaseBeatsPerMeasure()
{
    //------Last Checked------//
    // - Dec 13, 2004
    
    // TEST CASE: IsValidBeatsPerMeasure
    {
        wxByte i = TimeSignature::MIN_BEATSPERMEASURE - 1;
        for (; i <= (TimeSignature::MAX_BEATSPERMEASURE + 1); i++)
            TEST(wxString::Format(wxT("IsValidBeatsPerMeasure - %d"), i), (TimeSignature::IsValidBeatsPerMeasure(i) == ((i >= TimeSignature::MIN_BEATSPERMEASURE) && (i <= TimeSignature::MAX_BEATSPERMEASURE))));
    }
    
    TimeSignature timeSignature;
    wxByte i = TimeSignature::MIN_BEATSPERMEASURE - 1;
    for (; i <= (TimeSignature::MAX_BEATSPERMEASURE + 1); i++)
    {
        timeSignature.SetBeatsPerMeasure(i);
        TEST(wxT("SetBeatsPerMeasure - %d"),
            (timeSignature.SetBeatsPerMeasure(i) == ((i >= TimeSignature::MIN_BEATSPERMEASURE) && (i <= TimeSignature::MAX_BEATSPERMEASURE))) &&
            (((i < TimeSignature::MIN_BEATSPERMEASURE) || (i > TimeSignature::MAX_BEATSPERMEASURE))) ? 1 : (timeSignature.GetBeatsPerMeasure() == i)
        );
    }
    return (true);
}

/// Tests the Beat Amount Functions
/// @return True if all tests were executed, false if not
bool TimeSignatureTestSuite::TestCaseBeatAmount()
{
    //------Last Checked------//
    // - Dec 13, 2004
    
    /// TEST CASE: IsValidBeatAmount
    {
        wxByte i = 1;
        for (; i <= (2 * TimeSignature::MAX_BEATAMOUNT); i += i)
            TEST(wxString::Format(wxT("IsValidBeatAmount - %d"), i), (TimeSignature::IsValidBeatAmount(i) == ((i >= TimeSignature::MIN_BEATAMOUNT) && (i <= TimeSignature::MAX_BEATAMOUNT))));
    }
    
    TimeSignature timeSignature;
    wxByte i = 1;
    for (; i <= (2 * TimeSignature::MAX_BEATAMOUNT); i += i)
    {
        timeSignature.SetBeatAmount(i);
        TEST(wxT("SetBeatAmount - %d"),
            (timeSignature.SetBeatAmount(i) == ((i >= TimeSignature::MIN_BEATAMOUNT) && (i <= TimeSignature::MAX_BEATAMOUNT))) &&
            (((i < TimeSignature::MIN_BEATAMOUNT) || (i > TimeSignature::MAX_BEATAMOUNT))) ? 1 : (timeSignature.GetBeatAmount() == i)
        );
    }
    return (true);
}

/// Tests the Beaming Pattern Functions
/// @return True if all tests were executed, false if not
bool TimeSignatureTestSuite::TestCaseBeamingPattern()
{
    //------Last Checked------//
    // - Dec 13, 2004
    TimeSignature timeSignature;
    
    TEST(wxT("SetBeamingPattern(wxByte, wxByte, wxByte, wxByte) - invalid beat1"), !timeSignature.SetBeamingPattern(0));
    TEST(wxT("SetBeamingPattern(wxByte, wxByte, wxByte, wxByte) - invalid beat2"), !timeSignature.SetBeamingPattern(4,TimeSignature::MAX_BEATAMOUNT + 1));
    TEST(wxT("SetBeamingPattern(wxByte, wxByte, wxByte, wxByte) - invalid beat3"), !timeSignature.SetBeamingPattern(4,4,TimeSignature::MAX_BEATAMOUNT + 1));
    TEST(wxT("SetBeamingPattern(wxByte, wxByte, wxByte, wxByte) - invalid beat4"), !timeSignature.SetBeamingPattern(4,4,4,TimeSignature::MAX_BEATAMOUNT + 1));
    
    wxByte beat1 = 0, beat2 = 0, beat3 = 0, beat4 = 0;
    timeSignature.SetBeamingPattern(4);
    timeSignature.GetBeamingPattern(beat1, beat2, beat3, beat4);
    TEST(wxT("SetBeamingPattern(wxByte, wxByte, wxByte, wxByte) - valid beat1"), 
        (beat1 == 4) && 
        (beat2 == 0) &&
        (beat3 == 0) &&
        (beat4 == 0)
    );
    
    beat1 = 0, beat2 = 0, beat3 = 0, beat4 = 0;
    timeSignature.SetBeamingPattern(3,4);
    timeSignature.GetBeamingPattern(beat1, beat2, beat3, beat4);
    TEST(wxT("SetBeamingPattern(wxByte, wxByte, wxByte, wxByte) - valid beat1, beat2"), 
        (beat1 == 3) &&
        (beat2 == 4) &&
        (beat3 == 0) &&
        (beat4 == 0)
    );
    
    beat1 = 0, beat2 = 0, beat3 = 0, beat4 = 0;
    timeSignature.SetBeamingPattern(2,3,4);
    timeSignature.GetBeamingPattern(beat1, beat2, beat3, beat4);
    TEST(wxT("SetBeamingPattern(wxByte, wxByte, wxByte, wxByte) - valid beat1, beat2, beat3"), 
        (beat1 == 2) &&
        (beat2 == 3) &&
        (beat3 == 4) &&
        (beat4 == 0)
    );
    
    beat1 = 0, beat2 = 0, beat3 = 0, beat4 = 0;
    timeSignature.SetBeamingPattern(1,2,3,4);
    timeSignature.GetBeamingPattern(beat1, beat2, beat3, beat4);
    TEST(wxT("SetBeamingPattern(wxByte, wxByte, wxByte, wxByte) - valid beat1, beat2, beat3, beat4"), 
        (beat1 == 1) &&
        (beat2 == 2) &&
        (beat3 == 3) &&
        (beat4 == 4)
    );
    
    // TEST CASE: SetBeamingPatternFromwxUint32
    {
        TimeSignature timeSignature;
        const int testValueCount = 4;
        wxUint32 testValues[testValueCount];
        testValues[0] = MAKELONG(MAKEWORD(0,0), MAKEWORD(0,0));
        testValues[1] = MAKELONG(MAKEWORD(4,TimeSignature::MAX_BEATAMOUNT + 1), MAKEWORD(0,0));
        testValues[2] = MAKELONG(MAKEWORD(3,4), MAKEWORD(TimeSignature::MAX_BEATAMOUNT + 1,0));
        testValues[3] = MAKELONG(MAKEWORD(2,3), MAKEWORD(4,TimeSignature::MAX_BEATAMOUNT + 1));
        
        int i = 0;
        for (; i < testValueCount; i++)
            TEST(wxString::Format(wxT("SetBeamingPatternFromwxUint32 - %d"), testValues[i]), !timeSignature.SetBeamingPatternFromwxUint32(testValues[i]));
            
        wxByte beat1 = 0, beat2 = 0, beat3 = 0, beat4 = 0;
        timeSignature.SetBeamingPattern(MAKELONG(MAKEWORD(4,0), MAKEWORD(0,0)));
        timeSignature.GetBeamingPattern(beat1, beat2, beat3, beat4);
        TEST(wxT("SetBeamingPattern(wxByte, wxByte, wxByte, wxByte) - valid beat1"), 
            (beat1 == 4) && 
            (beat2 == 0) &&
            (beat3 == 0) &&
            (beat4 == 0)
        );
    
        beat1 = 0, beat2 = 0, beat3 = 0, beat4 = 0;
        timeSignature.SetBeamingPatternFromwxUint32(MAKELONG(MAKEWORD(3,4), MAKEWORD(0,0)));
        timeSignature.GetBeamingPattern(beat1, beat2, beat3, beat4);
        TEST(wxT("SetBeamingPattern(wxByte, wxByte, wxByte, wxByte) - valid beat1, beat2"), 
            (beat1 == 3) &&
            (beat2 == 4) &&
            (beat3 == 0) &&
            (beat4 == 0)
        );
    
        beat1 = 0, beat2 = 0, beat3 = 0, beat4 = 0;
        timeSignature.SetBeamingPatternFromwxUint32(MAKELONG(MAKEWORD(2,3), MAKEWORD(4,0)));
        timeSignature.GetBeamingPattern(beat1, beat2, beat3, beat4);
        TEST(wxT("SetBeamingPattern(wxByte, wxByte, wxByte, wxByte) - valid beat1, beat2, beat3"), 
            (beat1 == 2) &&
            (beat2 == 3) &&
            (beat3 == 4) &&
            (beat4 == 0)
        );
    
        beat1 = 0, beat2 = 0, beat3 = 0, beat4 = 0;
        timeSignature.SetBeamingPatternFromwxUint32(MAKELONG(MAKEWORD(1,2), MAKEWORD(3,4)));
        timeSignature.GetBeamingPattern(beat1, beat2, beat3, beat4);
        TEST(wxT("SetBeamingPattern(wxByte, wxByte, wxByte, wxByte) - valid beat1, beat2, beat3, beat4"), 
            (beat1 == 1) &&
            (beat2 == 2) &&
            (beat3 == 3) &&
            (beat4 == 4)
        );
    }
    return (true);
}

/// Tests the Show Functions
/// @return True if all tests were executed, false if not
bool TimeSignatureTestSuite::TestCaseShow()
{
    //------Last Checked------//
    // - Dec 13, 2004
    TimeSignature timeSignature;
    timeSignature.Show();
    TEST(wxT("Show - true"), timeSignature.IsShown());
    timeSignature.Hide();
    TEST(wxT("Show - false"), !timeSignature.IsShown());
    return (true);
}

/// Tests the Pulses Functions
/// @return True if all tests were executed, false if not
bool TimeSignatureTestSuite::TestCasePulses()
{
    //------Last Checked------//
    // - Dec 13, 2004
    TimeSignature timeSignature;
    wxByte i = TimeSignature::MIN_PULSES - 1;
    for (; i <= (TimeSignature::MAX_PULSES + 1); i++)
        TEST(wxT("IsValidPulses - %d"), (TimeSignature::IsValidPulses(i) == ((i >= TimeSignature::MIN_PULSES) && (i <= TimeSignature::MAX_PULSES))));
    
    i = TimeSignature::MIN_PULSES - 1;
    {
        timeSignature.SetPulses(i);
        TEST(wxT("SetPulses - %d"),
            (timeSignature.SetPulses(i) == ((i >= TimeSignature::MIN_PULSES) && (i <= TimeSignature::MAX_PULSES))) &&
            (((i < TimeSignature::MIN_PULSES) || (i > TimeSignature::MAX_PULSES))) ? 1 : (timeSignature.GetPulses() == i)
        );
    }
    return (true);
}

/// Tests the Flag Functions
/// @return True if all tests were executed, false if not
bool TimeSignatureTestSuite::TestCaseFlag()
{
    //------Last Checked------//
    // - Dec 13, 2004
    const int testValueCount = 5;
    wxUint32 testValues[testValueCount];
    testValues[0] = TimeSignature::show;
    testValues[1] = TimeSignature::brackets;
    testValues[2] = TimeSignature::cutTime;
    testValues[3] = TimeSignature::commonTime;
    testValues[4] = 29393;
    
    TimeSignature timeSignature;
    int i = 0;
    for (; i < testValueCount; i++)
    {
        timeSignature.SetFlag(testValues[i]);
        TEST(wxString::Format(wxT("SetFlag - 0x%x"), testValues[i]), ((timeSignature.SetFlag(testValues[i]) == (i < 4)) && (timeSignature.IsFlagSet(testValues[i]) == (i < 4))));
    }
    return (true);
}
