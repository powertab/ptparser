/////////////////////////////////////////////////////////////////////////////
// Name:            notetestsuite.h
// Purpose:         Performs unit testing on the Note class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 5, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __NOTETESTSUITE_H__
#define __NOTETESTSUITE_H__

/// Performs unit testing on the Note class
class NoteTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(NoteTestSuite)
    
public:
    // Constructor/Destructor
    NoteTestSuite();
    ~NoteTestSuite();

    // Overrides    
    size_t GetTestCount() const;
    bool RunTestCases();
    
    // Test Cases
private:
    bool TestCaseConstructor();
    bool TestCaseCreation();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCaseString();
    bool TestCaseFretNumber();
    bool TestCaseTied();
    bool TestCaseMuted();
    bool TestCaseTieWrap();
    bool TestCaseHammerOn();
    bool TestCaseHammerOnFromNowhere();
    bool TestCasePullOff();
    bool TestCasePullOffToNowhere();
    bool TestCaseNaturalHarmonic();
    bool TestCaseGhostNote();
    bool TestCaseOctave8va();
    bool TestCaseOctave15ma();
    bool TestCaseOctave8mb();
    bool TestCaseOctave15mb();
    bool TestCaseSimpleFlags();
    bool TestCaseSlide();
    bool TestCaseBend();
    bool TestCaseTappedHarmonic();
    bool TestCaseTrill();
    bool TestCaseArtificialHarmonic();
    bool TestCaseComplexSymbol();
};   
#endif
