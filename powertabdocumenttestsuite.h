/////////////////////////////////////////////////////////////////////////////
// Name:            powertabdocumenttestsuite.h
// Purpose:         Performs unit testing on the PowerTabDocument class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 27, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __POWERTABDOCUMENTTESTSUITE_H__
#define __POWERTABDOCUMENTTESTSUITE_H__

/// Performs unit testing on the PowerTabDocument class
class PowerTabDocumentTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(PowerTabDocumentTestSuite)

// Constructor/Destructor
public:
    PowerTabDocumentTestSuite();
    ~PowerTabDocumentTestSuite();

// Overrides    
    size_t GetTestCount() const;
    bool RunTestCases();
    
// Test Cases
private:
    bool TestCaseConstructor();
    bool TestCaseScore();
    bool TestCaseChordNameFontSetting();
    bool TestCaseSetTablatureNumbersFontSetting();
    bool TestCaseTablatureStaffLineSpacing();
    bool TestCaseFadeIn();
    bool TestCaseFadeOut();
};   
#endif
