/////////////////////////////////////////////////////////////////////////////
// Name:            generalmiditestsuite.h
// Purpose:         Performs unit testing on the General MIDI functions
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 9, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __GENERALMIDITESTSUITE_H__
#define __GENERALMIDITESTSUITE_H__

/// Performs unit testing on the General MIDI functions
class GeneralMidiTestSuite : 
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(GeneralMidiTestSuite)
    
// Constructor/Destructor
public:
    GeneralMidiTestSuite();
    ~GeneralMidiTestSuite();
    
// Overrides
    size_t GetTestCount() const;
    bool RunTestCases();
    
// Test Case Functions
private:
    bool TestCaseMidiChannel();
    bool TestCaseMidiNote();
    bool TestCaseMidiPreset();
    bool TestCaseMidiPercussionPreset();
};

#endif
