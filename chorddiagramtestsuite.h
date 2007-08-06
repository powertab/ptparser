/////////////////////////////////////////////////////////////////////////////
// Name:            chorddiagramtestsuite.h
// Purpose:         Performs unit testing on the ChordDiagram class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 12, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __CHORDDIAGRAMTESTSUITE_H__
#define __CHORDDIAGRAMTESTSUITE_H__

/// Performs unit testing on the ChordDiagram class
class ChordDiagramTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(ChordDiagramTestSuite)
    
// Constructor/Destructor
public:
    ChordDiagramTestSuite();
    ~ChordDiagramTestSuite();

// Overrides
    size_t GetTestCount() const;
    bool RunTestCases();
    
// Test Cases
private:
    bool TestCaseConstructor();
    bool TestCaseCreation();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCaseChordDiagram();
    bool TestCaseChordName();
    bool TestCaseTopFret();
    bool TestCaseString();
    bool TestCaseFretNumber();
    bool TestCaseVoicing();
    bool TestCaseOperations();
};   
#endif
