/////////////////////////////////////////////////////////////////////////////
// Name:            floatingtexttestsuite.h
// Purpose:         Performs unit testing on the FloatingText class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 5, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __FLOATINGTEXTTESTSUITE_H__
#define __FLOATINGTEXTTESTSUITE_H__

/// Performs unit testing on the FloatingText class
class FloatingTextTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(FloatingTextTestSuite)
    
// Constructor/Destructor
public:
    FloatingTextTestSuite();
    ~FloatingTextTestSuite();
    
// Overrides
    size_t GetTestCount() const;
    bool RunTestCases();

// Test Case Functions
private:
    bool TestCaseConstructor();
    bool TestCaseCreation();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCaseText();
    bool TestCaseRect();
    bool TestCaseFlags();
    bool TestCaseAlignment();
    bool TestCaseBorder();
    bool TestCaseFontSetting();
};   
#endif
