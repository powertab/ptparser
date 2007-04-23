/////////////////////////////////////////////////////////////////////////////
// Name:            testingframework.h
// Purpose:         A framework for performing unit tests on classes
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 2, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __TESTINGFRAMEWORK_H__
#define __TESTINGFRAMEWORK_H__

#include "testsuite.h"

/// A framework for performing unit tests on classes
class TestingFramework : public wxObject
{
    DECLARE_DYNAMIC_CLASS(TestingFramework)
    
protected:
    wxTestSuiteArray m_testSuiteArray;                          ///< Holds a list of test suites that can be tested by the framework
    
public:
    // Constructor/Destructor
    TestingFramework();
    ~TestingFramework();

    // Test Suite Array Functions
    size_t GetTestSuiteCount() const                            {return (m_testSuiteArray.GetCount());}
    bool IsValidTestSuiteIndex(size_t index) const              {return (index < GetTestSuiteCount());}
    bool AddTestSuite(TestSuite* testSuite)                     {wxCHECK(testSuite, false); m_testSuiteArray.Add(testSuite); return (true);}
    TestSuite* GetTestSuite(size_t index) const                 {return ((IsValidTestSuiteIndex(index)) ? m_testSuiteArray[index] : NULL);}
    void SortTestSuitesByName(bool sortAscending = true);
    void DeleteTestSuiteArrayContents();
};

#endif
