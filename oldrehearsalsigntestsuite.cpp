/////////////////////////////////////////////////////////////////////////////
// Name:            oldrehearsalsigntestsuite.cpp
// Purpose:         Performs unit testing on the OldRehearsalSign class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "oldrehearsalsigntestsuite.h"

#include "oldrehearsalsign.h"
#include "rehearsalsign.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(OldRehearsalSignTestSuite, TestSuite)

/// Default Constructor
OldRehearsalSignTestSuite::OldRehearsalSignTestSuite()
{
    //------Last Checked------//
    // - Jan 3, 2005    
}

/// Destructor
OldRehearsalSignTestSuite::~OldRehearsalSignTestSuite()
{
    //------Last Checked------//
    // - Jan 3, 2005
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t OldRehearsalSignTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Jan 3, 2005
    return (15);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool OldRehearsalSignTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Jan 3, 2005
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseConstruction())
        return (false);
    if (!TestCaseOperator())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool OldRehearsalSignTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 3, 2005
    
    // TEST CASE: Default Constructor
    {
        OldRehearsalSign oldRehearsalSign;
        TEST(wxT("Default Constructor"), (
            (oldRehearsalSign.m_system == OldRehearsalSign::DEFAULT_SYSTEM) &&
            (oldRehearsalSign.m_position == OldRehearsalSign::DEFAULT_POSITION) &&
            (oldRehearsalSign.m_data == OldRehearsalSign::DEFAULT_DATA) &&
            (oldRehearsalSign.m_letter == OldRehearsalSign::DEFAULT_LETTER) &&
            (oldRehearsalSign.m_description == OldRehearsalSign::DEFAULT_DESCRIPTION)
        ));
    }
    return (true);
}

/// Tests the Construction Functions
/// @return True if all tests were executed, false if not
bool OldRehearsalSignTestSuite::TestCaseConstruction()
{
    //------Last Checked------//
    // - Jan 3, 2005    
    
    OldRehearsalSign oldRehearsalSign;
    oldRehearsalSign.m_system = 10;
    oldRehearsalSign.m_position = 11;
    oldRehearsalSign.m_data = 12;
    oldRehearsalSign.m_letter = 'Z';
    oldRehearsalSign.m_description = wxT("Test");
    
    RehearsalSign rehearsalSign;
    bool ok = oldRehearsalSign.ConstructRehearsalSign(rehearsalSign);
    TEST(wxT("ConstructRehearsalSign"), 
        ok &&
        (rehearsalSign.GetLetter() == 'Z') &&
        (rehearsalSign.GetDescription() == wxT("Test"))
    );
    
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool OldRehearsalSignTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 5, 2005
    
    // TEST CASE: Assignment Operator
    {
        OldRehearsalSign oldRehearsalSign;
        oldRehearsalSign.m_system = 1;
        oldRehearsalSign.m_position = 2;
        oldRehearsalSign.m_data = 3;
        oldRehearsalSign.m_letter = 'Z';
        oldRehearsalSign.m_description = wxT("Test");
        
        OldRehearsalSign oldRehearsalSign2 = oldRehearsalSign;
        TEST(wxT("Operator="), (oldRehearsalSign == oldRehearsalSign2));
    }

    // TEST CASE: Equality Operator
    {
        OldRehearsalSign oldRehearsalSign;
        OldRehearsalSign oldRehearsalSign2;
        OldRehearsalSign oldRehearsalSign3;
        oldRehearsalSign3.m_system = 1;
        OldRehearsalSign oldRehearsalSign4;
        oldRehearsalSign4.m_position = 2;
        OldRehearsalSign oldRehearsalSign5;
        oldRehearsalSign5.m_data = 3;
        OldRehearsalSign oldRehearsalSign6;
        oldRehearsalSign6.m_letter = 'Z';
        OldRehearsalSign oldRehearsalSign7;
        oldRehearsalSign7.m_description = wxT("Test");

        TEST(wxT("Operator== - oldRehearsalSign == oldRehearsalSign"),
            (oldRehearsalSign == oldRehearsalSign2));
        TEST(wxT("Operator== - oldRehearsalSign != oldRehearsalSign"),
            !(oldRehearsalSign == oldRehearsalSign3));
        TEST(wxT("Operator== - oldRehearsalSign != oldRehearsalSign 2"),
            !(oldRehearsalSign == oldRehearsalSign4));
        TEST(wxT("Operator== - oldRehearsalSign != oldRehearsalSign 3"),
            !(oldRehearsalSign == oldRehearsalSign5));
        TEST(wxT("Operator== - oldRehearsalSign != oldRehearsalSign 4"),
            !(oldRehearsalSign == oldRehearsalSign6));
        TEST(wxT("Operator== - oldRehearsalSign != oldRehearsalSign 5"),
            !(oldRehearsalSign == oldRehearsalSign7));
    }
    
    // TEST CASE: Inequality Operator
    {
        OldRehearsalSign oldRehearsalSign;
        OldRehearsalSign oldRehearsalSign2;
        OldRehearsalSign oldRehearsalSign3;
        oldRehearsalSign3.m_system = 1;
        OldRehearsalSign oldRehearsalSign4;
        oldRehearsalSign4.m_position = 2;
        OldRehearsalSign oldRehearsalSign5;
        oldRehearsalSign5.m_data = 3;
        OldRehearsalSign oldRehearsalSign6;
        oldRehearsalSign6.m_letter = 'Z';
        OldRehearsalSign oldRehearsalSign7;
        oldRehearsalSign7.m_description = wxT("Test");

        TEST(wxT("Operator!= - oldRehearsalSign == oldRehearsalSign"),
            !(oldRehearsalSign != oldRehearsalSign2));
        TEST(wxT("Operator!= - oldRehearsalSign != oldRehearsalSign"), 
            (oldRehearsalSign != oldRehearsalSign3));
        TEST(wxT("Operator!= - oldRehearsalSign != oldRehearsalSign 2"),
            (oldRehearsalSign != oldRehearsalSign4));
        TEST(wxT("Operator!= - oldRehearsalSign != oldRehearsalSign 3"),
            (oldRehearsalSign != oldRehearsalSign5));
        TEST(wxT("Operator!= - oldRehearsalSign != oldRehearsalSign 4"),
            (oldRehearsalSign != oldRehearsalSign6));
        TEST(wxT("Operator!= - oldRehearsalSign != oldRehearsalSign 5"),
            (oldRehearsalSign != oldRehearsalSign7));
    }
        
    return (true);
}
