/////////////////////////////////////////////////////////////////////////////
// Name:            alternateendingtestsuite.h
// Purpose:         Performs unit testing on the AlternateEnding class 
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 4, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __ALTERNATEENDINGTESTSUITE_H__
#define __ALTERNATEENDINGTESTSUITE_H__

/// Performs unit testing on the AlternateEnding class
class AlternateEndingTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(AlternateEndingTestSuite)

// Constructor/Destructor
public:
    AlternateEndingTestSuite();
    ~AlternateEndingTestSuite();

// Overrides
    size_t GetTestCount() const;
    bool RunTestCases();
    
// Test Case Functions
private:
    bool TestCaseConstructor();
    bool TestCaseCreation();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCaseNumbers();
    bool TestCaseDaCapo();
    bool TestCaseDalSegno();
    bool TestCaseDalSegnoSegno();
    bool TestCaseText();
};   
#endif
