/////////////////////////////////////////////////////////////////////////////
// Name:            fontsettingtestsuite.cpp
// Purpose:         Performs unit testing on the FontSetting class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 7, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "fontsettingtestsuite.h"

#include "fontsetting.h"
#include "powertabfileheader.h"         // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(FontSettingTestSuite, TestSuite)

/// Default Constructor
FontSettingTestSuite::FontSettingTestSuite()
{
    //------Last Checked------//
    // - Dec 6, 2004
}

/// Destructor
FontSettingTestSuite::~FontSettingTestSuite()
{
    //------Last Checked------//
    // - Dec 6, 2004
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t FontSettingTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Dec 6, 2004
    return (79);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool FontSettingTestSuite::RunTestCases()
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
    if (!TestCaseSetFontSetting())
        return (false);
    if (!TestCaseSetFontSettingFromString())
        return (false);
    if (!TestCaseFaceName())
        return (false);
    if (!TestCasePointSize())
        return (false);
    if (!TestCaseWeight())
        return (false);
    if (!TestCaseItalic())
        return (false);
    if (!TestCaseUnderline())
        return (false);
    if (!TestCaseStrikeOut())
        return (false);
    if (!TestCaseColor())
        return (false);
    return (true);
}

// Test Case Functions
/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool FontSettingTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Dec 6, 2004
    
    // TEST CASE: Default constructor
    {
        FontSetting fontSetting;
        TEST(wxT("Default Constructor"), 
            (fontSetting.GetFaceName() == FontSetting::DEFAULT_FACENAME) &&
            (fontSetting.GetPointSize() == FontSetting::DEFAULT_POINTSIZE) &&
            (fontSetting.GetWeight() == FontSetting::DEFAULT_WEIGHT) &&
            (fontSetting.IsItalic() == FontSetting::DEFAULT_ITALIC) &&
            (fontSetting.IsUnderline() == FontSetting::DEFAULT_UNDERLINE) &&
            (fontSetting.IsStrikeOut() == FontSetting::DEFAULT_STRIKEOUT) &&
            (fontSetting.GetColor() == FontSetting::DEFAULT_COLOR)
        );        
    }
    
    // TEST CASE: Primary constructor
    {
        FontSetting fontSetting(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0));
        TEST(wxT("Primary Constructor"), 
            (fontSetting.GetFaceName() == wxT("Arial")) &&
            (fontSetting.GetPointSize() == 12) &&
            (fontSetting.GetWeight() == FontSetting::weightBold) &&
            (fontSetting.IsItalic()) &&
            (fontSetting.IsUnderline()) &&
            (fontSetting.IsStrikeOut()) &&
            (fontSetting.GetColor() == wxColor(255,0,0))
        );
    }
    
    // TEST CASE: Copy constructor
    {
        FontSetting fontSetting(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0));
        FontSetting fontSetting2(fontSetting);
        TEST(wxT("Copy Constructor"), 
            (fontSetting2.GetFaceName() == wxT("Arial")) &&
            (fontSetting2.GetPointSize() == 12) &&
            (fontSetting2.GetWeight() == FontSetting::weightBold) &&
            (fontSetting2.IsItalic()) &&
            (fontSetting2.IsUnderline()) &&
            (fontSetting2.IsStrikeOut()) &&
            (fontSetting2.GetColor() == wxColor(255,0,0))
        );
    }
    
    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool FontSettingTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 12, 2005
    FontSetting fontSetting(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0));
    FontSetting* clone = (FontSetting*)fontSetting.CloneObject();
    TEST(wxT("CloneObject"),
        (*clone == fontSetting)
    );
    delete clone;
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool FontSettingTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Dec 6, 2004
    
    // TEST CASE: Operator =
	{
	    FontSetting fontSetting(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0));
        FontSetting fontSetting2 = fontSetting;
        TEST(wxT("Operator="), 
            (fontSetting2.GetFaceName() == wxT("Arial")) &&
            (fontSetting2.GetPointSize() == 12) &&
            (fontSetting2.GetWeight() == FontSetting::weightBold) &&
            (fontSetting2.IsItalic()) &&
            (fontSetting2.IsUnderline()) &&
            (fontSetting2.IsStrikeOut()) &&
            (fontSetting2.GetColor() == wxColor(255,0,0))
        );
            
		// TEST CASE: Self assignment
		{
		    FontSetting fontSetting(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0));
            fontSetting = fontSetting;
            TEST(wxT("Operator= (self-assignment)"), 
                (fontSetting.GetFaceName() == wxT("Arial")) &&
                (fontSetting.GetPointSize() == 12) &&
                (fontSetting.GetWeight() == FontSetting::weightBold) &&
                (fontSetting.IsItalic()) &&
                (fontSetting.IsUnderline()) &&
                (fontSetting.IsStrikeOut()) &&
                (fontSetting.GetColor() == wxColor(255,0,0))
            );
        }
    }

	// TEST CASE: Operator==
	{
	    FontSetting fontSetting(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0));
	    FontSetting fontSetting2(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0));
	    FontSetting fontSetting3(wxT("Times New Roman"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0));
	    FontSetting fontSetting4(wxT("Arial"), 11, FontSetting::weightBold, true, true, true, wxColor(255,0,0));
	    FontSetting fontSetting5(wxT("Arial"), 12, FontSetting::weightNormal, true, true, true, wxColor(255,0,0));
	    FontSetting fontSetting6(wxT("Arial"), 12, FontSetting::weightBold, false, true, true, wxColor(255,0,0));
	    FontSetting fontSetting7(wxT("Arial"), 12, FontSetting::weightBold, true, false, true, wxColor(255,0,0));
	    FontSetting fontSetting8(wxT("Arial"), 12, FontSetting::weightBold, true, true, false, wxColor(255,0,0));
	    FontSetting fontSetting9(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColor(254,0,0));
	    
		// TEST CASE: fontSetting == fontSetting
		TEST(wxT("Operator== - fontSetting == fontSetting"), (fontSetting == fontSetting2));
		TEST(wxT("Operator== - fontSetting != fontSetting"), !(fontSetting == fontSetting3));
		TEST(wxT("Operator== - fontSetting != fontSetting 2"), !(fontSetting == fontSetting4));
		TEST(wxT("Operator== - fontSetting != fontSetting 3"), !(fontSetting == fontSetting5));
		TEST(wxT("Operator== - fontSetting != fontSetting 4"), !(fontSetting == fontSetting6));
		TEST(wxT("Operator== - fontSetting != fontSetting 5"), !(fontSetting == fontSetting7));
		TEST(wxT("Operator== - fontSetting != fontSetting 6"), !(fontSetting == fontSetting8));
		TEST(wxT("Operator== - fontSetting != fontSetting 7"), !(fontSetting == fontSetting9));
	}

	// TEST CASE: Operator!=
	{
	    FontSetting fontSetting(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0));
	    FontSetting fontSetting2(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0));
	    FontSetting fontSetting3(wxT("Times New Roman"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0));
	    FontSetting fontSetting4(wxT("Arial"), 11, FontSetting::weightBold, true, true, true, wxColor(255,0,0));
	    FontSetting fontSetting5(wxT("Arial"), 12, FontSetting::weightNormal, true, true, true, wxColor(255,0,0));
	    FontSetting fontSetting6(wxT("Arial"), 12, FontSetting::weightBold, false, true, true, wxColor(255,0,0));
	    FontSetting fontSetting7(wxT("Arial"), 12, FontSetting::weightBold, true, false, true, wxColor(255,0,0));
	    FontSetting fontSetting8(wxT("Arial"), 12, FontSetting::weightBold, true, true, false, wxColor(255,0,0));
	    FontSetting fontSetting9(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColor(254,0,0));
	    
		// TEST CASE: fontSetting == fontSetting
		TEST(wxT("Operator!= - fontSetting == fontSetting"), !(fontSetting != fontSetting2));
		TEST(wxT("Operator!= - fontSetting != fontSetting"), (fontSetting != fontSetting3));
		TEST(wxT("Operator!= - fontSetting != fontSetting 2"), (fontSetting != fontSetting4));
		TEST(wxT("Operator!= - fontSetting != fontSetting 3"), (fontSetting != fontSetting5));
		TEST(wxT("Operator!= - fontSetting != fontSetting 4"), (fontSetting != fontSetting6));
		TEST(wxT("Operator!= - fontSetting != fontSetting 5"), (fontSetting != fontSetting7));
		TEST(wxT("Operator!= - fontSetting != fontSetting 6"), (fontSetting != fontSetting8));
		TEST(wxT("Operator!= - fontSetting != fontSetting 7"), (fontSetting != fontSetting9));
	}
	    
    return (true);
}

/// Tests Serialization
/// @return True if all tests were executed, false if not
bool FontSettingTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Dec 6, 2004
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    FontSetting fontSettingOut(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0));
    fontSettingOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        FontSetting fontSettingIn;
        fontSettingIn.Deserialize(streamIn, PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((fontSettingIn == fontSettingOut) 
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}    

/// Tests the SetFontSetting Function
/// @return True if all tests were executed, false if not
bool FontSettingTestSuite::TestCaseSetFontSetting()
{
    //------Last Checked------//
    // - Dec 6, 2004
    FontSetting fontSetting;
    
    TEST(wxT("SetFontSetting - NULL facename"), 
        !fontSetting.SetFontSetting(NULL, 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0)));
    TEST(wxT("SetFontSetting - invalid point size"), 
        !fontSetting.SetFontSetting(wxT("Arial"), 0, FontSetting::weightBold, true, true, true, wxColor(255,0,0)));
    TEST(wxT("SetFontSetting - invalid weight"), 
        !fontSetting.SetFontSetting(wxT("Arial"), 12, 139, true, true, true, wxColor(255,0,0)));
   
    TEST(wxT("SetFontSetting - valid"),
        fontSetting.SetFontSetting(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColor(255,0,0)) &&
        (fontSetting.GetFaceName() == wxT("Arial")) &&
        (fontSetting.GetPointSize() == 12) &&
        (fontSetting.GetWeight() == FontSetting::weightBold) &&
        (fontSetting.IsItalic()) &&
        (fontSetting.IsUnderline()) &&
        (fontSetting.IsStrikeOut()) &&
        (fontSetting.GetColor() == wxColor(255,0,0))
    );
    
    return (true);
}

/// Tests the SetFontSettingFromString Function
/// @return True if all tests were executed, false if not
bool FontSettingTestSuite::TestCaseSetFontSettingFromString()
{
    //------Last Checked------//
    // - Dec 6, 2004
    FontSetting fontSetting;
    TEST(wxT("SetFontSettingFromString - NULL string"), !fontSetting.SetFontSettingFromString(NULL));
    
    // String format = comma delimited: FaceName,PointSize,Weight,Italic(T/F),Underline(T/F),StrikeOut(T/F),Color
    TEST(wxT("SetFontSettingFromString - valid string"),
        fontSetting.SetFontSettingFromString(wxT("Arial,12,700,T,T,F,255")) && 
        (fontSetting.GetFaceName() == wxT("Arial")) &&
        (fontSetting.GetPointSize() == 12) &&
        (fontSetting.GetWeight() == FontSetting::weightBold) &&
        (fontSetting.IsItalic()) &&
        (fontSetting.IsUnderline()) &&
        (!fontSetting.IsStrikeOut()) &&
        (fontSetting.GetColor() == wxColor(255,0,0))
    );
    
    return (true);
}

/// Tests the FaceName Functions
/// @return True if all tests were executed, false if not
bool FontSettingTestSuite::TestCaseFaceName()
{
    //------Last Checked------//
    // - Dec 6, 2004
    FontSetting fontSetting;
    TEST(wxT("SetFaceName - NULL"), (!fontSetting.SetFaceName(NULL)));
    TEST(wxT("SetFaceName - Arial"), ((fontSetting.SetFaceName(wxT("Arial"))) && (fontSetting.GetFaceName() == wxT("Arial"))));
    return (true);
}

/// Tests the PointSize Functions
/// @return True if all tests were executed, false if not
bool FontSettingTestSuite::TestCasePointSize()
{
    //------Last Checked------//
    // - Dec 6, 2004
    
    const int testValueCount = 5;
    wxInt32 testValues[testValueCount];
    testValues[0] = FontSetting::MIN_POINTSIZE - 1;
    testValues[1] = FontSetting::MIN_POINTSIZE;
    testValues[2] = 12;
    testValues[3] = FontSetting::MAX_POINTSIZE;
    testValues[4] = FontSetting::MAX_POINTSIZE + 1;
    bool expectedResults[testValueCount];
    expectedResults[0] = false;
    expectedResults[1] = true;
    expectedResults[2] = true;
    expectedResults[3] = true;
    expectedResults[4] = false;
    
    int i = 0;
    for (; i < testValueCount; i++)
    {
        TEST(wxString::Format(wxT("IsValidPointSize - %d"), testValues[i]), (FontSetting::IsValidPointSize(testValues[i]) == expectedResults[i]));
        
        FontSetting fontSetting;
        TEST(wxString::Format(wxT("SetPointSize - %d"), testValues[i]), 
            (fontSetting.SetPointSize(testValues[i]) == expectedResults[i]) &&
            ((!expectedResults[i]) ? 1 : (fontSetting.GetPointSize() == testValues[i]))
        );
    }
        
    return (true);
}

/// Tests the Weight Functions
/// @return True if all tests were executed, false if not
bool FontSettingTestSuite::TestCaseWeight()
{
    //------Last Checked------//
    // - Dec 6, 2004
    
    const int testValueCount = 17;
    wxInt32 testValues[testValueCount];
    testValues[0] = FontSetting::weightDontCare;
    testValues[1] = FontSetting::weightThin;
    testValues[2] = FontSetting::weightExtraLight;
    testValues[3] = FontSetting::weightUltraLight;
    testValues[4] = FontSetting::weightLight;
    testValues[5] = FontSetting::weightNormal;
    testValues[6] = FontSetting::weightRegular;
    testValues[7] = FontSetting::weightMedium;
    testValues[8] = FontSetting::weightSemiBold;
    testValues[9] = FontSetting::weightDemiBold;
    testValues[10] = FontSetting::weightBold;
    testValues[11] = FontSetting::weightExtraBold;
    testValues[12] = FontSetting::weightUltraBold;
    testValues[13] = FontSetting::weightBlack;
    testValues[14] = FontSetting::weightHeavy;
    testValues[15] = -1;
    testValues[16] = 139;
        
    bool expectedResults[testValueCount];
    expectedResults[0] = true;
    expectedResults[1] = true;
    expectedResults[2] = true;
    expectedResults[3] = true;
    expectedResults[4] = true;
    expectedResults[5] = true;
    expectedResults[6] = true;
    expectedResults[7] = true;
    expectedResults[8] = true;
    expectedResults[9] = true;
    expectedResults[10] = true;
    expectedResults[11] = true;
    expectedResults[12] = true;
    expectedResults[13] = true;
    expectedResults[14] = true;
    expectedResults[15] = false;
    expectedResults[16] = false;
    
    int i = 0;
    for (; i < testValueCount; i++)
    {
        TEST(wxString::Format(wxT("IsValidWeight - %d"), testValues[i]), (FontSetting::IsValidWeight(testValues[i]) == expectedResults[i]));
        
        FontSetting fontSetting;
        TEST(wxString::Format(wxT("SetWeight - %d"), testValues[i]), 
            (fontSetting.SetWeight(testValues[i]) == expectedResults[i]) &&
            ((!expectedResults[i]) ? 1 : (fontSetting.GetWeight() == testValues[i]))
        );
    }

    return (true);
}

/// Tests the Italic Functions
/// @return True if all tests were executed, false if not
bool FontSettingTestSuite::TestCaseItalic()
{
    //------Last Checked------//
    // - Dec 6, 2004
    FontSetting fontSetting;
    fontSetting.SetItalic();
    TEST(wxT("SetItalic"), (fontSetting.IsItalic()));
    return (true);
}

/// Tests the Underline Functions
/// @return True if all tests were executed, false if not
bool FontSettingTestSuite::TestCaseUnderline()
{
    //------Last Checked------//
    // - Dec 6, 2004
    FontSetting fontSetting;
    fontSetting.SetUnderline();
    TEST(wxT("SetUnderline"), (fontSetting.IsUnderline()));
    return (true);
}

/// Tests the StrikeOut Functions
/// @return True if all tests were executed, false if not
bool FontSettingTestSuite::TestCaseStrikeOut()
{
    //------Last Checked------//
    // - Dec 6, 2004
    FontSetting fontSetting;
    fontSetting.SetStrikeOut();
    TEST(wxT("SetStrikeOut"), (fontSetting.IsStrikeOut()));
    return (true);
}

/// Tests the Color Functions
/// @return True if all tests were executed, false if not
bool FontSettingTestSuite::TestCaseColor()
{
    //------Last Checked------//
    // - Dec 6, 2004
    FontSetting fontSetting;
    fontSetting.SetColor(wxColor(255,255,255));
    TEST(wxT("SetColor"), (fontSetting.GetColor() == wxColor(255,255,255)));
    return (true);
}
