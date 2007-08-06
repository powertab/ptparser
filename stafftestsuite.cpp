/////////////////////////////////////////////////////////////////////////////
// Name:            stafftestsuite.cpp
// Purpose:         Performs unit testing on the Staff class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 5, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "stafftestsuite.h"

#include "staff.h"
#include "powertabfileheader.h"         // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(StaffTestSuite, TestSuite)

/// Default Constructor
StaffTestSuite::StaffTestSuite()
{
    //------Last Checked------//
    // - Jan 5, 2005
}

/// Destructor
StaffTestSuite::~StaffTestSuite()
{
    //------Last Checked------//
    // - Jan 5, 2005
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t StaffTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Jan 5, 2005
    return (62);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool StaffTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Jan 5, 2005
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseCreation())
        return (false);
    if (!TestCaseOperator())
        return (false);
    if (!TestCaseSerialize())
        return (false);
    if (!TestCaseClef())
        return (false);
    if (!TestCaseTablatureStaffType())
        return (false);
    if (!TestCaseStandardNotationStaffAboveSpacing())
        return (false);
    if (!TestCaseStandardNotationStaffBelowSpacing())
        return (false);
    if (!TestCaseSymbolSpacing())
        return (false);
    if (!TestCaseTablatureStaffBelowSpacing())
        return (false);
    if (!TestCaseVoice())
        return (false);
    if (!TestCasePositionArray())
        return (false);
    
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool StaffTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 5, 2005
    
    // TEST CASE: Default Constructor
    {
        Staff staff;
        TEST(wxT("Default Constructor"),
            (staff.GetClef() == Staff::DEFAULT_CLEF) &&
            (staff.GetTablatureStaffType() ==
                Staff::DEFAULT_TABLATURE_STAFF_TYPE) &&
            (staff.GetStandardNotationStaffAboveSpacing() ==
                Staff::DEFAULT_STANDARD_NOTATION_STAFF_ABOVE_SPACING) &&
            (staff.GetStandardNotationStaffBelowSpacing() ==
                Staff::DEFAULT_STANDARD_NOTATION_STAFF_BELOW_SPACING) &&
            (staff.GetSymbolSpacing() == Staff::DEFAULT_SYMBOL_SPACING) &&
            (staff.GetTablatureStaffBelowSpacing() ==
                Staff::DEFAULT_TABLATURE_STAFF_BELOW_SPACING)
        );
    }
    
    // TEST CASE: Primary Constructor
    {
        Staff staff(4, Staff::BASS_CLEF);
        staff.m_positionArray[0].Add(new Position);
        staff.m_positionArray[1].Add(new Position);
        
        TEST(wxT("Copy Constructor"),
            (staff.GetClef() == Staff::BASS_CLEF) &&
            (staff.GetTablatureStaffType() == 4) &&
            (staff.GetStandardNotationStaffAboveSpacing() ==
                Staff::DEFAULT_STANDARD_NOTATION_STAFF_ABOVE_SPACING) &&
            (staff.GetStandardNotationStaffBelowSpacing() ==
                Staff::DEFAULT_STANDARD_NOTATION_STAFF_BELOW_SPACING) &&
            (staff.GetSymbolSpacing() == Staff::DEFAULT_SYMBOL_SPACING) &&
            (staff.GetTablatureStaffBelowSpacing() ==
                Staff::DEFAULT_TABLATURE_STAFF_BELOW_SPACING)
        );
    }
    
    // TEST CASE: Copy Constructor
    {
        Staff staff(4, Staff::BASS_CLEF);
        staff.m_positionArray[0].Add(new Position);
        staff.m_positionArray[1].Add(new Position);
        Staff staff2(staff);
        
        TEST(wxT("Copy Constructor"), staff == staff2);
    }
    
    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool StaffTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 12, 2005
    Staff staff(4, Staff::BASS_CLEF);
    Staff* clone = (Staff*)staff.CloneObject();
    TEST(wxT("CloneObject"),
        (*clone == staff)
    );
    delete clone;
    
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool StaffTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 5, 2005
    
    // TEST CASE: Assignment Operator
    {
        Staff staff(4, Staff::BASS_CLEF);
        staff.m_positionArray[0].Add(new Position);
        staff.m_positionArray[1].Add(new Position);
        
        Staff staff2 = staff;
        TEST(wxT("Operator="), staff2 == staff);
        
        // TEST CASE: Self-assignment
        staff = staff;
        TEST(wxT("Operator= (self-assignment)"), staff == staff);
    }
    
    // TEST CASE: Equality Operator
    {
        Staff staff(4, Staff::BASS_CLEF);
        Staff staff2(4, Staff::BASS_CLEF);
        Staff staff3(5, Staff::BASS_CLEF);
        Staff staff4(4, Staff::TREBLE_CLEF);
        Staff staff5(4, Staff::BASS_CLEF);
        staff5.SetStandardNotationStaffAboveSpacing(12);
        Staff staff6(4, Staff::BASS_CLEF);
        staff6.SetStandardNotationStaffBelowSpacing(12);
        Staff staff7(4, Staff::BASS_CLEF);
        staff7.SetSymbolSpacing(12);
        Staff staff8(4, Staff::BASS_CLEF);
        staff8.SetTablatureStaffBelowSpacing(12);
        Staff staff9(4, Staff::BASS_CLEF);
        staff9.m_positionArray[0].Add(new Position);
        Staff staff10(4, Staff::BASS_CLEF);
        staff10.m_positionArray[1].Add(new Position);

        TEST(wxT("Operator== - staff == staff"), (staff == staff2));
        TEST(wxT("Operator== - staff != staff"), !(staff == staff3));
        TEST(wxT("Operator== - staff != staff 2"), !(staff == staff4));
        TEST(wxT("Operator== - staff != staff 3"), !(staff == staff5));
        TEST(wxT("Operator== - staff != staff 4"), !(staff == staff6));
        TEST(wxT("Operator== - staff != staff 5"), !(staff == staff7));
        TEST(wxT("Operator== - staff != staff 6"), !(staff == staff8));
        TEST(wxT("Operator== - staff != staff 7"), !(staff == staff9));
    }
    
    // TEST CASE: Inequality Operator
    {
        Staff staff(4, Staff::BASS_CLEF);
        Staff staff2(4, Staff::BASS_CLEF);
        Staff staff3(5, Staff::BASS_CLEF);
        Staff staff4(4, Staff::TREBLE_CLEF);
        Staff staff5(4, Staff::BASS_CLEF);
        staff5.SetStandardNotationStaffAboveSpacing(12);
        Staff staff6(4, Staff::BASS_CLEF);
        staff6.SetStandardNotationStaffBelowSpacing(12);
        Staff staff7(4, Staff::BASS_CLEF);
        staff7.SetSymbolSpacing(12);
        Staff staff8(4, Staff::BASS_CLEF);
        staff8.SetTablatureStaffBelowSpacing(12);
        Staff staff9(4, Staff::BASS_CLEF);
        staff9.m_positionArray[0].Add(new Position);
        Staff staff10(4, Staff::BASS_CLEF);
        staff10.m_positionArray[1].Add(new Position);

        TEST(wxT("Operator!= - staff == staff"), !(staff != staff2));
        TEST(wxT("Operator!= - staff != staff"), (staff != staff3));
        TEST(wxT("Operator!= - staff != staff 2"), (staff != staff4));
        TEST(wxT("Operator!= - staff != staff 3"), (staff != staff5));
        TEST(wxT("Operator!= - staff != staff 4"), (staff != staff6));
        TEST(wxT("Operator!= - staff != staff 5"), (staff != staff7));
        TEST(wxT("Operator!= - staff != staff 6"), (staff != staff8));
        TEST(wxT("Operator!= - staff != staff 7"), (staff != staff9));
    }
    
    return (true);
}

/// Tests the Serialization Functions
/// @return True if all tests were executed, false if not
bool StaffTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Jan 5, 2005

    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    Staff staffOut(4, Staff::BASS_CLEF);
    wxUint32 i = 0;
    for (; i < 3; i++)
    {
        staffOut.m_positionArray[0].Add(new Position);
        staffOut.m_positionArray[1].Add(new Position);
    }
    staffOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        Staff staffIn;
        staffIn.Deserialize(streamIn, PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((staffIn == staffOut)
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the Clef Functions
/// @return True if all tests were executed, false if not
bool StaffTestSuite::TestCaseClef()
{
    //------Last Checked------//
    // - Jan 5, 2005
    
    // TEST CASE: IsValidClef
    {
        wxByte i = Staff::TREBLE_CLEF;
        for (; i <= (Staff::BASS_CLEF + 1); i++)
            TEST(wxString::Format(wxT("IsValidClef - %d"), i),
                (Staff::IsValidClef(i) == (i <= Staff::BASS_CLEF))
            );
    }
    
    // TEST CASE: SetClef
    {
        Staff staff;
        wxByte i = Staff::TREBLE_CLEF;
        for (; i <= (Staff::BASS_CLEF + 1); i++)
            TEST(wxString::Format(wxT("SetClef - %d"), i),
                (staff.SetClef(i) == (i <= Staff::BASS_CLEF)) &&
                ((i > Staff::BASS_CLEF) ? 1 : (staff.GetClef() == i))
            );
    }
    return (true);
}

/// Tests the Tablature Staff Type Functions
/// @return True if all tests were executed, false if not
bool StaffTestSuite::TestCaseTablatureStaffType()
{
    //------Last Checked------//
    // - Jan 5, 2005
    
    // TEST CASE: IsValidTablatureStaffType
    {
        wxByte i = Staff::MIN_TABLATURE_STAFF_TYPE - 1;
        for (; i <= (Staff::MAX_TABLATURE_STAFF_TYPE + 1); i++)
        {
            TEST(wxString::Format(wxT("IsValidTablatureStaffType - %d"), i),
                (Staff::IsValidTablatureStaffType(i) ==
                ((i >= Staff::MIN_TABLATURE_STAFF_TYPE) &&
                (i <= Staff::MAX_TABLATURE_STAFF_TYPE)))
            );
        }
    }
    
    // TEST CASE: SetTablatureStaffType
    {
        Staff staff;
        wxByte i = Staff::MIN_TABLATURE_STAFF_TYPE - 1;
        for (; i <= (Staff::MAX_TABLATURE_STAFF_TYPE + 1); i++)
        {
            TEST(wxString::Format(wxT("SetTablatureStaffType - %d"), i),
                (staff.SetTablatureStaffType(i) ==
                ((i >= Staff::MIN_TABLATURE_STAFF_TYPE) &&
                (i <= Staff::MAX_TABLATURE_STAFF_TYPE))) &&
                (((i < Staff::MIN_TABLATURE_STAFF_TYPE) ||
                (i > Staff::MAX_TABLATURE_STAFF_TYPE)) ? 1 :
                (staff.GetTablatureStaffType() == i))
            );
        }
    }
    
    return (true);
}

/// Tests the Standard Notation Staff Above Spacing Functions
/// @return True if all tests were executed, false if not
bool StaffTestSuite::TestCaseStandardNotationStaffAboveSpacing()
{
    //------Last Checked------//
    // - Jan 5, 2005
    Staff staff;
    staff.SetStandardNotationStaffAboveSpacing(45);
    TEST(wxT("SetStandardNotationStaffAboveSpacing"),
        staff.GetStandardNotationStaffAboveSpacing() == 45);
    return (true);
}

/// Tests the Standard Notation Staff Below Spacing Functions
/// @return True if all tests were executed, false if not
bool StaffTestSuite::TestCaseStandardNotationStaffBelowSpacing()
{
    //------Last Checked------//
    // - Jan 5, 2005
    Staff staff;
    staff.SetStandardNotationStaffBelowSpacing(45);
    TEST(wxT("SetStandardNotationStaffBelowSpacing"),
        staff.GetStandardNotationStaffBelowSpacing() == 45);
    return (true);
}

/// Tests the Symbol Spacing Functions
/// @return True if all tests were executed, false if not
bool StaffTestSuite::TestCaseSymbolSpacing()
{
    //------Last Checked------//
    // - Jan 5, 2005
    Staff staff;
    staff.SetSymbolSpacing(45);
    TEST(wxT("SetSymbolSpacing"), staff.GetSymbolSpacing() == 45);
    return (true);
}

/// Tests the Tablature Staff Below Spacing Functions
/// @return True if all tests were executed, false if not
bool StaffTestSuite::TestCaseTablatureStaffBelowSpacing()
{
    //------Last Checked------//
    // - Jan 5, 2005
    Staff staff;
    staff.SetTablatureStaffBelowSpacing(45);
    TEST(wxT("SetTablatureStaffBelowSpacing"),
        staff.GetTablatureStaffBelowSpacing() == 45);    
    return (true);
}

/// Tests the Voice Functions
/// @return True if all tests were executed, false if not
bool StaffTestSuite::TestCaseVoice()
{
    //------Last Checked------//
    // - Jan 25, 2005
    
    // TEST CASE: IsValidVoice
    {
        wxUint32 i = 0;
        for (; i <= NUM_STAFF_VOICES; i++)
            TEST(wxString::Format(wxT("IsValidVoice - %d"), i),
                (Staff::IsValidVoice(i) == (i < NUM_STAFF_VOICES))
            );
    }
    return (true);
}

/// Tests the Position Functions
/// @return True if all tests were executed, false if not
bool StaffTestSuite::TestCasePositionArray()
{
    //------Last Checked------//
    // - Jan 25, 2005
    
    Staff staff;
    staff.m_positionArray[0].Add(new Position);
    staff.m_positionArray[1].Add(new Position);
    
    wxUint32 i = 0;
    for (; i <= NUM_STAFF_VOICES; i++)
    {
        wxUint32 j = 0;
        for (; j < 2; j++)
        {
            TEST(wxString::Format(wxT("IsValidPositionIndex - %d, %d"), i, j),
                (staff.IsValidPositionIndex(i, j) ==
                ((i < NUM_STAFF_VOICES) && (j == 0)))
            );
            
            bool valid = ((i < NUM_STAFF_VOICES) && (j == 0));
            bool validPointer = (staff.GetPosition(i, j) != NULL);
            
            TEST(wxString::Format(wxT("GetPosition - %d, %d"), i, j),
                (valid == validPointer)
            );
        }
    }
    
    return (true);
}
