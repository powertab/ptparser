/////////////////////////////////////////////////////////////////////////////
// Name:            rehearsalsigntestsuite.h
// Purpose:         Performs unit testing on the RehearsalSign class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __REHEARSALSIGNTESTSUITE_H__
#define __REHEARSALSIGNTESTSUITE_H__

/// Performs unit testing on the RehearsalSign class
class RehearsalSignTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(RehearsalSignTestSuite)
    
// Constructor/Destructor
public:
    RehearsalSignTestSuite();
    ~RehearsalSignTestSuite();
    
// Overrides
    size_t GetTestCount() const;
    bool RunTestCases();
    
// Test Cases
private:
    bool TestCaseConstructor();
    bool TestCaseCreation();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCaseLetter();
    bool TestCaseDescription();
    bool TestCaseOperations();
};
#endif
