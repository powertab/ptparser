/////////////////////////////////////////////////////////////////////////////
// Name:            timesignaturetestsuite.h
// Purpose:         Performs unit testing on the TimeSignature class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 13, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __TIMESIGNATURETESTSUITE_H__
#define __TIMESIGNATURETESTSUITE_H__

/// Performs unit testing on the TimeSignature class
class TimeSignatureTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(TimeSignatureTestSuite)
    
public:
    // Constructor/Destructor
    TimeSignatureTestSuite();
    ~TimeSignatureTestSuite();
    
    // Overrides
    size_t GetTestCount() const;
    bool RunTestCases();
    
    // Test Cases
private:
    bool TestCaseConstructor();
    bool TestCaseCreation();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCaseMeter();
    bool TestCaseBeatsPerMeasure();
    bool TestCaseBeatAmount();
    bool TestCaseBeamingPattern();
    bool TestCaseShow();
    bool TestCasePulses();
    bool TestCaseFlag();
};   
#endif
