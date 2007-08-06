/////////////////////////////////////////////////////////////////////////////
// Name:            guitarintestsuite.h
// Purpose:         Performs unit testing on the GuitarIn class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __GUITARINTESTSUITE_H__
#define __GUITARINTESTSUITE_H__

/// Performs unit testing on the GuitarIn class
class GuitarInTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(GuitarInTestSuite)
    
// Constructor/Destructor
public:
    GuitarInTestSuite();
    ~GuitarInTestSuite();

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
    bool TestCaseGuitars();
    bool TestCaseOperations();
};   
#endif
