/////////////////////////////////////////////////////////////////////////////
// Name:            directiontestsuite.h
// Purpose:         Performs unit testing on the Direction class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 9, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __DIRECTIONTESTSUITE_H__
#define __DIRECTIONTESTSUITE_H__

/// Performs unit testing on the Direction class
class DirectionTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(DirectionTestSuite)
    
// Constructor/Destructor
public:
    DirectionTestSuite();
    ~DirectionTestSuite();

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
    bool TestCaseSymbolType();
    bool TestCaseActiveSymbol();
    bool TestCaseRepeatNumber();
    bool TestCaseSymbolArray();
    bool TestCaseOperations();
};   
#endif
