/////////////////////////////////////////////////////////////////////////////
// Name:            guitarintestsuite.cpp
// Purpose:         Performs unit testing on the GuitarIn class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "guitarintestsuite.h"

#include "guitarin.h"
#include "powertabfileheader.h"     // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(GuitarInTestSuite, TestSuite)

/// Default Constructor
GuitarInTestSuite::GuitarInTestSuite()
{
    //------Last Checked------//
    // - Jan 25, 2005
}

/// Destructor
GuitarInTestSuite::~GuitarInTestSuite()
{
    //------Last Checked------//
    // - Jan 25, 2005
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t GuitarInTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Jan 25, 2005
    return (557);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool GuitarInTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Jan 25, 2005
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseCreation())
        return (false);
    if (!TestCaseOperator())
        return (false);
    if (!TestCaseSerialize())
        return (false);
    if (!TestCaseSystem())
        return (false);
    if (!TestCaseStaff())
        return (false);
    if (!TestCasePosition())
        return (false);
    if (!TestCaseGuitars())
        return (false);
    if (!TestCaseOperations())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool GuitarInTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 25, 2005
    
    // TEST CASE: Default constructor
    {
        GuitarIn guitarIn;
        TEST(wxT("Default Constructor"), 
            (guitarIn.GetSystem() == GuitarIn::DEFAULT_SYSTEM) &&
            (guitarIn.GetStaff() == GuitarIn::DEFAULT_STAFF) &&
            (guitarIn.GetPosition() == GuitarIn::DEFAULT_POSITION) &&
            (guitarIn.m_data == GuitarIn::DEFAULT_DATA)
        );
    }
    
    // TEST CASE: Primary constructor
    {
        GuitarIn guitarIn(1,2,3,4,2);
        TEST(wxT("Primary Constructor"), 
            (guitarIn.GetSystem() == 1) &&
            (guitarIn.GetStaff() == 2) &&
            (guitarIn.GetPosition() == 3) &&
            (guitarIn.GetStaffGuitars() == 4) &&
            (guitarIn.GetRhythmSlashGuitars() == 2)
        );
    }
    
    // TEST CASE: Copy constructor
    {
        GuitarIn guitarIn(1,2,3,4,2);
        GuitarIn guitarIn2(guitarIn);
        TEST(wxT("Copy Constructor"), 
            (guitarIn == guitarIn2)
        );
    }
        
    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool GuitarInTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 25, 2005
    GuitarIn guitarIn(1,2,3,4,2);
    GuitarIn* clone = (GuitarIn*)guitarIn.CloneObject();
    TEST(wxT("CloneObject"),
        (*clone == guitarIn)
    );
    delete clone;
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool GuitarInTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 25, 2005
    
    // TEST CASE: Assignment Operator
    {
        GuitarIn guitarIn(1,2,3,4,2);
        GuitarIn guitarIn2 = guitarIn;
        TEST(wxT("Operator="), 
            (guitarIn == guitarIn2)
        );
        
        // TEST CASE: Operator= (self-assignment)
        guitarIn = guitarIn;
        TEST(wxT("Operator= (self-assignment)"),
            (guitarIn == guitarIn)
        );
    }

    // TEST CASE: Equality Operator
    {
        GuitarIn guitarIn(1,2,3,4,2);
        GuitarIn guitarIn2(1,2,3,4,2);
        GuitarIn guitarIn3(2,2,3,4,2);
        GuitarIn guitarIn4(1,3,3,4,2);
        GuitarIn guitarIn5(1,2,4,4,2);
        GuitarIn guitarIn6(1,2,3,8,2);
        GuitarIn guitarIn7(1,2,3,4,4);
        
        TEST(wxT("Operator== - guitarIn == guitarIn"),
            (guitarIn == guitarIn2));
        TEST(wxT("Operator== - guitarIn != guitarIn"),
            !(guitarIn == guitarIn3));
        TEST(wxT("Operator== - guitarIn != guitarIn 2"),
            !(guitarIn == guitarIn4));
        TEST(wxT("Operator== - guitarIn != guitarIn 3"),
            !(guitarIn == guitarIn5));
        TEST(wxT("Operator== - guitarIn != guitarIn 4"),
            !(guitarIn == guitarIn6));
        TEST(wxT("Operator== - guitarIn != guitarIn 5"),
            !(guitarIn == guitarIn7));
    }
    
    // TEST CASE: Inequality Operator
    {
        GuitarIn guitarIn(1,2,3,4,2);
        GuitarIn guitarIn2(1,2,3,4,2);
        GuitarIn guitarIn3(2,2,3,4,2);
        GuitarIn guitarIn4(1,3,3,4,2);
        GuitarIn guitarIn5(1,2,4,4,2);
        GuitarIn guitarIn6(1,2,3,8,2);
        GuitarIn guitarIn7(1,2,3,4,4);
        
        TEST(wxT("Operator!= - guitarIn == guitarIn"),
            !(guitarIn != guitarIn2));
        TEST(wxT("Operator!= - guitarIn != guitarIn"),
            (guitarIn != guitarIn3));
        TEST(wxT("Operator!= - guitarIn != guitarIn 2"),
            (guitarIn != guitarIn4));
        TEST(wxT("Operator!= - guitarIn != guitarIn 3"),
            (guitarIn != guitarIn5));
        TEST(wxT("Operator!= - guitarIn != guitarIn 4"),
            (guitarIn != guitarIn6));
        TEST(wxT("Operator!= - guitarIn != guitarIn 5"),
            (guitarIn != guitarIn7));
    }
        
    return (true);
}

/// Tests the Serialization Functions
/// @return True if all tests were executed, false if not
bool GuitarInTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Jan 25, 2005
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    GuitarIn guitarInOut(1,2,3,4,2);
    guitarInOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        GuitarIn guitarInIn;
        guitarInIn.Deserialize(streamIn,
            PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((guitarInIn == guitarInOut)
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
       
    return (true);
}

/// Tests the System Functions
/// @return True if all tests were executed, false if not
bool GuitarInTestSuite::TestCaseSystem()
{
    //------Last Checked------//
    // - Jan 25, 2005
    
    // Note: Using a loop to test all values runs too slow
    const wxUint32 testValueCount = 4;
    wxUint32 testValues[testValueCount];
    testValues[0] = 0;
    testValues[1] = 16384;
    testValues[2] = 65535;
    testValues[3] = 65536;
    
    // TEST CASE: IsValidSystem
    {
        wxUint32 i = 0;
        for (; i < testValueCount; i++)
        {
            TEST(wxString::Format(wxT("IsValidSystem - %d"), testValues[i]),
                (GuitarIn::IsValidSystem(testValues[i]) == (i < 3))
            );
        }
    }
    
    // TEST CASE: SetSystem
    {
        GuitarIn guitarIn;
        
        wxUint32 i = 0;
        for (; i < testValueCount; i++)
        {
            TEST(wxString::Format(wxT("SetSystem - %d"), testValues[i]),
                (guitarIn.SetSystem(testValues[i]) == (i < 3)) &&
                ((i == 3) ? 1 : (guitarIn.GetSystem() == testValues[i]))
            );
        }
    }
    return (true);
}

/// Tests the Staff Functions
/// @return True if all tests were executed, false if not
bool GuitarInTestSuite::TestCaseStaff()
{
    //------Last Checked------//
    // - Jan 25, 2005
    
    // TEST CASE: IsValidStaff
    {
        wxUint32 i = 0;
        for (; i <= (GuitarIn::MAX_STAFF + 1); i++)
        {
            TEST(wxString::Format(wxT("IsValidStaff - %d"), i),
                (GuitarIn::IsValidStaff(i) == (i <= GuitarIn::MAX_STAFF))
            );
        }
    }
    
    // TEST CASE: SetStaff
    {
        GuitarIn guitarIn;
        wxUint32 i = 0;
        for (; i <= (GuitarIn::MAX_STAFF + 1); i++)
        {
            TEST(wxString::Format(wxT("SetStaff - %d"), i),
                (guitarIn.SetStaff(i) == (i <= GuitarIn::MAX_STAFF)) &&
                ((i > GuitarIn::MAX_STAFF) ? 1 : (guitarIn.GetStaff() == i))
            );
        }
    }
    
    return (true);
}

/// Tests the Position Functions
/// @return True if all tests were executed, false if not
bool GuitarInTestSuite::TestCasePosition()
{
    //------Last Checked------//
    // - Jan 25, 2005
    
    // TEST CASE: IsValidPosition
    {
        wxUint32 i = 0;
        for (; i <= (GuitarIn::MAX_POSITION + 1); i++)
        {
            TEST(wxString::Format(wxT("IsValidPosition - %d"), i),
                (GuitarIn::IsValidPosition(i) == (i <= GuitarIn::MAX_POSITION))
            );
        }
    }
    
    // TEST CASE: SetPosition
    {
        GuitarIn guitarIn;
        wxUint32 i = 0;
        for (; i <= (GuitarIn::MAX_POSITION + 1); i++)
        {
            TEST(wxString::Format(wxT("SetPosition - %d"), i),
                (guitarIn.SetPosition(i) == (i <= GuitarIn::MAX_POSITION)) &&
                ((i > GuitarIn::MAX_POSITION) ? 1 :
                    (guitarIn.GetPosition() == i))
            );
        }
    }
    return (true);
}
    
/// Tests the Guitars Functions
/// @return True if all tests were executed, false if not
bool GuitarInTestSuite::TestCaseGuitars()
{
    //------Last Checked------//
    // - Jan 25, 2005
    
    // TEST CASE: SetStaffGuitars
    {
        GuitarIn guitarIn;
        TEST(wxT("SetStaffGuitars"), 
            (guitarIn.SetStaffGuitars(4)) &&
            (guitarIn.GetStaffGuitars() == 4) &&
            (guitarIn.HasStaffGuitarsSet())
        );
    }

    // TEST CASE: SetRhythmSlashGuitars
    {
        GuitarIn guitarIn;
        TEST(wxT("SetRhythmSlashGuitars"), 
            (guitarIn.SetRhythmSlashGuitars(2)) &&
            (guitarIn.GetRhythmSlashGuitars() == 2) &&
            (guitarIn.HasRhythmSlashGuitarsSet())
        );
    }
    
    // TEST CASE: SetGuitars
    {
        GuitarIn guitarIn;
        TEST(wxT("SetGuitars - staff"), 
            (guitarIn.SetGuitars(false, 4)) &&
            (guitarIn.GetGuitars(false) == 4) &&
            (guitarIn.HasGuitarsSet(false))
        );
        
        TEST(wxT("SetGuitars - rhythm slash"), 
            (guitarIn.SetGuitars(true, 2)) &&
            (guitarIn.GetGuitars(true) == 2) &&
            (guitarIn.HasGuitarsSet(true))
        );
    }
    return (true);
}

/// Tests the Operations Functions
/// @return True if all tests were executed, false if not
bool GuitarInTestSuite::TestCaseOperations()
{
    //------Last Checked------//
    // - Jan 25, 2005
    
    // TEST CASE: GetText
    {
        GuitarIn guitarIn;
        TEST(wxT("GetText - staff empty"),
            (guitarIn.GetText(false) == wxT(""))
        );
        GuitarIn guitarIn2;
        TEST(wxT("GetText - rhythm slash empty"),
            (guitarIn.GetText(true) == wxT(""))
        );
           
        GuitarIn guitarIn3(1,2,3,0x7f,2);
        TEST(wxT("GetText - staff"),
            (guitarIn3.GetText(false) == wxT("Gtrs I, II, III, IV, V, VI, VII"))
        );
        TEST(wxT("GetText - rhythm slash"),
            (guitarIn3.GetText(true) == wxT("Gtr II"))
        );
    }
    return (true);
}
