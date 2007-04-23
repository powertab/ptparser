/////////////////////////////////////////////////////////////////////////////
// Name:            barlinetestsuite.h
// Purpose:         Performs unit testing on the Barline class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 4, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __BARLINETESTSUITE_H__
#define __BARLINETESTSUITE_H__

/// Performs unit testing on the Barline class
class BarlineTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(BarlineTestSuite)
    
public:
    // Constructor/Destructor
    BarlineTestSuite();
    ~BarlineTestSuite();

    // Overrides    
    size_t GetTestCount() const;
    bool RunTestCases();
    
    // Test Cases
private:
    bool TestCaseConstructor();
    bool TestCaseCreation();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCasePosition();
    bool TestCaseBarlineData();
    bool TestCaseType();
    bool TestCaseRepeatCount();
    bool TestCaseKeySignature();
    bool TestCaseTimeSignature();
    bool TestCaseRehearsalSign();
};   
#endif
