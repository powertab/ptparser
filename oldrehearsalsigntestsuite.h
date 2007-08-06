/////////////////////////////////////////////////////////////////////////////
// Name:            oldrehearsalsigntestsuite.h
// Purpose:         Performs unit testing on the OldRehearsalSign class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __OLDREHEARSALSIGNTESTSUITE_H__
#define __OLDREHEARSALSIGNTESTSUITE_H__

/// Performs unit testing on the OldRehearsalSign class
class OldRehearsalSignTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(OldRehearsalSignTestSuite)

// Constructor/Destructor
public:
    OldRehearsalSignTestSuite();
    ~OldRehearsalSignTestSuite();

// Overrides    
    size_t GetTestCount() const;
    bool RunTestCases();
    
// Test Cases
private:
    bool TestCaseConstructor();
    bool TestCaseConstruction();
    bool TestCaseOperator();
};   
#endif
