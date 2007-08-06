/////////////////////////////////////////////////////////////////////////////
// Name:            chorddiagramtestsuite.cpp
// Purpose:         Performs unit testing on the ChordDiagram class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 12, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "chorddiagramtestsuite.h"

#include "chorddiagram.h"
#include "powertabfileheader.h"         // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(ChordDiagramTestSuite, TestSuite)

/// Default Constructor
ChordDiagramTestSuite::ChordDiagramTestSuite()
{
    //------Last Checked------//
    // - Jan 16, 2005
}

/// Destructor
ChordDiagramTestSuite::~ChordDiagramTestSuite()
{
    //------Last Checked------//
    // - Jan 16, 2005
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t ChordDiagramTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Jan 16, 2005
    return (140);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool ChordDiagramTestSuite::RunTestCases()
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
    if (!TestCaseChordDiagram())
        return (false);
    if (!TestCaseChordName())
        return (false);
    if (!TestCaseTopFret())
        return (false);
    if (!TestCaseString())
        return (false);
    if (!TestCaseFretNumber())
        return (false);
    if (!TestCaseVoicing())
        return (false);
    if (!TestCaseOperations())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool ChordDiagramTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 15, 2005
    
    ChordName chordName;
    chordName.SetFormula(ChordName::minor);
    
    // TEST CASE: Default Constructor
    {
        ChordDiagram chordDiagram;
        TEST(wxT("Default Constructor"),
            (chordDiagram.GetTopFret() == ChordDiagram::DEFAULT_TOP_FRET) &&
            (chordDiagram.GetStringCount() == 0)
        );
    }
    
    // TEST CASE: Primary Constructor
    {
        ChordDiagram chordDiagram(chordName, 3, 3, 4, 5, 5, 3,
            ChordDiagram::stringMuted);
        TEST(wxT("Primary Constructor"),
            (chordDiagram.GetChordName() == chordName) &&
            (chordDiagram.GetTopFret() == 3) &&
            (chordDiagram.IsSameVoicing(3,4,5,5,3,ChordDiagram::stringMuted))
        );
    }
    
    // TEST CASE: Secondary Constructor
    {
        ChordDiagram chordDiagram(3, 3, 4, 5, 5, 3, ChordDiagram::stringMuted);
        TEST(wxT("Secondary Constructor"),
            (chordDiagram.GetTopFret() == 3) &&
            (chordDiagram.IsSameVoicing(3,4,5,5,3,ChordDiagram::stringMuted))
        );
    }
    
    // TEST CASE: Copy Constructor
    {
        ChordDiagram chordDiagram(chordName, 3, 3, 4, 5, 5, 3,
            ChordDiagram::stringMuted);        
        ChordDiagram chordDiagram2(chordDiagram);
        TEST(wxT("Copy Constructor"),
            (chordDiagram2 == chordDiagram)
        );
    }
        
    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool ChordDiagramTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 15, 2005
    
    ChordName chordName;
    chordName.SetFormula(ChordName::minor);
    
    ChordDiagram chordDiagram(chordName, 3, 3, 4, 5, 5, 3,
        ChordDiagram::stringMuted);
    ChordDiagram* clone = (ChordDiagram*)chordDiagram.CloneObject();
    TEST(wxT("CloneObject"),
        (*clone == chordDiagram)
    );
    delete clone;
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool ChordDiagramTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 15, 2005
    ChordName chordName;
    chordName.SetFormula(ChordName::minor);
    ChordName chordName2;
    chordName2.SetFormula(ChordName::augmented);
            
    // TEST CASE: Operator=
    {
        ChordDiagram chordDiagram(chordName, 3, 3, 4, 5, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram2 = chordDiagram;
        TEST(wxT("Copy Constructor"), 
            (chordDiagram2 == chordDiagram)
        );
        
        // TEST CASE: Operator= (self-assignment)
        chordDiagram = chordDiagram;
        TEST(wxT("Operator= (self-assignment)"),
            (chordDiagram == chordDiagram)
        );
    }
    
    // TEST CASE: Operator==
    {
        ChordDiagram chordDiagram(chordName, 3, 3, 4, 5, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram2(chordName, 3, 3, 4, 5, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram3(chordName2, 3, 3, 4, 5, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram4(chordName, 2, 3, 4, 5, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram5(chordName, 3, 4, 4, 5, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram6(chordName, 3, 3, 5, 5, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram7(chordName, 3, 3, 4, 6, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram8(chordName, 3, 3, 4, 5, 6, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram9(chordName, 3, 3, 4, 5, 5, 4,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram10(chordName, 3, 3, 4, 5, 5, 3, 3);
        ChordDiagram chordDiagram11(chordName, 3, 3, 4, 5);
        ChordDiagram chordDiagram12(chordName, 3, 3, 4, 5, 5);
        ChordDiagram chordDiagram13(chordName, 3, 3, 4, 5, 5, 3);
        ChordDiagram chordDiagram14(chordName, 3, 3, 4, 5, 5, 3, 3, 3);
        
        TEST(wxT("Operator== - chordDiagram == chordDiagram"),
            (chordDiagram == chordDiagram2));
        TEST(wxT("Operator== - chordDiagram != chordDiagram"),
            !(chordDiagram == chordDiagram3));
        TEST(wxT("Operator== - chordDiagram != chordDiagram 2"),
            !(chordDiagram == chordDiagram4));
        TEST(wxT("Operator== - chordDiagram != chordDiagram 3"),
            !(chordDiagram == chordDiagram5));
        TEST(wxT("Operator== - chordDiagram != chordDiagram 4"),
            !(chordDiagram == chordDiagram6));
        TEST(wxT("Operator== - chordDiagram != chordDiagram 5"),
            !(chordDiagram == chordDiagram7));
        TEST(wxT("Operator== - chordDiagram != chordDiagram 6"),
            !(chordDiagram == chordDiagram8));
        TEST(wxT("Operator== - chordDiagram != chordDiagram 7"),
            !(chordDiagram == chordDiagram9));
        TEST(wxT("Operator== - chordDiagram != chordDiagram 8"),
            !(chordDiagram == chordDiagram10));
        TEST(wxT("Operator== - chordDiagram != chordDiagram 9"),
            !(chordDiagram == chordDiagram11));
        TEST(wxT("Operator== - chordDiagram != chordDiagram 10"),
            !(chordDiagram == chordDiagram12));
        TEST(wxT("Operator== - chordDiagram != chordDiagram 11"),
            !(chordDiagram == chordDiagram13));
        TEST(wxT("Operator== - chordDiagram != chordDiagram 12"),
            !(chordDiagram == chordDiagram14));
    }
        
    // TEST CASE: Operator!=
    {
        ChordDiagram chordDiagram(chordName, 3, 3, 4, 5, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram2(chordName, 3, 3, 4, 5, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram3(chordName2, 3, 3, 4, 5, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram4(chordName, 2, 3, 4, 5, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram5(chordName, 3, 4, 4, 5, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram6(chordName, 3, 3, 5, 5, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram7(chordName, 3, 3, 4, 6, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram8(chordName, 3, 3, 4, 5, 6, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram9(chordName, 3, 3, 4, 5, 5, 4,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram10(chordName, 3, 3, 4, 5, 5, 3, 3);
        ChordDiagram chordDiagram11(chordName, 3, 3, 4, 5);
        ChordDiagram chordDiagram12(chordName, 3, 3, 4, 5, 5);
        ChordDiagram chordDiagram13(chordName, 3, 3, 4, 5, 5, 3);
        ChordDiagram chordDiagram14(chordName, 3, 3, 4, 5, 5, 3, 3, 3);
        
        TEST(wxT("Operator!= - chordDiagram == chordDiagram"),
            !(chordDiagram != chordDiagram2));
        TEST(wxT("Operator!= - chordDiagram != chordDiagram"),
            (chordDiagram != chordDiagram3));
        TEST(wxT("Operator!= - chordDiagram != chordDiagram 2"),
            (chordDiagram != chordDiagram4));
        TEST(wxT("Operator!= - chordDiagram != chordDiagram 3"),
            (chordDiagram != chordDiagram5));
        TEST(wxT("Operator!= - chordDiagram != chordDiagram 4"),
            (chordDiagram != chordDiagram6));
        TEST(wxT("Operator!= - chordDiagram != chordDiagram 5"),
            (chordDiagram != chordDiagram7));
        TEST(wxT("Operator!= - chordDiagram != chordDiagram 6"),
            (chordDiagram != chordDiagram8));
        TEST(wxT("Operator!= - chordDiagram != chordDiagram 7"),
            (chordDiagram != chordDiagram9));
        TEST(wxT("Operator!= - chordDiagram != chordDiagram 8"),
            (chordDiagram != chordDiagram10));
        TEST(wxT("Operator!= - chordDiagram != chordDiagram 9"),
            (chordDiagram != chordDiagram11));
        TEST(wxT("Operator!= - chordDiagram != chordDiagram 10"),
            (chordDiagram != chordDiagram12));
        TEST(wxT("Operator!= - chordDiagram != chordDiagram 11"),
            (chordDiagram != chordDiagram13));
        TEST(wxT("Operator!= - chordDiagram != chordDiagram 12"),
            (chordDiagram != chordDiagram14));
    }

    return (true);
}

/// Tests the Serialization Fucntions
/// @return True if all tests were executed, false if not
bool ChordDiagramTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Jan 15, 2005
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    ChordName chordName;
    chordName.SetFormula(ChordName::minor);
    
    // Write test data to stream
    ChordDiagram chordDiagramOut(chordName, 3, 3, 4, 5, 5, 3,
        ChordDiagram::stringMuted);
    chordDiagramOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        ChordDiagram chordDiagramIn;
        chordDiagramIn.Deserialize(streamIn,
            PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((chordDiagramIn == chordDiagramOut) 
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the Chord Diagram Functions
/// @return True if all tests were executed, false if not
bool ChordDiagramTestSuite::TestCaseChordDiagram()
{
    //------Last Checked------//
    // - Jan 16, 2005
    
    ChordName chordName;
    chordName.SetFormula(ChordName::major6th);
    
    ChordDiagram chordDiagram;
    TEST(wxT("SetChordDiagram - invalid top fret"),
        !chordDiagram.SetChordDiagram(chordName,192,3,4,5,5,3,3,3));
    TEST(wxT("SetChordDiagram - invalid fret number 1"),
        !chordDiagram.SetChordDiagram(chordName,3,192,4,5,5,3,3,3));
    TEST(wxT("SetChordDiagram - invalid fret number 2"),
        !chordDiagram.SetChordDiagram(chordName,3,3,192,5,5,3,3,3));
    TEST(wxT("SetChordDiagram - invalid fret number 3"),
        !chordDiagram.SetChordDiagram(chordName,3,3,4,192,5,3,3,3));
    TEST(wxT("SetChordDiagram - invalid fret number 4"),
        !chordDiagram.SetChordDiagram(chordName,3,3,4,5,192,3,3,3));
    TEST(wxT("SetChordDiagram - invalid fret number 5"),
        !chordDiagram.SetChordDiagram(chordName,3,3,4,5,5,192,3,3));
    TEST(wxT("SetChordDiagram - invalid fret number 6"),
        !chordDiagram.SetChordDiagram(chordName,3,3,4,5,5,3,192,3));
    TEST(wxT("SetChordDiagram - invalid fret number 7"),
        !chordDiagram.SetChordDiagram(chordName,3,3,4,5,5,3,3,192));
    TEST(wxT("SetChordDiagram - valid"),
        chordDiagram.SetChordDiagram(chordName,3,3,4,5,5,3,3,3));
        
    return (true);
}

/// Tests the Chord Name Functions
/// @return True if all tests were executed, false if not
bool ChordDiagramTestSuite::TestCaseChordName()
{
    //------Last Checked------//
    // - Jan 14, 2005
    ChordName chordName;
    chordName.SetFormula(ChordName::major6th);
    
    ChordDiagram chordDiagram;
    chordDiagram.SetChordName(chordName);
    TEST(wxT("SetChordName"), 
        (chordName == chordDiagram.GetChordName()) &&
        (chordName == chordDiagram.GetChordNameRef()) &&
        (chordName == chordDiagram.GetChordNameConstRef()) &&
        (chordName == *chordDiagram.GetChordNamePtr())
    );
    return (true);
}

/// Tests the Top Fret Functions
/// @return True if all tests were executed, false if not
bool ChordDiagramTestSuite::TestCaseTopFret()
{
    //------Last Checked------//
    // - Jan 14, 2005
    // TEST CASE: IsValidTopFret
    wxByte i = ChordDiagram::MIN_TOP_FRET;
    for (; i <= (ChordDiagram::MAX_TOP_FRET + 1); i++)
        TEST(wxString::Format(wxT("IsValidTopFret - %d"), i),
            (ChordDiagram::IsValidTopFret(i) ==
            (i <= ChordDiagram::MAX_TOP_FRET)));   
    return (true);
}

/// Tests the String Functions
/// @return True if all tests were executed, false if not
bool ChordDiagramTestSuite::TestCaseString()
{
    //------Last Checked------//
    // - Jan 16, 2005
    
    ChordName chordName;
    chordName.SetFormula(ChordName::minor);
    
    // Write test data to stream
    ChordDiagram chordDiagram(chordName, 3, 3, 4, 5, 5, 3,
        ChordDiagram::stringMuted);
    const size_t stringCount = chordDiagram.GetStringCount();
    wxUint32 i = 0;
    for (; i <= (stringCount + 1); i++)
        TEST(wxString::Format(wxT("IsValidString - %d"), i),
        (chordDiagram.IsValidString(i) == ((i >= 0) && (i < stringCount))));
            
    return (true);
}

/// Tests the Fret Number Functions
/// @return True if all tests were executed, false if not
bool ChordDiagramTestSuite::TestCaseFretNumber()
{
    //------Last Checked------//
    // - Jan 16, 2005
    
    // TEST CASE: IsValidFretNumber
    {
        wxByte i = ChordDiagram::MIN_FRET_NUMBER;
        for (; i <= (ChordDiagram::MAX_FRET_NUMBER + 1); i++)
            TEST(wxString::Format(wxT("IsValidFretNumber - %d"), i), 
                (ChordDiagram::IsValidFretNumber(i) ==
                (i <= ChordDiagram::MAX_FRET_NUMBER))
            );
        TEST(wxT("IsValidFretNumber - string muted"),
            ChordDiagram::IsValidFretNumber(ChordDiagram::stringMuted));
        TEST(wxT("IsValidFretNumber - not used"),
            ChordDiagram::IsValidFretNumber(ChordDiagram::notUsed));
    }
    
    // TEST CASE: SetFretNumber
    {
        ChordName chordName;
        chordName.SetFormula(ChordName::minor);
        ChordDiagram chordDiagram(chordName, 3, 3, 4, 5, 5, 3,
            ChordDiagram::stringMuted);
        TEST(wxT("SetFretNumber - invalid string"),
            !chordDiagram.SetFretNumber(6, 2));
        TEST(wxT("SetFretNumber - invalid fret number"),
            !chordDiagram.SetFretNumber(0, 192));
        
        wxUint32 i = 0;
        wxUint32 stringCount = chordDiagram.GetStringCount();
        for (; i < stringCount; i++)
            TEST(wxString::Format(wxT("SetFretNumber - string %d"), i), 
                (chordDiagram.SetFretNumber(i, 2)) &&
                (chordDiagram.GetFretNumber(i) == 2)
            );
        TEST(wxT("GetFretNumber - invalid string"),
            chordDiagram.GetFretNumber(6) == 0);
    }
    
    // TEST CASE: AddFretNumbers
    {
        ChordDiagram chordDiagram;
        TEST(wxT("AddFretNumbers - invalid fret number1"),
            !chordDiagram.AddFretNumbers(192, 4, 5, 5, 3, 3, 3));
        TEST(wxT("AddFretNumbers - invalid fret number2"),
            !chordDiagram.AddFretNumbers(3, 192, 5, 5, 3, 3, 3));
        TEST(wxT("AddFretNumbers - invalid fret number3"),
            !chordDiagram.AddFretNumbers(3, 4, 192, 5, 3, 3, 3));
        TEST(wxT("AddFretNumbers - invalid fret number4"),
            !chordDiagram.AddFretNumbers(3, 4, 5, 192, 3, 3, 3));
        TEST(wxT("AddFretNumbers - invalid fret number5"),
            !chordDiagram.AddFretNumbers(3, 4, 5, 5, 192, 3, 3));
        TEST(wxT("AddFretNumbers - invalid fret number6"),
            !chordDiagram.AddFretNumbers(3, 4, 5, 5, 3, 192, 3));
        TEST(wxT("AddFretNumbers - invalid fret number7"),
            !chordDiagram.AddFretNumbers(3, 4, 5, 5, 3, 3, 192));
                
        TEST(wxT("AddFretNumbers - 3 string chordDiagram"), 
            chordDiagram.AddFretNumbers(3, 4, 5, ChordDiagram::notUsed,
            ChordDiagram::notUsed, ChordDiagram::notUsed,
            ChordDiagram::notUsed) &&
            chordDiagram.IsSameVoicing(3, 4, 5)
        );
        TEST(wxT("AddFretNumbers - 4 string chordDiagram"), 
            chordDiagram.AddFretNumbers(3, 4, 5, 5, ChordDiagram::notUsed,
            ChordDiagram::notUsed, ChordDiagram::notUsed) &&
            chordDiagram.IsSameVoicing(3, 4, 5, 5)
        );  
        TEST(wxT("AddFretNumbers - 5 string chordDiagram"), 
            chordDiagram.AddFretNumbers(3, 4, 5, 5, 3, ChordDiagram::notUsed,
            ChordDiagram::notUsed) &&
            chordDiagram.IsSameVoicing(3, 4, 5, 5, 3)
        );
        TEST(wxT("AddFretNumbers - 6 string chordDiagram"), 
            chordDiagram.AddFretNumbers(3, 4, 5, 5, 3, 3,
            ChordDiagram::notUsed) &&
            chordDiagram.IsSameVoicing(3, 4, 5, 5, 3, 3)
        );
        TEST(wxT("AddFretNumbers - 7 string chordDiagram"), 
            chordDiagram.AddFretNumbers(3, 4, 5, 5, 3, 3, 3) &&
            chordDiagram.IsSameVoicing(3, 4, 5, 5, 3, 3, 3)
        );
    }
    return (true);
}

/// Tests the Voicing Functions
/// @return True if all tests were executed, false if not
bool ChordDiagramTestSuite::TestCaseVoicing()
{
    //------Last Checked------//
    // - Jan 16, 2005
    
    ChordName chordName;
    chordName.SetFormula(ChordName::major6th);
    
    // TEST CASE: IsSameVoicing(ChordDiagram)
    {
        ChordDiagram chordDiagram(chordName, 3, 3, 4, 5, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram2(chordName, 3, 3, 4, 5, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram3(chordName, 3, 4, 4, 5, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram4(chordName, 3, 3, 5, 5, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram5(chordName, 3, 3, 4, 6, 5, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram6(chordName, 3, 3, 4, 5, 6, 3,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram7(chordName, 3, 3, 4, 5, 5, 4,
            ChordDiagram::stringMuted);
        ChordDiagram chordDiagram8(chordName, 3, 3, 4, 5, 5, 3, 3);
        ChordDiagram chordDiagram9(chordName, 3, 3, 4, 5);
        ChordDiagram chordDiagram10(chordName, 3, 3, 4, 5, 5);
        ChordDiagram chordDiagram11(chordName, 3, 3, 4, 5, 5, 3);
        ChordDiagram chordDiagram12(chordName, 3, 3, 4, 5, 5, 3, 3, 3);
                
        TEST(wxT("IsSameVoicing - chordDiagram == chordDiagram"),
            chordDiagram.IsSameVoicing(chordDiagram2));
        TEST(wxT("IsSameVoicing - chordDiagram != chordDiagram"),
            !chordDiagram.IsSameVoicing(chordDiagram3));
        TEST(wxT("IsSameVoicing - chordDiagram != chordDiagram 2"),
            !chordDiagram.IsSameVoicing(chordDiagram4));
        TEST(wxT("IsSameVoicing - chordDiagram != chordDiagram 3"),
            !chordDiagram.IsSameVoicing(chordDiagram5));
        TEST(wxT("IsSameVoicing - chordDiagram != chordDiagram 4"),
            !chordDiagram.IsSameVoicing(chordDiagram6));
        TEST(wxT("IsSameVoicing - chordDiagram != chordDiagram 5"),
            !chordDiagram.IsSameVoicing(chordDiagram7));
        TEST(wxT("IsSameVoicing - chordDiagram != chordDiagram 6"),
            !chordDiagram.IsSameVoicing(chordDiagram8));
        TEST(wxT("IsSameVoicing - chordDiagram != chordDiagram 7"),
            !chordDiagram.IsSameVoicing(chordDiagram9));
        TEST(wxT("IsSameVoicing - chordDiagram != chordDiagram 8"),
            !chordDiagram.IsSameVoicing(chordDiagram10));
        TEST(wxT("IsSameVoicing - chordDiagram != chordDiagram 9"),
            !chordDiagram.IsSameVoicing(chordDiagram11));
        TEST(wxT("IsSameVoicing - chordDiagram != chordDiagram 10"),
            !chordDiagram.IsSameVoicing(chordDiagram12));
    }

    // TEST CASE: IsSameVoicing(wxByte,wxByte,wxByte,wxByte,wxByte,wxByte,wxByte)
    {
        ChordDiagram chordDiagram(chordName, 3, 3, 4, 5);
        ChordDiagram chordDiagram2(chordName, 3, 3, 4, 5, 5);
        ChordDiagram chordDiagram3(chordName, 3, 3, 4, 5, 5, 3);
        ChordDiagram chordDiagram4(chordName, 3, 3, 4, 5, 5, 3, 3);
        ChordDiagram chordDiagram5(chordName, 3, 3, 4, 5, 5, 3, 3, 3);
                
        TEST(wxT("IsSameVoicing - 3 string chord diagram"),
            chordDiagram.IsSameVoicing(3,4,5));
        TEST(wxT("IsSameVoicing - 4 string chord diagram"),
            chordDiagram2.IsSameVoicing(3,4,5,5));
        TEST(wxT("IsSameVoicing - 5 string chord diagram"),
            chordDiagram3.IsSameVoicing(3,4,5,5,3));
        TEST(wxT("IsSameVoicing - 6 string chord diagram"),
            chordDiagram4.IsSameVoicing(3,4,5,5,3,3));
        TEST(wxT("IsSameVoicing - 7 string chord diagram"),
            chordDiagram5.IsSameVoicing(3,4,5,5,3,3,3));
    }
    
    return (true);
}

/// Tests the Operations
/// @return True if all tests were executed, false if not
bool ChordDiagramTestSuite::TestCaseOperations()
{
    //------Last Checked------//
    // - Jan 16, 2005
    ChordDiagram chordDiagram(3,3,4,5,5,3,ChordDiagram::stringMuted);
    TEST(wxT("GetSpelling"), chordDiagram.GetSpelling() == wxT("x 3 5 5 4 3"));
    return (true);
}
