/////////////////////////////////////////////////////////////////////////////
// Name:            rehearsalsigntestsuite.cpp
// Purpose:         Performs unit testing on the RehearsalSign class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "rehearsalsigntestsuite.h"

#include "rehearsalsign.h"
#include "powertabfileheader.h"         // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(RehearsalSignTestSuite, TestSuite)

/// Default Constructor
RehearsalSignTestSuite::RehearsalSignTestSuite()
{
    //------Last Checked------//
    // - Dec 10, 2004
}

/// Destructor
RehearsalSignTestSuite::~RehearsalSignTestSuite()
{
    //------Last Checked------//
    // - Dec 10, 2004
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t RehearsalSignTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Dec 10, 2004
    return (47);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool RehearsalSignTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Dec 10, 2004
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseCreation())
        return (false);
    if (!TestCaseOperator())
        return (false);
    if (!TestCaseSerialize())
        return (false);
    if (!TestCaseLetter())
        return (false);
    if (!TestCaseDescription())
        return (false);
    if (!TestCaseOperations())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool RehearsalSignTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Dec 10, 2004
        
    // TEST CASE: Default Constructor
    {
        RehearsalSign rehearsalSign;
        TEST(wxT("Default Constructor"), (
            (!rehearsalSign.IsSet()) &&
            (rehearsalSign.GetDescription() == wxT(""))
        ));
    }
    
    // TEST CASE: Primary Constructor
    {
        RehearsalSign rehearsalSign(wxT('C'), wxT("Chorus"));
        TEST(wxT("Primary Constructor"), (
            (rehearsalSign.GetLetter() == wxT('C')) &&
            (rehearsalSign.GetDescription() == wxT("Chorus"))
        ));
    }
    
    // TEST CASE: Copy Constructor
    {
        RehearsalSign rehearsalSign(wxT('C'), wxT("Chorus"));
        RehearsalSign rehearsalSign2(rehearsalSign);
        TEST(wxT("Copy Constructor"), (
            (rehearsalSign2.GetLetter() == wxT('C')) &&
            (rehearsalSign2.GetDescription() == wxT("Chorus"))
        ));
    }
    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool RehearsalSignTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 12, 2005
    RehearsalSign rehearsalSign(wxT('C'), wxT("Chorus"));
    RehearsalSign* clone = (RehearsalSign*)rehearsalSign.CloneObject();    
    TEST(wxT("CloneObject"),
        (*clone == rehearsalSign)
    );
    delete clone;
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool RehearsalSignTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Dec 10, 2004
    
    // TEST CASE: Operator=
    {
        RehearsalSign rehearsalSign(wxT('C'), wxT("Chorus"));
        RehearsalSign rehearsalSign2 = rehearsalSign;
        TEST(wxT("Operator="), (
            (rehearsalSign2.GetLetter() == wxT('C')) &&
            (rehearsalSign2.GetDescription() == wxT("Chorus"))
        ));
        
        // TEST CASE: Operator= (self-assignment)
        rehearsalSign = rehearsalSign;
        TEST(wxT("Operator= (self-assignment)"),
            (rehearsalSign == rehearsalSign)
        );
    }
    
    // TEST CASE: Operator==
    {
        RehearsalSign rehearsalSign(wxT('C'), wxT("Chorus"));
        RehearsalSign rehearsalSign2(wxT('C'), wxT("Chorus"));
        RehearsalSign rehearsalSign3(wxT('D'), wxT("Chorus"));
        RehearsalSign rehearsalSign4(wxT('C'), wxT("Chorus2"));
        
        TEST(wxT("Operator== - rehearsalSign == rehearsalSign"), (rehearsalSign == rehearsalSign2));
        TEST(wxT("Operator== - rehearsalSign != rehearsalSign 2"), !(rehearsalSign == rehearsalSign3));
        TEST(wxT("Operator== - rehearsalSign != rehearsalSign 3"), !(rehearsalSign == rehearsalSign4));
    }
    
    // TEST CASE: Operator!=
    {
        RehearsalSign rehearsalSign(wxT('C'), wxT("Chorus"));
        RehearsalSign rehearsalSign2(wxT('C'), wxT("Chorus"));
        RehearsalSign rehearsalSign3(wxT('D'), wxT("Chorus"));
        RehearsalSign rehearsalSign4(wxT('C'), wxT("Chorus2"));
        
        TEST(wxT("Operator!= - rehearsalSign == rehearsalSign"), !(rehearsalSign != rehearsalSign2));
        TEST(wxT("Operator!= - rehearsalSign != rehearsalSign 2"), (rehearsalSign != rehearsalSign3));
        TEST(wxT("Operator!= - rehearsalSign != rehearsalSign 3"), (rehearsalSign != rehearsalSign4));
    }
    
    return (true);
}

/// Tests Serialization
/// @return True if all tests were executed, false if not
bool RehearsalSignTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Dec 10, 2004
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    RehearsalSign rehearsalSignOut(wxT('C'), wxT("Chorus"));
    rehearsalSignOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        RehearsalSign rehearsalSignIn;
        rehearsalSignIn.Deserialize(streamIn, PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((rehearsalSignIn == rehearsalSignOut) 
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the Letter Functions
/// @return True if all tests were executed, false if not
bool RehearsalSignTestSuite::TestCaseLetter()
{
    //------Last Checked------//
    // - Dec 10, 2004
    RehearsalSign rehearsalSign;
    wxInt8 i = 'A' - 1;
    for (; i <= ('Z' + 1); i++)
        TEST(wxString::Format(wxT("SetLetter - %c"), i), 
            (rehearsalSign.SetLetter(i) == ((i >= 'A') && (i <= 'Z'))) &&
            (((i < 'A') || (i > 'Z')) ? 1 : (rehearsalSign.GetLetter() == i))
        );
    TEST(wxT("SetLetter - notset"), ((rehearsalSign.SetLetter(RehearsalSign::notSet)) && (!rehearsalSign.IsSet())));
    return (true);
}

/// Tests the Description Functions
/// @return True if all tests were executed, false if not
bool RehearsalSignTestSuite::TestCaseDescription()
{
    //------Last Checked------//
    // - Dec 10, 2004
    RehearsalSign rehearsalSign;
    TEST(wxT("SetDescription - NULL"), !rehearsalSign.SetDescription(NULL));
    TEST(wxT("SetDescription - valid"), (rehearsalSign.SetDescription(wxT("Chorus")) && (rehearsalSign.GetDescription() == wxT("Chorus"))));
    return (true);
}

/// Tests the Operations
/// @return True if all tests were executed, false if not
bool RehearsalSignTestSuite::TestCaseOperations()
{
    //------Last Checked------//
    // - Dec 10, 2004
    RehearsalSign rehearsalSign;
    TEST(wxT("IsSet - false"), !rehearsalSign.IsSet());
    rehearsalSign.SetLetter(wxT('C'));
    rehearsalSign.SetDescription(wxT("Chorus"));
    TEST(wxT("IsSet - true"), rehearsalSign.IsSet());
    rehearsalSign.Clear();
    TEST(wxT("Clear"), !rehearsalSign.IsSet());
    return (true);
}
