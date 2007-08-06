/////////////////////////////////////////////////////////////////////////////
// Name:            powertabobjecttestsuite.h
// Purpose:         Performs unit testing on the PowerTabObject class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 24, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __POWERTABOBJECTTESTSUITE_H__
#define __POWERTABOBJECTTESTSUITE_H__

/// Performs unit testing on the PowerTabObject class
class PowerTabObjectTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(PowerTabObjectTestSuite)
    
// Constructor/Destructor
public:
    PowerTabObjectTestSuite();
    ~PowerTabObjectTestSuite();
    
// Overrides
    size_t GetTestCount() const;
    bool RunTestCases();
    
// Test Cases
private:
    bool TestCaseCreateObject();
    bool TestCaseMFCClassInformation();
};
#endif
