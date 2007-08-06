/////////////////////////////////////////////////////////////////////////////
// Name:            fontsettingtestsuite.h
// Purpose:         Performs unit testing on the FontSetting class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 7, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __FONTSETTINGTESTSUITE_H__
#define __FONTSETTINGTESTSUITE_H__

/// Performs unit testing on the FontSetting class
class FontSettingTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(FontSettingTestSuite)
    
// Constructor/Destructor
public:
    FontSettingTestSuite();
    ~FontSettingTestSuite();
    
// Overrides
    size_t GetTestCount() const;
    bool RunTestCases();
    
// Test Case Functions
private:
    bool TestCaseConstructor();
    bool TestCaseCreation();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCaseSetFontSetting();
    bool TestCaseSetFontSettingFromString();
    bool TestCaseFaceName();
    bool TestCasePointSize();
    bool TestCaseWeight();
    bool TestCaseItalic();
    bool TestCaseUnderline();
    bool TestCaseStrikeOut();
    bool TestCaseColor();
};   
#endif
