/////////////////////////////////////////////////////////////////////////////
// Name:            chordnametestsuite.cpp
// Purpose:         Performs unit testing on the ChordName class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "chordnametestsuite.h"

#include "chordname.h"
#include "powertabfileheader.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(ChordNameTestSuite, TestSuite)

/// Default Constructor
ChordNameTestSuite::ChordNameTestSuite()
{
    //------Last Checked------//
    // - Jan 4, 2005
}

/// Destructor
ChordNameTestSuite::~ChordNameTestSuite()
{
    //------Last Checked------//
    // - Jan 4, 2005
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t ChordNameTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Jan 4, 2005
    return (243);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool ChordNameTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Jan 16, 2005
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseCreation())
        return (false);
    if (!TestCaseOperator())
        return (false);
    if (!TestCaseSerialize())
        return (false);
    if (!TestCaseTonic())
        return (false);
    if (!TestCaseBassNote())
        return (false);
    if (!TestCaseFormula())
        return (false);
    if (!TestCaseBrackets())
        return (false);
    if (!TestCaseNoChord())
        return (false);
    if (!TestCaseFormulaFlags())
        return (false);
    if (!TestCaseFormulaModifications())
        return (false);
    if (!TestCaseFretPosition())
        return (false);
    if (!TestCaseType())
        return (false);
        
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool ChordNameTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 17, 2005
    
    // TEST CASE: Default constructor
    {
        ChordName chordName;
        TEST(wxT("Default Constructor"), 
            (chordName.IsSameTonic(ChordName::C, ChordName::variationDefault)) &&
            (chordName.IsSameBassNote(ChordName::C, ChordName::variationDefault)) &&
            (chordName.GetFormula() == ChordName::major) &&
            (chordName.GetFormulaModificationsCount() == 0) &&
            (!chordName.IsFretPositionUsed()) &&
            (!chordName.IsTypeUsed())
        );        
    }
    
    // TEST CASE: Primary constructor
    {
        ChordName chordName(ChordName::D, ChordName::variationDefault,
            ChordName::dominant7th,
            ChordName::extended9th | ChordName::suspended4th, 3, 2);
        TEST(wxT("Primary Constructor"),
            (chordName.IsSameTonic(ChordName::D, ChordName::variationDefault)) &&
            (chordName.GetFormula() == ChordName::dominant7th) &&
            (chordName.GetFretPosition() == 3) &&
            (chordName.GetType() == 2)
        );
    }
    
    // TEST CASE: Copy constructor
    {
        ChordName chordName(ChordName::D, ChordName::variationDefault,
            ChordName::dominant7th,
            ChordName::extended9th | ChordName::suspended4th, 3, 2);
        ChordName chordName2(chordName);
        TEST(wxT("Copy Constructor"), 
            (chordName2 == chordName)
        );
    }
    
    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool ChordNameTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 17, 2005
    ChordName chordName(ChordName::D, ChordName::variationDefault,
        ChordName::dominant7th,
        ChordName::extended9th | ChordName::suspended4th, 3, 2);
    
    ChordName* clone = (ChordName*)chordName.CloneObject();
    TEST(wxT("CloneObject"),
        (*clone == chordName)
    );
    delete clone;
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool ChordNameTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 17, 2005
    
    // TEST CASE: Operator=
    {
        ChordName chordName(ChordName::D, ChordName::variationDefault,
            ChordName::dominant7th,
            ChordName::extended9th | ChordName::suspended4th, 3, 2);
        ChordName chordName2 = chordName;
        TEST(wxT("Operator="),
            (chordName2 == chordName)
        );
        
        chordName = chordName;
        TEST(wxT("Operator= (self-assignment)"),
            (chordName == chordName)
        );
    }
    
    // TEST CASE: Operator==
    {
        ChordName chordName(ChordName::D, ChordName::variationDefault,
            ChordName::dominant7th,
            ChordName::extended9th | ChordName::suspended4th, 3, 2);
        ChordName chordName2(ChordName::D, ChordName::variationDefault,
            ChordName::dominant7th,
            ChordName::extended9th | ChordName::suspended4th, 3, 2);
        ChordName chordName3(ChordName::EFlat, ChordName::variationDefault,
            ChordName::dominant7th,
            ChordName::extended9th | ChordName::suspended4th, 3, 2);
        ChordName chordName4(ChordName::D, ChordName::variationUp,
            ChordName::dominant7th,
            ChordName::extended9th | ChordName::suspended4th, 3, 2);
        ChordName chordName5(ChordName::D, ChordName::variationDefault,
            ChordName::major7th,
            ChordName::extended9th | ChordName::suspended4th, 3, 2);
        ChordName chordName6(ChordName::D, ChordName::variationDefault,
            ChordName::dominant7th, ChordName::extended11th, 3, 2);
        ChordName chordName7(ChordName::D, ChordName::variationDefault,
            ChordName::dominant7th,
            ChordName::extended9th | ChordName::suspended4th, 4, 2);
        ChordName chordName8(ChordName::D, ChordName::variationDefault,
            ChordName::dominant7th,
            ChordName::extended9th | ChordName::suspended4th, 3, 3);
        
        TEST(wxT("Operator== - chordName == chordName"),
            (chordName == chordName2));
        TEST(wxT("Operator== - chordName != chordName"),
            !(chordName == chordName3));
        TEST(wxT("Operator== - chordName != chordName 2"),
            !(chordName == chordName4));
        TEST(wxT("Operator== - chordName != chordName 3"),
            !(chordName == chordName5));
        TEST(wxT("Operator== - chordName != chordName 4"),
            !(chordName == chordName6));
        TEST(wxT("Operator== - chordName != chordName 5"),
            !(chordName == chordName7));
        TEST(wxT("Operator== - chordName != chordName 6"),
            !(chordName == chordName8));
    }
        
    // TEST CASE: Operator!=
    {
        ChordName chordName(ChordName::D, ChordName::variationDefault,
            ChordName::dominant7th,
            ChordName::extended9th | ChordName::suspended4th, 3, 2);
        ChordName chordName2(ChordName::D, ChordName::variationDefault,
            ChordName::dominant7th,
            ChordName::extended9th | ChordName::suspended4th, 3, 2);
        ChordName chordName3(ChordName::EFlat, ChordName::variationDefault,
            ChordName::dominant7th,
            ChordName::extended9th | ChordName::suspended4th, 3, 2);
        ChordName chordName4(ChordName::D, ChordName::variationUp,
            ChordName::dominant7th,
            ChordName::extended9th | ChordName::suspended4th, 3, 2);
        ChordName chordName5(ChordName::D, ChordName::variationDefault,
            ChordName::major7th,
            ChordName::extended9th | ChordName::suspended4th, 3, 2);
        ChordName chordName6(ChordName::D, ChordName::variationDefault,
            ChordName::dominant7th,
            ChordName::extended11th, 3, 2);
        ChordName chordName7(ChordName::D, ChordName::variationDefault,
            ChordName::dominant7th,
            ChordName::extended9th | ChordName::suspended4th, 4, 2);
        ChordName chordName8(ChordName::D, ChordName::variationDefault,
            ChordName::dominant7th,
            ChordName::extended9th | ChordName::suspended4th, 3, 3);
        
        TEST(wxT("Operator!= - chordName == chordName"),
            !(chordName != chordName2));
        TEST(wxT("Operator!= - chordName != chordName"),
            (chordName != chordName3));
        TEST(wxT("Operator!= - chordName != chordName 2"),
            (chordName != chordName4));
        TEST(wxT("Operator!= - chordName != chordName 3"),
            (chordName != chordName5));
        TEST(wxT("Operator!= - chordName != chordName 4"),
            (chordName != chordName6));
        TEST(wxT("Operator!= - chordName != chordName 5"),
            (chordName != chordName7));
        TEST(wxT("Operator!= - chordName != chordName 6"),
            (chordName != chordName8));
    }
    
    return (true);
}

/// Tests the Serialization Functions
/// @return True if all tests were executed, false if not
bool ChordNameTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Jan 17, 2005
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    ChordName chordNameOut(ChordName::D, ChordName::variationDefault,
        ChordName::dominant7th,
        ChordName::extended9th | ChordName::suspended4th, 3, 2);
    chordNameOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        ChordName chordNameIn;
        chordNameIn.Deserialize(streamIn,
            PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((chordNameIn == chordNameOut) 
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the Tonic Functions
/// @return True if all tests were executed, false if not
bool ChordNameTestSuite::TestCaseTonic()
{
    //------Last Checked------//
    // - Jan 17, 2005
    
    // TEST CASE: SetTonic
    {
        ChordName chordName;
        TEST(wxT("SetTonic - invalid key"), 
            (!chordName.SetTonic(255, ChordName::variationDefault))
        );
        TEST(wxT("SetTonic - invalid key variation"), 
            (!chordName.SetTonic(ChordName::AFlat, 255))
        );
        
        wxByte i = ChordName::C;
        for (; i <= ChordName::B; i++)
        {
            wxByte j = ChordName::variationDown;
            for (; j <= ChordName::variationUp; j++)
            {
                bool set = chordName.SetTonic(i,j);
                wxByte key = 0;
                wxByte keyVariation = 0;
                chordName.GetTonic(key, keyVariation);
                
                TEST(wxString::Format(wxT("SetTonic - %d, %d"), i, j), 
                    (set == !((i == ChordName::AFlat) &&
                    (j == ChordName::variationUp))) &&
                    (((i == ChordName::AFlat) &&
                    (j == ChordName::variationUp)) ? 1 : 
                    (key == i && keyVariation == j))
                );
            }
        }
    }
    return (true);
}

/// Tests the Bass Note Functions
/// @return True if all tests were executed, false if not
bool ChordNameTestSuite::TestCaseBassNote()
{
    //------Last Checked------//
    // - Jan 17, 2005
    
    // TEST CASE: SetBassNote
    {
        ChordName chordName;
        TEST(wxT("SetBassNote - invalid key"), 
            (!chordName.SetBassNote(255, ChordName::variationDefault))
        );
        TEST(wxT("SetBassNote - invalid key variation"), 
            (!chordName.SetBassNote(ChordName::AFlat, 255))
        );
        
        wxByte i = ChordName::C;
        for (; i <= ChordName::B; i++)
        {
            wxByte j = ChordName::variationDown;
            for (; j <= ChordName::variationUp; j++)
            {
                bool set = chordName.SetBassNote(i,j);
                wxByte key = 0;
                wxByte keyVariation = 0;
                chordName.GetBassNote(key, keyVariation);
                
                TEST(wxString::Format(wxT("SetBassNote - %d, %d"), i, j), 
                    (set == !((i == ChordName::AFlat) &&
                    (j == ChordName::variationUp))) &&
                    ((i == ChordName::AFlat) &&
                    (j == ChordName::variationUp)) ? 1 : 
                    (key == i && keyVariation == j)
                );
            }
        }
    }
    
    return (true);
}
    
/// Tests the Formula Functions
/// @return True if all tests were executed, false if not
bool ChordNameTestSuite::TestCaseFormula()
{
    //------Last Checked------//
    // - Jan 16, 2005
    
    // TEST CASE: IsValidFormula
    {
        wxByte i = ChordName::major;
        for (; i <= (ChordName::minor7thFlatted5th + 1); i++)
            TEST(wxString::Format(wxT("IsValidFormula - %d"), i),
                (ChordName::IsValidFormula(i) ==
                    (i <= ChordName::minor7thFlatted5th))
                );
    }
    
    // TEST CASE: SetFormula
    {
        ChordName chordName;
        wxByte i = ChordName::major;
        for (; i <= (ChordName::minor7thFlatted5th + 1); i++)
            TEST(wxString::Format(wxT("SetFormula - %d"), i),
                (chordName.SetFormula(i) ==
                    (i <= ChordName::minor7thFlatted5th)) &&
                ((i > ChordName::minor7thFlatted5th) ? 1 :
                    (chordName.GetFormula() == i))
            );
    }
    
    return (true);
}

/// Tests the Brackets Functions
/// @return True if all tests were executed, false if not
bool ChordNameTestSuite::TestCaseBrackets()
{
    //------Last Checked------//
    // - Jan 16, 2005
    ChordName chordName;
    TEST(wxT("SetBrackets - true"), 
        chordName.SetBrackets(true) &&
        chordName.HasBrackets()
    );
    
    chordName.SetBrackets(false);
    TEST(wxT("SetBrackets - false"), 
        chordName.SetBrackets(false) &&
        !chordName.HasBrackets()
    );
    
    return (true);
}

/// Tests the No Chord Functions
/// @return True if all tests were executed, false if not
bool ChordNameTestSuite::TestCaseNoChord()
{
    //------Last Checked------//
    // - Jan 16, 2005
    ChordName chordName;
    TEST(wxT("SetNoChord - true"), 
        chordName.SetNoChord(true) &&
        chordName.IsNoChord()
    );
    
    TEST(wxT("SetNoChord - false"), 
        chordName.SetNoChord(false) &&
        !chordName.IsNoChord()
    );
    return (true);
}
    
/// Tests the Formula Flag Functions
/// @return True if all tests were executed, false if not
bool ChordNameTestSuite::TestCaseFormulaFlags()
{
    //------Last Checked------//
    // - Jan 16, 2005
 
    // TEST CASE: IsValidFormulaFlag
    {
        wxByte i = 1;
        for (; i <= ChordName::tonicSharps; i *= 2)
        {
            TEST(wxString::Format(wxT("IsValidFormulaFlag - %d"), i),
                (ChordName::IsValidFormulaFlag(i) == (i >= ChordName::noChord))
            );
            
            // Must break due to overflow
            if (i == ChordName::tonicSharps)
                break;
        }
    }
    
    // TEST CASE: SetFormulaFlag
    {
        ChordName chordName;
    
        wxByte i = 1;
        for (; i <= ChordName::tonicSharps; i *= 2)
        {
            TEST(wxString::Format(wxT("SetFormulaFlag - %d"), i),
                (chordName.SetFormulaFlag(i) == (i >= ChordName::noChord)) &&
                ((i < ChordName::noChord) ? 1 : chordName.IsFormulaFlagSet(i)));
        
            TEST(wxString::Format(wxT("ClearFormulaFlag - %d"), i),
                (chordName.ClearFormulaFlag(i) == (i >= ChordName::noChord)) &&
                ((i < ChordName::noChord) ? 1 : !chordName.IsFormulaFlagSet(i)));
                
            // Must break due to overflow
            if (i == ChordName::tonicSharps)
                break;
        }
    }
    
    return (true);
}

/// Tests the Formula Modifications Functions
/// @return True if all tests were executed, false if not
bool ChordNameTestSuite::TestCaseFormulaModifications()
{
    //------Last Checked------//
    // - Jan 16, 2005
    
    // TEST CASE: SetFormulaModifications
    {
        ChordName chordName;
        chordName.SetFormulaModifications(
            ChordName::added2nd | ChordName::added4th);
        TEST(wxT("SetFormulaModifications"),
            (chordName.IsFormulaModificationFlagSet(ChordName::added2nd)) &&
            (chordName.IsFormulaModificationFlagSet(ChordName::added4th)) 
        );
    }
    
    // TEST CASE: GetFormulaModificationCount
    {
        ChordName chordName;
        TEST(wxT("GetFormulaModificationCount - zero"),
            (chordName.GetFormulaModificationsCount() == 0)
        );
        size_t i = 0;
        for (i = 0; i < 16; i++)
        {
            wxWord flag = (wxWord)pow((double)2,(double)i);
            chordName.SetFormulaModificationFlag(flag);
            TEST(wxString::Format(wxT("GetFormulaModificationCount - %d"),
                i + 1),
                (chordName.GetFormulaModificationsCount() == (i + 1))
            );
        }
    }
    
    // TEST CASE: ClearFormulaModifications
    {
        ChordName chordName;
        chordName.SetFormulaModifications(
            ChordName::added2nd | ChordName::added4th);
        chordName.ClearFormulaModifications();
        TEST(wxT("ClearFormulaModifications"),
            (chordName.GetFormulaModificationsCount() == 0)
        );
    }

    // TEST CASE: SetFormulaModificationFlag
    {
        ChordName chordName;
    
        wxWord i = ChordName::extended9th;
        for (; i <= ChordName::suspended4th; i = 2 * i)
        {
            chordName.SetFormulaModificationFlag(i);
            TEST(wxString::Format(wxT("SetFormulaModificationFlag - %d"), i),
                (chordName.IsFormulaModificationFlagSet(i))
            );
        
            chordName.ClearFormulaModificationFlag(i);
            TEST(wxString::Format(wxT("ClearFormulaModificationFlag - %d"), i),
                !(chordName.IsFormulaModificationFlagSet(i))
            );
            
            // Must break due to overflow
            if (i == ChordName::suspended4th)
                break;
        }
    }
    
    return (true);
}

/// Tests the Fret Position Functions
/// @return True if all tests were executed, false if not
bool ChordNameTestSuite::TestCaseFretPosition()
{
    //------Last Checked------//
    // - Jan 4, 2005
    ChordName chordName;
    wxByte i = ChordName::MIN_FRET_POSITION;
    for (; i <= (ChordName::MAX_FRET_POSITION + 1); i++)
    {
        TEST(wxString::Format(wxT("SetFretPosition - %d"), i),
            (chordName.SetFretPosition(i) ==
            (i <= ChordName::MAX_FRET_POSITION)) &&
            ((i > ChordName::MAX_FRET_POSITION) ? 1 :
                ((chordName.GetFretPosition() == i) &&
                (chordName.IsFretPositionUsed())))
        );
    }
    TEST(wxT("SetFretPosition - not used"), 
        (chordName.SetFretPosition(ChordName::fretPositionNotUsed)) &&
        (chordName.GetFretPosition() == ChordName::fretPositionNotUsed) &&
        (!chordName.IsFretPositionUsed())
    );
    
    return (true);
}

/// Tests the Type Functions
/// @return True if all tests were executed, false if not
bool ChordNameTestSuite::TestCaseType()
{
    //------Last Checked------//
    // - Jan 4, 2005
    ChordName chordName;
    wxByte i = ChordName::MIN_TYPE - 1;
    for (; i <= (ChordName::MAX_TYPE + 1); i++)
    {
        TEST(wxString::Format(wxT("GetType - %d"), i),
            (chordName.SetType(i) == ((i >= ChordName::MIN_TYPE) &&
            (i <= ChordName::MAX_TYPE))) &&
            (((i < ChordName::MIN_TYPE) || (i > ChordName::MAX_TYPE)) ? 1 :
            ((chordName.GetType() == i) && (chordName.IsTypeUsed())))
        );
    }
    TEST(wxT("SetType - not used"),
        (chordName.SetType(ChordName::typeNotUsed)) &&
        (chordName.GetType() == ChordName::typeNotUsed) &&
        (!chordName.IsTypeUsed())
    );
    return (true);
}
