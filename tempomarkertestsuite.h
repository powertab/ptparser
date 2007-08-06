/////////////////////////////////////////////////////////////////////////////
// Name:            tempomarkertestsuite.h
// Purpose:         Performs unit testing on the TempoMarker class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __TEMPOMARKERTESTSUITE_H__
#define __TEMPOMARKERTESTSUITE_H__

/// Performs unit testing on the TempoMarker class
class TempoMarkerTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(TempoMarkerTestSuite)

// Constructor/Destructor
public:
    TempoMarkerTestSuite();
    ~TempoMarkerTestSuite();
    
// Overrides
    size_t GetTestCount() const;
    bool RunTestCases();
    
// Test Cases
private:
    bool TestCaseConstructor();
    bool TestCaseCreation();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCaseType();
    bool TestCaseStandardMarker();
    bool TestCaseListesso();
    bool TestCaseAlterationOfPace();
    bool TestCaseBeatType();
    bool TestCaseListessoBeatType();
    bool TestCaseTripletFeel();
    bool TestCaseBeatsPerMinute();
    bool TestCaseDescription();
};   
#endif
