/////////////////////////////////////////////////////////////////////////////
// Name:            rhythmslashtestsuite.h
// Purpose:         Performs unit testing on the RhythmSlash class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 5, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __RHYTHMSLASHTESTSUITE_H__
#define __RHYTHMSLASHTESTSUITE_H__

/// Performs unit testing on the RhythmSlash class
class RhythmSlashTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(RhythmSlashTestSuite)
    
public:
    // Constructor/Destructor
    RhythmSlashTestSuite();
    ~RhythmSlashTestSuite();

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
    bool TestCaseDurationType();
    bool TestCaseBeaming();
    bool TestCaseTriplet();
    bool TestCaseDotted();
    bool TestCaseRest();
    bool TestCaseTied();
    bool TestCaseMuted();
    bool TestCaseStaccato();
    bool TestCasePickStroke();
    bool TestCaseArpeggio();
    bool TestCaseTripletFeel();
    bool TestCaseAccent();
    bool TestCaseSlideInto();
    bool TestCaseSlideOutOf();
    bool TestCaseSingleNoteData();
};   
#endif
