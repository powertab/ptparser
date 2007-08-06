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
    
// Member Variables
protected:
    wxTestSuiteArray m_testSuiteArray;                          ///< Holds a list of test suites that can be tested by the framework
    
// Constructor/Destructor
public:
    TestingFramework();
    ~TestingFramework();

// Test Suite Array Functions
    /// Gets the number of test suites in the framework
    /// @return The number of test suites in the framework
    size_t GetTestSuiteCount() const
        {return (m_testSuiteArray.GetCount());}
    /// Determines if a test suite index is valid
    /// @param index Test suite index to validate
    /// @return True if the index is valid, false if not
    bool IsValidTestSuiteIndex(size_t index) const
        {return (index < GetTestSuiteCount());}
    /// Adds a tests suite to the framework
    /// @param testSuite Pointer to the test suite to add
    /// @return True if the test suite was added, false if not
    bool AddTestSuite(TestSuite* testSuite)
    {
        wxCHECK(testSuite, false);
        m_testSuiteArray.Add(testSuite);
        return (true);
    }
    /// Gets a pointer to a test suite
    /// @param index Zero-based index of the test suite to retrieve
    /// @return A pointer to the test suite, or NULL if the index is invalid
    TestSuite* GetTestSuite(size_t index) const 
    {
        return ((IsValidTestSuiteIndex(index)) ? m_testSuiteArray[index] : NULL);
    }
    void SortTestSuitesByName(bool sortAscending = true);
    void DeleteTestSuiteArrayContents();
};

#endif
