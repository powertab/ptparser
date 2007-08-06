/////////////////////////////////////////////////////////////////////////////
// Name:            oldtimesignaturetestsuite.h
// Purpose:         Performs unit testing on the OldTimeSignature class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __OLDTIMESIGNATURETESTSUITE_H__
#define __OLDTIMESIGNATURETESTSUITE_H__

/// Performs unit testing on the OldTimeSignature class
class OldTimeSignatureTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(OldTimeSignatureTestSuite)

// Constructor/Destructor
public:
    OldTimeSignatureTestSuite();
    ~OldTimeSignatureTestSuite();

// Overrides    
    size_t GetTestCount() const;
    bool RunTestCases();
    
// Test Cases
private:
    bool TestCaseConstructor();
    bool TestCaseConstruction();
    bool TestCaseOperator();
};   
#endif
