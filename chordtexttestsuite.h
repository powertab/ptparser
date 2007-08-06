/////////////////////////////////////////////////////////////////////////////
// Name:            chordtexttestsuite.h
// Purpose:         Performs unit testing on the ChordText class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 3, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __CHORDTEXTTESTSUITE_H__
#define __CHORDTEXTTESTSUITE_H__

/// Performs unit testing on the ChordText class
class ChordTextTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(ChordTextTestSuite)
    
// Constructor/Destructor
public:
    ChordTextTestSuite();
    ~ChordTextTestSuite();

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
    bool TestCaseChordName();
};   
#endif
