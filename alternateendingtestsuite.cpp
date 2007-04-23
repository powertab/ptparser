/////////////////////////////////////////////////////////////////////////////
// Name:            alternateendingtestsuite.cpp
// Purpose:         Performs unit testing on the AlternateEnding class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 4, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "alternateendingtestsuite.h"

#include "alternateending.h"
#include "powertabfileheader.h"         // Needed for file version constants
#include <math.h>                       // Needed for pow

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(AlternateEndingTestSuite, TestSuite)

const wxWord testNumbers = (wxWord)(1 | 16 | 32 | 64 | 512);    // 1., 5.-7., D.S.

/// Default Constructor
AlternateEndingTestSuite::AlternateEndingTestSuite()
{
    //------Last Checked------//
    // - Dec 4, 2004
}

/// Destructor
AlternateEndingTestSuite::~AlternateEndingTestSuite()
{
    //------Last Checked------//
    // - Dec 4, 2004
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t AlternateEndingTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Jan 12, 2005
    return (105);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool AlternateEndingTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Jan 12, 2005
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseCreation())
        return (false);
    if (!TestCaseOperator())
        return (false);
    if (!TestCaseSerialize())
        return (false);
    if (!TestCaseNumbers())
        return (false);
    if (!TestCaseDaCapo())
        return (false);
    if (!TestCaseDalSegno())
        return (false);
    if (!TestCaseDalSegnoSegno())
        return (false);
    if (!TestCaseText())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool AlternateEndingTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 12, 2005
    
    // TEST CASE: Default Constructor
    {
        AlternateEnding alternateEnding;
	    TEST(wxT("Default Constructor"), 
	    (
	        (alternateEnding.GetNumbers() == 0)
	    ));
    }
    
    // TEST CASE: Primary Constructor
    {
        AlternateEnding alternateEnding(1, 2, testNumbers);
	    TEST(wxT("Primary Constructor"), 
	    (
	        (alternateEnding.GetSystem() == 1) &&
	        (alternateEnding.GetPosition() == 2) &&
	        (alternateEnding.IsNumberSet(1)) &&
	        (!alternateEnding.IsNumberSet(2)) &&
	        (!alternateEnding.IsNumberSet(3)) &&
	        (!alternateEnding.IsNumberSet(4)) &&
	        (alternateEnding.IsNumberSet(5)) &&
	        (alternateEnding.IsNumberSet(6)) &&
	        (alternateEnding.IsNumberSet(7)) &&
	        (!alternateEnding.IsNumberSet(8)) &&
	        (!alternateEnding.IsDaCapoSet()) &&
	        (alternateEnding.IsDalSegnoSet()) &&
	        (!alternateEnding.IsDalSegnoSegnoSet())
	    ));
    }
    
    // TEST CASE: Copy Constructor
    {
        AlternateEnding alternateEnding(1,2,testNumbers);
        AlternateEnding alternateEnding2(alternateEnding);

    	TEST(wxT("Copy Constructor"), 
	    (
	        (alternateEnding2 == alternateEnding)
    	));
    }
    
    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool AlternateEndingTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 12, 2005
    AlternateEnding alternateEnding(1,2,testNumbers);
    AlternateEnding* clone = (AlternateEnding*)alternateEnding.CloneObject();
    TEST(wxT("CloneObject"),
        (*clone == alternateEnding)
    );
    delete clone;
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool AlternateEndingTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 12, 2005
    
    // TEST CASE: Assignment Operator
    {
        AlternateEnding alternateEnding(1,2,testNumbers);
        AlternateEnding alternateEnding2(alternateEnding);
        
        alternateEnding2 = alternateEnding;

	    TEST(wxT("Operator="), 
	    (
	        (alternateEnding2 == alternateEnding)
	    ));
	    
	    // TEST CASE: Self assignment
	    alternateEnding = alternateEnding;
	    TEST(wxT("Operator= - self assignment"), (alternateEnding == alternateEnding));
    }

    // TEST CASE: Equality Operator
    {
        AlternateEnding alternateEnding(1,2,testNumbers);
        AlternateEnding alternateEnding2(1,2,testNumbers);
        AlternateEnding alternateEnding3(2,2,testNumbers);
        AlternateEnding alternateEnding4(1,3,testNumbers);
        AlternateEnding alternateEnding5(1,2,testNumbers + 1);
        AlternateEnding alternateEnding6(1,2,1);
        AlternateEnding alternateEnding7(1,2,2);
        AlternateEnding alternateEnding8(1,2,4);
        AlternateEnding alternateEnding9(1,2,8);
        AlternateEnding alternateEnding10(1,2,16);
        AlternateEnding alternateEnding11(1,2,32);
        AlternateEnding alternateEnding12(1,2,64);
        AlternateEnding alternateEnding13(1,2,128);
        AlternateEnding alternateEnding14(1,2,256);
        AlternateEnding alternateEnding15(1,2,512);
        AlternateEnding alternateEnding16(1,2,1024);
        AlternateEnding alternateEnding17(1,2,2048);
        
        TEST(wxT("Operator== - alternateEnding == alternateEnding"), (alternateEnding == alternateEnding2));
        TEST(wxT("Operator== - alternateEnding != alternateEnding"), !(alternateEnding == alternateEnding3));
        TEST(wxT("Operator== - alternateEnding != alternateEnding 2"), !(alternateEnding == alternateEnding4));
        TEST(wxT("Operator== - alternateEnding != alternateEnding 3"), !(alternateEnding == alternateEnding5));
        TEST(wxT("Operator== - alternateEnding != alternateEnding 4"), !(alternateEnding == alternateEnding6));
        TEST(wxT("Operator== - alternateEnding != alternateEnding 5"), !(alternateEnding == alternateEnding7));
        TEST(wxT("Operator== - alternateEnding != alternateEnding 6"), !(alternateEnding == alternateEnding8));
        TEST(wxT("Operator== - alternateEnding != alternateEnding 7"), !(alternateEnding == alternateEnding9));
        TEST(wxT("Operator== - alternateEnding != alternateEnding 8"), !(alternateEnding == alternateEnding10));
        TEST(wxT("Operator== - alternateEnding != alternateEnding 9"), !(alternateEnding == alternateEnding11));
        TEST(wxT("Operator== - alternateEnding != alternateEnding 10"), !(alternateEnding == alternateEnding12));
        TEST(wxT("Operator== - alternateEnding != alternateEnding 11"), !(alternateEnding == alternateEnding13));
        TEST(wxT("Operator== - alternateEnding != alternateEnding 12"), !(alternateEnding == alternateEnding14));
        TEST(wxT("Operator== - alternateEnding != alternateEnding 13"), !(alternateEnding == alternateEnding15));
        TEST(wxT("Operator== - alternateEnding != alternateEnding 14"), !(alternateEnding == alternateEnding16));
        TEST(wxT("Operator== - alternateEnding != alternateEnding 15"), !(alternateEnding == alternateEnding17));
    }
    
    // TEST CASE: Inequality Operator
    {
        AlternateEnding alternateEnding(1,2,testNumbers);
        AlternateEnding alternateEnding2(1,2,testNumbers);
        AlternateEnding alternateEnding3(2,2,testNumbers);
        AlternateEnding alternateEnding4(1,3,testNumbers);
        AlternateEnding alternateEnding5(1,2,testNumbers + 1);
        AlternateEnding alternateEnding6(1,2,1);
        AlternateEnding alternateEnding7(1,2,2);
        AlternateEnding alternateEnding8(1,2,4);
        AlternateEnding alternateEnding9(1,2,8);
        AlternateEnding alternateEnding10(1,2,16);
        AlternateEnding alternateEnding11(1,2,32);
        AlternateEnding alternateEnding12(1,2,64);
        AlternateEnding alternateEnding13(1,2,128);
        AlternateEnding alternateEnding14(1,2,256);
        AlternateEnding alternateEnding15(1,2,512);
        AlternateEnding alternateEnding16(1,2,1024);
        AlternateEnding alternateEnding17(1,2,2048);
        
        TEST(wxT("Operator!= - alternateEnding == alternateEnding"), !(alternateEnding != alternateEnding2));
        TEST(wxT("Operator!= - alternateEnding != alternateEnding"), (alternateEnding != alternateEnding3));
        TEST(wxT("Operator!= - alternateEnding != alternateEnding 2"), (alternateEnding != alternateEnding4));
        TEST(wxT("Operator!= - alternateEnding != alternateEnding 2"), (alternateEnding != alternateEnding5));
        TEST(wxT("Operator!= - alternateEnding != alternateEnding 4"), (alternateEnding != alternateEnding6));
        TEST(wxT("Operator!= - alternateEnding != alternateEnding 5"), (alternateEnding != alternateEnding7));
        TEST(wxT("Operator!= - alternateEnding != alternateEnding 6"), (alternateEnding != alternateEnding8));
        TEST(wxT("Operator!= - alternateEnding != alternateEnding 7"), (alternateEnding != alternateEnding9));
        TEST(wxT("Operator!= - alternateEnding != alternateEnding 8"), (alternateEnding != alternateEnding10));
        TEST(wxT("Operator!= - alternateEnding != alternateEnding 9"), (alternateEnding != alternateEnding11));
        TEST(wxT("Operator!= - alternateEnding != alternateEnding 10"), (alternateEnding != alternateEnding12));
        TEST(wxT("Operator!= - alternateEnding != alternateEnding 11"), (alternateEnding != alternateEnding13));
        TEST(wxT("Operator!= - alternateEnding != alternateEnding 12"), (alternateEnding != alternateEnding14));
        TEST(wxT("Operator!= - alternateEnding != alternateEnding 13"), (alternateEnding != alternateEnding15));
        TEST(wxT("Operator!= - alternateEnding != alternateEnding 14"), (alternateEnding != alternateEnding16));
        TEST(wxT("Operator!= - alternateEnding != alternateEnding 15"), (alternateEnding != alternateEnding17));
    }
    return (true);
}

/// Tests the Serialization Functions
/// @return True if all tests were executed, false if not
bool AlternateEndingTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Dec 4, 2004
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    AlternateEnding alternateEndingOut(1, 2, testNumbers);
    alternateEndingOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        AlternateEnding alternateEndingIn;
        alternateEndingIn.Deserialize(streamIn, PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((alternateEndingIn == alternateEndingOut) 
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);

	return (true);
}

/// Tests the Number Functions
/// @return True if all tests were executed, false if not
bool AlternateEndingTestSuite::TestCaseNumbers()
{
    //------Last Checked------//
    // - Jan 12, 2005
    
    // TEST CASE: IsValidNumbers
    {
        wxUint32 i = 0;
        for (; i <= (AlternateEnding::dalSegnoSegno + 1); i++)
        {
        
            wxWord numbers = 0;
            if (i > 0)
                numbers = (wxWord)pow((double)2, (double)i - 1);
            TEST(wxString::Format(wxT("IsValidNumbers - %d"), numbers),
                (AlternateEnding::IsValidNumbers(numbers) == (i <= AlternateEnding::dalSegnoSegno))
            );
        }
    }
    
    // TEST CASE: IsValidNumber
    {
        wxUint32 i = 0;
        for (; i <= (AlternateEnding::dalSegnoSegno + 1); i++)
            TEST(wxString::Format(wxT("IsValidNumber - %d"), i),
                (AlternateEnding::IsValidNumber(i) == ((i > 0) && (i <= AlternateEnding::dalSegnoSegno)))
            );
    }
    
    // TEST CASE: SetNumbers
    {
        AlternateEnding alternateEnding;
        TEST(wxT("SetNumbers - 0"), 
            (alternateEnding.SetNumbers(0)) &&
            (alternateEnding.GetNumbers() == 0)
        );
        
        TEST(wxT("SetNumbers - invalid"),
            (!alternateEnding.SetNumbers(0xffff))
        );
        
        TEST(wxT("SetNumbers - 1,5-7,D.S."),
            (alternateEnding.SetNumbers(testNumbers)) &&
            (alternateEnding.GetNumbers() == testNumbers) &&
            (alternateEnding.IsNumberSet(1)) &&
            (alternateEnding.IsNumberSet(5)) &&
            (alternateEnding.IsNumberSet(6)) &&
            (alternateEnding.IsNumberSet(7)) &&
            (alternateEnding.IsDalSegnoSet())
        );  
    }
    
    // TEST CASE: SetNumber
    {
        AlternateEnding alternateEnding;
        wxUint32 i = 0;
        for (; i <= (AlternateEnding::dalSegnoSegno + 1); i++)
            TEST(wxString::Format(wxT("SetNumber - %d"), i),
                (alternateEnding.SetNumber(i) == ((i > 0) && (i <= AlternateEnding::dalSegnoSegno)) &&
                ((i == 0) || (i > AlternateEnding::dalSegnoSegno)) ? 1 : (alternateEnding.IsNumberSet(i)))
            );
    }
    
    return (true);
}

/// Tests the Da Capo Functions
/// @return True if all tests were executed, false if not
bool AlternateEndingTestSuite::TestCaseDaCapo()
{
    //------Last Checked------//
    // - Jan 12, 2005
    AlternateEnding alternateEnding;
    alternateEnding.SetDaCapo();
    TEST(wxT("SetDaCapo"), alternateEnding.IsDaCapoSet());
    alternateEnding.ClearDaCapo();
    TEST(wxT("ClearDaCapo"), !alternateEnding.IsDaCapoSet());
    
    return (true);
}

/// Tests the Dal Segno Functions
/// @return True if all tests were executed, false if not
bool AlternateEndingTestSuite::TestCaseDalSegno()
{
    //------Last Checked------//
    // - Jan 12, 2005
    AlternateEnding alternateEnding;
    alternateEnding.SetDalSegno();
    TEST(wxT("SetDalSegno"), alternateEnding.IsDalSegnoSet());
    alternateEnding.ClearDalSegno();
    TEST(wxT("ClearDalSegno"), !alternateEnding.IsDalSegnoSet());
    
    return (true);
}

/// Tests the Dal Segno Segno Functions
/// @return True if all tests were executed, false if not
bool AlternateEndingTestSuite::TestCaseDalSegnoSegno()
{
    //------Last Checked------//
    // - Jan 12, 2005
    AlternateEnding alternateEnding;
    alternateEnding.SetDalSegnoSegno();
    TEST(wxT("SetDalSegnoSegno"), alternateEnding.IsDalSegnoSegnoSet());
    alternateEnding.ClearDalSegnoSegno();
    TEST(wxT("ClearDalSegnoSegno"), !alternateEnding.IsDalSegnoSegnoSet());
    
    return (true);
}

/// Tests the Text Functions
/// @return True if all tests were executed, false if not
bool AlternateEndingTestSuite::TestCaseText()
{
    //------Last Checked------//
    // - Jan 12, 2005
    
    // TEST CASE: GetNumberText
    {
        wxUint32 i = 0;
        for (; i <= (AlternateEnding::dalSegnoSegno + 1); i++)
        {
            wxString text = wxT("");
            if ((i > 0) && (i < AlternateEnding::daCapo))
                text = wxString::Format(wxT("%d"), i);
            else if (i == AlternateEnding::daCapo)
                text = wxT("D.C.");
            else if (i == AlternateEnding::dalSegno)
                text = wxT("D.S.");
            else if (i == AlternateEnding::dalSegnoSegno)
                text = wxT("D.S.S.");
            TEST(wxString::Format(wxT("GetNumberText - %d"), i),
                (AlternateEnding::GetNumberText(i) == text)
            );
        }
    }
    
    // TEST CASE: GetText
    {
        AlternateEnding alternateEnding;
        TEST(wxT("GetText - empty"), (alternateEnding.GetText() == wxT("")));
        
        alternateEnding.SetNumbers(1);
        TEST(wxT("GetText - 1."), (alternateEnding.GetText() == wxT("1.")));
        
        alternateEnding.SetNumbers(3);
        TEST(wxT("GetText - 1., 2."), (alternateEnding.GetText() == wxT("1., 2.")));
        
        alternateEnding.SetNumbers(7);
        TEST(wxT("GetText - 1.-3."), (alternateEnding.GetText() == wxT("1.-3.")));
        
        alternateEnding.SetNumbers(testNumbers);
        TEST(wxT("GetText - 1., 5.-7., D.S."), (alternateEnding.GetText() == wxT("1., 5.-7., D.S.")));
    }
    return (true);
}
