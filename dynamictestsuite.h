/////////////////////////////////////////////////////////////////////////////
// Name:            dynamictestsuite.h
// Purpose:         Performs unit testing on the Dynamic class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMICTESTSUITE_H__
#define __DYNAMICTESTSUITE_H__

/// Performs unit testing on the Dynamic class
class DynamicTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(DynamicTestSuite)

// Constructor/Destructor
public:
    DynamicTestSuite();
    ~DynamicTestSuite();

// Overrides
    size_t GetTestCount() const;
    bool RunTestCases();
    
// Test Cases
private:
    bool TestCaseConstructor();
    bool TestCaseCreation();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCaseSystem();
    bool TestCaseStaff();
    bool TestCasePosition();
    bool TestCaseVolume();
};   
#endif
