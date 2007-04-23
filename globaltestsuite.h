/////////////////////////////////////////////////////////////////////////////
// Name:            globaltestsuite.h
// Purpose:         Performs unit testing on global functions
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 30, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __GLOBALTESTSUITE_H__
#define __GLOBALTESTSUITE_H__

/// Performs unit testing on global functions
class GlobalTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(GlobalTestSuite)
    
public:
    // Constructor/Destructor
    GlobalTestSuite();
    ~GlobalTestSuite();

    // Overrides    
    size_t GetTestCount() const;
    bool RunTestCases();
    
    // Test Cases
private:
    bool TestCasewxExtractSubString();
    bool TestCasewxArabicToRoman();
};   
#endif
