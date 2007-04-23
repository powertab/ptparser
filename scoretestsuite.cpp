/////////////////////////////////////////////////////////////////////////////
// Name:            scoretestsuite.cpp
// Purpose:         Performs unit testing on the Score class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 5, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "scoretestsuite.h"

#include "score.h"
#include "powertabfileheader.h"         // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(ScoreTestSuite, TestSuite)

/// Default Constructor
ScoreTestSuite::ScoreTestSuite()
{
    //------Last Checked------//
    // - Jan 3, 2005    
}

/// Destructor
ScoreTestSuite::~ScoreTestSuite()
{
    //------Last Checked------//
    // - Jan 3, 2005
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t ScoreTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Jan 3, 2005
    return (40);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool ScoreTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Jan 6, 2005
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseCreation())
        return (false);
    if (!TestCaseOperator())
        return (false);
    if (!TestCaseSerialize())
        return (false);
    if (!TestCaseGuitarArray())
        return (false);
    if (!TestCaseChordDiagramArray())
        return (false);
    if (!TestCaseFloatingTextArray())
        return (false);
    if (!TestCaseGuitarInArray())
        return (false);
    if (!TestCaseTempoMarkerArray())
        return (false);
    if (!TestCaseDynamicArray())
        return (false);
    if (!TestCaseAlternateEndingArray())
        return (false);
    if (!TestCaseSystemArray())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool ScoreTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 6, 2005
    
    // TEST CASE: Default Constructor
    {
        Score score;        
        TEST(wxT("Default Constructor"), 
            (score.GetGuitarCount() == 0) &&
            (score.GetChordDiagramCount() == 0) &&
            (score.GetFloatingTextCount() == 0) &&
            (score.GetGuitarInCount() == 0) &&
            (score.GetTempoMarkerCount() == 0) &&
            (score.GetDynamicCount() == 0) &&
            (score.GetAlternateEndingCount() == 0) &&
            (score.GetSystemCount() == 0)
        );
    }
    
    // TEST CASE: Copy Constructor
    {
        Score score;
        score.m_guitarArray.Add(new Guitar);
        score.m_chordDiagramArray.Add(new ChordDiagram);
        score.m_floatingTextArray.Add(new FloatingText);
        score.m_guitarInArray.Add(new GuitarIn);
        score.m_tempoMarkerArray.Add(new TempoMarker);
        score.m_dynamicArray.Add(new Dynamic);
        score.m_alternateEndingArray.Add(new AlternateEnding);
        score.m_systemArray.Add(new System);
        
        Score score2(score);
        TEST(wxT("Copy Constructor"), score2 == score);
    }
    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool ScoreTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 6, 2005
    Score score;
    score.m_guitarArray.Add(new Guitar);
    score.m_chordDiagramArray.Add(new ChordDiagram);
    score.m_floatingTextArray.Add(new FloatingText);
    score.m_guitarInArray.Add(new GuitarIn);
    score.m_tempoMarkerArray.Add(new TempoMarker);
    score.m_dynamicArray.Add(new Dynamic);
    score.m_alternateEndingArray.Add(new AlternateEnding);
    score.m_systemArray.Add(new System);
        
    Score* clone = (Score*)score.CloneObject();
    TEST(wxT("CloneObject"), 
        (*clone == score)
    );
    
    delete clone;
        
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool ScoreTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 6, 2005
    
    // TEST CASE: Assignment Operator
    {
        Score score;
        score.m_guitarArray.Add(new Guitar);
        score.m_chordDiagramArray.Add(new ChordDiagram);
        score.m_floatingTextArray.Add(new FloatingText);
        score.m_guitarInArray.Add(new GuitarIn);
        score.m_tempoMarkerArray.Add(new TempoMarker);
        score.m_dynamicArray.Add(new Dynamic);
        score.m_alternateEndingArray.Add(new AlternateEnding);
        score.m_systemArray.Add(new System);
        
        Score score2 = score;
        TEST(wxT("Operator="), score2 == score);
        
        // TEST CASE: Operator= (self-assignment)
        score = score;
        TEST(wxT("Operator= (self-assignment)"),
            (score == score)
        );
    }
    
    // TEST CASE: Equality Operator
    {
        Score score;
        Score score2;
        
        Score score3;
        score3.m_guitarArray.Add(new Guitar(2));
        
        Score score4;
        score4.m_chordDiagramArray.Add(new ChordDiagram(ChordName(), 2, 1, 2, 3));
        
        Score score5;
        score5.m_floatingTextArray.Add(new FloatingText(wxT("Test"), wxRect(1,2,3,4), 0, FontSetting()));
        
        Score score6;
        score6.m_guitarInArray.Add(new GuitarIn(1,2,3,4,2));
        
        Score score7;
        score7.m_tempoMarkerArray.Add(new TempoMarker(1,2, 1, 1, wxT("Test")));
        
        Score score8;
        score8.m_dynamicArray.Add(new Dynamic(1,2,3,1,1));
        
        Score score9;
        score9.m_alternateEndingArray.Add(new AlternateEnding(1,2,12));
        
        Score score10;
        score10.m_systemArray.Add(new System);
        
        TEST(wxT("Operator== - score == score"), score == score2);
        TEST(wxT("Operator== - score != score"), !(score == score3));
        TEST(wxT("Operator== - score != score 2"), !(score == score4));
        TEST(wxT("Operator== - score != score 3"), !(score == score5));
        TEST(wxT("Operator== - score != score 4"), !(score == score6));
        TEST(wxT("Operator== - score != score 5"), !(score == score7));
        TEST(wxT("Operator== - score != score 6"), !(score == score8));
        TEST(wxT("Operator== - score != score 7"), !(score == score9));
        TEST(wxT("Operator== - score != score 8"), !(score == score10));
    }
    
    // TEST CASE: Inequality Operator
    {
        Score score;
        Score score2;
        
        Score score3;
        score3.m_guitarArray.Add(new Guitar(2));
        
        Score score4;
        score4.m_chordDiagramArray.Add(new ChordDiagram(ChordName(), 2, 1, 2, 3));
        
        Score score5;
        score5.m_floatingTextArray.Add(new FloatingText(wxT("Test"), wxRect(1,2,3,4), 0, FontSetting()));
        
        Score score6;
        score6.m_guitarInArray.Add(new GuitarIn(1,2,3,4,2));
        
        Score score7;
        score7.m_tempoMarkerArray.Add(new TempoMarker(1,2, 1, 120, wxT("Test")));
        
        Score score8;
        score8.m_dynamicArray.Add(new Dynamic(1,2,3,1,1));
        
        Score score9;
        score9.m_alternateEndingArray.Add(new AlternateEnding(1,2,12));
        
        Score score10;
        score10.m_systemArray.Add(new System);
        
        TEST(wxT("Operator!= - score == score"), !(score != score2));
        TEST(wxT("Operator!= - score != score"), (score != score3));
        TEST(wxT("Operator!= - score != score 2"), (score != score4));
        TEST(wxT("Operator!= - score != score 3"), (score != score5));
        TEST(wxT("Operator!= - score != score 4"), (score != score6));
        TEST(wxT("Operator!= - score != score 5"), (score != score7));
        TEST(wxT("Operator!= - score != score 6"), (score != score8));
        TEST(wxT("Operator!= - score != score 7"), (score != score9));
        TEST(wxT("Operator!= - score != score 8"), (score != score10));
    }
    
    return (true);
}

/// Tests the Serialization Functions
/// @return True if all tests were executed, false if not
bool ScoreTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Jan 6, 2005
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    Score scoreOut;
    wxUint32 i = 0;
    for (; i < 3; i++)
    {
        scoreOut.m_guitarArray.Add(new Guitar);
        scoreOut.m_chordDiagramArray.Add(new ChordDiagram);
        scoreOut.m_floatingTextArray.Add(new FloatingText);
        scoreOut.m_guitarInArray.Add(new GuitarIn);
        scoreOut.m_tempoMarkerArray.Add(new TempoMarker);
        scoreOut.m_dynamicArray.Add(new Dynamic);
        scoreOut.m_alternateEndingArray.Add(new AlternateEnding);
        scoreOut.m_systemArray.Add(new System);
    }
    scoreOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        Score scoreIn;
        scoreIn.Deserialize(streamIn, PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((scoreIn == scoreOut)
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the Guitar Array Functions
/// @return True if all tests were executed, false if not
bool ScoreTestSuite::TestCaseGuitarArray()
{
    //------Last Checked------//
    // - Jan 6, 2005
    Score score;
    TEST(wxT("IsValidGuitarIndex - false"), !score.IsValidGuitarIndex(0));
    TEST(wxT("GetGuitar - invalid index"), (score.GetGuitar(0) == NULL));
    return (true);
}

/// Tests the Chord Diagram Array Functions
/// @return True if all tests were executed, false if not
bool ScoreTestSuite::TestCaseChordDiagramArray()
{
    //------Last Checked------//
    // - Jan 6, 2005
    Score score;
    TEST(wxT("IsValidChordDiagramIndex - false"), !score.IsValidChordDiagramIndex(0));
    TEST(wxT("GetChordDiagram - invalid index"), (score.GetChordDiagram(0) == NULL));
    return (true);
}

/// Tests the Floating Text Array Functions
/// @return True if all tests were executed, false if not
bool ScoreTestSuite::TestCaseFloatingTextArray()
{
    //------Last Checked------//
    // - Jan 6, 2005
    Score score;
    TEST(wxT("IsValidFloatingTextIndex - false"), !score.IsValidFloatingTextIndex(0));
    TEST(wxT("GetFloatingText - invalid index"), (score.GetFloatingText(0) == NULL));
    return (true);
}

/// Tests the Guitar In Array Functions
/// @return True if all tests were executed, false if not
bool ScoreTestSuite::TestCaseGuitarInArray()
{
    //------Last Checked------//
    // - Jan 6, 2005
    Score score;
    TEST(wxT("IsValidGuitarInIndex - false"), !score.IsValidGuitarInIndex(0));
    TEST(wxT("GetGuitarIn - invalid index"), (score.GetGuitarIn(0) == NULL));
    return (true);
}

/// Tests the Tempo Marker Array Functions
/// @return True if all tests were executed, false if not
bool ScoreTestSuite::TestCaseTempoMarkerArray()
{
    //------Last Checked------//
    // - Jan 6, 2005
    Score score;
    TEST(wxT("IsValidTempoMarkerIndex - false"), !score.IsValidTempoMarkerIndex(0));
    TEST(wxT("GetTempoMarker - invalid index"), (score.GetTempoMarker(0) == NULL));
    return (true);
}

/// Tests the Dynamic Array Functions
/// @return True if all tests were executed, false if not
bool ScoreTestSuite::TestCaseDynamicArray()
{
    //------Last Checked------//
    // - Jan 6, 2005
    Score score;
    TEST(wxT("IsValidDynamicIndex - false"), !score.IsValidDynamicIndex(0));
    TEST(wxT("GetDynamic - invalid index"), (score.GetDynamic(0) == NULL));
    return (true);
}

/// Tests the Alternate Ending Array Functions
/// @return True if all tests were executed, false if not
bool ScoreTestSuite::TestCaseAlternateEndingArray()
{
    //------Last Checked------//
    // - Jan 6, 2005
    Score score;
    TEST(wxT("IsValidAlternateEndingIndex - false"), !score.IsValidAlternateEndingIndex(0));
    TEST(wxT("GetAlternateEnding - invalid index"), (score.GetAlternateEnding(0) == NULL));
    return (true);
}

/// Tests the System Array Functions
/// @return True if all tests were executed, false if not
bool ScoreTestSuite::TestCaseSystemArray()
{
    //------Last Checked------//
    // - Jan 6, 2005
    Score score;
    TEST(wxT("IsValidSystemIndex - false"), !score.IsValidSystemIndex(0));
    TEST(wxT("GetSystem - invalid index"), (score.GetSystem(0) == NULL));
    return (true);
}
