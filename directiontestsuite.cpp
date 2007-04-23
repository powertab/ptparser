/////////////////////////////////////////////////////////////////////////////
// Name:            directiontestsuite.cpp
// Purpose:         Performs unit testing on the Direction class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 9, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "directiontestsuite.h"

#include "direction.h"
#include "powertabfileheader.h"         // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(DirectionTestSuite, TestSuite)

/// Default Constructor
DirectionTestSuite::DirectionTestSuite()
{
    //------Last Checked------//
    // - Jan 11, 2005
}

/// Destructor
DirectionTestSuite::~DirectionTestSuite()
{
    //------Last Checked------//
    // - Jan 11, 2005
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t DirectionTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Jan 11, 2005
    return (602);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool DirectionTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Jan 11, 2005
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
    if (!TestCaseSymbolType())
        return (false);
    if (!TestCaseActiveSymbol())
        return (false);
    if (!TestCaseRepeatNumber())
        return (false);
    if (!TestCaseSymbolArray())
        return (false);
    if (!TestCaseOperations())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool DirectionTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 11, 2005
    
    // TEST CASE: Default constructor
    {
        Direction direction;
        TEST(wxT("Default Constructor"), 
            (direction.GetPosition() == Direction::DEFAULT_POSITION) &&
            (direction.GetSymbolCount() == 0)
        );        
    }
    
    // TEST CASE: Primary constructor
    {
        Direction direction(12, Direction::toCoda, Direction::activeDaCapo, 4);
        wxByte symbolType = 0;
        wxByte activeSymbol = 0;
        wxByte repeatNumber = 0;
        bool ok = direction.GetSymbol(0, symbolType, activeSymbol, repeatNumber);
        TEST(wxT("Primary Constructor"), 
            (ok) &&
            (direction.GetPosition() ==  12) &&
            (symbolType == Direction::toCoda) &&
            (activeSymbol == Direction::activeDaCapo) &&
            (repeatNumber == 4)
        );
    }
    
    // TEST CASE: Copy constructor
    {
        Direction direction(12, Direction::toCoda, Direction::activeDaCapo, 4);
        Direction direction2(direction);
        TEST(wxT("Copy Constructor"), 
            (direction2 == direction)
        );
    }
    
    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool DirectionTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 11, 2005

    Direction direction(12, Direction::toCoda, Direction::activeDaCapo, 4);
    Direction* clone = (Direction*)direction.CloneObject();    
    TEST(wxT("CloneObject"),
        (*clone == direction)
    );
    delete clone;
    
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool DirectionTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 11, 2005
                
    // TEST CASE: Operator=
    {
        Direction direction(12, Direction::toCoda, Direction::activeDaCapo, 4);
        Direction direction2 = direction;        
        TEST(wxT("Operator="), 
            (direction2 == direction)
        );
        
        direction = direction;
        TEST(wxT("Operator= (self-assignment)"), 
            (direction == direction)
        );
    }
    
    // TEST CASE: Operator==
    {
        Direction direction(12, Direction::toCoda, Direction::activeDaCapo, 4);
        Direction direction2(12, Direction::toCoda, Direction::activeDaCapo, 4);
        Direction direction3(13, Direction::toDoubleCoda, Direction::activeDaCapo, 4);
        Direction direction4(12, Direction::toCoda, Direction::activeNone, 4);
        Direction direction5(12, Direction::toCoda, Direction::activeDaCapo, 5);
        Direction direction6(12, Direction::toCoda, Direction::activeDaCapo, 4);
        direction6.AddSymbol(Direction::toDoubleCoda, Direction::activeDaCapo, 4);
                       
        TEST(wxT("Operator== - direction == direction"), (direction == direction2));
        TEST(wxT("Operator== - direction != direction"), !(direction == direction3));
        TEST(wxT("Operator== - direction != direction 2"), !(direction == direction4));
        TEST(wxT("Operator== - direction != direction 3"), !(direction == direction5));
        TEST(wxT("Operator== - direction != direction 4"), !(direction == direction6));
    }
        
    // TEST CASE: Operator!=
    {
        Direction direction(12, Direction::toCoda, Direction::activeDaCapo, 4);
        Direction direction2(12, Direction::toCoda, Direction::activeDaCapo, 4);
        Direction direction3(13, Direction::toDoubleCoda, Direction::activeDaCapo, 4);
        Direction direction4(12, Direction::toCoda, Direction::activeNone, 4);
        Direction direction5(12, Direction::toCoda, Direction::activeDaCapo, 5);
        Direction direction6(12, Direction::toCoda, Direction::activeDaCapo, 4);
        direction6.AddSymbol(Direction::toDoubleCoda, Direction::activeDaCapo, 4);
                       
        TEST(wxT("Operator!= - direction == direction"), !(direction != direction2));
        TEST(wxT("Operator!= - direction != direction"), (direction != direction3));
        TEST(wxT("Operator!= - direction != direction 2"), (direction != direction4));
        TEST(wxT("Operator!= - direction != direction 3"), (direction != direction5));
        TEST(wxT("Operator!= - direction != direction 4"), (direction != direction6));
    }

    return (true);
}

/// Tests the Serialization Fucntions
/// @return True if all tests were executed, false if not
bool DirectionTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Jan 11, 2005
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    Direction directionOut(12, Direction::toCoda, Direction::activeDaCapo, 4);
    directionOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        Direction directionIn;
        directionIn.Deserialize(streamIn, PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((directionIn == directionOut) 
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the Position Functions
/// @return True if all tests were executed, false if not
bool DirectionTestSuite::TestCasePosition()
{
    //------Last Checked------//
    // - Jan 11, 2005
    Direction direction;
    
    // TEST CASE: IsValidPosition
    {
        wxUint32 i = 0;
        for (; i <= (Direction::MAX_POSITION + 1); i++)
        {
            TEST(wxString::Format(wxT("IsValidPosition - %d"), i),
                (Direction::IsValidPosition(i) == (i <= Direction::MAX_POSITION))
            );
        }
    }
    
    // TEST CASE: SetPosition
    {
        wxUint32 i = 0;
        for (; i <= (Direction::MAX_POSITION + 1); i++)
        {
            TEST(wxT("SetPosition - %d"), 
                (direction.SetPosition(i) == (i <= Direction::MAX_POSITION)) &&
                ((i > Direction::MAX_POSITION) ? 1 : (direction.GetPosition() == i))
            );
        }
    }
    return (true);
}

/// Tests the Symbol Type Functions
/// @return True if all tests were executed, false if not
bool DirectionTestSuite::TestCaseSymbolType()
{
    //------Last Checked------//
    // - Jan 11, 2005
    wxByte i = Direction::coda;
    for (; i <= (Direction::dalSegnoSegnoAlFine + 1); i++)
        TEST(wxString::Format(wxT("IsValidSymbolType - %d"), i),
            (Direction::IsValidSymbolType(i) == (i <= Direction::dalSegnoSegnoAlFine))
        );
    return (true);
}

/// Tests the Active Symbol Functions
/// @return True if all tests were executed, false if not
bool DirectionTestSuite::TestCaseActiveSymbol()
{
    //------Last Checked------//
    // - Jan 11, 2005
    wxByte i = Direction::activeNone;
    for (; i <= (Direction::activeDalSegnoSegno + 1); i++)
        TEST(wxString::Format(wxT("IsValidActiveSymbol - %d"), i),
            (Direction::IsValidActiveSymbol(i) == (i <= Direction::activeDalSegnoSegno))
        );
    return (true);
}

/// Tests the Repeat Number Functions
/// @return True if all tests were executed, false if not
bool DirectionTestSuite::TestCaseRepeatNumber()
{
    //------Last Checked------//
    // - Jan 11, 2005
    wxByte i = 0;
    for (; i <= (Direction::MAX_REPEAT_NUMBER + 1); i++)
        TEST(wxString::Format(wxT("IsValidRepeatNumber - %d"), i),
            (Direction::IsValidRepeatNumber(i) == (i <= Direction::MAX_REPEAT_NUMBER))
        );
    return (true);
}
    
/// Tests the Symbol Array Functions
bool DirectionTestSuite::TestCaseSymbolArray()
{
    //------Last Checked------//
    // - Jan 11, 2005
    
    Direction direction(12, Direction::toCoda, Direction::activeDaCapo, 4);
    direction.AddSymbol(Direction::toDoubleCoda, Direction::activeDalSegno, 5);
    direction.AddSymbol(Direction::coda);
    
    // TEST CASE: IsValidSymbolIndex
    {
        wxUint32 i = 0;
        for (; i <= Direction::MAX_SYMBOLS; i++)
            TEST(wxString::Format(wxT("IsValidSymbolIndex - %d"), i), 
                (direction.IsValidSymbolIndex(i) == (i < Direction::MAX_SYMBOLS))
            );
    }
    
    // TEST CASE: AddSymbol
    {
        Direction direction2;
        TEST(wxT("AddSymbol"), 
            (direction2.AddSymbol(Direction::toCoda, Direction::activeDaCapo, 5)) &&
            (direction2.GetSymbolCount() == 1)
        );
        
        TEST(wxT("AddSymbol - full"), (!direction.AddSymbol(Direction::doubleCoda)));
    }

    // TEST CASE: GetSymbolCount
    {    
        TEST(wxT("GetSymbolCount"), (direction.GetSymbolCount() == 3));
    }
    
    // TEST CASE: SetSymbol
    {
        Direction direction2(12, Direction::toCoda, Direction::activeDaCapo, 5);
        TEST(wxT("SetSymbol - invalid index"),
            (!direction2.SetSymbol(Direction::MAX_SYMBOLS, Direction::coda, Direction::activeNone, 0))
        );
        
        TEST(wxT("SetSymbol - invalid symbol type"),
            (!direction2.SetSymbol(0, 255, Direction::activeNone, 0))
        );
        
        TEST(wxT("SetSymbol - invalid active symbol"),
            (!direction2.SetSymbol(0, Direction::coda, 255, 0))
        );
        
        TEST(wxT("SetSymbol - invalid repeat number"),
            (!direction2.SetSymbol(0, Direction::coda, Direction::activeNone, Direction::MAX_REPEAT_NUMBER + 1))
        );
        
        direction2.SetSymbol(0, Direction::coda, Direction::activeNone, 0);
        
        wxByte symbolType = 0;
        wxByte activeSymbol = 0;
        wxByte repeatNumber = 0;
        direction2.GetSymbol(0, symbolType, activeSymbol, repeatNumber);
        
        TEST(wxT("SetSymbol"),
            (symbolType == Direction::coda) &&
            (activeSymbol == Direction::activeNone) &&
            (repeatNumber == 0)
        );
    }
    
    // TEST CASE: IsSymbolType
    {
        TEST(wxT("IsSymbolType - invalid index"),
            (!direction.IsSymbolType(Direction::MAX_SYMBOLS, Direction::toCoda))
        );
        
        TEST(wxT("IsSymbolType - invalid symbol type"),
            (!direction.IsSymbolType(0, 255))
        );
        
        TEST(wxT("IsSymbolType"),
            (direction.IsSymbolType(0, Direction::toCoda)) &&
            (direction.IsSymbolType(1, Direction::toDoubleCoda)) &&
            (direction.IsSymbolType(2, Direction::coda))
        );
    }
    
    // TEST CASE: RemoveSymbolAtIndex
    {
        TEST(wxT("RemoveSymbolAtIndex - invalid index"),
            (!direction.RemoveSymbolAtIndex(Direction::MAX_SYMBOLS))
        );
        TEST(wxT("RemoveSymbolAtIndex"),
            (direction.RemoveSymbolAtIndex(0)) &&
            (direction.GetSymbolCount() == 2)
        );
    }
    
    // TEST CASE: DeleteSymbolArrayContents
    {
        direction.DeleteSymbolArrayContents();
        TEST(wxT("DeleteSymbolArrayContents"),
            (direction.GetSymbolCount() == 0)
        );
    }
    return (true);
}

/// Tests the Operations
/// @return True if all tests were executed, false if not
bool DirectionTestSuite::TestCaseOperations()
{
    //------Last Checked------//
    // - Jan 11, 2005
    
    Direction direction(12, Direction::toCoda, Direction::activeDaCapo, 4);
    TEST(wxT("GetText - invalid symbol index"), (!direction.GetText(1)));
    TEST(wxT("GetText"), (direction.GetText(0) == wxT("To Coda")));
    return (true);
}
