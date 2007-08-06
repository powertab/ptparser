/////////////////////////////////////////////////////////////////////////////
// Name:            keysignaturetestsuite.cpp
// Purpose:         Performs unit testing on the KeySignature class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "keysignaturetestsuite.h"

#include "keysignature.h"
#include "powertabfileheader.h"         // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(KeySignatureTestSuite, TestSuite)

/// Default Constructor
KeySignatureTestSuite::KeySignatureTestSuite()
{
    //------Last Checked------//
    // - Dec 10, 2004
}

/// Destructor
KeySignatureTestSuite::~KeySignatureTestSuite()
{
    //------Last Checked------//
    // - Dec 10, 2004
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t KeySignatureTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Dec 11, 2004
    return (293);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool KeySignatureTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Dec 11, 2004
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseCreation())
        return (false);
    if (!TestCaseOperator())
        return (false);
    if (!TestCaseSerialize())
        return (false);
    if (!TestCaseKey())
        return (false);
    if (!TestCaseKeyType()) 
        return (false);
    if (!TestCaseKeyAccidentals()) 
        return (false);
    if (!TestCaseShow()) 
        return (false);
    if (!TestCaseCancellation()) 
        return (false);
    if (!TestCaseFlag())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool KeySignatureTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Dec 11, 2004
    
    // TEST CASE: Default Constructor
    {
        KeySignature keySignature;
        TEST(wxT("Default Constructor"),
            (keySignature.IsMajorKey()) &&
            (keySignature.IsMajorKey()) &&
            (!keySignature.IsShown()) &&
            (!keySignature.IsCancellation())
        );
    }
    
    // TEST CASE: Primary Constructor
    {
        KeySignature keySignature(KeySignature::minorKey,
            KeySignature::threeFlats);
        TEST(wxT("Primary Constructor"),
            (keySignature.IsMinorKey()) &&
            (keySignature.HasThreeFlats()) &&
            (!keySignature.IsShown()) &&
            (!keySignature.IsCancellation())
        );
    }

    // TEST CASE: Copy Constructors
    {
        KeySignature keySignature(KeySignature::minorKey,
            KeySignature::threeFlats);
        KeySignature keySignature2(keySignature);
        TEST(wxT("Copy Constructor"),
            (keySignature2.IsMinorKey()) &&
            (keySignature2.HasThreeFlats()) &&
            (!keySignature.IsShown()) &&
            (!keySignature.IsCancellation())
        );
    }
    
    return (true);
}

/// Tests the Creation Functions
bool KeySignatureTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 12, 2005
    KeySignature keySignature(KeySignature::minorKey, KeySignature::threeFlats);
    KeySignature* clone = (KeySignature*)keySignature.CloneObject();    
    TEST(wxT("CloneObject"),
        (*clone == keySignature)
    );
    delete clone;
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool KeySignatureTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Dec 11, 2004

    // TEST CASE: operator=
    {
        KeySignature keySignature(KeySignature::minorKey,
            KeySignature::threeFlats);
        KeySignature keySignature2 = keySignature;
        TEST(wxT("Operator="),
            (keySignature2.IsMinorKey()) &&
            (keySignature2.HasThreeFlats()) &&
            (!keySignature.IsShown()) &&
            (!keySignature.IsCancellation())
        );
        
        // TEST CASE: Operator= (self assignment)
        keySignature = keySignature;
        TEST(wxT("Operator= (self-assignment)"),
            (keySignature == keySignature)
        );
    }
    
    // TEST CASE: Operator==
    {
        KeySignature keySignature(KeySignature::minorKey,
            KeySignature::threeFlats);
        KeySignature keySignature2(KeySignature::minorKey,
            KeySignature::threeFlats);
        KeySignature keySignature3(KeySignature::majorKey,
            KeySignature::threeFlats);
        KeySignature keySignature4(KeySignature::minorKey,
            KeySignature::fourFlats);
        KeySignature keySignature5(KeySignature::minorKey,
            KeySignature::threeFlats);
        keySignature5.SetCancellation();
        KeySignature keySignature6(KeySignature::minorKey,
            KeySignature::threeFlats);
        keySignature6.Show();
        TEST(wxT("Operator== - keySignature == keySignature"),
            (keySignature == keySignature2));
        TEST(wxT("Operator== - keySignature != keySignature"),
            !(keySignature == keySignature3));
        TEST(wxT("Operator== - keySignature != keySignature 2"),
            !(keySignature == keySignature4));
        TEST(wxT("Operator== - keySignature != keySignature 3"),
            !(keySignature == keySignature5));
        TEST(wxT("Operator== - keySignature != keySignature 4"),
            !(keySignature == keySignature6));
    }
    
    // TEST CASE: Operator!=
    {
        KeySignature keySignature(KeySignature::minorKey,
            KeySignature::threeFlats);
        KeySignature keySignature2(KeySignature::minorKey,
            KeySignature::threeFlats);
        KeySignature keySignature3(KeySignature::majorKey,
            KeySignature::threeFlats);
        KeySignature keySignature4(KeySignature::minorKey,
            KeySignature::fourFlats);
        KeySignature keySignature5(KeySignature::minorKey,
            KeySignature::threeFlats);
        keySignature5.SetCancellation();
        KeySignature keySignature6(KeySignature::minorKey,
            KeySignature::threeFlats);
        keySignature6.Show();
        TEST(wxT("Operator!= - keySignature == keySignature"),
            !(keySignature != keySignature2));
        TEST(wxT("Operator!= - keySignature != keySignature"),
            (keySignature != keySignature3));
        TEST(wxT("Operator!= - keySignature != keySignature 2"),
            (keySignature != keySignature4));
        TEST(wxT("Operator!= - keySignature != keySignature 3"),
            (keySignature != keySignature5));
        TEST(wxT("Operator!= - keySignature != keySignature 4"),
            (keySignature != keySignature6));
    }
    
    return (true);
}

/// Tests Serialization
/// @return True if all tests were executed, false if not
bool KeySignatureTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Dec 10, 2004
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    KeySignature keySignatureOut(KeySignature::minorKey,
        KeySignature::threeFlats);
    keySignatureOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        KeySignature keySignatureIn;
        keySignatureIn.Deserialize(streamIn,
            PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((keySignatureIn == keySignatureOut) 
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the Key Functions
/// @return True if all tests were executed, false if not
bool KeySignatureTestSuite::TestCaseKey()
{
    //------Last Checked------//
    // - Dec 11, 2004
    KeySignature keySignature;
    TEST(wxT("SetKey - invalid key type"),
        !keySignature.SetKey(44, KeySignature::threeFlats));
    TEST(wxT("SetKey - invalid key accidentals"),
        !keySignature.SetKey(KeySignature::minorKey, 44));
    TEST(wxT("SetKey - valid"),
        keySignature.SetKey(KeySignature::minorKey, KeySignature::threeFlats) &&
        (keySignature.GetKeyType() == KeySignature::minorKey) &&
        (keySignature.GetKeyAccidentals() == KeySignature::threeFlats)
    );
    
    // TEST CASE: IsSameKey
    {
        KeySignature keySignature(KeySignature::minorKey,
            KeySignature::threeFlats);
        keySignature.Show();
        KeySignature keySignature2(KeySignature::minorKey,
            KeySignature::threeFlats);
        KeySignature keySignature3(KeySignature::majorKey,
            KeySignature::threeFlats);
        KeySignature keySignature4(KeySignature::minorKey,
            KeySignature::fourFlats);
        TEST(wxT("IsSameKey - true"), keySignature.IsSameKey(keySignature2));
        TEST(wxT("IsSameKey - false"), !keySignature.IsSameKey(keySignature3));
        TEST(wxT("IsSameKey - false"), !keySignature.IsSameKey(keySignature4));
    }
    return (true);
}

/// Tests the Key Type Functions
/// @return True if all tests were executed, false if not
bool KeySignatureTestSuite::TestCaseKeyType()
{
    //------Last Checked------//
    // - Dec 11, 2004

    // TEST CASE: IsValidKeyType
    {
        wxByte i = KeySignature::majorKey;
        for (; i <= (KeySignature::minorKey + 1); i++)
        {
            TEST(wxString::Format(wxT("IsValidKeyType - %d"), i), 
                (KeySignature::IsValidKeyType(i) == (i <= KeySignature::minorKey))
            );
        }
    }
    
    KeySignature keySignature;
    wxByte i = KeySignature::majorKey;
    for (; i <= (KeySignature::minorKey + 1); i++)
    {
        TEST(wxString::Format(wxT("SetKeyType - %d"), i), 
                (keySignature.SetKeyType(i) == (i <= KeySignature::minorKey)) &&
                ((i > KeySignature::minorKey) ? 1 :
                    (keySignature.GetKeyType() == i))
            );
    }
    return (true);
}

/// Tests the Key Accidentals Functions
/// @return True if all tests were executed, false if not
bool KeySignatureTestSuite::TestCaseKeyAccidentals()
{
    //------Last Checked------//
    // - Dec 11, 2004
    
    // TEST CASE: IsValidKeyAccidentals
    {
        wxByte i = KeySignature::noAccidentals;
        for (; i <= (KeySignature::sevenFlats + 1); i++)
        {
            TEST(wxString::Format(wxT("IsValidKeyAccidentals - %d"), i), 
                (KeySignature::IsValidKeyAccidentals(i) ==
                    (i <= KeySignature::sevenFlats))
            );
        }
    }
    
    KeySignature keySignature;
    wxByte i = KeySignature::noAccidentals;
    for (; i <= (KeySignature::sevenFlats + 1); i++)
    {
        TEST(wxString::Format(wxT("SetKeyAccidentals - %d"), i), 
                (keySignature.SetKeyAccidentals(i) ==
                    (i <= KeySignature::sevenFlats)) &&
                ((i > KeySignature::sevenFlats) ? 1 :
                    (keySignature.GetKeyAccidentals() == i))
            );
    }
            
    // TEST CASE: HasNAccidentals
    {
        KeySignature keySignature;
        wxByte i = KeySignature::noAccidentals;
        for (; i <= KeySignature::sevenFlats; i++)
        {
            keySignature.SetKeyAccidentals(i);
            TEST(wxString::Format(wxT("HasNoKeyAccidentals - %d"), i),
                (keySignature.HasNoKeyAccidentals() == (i == KeySignature::noAccidentals)));
            TEST(wxString::Format(wxT("HasOneSharp - %d"), i),
                (keySignature.HasOneSharp() == (i == KeySignature::oneSharp)));
            TEST(wxString::Format(wxT("HasTwoSharps - %d"), i),
                (keySignature.HasTwoSharps() == (i == KeySignature::twoSharps)));
            TEST(wxString::Format(wxT("HasThreeSharps - %d"), i),
                (keySignature.HasThreeSharps() == (i == KeySignature::threeSharps)));
            TEST(wxString::Format(wxT("HasFourSharps - %d"), i),
                (keySignature.HasFourSharps() == (i == KeySignature::fourSharps)));
            TEST(wxString::Format(wxT("HasFiveSharps - %d"), i),
                (keySignature.HasFiveSharps() == (i == KeySignature::fiveSharps)));
            TEST(wxString::Format(wxT("HasSixSharps - %d"), i),
                (keySignature.HasSixSharps() == (i == KeySignature::sixSharps)));
            TEST(wxString::Format(wxT("HasSevenSharps - %d"), i),
                (keySignature.HasSevenSharps() == (i == KeySignature::sevenSharps)));
            TEST(wxString::Format(wxT("HasOneFlat - %d"), i),
                (keySignature.HasOneFlat() == (i == KeySignature::oneFlat)));
            TEST(wxString::Format(wxT("HasTwoFlats - %d"), i),
                (keySignature.HasTwoFlats() == (i == KeySignature::twoFlats)));
            TEST(wxString::Format(wxT("HasThreeFlats - %d"), i),
                (keySignature.HasThreeFlats() == (i == KeySignature::threeFlats)));
            TEST(wxString::Format(wxT("HasFourFlats - %d"), i),
                (keySignature.HasFourFlats() == (i == KeySignature::fourFlats)));
            TEST(wxString::Format(wxT("HasFiveFlats - %d"), i),
                (keySignature.HasFiveFlats() == (i == KeySignature::fiveFlats)));
            TEST(wxString::Format(wxT("HasSixFlats - %d"), i),
                (keySignature.HasSixFlats() == (i == KeySignature::sixFlats)));
            TEST(wxString::Format(wxT("HasSevenFlats - %d"), i),
                (keySignature.HasSevenFlats() == (i == KeySignature::sevenFlats)));
        }   
    }
    return (true);
}

/// Tests the Show Functions
/// @return True if all tests were executed, false if not
bool KeySignatureTestSuite::TestCaseShow()
{
    //------Last Checked------//
    // - Dec 11, 2004
    KeySignature keySignature;
    keySignature.Show();
    TEST(wxT("Show - true"), keySignature.IsShown());
    keySignature.Hide();
    TEST(wxT("Show - false"), !keySignature.IsShown());
    return (true);
}

/// Tests the Cancellation Functions
/// @return True if all tests were executed, false if not
bool KeySignatureTestSuite::TestCaseCancellation()
{
    //------Last Checked------//
    // - Dec 11, 2004
    KeySignature keySignature;
    keySignature.SetCancellation();
    TEST(wxT("SetCancellation - true"), keySignature.IsCancellation());
    keySignature.SetCancellation(false);
    TEST(wxT("SetCancellation - false"), !keySignature.IsCancellation());
    return (true);
}

/// Tests the Flag Functions
/// @return True if all tests were executed, false if not
bool KeySignatureTestSuite::TestCaseFlag()
{
    //------Last Checked------//
    // - Dec 13, 2004
    const int testValueCount = 3;
    wxUint32 testValues[testValueCount];
    testValues[0] = KeySignature::show;
    testValues[1] = KeySignature::cancellation;
    testValues[2] = 255;
    
    KeySignature keySignature;
    int i = 0;
    for (; i < testValueCount; i++)
    {
        keySignature.SetFlag(testValues[i]);
        TEST(wxString::Format(wxT("SetFlag - 0x%x"), testValues[i]),
            ((keySignature.SetFlag(testValues[i]) == (i < 2)) &&
            (keySignature.IsFlagSet(testValues[i]) == (i < 2))));
    }
    return (true);
}
