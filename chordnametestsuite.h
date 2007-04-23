/////////////////////////////////////////////////////////////////////////////
// Name:            chordnametestsuite.h
// Purpose:         Performs unit testing on the ChordName class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 4, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __CHORDNAMETESTSUITE_H__
#define __CHORDNAMETESTSUITE_H__

/// Performs unit testing on the ChordName class
class ChordNameTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(ChordNameTestSuite)
    
public:
    // Constructor/Destructor
    ChordNameTestSuite();
    ~ChordNameTestSuite();

    // Overrides    
    size_t GetTestCount() const;
    bool RunTestCases();
    
    // Test Cases
private:
    bool TestCaseConstructor();
    bool TestCaseCreation();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCaseTonic();
    bool TestCaseBassNote();
    bool TestCaseFormula();
    bool TestCaseBrackets();
    bool TestCaseNoChord();
    bool TestCaseFormulaFlags();
    bool TestCaseFormulaModifications();
    bool TestCaseFretPosition();
    bool TestCaseType();
};   
#endif
