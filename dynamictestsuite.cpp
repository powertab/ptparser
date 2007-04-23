/////////////////////////////////////////////////////////////////////////////
// Name:            dynamictestsuite.cpp
// Purpose:         Performs unit testing on the Dynamic class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "dynamictestsuite.h"

#include "dynamic.h"
#include "powertabfileheader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(DynamicTestSuite, TestSuite)

/// Default Constructor
DynamicTestSuite::DynamicTestSuite()
{
    //------Last Checked------//
    // - Jan 13, 2005
}

/// Destructor
DynamicTestSuite::~DynamicTestSuite()
{
    //------Last Checked------//
    // - Jan 13, 2005
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t DynamicTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Jan 13, 2005
    return (568);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool DynamicTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Jan 13, 2005
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
    if (!TestCaseVolume())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool DynamicTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 12, 2005
    
    // TEST CASE: Default constructor
    {
        Dynamic dynamic;
        TEST(wxT("Default Constructor"), 
            (dynamic.GetSystem() == Dynamic::DEFAULT_SYSTEM) &&
            (dynamic.GetStaff() == Dynamic::DEFAULT_STAFF) &&
            (dynamic.GetPosition() == Dynamic::DEFAULT_POSITION) &&
            (dynamic.GetStaffVolume() == Dynamic::DEFAULT_STAFF_VOLUME) &&
            (dynamic.GetRhythmSlashVolume() == Dynamic::DEFAULT_RHYTHM_SLASH_VOLUME)
        );
    }
    
    // TEST CASE: Primary constructor
    {
        Dynamic dynamic(1,2,3,Dynamic::ff,Dynamic::mf);
        TEST(wxT("Primary Constructor"), 
            (dynamic.GetSystem() == 1) &&
            (dynamic.GetStaff() == 2) &&
            (dynamic.GetPosition() == 3) &&
            (dynamic.GetStaffVolume() == Dynamic::ff) &&
            (dynamic.GetRhythmSlashVolume() == Dynamic::mf)
        );
    }
    
    // TEST CASE: Copy constructor
    {
        Dynamic dynamic(1,2,3,Dynamic::ff,Dynamic::mf);
        Dynamic dynamic2(dynamic);
        TEST(wxT("Copy Constructor"), 
            (dynamic == dynamic2)
        );
    }
        
    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool DynamicTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 12, 2005
    Dynamic dynamic(1,2,3,Dynamic::ff,Dynamic::mf);
    Dynamic* clone = (Dynamic*)dynamic.CloneObject();
    TEST(wxT("CloneObject"),
        (*clone == dynamic)
    );
    delete clone;
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool DynamicTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 12, 2005
    
    // TEST CASE: Assignment Operator
    {
        Dynamic dynamic(1,2,3,Dynamic::ff,Dynamic::mf);
        Dynamic dynamic2 = dynamic;
        TEST(wxT("Operator="), 
            (dynamic == dynamic2)
        );
        
        // TEST CASE: Operator= (self-assignment)
        dynamic = dynamic;
        TEST(wxT("Operator= (self-assignment)"),
            (dynamic == dynamic)
        );
    }

    // TEST CASE: Equality Operator
    {
        Dynamic dynamic(1,2,3,Dynamic::ff,Dynamic::mf);
        Dynamic dynamic2(1,2,3,Dynamic::ff,Dynamic::mf);
        Dynamic dynamic3(2,2,3,Dynamic::ff,Dynamic::mf);
        Dynamic dynamic4(1,3,3,Dynamic::ff,Dynamic::mf);
        Dynamic dynamic5(1,2,4,Dynamic::ff,Dynamic::mf);
        Dynamic dynamic6(1,2,3,Dynamic::fff,Dynamic::mf);
        Dynamic dynamic7(1,2,3,Dynamic::ff,Dynamic::f);
        
        TEST(wxT("Operator== - dynamic == dynamic"), (dynamic == dynamic2));
        TEST(wxT("Operator== - dynamic != dynamic"), !(dynamic == dynamic3));
        TEST(wxT("Operator== - dynamic != dynamic 2"), !(dynamic == dynamic4));
        TEST(wxT("Operator== - dynamic != dynamic 3"), !(dynamic == dynamic5));
        TEST(wxT("Operator== - dynamic != dynamic 4"), !(dynamic == dynamic6));
        TEST(wxT("Operator== - dynamic != dynamic 5"), !(dynamic == dynamic7));
    }
    
    // TEST CASE: Inequality Operator
    {
        Dynamic dynamic(1,2,3,Dynamic::ff,Dynamic::mf);
        Dynamic dynamic2(1,2,3,Dynamic::ff,Dynamic::mf);
        Dynamic dynamic3(2,2,3,Dynamic::ff,Dynamic::mf);
        Dynamic dynamic4(1,3,3,Dynamic::ff,Dynamic::mf);
        Dynamic dynamic5(1,2,4,Dynamic::ff,Dynamic::mf);
        Dynamic dynamic6(1,2,3,Dynamic::fff,Dynamic::mf);
        Dynamic dynamic7(1,2,3,Dynamic::ff,Dynamic::f);
        
        TEST(wxT("Operator!= - dynamic == dynamic"), !(dynamic != dynamic2));
        TEST(wxT("Operator!= - dynamic != dynamic"), (dynamic != dynamic3));
        TEST(wxT("Operator!= - dynamic != dynamic 2"), (dynamic != dynamic4));
        TEST(wxT("Operator!= - dynamic != dynamic 3"), (dynamic != dynamic5));
        TEST(wxT("Operator!= - dynamic != dynamic 4"), (dynamic != dynamic6));
        TEST(wxT("Operator!= - dynamic != dynamic 5"), (dynamic != dynamic7));
    }
        
    return (true);
}

/// Tests the Serialization Functions
/// @return True if all tests were executed, false if not
bool DynamicTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Jan 12, 2005
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    Dynamic dynamicOut(1,2,3,Dynamic::f,Dynamic::mf);
    dynamicOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        Dynamic dynamicIn;
        dynamicIn.Deserialize(streamIn, PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((dynamicIn == dynamicOut)
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
       
    return (true);
}

/// Tests the System Functions
/// @return True if all tests were executed, false if not
bool DynamicTestSuite::TestCaseSystem()
{
    //------Last Checked------//
    // - Jan 12, 2005
    
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
                (Dynamic::IsValidSystem(testValues[i]) == (i < 3))
            );
        }
    }
    
    // TEST CASE: SetSystem
    {
        Dynamic dynamic;
        
        wxUint32 i = 0;
        for (; i < testValueCount; i++)
        {
            TEST(wxString::Format(wxT("SetSystem - %d"), testValues[i]),
                (dynamic.SetSystem(testValues[i]) == (i < 3)) &&
                ((i == 3) ? 1 : (dynamic.GetSystem() == testValues[i]))
            );
        }
    }
    return (true);
}

/// Tests the Staff Functions
/// @return True if all tests were executed, false if not
bool DynamicTestSuite::TestCaseStaff()
{
    //------Last Checked------//
    // - Jan 12, 2005
    
    // TEST CASE: IsValidStaff
    {
        wxUint32 i = 0;
        for (; i <= (Dynamic::MAX_STAFF + 1); i++)
        {
            TEST(wxString::Format(wxT("IsValidStaff - %d"), i),
                (Dynamic::IsValidStaff(i) == (i <= Dynamic::MAX_STAFF))
            );
        }
    }
    
    // TEST CASE: SetStaff
    {
        Dynamic dynamic;
        wxUint32 i = 0;
        for (; i <= (Dynamic::MAX_STAFF + 1); i++)
        {
            TEST(wxString::Format(wxT("SetStaff - %d"), i),
                (dynamic.SetStaff(i) == (i <= Dynamic::MAX_STAFF)) &&
                ((i > Dynamic::MAX_STAFF) ? 1 : (dynamic.GetStaff() == i))
            );
        }
    }
    
    return (true);
}

/// Tests the Position Functions
/// @return True if all tests were executed, false if not
bool DynamicTestSuite::TestCasePosition()
{
    //------Last Checked------//
    // - Jan 12, 2005
    
    // TEST CASE: IsValidPosition
    {
        wxUint32 i = 0;
        for (; i <= (Dynamic::MAX_POSITION + 1); i++)
        {
            TEST(wxString::Format(wxT("IsValidPosition - %d"), i),
                (Dynamic::IsValidPosition(i) == (i <= Dynamic::MAX_POSITION))
            );
        }
    }
    
    // TEST CASE: SetPosition
    {
        Dynamic dynamic;
        wxUint32 i = 0;
        for (; i <= (Dynamic::MAX_POSITION + 1); i++)
        {
            TEST(wxString::Format(wxT("SetPosition - %d"), i),
                (dynamic.SetPosition(i) == (i <= Dynamic::MAX_POSITION)) &&
                ((i > Dynamic::MAX_POSITION) ? 1 : (dynamic.GetPosition() == i))
            );
        }
    }
    return (true);
}
    
/// Tests the Volume Functions
/// @return True if all tests were executed, false if not
bool DynamicTestSuite::TestCaseVolume()
{
    //------Last Checked------//
    // - Jan 12, 2005
    
    // TEST CASE: IsValidVolume
    {
        const wxUint32 testValueCount = 11;
        
        wxByte testValues[testValueCount];
        testValues[0] = Dynamic::notSet;
        testValues[1] = Dynamic::fff;
        testValues[2] = Dynamic::ff;
        testValues[3] = Dynamic::f;
        testValues[4] = Dynamic::mf;
        testValues[5] = Dynamic::mp;
        testValues[6] = Dynamic::p;
        testValues[7] = Dynamic::pp;
        testValues[8] = Dynamic::ppp;
        testValues[9] = Dynamic::off;
        testValues[10] = Dynamic::notSet - 1;
        
        wxUint32 i = 0;
        for (; i < testValueCount; i++)
            TEST(wxString::Format(wxT("IsValidVolume - %d"), i),
                (Dynamic::IsValidVolume(testValues[i]) == (testValues[i] != (Dynamic::notSet - 1)))
            );
    }
    
    // TEST CASE: SetStaffVolume
    {
        Dynamic dynamic;
        TEST(wxT("SetStaffVolume - invalid volume"), !dynamic.SetStaffVolume(Dynamic::notSet - 1));
        TEST(wxT("SetStaffVolume - valid volume"), 
            (dynamic.SetStaffVolume(Dynamic::ff)) &&
            (dynamic.GetStaffVolume() == Dynamic::ff) &&
            (dynamic.IsStaffVolumeSet())
        );
    }

    // TEST CASE: SetRhythmSlashVolume
    {
        Dynamic dynamic;
        TEST(wxT("SetRhythmSlashVolume - invalid volume"), !dynamic.SetRhythmSlashVolume(Dynamic::notSet - 1));
        TEST(wxT("SetRhythmSlashVolume - valid volume"), 
            (dynamic.SetRhythmSlashVolume(Dynamic::ff)) &&
            (dynamic.GetRhythmSlashVolume() == Dynamic::ff) &&
            (dynamic.IsRhythmSlashVolumeSet())
        );
    }
    
    // TEST CASE: SetVolume
    {
        Dynamic dynamic;
        TEST(wxT("SetVolume - invalid staff volume"), !dynamic.SetVolume(false, Dynamic::notSet - 1));
        TEST(wxT("SetVolume - staff valid"), 
            (dynamic.SetVolume(false, Dynamic::ff)) &&
            (dynamic.GetVolume(false) == Dynamic::ff) &&
            (dynamic.IsVolumeSet(false))
        );
        
        TEST(wxT("SetVolume - invalid rhythm slash volume"), !dynamic.SetVolume(true, Dynamic::notSet - 1));
        TEST(wxT("SetVolume - rhythm slash valid"), 
            (dynamic.SetVolume(true, Dynamic::ff)) &&
            (dynamic.GetVolume(true) == Dynamic::ff) &&
            (dynamic.IsVolumeSet(true))
        );
    }
    return (true);
}
