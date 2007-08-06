/////////////////////////////////////////////////////////////////////////////
// Name:            tempomarkertestsuite.cpp
// Purpose:         Performs unit testing on the TempoMarker class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "tempomarkertestsuite.h"

#include "tempomarker.h"
#include "powertabfileheader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(TempoMarkerTestSuite, TestSuite)

/// Default Constructor
TempoMarkerTestSuite::TempoMarkerTestSuite()
{
    //------Last Checked------//
    // - Jan 13, 2005
}

/// Destructor
TempoMarkerTestSuite::~TempoMarkerTestSuite()
{
    //------Last Checked------//
    // - Jan 13, 2005
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t TempoMarkerTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Jan 13, 2005
    return (624);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool TempoMarkerTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Jan 13, 2005
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseCreation())
        return (false);
    if (!TestCaseOperator())
        return (false);
    if (!TestCaseSerialize())
        return (false);
    if (!TestCaseType())
        return (false);
    if (!TestCaseStandardMarker())
        return (false);
    if (!TestCaseListesso())
        return (false);
    if (!TestCaseAlterationOfPace())
        return (false);
    if (!TestCaseBeatType())
        return (false);
    if (!TestCaseListessoBeatType())
        return (false);
    if (!TestCaseTripletFeel())
        return (false);
    if (!TestCaseBeatsPerMinute())
        return (false);
    if (!TestCaseDescription())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool TempoMarkerTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 13, 2005
       
    // TEST CASE: Default constructor
    {
        TempoMarker tempoMarker;
        TEST(wxT("Default Constructor"), 
            (tempoMarker.GetSystem() == SystemSymbol::DEFAULT_SYSTEM) &&
            (tempoMarker.GetPosition() == SystemSymbol::DEFAULT_POSITION) &&
            (tempoMarker.IsStandardMarker()) &&
            (tempoMarker.GetBeatType() == TempoMarker::DEFAULT_BEAT_TYPE) &&
            (tempoMarker.GetBeatsPerMinute() ==
            TempoMarker::DEFAULT_BEATS_PER_MINUTE)
        );
    }
    
    // TEST CASE: Primary constructor
    {
        TempoMarker tempoMarker(1, 2, TempoMarker::quarter, 130, wxT("Test"),
            TempoMarker::tripletFeelEighth);
        TEST(wxT("Primary Constructor"), 
            (tempoMarker.IsStandardMarker()) &&
            (tempoMarker.GetSystem() == 1) &&
            (tempoMarker.GetPosition() == 2) &&
            (tempoMarker.GetBeatType() == TempoMarker::quarter) &&
            (tempoMarker.GetBeatsPerMinute() == 130) &&
            (tempoMarker.GetDescription() == wxT("Test")) &&
            (tempoMarker.GetTripletFeelType() == TempoMarker::tripletFeelEighth)
        );
    }
    
    // TEST CASE: Listesso Constructor
    {
        TempoMarker tempoMarker(1, 2, TempoMarker::quarter, TempoMarker::half,
            wxT("Test"));
        TEST(wxT("Listesso Constructor"),
            (tempoMarker.IsListesso()) &&
            (tempoMarker.GetSystem() == 1) &&
            (tempoMarker.GetPosition() == 2) &&
            (tempoMarker.GetBeatType() == TempoMarker::quarter) &&
            (tempoMarker.GetListessoBeatType() == TempoMarker::half) &&
            (tempoMarker.GetDescription() == wxT("Test"))
        ); 
    }
    
    // TEST CASE: Alteration Of Pace Constructor
    {
        TempoMarker tempoMarker(1, 2, true);
        TEST(wxT("Alteration Of Pace Constructor"),
            (tempoMarker.IsAlterationOfPace()) &&
            (tempoMarker.IsAccelerando())
        );
        
        TempoMarker tempoMarker2(1, 2, false);
        TEST(wxT("Alteration Of Pace Constructor"),
            (tempoMarker2.IsAlterationOfPace()) &&
            (tempoMarker2.IsRitardando())
        );
    }
    
    // TEST CASE: Copy constructor
    {
        TempoMarker tempoMarker(1, 2, TempoMarker::quarterDotted, 60,
            wxT("Test"), TempoMarker::tripletFeelEighth);
        TempoMarker tempoMarker2(tempoMarker);
        TEST(wxT("Copy Constructor"), 
            (tempoMarker2 == tempoMarker)
        );
    }

    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool TempoMarkerTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 12, 2005
    TempoMarker tempoMarker(1, 2, TempoMarker::quarter, 130, wxT("Test"),
        TempoMarker::tripletFeelEighth);
    TempoMarker* clone = (TempoMarker*)tempoMarker.CloneObject();
    TEST(wxT("CloneObject"),
        (*clone == tempoMarker)
    );
    delete clone;
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool TempoMarkerTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 13, 2005
            
    // TEST CASE: Operator=
    {
        TempoMarker tempoMarker(1, 2, TempoMarker::quarter, 130, wxT("Test"),
            TempoMarker::tripletFeelEighth);
        TempoMarker tempoMarker2 = tempoMarker;
        TEST(wxT("Operator="), 
            (tempoMarker2 == tempoMarker)
        );
        
        tempoMarker = tempoMarker;
        TEST(wxT("Operator= (self-assignment)"),
            (tempoMarker == tempoMarker)
        );
    }
    
    // TEST CASE: Operator==
    {
        TempoMarker tempoMarker(1, 2, TempoMarker::quarter, 130, wxT("Test"),
            TempoMarker::tripletFeelEighth);
        TempoMarker tempoMarker2(1, 2, TempoMarker::quarter, 130, wxT("Test"),
            TempoMarker::tripletFeelEighth);
        TempoMarker tempoMarker3(2, 2, TempoMarker::quarter, 130, wxT("Test"),
            TempoMarker::tripletFeelEighth);
        TempoMarker tempoMarker4(1, 3, TempoMarker::quarter, 130, wxT("Test"),
            TempoMarker::tripletFeelEighth);
        TempoMarker tempoMarker5(1, 2, TempoMarker::quarterDotted, 130,
            wxT("Test"), TempoMarker::tripletFeelEighth);
        TempoMarker tempoMarker6(1, 2, TempoMarker::quarter, 131, wxT("Test"),
            TempoMarker::tripletFeelEighth);
        TempoMarker tempoMarker7(1, 2, TempoMarker::quarter, 130, wxT("Test2"),
            TempoMarker::tripletFeelEighth);
        TempoMarker tempoMarker8(1, 2, TempoMarker::quarter, 130, wxT("Test"),
            TempoMarker::tripletFeelEighthOff);
        TempoMarker tempoMarker9(1, 2, TempoMarker::quarter, TempoMarker::half,
            wxT("Test"));
        TempoMarker tempoMarker10(1, 2, true);
        TempoMarker tempoMarker11(1, 2, false);
               
        TEST(wxT("Operator== - tempoMarker == tempoMarker"),
            (tempoMarker == tempoMarker2));
        TEST(wxT("Operator== - tempoMarker != tempoMarker"),
            !(tempoMarker == tempoMarker3));
        TEST(wxT("Operator== - tempoMarker != tempoMarker 2"),
            !(tempoMarker == tempoMarker4));
        TEST(wxT("Operator== - tempoMarker != tempoMarker 3"),
            !(tempoMarker == tempoMarker5));
        TEST(wxT("Operator== - tempoMarker != tempoMarker 4"),
            !(tempoMarker == tempoMarker6));
        TEST(wxT("Operator== - tempoMarker != tempoMarker 5"),
            !(tempoMarker == tempoMarker7));
        TEST(wxT("Operator== - tempoMarker != tempoMarker 6"),
            !(tempoMarker == tempoMarker8));
        TEST(wxT("Operator== - tempoMarker != tempoMarker 7"),
            !(tempoMarker == tempoMarker9));
        TEST(wxT("Operator== - tempoMarker != tempoMarker 8"),
            !(tempoMarker == tempoMarker10));
        TEST(wxT("Operator== - tempoMarker != tempoMarker 9"),
            !(tempoMarker == tempoMarker11));
    }
        
    // TEST CASE: Operator!=
    {
        TempoMarker tempoMarker(1, 2, TempoMarker::quarter, 130, wxT("Test"),
            TempoMarker::tripletFeelEighth);
        TempoMarker tempoMarker2(1, 2, TempoMarker::quarter, 130, wxT("Test"),
            TempoMarker::tripletFeelEighth);
        TempoMarker tempoMarker3(2, 2, TempoMarker::quarter, 130, wxT("Test"),
            TempoMarker::tripletFeelEighth);
        TempoMarker tempoMarker4(1, 3, TempoMarker::quarter, 130, wxT("Test"),
            TempoMarker::tripletFeelEighth);
        TempoMarker tempoMarker5(1, 2, TempoMarker::quarterDotted, 130,
            wxT("Test"), TempoMarker::tripletFeelEighth);
        TempoMarker tempoMarker6(1, 2, TempoMarker::quarter, 131, wxT("Test"),
            TempoMarker::tripletFeelEighth);
        TempoMarker tempoMarker7(1, 2, TempoMarker::quarter, 130, wxT("Test2"),
            TempoMarker::tripletFeelEighth);
        TempoMarker tempoMarker8(1, 2, TempoMarker::quarter, 130, wxT("Test"),
            TempoMarker::tripletFeelEighthOff);
        TempoMarker tempoMarker9(1, 2, TempoMarker::quarter, TempoMarker::half,
            wxT("Test"));
        TempoMarker tempoMarker10(1, 2, true);
        TempoMarker tempoMarker11(1, 2, false);
               
        TEST(wxT("Operator!= - tempoMarker == tempoMarker"),
            !(tempoMarker != tempoMarker2));
        TEST(wxT("Operator!= - tempoMarker != tempoMarker"),
            (tempoMarker != tempoMarker3));
        TEST(wxT("Operator!= - tempoMarker != tempoMarker 2"),
            (tempoMarker != tempoMarker4));
        TEST(wxT("Operator!= - tempoMarker != tempoMarker 3"),
            (tempoMarker != tempoMarker5));
        TEST(wxT("Operator!= - tempoMarker != tempoMarker 4"),
            (tempoMarker != tempoMarker6));
        TEST(wxT("Operator!= - tempoMarker != tempoMarker 5"),
            (tempoMarker != tempoMarker7));
        TEST(wxT("Operator!= - tempoMarker != tempoMarker 6"),
            (tempoMarker != tempoMarker8));
        TEST(wxT("Operator!= - tempoMarker != tempoMarker 7"),
            (tempoMarker != tempoMarker9));
        TEST(wxT("Operator!= - tempoMarker != tempoMarker 8"),
            (tempoMarker != tempoMarker10));
        TEST(wxT("Operator!= - tempoMarker != tempoMarker 9"),
            (tempoMarker != tempoMarker11));
    }
    
    return (true);
}

/// Tests the Serialization Functions
/// @return True if all tests were executed, false if not
bool TempoMarkerTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Jan 13, 2005
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    TempoMarker tempoMarkerOut(1, 2, TempoMarker::quarter, 130, wxT("Test"),
        TempoMarker::tripletFeelEighth);
    tempoMarkerOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        TempoMarker tempoMarkerIn;
        tempoMarkerIn.Deserialize(streamIn,
            PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((tempoMarkerIn == tempoMarkerOut) 
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the Type Functions
/// @return True if all tests were executed, false if not
bool TempoMarkerTestSuite::TestCaseType()
{
    //------Last Checked------//
    // - Jan 13, 2005
    
    // TEST CASE: IsValidType
    {
        wxByte i = TempoMarker::notShown;
        for (; i <= (TempoMarker::alterationOfPace + 1); i++)
        {
            TEST(wxString::Format(wxT("IsValidType - %d"), i),
                (TempoMarker::IsValidType(i) ==
                (i <= TempoMarker::alterationOfPace))
            );
        }
    }
    
    // TEST CASE: SetType
    {
        TempoMarker tempoMarker;
        wxByte i = TempoMarker::notShown;
        for (; i <= (TempoMarker::alterationOfPace + 1); i++)
        {
            TEST(wxString::Format(wxT("SetType - %d"), i),
                (tempoMarker.SetType(i) == (i <= TempoMarker::alterationOfPace)) &&
                ((i > TempoMarker::alterationOfPace) ? 1 :
                (tempoMarker.GetType() == i))
            );
        }
    }      
      
    return (true);
}

/// Tests the Standard Marker Functions
/// @return True if all tests were executed, false if not
bool TempoMarkerTestSuite::TestCaseStandardMarker()
{
    //------Last Checked------//
    // - Jan 13, 2005
    TempoMarker tempoMarker;
    
    TEST(wxT("SetStandardMarker - invalid beat type"),
        !tempoMarker.SetStandardMarker(255, 130, wxT("Test"),
        TempoMarker::tripletFeelEighth)
    );
    
    TEST(wxT("SetStandardMarker - invalid bpm"),
        !tempoMarker.SetStandardMarker(TempoMarker::quarter, 430, wxT("Test"),
        TempoMarker::tripletFeelEighth)
    );
    
    TEST(wxT("SetStandardMarker - invalid description"),
        !tempoMarker.SetStandardMarker(TempoMarker::quarter, 130, NULL,
        TempoMarker::tripletFeelEighth)
    );
    
    TEST(wxT("SetStandardMarker - invalid triplet feel type"),
        !tempoMarker.SetStandardMarker(TempoMarker::quarter, 130, wxT("Test"),
        255)
    );
    
    TEST(wxT("SetStandardMarker - valid"),
        tempoMarker.SetStandardMarker(TempoMarker::quarter, 130, wxT("Test"),
        TempoMarker::tripletFeelEighth) &&
        (tempoMarker.GetBeatType() == TempoMarker::quarter) &&
        (tempoMarker.GetBeatsPerMinute() == 130) &&
        (tempoMarker.GetDescription() == wxT("Test")) &&
        (tempoMarker.GetTripletFeelType() == TempoMarker::tripletFeelEighth)
    );
    
    return (true);
}

/// Tests the Listesso Functions
/// @return True if all tests were executed, false if not
bool TempoMarkerTestSuite::TestCaseListesso()
{
    //------Last Checked------//
    // - Jan 13, 2005
    
    TempoMarker tempoMarker;
    TEST(wxT("SetListesso - invalid beat type"),
        !tempoMarker.SetListesso(255, TempoMarker::quarter, wxT("Test"))
    );
    
    TEST(wxT("SetListesso - invalid listesso beat type"),
        !tempoMarker.SetListesso(TempoMarker::half, 255, wxT("Test"))
    );
    
    TEST(wxT("SetListesso - invalid description"),
        !tempoMarker.SetListesso(TempoMarker::half, TempoMarker::quarter, NULL)
    );
    
    TEST(wxT("SetListesso - valid"),
        (tempoMarker.SetListesso(TempoMarker::half, TempoMarker::quarter,
        wxT("Test"))) &&
        (tempoMarker.IsListesso()) &&
        (tempoMarker.GetBeatType() == TempoMarker::half) &&
        (tempoMarker.GetListessoBeatType() == TempoMarker::quarter) &&
        (tempoMarker.GetDescription() == wxT("Test"))
    );
    
    return (true);
}

/// Tests the Alteration Of Pace Functions
/// @return True if all tests were executed, false if not
bool TempoMarkerTestSuite::TestCaseAlterationOfPace()
{
    //------Last Checked------//
    // - Jan 13, 2005
    
    TempoMarker tempoMarker;
    TEST(wxT("SetAlterationOfPace - accelerando"),
        tempoMarker.SetAlterationOfPace(true) &&
        (tempoMarker.IsAlterationOfPace()) &&
        (tempoMarker.IsAccelerando())
    );
    
    TEST(wxT("SetAlterationOfPace - ritardando"),
        tempoMarker.SetAlterationOfPace(false) &&
        (tempoMarker.IsAlterationOfPace()) &&
        (tempoMarker.IsRitardando())
    );
        
    return (true);
}

/// Tests the Beat Type Functions
/// @return True if all tests were executed, false if not
bool TempoMarkerTestSuite::TestCaseBeatType()
{
    //------Last Checked------//
    // - Jan 13, 2005
    
    // TEST CASE: IsValidBeatType
    {
        wxByte i = TempoMarker::half;
        for (; i <= (TempoMarker::thirtySecondDotted + 1); i++)
            TEST(wxString::Format(wxT("IsValidBeatType - %d"), i),
                (TempoMarker::IsValidBeatType(i) ==
                (i <= TempoMarker::thirtySecondDotted))
            );
    }
    
    // TEST CASE: SetBeatType
    {
        TempoMarker tempoMarker;
        wxByte i = TempoMarker::half;
        for (; i <= (TempoMarker::thirtySecondDotted + 1); i++)
            TEST(wxString::Format(wxT("SetBeatType - %d"), i),
                (tempoMarker.SetBeatType(i) ==
                (i <= TempoMarker::thirtySecondDotted)) &&
                ((i > TempoMarker::thirtySecondDotted) ? 1 :
                (tempoMarker.GetBeatType() == i))
            );
    }      
  
    return (true);
}

/// Tests the Listesso Beat Type Functions
/// @return True if all tests were executed, false if not
bool TempoMarkerTestSuite::TestCaseListessoBeatType()
{
    //------Last Checked------//
    // - Jan 13, 2005
    
    // TEST CASE: SetListessoBeatType
    {
        TempoMarker tempoMarker;
        wxByte i = TempoMarker::half;
        for (; i <= (TempoMarker::thirtySecondDotted + 1); i++)
            TEST(wxString::Format(wxT("SetListessoBeatType - %d"), i),
                (tempoMarker.SetListessoBeatType(i) == 
                (i <= TempoMarker::thirtySecondDotted)) &&
                ((i > TempoMarker::thirtySecondDotted) ? 1 :
                (tempoMarker.GetListessoBeatType() == i))
            );
    }      
  
    return (true);
}

/// Tests the Triplet Feel Functions
/// @return True if all tests were executed, false if not
bool TempoMarkerTestSuite::TestCaseTripletFeel()
{
    //------Last Checked------//
    // - Jan 13, 2005
    
    // TEST CASE: IsValidTripletFeelType
    {
        wxByte i = TempoMarker::noTripletFeel;
        for (; i <= (TempoMarker::tripletFeelSixteenthOff + 1); i++)
            TEST(wxString::Format(wxT("IsValidTripletFeelType - %d"), i),
                (TempoMarker::IsValidTripletFeelType(i) ==
                (i <= TempoMarker::tripletFeelSixteenthOff))
            );
    }
    
    // TEST CASE: SetTripletFeelType
    {
        TempoMarker tempoMarker;
        wxByte i = TempoMarker::noTripletFeel;
        for (; i <= (TempoMarker::tripletFeelSixteenthOff + 1); i++)
            TEST(wxString::Format(wxT("SetTripletFeelType - %d"), i),
                (tempoMarker.SetTripletFeelType(i) ==
                (i <= TempoMarker::tripletFeelSixteenthOff)) &&
                ((i > TempoMarker::tripletFeelSixteenthOff) ? 1 :
                (tempoMarker.GetTripletFeelType() == i))
            );
    }
        
    return (true);
}

/// Tests the Beats Per Minute Functions
/// @return True if all tests were executed, false if not
bool TempoMarkerTestSuite::TestCaseBeatsPerMinute()
{
    //------Last Checked------//
    // - Jan 13, 2005
    
    // TEST CASE: IsValidBeatsPerMinute
    {
        wxWord i = TempoMarker::MIN_BEATS_PER_MINUTE - 1;
        for (; i <= (TempoMarker::MAX_BEATS_PER_MINUTE + 1); i++)
            TEST(wxString::Format(wxT("IsValidBeatsPerMinute - %d"), i),
                (TempoMarker::IsValidBeatsPerMinute(i) ==
                ((i >= TempoMarker::MIN_BEATS_PER_MINUTE) &&
                (i <= TempoMarker::MAX_BEATS_PER_MINUTE)))
            );
    }
    
    // TEST CASE: SetBeatsPerMinute
    {
        TempoMarker tempoMarker;
        wxWord i = TempoMarker::MIN_BEATS_PER_MINUTE - 1;
        for (; i <= (TempoMarker::MAX_BEATS_PER_MINUTE + 1); i++)
            TEST(wxString::Format(wxT("SetBeatsPerMinute - %d"), i),
                (tempoMarker.SetBeatsPerMinute(i) == 
                ((i >= TempoMarker::MIN_BEATS_PER_MINUTE) &&
                (i <= TempoMarker::MAX_BEATS_PER_MINUTE))) &&
                (((i < TempoMarker::MIN_BEATS_PER_MINUTE) ||
                (i > TempoMarker::MAX_BEATS_PER_MINUTE)) ? 1 :
                (tempoMarker.GetBeatsPerMinute() == i))
            );
    }
    
    return (true);
}

/// Tests the Description Functions
/// @return True if all tests were executed, false if not
bool TempoMarkerTestSuite::TestCaseDescription()
{
    //------Last Checked------//
    // - Jan 13, 2005
    TempoMarker tempoMarker;
    TEST(wxT("SetDescription - NULL"),
        (!tempoMarker.SetDescription(NULL))
    );
    TEST(wxT("SetDescription"), 
        (tempoMarker.SetDescription(wxT("Test"))) &&
        (tempoMarker.GetDescription() == wxT("Test"))
    );
    return (true);
}
