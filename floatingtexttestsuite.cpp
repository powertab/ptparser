/////////////////////////////////////////////////////////////////////////////
// Name:            floatingtexttestsuite.cpp
// Purpose:         Performs unit testing on the FloatingText class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 5, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "floatingtexttestsuite.h"
#include "floatingtext.h"

#include "powertabfileheader.h"     // Needed for PowerTabFileHeader constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(FloatingTextTestSuite, TestSuite)

/// Default Constructor
FloatingTextTestSuite::FloatingTextTestSuite()
{
    //------Last Checked------//
    // - Dec 6, 2004
}

/// Destructor
FloatingTextTestSuite::~FloatingTextTestSuite()
{
    //------Last Checked------//
    // - Dec 6, 2004
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t FloatingTextTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Dec 6, 2004
    return (47);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool FloatingTextTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Dec 6, 2004
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseCreation())
        return (false);
    if (!TestCaseOperator())
        return (false);
    if (!TestCaseSerialize())
        return (false);
    if (!TestCaseText())
        return (false);
    if (!TestCaseRect())
        return (false);
    if (!TestCaseFlags())
        return (false);
    if (!TestCaseAlignment())
        return (false);
    if (!TestCaseBorder())
        return (false);
    if (!TestCaseFontSetting())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool FloatingTextTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Dec 6, 2004

    const FontSetting fontSetting(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0));    
    
    // TEST CASE: Default constructor
    {
        FloatingText floatingText;
        TEST(wxT("Default Constructor"), 
        (
            (floatingText.GetText() == FloatingText::DEFAULT_TEXT) &&
            (floatingText.GetRect() == FloatingText::DEFAULT_RECT) &&
            (floatingText.IsAlignedLeft()) &&
            (!floatingText.HasBorder()) &&
            (floatingText.GetFontSetting() == FontSetting())
        ));
    }

    // TEST CASE: Primary constructor
    {
        FloatingText floatingText(wxT("Test"), wxRect(10,10,20,20), FloatingText::alignCenter | FloatingText::border, fontSetting);
        TEST(wxT("Primary Constructor"), 
            (floatingText.GetText() == wxT("Test")) &&
            (floatingText.GetRect() == wxRect(10,10,20,20)) &&
            (floatingText.IsAlignedCenter()) &&
            (floatingText.HasBorder()) &&
            (floatingText.GetFontSetting() == fontSetting)
        );
    }
    
    // TEST CASE: Copy constructor
    {
        FloatingText floatingText(wxT("Test"), wxRect(10,10,20,20), FloatingText::alignCenter | FloatingText::border, fontSetting);
        FloatingText floatingText2(floatingText);

        TEST(wxT("Copy Constructor"), 
        (
            (floatingText == floatingText2)
        ));
    }
    
    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool FloatingTextTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 12, 2005
    
    const FontSetting fontSetting(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0));    
    FloatingText floatingText(wxT("Test"), wxRect(10,10,20,20), FloatingText::alignCenter | FloatingText::border, fontSetting);
    FloatingText* clone = (FloatingText*)floatingText.CloneObject();
    TEST(wxT("CloneObject"),
        (*clone == floatingText)
    );
    delete clone;
    
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool FloatingTextTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Dec 7, 2004
    
    const FontSetting fontSetting(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0));
    const FontSetting fontSetting2(wxT("Arial2"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0));
    
    // TEST CASE: Operator =
	{    
	    FloatingText floatingText(wxT("Test"), wxRect(10,10,20,20), FloatingText::alignCenter | FloatingText::border, fontSetting);
	    FloatingText floatingText2 = floatingText;
        TEST(wxT("Operator="), 
            (floatingText2.GetText() == wxT("Test")) &&
            (floatingText2.GetRect() == wxRect(10,10,20,20)) &&
            (floatingText2.IsAlignedCenter()) &&
            (floatingText2.HasBorder()) &&
            (floatingText2.GetFontSetting() == fontSetting)
        );
            
		// TEST CASE: Self assignment
		{
		    FloatingText floatingText(wxT("Test"), wxRect(10,10,20,20), FloatingText::alignCenter | FloatingText::border, fontSetting);
		    floatingText = floatingText;
            TEST(wxT("Operator= (self-assignment)"), 
                (floatingText.GetText() == wxT("Test")) &&
                (floatingText.GetRect() == wxRect(10,10,20,20)) &&
                (floatingText.IsAlignedCenter()) &&
                (floatingText.HasBorder()) &&
                (floatingText.GetFontSetting() == fontSetting)
            );
        }
    }

	// TEST CASE: Operator==
	{
	    FloatingText floatingText(wxT("Test"), wxRect(10,10,20,20), FloatingText::alignCenter | FloatingText::border, fontSetting);
	    FloatingText floatingText2(wxT("Test"), wxRect(10,10,20,20), FloatingText::alignCenter | FloatingText::border, fontSetting);
	    FloatingText floatingText3(wxT("Test2"), wxRect(10,10,20,20), FloatingText::alignCenter | FloatingText::border, fontSetting);
	    FloatingText floatingText4(wxT("Test"), wxRect(11,10,20,20), FloatingText::alignCenter | FloatingText::border, fontSetting);
	    FloatingText floatingText5(wxT("Test"), wxRect(10,10,20,20), FloatingText::alignLeft | FloatingText::border, fontSetting);
	    FloatingText floatingText6(wxT("Test"), wxRect(10,10,20,20), FloatingText::alignCenter, fontSetting);
	    FloatingText floatingText7(wxT("Test"), wxRect(10,10,20,20), FloatingText::alignCenter | FloatingText::border, fontSetting2);
	    
		// TEST CASE: floatingText == floatingText
		TEST(wxT("Operator== - floatingText == floatingText"), (floatingText == floatingText2));
		TEST(wxT("Operator== - floatingText != floatingText"), !(floatingText == floatingText3));
		TEST(wxT("Operator== - floatingText != floatingText 2"), !(floatingText == floatingText4));
		TEST(wxT("Operator== - floatingText != floatingText 3"), !(floatingText == floatingText5));
		TEST(wxT("Operator== - floatingText != floatingText 4"), !(floatingText == floatingText6));
		TEST(wxT("Operator== - floatingText != floatingText 5"), !(floatingText == floatingText7));
	}

	// TEST CASE: Operator!=
	{
	    FloatingText floatingText(wxT("Test"), wxRect(10,10,20,20), FloatingText::alignCenter | FloatingText::border, fontSetting);
	    FloatingText floatingText2(wxT("Test"), wxRect(10,10,20,20), FloatingText::alignCenter | FloatingText::border, fontSetting);
	    FloatingText floatingText3(wxT("Test2"), wxRect(10,10,20,20), FloatingText::alignCenter | FloatingText::border, fontSetting);
	    FloatingText floatingText4(wxT("Test"), wxRect(11,10,20,20), FloatingText::alignCenter | FloatingText::border, fontSetting);
	    FloatingText floatingText5(wxT("Test"), wxRect(10,10,20,20), FloatingText::alignLeft | FloatingText::border, fontSetting);
	    FloatingText floatingText6(wxT("Test"), wxRect(10,10,20,20), FloatingText::alignCenter, fontSetting);
	    FloatingText floatingText7(wxT("Test"), wxRect(10,10,20,20), FloatingText::alignCenter | FloatingText::border, fontSetting2);
	   
	    // TEST CASE: floatingText != floatingText
		TEST(wxT("Operator!= - floatingText == floatingText"), !(floatingText != floatingText2));
		TEST(wxT("Operator!= - floatingText != floatingText"), (floatingText != floatingText3));
		TEST(wxT("Operator!= - floatingText != floatingText 2"), (floatingText != floatingText4));
		TEST(wxT("Operator!= - floatingText != floatingText 3"), (floatingText != floatingText5));
		TEST(wxT("Operator!= - floatingText != floatingText 4"), (floatingText != floatingText6));
		TEST(wxT("Operator!= - floatingText != floatingText 5"), (floatingText != floatingText7));
	}
	    
    return (true);
}

/// Tests Serialization
/// @return True if all tests were executed, false if not
bool FloatingTextTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Dec 7, 2004

    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    FloatingText floatingTextOut(wxT("Text"), wxRect(10, 10, 20, 20), FloatingText::alignCenter | FloatingText::border, FontSetting(wxT("Arial"), 10, FontSetting::weightBold, true, true, true, wxColor(255,0,0)));
    floatingTextOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        FloatingText floatingTextIn;
        floatingTextIn.Deserialize(streamIn, PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((floatingTextIn == floatingTextOut) 
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the Text Functions
/// @return True if all tests were executed, false if not
bool FloatingTextTestSuite::TestCaseText()
{
    //------Last Checked------//
    // - Dec 7, 2004
    FloatingText floatingText;
    TEST(wxT("SetText - NULL"), !floatingText.SetText(NULL));
    TEST(wxT("SetText - valid text"), ((floatingText.SetText(wxT("Test"))) && (floatingText.GetText() == wxT("Test"))));
    return (true);
}

/// Tests the Rect Functions
/// @return True if all tests were executed, false if not
bool FloatingTextTestSuite::TestCaseRect()
{
    //------Last Checked------//
    // - Dec 7, 2004
    FloatingText floatingText;
    floatingText.SetRect(wxRect(10,10,20,20));
    TEST(wxT("SetRect"), (floatingText.GetRect() == wxRect(10,10,20,20)));
    floatingText.SetRect(wxRect(0,0,0,0));
    TEST(wxT("IsEmpty"), (floatingText.IsEmpty()));
    return (true);
}

/// Tests the Flags Functions
/// @return True if all tests were executed, false if not
bool FloatingTextTestSuite::TestCaseFlags()
{
    //------Last Checked------//
    // - Dec 7, 2004
    FloatingText floatingText;
    floatingText.SetFlag(FloatingText::border);
    TEST(wxT("SetFlag"), floatingText.IsFlagSet(FloatingText::border));
    floatingText.ClearFlag(FloatingText::border);
    TEST(wxT("ClearFlag"), !floatingText.IsFlagSet(FloatingText::border));
    return (true);
}

/// Tests the Alignment Functions
/// @return True if all tests were executed, false if not
bool FloatingTextTestSuite::TestCaseAlignment()
{
    //------Last Checked------//
    // - Dec 7, 2004
    
    const int testValueCount = 4;
    wxByte testValues[testValueCount];
    testValues[0] = 0;
    testValues[1] = FloatingText::alignLeft;
    testValues[2] = FloatingText::alignCenter;
    testValues[3] = FloatingText::alignRight;
    
    // TEST CASE: IsValidAlignment
    {
        bool expectedResults[testValueCount];
        expectedResults[0] = false;
        expectedResults[1] = true;
        expectedResults[2] = true;
        expectedResults[3] = true;
        
        int i = 0;
        for (; i < testValueCount; i++)
            TEST(wxString::Format(wxT("IsValidAlignment - %d"), testValues[i]), (FloatingText::IsValidAlignment(testValues[i]) == expectedResults[i]));
    }
    
    // TEST CASE: SetAlignment
    {
        FloatingText floatingText;
        bool expectedResults[testValueCount];
        expectedResults[0] = false;
        expectedResults[1] = true;
        expectedResults[2] = true;
        expectedResults[3] = true;
        
        int i = 0;
        for (; i < testValueCount; i++)
            TEST(wxString::Format(wxT("SetAlignment - %d"), testValues[i]), 
                (floatingText.SetAlignment(testValues[i]) == expectedResults[i]) &&
                (!expectedResults[i]) ? 1 : ((floatingText.IsAligned(testValues[i]) && (floatingText.GetAlignment() == testValues[i])))
            );
    }
    
    // TEST CASE: IsAlignedLeft
    {
        FloatingText floatingText;
        bool expectedResults[testValueCount];
        expectedResults[0] = false;
        expectedResults[1] = true;
        expectedResults[2] = false;
        expectedResults[3] = false;
        
        // Start at one, we don't need to test zero
        int i = 1;
        for (; i < testValueCount; i++)
        {
            floatingText.SetAlignment(testValues[i]);
            TEST(wxString::Format(wxT("IsAlignedLeft - %d"), testValues[i]), (floatingText.IsAlignedLeft() == expectedResults[i]));
        }
    }
    
    // TEST CASE: IsAlignedCenter
    {
        FloatingText floatingText;
        bool expectedResults[testValueCount];
        expectedResults[0] = false;
        expectedResults[1] = false;
        expectedResults[2] = true;
        expectedResults[3] = false;
        
        // Start at one, we don't need to test zero
        int i = 1;
        for (; i < testValueCount; i++)
        {
            floatingText.SetAlignment(testValues[i]);
            TEST(wxString::Format(wxT("IsAlignedCenter - %d"), testValues[i]), (floatingText.IsAlignedCenter() == expectedResults[i]));
        }
    }
    
    // TEST CASE: IsAlignedRight
    {
        FloatingText floatingText;
        bool expectedResults[testValueCount];
        expectedResults[0] = false;
        expectedResults[1] = false;
        expectedResults[2] = false;
        expectedResults[3] = true;
        
        // Start at one, we don't need to test zero
        int i = 1;
        for (; i < testValueCount; i++)
        {
            floatingText.SetAlignment(testValues[i]);
            TEST(wxString::Format(wxT("IsAlignedRight - %d"), testValues[i]), (floatingText.IsAlignedRight() == expectedResults[i]));
        }
    }
    
    return (true);
}

/// Tests the Border Functions
/// @return True if all tests were executed, false if not
bool FloatingTextTestSuite::TestCaseBorder()
{
    //------Last Checked------//
    // - Dec 7, 2004
    FloatingText floatingText;
    floatingText.SetBorder();
    TEST(wxT("SetBorder - true"), (floatingText.HasBorder()));
    floatingText.SetBorder(false);
    TEST(wxT("SetBorder - false"), (!floatingText.HasBorder()));
    return (true);
}

/// Tests the FontSetting Functions
/// @return True if all tests were executed, false if not
bool FloatingTextTestSuite::TestCaseFontSetting()
{
    //------Last Checked------//
    // - Dec 7, 2004
    FloatingText floatingText;
    FontSetting fontSetting(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0));
    floatingText.SetFontSetting(fontSetting);
    TEST(wxT("SetFontSetting"), (floatingText.GetFontSetting() == fontSetting));
    TEST(wxT("SetFontSetting 2"), (floatingText.GetFontSettingRef() == fontSetting));
    TEST(wxT("SetFontSetting 3"), (floatingText.GetFontSettingConstRef() == fontSetting));
    return (true);
}
