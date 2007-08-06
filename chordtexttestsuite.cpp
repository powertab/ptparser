/////////////////////////////////////////////////////////////////////////////
// Name:            chordtexttestsuite.cpp
// Purpose:         Performs unit testing on the ChordText class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 3, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "chordtexttestsuite.h"
#include "chordtext.h"

#include "powertabfileheader.h"         // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(ChordTextTestSuite, TestSuite)

/// Default Constructor
ChordTextTestSuite::ChordTextTestSuite()
{
    //------Last Checked------//
    // - Jan 3, 2005
}

/// Destructor
ChordTextTestSuite::~ChordTextTestSuite()
{
    //------Last Checked------//
    // - Jan 3, 2005
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t ChordTextTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Jan 3, 2005
    return (528);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool ChordTextTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Jan 3, 2005
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseCreation())
        return (false);
    if (!TestCaseOperator())
        return (false);
    if (!TestCaseSerialize())
        return (false);
    if (!TestCasePosition())
        return (false);
    if (!TestCaseChordName())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool ChordTextTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 3, 2005
    
    ChordName chordName;
    chordName.SetFormula(ChordName::minor);
    
    // TEST CASE: Default constructor
    {
        ChordText chordText;
        TEST(wxT("Default Constructor"), 
            (chordText.GetPosition() == 0)
        );        
    }
    
    // TEST CASE: Primary constructor
    {
        ChordText chordText(12, chordName);
        TEST(wxT("Primary Constructor"), 
            (chordText.GetPosition() ==  12) &&
            (chordText.GetChordName() == chordName)
        );
    }
    
    // TEST CASE: Copy constructor
    {
        ChordText chordText(12, chordName);
        ChordText chordText2(chordText);
        TEST(wxT("Copy Constructor"), 
            (chordText2.GetPosition() == 12) &&
            (chordText2.GetChordName() == chordName)
        );
    }
    
    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool ChordTextTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 12, 2005
    ChordName chordName;
    chordName.SetFormula(ChordName::minor);
    
    ChordText chordText(12, chordName);
    ChordText* clone = (ChordText*)chordText.CloneObject();
    TEST(wxT("CloneObject"),
        (*clone == chordText)
    );
    delete clone;
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool ChordTextTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 3, 2005
    ChordName chordName;
    chordName.SetFormula(ChordName::minor);
    ChordName chordName2;
    chordName2.SetFormula(ChordName::augmented);
            
    // TEST CASE: Operator=
    {
        ChordText chordText(12, chordName);
        ChordText chordText2 = chordText;
        TEST(wxT("Operator="), 
            (chordText2.GetPosition() == 12) &&
            (chordText2.GetChordName() == chordName)
        );
        
        chordText = chordText;
        TEST(wxT("Operator= (self-assignment)"),
            (chordText == chordText)
        );
    }
    
    // TEST CASE: Operator==
    {
        ChordText chordText(12, chordName);
        ChordText chordText2(12, chordName);
        ChordText chordText3(13, chordName);
        ChordText chordText4(12, chordName2);
               
        TEST(wxT("Operator== - chordText == chordText"),
            (chordText == chordText2));
        TEST(wxT("Operator== - chordText != chordText"),
            !(chordText == chordText3));
        TEST(wxT("Operator== - chordText != chordText 2"),
            !(chordText == chordText4));
    }
        
    // TEST CASE: Operator!=
    {
        ChordText chordText(12, chordName);
        ChordText chordText2(12, chordName);
        ChordText chordText3(13, chordName);
        ChordText chordText4(12, chordName2);
               
        TEST(wxT("Operator!= - chordText == chordText"),
            !(chordText != chordText2));
        TEST(wxT("Operator!= - chordText != chordText"),
            (chordText != chordText3));
        TEST(wxT("Operator!= - chordText != chordText 2"),
            (chordText != chordText4));
    }

    return (true);
}

/// Tests the Serialization Fucntions
/// @return True if all tests were executed, false if not
bool ChordTextTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Jan 3, 2005
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    ChordText chordTextOut(12, ChordName());
    chordTextOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        ChordText chordTextIn;
        chordTextIn.Deserialize(streamIn,
            PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((chordTextIn == chordTextOut) 
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the Position Functions
/// @return True if all tests were executed, false if not
bool ChordTextTestSuite::TestCasePosition()
{
    //------Last Checked------//
    // - Jan 3, 2005
    ChordText chordText;
    
    // TEST CASE: IsValidPosition
    {
        wxUint32 i = 0;
        for (; i <= 256; i++)
        {
            TEST(wxString::Format(wxT("IsValidPosition - %d"), i),
                (ChordText::IsValidPosition(i) == (i < 256))
            );
        }
    }
    
    // TEST CASE: SetPosition
    {
        wxUint32 i = 0;
        for (; i <= 256; i++)
        {
            TEST(wxString::Format(wxT("SetPosition - %d"), i),
                (chordText.SetPosition(i) == (i < 256)) &&
                ((i == 256) ? 1 : (chordText.GetPosition() == i))
            );
        }
    }
    return (true);
}

/// Tests the Chord Name Functions
/// @return True if all tests were executed, false if not
bool ChordTextTestSuite::TestCaseChordName()
{
    //------Last Checked------//
    // - Jan 3, 2005
    ChordName chordName;
    chordName.SetFormula(ChordName::major6th);
    
    ChordText chordText;
    chordText.SetChordName(chordName);
    TEST(wxT("SetChordName"), (chordName == chordText.GetChordName()));
    return (true);
}
