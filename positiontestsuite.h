/////////////////////////////////////////////////////////////////////////////
// Name:            positiontestsuite.h
// Purpose:         Performs unit testing on the Position class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 5, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __POSITIONTESTSUITE_H__
#define __POSITIONTESTSUITE_H__

/// Performs unit testing on the Position class
class PositionTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(PositionTestSuite)
    
public:
    // Constructor/Destructor
    PositionTestSuite();
    ~PositionTestSuite();

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
    bool TestCaseIrregularGrouping();
    bool TestCaseBeaming();
    bool TestCaseDotted();
    bool TestCaseRest();
    bool TestCaseVibrato();
    bool TestCaseArpeggio();
    bool TestCasePickStroke();
    bool TestCaseStaccato();
    bool TestCaseAccent();
    bool TestCaseTremoloPicking();
    bool TestCasePalmMuting();
    bool TestCaseTap();
    bool TestCaseGraceNotes();
    bool TestCaseTripletFeel();
    bool TestCaseLetRing();
    bool TestCaseFermata();
    bool TestCaseVolumeSwell();
    bool TestCaseTremoloBar();
    bool TestCaseMultibarRest();
    bool TestCaseComplexSymbol();
    bool TestCaseNoteArray();
};   
#endif
