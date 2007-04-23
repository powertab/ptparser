/////////////////////////////////////////////////////////////////////////////
// Name:            tuningtestsuite.h
// Purpose:         Performs unit testing on the Tuning class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 9, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __TUNINGTESTSUITE_H__
#define __TUNINGTESTSUITE_H__

/// Performs unit testing on the Tuning class
class TuningTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(TuningTestSuite)
    
public:
    // Constructor/Destructor
    TuningTestSuite();
    ~TuningTestSuite();
    
    // Overrides
    size_t GetTestCount() const;
    bool RunTestCases();
    
    // Test Cases
private:
    bool TestCaseConstructor();
    bool TestCaseCreation();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCaseTuning();
    bool TestCaseName();
    bool TestCaseMusicNotationOffset();
    bool TestCaseSharps();
    bool TestCaseString();
    bool TestCaseNote();
    bool TestCaseOperations();
};   
#endif
