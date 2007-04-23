/////////////////////////////////////////////////////////////////////////////
// Name:            stafftestsuite.h
// Purpose:         Performs unit testing on the Staff class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 5, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __STAFFTESTSUITE_H__
#define __STAFFTESTSUITE_H__

/// Performs unit testing on the Staff class
class StaffTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(StaffTestSuite)
    
public:
    // Constructor/Destructor
    StaffTestSuite();
    ~StaffTestSuite();

    // Overrides    
    size_t GetTestCount() const;
    bool RunTestCases();
    
    // Test Cases
private:
    bool TestCaseConstructor();
    bool TestCaseCreation();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCaseClef();
    bool TestCaseTablatureStaffType();
    bool TestCaseStandardNotationStaffAboveSpacing();
    bool TestCaseStandardNotationStaffBelowSpacing();
    bool TestCaseSymbolSpacing();
    bool TestCaseTablatureStaffBelowSpacing();
    bool TestCaseVoice();
    bool TestCasePositionArray();
};   
#endif
