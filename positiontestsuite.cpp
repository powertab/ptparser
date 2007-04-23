/////////////////////////////////////////////////////////////////////////////
// Name:            positiontestsuite.cpp
// Purpose:         Performs unit testing on the Position class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 5, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "positiontestsuite.h"

#include "position.h"
#include "powertabfileheader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(PositionTestSuite, TestSuite)

/// Default Constructor
PositionTestSuite::PositionTestSuite()
{
    //------Last Checked------//
    // - Dec 10, 2004
}

/// Destructor
PositionTestSuite::~PositionTestSuite()
{
    //------Last Checked------//
    // - Dec 10, 2004
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t PositionTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Dec 10, 2004
    return (1730);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool PositionTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Dec 10, 2004
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
    if (!TestCaseIrregularGrouping())
        return (false);
    if (!TestCaseBeaming())
        return (false);
    if (!TestCaseDotted())
        return (false);
    if (!TestCaseRest())
        return (false);
    if (!TestCaseVibrato())
        return (false);
    if (!TestCaseArpeggio())
        return (false);
    if (!TestCasePickStroke())
        return (false);
    if (!TestCaseStaccato())
        return (false);
    if (!TestCaseAccent())
        return (false);
    if (!TestCaseTremoloPicking())
        return (false);
    if (!TestCasePalmMuting())
        return (false);
    if (!TestCaseTap())
        return (false);
    if (!TestCaseGraceNotes())
        return (false);
    if (!TestCaseTripletFeel())
        return (false);
    if (!TestCaseLetRing())
        return (false);
    if (!TestCaseFermata())
        return (false);
    if (!TestCaseIrregularGrouping())
        return (false);
    if (!TestCaseVolumeSwell())
        return (false);
    if (!TestCaseTremoloBar())
        return (false);
    if (!TestCaseMultibarRest())
        return (false);
    if (!TestCaseComplexSymbol())
        return (false);
    if (!TestCaseNoteArray())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 18, 2005
    
    // TEST CASE: Default Constructor
    {
        Position position;
        TEST(wxT("Default Constructor"),
            (position.m_position == Position::DEFAULT_POSITION) &&
            (position.m_beaming == Position::DEFAULT_BEAMING) &&
            (position.GetDurationType() == 8) &&
            (position.m_data == Position::DEFAULT_DATA)
        );
    }
    
    // TEST CASE: Primary Constructor
    {
        Position position(12,4,2);
        TEST(wxT("Primary Constructor"),
            (position.GetPosition() == 12) &&
            (position.m_beaming == 0) &&
            (position.GetDurationType() == 4) &&
            (position.IsDoubleDotted())
        );
    }
    
    // TEST CASE: Copy Constructor
    {
        Position position(12,4,2);
        Position position2(position);
        TEST(wxT("Copy Constructor"),
            (position == position2)
        );
    }
    
    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 18, 2005
    Position position(12,4,2);
    Position* clone = (Position*)position.CloneObject();
    TEST(wxT("CloneObject"),
        (*clone == position)
    );
    delete clone;
    
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 18, 2005
    
    // TEST CASE: Assignment Operator
    {
        Position position(12,4,2);
        Position position2 = position;
        TEST(wxT("Operator="), 
            (position == position2)
        );
        
        // TEST CASE: Operator= (self-assignment)
        position = position;
        TEST(wxT("Operator= (self-assignment)"),
            (position == position)
        );
    }
    
    // TEST CASE: Equality Operator
    {
        Position position(12,4,2);
        Position position2(12,4,2);
        Position position3(13,4,2);
        Position position4(12,8,2);
        Position position5(12,4,1);
        Position position6(12,4,2);
        position6.SetIrregularGroupingTiming(3,2);
        Position position7(12,4,2);
        position7.SetPreviousBeamDurationType(16);
        Position position8(12,4,2);
        position8.SetBeamStart();
        Position position9(12,4,2);
        position9.SetFractionalLeftBeam();
        Position position10(12,4,2);
        position10.SetFractionalRightBeam();
        Position position11(12,4,2);
        position11.SetBeamEnd();
        Position position12(12,4,2);
        position12.SetDotted();
        Position position13(12,4,2);
        position13.SetRest();
        Position position14(12,4,2);
        position14.SetVibrato();
        Position position15(12,4,2);
        position15.SetWideVibrato();
        Position position16(12,4,2);
        position16.SetArpeggioUp();
        Position position17(12,4,2);
        position17.SetArpeggioDown();
        Position position18(12,4,2);
        position18.SetPickStrokeUp();
        Position position19(12,4,2);
        position19.SetPickStrokeDown();
        Position position20(12,4,2);
        position20.SetStaccato();
        Position position21(12,4,2);
        position21.SetMarcato();
        Position position22(12,4,2);
        position22.SetSforzando();
        Position position23(12,4,2);
        position23.SetTremoloPicking();
        Position position24(12,4,2);
        position24.SetPalmMuting();
        Position position25(12,4,2);
        position25.SetTap();
        Position position26(12,4,2);
        position26.SetAcciaccatura();
        Position position27(12,4,2);
        position27.SetTripletFeel1st();
        Position position28(12,4,2);
        position28.SetTripletFeel2nd();
        Position position29(12,4,2);
        position29.SetLetRing();
        Position position30(12,4,2);
        position30.SetFermata();
        Position position31(12,4,2);
        position31.SetIrregularGroupingStart();
        Position position32(12,4,2);
        position32.SetIrregularGroupingMiddle();
        Position position33(12,4,2);
        position33.SetIrregularGroupingEnd();
        Position position34(12,4,2);
        position34.SetVolumeSwell(Dynamic::off, Dynamic::mp, 1);
        Position position35(12,4,2);
        position35.SetTremoloBar(Position::invertedDip, 1, 12);
        
        TEST(wxT("Operator== - position == position"), (position == position2));
        TEST(wxT("Operator== - position != position"), !(position == position3));
        TEST(wxT("Operator== - position != position 2"), !(position == position4));
        TEST(wxT("Operator== - position != position 3"), !(position == position5));
        TEST(wxT("Operator== - position != position 4"), !(position == position6));
        TEST(wxT("Operator== - position != position 5"), !(position == position7));
        TEST(wxT("Operator== - position != position 6"), !(position == position8));
        TEST(wxT("Operator== - position != position 7"), !(position == position9));
        TEST(wxT("Operator== - position != position 8"), !(position == position10));
        TEST(wxT("Operator== - position != position 9"), !(position == position11));
        TEST(wxT("Operator== - position != position 10"), !(position == position12));
        TEST(wxT("Operator== - position != position 11"), !(position == position13));
        TEST(wxT("Operator== - position != position 12"), !(position == position14));
        TEST(wxT("Operator== - position != position 13"), !(position == position15));
        TEST(wxT("Operator== - position != position 14"), !(position == position16));
        TEST(wxT("Operator== - position != position 15"), !(position == position17));
        TEST(wxT("Operator== - position != position 16"), !(position == position18));
        TEST(wxT("Operator== - position != position 17"), !(position == position19));
        TEST(wxT("Operator== - position != position 18"), !(position == position20));
        TEST(wxT("Operator== - position != position 19"), !(position == position21));
        TEST(wxT("Operator== - position != position 20"), !(position == position22));
        TEST(wxT("Operator== - position != position 21"), !(position == position23));
        TEST(wxT("Operator== - position != position 22"), !(position == position24));
        TEST(wxT("Operator== - position != position 23"), !(position == position25));
        TEST(wxT("Operator== - position != position 24"), !(position == position26));
        TEST(wxT("Operator== - position != position 25"), !(position == position27));
        TEST(wxT("Operator== - position != position 26"), !(position == position28));
        TEST(wxT("Operator== - position != position 27"), !(position == position29));
        TEST(wxT("Operator== - position != position 28"), !(position == position30));
        TEST(wxT("Operator== - position != position 29"), !(position == position31));
        TEST(wxT("Operator== - position != position 30"), !(position == position32));
        TEST(wxT("Operator== - position != position 31"), !(position == position33));
        TEST(wxT("Operator== - position != position 32"), !(position == position34));
        TEST(wxT("Operator== - position != position 33"), !(position == position35));
    }
    
    // Inequality Operator
    {
        Position position(12,4,2);
        Position position2(12,4,2);
        Position position3(13,4,2);
        Position position4(12,8,2);
        Position position5(12,4,1);
        Position position6(12,4,2);
        position6.SetIrregularGroupingTiming(3,2);
        Position position7(12,4,2);
        position7.SetPreviousBeamDurationType(16);
        Position position8(12,4,2);
        position8.SetBeamStart();
        Position position9(12,4,2);
        position9.SetFractionalLeftBeam();
        Position position10(12,4,2);
        position10.SetFractionalRightBeam();
        Position position11(12,4,2);
        position11.SetBeamEnd();
        Position position12(12,4,2);
        position12.SetDotted();
        Position position13(12,4,2);
        position13.SetRest();
        Position position14(12,4,2);
        position14.SetVibrato();
        Position position15(12,4,2);
        position15.SetWideVibrato();
        Position position16(12,4,2);
        position16.SetArpeggioUp();
        Position position17(12,4,2);
        position17.SetArpeggioDown();
        Position position18(12,4,2);
        position18.SetPickStrokeUp();
        Position position19(12,4,2);
        position19.SetPickStrokeDown();
        Position position20(12,4,2);
        position20.SetStaccato();
        Position position21(12,4,2);
        position21.SetMarcato();
        Position position22(12,4,2);
        position22.SetSforzando();
        Position position23(12,4,2);
        position23.SetTremoloPicking();
        Position position24(12,4,2);
        position24.SetPalmMuting();
        Position position25(12,4,2);
        position25.SetTap();
        Position position26(12,4,2);
        position26.SetAcciaccatura();
        Position position27(12,4,2);
        position27.SetTripletFeel1st();
        Position position28(12,4,2);
        position28.SetTripletFeel2nd();
        Position position29(12,4,2);
        position29.SetLetRing();
        Position position30(12,4,2);
        position30.SetFermata();
        Position position31(12,4,2);
        position31.SetIrregularGroupingStart();
        Position position32(12,4,2);
        position32.SetIrregularGroupingMiddle();
        Position position33(12,4,2);
        position33.SetIrregularGroupingEnd();
        Position position34(12,4,2);
        position34.SetVolumeSwell(Dynamic::off, Dynamic::mp, 1);
        Position position35(12,4,2);
        position35.SetTremoloBar(Position::invertedDip, 1, 12);
        
        TEST(wxT("Operator!= - position == position"), !(position != position2));
        TEST(wxT("Operator!= - position != position"), (position != position3));
        TEST(wxT("Operator!= - position != position 2"), (position != position4));
        TEST(wxT("Operator!= - position != position 3"), (position != position5));
        TEST(wxT("Operator!= - position != position 4"), (position != position6));
        TEST(wxT("Operator!= - position != position 5"), (position != position7));
        TEST(wxT("Operator!= - position != position 6"), (position != position8));
        TEST(wxT("Operator!= - position != position 7"), (position != position9));
        TEST(wxT("Operator!= - position != position 8"), (position != position10));
        TEST(wxT("Operator!= - position != position 9"), (position != position11));
        TEST(wxT("Operator!= - position != position 10"), (position != position12));
        TEST(wxT("Operator!= - position != position 11"), (position != position13));
        TEST(wxT("Operator!= - position != position 12"), (position != position14));
        TEST(wxT("Operator!= - position != position 13"), (position != position15));
        TEST(wxT("Operator!= - position != position 14"), (position != position16));
        TEST(wxT("Operator!= - position != position 15"), (position != position17));
        TEST(wxT("Operator!= - position != position 16"), (position != position18));
        TEST(wxT("Operator!= - position != position 17"), (position != position19));
        TEST(wxT("Operator!= - position != position 18"), (position != position20));
        TEST(wxT("Operator!= - position != position 19"), (position != position21));
        TEST(wxT("Operator!= - position != position 20"), (position != position22));
        TEST(wxT("Operator!= - position != position 21"), (position != position23));
        TEST(wxT("Operator!= - position != position 22"), (position != position24));
        TEST(wxT("Operator!= - position != position 23"), (position != position25));
        TEST(wxT("Operator!= - position != position 24"), (position != position26));
        TEST(wxT("Operator!= - position != position 25"), (position != position27));
        TEST(wxT("Operator!= - position != position 26"), (position != position28));
        TEST(wxT("Operator!= - position != position 27"), (position != position29));
        TEST(wxT("Operator!= - position != position 28"), (position != position30));
        TEST(wxT("Operator!= - position != position 29"), (position != position31));
        TEST(wxT("Operator!= - position != position 30"), (position != position32));
        TEST(wxT("Operator!= - position != position 31"), (position != position33));
        TEST(wxT("Operator!= - position != position 32"), (position != position34));
        TEST(wxT("Operator!= - position != position 33"), (position != position35));
    }
    
    return (true);
}

/// Tests the Serialization Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Jan 18, 2005
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    Position positionOut(12, 4, 2);
    positionOut.SetVibrato();
    positionOut.SetVolumeSwell(Dynamic::off, Dynamic::mp, 1);
    positionOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        Position positionIn;
        positionIn.Deserialize(streamIn, PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((positionIn == positionOut)
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the Position Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCasePosition()
{
    //------Last Checked------//
    // - Jan 11, 2005
    Position position;
    
    // TEST CASE: IsValidPosition
    {
        wxUint32 i = 0;
        for (; i <= (Position::MAX_POSITION + 1); i++)
        {
            TEST(wxString::Format(wxT("IsValidPosition - %d"), i),
                (Position::IsValidPosition(i) == (i <= Position::MAX_POSITION))
            );
        }
    }
    
    // TEST CASE: SetPosition
    {
        wxUint32 i = 0;
        for (; i <= (Position::MAX_POSITION + 1); i++)
        {
            TEST(wxT("SetPosition - %d"), 
                (position.SetPosition(i) == (i <= Position::MAX_POSITION)) &&
                ((i > Position::MAX_POSITION) ? 1 : (position.GetPosition() == i))
            );
        }
    }
    return (true);
}

/// Tests the Duration Type Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseDurationType()
{
    //------Last Checked------//
    // - Jan 18, 2005
    
    // TEST CASE: IsValidDurationType
    {
        TEST(wxT("IsValidDurationType - 0"), !Position::IsValidDurationType(0));
        
        wxByte i = 1;
        for (; i <= 128; i = i * 2)
        {
            TEST(wxString::Format(wxT("IsValidDurationType - %d"), i),
                (Position::IsValidDurationType(i) == (i < 128))
            );
            
            // Block overflow
            if (i == 128)
                break;
        }
    }
    
    // TEST CASE: SetDurationType
    {
        Position position;
        
        TEST(wxT("SetDurationType - 0"), !position.SetDurationType(0));
        
        wxByte i = 1;
        for (; i <= 128; i = i * 2)
        {
            TEST(wxString::Format(wxT("SetDurationType - %d"), i),
                (position.SetDurationType(i) == (i < 128)) &&
                ((i >= 128) ? 1 : (position.GetDurationType() == i))
            );
            
            // Block overflow
            if (i == 128)
                break;
        }
    }
    return (true);
}

/// Tests the Irregular Grouping Functions
/// @return True if the all tests were executed, false if not
bool PositionTestSuite::TestCaseIrregularGrouping()
{
    //------Last Checked------//
    // - Jan 18, 2005
    
    // TEST CASE: IsValidIrregularGroupingTiming
    {
        wxByte i = Position::MIN_IRREGULAR_GROUPING_NOTES_PLAYED - 1;
        for (; i < (Position::MAX_IRREGULAR_GROUPING_NOTES_PLAYED + 1); i++)
        {
            wxByte j = Position::MIN_IRREGULAR_GROUPING_NOTES_PLAYED_OVER - 1;
            for (; j < (Position::MAX_IRREGULAR_GROUPING_NOTES_PLAYED_OVER + 1); j++)
            {
                TEST(wxString::Format(wxT("IsValidIrregularGroupingTiming - %d, %d"), i, j),
                    (Position::IsValidIrregularGroupingTiming(i, j) == 
                        (((i >= Position::MIN_IRREGULAR_GROUPING_NOTES_PLAYED) && (i <= Position::MAX_IRREGULAR_GROUPING_NOTES_PLAYED)) &&
                        ((j >= Position::MIN_IRREGULAR_GROUPING_NOTES_PLAYED_OVER) && (j <= Position::MAX_IRREGULAR_GROUPING_NOTES_PLAYED_OVER))))
                );
            }
        }   
    }
    
    // TEST CASE: SetIrregularGroupingTiming
    {
        Position position;
        
        wxByte i = Position::MIN_IRREGULAR_GROUPING_NOTES_PLAYED - 1;
        for (; i < (Position::MAX_IRREGULAR_GROUPING_NOTES_PLAYED + 1); i++)
        {
            wxByte j = Position::MIN_IRREGULAR_GROUPING_NOTES_PLAYED_OVER - 1;
            for (; j < (Position::MAX_IRREGULAR_GROUPING_NOTES_PLAYED_OVER + 1); j++)
            {
                bool set = position.SetIrregularGroupingTiming(i,j);
                bool valid = (i >= Position::MIN_IRREGULAR_GROUPING_NOTES_PLAYED) && (i <= Position::MAX_IRREGULAR_GROUPING_NOTES_PLAYED) &&
                        (j >= Position::MIN_IRREGULAR_GROUPING_NOTES_PLAYED_OVER) && (j <= Position::MAX_IRREGULAR_GROUPING_NOTES_PLAYED_OVER);
                         
                wxByte notesPlayed = 0;
                wxByte notesPlayedOver = 0;
                position.GetIrregularGroupingTiming(notesPlayed, notesPlayedOver);
                
                TEST(wxString::Format(wxT("SetIrregularGroupingTiming - %d, %d"), i, j),
                    (set == valid) &&
                    ((!valid) ? 1 : (position.HasIrregularGroupingTiming() && ((notesPlayed == i) && (notesPlayedOver == j))))
                );
            }
        }   
    }
    
    // TEST CASE: ClearIrregularGroupingTiming
    {
        Position position;
        position.SetIrregularGroupingTiming(3,2);
        
        bool clear = position.ClearIrregularGroupingTiming();
        TEST(wxT("ClearIrregularGroupingTiming"),
            (clear && !position.HasIrregularGroupingTiming())
        );
    }
    
    return (true);
}

/// Tests the Beaming Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseBeaming()
{
    //------Last Checked------//
    // - Jan 18, 2005
    
    // TEST CASE: IsValidPreviousBeamDurationType
    {
        TEST(wxT("IsValidPreviousBeamDurationType - 0"), Position::IsValidPreviousBeamDurationType(0));
        
        wxByte i = 1;
        for (; i <= 128; i = i * 2)
        {
            TEST(wxString::Format(wxT("IsValidPreviousBeamDurationType - %d"), i),
                (Position::IsValidPreviousBeamDurationType(i) == ((i == 0) || (i == 8) || (i == 16) || (i == 32) || (i == 64)))
            );
            
            // Block overflow
            if (i == 128)
                break;
        }
    }
    
    // TEST CASE: SetPreviousBeamDurationType
    {
        Position position;
        
        TEST(wxT("SetPreviousBeamDurationType - 0"), position.SetPreviousBeamDurationType(0));
        
        wxByte i = 1;
        for (; i <= 128; i = i * 2)
        {
            TEST(wxString::Format(wxT("SetPreviousBeamDurationType - %d"), i),
                (position.SetPreviousBeamDurationType(i) == ((i == 0) || (i == 8) || (i == 16) || (i == 32) || (i == 64))) &&
                (!((i == 0) || (i == 8) || (i == 16) || (i == 32) || (i == 64)) ? 1 : (position.GetPreviousBeamDurationType() == i))
            );
            
            // Block overflow
            if (i == 128)
                break;
        }
    }
    
    // TEST CASE: SetBeamStart
    {
        Position position;
        TEST(wxT("SetBeamStart - true"), (position.SetBeamStart() && position.IsBeamStart()));
        TEST(wxT("SetBeamStart - false"), (position.SetBeamStart(false) && !position.IsBeamStart()));
    }
    
    // TEST CASE: SetFractionalLeftBeam
    {
        Position position;
        TEST(wxT("SetFractionalLeftBeam - true"), (position.SetFractionalLeftBeam() && position.HasFractionalLeftBeam()));
        TEST(wxT("SetFractionalLeftBeam - false"), (position.SetFractionalLeftBeam(false) && !position.HasFractionalLeftBeam()));
    }
    
    // TEST CASE: SetFractionalRightBeam
    {
        Position position;
        TEST(wxT("SetFractionalRightBeam - true"), (position.SetFractionalRightBeam() && position.HasFractionalRightBeam()));
        TEST(wxT("SetFractionalRightBeam - false"), (position.SetFractionalRightBeam(false) && !position.HasFractionalRightBeam()));
    }
    
    // TEST CASE: SetBeamEnd
    {
        Position position;
        TEST(wxT("SetBeamEnd - true"), (position.SetBeamEnd() && position.IsBeamEnd()));
        TEST(wxT("SetBeamEnd - false"), (position.SetBeamEnd(false) && !position.IsBeamEnd()));
    }
    
    // TEST CASE: ClearBeam
    {
        Position position;
        
        position.SetPreviousBeamDurationType(16);
        position.SetBeamStart();
        TEST(wxT("ClearBeam - beam start"), 
            position.ClearBeam() &&
            (!position.IsBeamStart()) &&
            (position.GetPreviousBeamDurationType() == 0)
        );
        
        position.SetPreviousBeamDurationType(16);
        position.SetFractionalLeftBeam();
        TEST(wxT("ClearBeam - fractional left beam"), 
            position.ClearBeam() &&
            (!position.HasFractionalLeftBeam()) &&
            (position.GetPreviousBeamDurationType() == 0)
        );
        
        position.SetPreviousBeamDurationType(16);
        position.SetFractionalRightBeam();
        TEST(wxT("ClearBeam - fractional right beam"), 
            position.ClearBeam() &&
            (!position.HasFractionalRightBeam()) &&
            (position.GetPreviousBeamDurationType() == 0)
        );
        
        position.SetPreviousBeamDurationType(16);
        position.SetBeamEnd();
        TEST(wxT("ClearBeam - beam end"), 
            position.ClearBeam() &&
            (!position.IsBeamEnd()) &&
            (position.GetPreviousBeamDurationType() == 0)
        );
    }
    
    return (true);
}

/// Tests the Dotted Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseDotted()
{
    //------Last Checked------//
    // - Jan 7, 2005
    
    // TEST CASE: Dotted
    {
        Position position;
        TEST(wxT("SetDotted - true"), (position.SetDotted() && position.IsDotted()));
        TEST(wxT("SetDotted - false"), (position.SetDotted(false) && !position.IsDotted()));
    }
    
    // TEST CASE: Double Dotted
    {
        Position position;
        TEST(wxT("SetDoubleDotted - true"), (position.SetDoubleDotted() && position.IsDoubleDotted()));
        TEST(wxT("SetDoubleDotted - false"), (position.SetDoubleDotted(false) && !position.IsDoubleDotted()));
    }
    
    return (true);
}

/// Tests the Rest Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseRest()
{
    //------Last Checked------//
    // - Jan 7, 2005
    
    Position position;
    TEST(wxT("SetRest - true"), (position.SetRest() && position.IsRest()));
    TEST(wxT("SetRest - false"), (position.SetRest(false) && !position.IsRest()));
    
    return (true);
}

/// Tests the Vibrato Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseVibrato()
{
    //------Last Checked------//
    // - Jan 18, 2005
    
    // TEST CASE: Vibrato
    {
        Position position;
        TEST(wxT("SetVibrato - true"), (position.SetVibrato() && position.HasVibrato()));
        TEST(wxT("SetVibrato - false"), (position.SetVibrato(false) && !position.HasVibrato()));
    }
    
    // TEST CASE: Wide Vibrato
    {
        Position position;
        TEST(wxT("SetWideVibrato - true"), (position.SetWideVibrato() && position.HasWideVibrato()));
        TEST(wxT("SetWideVibrato - false"), (position.SetWideVibrato(false) && !position.HasWideVibrato()));
    }
    
    return (true);
}

/// Tests the Arpeggio Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseArpeggio()
{
    //------Last Checked------//
    // - Jan 7, 2005
    
    // TEST CASE: SetArpeggioDown
    {
        Position position;
        TEST(wxT("SetArpeggioDown - true"), (position.SetArpeggioDown() && position.HasArpeggioDown()));
        TEST(wxT("SetArpeggioDown - false"), (position.SetArpeggioDown(false) && !position.HasArpeggioDown()));
    }
    
    // TEST CASE: SetArpeggioUp
    {
        Position position;
        TEST(wxT("SetArpeggioUp - true"), (position.SetArpeggioUp() && position.HasArpeggioUp()));
        TEST(wxT("SetArpeggioUp - false"), (position.SetArpeggioUp(false) && !position.HasArpeggioUp()));
    }
    
    return (true);
}

/// Tests the Pick Stroke Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCasePickStroke()
{
    //------Last Checked------//
    // - Jan 7, 2005
    
    // TEST CASE: SetPickStrokeUp
    {
        Position position;
        TEST(wxT("SetPickStrokeUp - true"), (position.SetPickStrokeUp() && position.HasPickStrokeUp()));
        TEST(wxT("SetPickStrokeUp - false"), (position.SetPickStrokeUp(false) && !position.HasPickStrokeUp()));
    }
    
    // TEST CASE: SetPickStrokeDown
    {
        Position position;
        TEST(wxT("SetPickStrokeDown - true"), (position.SetPickStrokeDown() && position.HasPickStrokeDown()));
        TEST(wxT("SetPickStrokeDown - false"), (position.SetPickStrokeDown(false) && !position.HasPickStrokeDown()));
    }
    
    return (true);
}

/// Tests the Staccato Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseStaccato()
{
    //------Last Checked------//
    // - Jan 7, 2005
  
    Position position;
    TEST(wxT("SetStaccato - true"), (position.SetStaccato() && position.IsStaccato()));
    TEST(wxT("SetStaccato - false"), (position.SetStaccato(false) && !position.IsStaccato()));
    
    return (true);
}

/// Tests the Accent Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseAccent()
{
    //------Last Checked------//
    // - Jan 7, 2005
       
    // TEST CASE: SetMarcato
    {
        Position position;    
        TEST(wxT("SetMarcato - true"), (position.SetMarcato() && position.HasMarcato()));
        TEST(wxT("SetMarcato - false"), (position.SetMarcato(false) && !position.HasMarcato()));
    }
    
    // TEST CASE: SetSforzando
    {
        Position position;
        TEST(wxT("SetSforzando - true"), (position.SetSforzando() && position.HasSforzando()));
        TEST(wxT("SetSforzando - false"), (position.SetSforzando(false) && !position.HasSforzando()));
    }
    
    return (true);
}

/// Tests the Tremolo Picking Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseTremoloPicking()
{
    //------Last Checked------//
    // - Jan 18, 2005
    Position position;
    TEST(wxT("SetTremoloPicking - true"), (position.SetTremoloPicking() && position.HasTremoloPicking()));
    TEST(wxT("SetTremoloPicking - false"), (position.SetTremoloPicking(false) && !position.HasTremoloPicking()));
    return (true);
}

/// Tests the Palm Muting Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCasePalmMuting()
{
    //------Last Checked------//
    // - Jan 18, 2005
    Position position;
    TEST(wxT("SetPalmMuting - true"), (position.SetPalmMuting() && position.HasPalmMuting()));
    TEST(wxT("SetPalmMuting - false"), (position.SetPalmMuting(false) && !position.HasPalmMuting()));
    return (true);
}

/// Tests the Tap Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseTap()
{
    //------Last Checked------//
    // - Jan 18, 2005
    Position position;
    TEST(wxT("SetTap - true"), (position.SetTap() && position.HasTap()));
    TEST(wxT("SetTap - false"), (position.SetTap(false) && !position.HasTap()));
    return (true);
}

/// Tests the Grace Note Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseGraceNotes()
{
    //------Last Checked------//
    // - Jan 18, 2005
    
    // TEST CASE: Acciaccatura
    {
        Position position;
        TEST(wxT("SetAcciaccatura - true"), (position.SetAcciaccatura() && position.IsAcciaccatura()));
        TEST(wxT("SetAcciaccatura - false"), (position.SetAcciaccatura(false) && !position.IsAcciaccatura()));
    }
    
    return (true);
}

/// Tests the Triplet Feel Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseTripletFeel()
{
    //------Last Checked------//
    // - Jan 7, 2005
       
    // TEST CASE: SetTripletFeel1st
    {
        Position position;
        TEST(wxT("SetTripletFeel1st - true"), (position.SetTripletFeel1st() && position.IsTripletFeel1st()));
        TEST(wxT("SetTripletFeel1st - false"), (position.SetTripletFeel1st(false) && !position.IsTripletFeel1st()));
    }
    
    // TEST CASE: SetTripletFeel2nd
    {
        Position position;
        TEST(wxT("SetTripletFeel2nd - true"), (position.SetTripletFeel2nd() && position.IsTripletFeel2nd()));
        TEST(wxT("SetTripletFeel2nd - false"), (position.SetTripletFeel2nd(false) && !position.IsTripletFeel2nd()));
    }
    
    return (true);
}

/// Tests the Let Ring Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseLetRing()
{
    //------Last Checked------//
    // - Jan 18, 2005
    Position position;
    TEST(wxT("SetLetRing - true"), (position.SetLetRing() && position.HasLetRing()));
    TEST(wxT("SetLetRing - false"), (position.SetLetRing(false) && !position.HasLetRing()));
    return (true);
}

/// Tests the Fermata Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseFermata()
{
    //------Last Checked------//
    // - Jan 18, 2005
    Position position;
    TEST(wxT("SetFermata - true"), (position.SetFermata() && position.HasFermata()));
    TEST(wxT("SetFermata - false"), (position.SetFermata(false) && !position.HasFermata()));
    return (true);
}

/// Tests the Volume Swell Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseVolumeSwell()
{
    //------Last Checked------//
    // - Jan 19, 2005
        
    // TEST CASE: SetVolumeSwell
    {
        Position position;
        TEST(wxT("SetVolumeSwell - invalid start volume"), !position.SetVolumeSwell(255, Dynamic::mp, 4));
        TEST(wxT("SetVolumeSwell - invalid end volume"), !position.SetVolumeSwell(Dynamic::off, 255, 4));
        TEST(wxT("SetVolumeSwell - invalid duration"), !position.SetVolumeSwell(Dynamic::off, Dynamic::mp, 255));
        TEST(wxT("SetVolumeSwell - same volumes"), !position.SetVolumeSwell(Dynamic::mp, Dynamic::mp, 4));
        
        bool set = position.SetVolumeSwell(Dynamic::off, Dynamic::mp, 1);
        wxByte startVolume = 0;
        wxByte endVolume = 0;
        wxByte duration = 0;
        bool get = position.GetVolumeSwell(startVolume, endVolume, duration);
        TEST(wxT("SetVolumeSwell - valid"), 
            ((set) &&
            (get) &&
            (position.HasVolumeSwell()) &&
            (startVolume == Dynamic::off) &&
            (endVolume == Dynamic::mp) &&
            (duration == 1))
        );
        
        {
            Position position;
            position.SetVolumeSwell(Dynamic::off, Dynamic::mp, 1);
            bool set = position.SetVolumeSwell(Dynamic::mf, Dynamic::fff, 3);
            wxByte startVolume = 0;
            wxByte endVolume = 0;
            wxByte duration = 0;
            bool get = position.GetVolumeSwell(startVolume, endVolume, duration);
            TEST(wxT("SetVolumeSwell - update"), 
                ((set) &&
                (get) &&
                (position.HasVolumeSwell()) &&
                (startVolume == Dynamic::mf) &&
                (endVolume == Dynamic::fff) &&
                (duration == 3))
            );
        }
    }
    
    // TEST CASE: GetVolumeSwell
    {
        Position position;
        wxByte startVolume = 0;
        wxByte endVolume = 0;
        wxByte duration = 0;
        TEST(wxT("GetVolumeSwell - empty"),
            !position.GetVolumeSwell(startVolume, endVolume, duration)
        );
    }
    
    // TEST CASE: ClearVolumeSwell
    {
        Position position;
        bool set = position.SetVolumeSwell(Dynamic::off, Dynamic::mp, 1);
        position.ClearVolumeSwell();
        TEST(wxT("ClearVolumeSwell"), 
            ((set) &&
            !position.HasVolumeSwell())
        );
    }
    
    return (true);
}

/// Tests the Tremolo Bar Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseTremoloBar()
{
    //------Last Checked------//
    // - Jan 19, 2005
        
    // TEST CASE: SetTremoloBar
    {
        Position position;
        TEST(wxT("SetTremoloBar - invalid type"), !position.SetTremoloBar(255, 1, 12));
        TEST(wxT("SetTremoloBar - invalid duration"), !position.SetTremoloBar(Position::invertedDip, 255, 12));
        TEST(wxT("SetTremoloBar - invalid pitch"), !position.SetTremoloBar(Position::invertedDip, 1, 255));
        
        bool set = position.SetTremoloBar(Position::invertedDip, 1, 12);
        wxByte type = 0;
        wxByte duration = 0;
        wxByte pitch = 0;
        bool get = position.GetTremoloBar(type, duration, pitch);
        TEST(wxT("SetTremoloBar - valid"), 
            ((set) &&
            (get) &&
            (position.HasTremoloBar()) &&
            (type == Position::invertedDip) &&
            (duration == 1) &&
            (pitch == 12))
        );
        
        {
            Position position;
            position.SetVolumeSwell(Dynamic::off, Dynamic::mp, 1);
            bool set = position.SetVolumeSwell(Dynamic::mf, Dynamic::fff, 3);
            wxByte startVolume = 0;
            wxByte endVolume = 0;
            wxByte duration = 0;
            bool get = position.GetVolumeSwell(startVolume, endVolume, duration);
            TEST(wxT("SetVolumeSwell - update"), 
                ((set) &&
                (get) &&
                (position.HasVolumeSwell()) &&
                (startVolume == Dynamic::mf) &&
                (endVolume == Dynamic::fff) &&
                (duration == 3))
            );
        }
    }
    
    // TEST CASE: GetTremoloBar
    {
        Position position;
        wxByte type = 0;
        wxByte duration = 0;
        wxByte pitch = 0;
        TEST(wxT("GetTremoloBar - empty"),
            !position.GetTremoloBar(type, duration, pitch)
        );
    }
    
    // TEST CASE: ClearTremoloBar
    {
        Position position;
        bool set = position.SetTremoloBar(Position::invertedDip, 1, 12);
        position.ClearTremoloBar();
        TEST(wxT("ClearTremoloBar"), 
            ((set) &&
            !position.HasTremoloBar())
        );
    }
    
    return (true);
}

/// Tests the Multibar Rest Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseMultibarRest()
{
    //------Last Checked------//
    // - Jan 19, 2005
    
    // TEST CASE: SetMultibarRest
    {
        wxByte i = 0;
        for (; i <= Position::MAX_MULTIBAR_REST_MEASURE_COUNT; i++)
        {
            Position position;
            bool set = position.SetMultibarRest(i);
            wxByte measureCount = 0;
            position.GetMultibarRest(measureCount);
            TEST(wxString::Format(wxT("SetMultibarRest - %d"), i),
                ((set == (i >= Position::MIN_MULTIBAR_REST_MEASURE_COUNT) && (i <= Position::MAX_MULTIBAR_REST_MEASURE_COUNT)) &&
                ((i < Position::MIN_MULTIBAR_REST_MEASURE_COUNT) ? 1 : 
                    ((position.HasMultibarRest()) && (measureCount == i))
                ))
            );
            
            if (i == Position::MAX_MULTIBAR_REST_MEASURE_COUNT)
                break;
        }
    }
    
    // TEST CASE: ClearMultibarRest
    {
        Position position;
        bool set = position.SetMultibarRest(10);
        position.ClearMultibarRest();
        TEST(wxT("ClearMultibarRest"), 
            ((set) &&
            !position.HasMultibarRest())
        );
    }
    
    return (true);
}

/// Tests the Complex Symbol Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseComplexSymbol()
{
    //------Last Checked------//
    // - Jan 19, 2005
    
    // TEST CASE: IsValidComplexSymbolType
    {
        wxByte i = 0;
        for (;;i++)
        {
            TEST(wxString::Format(wxT("IsValidComplexSymbolType - %d"), i),
                (Position::IsValidComplexSymbolType(i) == ((i == Position::volumeSwell) || (i == Position::tremoloBar) || (i == Position::multibarRest)))
            );
            
            // block overflow
            if (i == 255)
                break;
        }
    }
    
    // TEST CASE: AddComplexSymbol
    {
        Position position;
        TEST(wxT("AddComplexSymbol - invalid type"), !position.AddComplexSymbol(0));
        position.SetVolumeSwell(Dynamic::off, Dynamic::mp, 1);
        position.SetTremoloBar(Position::invertedDip, 1, 12);
        TEST(wxT("AddComplexSymbol - full"), !position.SetMultibarRest(10));
    }
    
    // TEST CASE: GetComplexSymbolCount
    {
        Position position;
        TEST(wxT("GetComplexSymbolCount - 0"),
            (position.GetComplexSymbolCount() == 0)
        );
        
        position.SetVolumeSwell(Dynamic::off, Dynamic::mp, 1);
        position.SetTremoloBar(Position::invertedDip, 1, 12);
        
        TEST(wxT("GetComplexSymbolCount - 2"), 
            (position.GetComplexSymbolCount() == 2)
        );
        
        position.ClearComplexSymbolArrayContents();
        TEST(wxT("GetComplexSymbolCount - 0"),
            (position.GetComplexSymbolCount() == 0)
        );
    }
    
    // TEST CASE: FindComplexSymbol
    {
        Position position;
        position.SetVolumeSwell(Dynamic::off, Dynamic::mp, 1);
        position.SetTremoloBar(Position::invertedDip, 1, 12);
        
        TEST(wxT("FindComplexSymbol - volume swell"), (position.FindComplexSymbol(Position::volumeSwell) == 0));
        TEST(wxT("FindComplexSymbol - tremolo bar"), (position.FindComplexSymbol(Position::tremoloBar) == 1));
    }

    // TEST CASE: RemoveComplexSymbol
    {
        Position position;
        position.SetVolumeSwell(Dynamic::off, Dynamic::mp, 1);
        position.SetTremoloBar(Position::invertedDip, 1, 12);
        
        TEST(wxT("RemoveComplexSymbol - tremolo bar"), 
            (position.RemoveComplexSymbol(Position::tremoloBar)) &&
            (!position.HasTremoloBar())
        );
        
        TEST(wxT("RemoveComplexSymbol - volume swell"), 
            (position.RemoveComplexSymbol(Position::volumeSwell)) &&
            (!position.HasVolumeSwell())
        );
    }
        
    return (true);
}

/// Tests the Note Array Functions
/// @return True if all tests were executed, false if not
bool PositionTestSuite::TestCaseNoteArray()
{
    //------Last Checked------//
    // - Jan 25, 2005
    Position position;
    TEST(wxT("IsValidNoteIndex - false"), !position.IsValidNoteIndex(0));
    TEST(wxT("GetNote - invalid index"), (position.GetNote(0) == NULL));
    return (true);
}
