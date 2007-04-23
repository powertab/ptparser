/////////////////////////////////////////////////////////////////////////////
// Name:            powertabdocumenttestsuite.cpp
// Purpose:         Performs unit testing on the PowerTabDocument class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 27, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "powertabdocumenttestsuite.h"

#include "powertabdocument.h"
#include "powertabfileheader.h"         // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(PowerTabDocumentTestSuite, TestSuite)

/// Default Constructor
PowerTabDocumentTestSuite::PowerTabDocumentTestSuite()
{
    //------Last Checked------//
    // - Jan 27, 2005
}

/// Destructor
PowerTabDocumentTestSuite::~PowerTabDocumentTestSuite()
{
    //------Last Checked------//
    // - Jan 27, 2005
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t PowerTabDocumentTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Jan 27, 2005
    return (27);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool PowerTabDocumentTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Jan 27, 2005
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseScore())
        return (false);
    if (!TestCaseChordNameFontSetting())
        return (false);
    if (!TestCaseSetTablatureNumbersFontSetting())
        return (false);
    if (!TestCaseFadeIn())
        return (false);
    if (!TestCaseFadeOut())
        return (false);
    if (!TestCaseTablatureStaffLineSpacing())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool PowerTabDocumentTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 27, 2005
        
    // TEST CASE: Default constructor
    {
        PowerTabDocument powerTabDocument;
        TEST(wxT("Default Constructor"), 
            (powerTabDocument.m_tablatureStaffLineSpacing == PowerTabDocument::DEFAULT_TABLATURE_STAFF_LINE_SPACING) &&
            (powerTabDocument.m_fadeIn == PowerTabDocument::DEFAULT_FADE_IN) &&
            (powerTabDocument.m_fadeOut == PowerTabDocument::DEFAULT_FADE_OUT)
        );        
    }
        
    return (true);
}

/// Tests the Score Functions
/// @return True if all tests were executed, false if not
bool PowerTabDocumentTestSuite::TestCaseScore()
{
    //------Last Checked------//
    // - Jan 27, 2005
    PowerTabDocument document;
    TEST(wxT("GetGuitarScore - invalid"),
        (document.GetGuitarScore() == NULL)
    );
    TEST(wxT("GetBassScore - invalid"),
        (document.GetBassScore() == NULL)
    );
    return (true);
}

/// Tests the Chord Name Font Setting Functions
/// @return True if all tests were executed, false if not
bool PowerTabDocumentTestSuite::TestCaseChordNameFontSetting()
{
    //------Last Checked------//
    // - Jan 27, 2005
    PowerTabDocument document;
    FontSetting fontSetting(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColour(25,25,25));
    document.SetChordNameFontSetting(fontSetting);
    TEST(wxT("SetChordNameFontSetting"),
        (document.GetChordNameFontSettingConstRef() == fontSetting)
    );
    
    return (true);
}

/// Tests the Tablature Numbers Font Setting Functions
/// @return True if all tests were executed, false if not
bool PowerTabDocumentTestSuite::TestCaseSetTablatureNumbersFontSetting()
{
    //------Last Checked------//
    // - Jan 27, 2005
    PowerTabDocument document;
    FontSetting fontSetting(wxT("Arial"), 12, FontSetting::weightBold, true, true, true, wxColour(25,25,25));
    document.SetTablatureNumbersFontSetting(fontSetting);
    TEST(wxT("SetTablatureNumbersFontSetting"),
        (document.GetTablatureNumbersFontSettingConstRef() == fontSetting)
    );

    return (true);
}

/// Tests the Tablature Staff Line Spacing Functions
/// @return True if all tests were executed, false if not
bool PowerTabDocumentTestSuite::TestCaseTablatureStaffLineSpacing()
{
    //------Last Checked------//
    // - Jan 27, 2005
    
    // TEST CASE: IsValidTablatureStaffLineSpacing
    {
        wxInt32 i = PowerTabDocument::MIN_TABLATURE_STAFF_LINE_SPACING - 1;
        for (; i < (PowerTabDocument::MAX_TABLATURE_STAFF_LINE_SPACING + 1); i++)
        {
            TEST(wxString::Format(wxT("IsValidTablatureStaffLineSpacing - %d"), i),
                (PowerTabDocument::IsValidTablatureStaffLineSpacing(i) == 
                    ((i >= PowerTabDocument::MIN_TABLATURE_STAFF_LINE_SPACING) && (PowerTabDocument::MAX_TABLATURE_STAFF_LINE_SPACING)))
            );
        }
    }
    
    PowerTabDocument document;
    {
        wxInt32 i = PowerTabDocument::MIN_TABLATURE_STAFF_LINE_SPACING - 1;
        for (; i < (PowerTabDocument::MAX_TABLATURE_STAFF_LINE_SPACING + 1); i++)
        {
            TEST(wxString::Format(wxT("SetTablatureStaffLineSpacing - %d"), i),
                (document.SetTablatureStaffLineSpacing(i) == 
                    ((i >= PowerTabDocument::MIN_TABLATURE_STAFF_LINE_SPACING) && (i <= PowerTabDocument::MAX_TABLATURE_STAFF_LINE_SPACING))) &&
                    ((i < PowerTabDocument::MIN_TABLATURE_STAFF_LINE_SPACING) || (i > PowerTabDocument::MAX_TABLATURE_STAFF_LINE_SPACING)) ?
                    1 : 
                    (document.GetTablatureStaffLineSpacing() == i)
            );
        }
    }
    return (true);
}

/// Tests the Fade In Functions
/// @return True if all tests were executed, false if not
bool PowerTabDocumentTestSuite::TestCaseFadeIn()
{
    //------Last Checked------//
    // - Jan 27, 2005
    PowerTabDocument document;
    document.SetFadeIn(1000);
    TEST(wxT("SetFadeIn"),
        (document.GetFadeIn() == 1000)
    );
    return (true);
}

/// Tests the Fade Out Functions
/// @return True if all tests were executed, false if not
bool PowerTabDocumentTestSuite::TestCaseFadeOut()
{
    //------Last Checked------//
    // - Jan 27, 2005
    
    PowerTabDocument document;
    document.SetFadeOut(2000);
    TEST(wxT("SetFadeOut"),
        (document.GetFadeOut() == 2000)
    );
    return (true);
}
