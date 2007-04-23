/////////////////////////////////////////////////////////////////////////////
// Name:            barlinetestsuite.cpp
// Purpose:         Performs unit testing on the Barline class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 4, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "barlinetestsuite.h"

#include "barline.h"
#include "powertabfileheader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(BarlineTestSuite, TestSuite)

/// Default Constructor
BarlineTestSuite::BarlineTestSuite()
{
    //------Last Checked------//
    // - Jan 4, 2005
}

/// Destructor
BarlineTestSuite::~BarlineTestSuite()
{
    //------Last Checked------//
    // - Jan 4, 2005
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t BarlineTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Jan 4, 2005
    return (605);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool BarlineTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Jan 4, 2005
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
    if (!TestCaseBarlineData())
        return (false);
    if (!TestCaseType())
        return (false);
    if (!TestCaseRepeatCount())
        return (false);
    if (!TestCaseKeySignature())
        return (false);
    if (!TestCaseTimeSignature())
        return (false);
    if (!TestCaseRehearsalSign())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool BarlineTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 4, 2005
    
    // TEST CASE: Default Constructor
    {
        Barline barline;
        TEST(wxT("Default Constructor"),
            (barline.GetPosition() == Barline::DEFAULT_POSITION) &&
            (barline.GetType() == Barline::bar) &&
            (barline.GetRepeatCount() == 0)
        );
    }
    
    // TEST CASE: Primary Constructor
    {
        Barline barline(14, Barline::repeatEnd, 12);
        TEST(wxT("Primary Constructor"),
            (barline.GetPosition() == 14) &&
            (barline.GetType() == Barline::repeatEnd) &&
            (barline.GetRepeatCount() == 12)
        );
    }
    
    // TEST CASE: Copy Constructor
    {
        Barline barline(14, Barline::repeatEnd, 12);
        Barline barline2(barline);
        TEST(wxT("Copy Constructor"),
            (barline2 == barline)
        );
    }
    return (true);
}

/// Tests the Creation Functions
bool BarlineTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 12, 2005
    Barline barline(14,Barline::repeatEnd,12);
    Barline* clone = (Barline*)barline.CloneObject();
    TEST(wxT("CloneObject"),
        (*clone == barline)
    );
    delete clone;
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool BarlineTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 4, 2005
    
    // TEST CASE: Operator=
    {
        Barline barline(14, Barline::repeatEnd, 12);
        Barline barline2 = barline;
        TEST(wxT("Operator="),
            (barline2 == barline)
        );
        
        // TEST CASE: Self-assignment
        barline = barline;
        TEST(wxT("Operator= (self-assignment"),
            (barline == barline)
        );
    }
    
    // TEST CASE: Operator==
    {
        Barline barline(14, Barline::repeatEnd, 12);
        Barline barline2(14, Barline::repeatEnd, 12);
        Barline barline3(15, Barline::repeatEnd, 12);
        Barline barline4(14, Barline::repeatStart, 12);
        Barline barline5(14, Barline::repeatEnd, 13);
        Barline barline6(14, Barline::repeatEnd, 12);
        barline6.GetKeySignatureRef().SetKeyAccidentals(KeySignature::fiveFlats);
        Barline barline7(14, Barline::repeatEnd, 12);
        barline7.GetTimeSignatureRef().SetMeter(12,8);
        Barline barline8(14, Barline::repeatEnd, 12);
        barline8.GetRehearsalSignRef().SetLetter(wxT('Z'));
                
        TEST(wxT("Operator== barline == barline"), (barline == barline2));
        TEST(wxT("Operator== barline != barline"), !(barline == barline3));
        TEST(wxT("Operator== barline != barline 2"), !(barline == barline4));
        TEST(wxT("Operator== barline != barline 3"), !(barline == barline5));        
        TEST(wxT("Operator== barline != barline 4"), !(barline == barline6));
        TEST(wxT("Operator== barline != barline 5"), !(barline == barline7));
        TEST(wxT("Operator== barline != barline 6"), !(barline == barline8));
    }
    
    // TEST CASE: Operator!=
    {
        Barline barline(14, Barline::repeatEnd, 12);
        Barline barline2(14, Barline::repeatEnd, 12);
        Barline barline3(15, Barline::repeatEnd, 12);
        Barline barline4(14, Barline::repeatStart, 12);
        Barline barline5(14, Barline::repeatEnd, 13);
        Barline barline6(14, Barline::repeatEnd, 12);
        barline6.GetKeySignatureRef().SetKeyAccidentals(KeySignature::fiveFlats);
        Barline barline7(14, Barline::repeatEnd, 12);
        barline7.GetTimeSignatureRef().SetMeter(12,8);
        Barline barline8(14, Barline::repeatEnd, 12);
        barline8.GetRehearsalSignRef().SetLetter(wxT('Z'));

        TEST(wxT("Operator!= barline == barline"), !(barline != barline2));
        TEST(wxT("Operator!= barline != barline"), (barline != barline3));
        TEST(wxT("Operator!= barline != barline 2"), (barline != barline4));
        TEST(wxT("Operator!= barline != barline 3"), (barline != barline5));
        TEST(wxT("Operator!= barline != barline 4"), (barline != barline6));
        TEST(wxT("Operator!= barline != barline 5"), (barline != barline7));
        TEST(wxT("Operator!= barline != barline 6"), (barline != barline8));
    }
    
    return (true);
}

/// Tests the Serialization Functions
/// @return True if all tests were executed, false if not
bool BarlineTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Jan 4, 2005
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    Barline barlineOut(12, Barline::repeatEnd, 12);
    barlineOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        Barline barlineIn;
        barlineIn.Deserialize(streamIn, PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((barlineIn == barlineOut)
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the Position Functions
/// @return True if all tests were executed, false if not
bool BarlineTestSuite::TestCasePosition()
{
    //------Last Checked------//
    // - Jan 4, 2005
    Barline barline;
    
    // TEST CASE: IsValidPosition
    {
        wxUint32 i = 0;
        for (; i <= 256; i++)
        {
            TEST(wxString::Format(wxT("IsValidPosition - %d"), i),
                (Barline::IsValidPosition(i) == (i < 256))
            );
        }
    }
    
    // TEST CASE: SetPosition
    {
        wxUint32 i = 0;
        for (; i <= 256; i++)
        {
            TEST(wxString::Format(wxT("SetPosition - %d"), i),
                (barline.SetPosition(i) == (i < 256)) &&
                ((i == 256) ? 1 : (barline.GetPosition() == i))
            );
        }
    }
    return (true);
}

/// Tests the Barline Data Functions
/// @return True if all tests were executed, false if not
bool BarlineTestSuite::TestCaseBarlineData()
{
    //------Last Checked------//
    // - Jan 4, 2005
    Barline barline;
    bool ok = barline.SetBarlineData(Barline::repeatEnd, 14);
    
    wxByte type = 0, repeatCount = 0;
    barline.GetBarlineData(type, repeatCount);
    
    TEST(wxT("SetBarlineData"), 
        (ok) &&
        (type == Barline::repeatEnd) &&
        (repeatCount == 14)
    );
    
    return (true);
}

/// Tests the Type Functions
/// @return True if all tests were executed, false if not
bool BarlineTestSuite::TestCaseType()
{
    //------Last Checked------//
    // - Jan 4, 2005
    
    // TEST CASE: IsValidType
    {
        wxByte i = Barline::bar;
        for (; i <= (Barline::doubleBarFine + 1); i++)
        {
            TEST(wxString::Format(wxT("IsValidType - %d"), i), 
                (Barline::IsValidType(i) == (i <= Barline::doubleBarFine))
            );
        }
    }
    
    // TEST CASE: SetType
    {
        Barline barline;
        wxByte i = Barline::bar;
        for (; i <= (Barline::doubleBarFine + 1); i++)
        {
            TEST(wxString::Format(wxT("SetType - %d"), i), 
                (barline.SetType(i) == (i <= Barline::doubleBarFine)) &&
                ((i > Barline::doubleBarFine) ? 1 : ((barline.GetType() == i)) &&
                (barline.IsBar() == (i == Barline::bar)) &&
                (barline.IsDoubleBar() == (i == Barline::doubleBar)) &&
                (barline.IsFreeTimeBar() == (i == Barline::freeTimeBar)) &&
                (barline.IsRepeatStart() == (i == Barline::repeatStart)) &&
                (barline.IsRepeatEnd() == (i == Barline::repeatEnd)) &&
                (barline.IsDoubleBarFine() == (i == Barline::doubleBarFine)))
            );
        }
    }
    return (true);
}

/// Tests the Repeat Count Functions
/// @return True if all tests were executed, false if not
bool BarlineTestSuite::TestCaseRepeatCount()
{
    //------Last Checked------//
    // - Jan 4, 2005
    
    // TEST CASE: IsValidRepeatCount
    {
        TEST(wxT("IsValidRepeatCount - 0"), Barline::IsValidRepeatCount(0));
        
        wxByte i = Barline::MIN_REPEAT_COUNT - 1;
        for (; i <= (Barline::MAX_REPEAT_COUNT + 1); i++)
        {
            TEST(wxString::Format(wxT("IsValidRepeatCount - %d"), i),
                (Barline::IsValidRepeatCount(i) == ((i >= Barline::MIN_REPEAT_COUNT) && (i <= Barline::MAX_REPEAT_COUNT)))
            );         
        }
    }
    
    // TEST CASE: SetRepeatCount
    {
        Barline barline;
        TEST(wxT("SetRepeatCount - 0"), (barline.SetRepeatCount(0) && (barline.GetRepeatCount() == 0)));
        wxByte i = Barline::MIN_REPEAT_COUNT - 1;
        for (; i <= (Barline::MAX_REPEAT_COUNT + 1); i++)
        {
            TEST(wxString::Format(wxT("SetRepeatCount - %d"), i),
                (barline.SetRepeatCount(i) == ((i >= Barline::MIN_REPEAT_COUNT) && (i <= Barline::MAX_REPEAT_COUNT))) &&
                (((i < Barline::MIN_REPEAT_COUNT) || (i > Barline::MAX_REPEAT_COUNT)) ? 1 : (barline.GetRepeatCount() == i))
            );
        }
    }
    return (true);
}

/// Tests the Key Signature Functions
/// @return True if all tests were executed, false if not
bool BarlineTestSuite::TestCaseKeySignature()
{
    //------Last Checked------//
    // - Jan 4, 2005
    KeySignature keySignature(KeySignature::minorKey, KeySignature::fiveSharps);
    Barline barline;
    barline.SetKeySignature(keySignature);
    TEST(wxT("SetKeySignature"), 
        (barline.GetKeySignatureConstRef() == keySignature)
    );    
    return (true);
}

/// Tests the Time Signature Functions
/// @return True if all tests were executed, false if not
bool BarlineTestSuite::TestCaseTimeSignature()
{
    //------Last Checked------//
    // - Jan 4, 2005
    TimeSignature timeSignature(12,8);
    Barline barline;
    barline.SetTimeSignature(timeSignature);
    TEST(wxT("SetTimeSignature"), 
        (barline.GetTimeSignatureConstRef() == timeSignature)
    );
    return (true);
}

/// Tests the Rehearsal Sign Functions
/// @return True if all tests were executed, false if not
bool BarlineTestSuite::TestCaseRehearsalSign()
{
    //------Last Checked------//
    // - Jan 4, 2005
    RehearsalSign rehearsalSign('Z', wxT("Test"));
    Barline barline;
    barline.SetRehearsalSign(rehearsalSign);
    TEST(wxT("SetRehearsalSign"), 
        (barline.GetRehearsalSignConstRef() == rehearsalSign)
    );
    return (true);
}
