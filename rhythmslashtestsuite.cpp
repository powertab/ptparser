/////////////////////////////////////////////////////////////////////////////
// Name:            rhythmslashtestsuite.cpp
// Purpose:         Performs unit testing on the RhythmSlash class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 5, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "rhythmslashtestsuite.h"

#include "rhythmslash.h"
#include "powertabfileheader.h"         // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(RhythmSlashTestSuite, TestSuite)

/// Default Constructor
RhythmSlashTestSuite::RhythmSlashTestSuite()
{
    //------Last Checked------//
    // - Jan 7, 2005
}

/// Destructor
RhythmSlashTestSuite::~RhythmSlashTestSuite()
{
    //------Last Checked------//
    // - Jan 7, 2005
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t RhythmSlashTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Jan 7, 2005
    return (694);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Jan 7, 2005
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
    if (!TestCaseDurationType())
        return (false);
    if (!TestCaseBeaming())
        return (false);
    if (!TestCaseTriplet())
        return (false);
    if (!TestCaseDotted())
        return (false);
    if (!TestCaseRest())
        return (false);
    if (!TestCaseTied())
        return (false);
    if (!TestCaseMuted())
        return (false);
    if (!TestCaseStaccato())
        return (false);
    if (!TestCasePickStroke())
        return (false);
    if (!TestCaseArpeggio())
        return (false);
    if (!TestCaseTripletFeel())
        return (false);
    if (!TestCaseAccent())
        return (false);
    if (!TestCaseSlideInto())
        return (false);
    if (!TestCaseSlideOutOf())
        return (false);
    if (!TestCaseSingleNoteData())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 7, 2005
    
    // TEST CASE: Default Constructor
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("Default Constructor"),
            (rhythmSlash.m_position == RhythmSlash::DEFAULT_POSITION) &&
            (rhythmSlash.m_beaming == RhythmSlash::DEFAULT_BEAMING) &&
            (rhythmSlash.GetDurationType() == 8) &&
            (rhythmSlash.m_data == RhythmSlash::DEFAULT_DATA)
        );
    }
    
    // TEST CASE: Primary Constructor
    {
        RhythmSlash rhythmSlash(12,4,2);
        TEST(wxT("Primary Constructor"),
            (rhythmSlash.GetPosition() == 12) &&
            (rhythmSlash.m_beaming == 0) &&
            (rhythmSlash.GetDurationType() == 4) &&
            (rhythmSlash.IsDoubleDotted())
        );
    }
    
    // TEST CASE: Copy Constructor
    {
        RhythmSlash rhythmSlash(12,4,2);
        RhythmSlash rhythmSlash2(rhythmSlash);
        TEST(wxT("Copy Constructor"),
            (rhythmSlash == rhythmSlash2)
        );
    }
    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 9, 2005
    
    RhythmSlash rhythmSlash(12,4,2);
    RhythmSlash* clone = (RhythmSlash*)rhythmSlash.CloneObject();
    TEST(wxT("CloneObject"),
        (*clone == rhythmSlash)
    );
    delete clone;
    
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 7, 2005
    
    // TEST CASE: Assignment Operator
    {
        RhythmSlash rhythmSlash(12,4,2);
        RhythmSlash rhythmSlash2 = rhythmSlash;
        TEST(wxT("Operator="), 
            (rhythmSlash == rhythmSlash2)
        );
        
        // TEST CASE: Operator= (self-assignment)
        rhythmSlash = rhythmSlash;
        TEST(wxT("Operator= (self-assignment)"),
            (rhythmSlash == rhythmSlash)
        );
    }
    
    // TEST CASE: Equality Operator
    {
        RhythmSlash rhythmSlash(12,4,2);
        RhythmSlash rhythmSlash2(12,4,2);
        RhythmSlash rhythmSlash3(13,4,2);
        RhythmSlash rhythmSlash4(12,8,2);
        RhythmSlash rhythmSlash5(12,4,1);
        RhythmSlash rhythmSlash6(12,4,2);
        rhythmSlash6.SetPreviousBeamDurationType(8);
        RhythmSlash rhythmSlash7(12,4,2);
        rhythmSlash7.SetBeamStart();
        RhythmSlash rhythmSlash8(12,4,2);
        rhythmSlash8.SetFractionalBeam();
        RhythmSlash rhythmSlash9(12,4,2);
        rhythmSlash9.SetBeamEnd();
        RhythmSlash rhythmSlash10(12,4,2);
        rhythmSlash10.SetTripletStart();
        RhythmSlash rhythmSlash11(12,4,2);
        rhythmSlash11.SetTripletMiddle();
        RhythmSlash rhythmSlash12(12,4,2);
        rhythmSlash12.SetTripletEnd();
        RhythmSlash rhythmSlash13(12,4,2);
        rhythmSlash13.SetDotted();
        RhythmSlash rhythmSlash14(11,4,2);
        rhythmSlash14.SetDoubleDotted();
        RhythmSlash rhythmSlash15(12,4,2);
        rhythmSlash15.SetRest();
        RhythmSlash rhythmSlash16(12,4,2);
        rhythmSlash16.SetTied();
        RhythmSlash rhythmSlash17(12,4,2);
        rhythmSlash17.SetMuted();
        RhythmSlash rhythmSlash18(12,4,2);
        rhythmSlash18.SetStaccato();
        RhythmSlash rhythmSlash19(12,4,2);
        rhythmSlash19.SetPickStrokeUp();
        RhythmSlash rhythmSlash20(12,4,2);
        rhythmSlash20.SetPickStrokeDown();
        RhythmSlash rhythmSlash21(12,4,2);
        rhythmSlash21.SetArpeggioUp();
        RhythmSlash rhythmSlash22(12,4,2);
        rhythmSlash22.SetArpeggioDown();
        RhythmSlash rhythmSlash23(12,4,2);
        rhythmSlash23.SetTripletFeel1st();
        RhythmSlash rhythmSlash24(12,4,2);
        rhythmSlash24.SetTripletFeel2nd();
        RhythmSlash rhythmSlash25(12,4,2);
        rhythmSlash25.SetMarcato();
        RhythmSlash rhythmSlash26(12,4,2);
        rhythmSlash26.SetSforzando();
        RhythmSlash rhythmSlash27(12,4,2);
        rhythmSlash27.SetSlideIntoFromAbove();
        RhythmSlash rhythmSlash28(12,4,2);
        rhythmSlash28.SetSlideIntoFromBelow();        
        RhythmSlash rhythmSlash29(12,4,2);
        rhythmSlash29.SetSlideOutOfDownwards();
        RhythmSlash rhythmSlash30(12,4,2);
        rhythmSlash30.SetSlideOutOfUpwards();
        RhythmSlash rhythmSlash31(12,4,2);
        rhythmSlash31.SetSingleNoteData(4,5);
                
        TEST(wxT("Operator== - rhythmSlash == rhythmSlash"), (rhythmSlash == rhythmSlash2));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash"), !(rhythmSlash == rhythmSlash3));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 2"), !(rhythmSlash == rhythmSlash4));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 3"), !(rhythmSlash == rhythmSlash5));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 4"), !(rhythmSlash == rhythmSlash6));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 5"), !(rhythmSlash == rhythmSlash7));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 6"), !(rhythmSlash == rhythmSlash8));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 7"), !(rhythmSlash == rhythmSlash9));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 8"), !(rhythmSlash == rhythmSlash10));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 9"), !(rhythmSlash == rhythmSlash11));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 10"), !(rhythmSlash == rhythmSlash12));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 11"), !(rhythmSlash == rhythmSlash13));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 12"), !(rhythmSlash == rhythmSlash14));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 13"), !(rhythmSlash == rhythmSlash15));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 14"), !(rhythmSlash == rhythmSlash16));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 15"), !(rhythmSlash == rhythmSlash17));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 16"), !(rhythmSlash == rhythmSlash18));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 17"), !(rhythmSlash == rhythmSlash19));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 18"), !(rhythmSlash == rhythmSlash20));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 19"), !(rhythmSlash == rhythmSlash21));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 20"), !(rhythmSlash == rhythmSlash22));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 21"), !(rhythmSlash == rhythmSlash23));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 22"), !(rhythmSlash == rhythmSlash24));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 23"), !(rhythmSlash == rhythmSlash25));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 24"), !(rhythmSlash == rhythmSlash26));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 25"), !(rhythmSlash == rhythmSlash27));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 26"), !(rhythmSlash == rhythmSlash28));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 27"), !(rhythmSlash == rhythmSlash29));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 28"), !(rhythmSlash == rhythmSlash30));
        TEST(wxT("Operator== - rhythmSlash != rhythmSlash 29"), !(rhythmSlash == rhythmSlash31));
    }
    
    // Inequality Operator
    {
        RhythmSlash rhythmSlash(12,4,2);
        RhythmSlash rhythmSlash2(12,4,2);
        RhythmSlash rhythmSlash3(13,4,2);
        RhythmSlash rhythmSlash4(12,8,2);
        RhythmSlash rhythmSlash5(12,4,1);
        RhythmSlash rhythmSlash6(12,4,2);
        rhythmSlash6.SetPreviousBeamDurationType(8);
        RhythmSlash rhythmSlash7(12,4,2);
        rhythmSlash7.SetBeamStart();
        RhythmSlash rhythmSlash8(12,4,2);
        rhythmSlash8.SetFractionalBeam();
        RhythmSlash rhythmSlash9(12,4,2);
        rhythmSlash9.SetBeamEnd();
        RhythmSlash rhythmSlash10(12,4,2);
        rhythmSlash10.SetTripletStart();
        RhythmSlash rhythmSlash11(12,4,2);
        rhythmSlash11.SetTripletMiddle();
        RhythmSlash rhythmSlash12(12,4,2);
        rhythmSlash12.SetTripletEnd();
        RhythmSlash rhythmSlash13(12,4,2);
        rhythmSlash13.SetDotted();
        RhythmSlash rhythmSlash14(11,4,2);
        rhythmSlash14.SetDoubleDotted();
        RhythmSlash rhythmSlash15(12,4,2);
        rhythmSlash15.SetRest();
        RhythmSlash rhythmSlash16(12,4,2);
        rhythmSlash16.SetTied();
        RhythmSlash rhythmSlash17(12,4,2);
        rhythmSlash17.SetMuted();
        RhythmSlash rhythmSlash18(12,4,2);
        rhythmSlash18.SetStaccato();
        RhythmSlash rhythmSlash19(12,4,2);
        rhythmSlash19.SetPickStrokeUp();
        RhythmSlash rhythmSlash20(12,4,2);
        rhythmSlash20.SetPickStrokeDown();
        RhythmSlash rhythmSlash21(12,4,2);
        rhythmSlash21.SetArpeggioUp();
        RhythmSlash rhythmSlash22(12,4,2);
        rhythmSlash22.SetArpeggioDown();
        RhythmSlash rhythmSlash23(12,4,2);
        rhythmSlash23.SetTripletFeel1st();
        RhythmSlash rhythmSlash24(12,4,2);
        rhythmSlash24.SetTripletFeel2nd();
        RhythmSlash rhythmSlash25(12,4,2);
        rhythmSlash25.SetMarcato();
        RhythmSlash rhythmSlash26(12,4,2);
        rhythmSlash26.SetSforzando();
        RhythmSlash rhythmSlash27(12,4,2);
        rhythmSlash27.SetSlideIntoFromAbove();
        RhythmSlash rhythmSlash28(12,4,2);
        rhythmSlash28.SetSlideIntoFromBelow();        
        RhythmSlash rhythmSlash29(12,4,2);
        rhythmSlash29.SetSlideOutOfDownwards();
        RhythmSlash rhythmSlash30(12,4,2);
        rhythmSlash30.SetSlideOutOfUpwards();
        RhythmSlash rhythmSlash31(12,4,2);
        rhythmSlash31.SetSingleNoteData(4,5);
                
        TEST(wxT("Operator!= - rhythmSlash == rhythmSlash"), !(rhythmSlash != rhythmSlash2));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash"), (rhythmSlash != rhythmSlash3));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 2"), (rhythmSlash != rhythmSlash4));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 3"), (rhythmSlash != rhythmSlash5));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 4"), (rhythmSlash != rhythmSlash6));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 5"), (rhythmSlash != rhythmSlash7));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 6"), (rhythmSlash != rhythmSlash8));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 7"), (rhythmSlash != rhythmSlash9));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 8"), (rhythmSlash != rhythmSlash10));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 9"), (rhythmSlash != rhythmSlash11));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 10"), (rhythmSlash != rhythmSlash12));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 11"), (rhythmSlash != rhythmSlash13));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 12"), (rhythmSlash != rhythmSlash14));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 13"), (rhythmSlash != rhythmSlash15));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 14"), (rhythmSlash != rhythmSlash16));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 15"), (rhythmSlash != rhythmSlash17));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 16"), (rhythmSlash != rhythmSlash18));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 17"), (rhythmSlash != rhythmSlash19));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 18"), (rhythmSlash != rhythmSlash20));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 19"), (rhythmSlash != rhythmSlash21));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 20"), (rhythmSlash != rhythmSlash22));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 21"), (rhythmSlash != rhythmSlash23));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 22"), (rhythmSlash != rhythmSlash24));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 23"), (rhythmSlash != rhythmSlash25));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 24"), (rhythmSlash != rhythmSlash26));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 25"), (rhythmSlash != rhythmSlash27));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 26"), (rhythmSlash != rhythmSlash28));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 27"), (rhythmSlash != rhythmSlash29));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 28"), (rhythmSlash != rhythmSlash30));
        TEST(wxT("Operator!= - rhythmSlash != rhythmSlash 29"), (rhythmSlash != rhythmSlash31));
    }
    
    return (true);
}

/// Tests the Serialization Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Jan 7, 2005
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    RhythmSlash rhythmSlashOut(12, 4, 2);
    rhythmSlashOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        RhythmSlash rhythmSlashIn;
        rhythmSlashIn.Deserialize(streamIn, PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((rhythmSlashIn == rhythmSlashOut)
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the Position Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCasePosition()
{
    //------Last Checked------//
    // - Jan 3, 2005
    
    // TEST CASE: IsValidPosition
    {
        wxUint32 i = RhythmSlash::MIN_POSITION;
        for (; i <= (RhythmSlash::MAX_POSITION + 1); i++)
        {
            TEST(wxString::Format(wxT("IsValidPosition - %d"), i),
                (RhythmSlash::IsValidPosition(i) == (i <= RhythmSlash::MAX_POSITION))
            );
        }
    }
    
    // TEST CASE: SetPosition
    {
        RhythmSlash rhythmSlash;
        wxUint32 i = 0;
        for (; i <= (RhythmSlash::MAX_POSITION + 1); i++)
        {
            TEST(wxT("SetPosition - %d"), 
                (rhythmSlash.SetPosition(i) == (i <= RhythmSlash::MAX_POSITION)) &&
                ((i > RhythmSlash::MAX_POSITION) ? 1 : (rhythmSlash.GetPosition() == i))
            );
        }
    }
    return (true);
}

/// Tests the Duration Type Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseDurationType()
{
    //------Last Checked------//
    // - Jan 6, 2005
    
    // TEST CASE: IsValidDurationType
    {
        TEST(wxT("IsValidDurationType - 0"), !RhythmSlash::IsValidDurationType(0));
        
        wxByte i = 1;
        for (; i <= 32; i = i * 2)
            TEST(wxString::Format(wxT("IsValidDurationType - %d"), i),
                (RhythmSlash::IsValidDurationType(i) == (i < 32))
            );
    }
    
    // TEST CASE: SetDurationType
    {
        RhythmSlash rhythmSlash;
        
        TEST(wxT("SetDurationType - 0"), !rhythmSlash.SetDurationType(0));
        
        wxByte i = 1;
        for (; i <= 32; i = i * 2)
            TEST(wxString::Format(wxT("SetDurationType - %d"), i),
                (rhythmSlash.SetDurationType(i) == (i < 32)) &&
                ((i >= 32) ? 1 : (rhythmSlash.GetDurationType() == i))
            );
    }
    return (true);
}

/// Tests the Beaming Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseBeaming()
{
    //------Last Checked------//
    // - Jan 7, 2005
    
    // TEST CASE: IsValidPreviousBeamDurationType
    {
        TEST(wxT("IsValidPreviousBeamDurationType - 0"), RhythmSlash::IsValidPreviousBeamDurationType(0));
        
        wxByte i = 1;
        for (; i <= 32; i = i * 2)
            TEST(wxString::Format(wxT("IsValidPreviousBeamDurationType - %d"), i),
                (RhythmSlash::IsValidPreviousBeamDurationType(i) == ((i == 0) || (i == 8) || (i == 16)))
            );
    }
    
    // TEST CASE: SetDurationType
    {
        RhythmSlash rhythmSlash;
        
        TEST(wxT("SetPreviousBeamDurationType - 0"), rhythmSlash.SetPreviousBeamDurationType(0));
        
        wxByte i = 1;
        for (; i <= 32; i = i * 2)
            TEST(wxString::Format(wxT("SetPreviousBeamDurationType - %d"), i),
                (rhythmSlash.SetPreviousBeamDurationType(i) == ((i == 0) || (i == 8) || (i == 16))) &&
                (!((i == 0) || (i == 8) || (i == 16)) ? 1 : (rhythmSlash.GetPreviousBeamDurationType() == i))
            );
    }
    
    // TEST CASE: SetBeamStart
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetBeamStart - true"), (rhythmSlash.SetBeamStart() && rhythmSlash.IsBeamStart()));
        TEST(wxT("SetBeamStart - false"), (rhythmSlash.SetBeamStart(false) && !rhythmSlash.IsBeamStart()));
    }
    
    // TEST CASE: SetFractionalBeam
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetFractionalBeam - true"), (rhythmSlash.SetFractionalBeam() && rhythmSlash.HasFractionalBeam()));
        TEST(wxT("SetFractionalBeam - false"), (rhythmSlash.SetFractionalBeam(false) && !rhythmSlash.HasFractionalBeam()));
    }
    
    // TEST CASE: SetBeamEnd
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetBeamEnd - true"), (rhythmSlash.SetBeamEnd() && rhythmSlash.IsBeamEnd()));
        TEST(wxT("SetBeamEnd - false"), (rhythmSlash.SetBeamEnd(false) && !rhythmSlash.IsBeamEnd()));
    }
    
    // TEST CASE: ClearBeam
    {
        RhythmSlash rhythmSlash;
        
        rhythmSlash.SetPreviousBeamDurationType(16);
        rhythmSlash.SetBeamStart();
        TEST(wxT("ClearBeam - beam start"), 
            rhythmSlash.ClearBeam() &&
            (!rhythmSlash.IsBeamStart()) &&
            (rhythmSlash.GetPreviousBeamDurationType() == 0)
        );
        
        rhythmSlash.SetPreviousBeamDurationType(16);
        rhythmSlash.SetFractionalBeam();
        TEST(wxT("ClearBeam - fractional beam"), 
            rhythmSlash.ClearBeam() &&
            (!rhythmSlash.HasFractionalBeam()) &&
            (rhythmSlash.GetPreviousBeamDurationType() == 0)
        );
        
        rhythmSlash.SetPreviousBeamDurationType(16);
        rhythmSlash.SetBeamEnd();
        TEST(wxT("ClearBeam - beam end"), 
            rhythmSlash.ClearBeam() &&
            (!rhythmSlash.IsBeamEnd()) &&
            (rhythmSlash.GetPreviousBeamDurationType() == 0)
        );
    }
    
    return (true);
}

/// Tests the Triplet Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseTriplet()
{
    //------Last Checked------//
    // - Jan 6, 2005
    
    // TEST CASE: IsValidTripletFlag
    {
        const wxUint32 testValueCount = 15;
        wxByte testValues[testValueCount];
        testValues[0] = RhythmSlash::tripletStart;
        testValues[1] = RhythmSlash::tripletMiddle;
        testValues[2] = RhythmSlash::tripletEnd;
        testValues[3] = (RhythmSlash::tripletStart | RhythmSlash::tripletMiddle);
        testValues[4] = (RhythmSlash::tripletStart | RhythmSlash::tripletEnd);
        testValues[5] = (RhythmSlash::tripletMiddle | RhythmSlash::tripletEnd);
        testValues[6] = (RhythmSlash::tripletStart | RhythmSlash::tripletMiddle | RhythmSlash::tripletEnd);
        testValues[7] = 0;
        testValues[8] = (RhythmSlash::tripletStart + 1);
        testValues[9] = (RhythmSlash::tripletMiddle + 1);
        testValues[10] = (RhythmSlash::tripletEnd + 1);
        testValues[11] = (RhythmSlash::tripletStart | RhythmSlash::tripletMiddle + 1);
        testValues[12] = (RhythmSlash::tripletStart | RhythmSlash::tripletEnd + 1);
        testValues[13] = (RhythmSlash::tripletMiddle | RhythmSlash::tripletEnd + 1);
        testValues[14] = (RhythmSlash::tripletStart | RhythmSlash::tripletMiddle | RhythmSlash::tripletEnd + 1);

        wxUint32 i = 0;
        for (; i < testValueCount; i++)
            TEST(wxString::Format(wxT("IsValidTripletFlag - %d"), testValues[i]), RhythmSlash::IsValidTripletFlag(testValues[i]) == (i < 7));
    }
    
    // TEST CASE: SetTripletFlag
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetTripletFlag - 0"), !rhythmSlash.SetTripletFlag(0));
        TEST(wxT("SetTripletFlag - 1"), !rhythmSlash.SetTripletFlag(1));
        TEST(wxT("SetTripletFlag - tripletStart"), 
            rhythmSlash.SetTripletFlag(RhythmSlash::tripletStart) &&
            rhythmSlash.IsTripletFlagSet(RhythmSlash::tripletStart) &&
            rhythmSlash.IsTripletStart() &&
            !rhythmSlash.IsTripletMiddle() &&
            !rhythmSlash.IsTripletEnd()
        );
        TEST(wxT("SetTripletFlag - tripletMiddle"), 
            rhythmSlash.SetTripletFlag(RhythmSlash::tripletMiddle) &&
            rhythmSlash.IsTripletFlagSet(RhythmSlash::tripletMiddle) &&
            !rhythmSlash.IsTripletStart() &&
            rhythmSlash.IsTripletMiddle() &&
            !rhythmSlash.IsTripletEnd()
        );
        
        TEST(wxT("SetTripletFlag - tripletEnd"), 
            rhythmSlash.SetTripletFlag(RhythmSlash::tripletEnd) &&
            rhythmSlash.IsTripletFlagSet(RhythmSlash::tripletEnd) &&
            !rhythmSlash.IsTripletStart() &&
            !rhythmSlash.IsTripletMiddle() &&
            rhythmSlash.IsTripletEnd()
        );           
    }
    
    // TEST CASE: ClearTripletFlag
    {
        const wxUint32 testValueCount = 5;
        wxByte testValues[testValueCount];
        testValues[0] = RhythmSlash::tripletStart;
        testValues[1] = RhythmSlash::tripletMiddle;
        testValues[2] = RhythmSlash::tripletEnd;
        testValues[3] = 0;
        testValues[4] = 1;
        
        RhythmSlash rhythmSlash;
        wxUint32 i = 0;
        for (; i < testValueCount; i++)
        {
            rhythmSlash.SetTripletFlag(testValues[i]);
            TEST(wxString::Format(wxT("ClearTripletFlag - %d"), i),
                (rhythmSlash.ClearTripletFlag(testValues[i]) == (i < 3)) &&
                (!rhythmSlash.IsTripletFlagSet(testValues[i]))
            );
        }
    }
    
    // TEST CASE: SetTripletStart
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetTripletStart - true"), (rhythmSlash.SetTripletStart() && rhythmSlash.IsTripletStart()));
        TEST(wxT("SetTripletStart - false"), (rhythmSlash.SetTripletStart(false) && !rhythmSlash.IsTripletStart()));
    }
    
    // TEST CASE: SetTripletMiddle
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetTripletMiddle - true"), (rhythmSlash.SetTripletMiddle() && rhythmSlash.IsTripletMiddle()));
        TEST(wxT("SetTripletMiddle - false"), (rhythmSlash.SetTripletMiddle(false) && !rhythmSlash.IsTripletMiddle()));
    }
    
    // TEST CASE: SetTripletEnd
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetTripletEnd - true"), (rhythmSlash.SetTripletEnd() && rhythmSlash.IsTripletEnd()));
        TEST(wxT("SetTripletEnd - false"), (rhythmSlash.SetTripletEnd(false) && !rhythmSlash.IsTripletEnd()));
    }
    
    // TEST CASE: ClearTriplet
    {
        RhythmSlash rhythmSlash;
        
        rhythmSlash.SetTripletStart();
        TEST(wxT("ClearTriplet - triplet start"),
            rhythmSlash.ClearTriplet() &&
            !rhythmSlash.IsTripletStart()
        );
        
        rhythmSlash.SetTripletMiddle();
        TEST(wxT("ClearTriplet - triplet middle"),
            rhythmSlash.ClearTriplet() &&
            !rhythmSlash.IsTripletMiddle()
        );
        
        rhythmSlash.SetTripletEnd();
        TEST(wxT("ClearTriplet - triplet start"),
            rhythmSlash.ClearTriplet() &&
            !rhythmSlash.IsTripletEnd()
        );
    }
    
    return (true);
}

/// Tests the Dotted Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseDotted()
{
    //------Last Checked------//
    // - Jan 7, 2005
    
    // TEST CASE: Dotted
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetDotted - true"), (rhythmSlash.SetDotted() && rhythmSlash.IsDotted()));
        TEST(wxT("SetDotted - false"), (rhythmSlash.SetDotted(false) && !rhythmSlash.IsDotted()));
    }
    
    // TEST CASE: Double Dotted
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetDoubleDotted - true"), (rhythmSlash.SetDoubleDotted() && rhythmSlash.IsDoubleDotted()));
        TEST(wxT("SetDoubleDotted - false"), (rhythmSlash.SetDoubleDotted(false) && !rhythmSlash.IsDoubleDotted()));
    }
    
    return (true);
}

/// Tests the Rest Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseRest()
{
    //------Last Checked------//
    // - Jan 7, 2005
    
    RhythmSlash rhythmSlash;
    TEST(wxT("SetRest - true"), (rhythmSlash.SetRest() && rhythmSlash.IsRest()));
    TEST(wxT("SetRest - false"), (rhythmSlash.SetRest(false) && !rhythmSlash.IsRest()));
    
    return (true);
}

/// Tests the Tied Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseTied()
{
    //------Last Checked------//
    // - Jan 7, 2005
    
    RhythmSlash rhythmSlash;
    TEST(wxT("SetTied - true"), (rhythmSlash.SetTied() && rhythmSlash.IsTied()));
    TEST(wxT("SetTied - false"), (rhythmSlash.SetTied(false) && !rhythmSlash.IsTied()));
    
    return (true);
}

/// Tests the Muted Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseMuted()
{
    //------Last Checked------//
    // - Jan 7, 2005
    
    RhythmSlash rhythmSlash;
    TEST(wxT("SetMuted - true"), (rhythmSlash.SetMuted() && rhythmSlash.IsMuted()));
    TEST(wxT("SetMuted - false"), (rhythmSlash.SetMuted(false) && !rhythmSlash.IsMuted()));
    
    return (true);
}

/// Tests the Staccato Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseStaccato()
{
    //------Last Checked------//
    // - Jan 7, 2005
  
    RhythmSlash rhythmSlash;
    TEST(wxT("SetStaccato - true"), (rhythmSlash.SetStaccato() && rhythmSlash.IsStaccato()));
    TEST(wxT("SetStaccato - false"), (rhythmSlash.SetStaccato(false) && !rhythmSlash.IsStaccato()));
    
    return (true);
}

/// Tests the Pick Stroke Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCasePickStroke()
{
    //------Last Checked------//
    // - Jan 7, 2005
    
    // TEST CASE: SetPickStrokeUp
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetPickStrokeUp - true"), (rhythmSlash.SetPickStrokeUp() && rhythmSlash.HasPickStrokeUp()));
        TEST(wxT("SetPickStrokeUp - false"), (rhythmSlash.SetPickStrokeUp(false) && !rhythmSlash.HasPickStrokeUp()));
    }
    
    // TEST CASE: SetPickStrokeDown
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetPickStrokeDown - true"), (rhythmSlash.SetPickStrokeDown() && rhythmSlash.HasPickStrokeDown()));
        TEST(wxT("SetPickStrokeDown - false"), (rhythmSlash.SetPickStrokeDown(false) && !rhythmSlash.HasPickStrokeDown()));
    }
    
    return (true);
}

/// Tests the Arpeggio Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseArpeggio()
{
    //------Last Checked------//
    // - Jan 7, 2005
    
    // TEST CASE: SetArpeggioDown
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetArpeggioDown - true"), (rhythmSlash.SetArpeggioDown() && rhythmSlash.HasArpeggioDown()));
        TEST(wxT("SetArpeggioDown - false"), (rhythmSlash.SetArpeggioDown(false) && !rhythmSlash.HasArpeggioDown()));
    }
    
    // TEST CASE: SetArpeggioUp
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetArpeggioUp - true"), (rhythmSlash.SetArpeggioUp() && rhythmSlash.HasArpeggioUp()));
        TEST(wxT("SetArpeggioUp - false"), (rhythmSlash.SetArpeggioUp(false) && !rhythmSlash.HasArpeggioUp()));
    }
    
    return (true);
}

/// Tests the Triplet Feel Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseTripletFeel()
{
    //------Last Checked------//
    // - Jan 7, 2005
       
    // TEST CASE: SetTripletFeel1st
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetTripletFeel1st - true"), (rhythmSlash.SetTripletFeel1st() && rhythmSlash.IsTripletFeel1st()));
        TEST(wxT("SetTripletFeel1st - false"), (rhythmSlash.SetTripletFeel1st(false) && !rhythmSlash.IsTripletFeel1st()));
    }
    
    // TEST CASE: SetTripletFeel2nd
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetTripletFeel2nd - true"), (rhythmSlash.SetTripletFeel2nd() && rhythmSlash.IsTripletFeel2nd()));
        TEST(wxT("SetTripletFeel2nd - false"), (rhythmSlash.SetTripletFeel2nd(false) && !rhythmSlash.IsTripletFeel2nd()));
    }
    
    return (true);
}

/// Tests the Accent Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseAccent()
{
    //------Last Checked------//
    // - Jan 7, 2005
       
    // TEST CASE: SetMarcato
    {
        RhythmSlash rhythmSlash;    
        TEST(wxT("SetMarcato - true"), (rhythmSlash.SetMarcato() && rhythmSlash.HasMarcato()));
        TEST(wxT("SetMarcato - false"), (rhythmSlash.SetMarcato(false) && !rhythmSlash.HasMarcato()));
    }
    
    // TEST CASE: SetSforzando
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetSforzando - true"), (rhythmSlash.SetSforzando() && rhythmSlash.HasSforzando()));
        TEST(wxT("SetSforzando - false"), (rhythmSlash.SetSforzando(false) && !rhythmSlash.HasSforzando()));
    }
    
    return (true);
}

/// Tests the Slide Into Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseSlideInto()
{
    //------Last Checked------//
    // - Jan 7, 2005
        
    // TEST CASE: SetSlideIntoFromAbove
    {
        RhythmSlash rhythmSlash;   
        TEST(wxT("SetSlideIntoFromAbove - true"), (rhythmSlash.SetSlideIntoFromAbove() && rhythmSlash.HasSlideIntoFromAbove()));
        TEST(wxT("SetSlideIntoFromAbove - false"), (rhythmSlash.SetSlideIntoFromAbove(false) && !rhythmSlash.HasSlideIntoFromAbove()));
    }
    
    // TEST CASE: SetSlideIntoFromBelow
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetSlideIntoFromBelow - true"), (rhythmSlash.SetSlideIntoFromBelow() && rhythmSlash.HasSlideIntoFromBelow()));
        TEST(wxT("SetSlideIntoFromBelow - false"), (rhythmSlash.SetSlideIntoFromBelow(false) && !rhythmSlash.HasSlideIntoFromBelow()));
    }
    
    return (true);
}

/// Tests the Slide Out Of Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseSlideOutOf()
{
    //------Last Checked------//
    // - Jan 7, 2005
   
    // TEST CASE: SetSlideOutOfDownwards
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetSlideOutOfDownwards - true"), (rhythmSlash.SetSlideOutOfDownwards() && rhythmSlash.HasSlideOutOfDownwards()));
        TEST(wxT("SetSlideOutOfDownwards - false"), (rhythmSlash.SetSlideOutOfDownwards(false) && !rhythmSlash.HasSlideOutOfDownwards()));
    }
    
    // TEST CASE: SetSlideOutOfUpwards
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetSlideOutOfUpwards - true"), (rhythmSlash.SetSlideOutOfUpwards() && rhythmSlash.HasSlideOutOfUpwards()));
        TEST(wxT("SetSlideOutOfUpwards - false"), (rhythmSlash.SetSlideOutOfUpwards(false) && !rhythmSlash.HasSlideOutOfUpwards()));
    }
    
    return (true);
}

/// Tests the Single Note Data Functions
/// @return True if all tests were executed, false if not
bool RhythmSlashTestSuite::TestCaseSingleNoteData()
{
    //------Last Checked------//
    // - Jan 6, 2005
    
    // TEST CASE: IsValidStringNumber
    {
        wxByte i = RhythmSlash::MIN_SINGLE_NOTE_STRING_NUMBER - 1;
        for (; i < (RhythmSlash::MIN_SINGLE_NOTE_STRING_NUMBER + 1); i++)
            TEST(wxString::Format(wxT("IsValidStringNumber - %d"), i),
                (RhythmSlash::IsValidStringNumber(i) == ((i >= RhythmSlash::MIN_SINGLE_NOTE_STRING_NUMBER) && (i <= RhythmSlash::MAX_SINGLE_NOTE_STRING_NUMBER)))
            );
    }
    
    // TEST CASE: IsValidFretNumber
    {
        wxByte i = RhythmSlash::MIN_SINGLE_NOTE_FRET_NUMBER - 1;
        for (; i < (RhythmSlash::MIN_SINGLE_NOTE_FRET_NUMBER + 1); i++)
            TEST(wxString::Format(wxT("IsValidFretNumber - %d"), i),
                (RhythmSlash::IsValidFretNumber(i) == ((i >= RhythmSlash::MIN_SINGLE_NOTE_FRET_NUMBER) && (i <= RhythmSlash::MAX_SINGLE_NOTE_FRET_NUMBER)))
            );
    }
    
    // TEST CASE: SetSingleNoteData
    {
        RhythmSlash rhythmSlash;
        TEST(wxT("SetSingleNoteData - invalid string number"), !rhythmSlash.SetSingleNoteData(200, 1));
        TEST(wxT("SetSingleNoteData - invalid fret number"), !rhythmSlash.SetSingleNoteData(1, 200));
        
        bool ok = rhythmSlash.SetSingleNoteData(3,5);
        wxByte stringNumber = 0;
        wxByte fretNumber = 0;
        rhythmSlash.GetSingleNoteData(stringNumber, fretNumber);
        TEST(wxT("SetSingleNoteData"), ok && (stringNumber == 3) && (fretNumber == 5));
    }
    
    // TEST CASE: ClearSingleNoteData
    {
        RhythmSlash rhythmSlash;
        rhythmSlash.SetSingleNoteData(3,5);
        
        bool ok = rhythmSlash.ClearSingleNoteData();
        wxByte stringNumber = 0;
        wxByte fretNumber = 0;
        rhythmSlash.GetSingleNoteData(stringNumber, fretNumber);
            
        TEST(wxT("ClearSingleNoteData"), 
            (ok) &&
            (stringNumber == 0) &&
            (fretNumber == 0)
        );  
    }
    
    return (true);
}
