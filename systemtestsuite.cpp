/////////////////////////////////////////////////////////////////////////////
// Name:            systemtestsuite.cpp
// Purpose:         Performs unit testing on the System class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 5, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "systemtestsuite.h"

#include "system.h"
#include "powertabfileheader.h"         // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(SystemTestSuite, TestSuite)

/// Default Constructor
SystemTestSuite::SystemTestSuite()
{
    //------Last Checked------//
    // - Dec 10, 2004
}

/// Destructor
SystemTestSuite::~SystemTestSuite()
{
    //------Last Checked------//
    // - Dec 10, 2004
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t SystemTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Dec 10, 2004
    return (42);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool SystemTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Jan 14, 2005
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseCreation())
        return (false);
    if (!TestCaseOperator())
        return (false);
    if (!TestCaseSerialize())
        return (false);
    if (!TestCaseDirectionArray())
        return (false);
    if (!TestCaseChordTextArray())
        return (false);
    if (!TestCaseRhythmSlashArray())
        return (false);
    if (!TestCaseStaffArray())
        return (false);
    if (!TestCaseBarlineArray())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool SystemTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 14, 2005
    
    // TEST CASE: Default Constructor
    {
        System system;
        TEST(wxT("Default Constructor"), 
            (system.GetRect() == System::DEFAULT_RECT) &&
            (system.GetPositionSpacing() == System::DEFAULT_POSITION_SPACING) &&
            (system.GetRhythmSlashSpacingAbove() == System::DEFAULT_RHYTHM_SLASH_SPACING_ABOVE) &&
            (system.GetRhythmSlashSpacingBelow() == System::DEFAULT_RHYTHM_SLASH_SPACING_BELOW) &&
            (system.GetExtraSpacing() == System::DEFAULT_EXTRA_SPACING) &&
            (system.GetDirectionCount() == 0) &&
            (system.GetChordTextCount() == 0) &&
            (system.GetRhythmSlashCount() == 0) &&
            (system.GetStaffCount() == 0) &&
            (system.GetBarlineCount() == 0)
        );
    }
            
    // TEST CASE: Copy Constructor
    {
        System system;
        system.m_rect = wxRect(1,2,3,4);
        system.m_positionSpacing = 1;
        system.m_rhythmSlashSpacingAbove = 2;
        system.m_rhythmSlashSpacingBelow = 3;
        system.m_extraSpacing = 4;
        
        system.m_startBar.SetBarlineData(Barline::doubleBar,0);
        system.m_directionArray.Add(new Direction);
        system.m_chordTextArray.Add(new ChordText);
        system.m_rhythmSlashArray.Add(new RhythmSlash);
        system.m_staffArray.Add(new Staff);
        system.m_barlineArray.Add(new Barline);
        system.m_endBar.SetBarlineData(Barline::doubleBarFine,0);
        
        System system2(system);
        TEST(wxT("Copy Constructor"), system2 == system);
    }

    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool SystemTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 14, 2005
    System system;
    System* clone = (System*)system.CloneObject();
    TEST(wxT("CloneObject"),
        (*clone == system)
    );
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool SystemTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 14, 2005
    
    // TEST CASE: Assignment Operator
    {
        System system;
        system.m_rect = wxRect(1,2,3,4);
        system.m_positionSpacing = 1;
        system.m_rhythmSlashSpacingAbove = 2;
        system.m_rhythmSlashSpacingBelow = 3;
        system.m_extraSpacing = 4;
        
        system.m_startBar.SetBarlineData(Barline::doubleBar,0);
        system.m_directionArray.Add(new Direction);
        system.m_chordTextArray.Add(new ChordText);
        system.m_rhythmSlashArray.Add(new RhythmSlash);
        system.m_staffArray.Add(new Staff);
        system.m_barlineArray.Add(new Barline);
        system.m_endBar.SetBarlineData(Barline::doubleBarFine,0);
        
        System system2 = system;
        TEST(wxT("Operator="), system2 == system);
        
        // TEST CASE: Operator= (self-assignment)
        system = system;
        TEST(wxT("Operator= (self-assignment)"),
            (system == system)
        );
    }
    
    // TEST CASE: Equality Operator
    {
        System system;
        System system2;
        
        System system3;
        system3.m_rect = wxRect(1,2,3,4);
        
        System system4;
        system4.m_positionSpacing = 1;
        
        System system5;
        system5.m_rhythmSlashSpacingAbove = 2;
        
        System system6;
        system6.m_rhythmSlashSpacingBelow = 3;
        
        System system7;
        system7.m_extraSpacing = 4;
        
        System system8;
        system8.m_startBar.SetBarlineData(Barline::doubleBar,0);
        
        System system9;
        system9.m_directionArray.Add(new Direction);
        
        System system10;
        system10.m_chordTextArray.Add(new ChordText);
        
        System system11;
        system11.m_rhythmSlashArray.Add(new RhythmSlash);
        
        System system12;
        system12.m_staffArray.Add(new Staff);
        
        System system13;
        system13.m_barlineArray.Add(new Barline);
        
        System system14;
        system14.m_endBar.SetBarlineData(Barline::doubleBarFine, 0);
        
        TEST(wxT("Operator== - system == system"), system == system2);
        TEST(wxT("Operator== - system != system"), !(system == system3));
        TEST(wxT("Operator== - system != system 2"), !(system == system4));
        TEST(wxT("Operator== - system != system 3"), !(system == system5));
        TEST(wxT("Operator== - system != system 4"), !(system == system6));
        TEST(wxT("Operator== - system != system 5"), !(system == system7));
        TEST(wxT("Operator== - system != system 6"), !(system == system8));
        TEST(wxT("Operator== - system != system 7"), !(system == system9));
        TEST(wxT("Operator== - system != system 8"), !(system == system10));
        TEST(wxT("Operator== - system != system 9"), !(system == system11));
        TEST(wxT("Operator== - system != system 10"), !(system == system12));
        TEST(wxT("Operator== - system != system 11"), !(system == system13));
        TEST(wxT("Operator== - system != system 12"), !(system == system14));
    }
    
    // TEST CASE: Inequality Operator
    {
        System system;
        System system2;
        
        System system3;
        system3.m_rect = wxRect(1,2,3,4);
        
        System system4;
        system4.m_positionSpacing = 1;
        
        System system5;
        system5.m_rhythmSlashSpacingAbove = 2;
        
        System system6;
        system6.m_rhythmSlashSpacingBelow = 3;
        
        System system7;
        system7.m_extraSpacing = 4;
        
        System system8;
        system8.m_startBar.SetBarlineData(Barline::doubleBar,0);
        
        System system9;
        system9.m_directionArray.Add(new Direction);
        
        System system10;
        system10.m_chordTextArray.Add(new ChordText);
        
        System system11;
        system11.m_rhythmSlashArray.Add(new RhythmSlash);
        
        System system12;
        system12.m_staffArray.Add(new Staff);
        
        System system13;
        system13.m_barlineArray.Add(new Barline);
        
        System system14;
        system14.m_endBar.SetBarlineData(Barline::doubleBarFine, 0);
        
        TEST(wxT("Operator!= - system == system"), !(system != system2));
        TEST(wxT("Operator!= - system != system"), (system != system3));
        TEST(wxT("Operator!= - system != system 2"), (system != system4));
        TEST(wxT("Operator!= - system != system 3"), (system != system5));
        TEST(wxT("Operator!= - system != system 4"), (system != system6));
        TEST(wxT("Operator!= - system != system 5"), (system != system7));
        TEST(wxT("Operator!= - system != system 6"), (system != system8));
        TEST(wxT("Operator!= - system != system 7"), (system != system9));
        TEST(wxT("Operator!= - system != system 8"), (system != system10));
        TEST(wxT("Operator!= - system != system 9"), (system != system11));
        TEST(wxT("Operator!= - system != system 10"), (system != system12));
        TEST(wxT("Operator!= - system != system 11"), (system != system13));
        TEST(wxT("Operator!= - system != system 12"), (system != system14));
    }
    
    return (true);
}

/// Tests the Serialization Functions
/// @return True if all tests were executed, false if not
bool SystemTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Jan 14, 2005
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    System systemOut;
    systemOut.m_rect = wxRect(1,2,3,4);
    systemOut.m_positionSpacing = 1;
    systemOut.m_rhythmSlashSpacingAbove = 2;
    systemOut.m_rhythmSlashSpacingBelow = 3;
    systemOut.m_extraSpacing = 4;
       
    wxUint32 i = 0;
    for (; i < 3; i++)
    {
        systemOut.m_directionArray.Add(new Direction);
        systemOut.m_chordTextArray.Add(new ChordText);
        systemOut.m_rhythmSlashArray.Add(new RhythmSlash);
        systemOut.m_staffArray.Add(new Staff);
        systemOut.m_barlineArray.Add(new Barline);
    }
    systemOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        System systemIn;
        systemIn.Deserialize(streamIn, PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((systemIn == systemOut)
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the Direction Array Functions
/// @return True if all tests were executed, false if not
bool SystemTestSuite::TestCaseDirectionArray()
{
    //------Last Checked------//
    // - Jan 6, 2005
    System system;
    TEST(wxT("IsValidDirectionIndex - false"), !system.IsValidDirectionIndex(0));
    TEST(wxT("GetDirection - invalid index"), (system.GetDirection(0) == NULL));
    return (true);
}

/// Tests the Chord Text Array Functions
/// @return True if all tests were executed, false if not
bool SystemTestSuite::TestCaseChordTextArray()
{
    //------Last Checked------//
    // - Jan 6, 2005
    System system;
    TEST(wxT("IsValidChordTextIndex - false"), !system.IsValidChordTextIndex(0));
    TEST(wxT("GetChordText - invalid index"), (system.GetChordText(0) == NULL));
    return (true);
}

/// Tests the Rhythm Slash Array Functions
/// @return True if all tests were executed, false if not
bool SystemTestSuite::TestCaseRhythmSlashArray()
{
    //------Last Checked------//
    // - Jan 6, 2005
    System system;
    TEST(wxT("IsValidRhythmSlashIndex - false"), !system.IsValidRhythmSlashIndex(0));
    TEST(wxT("GetRhythmSlash - invalid index"), (system.GetRhythmSlash(0) == NULL));
    return (true);
}

/// Tests the Staff Array Functions
/// @return True if all tests were executed, false if not
bool SystemTestSuite::TestCaseStaffArray()
{
    //------Last Checked------//
    // - Jan 6, 2005
    System system;
    TEST(wxT("IsValidStaffIndex - false"), !system.IsValidStaffIndex(0));
    TEST(wxT("GetStaff - invalid index"), (system.GetStaff(0) == NULL));
    return (true);
}

/// Tests the Barline Array Functions
/// @return True if all tests were executed, false if not
bool SystemTestSuite::TestCaseBarlineArray()
{
    //------Last Checked------//
    // - Jan 6, 2005
    System system;
    TEST(wxT("IsValidBarlineIndex - false"), !system.IsValidBarlineIndex(0));
    TEST(wxT("GetBarline - invalid index"), (system.GetBarline(0) == NULL));
    return (true);
}
