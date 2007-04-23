/////////////////////////////////////////////////////////////////////////////
// Name:            keysignaturetestsuite.h
// Purpose:         Performs unit testing on the KeySignature class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __KEYSIGNATURETESTSUITE_H__
#define __KEYSIGNATURETESTSUITE_H__

/// Performs unit testing on the KeySignature class
class KeySignatureTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(KeySignatureTestSuite)
    
public:
    // Constructor/Destructor
    KeySignatureTestSuite();
    ~KeySignatureTestSuite();
    
    // Overrides
    size_t GetTestCount() const;
    bool RunTestCases();
    
    // Test Cases
private:
    bool TestCaseConstructor();
    bool TestCaseCreation();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCaseKey();
    bool TestCaseKeyType();
    bool TestCaseKeyAccidentals();
    bool TestCaseShow();
    bool TestCaseCancellation();
    bool TestCaseFlag();
};   
#endif
