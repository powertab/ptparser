/////////////////////////////////////////////////////////////////////////////
// Name:            systemsymboltestsuite.h
// Purpose:         Performs unit testing on the SystemSymbol class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 13, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __SYSTEMSYMBOLTESTSUITE_H__
#define __SYSTEMSYMBOLTESTSUITE_H__

/// Performs unit testing on the SystemSymbol class
class SystemSymbolTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(SystemSymbolTestSuite)

// Constructor/Destructor
public:
    SystemSymbolTestSuite();
    ~SystemSymbolTestSuite();

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
    bool TestCasePosition();
    bool TestCaseData();
};   
#endif
