/////////////////////////////////////////////////////////////////////////////
// Name:            testsuite.cpp
// Purpose:         Helper class to perform unit testing on classes
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 2, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "testsuite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Default Constants
const bool         TestSuite::DEFAULT_EXECUTE      = false;               ///< Default value for the execute member variable
const size_t       TestSuite::DEFAULT_PASSED       = 0;                   ///< Default value for the execute member variable
const size_t       TestSuite::DEFAULT_FAILED       = 0;                   ///< Default value for the execute member variable

IMPLEMENT_ABSTRACT_CLASS(TestSuite, wxObject)

// TODO: add copy constructor + assignment operator

// Constructor/Destructor
/// Default Constructor
TestSuite::TestSuite() :
    m_execute(DEFAULT_EXECUTE), m_passed(DEFAULT_PASSED), m_failed(DEFAULT_FAILED), m_testSuiteCallback(NULL), m_clientData(NULL)
{
    //------Last Verified------//
    // - Dec 2, 2004
}

/// Destructor
TestSuite::~TestSuite()
{
    //------Last Verified------//
    // - Dec 2, 2004
}

// Name Functions
/// Gets the name of the test suite, which by default is the class name.
wxString TestSuite::GetName() const
{
    //------Last Checked------//
    // - Apr 22, 2007
    wxClassInfo* classInfo = GetClassInfo();
    wxCHECK(classInfo != NULL, wxT(""));
    return (classInfo->GetClassName());
}

/// Executes all the tests in a TestSuite object
/// @param testSuiteCallback Callback function that will receive the results of each test in the test suite
/// @param clientData User defined data (optional)
bool TestSuite::Run(TESTSUITECALLBACK testSuiteCallback, void* clientData)
{
    //------Last Verified------//
    // - Dec 2, 2004
    wxCHECK(testSuiteCallback != NULL, false);
    
    // Update the local variables
    m_testSuiteCallback = testSuiteCallback;
    m_clientData = clientData;
    
    // Reset the test suite stats
    Reset();
    
    return (this->RunTestCases());
}

/// Passes the results of a test to the test suite callback function
/// @param record Indicates whether or note the results of the test should be recorded to the results tree ctrl if the test was successful
/// @param startTime The time when the test was started
/// @param testName Name of the test
/// @param success Indicates the success/failure of the test
/// @param fileName Name of the file where the test occurred
/// @param lineNumber Line number in the file where the test occurred
bool TestSuite::Test(bool record, wxLongLong startTime, const wxChar* testName, bool success, char* fileName, size_t lineNumber)
{
    //------Last Checked------//
    // - Dec 2, 2004
           
    // Calculate the time to execute the test (in seconds)
    wxLongLong span = ::wxGetLocalTimeMillis() - startTime;
    double executionTime = ((double)span.ToLong()) / 1000.0;

    // If the test suite isn't being executed, bail out
    if (!IsExecuted())
        return (false);

    // Update the success or failure of the test
    if (success)
        m_passed++;
    else
        m_failed++;

    wxCHECK(testName != NULL, false);
    wxCHECK(fileName != NULL, false);
    wxCHECK(m_testSuiteCallback != NULL, false);

    // Create a temp string used for the filename (since it's ANSI and we want it this to work on Unicode builds)
    wxString tempFileName(fileName);

    // Send the results of the test to the callback
    return (m_testSuiteCallback(this, testName, success, tempFileName, lineNumber, record, executionTime, m_clientData));
}
