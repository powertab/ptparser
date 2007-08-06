/////////////////////////////////////////////////////////////////////////////
// Name:            scoretestsuite.h
// Purpose:         Performs unit testing on the Score class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 5, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __SCORETESTSUITE_H__
#define __SCORETESTSUITE_H__

/// Performs unit testing on the Score class
class ScoreTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(ScoreTestSuite)

// Constructor/Destructor
public:
    ScoreTestSuite();
    ~ScoreTestSuite();

// Overrides    
    size_t GetTestCount() const;
    bool RunTestCases();
    
// Test Cases
private:
    bool TestCaseConstructor();
    bool TestCaseCreation();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCaseGuitarArray();
    bool TestCaseChordDiagramArray();
    bool TestCaseFloatingTextArray();
    bool TestCaseGuitarInArray();
    bool TestCaseTempoMarkerArray();
    bool TestCaseDynamicArray();
    bool TestCaseAlternateEndingArray();
    bool TestCaseSystemArray();
};   
#endif
