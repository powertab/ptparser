/////////////////////////////////////////////////////////////////////////////
// Name:            systemsymboltestsuite.cpp
// Purpose:         Performs unit testing on the SystemSymbol class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 13, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "systemsymboltestsuite.h"

#include "systemsymbol.h"
#include "powertabfileheader.h"         // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(SystemSymbolTestSuite, TestSuite)

/// Default Constructor
SystemSymbolTestSuite::SystemSymbolTestSuite()
{
    //------Last Checked------//
    // - Jan 13, 2005
}

/// Destructor
SystemSymbolTestSuite::~SystemSymbolTestSuite()
{
    //------Last Checked------//
    // - Jan 13, 2005
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t SystemSymbolTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Jan 13, 2005
    return (538);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool SystemSymbolTestSuite::RunTestCases()
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
    if (!TestCasePosition())
        return (false);
    if (!TestCaseData())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool SystemSymbolTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 13, 2005
        
    // TEST CASE: Default constructor
    {
        SystemSymbol systemSymbol;
        TEST(wxT("Default Constructor"),
            (systemSymbol.GetSystem() == SystemSymbol::DEFAULT_SYSTEM) && 
            (systemSymbol.GetPosition() == SystemSymbol::DEFAULT_POSITION) &&
            (systemSymbol.GetData() == SystemSymbol::DEFAULT_DATA)
        );        
    }
    
    // TEST CASE: Primary constructor
    {
        SystemSymbol systemSymbol(1,2,3);
        TEST(wxT("Primary Constructor"), 
            (systemSymbol.GetSystem() == 1) && 
            (systemSymbol.GetPosition() == 2) &&
            (systemSymbol.GetData() == 3)
        );
    }
    
    // TEST CASE: Copy constructor
    {
        SystemSymbol systemSymbol(1,2,3);
        SystemSymbol systemSymbol2(systemSymbol);
        TEST(wxT("Copy Constructor"), 
            (systemSymbol2 == systemSymbol)
        );
    }
    
    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool SystemSymbolTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 12, 2005   
    SystemSymbol systemSymbol(1,2,3);
    SystemSymbol* clone = (SystemSymbol*)systemSymbol.CloneObject();
    TEST(wxT("CloneObject"),
        (*clone == systemSymbol)
    );
    delete clone;
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool SystemSymbolTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 13, 2005
                
    // TEST CASE: Operator=
    {
        SystemSymbol systemSymbol(1,2,3);
        SystemSymbol systemSymbol2 = systemSymbol;
        TEST(wxT("Operator="), 
            (systemSymbol2 == systemSymbol)
        );
        
        systemSymbol = systemSymbol;
        TEST(wxT("Operator= (self-assignment)"),
            (systemSymbol == systemSymbol)
        );
    }
    
    // TEST CASE: Operator==
    {
        SystemSymbol systemSymbol(1,2,3);
        SystemSymbol systemSymbol2(1,2,3);
        SystemSymbol systemSymbol3(2,2,3);
        SystemSymbol systemSymbol4(1,3,3);
        SystemSymbol systemSymbol5(1,2,4);
               
        TEST(wxT("Operator== - systemSymbol == systemSymbol"),
            (systemSymbol == systemSymbol2));
        TEST(wxT("Operator== - systemSymbol != systemSymbol"),
            !(systemSymbol == systemSymbol3));
        TEST(wxT("Operator== - systemSymbol != systemSymbol 2"),
            !(systemSymbol == systemSymbol4));
        TEST(wxT("Operator== - systemSymbol != systemSymbol 3"),
            !(systemSymbol == systemSymbol4));
    }
        
    // TEST CASE: Operator!=
    {
        SystemSymbol systemSymbol(1,2,3);
        SystemSymbol systemSymbol2(1,2,3);
        SystemSymbol systemSymbol3(2,2,3);
        SystemSymbol systemSymbol4(1,3,3);
        SystemSymbol systemSymbol5(1,2,4);
               
        TEST(wxT("Operator!= - systemSymbol == systemSymbol"),
            !(systemSymbol != systemSymbol2));
        TEST(wxT("Operator!= - systemSymbol != systemSymbol"),
            (systemSymbol != systemSymbol3));
        TEST(wxT("Operator!= - systemSymbol != systemSymbol 2"),
            (systemSymbol != systemSymbol4));
        TEST(wxT("Operator!= - systemSymbol != systemSymbol 3"),
            (systemSymbol != systemSymbol5));
    }

    return (true);
}

/// Tests the Serialization Fucntions
/// @return True if all tests were executed, false if not
bool SystemSymbolTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Jan 3, 2005
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    SystemSymbol systemSymbolOut(1,2,3);
    systemSymbolOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        SystemSymbol systemSymbolIn;
        systemSymbolIn.Deserialize(streamIn,
            PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((systemSymbolIn == systemSymbolOut) 
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the System Functions
/// @return True if all tests were executed, false if not
bool SystemSymbolTestSuite::TestCaseSystem()
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
                (SystemSymbol::IsValidSystem(testValues[i]) == (i < 3))
            );
        }
    }
    
    // TEST CASE: SetSystem
    {
        SystemSymbol systemSymbol;
        
        wxUint32 i = 0;
        for (; i < testValueCount; i++)
        {
            TEST(wxString::Format(wxT("SetSystem - %d"), testValues[i]),
                (systemSymbol.SetSystem(testValues[i]) == (i < 3)) &&
                ((i == 3) ? 1 : (systemSymbol.GetSystem() == testValues[i]))
            );
        }
    }
    return (true);
}

/// Tests the Position Functions
/// @return True if all tests were executed, false if not
bool SystemSymbolTestSuite::TestCasePosition()
{
    //------Last Checked------//
    // - Jan 13, 2005
    
    // TEST CASE: IsValidPosition
    {
        wxUint32 i = 0;
        for (; i <= (SystemSymbol::MAX_POSITION + 1); i++)
        {
            TEST(wxString::Format(wxT("IsValidPosition - %d"), i),
                (SystemSymbol::IsValidPosition(i) ==
                (i <= SystemSymbol::MAX_POSITION))
            );
        }
    }
    
    // TEST CASE: SetPosition
    {
        SystemSymbol systemSymbol;
        wxUint32 i = 0;
        for (; i <= (SystemSymbol::MAX_POSITION + 1); i++)
        {
            TEST(wxString::Format(wxT("SetPosition - %d"), i),
                (systemSymbol.SetPosition(i) ==
                (i <= SystemSymbol::MAX_POSITION)) &&
                ((i > SystemSymbol::MAX_POSITION) ? 1 :
                (systemSymbol.GetPosition() == i))
            );
        }
    }
    return (true);
}

/// Tests the Data Functions
/// @return True if all tests were executed, false if not
bool SystemSymbolTestSuite::TestCaseData()
{
    //------Last Checked------//
    // - Jan 13, 2005
    SystemSymbol systemSymbol;
    systemSymbol.SetData(12);
    TEST(wxT("SetData"), (systemSymbol.GetData() == 12));
    return (true);
}
