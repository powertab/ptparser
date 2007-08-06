/////////////////////////////////////////////////////////////////////////////
// Name:            systemtestsuite.h
// Purpose:         Performs unit testing on the System class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 5, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __SYSTEMTESTSUITE_H__
#define __SYSTEMTESTSUITE_H__

/// Performs unit testing on the System class
class SystemTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(SystemTestSuite)

// Constructor/Destructor
public:
    SystemTestSuite();
    ~SystemTestSuite();

// Overrides    
    size_t GetTestCount() const;
    bool RunTestCases();
    
// Test Cases
private:
    bool TestCaseConstructor();
    bool TestCaseCreation();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCaseDirectionArray();
    bool TestCaseChordTextArray();
    bool TestCaseRhythmSlashArray();
    bool TestCaseStaffArray();
    bool TestCaseBarlineArray();    
};   
#endif
