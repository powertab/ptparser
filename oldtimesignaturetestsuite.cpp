/////////////////////////////////////////////////////////////////////////////
// Name:            oldtimesignaturetestsuite.cpp
// Purpose:         Performs unit testing on the OldTimeSignature class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "oldtimesignaturetestsuite.h"

#include "oldtimesignature.h"
#include "timesignature.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(OldTimeSignatureTestSuite, TestSuite)

/// Default Constructor
OldTimeSignatureTestSuite::OldTimeSignatureTestSuite()
{
    //------Last Checked------//
    // - Jan 3, 2005    
}

/// Destructor
OldTimeSignatureTestSuite::~OldTimeSignatureTestSuite()
{
    //------Last Checked------//
    // - Jan 3, 2005
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t OldTimeSignatureTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Jan 3, 2005
    return (11);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool OldTimeSignatureTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Jan 3, 2005
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseConstruction())
        return (false);
    if (!TestCaseOperator())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool OldTimeSignatureTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 3, 2005
    
    // TEST CASE: Default Constructor
    {
        OldTimeSignature oldTimeSignature;
        TEST(wxT("Default Constructor"), (
            (oldTimeSignature.m_system == OldTimeSignature::DEFAULT_SYSTEM) &&
            (oldTimeSignature.m_position == OldTimeSignature::DEFAULT_POSITION) &&
            (oldTimeSignature.m_data == OldTimeSignature::DEFAULT_DATA)
        ));
    }
    return (true);
}

/// Tests the Construction Functions
/// @return True if all tests were executed, false if not
bool OldTimeSignatureTestSuite::TestCaseConstruction()
{
    //------Last Checked------//
    // - Jan 3, 2005    
    
    OldTimeSignature oldTimeSignature;
    oldTimeSignature.m_system = 10;
    oldTimeSignature.m_position = 11;
    oldTimeSignature.m_data = (11 << 27) + (3 << 24) + 3;  // 12/8, 3 beam
    
    TimeSignature timeSignature;
    bool ok = oldTimeSignature.ConstructTimeSignature(timeSignature);
    wxByte beat1 = 0, beat2 = 0, beat3 = 0, beat4 = 0;
    timeSignature.GetBeamingPattern(beat1, beat2, beat3, beat4);
    TEST(wxT("ConstructTimeSignature"), 
        ok &&
        (timeSignature.GetBeatsPerMeasure() == 12) &&
        (timeSignature.GetBeatAmount() == 8) &&
        (beat1 == 3) &&
        (beat2 == 0) &&
        (beat3 == 0) &&
        (beat4 == 0)
    );
    
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool OldTimeSignatureTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 5, 2005
    
    // TEST CASE: Assignment Operator
    {
        OldTimeSignature oldTimeSignature;
        oldTimeSignature.m_system = 1;
        oldTimeSignature.m_position = 2;
        oldTimeSignature.m_data = 3;
        
        OldTimeSignature oldTimeSignature2 = oldTimeSignature;
        TEST(wxT("Operator="), (oldTimeSignature == oldTimeSignature2));
    }

    // TEST CASE: Equality Operator
    {
        OldTimeSignature oldTimeSignature;
        OldTimeSignature oldTimeSignature2;
        OldTimeSignature oldTimeSignature3;
        oldTimeSignature3.m_system = 1;
        OldTimeSignature oldTimeSignature4;
        oldTimeSignature4.m_position = 2;
        OldTimeSignature oldTimeSignature5;
        oldTimeSignature5.m_data = 3;

        TEST(wxT("Operator== - oldTimeSignature == oldTimeSignature"),
            (oldTimeSignature == oldTimeSignature2));
        TEST(wxT("Operator== - oldTimeSignature != oldTimeSignature"),
            !(oldTimeSignature == oldTimeSignature3));
        TEST(wxT("Operator== - oldTimeSignature != oldTimeSignature 2"),
            !(oldTimeSignature == oldTimeSignature4));
        TEST(wxT("Operator== - oldTimeSignature != oldTimeSignature 3"),
            !(oldTimeSignature == oldTimeSignature5));
    }
    
    // TEST CASE: Inequality Operator
    {
        OldTimeSignature oldTimeSignature;
        OldTimeSignature oldTimeSignature2;
        OldTimeSignature oldTimeSignature3;
        oldTimeSignature3.m_system = 1;
        OldTimeSignature oldTimeSignature4;
        oldTimeSignature4.m_position = 2;
        OldTimeSignature oldTimeSignature5;
        oldTimeSignature5.m_data = 3;

        TEST(wxT("Operator!= - oldTimeSignature == oldTimeSignature"),
            !(oldTimeSignature != oldTimeSignature2));
        TEST(wxT("Operator!= - oldTimeSignature != oldTimeSignature"),
            (oldTimeSignature != oldTimeSignature3));
        TEST(wxT("Operator!= - oldTimeSignature != oldTimeSignature 2"),
            (oldTimeSignature != oldTimeSignature4));
        TEST(wxT("Operator!= - oldTimeSignature != oldTimeSignature 3"),
            (oldTimeSignature != oldTimeSignature5));
    }
        
    return (true);
}
