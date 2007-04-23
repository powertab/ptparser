/////////////////////////////////////////////////////////////////////////////
// Name:            powertabobjecttestsuite.cpp
// Purpose:         Performs unit testing on the PowerTabObject class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 24, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "powertabobjecttestsuite.h"

#include "powertabobject.h"                 // Test class
#include "powertabfileheader.h"             // Needed for file version constants
#include "floatingtext.h"                   // Test class used during serialization

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(PowerTabObjectTestSuite, TestSuite)

/// Default Constructor
PowerTabObjectTestSuite::PowerTabObjectTestSuite()
{
    //------Last Checked------//
    // - Dec 24, 2004
}

/// Destructor
PowerTabObjectTestSuite::~PowerTabObjectTestSuite()
{
    //------Last Checked------//
    // - Dec 24, 2004
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t PowerTabObjectTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Dec 27, 2004
    return (2);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool PowerTabObjectTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Dec 27, 2004
    if (!TestCaseCreateObject())
        return (false);    
    if (!TestCaseMFCClassInformation())
        return (false);
    return (true);
}

/// Tests the CreateObject Function
/// @return True if all tests were executed, false it not
bool PowerTabObjectTestSuite::TestCaseCreateObject()
{
    //------Last Checked------//
    // - Dec 27, 2004
    
    TEST(wxT("CreateObject - invalid class id"), (PowerTabObject::CreateObject(wxT("Dummy")) == NULL));
    
    return (true);
}

/// Tests the MFC Class Information Functions
/// @return True if all tests were executed, false if not
bool PowerTabObjectTestSuite::TestCaseMFCClassInformation()
{
    //------Last Checked------//
    // - Dec 24, 2004

    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    FloatingText floatingText;
    floatingText.WriteMFCClassInformation(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        wxString classId = wxT("");
        ok = ((floatingText.ReadMFCClassInformation(streamIn, PowerTabFileHeader::FILEVERSION_CURRENT, classId)) &&
                (classId == wxT("CFloatingText-1")) &&
                (streamIn.CheckState())
        );
    }
    
    TEST(wxT("WriteMFCClassInformation"), ok);
    
    return (true);
}
