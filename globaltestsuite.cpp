/////////////////////////////////////////////////////////////////////////////
// Name:            globaltestsuite.cpp
// Purpose:         Performs unit testing on global functions
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 30, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "globaltestsuite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(GlobalTestSuite, TestSuite)

/// Default Constructor
GlobalTestSuite::GlobalTestSuite()
{
    //------Last Checked------//
    // - Dec 30, 2004
}

/// Destructor
GlobalTestSuite::~GlobalTestSuite()
{
    //------Last Checked------//
    // - Dec 30, 2004
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t GlobalTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Dec 30, 2004
    return (30);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool GlobalTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Dec 30, 2004
    if (!TestCasewxExtractSubString())
        return (false);
    if (!TestCasewxArabicToRoman())
        return (false);
    
    return (true);
}

/// Tests the wxExtractSubString function
/// @return True if all tests were executed, false if not
bool GlobalTestSuite::TestCasewxExtractSubString()
{
    //------Last Checked------//
    // - Dec 30, 2004
    wxString string;
    wxString fullString = wxT("1,2,3,4,5");
    wxChar separator = wxT(',');
    
    TEST(wxT("wxExtractSubString - invalid fullString"),
        !wxExtractSubString(string, NULL, 1, separator));
    TEST(wxT("wxExtractSubString - empty fullString"),
        !wxExtractSubString(string, wxT(""), 1, separator));
 
    size_t i = 0;
    size_t count = 6;
    for (; i < count; i++)
    {
        wxString expectedValue = wxString::Format(wxT("%d"), i + 1);
        TEST(wxString::Format(wxT("wxExtractSubString - valid string w/5 substrings; substring %d"),
            i), (wxExtractSubString(string, fullString, i, separator) == (i < 5)) &&
            ((i >= 5) ? 1 : (string == expectedValue))
        );            
    }   
    return (true);
}

/// Tests the wxArabicToRoman function
/// @return True if all tests were executed, false if not
bool GlobalTestSuite::TestCasewxArabicToRoman()
{
    //------Last Checked------//
    // - Dec 30, 2004
    
    const wxUint32 testValueCount = 11;
	wxInt32 testValues[testValueCount] =
	{
		-1,
		0,
		1,
		4,
		5,
		10,
		43,
		50,
		58,
		99,
		100
	};

	wxString expectedResults[testValueCount] =
	{
		_T(""),
		_T(""),
		_T("i"),
		_T("iv"),
		_T("v"),
		_T("x"),
		_T("xliii"),
		_T("l"),
		_T("lviii"),
		_T("xcix"),
		_T("c")
	};

	// Check lower and upper case
	wxUint32 i = 0;
	for (; i < 2; i++)
	{
	    wxUint32 j = 0;
		for (; j < testValueCount; j++)
		{
		    wxString expectedResult = expectedResults[j];
		    if (i == 1)
		        expectedResult.MakeUpper();
		        
		    TEST(wxString::Format(wxT("wxArabicToRoman - %d"), testValues[j]), 
		        (wxArabicToRoman(testValues[j], (i == 1)) == expectedResult));
		}
	}
	
    return (true);
}
