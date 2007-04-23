/////////////////////////////////////////////////////////////////////////////
// Name:            testsuite.h
// Purpose:         Helper class to perform unit testing on classes
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 2, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __TESTSUITE_H__
#define __TESTSUITE_H__

#include "teststream.h"     // Used for serialization testing

// Macros
#define TEST(test, condition)                                   if (!Test(false, ::wxGetLocalTimeMillis(), test, condition, __FILE__, __LINE__)) return (false);
#define TEST_AND_RECORD(time, test, condition)                  if (!Test(true, time, test, condition, __FILE__, __LINE__)) return (false);

class TestSuite;

// Function pointers
typedef bool (*TESTSUITECALLBACK)(TestSuite*, const wxChar*, bool, const wxChar*, size_t, bool, double, void*);

/// Helper class to perform unit testing on classes
class TestSuite : public wxObject
{
    DECLARE_ABSTRACT_CLASS(TestSuite)

// Constants
public:
    // Default constants
    static const bool         DEFAULT_EXECUTE;                  ///< Default value for the execute member variable
    static const size_t       DEFAULT_PASSED;                   ///< Default value for the passed member variable
    static const size_t       DEFAULT_FAILED;                   ///< Default value for the failed member variable
        
protected:
    bool                    m_execute;                          // Indicates whether or not the test suite should be executed by the testing framework
    size_t                  m_passed;                           // Number of tests in the test suite that have passed
    size_t                  m_failed;                           // Number of tests in the test suite that have failed
    TESTSUITECALLBACK       m_testSuiteCallback;                // Callback function that will receive the results of each test in the test suite
    void*                   m_clientData;                       // User defined data

public:
    // Constructor/Destructor
    TestSuite();
    virtual ~TestSuite();

    // Name Functions
    virtual wxString GetName() const;
    wxString GetTestFileName() const                            
        {return (wxString::Format(wxT("%s.testxxx"), GetName().c_str()));}
    
    // Execute Functions
    void SetExecute(bool set = true)                            
        {m_execute = set;}
    bool IsExecuted() const                                     
        {return (m_execute);}

    // Passed Functions
    size_t GetPassed() const                                    
        {return (m_passed);}
    bool HasPassed() const                                      
        {return (HasTests() && (GetPassed() == GetTestCount()));}

    // Failed Functions
    size_t GetFailed() const                                    
        {return (m_failed);}
    bool HasFailed() const                                      
        {return (GetFailed() > 0);}

    // Client Data Functions
    void SetClientData(void* clientData)                        
        {m_clientData = clientData;}
    void* GetClientData() const                                 
        {return (m_clientData);}

    // Test Functions
    size_t GetTestsRun() const                                  
        {return (GetPassed() + GetFailed());}
    virtual size_t GetTestCount() const = 0;
    bool HasTests() const                                       
        {return (GetTestCount() > 0);}

    // Operations   
    bool Run(TESTSUITECALLBACK testSuiteCallback, void* clientData = NULL);
    
protected:
    bool Test(bool record, wxLongLong startTime, const wxChar* testName, bool success, char* fileName, size_t lineNumber);
    virtual bool RunTestCases() = 0;
    void Reset()                                                
        {m_passed = m_failed = 0;}
};

// Array Declarations
WX_DEFINE_ARRAY(TestSuite *, wxTestSuiteArray);

// Comparison Functions
/// Compares two TestSuite objects by their Names (sort ascending)
inline int CompareTestSuiteNameAscending(TestSuite ** first, TestSuite ** second)
{
    //------Last Verified------//
    // - Dec 2, 2004
    wxCHECK(*first != NULL, 0);
    wxCHECK(*second != NULL, 0);
    wxClassInfo* classInfoFirst = (*first)->GetClassInfo();
    wxClassInfo* classInfoSecond = (*second)->GetClassInfo();
    return (wxStrcmp(classInfoFirst->GetClassName(), classInfoSecond->GetClassName()));
}

/// Compares two TestSuite objects by their Names (sort descending)
inline int CompareTestSuiteNameDescending(TestSuite ** first, TestSuite ** second)
{
    //------Last Verified------//
    // - Dec 2, 2004
    wxCHECK(*first != NULL, 0);
    wxCHECK(*second != NULL, 0);
    wxClassInfo* classInfoFirst = (*first)->GetClassInfo();
    wxClassInfo* classInfoSecond = (*second)->GetClassInfo();
    return (wxStrcmp(classInfoSecond->GetClassName(), classInfoFirst->GetClassName()));
}

#endif
