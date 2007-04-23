/////////////////////////////////////////////////////////////////////////////
// Name:            guitartestsuite.h
// Purpose:         Performs unit testing on the Guitar class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 8, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __GUITARTESTSUITE_H__
#define __GUITARTESTSUITE_H__

/// Performs unit testing on the Guitar class
class GuitarTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(GuitarTestSuite)
    
public:
    // Constructor/Destructor
    GuitarTestSuite();
    ~GuitarTestSuite();

    // Overrides    
    size_t GetTestCount() const;
    bool RunTestCases();
    
    // Test Cases
private:
    bool TestCaseConstructor();
    bool TestCaseCreation();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCaseNumber();
    bool TestCasePreset();
    bool TestCaseInitialVolume();
    bool TestCaseDescription();
    bool TestCaseReverb();
    bool TestCaseChorus();
    bool TestCaseTremolo();
    bool TestCasePhaser();
    bool TestCaseCapo();
    bool TestCaseTuning();
};   
#endif
