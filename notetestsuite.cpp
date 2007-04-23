/////////////////////////////////////////////////////////////////////////////
// Name:            notetestsuite.cpp
// Purpose:         Performs unit testing on the Note class
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 5, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "notetestsuite.h"

#include "note.h"
#include "powertabfileheader.h"         // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(NoteTestSuite, TestSuite)

/// Default Constructor
NoteTestSuite::NoteTestSuite()
{
    //------Last Checked------//
    // - Dec 10, 2004
}

/// Destructor
NoteTestSuite::~NoteTestSuite()
{
    //------Last Checked------//
    // - Dec 10, 2004
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t NoteTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Dec 10, 2004
    return (723);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool NoteTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Jan 17, 2005
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseCreation())
        return (false);
    if (!TestCaseOperator())
        return (false);
    if (!TestCaseSerialize())
        return (false);
    if (!TestCaseString())
        return (false);
    if (!TestCaseFretNumber())
        return (false);
    if (!TestCaseTied())
        return (false);
    if (!TestCaseMuted())
        return (false);
    if (!TestCaseTieWrap())
        return (false);
    if (!TestCaseHammerOn())
        return (false);
    if (!TestCaseHammerOnFromNowhere())
        return (false);
    if (!TestCasePullOff())
        return (false);
    if (!TestCasePullOffToNowhere())
        return (false);
    if (!TestCaseNaturalHarmonic())
        return (false);
    if (!TestCaseGhostNote())
        return (false);
    if (!TestCaseOctave8va())
        return (false);
    if (!TestCaseOctave15ma())
        return (false);
    if (!TestCaseOctave8mb())
        return (false);
    if (!TestCaseOctave15mb())
        return (false);
    if (!TestCaseSimpleFlags())
        return (false);
    if (!TestCaseSlide())
        return (false);
    if (!TestCaseBend())
        return (false);
    if (!TestCaseTappedHarmonic())
        return (false);
    if (!TestCaseTrill())
        return (false);
    if (!TestCaseArtificialHarmonic())
        return (false);
    if (!TestCaseComplexSymbol())
        return (false);
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Jan 17, 2005
    
    // TEST CASE: Default constructor
    {
        Note note;
        TEST(wxT("Default Constructor"), 
            (note.m_stringData == Note::DEFAULT_STRING_DATA) &&
            (note.m_simpleData == Note::DEFAULT_SIMPLE_DATA) &&
            (note.GetComplexSymbolCount() == 0)
        );
    }
    
    // TEST CASE: Primary constructor
    {
        Note note(2, 10);
        TEST(wxT("Primary Constructor"), 
            (note.GetString() == 2) &&
            (note.GetFretNumber() == 10) &&
            (note.m_simpleData == Note::DEFAULT_SIMPLE_DATA) &&
            (note.GetComplexSymbolCount() == 0)
        );
    }
    
    // TEST CASE: Copy constructor
    {
        Note note(2, 10);
        note.SetHammerOn();
        note.SetTappedHarmonic(13);
        note.SetTrill(5);
        note.SetArtificialHarmonic(ChordName::C, ChordName::variationDefault, 1);
        Note note2(note);
        
        TEST(wxT("Copy Constructor"), 
            (note2 == note)
        );
    }

    return (true);
}

/// Tests the Creation Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseCreation()
{
    //------Last Checked------//
    // - Jan 12, 2005   
    Note note;
    Note* clone = (Note*)note.CloneObject();
    TEST(wxT("CloneObject"),
        (*clone == note)
    );
    delete clone;
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Jan 17, 2005
    
    // TEST CASE: Operator=
    {
        Note note(2,10);
        note.SetHammerOn();
        note.SetTappedHarmonic(13);
        note.SetTrill(5);
        note.SetArtificialHarmonic(ChordName::C, ChordName::variationDefault, 1);
        
        Note note2 = note;
        TEST(wxT("Operator="), 
            (note2 == note)
        );
        
        note = note;
        TEST(wxT("Operator= (self-assignment)"),
            (note == note)
        );
    }
    
    // TEST CASE: Operator==
    {
        Note note(2,10);
        Note note2(2,10);
        Note note3(3,10);
        Note note4(2,11);
        Note note5(2,10);
        note5.SetTied();
        Note note6(2,10);
        note6.SetMuted();
        Note note7(2,10);
        note7.SetTieWrap();
        Note note8(2,10);
        note8.SetHammerOn();
        Note note9(2,10);
        note9.SetHammerOnFromNowhere();
        Note note10(2,10);
        note10.SetPullOff();
        Note note11(2,10);
        note11.SetPullOffToNowhere();
        Note note12(2,10);
        note12.SetNaturalHarmonic();
        Note note13(2,10);
        note13.SetGhostNote();
        Note note14(2,10);
        note14.SetOctave8va();
        Note note15(2,10);
        note15.SetOctave15ma();
        Note note16(2,10);
        note16.SetOctave8vb();
        Note note17(2,10);
        note17.SetOctave15mb();
        Note note18(2,10);
        note18.SetSlideInto(Note::slideIntoFromBelow);
        Note note19(2,10);
        note19.SetBend(Note::bendAndHold, 4, 0, 1, Note::lowPoint, Note::highPoint);
        Note note20(2,10);
        note20.SetTappedHarmonic(14);
        Note note21(2,10);
        note21.SetTrill(5);
        Note note22(2,10);
        note22.SetArtificialHarmonic(ChordName::C, ChordName::variationDefault, 1);
       
        TEST(wxT("Operator== - note == note"), (note == note2));
        TEST(wxT("Operator== - note != note"), !(note == note3));
        TEST(wxT("Operator== - note != note 2"), !(note == note4));
        TEST(wxT("Operator== - note != note 3"), !(note == note5));
        TEST(wxT("Operator== - note != note 4"), !(note == note6));
        TEST(wxT("Operator== - note != note 5"), !(note == note7));
        TEST(wxT("Operator== - note != note 6"), !(note == note8));
        TEST(wxT("Operator== - note != note 7"), !(note == note9));
        TEST(wxT("Operator== - note != note 8"), !(note == note10));
        TEST(wxT("Operator== - note != note 9"), !(note == note11));
        TEST(wxT("Operator== - note != note 10"), !(note == note12));
        TEST(wxT("Operator== - note != note 11"), !(note == note13));
        TEST(wxT("Operator== - note != note 12"), !(note == note14));
        TEST(wxT("Operator== - note != note 13"), !(note == note15));
        TEST(wxT("Operator== - note != note 14"), !(note == note16));
        TEST(wxT("Operator== - note != note 15"), !(note == note17));
        TEST(wxT("Operator== - note != note 16"), !(note == note18));
        TEST(wxT("Operator== - note != note 17"), !(note == note19));
        TEST(wxT("Operator== - note != note 18"), !(note == note20));
        TEST(wxT("Operator== - note != note 19"), !(note == note21));
        TEST(wxT("Operator== - note != note 20"), !(note == note22));
    }
        
    // TEST CASE: Operator!=
    {
        Note note(2,10);
        Note note2(2,10);
        Note note3(3,10);
        Note note4(2,11);
        Note note5(2,10);
        note5.SetTied();
        Note note6(2,10);
        note6.SetMuted();
        Note note7(2,10);
        note7.SetTieWrap();
        Note note8(2,10);
        note8.SetHammerOn();
        Note note9(2,10);
        note9.SetHammerOnFromNowhere();
        Note note10(2,10);
        note10.SetPullOff();
        Note note11(2,10);
        note11.SetPullOffToNowhere();
        Note note12(2,10);
        note12.SetNaturalHarmonic();
        Note note13(2,10);
        note13.SetGhostNote();
        Note note14(2,10);
        note14.SetOctave8va();
        Note note15(2,10);
        note15.SetOctave15ma();
        Note note16(2,10);
        note16.SetOctave8vb();
        Note note17(2,10);
        note17.SetOctave15mb();
        Note note18(2,10);
        note18.SetSlideInto(Note::slideIntoFromBelow);
        Note note19(2,10);
        note19.SetBend(Note::bendAndHold, 4, 0, 1, Note::lowPoint, Note::highPoint);
        Note note20(2,10);
        note20.SetTappedHarmonic(14);
        Note note21(2,10);
        note21.SetTrill(5);
        Note note22(2,10);
        note22.SetArtificialHarmonic(ChordName::C, ChordName::variationDefault, 1);
       
        TEST(wxT("Operator!= - note != note"), !(note != note2));
        TEST(wxT("Operator!= - note != note"), (note != note3));
        TEST(wxT("Operator!= - note != note 2"), (note != note4));
        TEST(wxT("Operator!= - note != note 3"), (note != note5));
        TEST(wxT("Operator!= - note != note 4"), (note != note6));
        TEST(wxT("Operator!= - note != note 5"), (note != note7));
        TEST(wxT("Operator!= - note != note 6"), (note != note8));
        TEST(wxT("Operator!= - note != note 7"), (note != note9));
        TEST(wxT("Operator!= - note != note 8"), (note != note10));
        TEST(wxT("Operator!= - note != note 9"), (note != note11));
        TEST(wxT("Operator!= - note != note 10"), (note != note12));
        TEST(wxT("Operator!= - note != note 11"), (note != note13));
        TEST(wxT("Operator!= - note != note 12"), (note != note14));
        TEST(wxT("Operator!= - note != note 13"), (note != note15));
        TEST(wxT("Operator!= - note != note 14"), (note != note16));
        TEST(wxT("Operator!= - note != note 15"), (note != note17));
        TEST(wxT("Operator!= - note != note 16"), (note != note18));
        TEST(wxT("Operator!= - note != note 17"), (note != note19));
        TEST(wxT("Operator!= - note != note 18"), (note != note20));
        TEST(wxT("Operator!= - note != note 19"), (note != note21));
        TEST(wxT("Operator!= - note != note 20"), (note != note22));
    }
    
    return (true);
}

/// Tests the Serialization Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Jan 17, 2005
    bool ok = false;
    
    TestStream testStream;
    PowerTabOutputStream streamOut(testStream.GetOutputStream());
    
    // Write test data to stream
    Note noteOut(2,10);
    noteOut.SetHammerOn();
    noteOut.SetTappedHarmonic(13);
    noteOut.SetTrill(5);
    noteOut.SetArtificialHarmonic(ChordName::C, ChordName::variationDefault, 1);
    noteOut.Serialize(streamOut);

    // Output must be OK before using input
    if (testStream.CheckOutputState())
    {
        PowerTabInputStream streamIn(testStream.GetInputStream());
    
        // Read test data back from stream
        Note noteIn;
        noteIn.Deserialize(streamIn, PowerTabFileHeader::FILEVERSION_CURRENT);

        // Validate the data
        ok = ((noteIn == noteOut) 
            && (streamIn.CheckState()));
    }
    
    TEST(wxT("Serialize"), ok);
    
    return (true);
}

/// Tests the String Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseString()
{
    //------Last Checked------//
    // - Jan 17, 2005
    
    // TEST CASE: IsValidString
    {
        wxByte i = Note::MIN_STRING;
        for (; i <= (Note::MAX_STRING + 1); i++)
            TEST(wxString::Format(wxT("IsValidString - %d"), i), 
                (Note::IsValidString(i) == (i <= Note::MAX_STRING))
            );
    }
    
    // TEST CASE: SetString
    {
        Note note;
        wxByte i = 0;
        for (; i < (Note::MAX_STRING + 1); i++)
            TEST(wxString::Format(wxT("SetString %d"), i), 
                (note.SetString(i) == (i <= Note::MAX_STRING)) &&
                ((i > Note::MAX_STRING) ? 1 : (note.GetString() == i))
            );
    }
    
    return (true);
}

/// Tests the Fret Number Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseFretNumber()
{
    //------Last Checked------//
    // - Jan 17, 2005
    
    // TEST CASE: IsValidFretNumber
    {
        wxByte i = Note::MIN_FRET_NUMBER;
        for (; i <= (Note::MAX_FRET_NUMBER + 1); i++)
            TEST(wxString::Format(wxT("IsValidFretNumber - %d"), i), 
                (Note::IsValidFretNumber(i) == (i <= Note::MAX_FRET_NUMBER))
            );
    }
    
    // TEST CASE: SetFretNumber
    {
        Note note;
        wxByte i = 0;
        for (; i < (Note::MAX_FRET_NUMBER + 1); i++)
            TEST(wxString::Format(wxT("SetFretNumber %d"), i), 
                (note.SetFretNumber(i) == (i <= Note::MAX_FRET_NUMBER)) &&
                ((i > Note::MAX_FRET_NUMBER) ? 1 : (note.GetFretNumber() == i))
            );
    }
    
    return (true);
}

/// Tests the Tied Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseTied()
{
    //------Last Checked------//
    // - Jan 17, 2005
    Note note;
    TEST(wxT("SetTied - true"), (note.SetTied() && note.IsTied()));
    TEST(wxT("SetTied - false"), (note.SetTied(false) && !note.IsTied()));
    return (true);
}

/// Tests the Muted Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseMuted()
{
    //------Last Checked------//
    // - Jan 17, 2005
    Note note;
    TEST(wxT("SetMuted - true"), (note.SetMuted() && note.IsMuted()));
    TEST(wxT("SetMuted - false"), (note.SetMuted(false) && !note.IsMuted()));
    return (true);
}

/// Tests the Tie Wrap Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseTieWrap()
{
    //------Last Checked------//
    // - Jan 17, 2005
    Note note;
    TEST(wxT("SetTieWrap - true"), (note.SetTieWrap() && note.HasTieWrap()));
    TEST(wxT("SetTieWrap - false"), (note.SetTieWrap(false) && !note.HasTieWrap()));
    return (true);
}

/// Tests the Hammer On Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseHammerOn()
{
    //------Last Checked------//
    // - Jan 17, 2005
    Note note;
    TEST(wxT("SetHammerOn - true"), (note.SetHammerOn() && note.HasHammerOn()));
    TEST(wxT("SetHammerOn - false"), (note.SetHammerOn(false) && !note.HasHammerOn()));
    return (true);
}

/// Tests the Hammer On From Nowhere Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseHammerOnFromNowhere()
{
    //------Last Checked------//
    // - Jan 24, 2005
    Note note;
    TEST(wxT("SetHammerOnFromNowhere - true"), (note.SetHammerOnFromNowhere() && note.HasHammerOnFromNowhere() && !note.HasHammerOn()));
    TEST(wxT("SetHammerOnFromNowhere - false"), (note.SetHammerOnFromNowhere(false) && !note.HasHammerOnFromNowhere()));
    return (true);
}

/// Tests the Pull Off Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCasePullOff()
{
    //------Last Checked------//
    // - Jan 17, 2005
    Note note;
    TEST(wxT("SetPullOff - true"), (note.SetPullOff() && note.HasPullOff()));
    TEST(wxT("SetPullOff - false"), (note.SetPullOff(false) && !note.HasPullOff()));
    return (true);
}

/// Tests the Pull Off To Nowhere Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCasePullOffToNowhere()
{
    //------Last Checked------//
    // - Jan 24, 2005
    Note note;
    TEST(wxT("SetPullOffToNowhere - true"), (note.SetPullOffToNowhere() && note.HasPullOffToNowhere() && !note.HasPullOff()));
    TEST(wxT("SetPullOffToNowhere - false"), (note.SetPullOffToNowhere(false) && !note.HasPullOffToNowhere()));
    return (true);
}
    
/// Tests the Natural Harmonic Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseNaturalHarmonic()
{
    //------Last Checked------//
    // - Jan 17, 2005
    Note note;
    TEST(wxT("SetNaturalHarmonic - true"), (note.SetNaturalHarmonic() && note.IsNaturalHarmonic()));
    TEST(wxT("SetNaturalHarmonic - false"), (note.SetNaturalHarmonic(false) && !note.IsNaturalHarmonic()));
    return (true);
}

/// Tests the Ghost Note Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseGhostNote()
{
    //------Last Checked------//
    // - Jan 17, 2005
    Note note;
    TEST(wxT("SetGhostNote - true"), (note.SetGhostNote() && note.IsGhostNote()));
    TEST(wxT("SetGhostNote - false"), (note.SetGhostNote(false) && !note.IsGhostNote()));
    return (true);
}

/// Tests the Octave 8va Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseOctave8va()
{
    //------Last Checked------//
    // - Jan 17, 2005
    Note note;
    TEST(wxT("SetOctave8va - true"), (note.SetOctave8va() && note.IsOctave8va()));
    TEST(wxT("SetOctave8va - false"), (note.SetOctave8va(false) && !note.IsOctave8va()));
    return (true);
}

/// Tests the Octave 15ma Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseOctave15ma()
{
    //------Last Checked------//
    // - Jan 17, 2005
    Note note;
    TEST(wxT("SetOctave15ma - true"), (note.SetOctave15ma() && note.IsOctave15ma()));
    TEST(wxT("SetOctave15ma - false"), (note.SetOctave15ma(false) && !note.IsOctave15ma()));
    return (true);
}

/// Tests the Octave 8mb Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseOctave8mb()
{
    //------Last Checked------//
    // - Jan 17, 2005
    Note note;
    TEST(wxT("SetOctave8vb - true"), (note.SetOctave8vb() && note.IsOctave8vb()));
    TEST(wxT("SetOctave8vb - false"), (note.SetOctave8vb(false) && !note.IsOctave8vb()));
    return (true);
}

/// Tests the Octave 15mb Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseOctave15mb()
{
    //------Last Checked------//
    // - Jan 17, 2005
    Note note;
    TEST(wxT("SetOctave15mb - true"), (note.SetOctave15mb() && note.IsOctave15mb()));
    TEST(wxT("SetOctave15mb - false"), (note.SetOctave15mb(false) && !note.IsOctave15mb()));
    return (true);
}

/// Tests the Simple Flags Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseSimpleFlags()
{
    //------Last Checked------//
    // - Jan 17, 2005
    
    // TEST CASE: IsValidSimpleFlag
    {
        wxWord i = Note::tied;
        for (; i <= (2 * Note::octave15mb); i *= 2)
        {
            TEST(wxString::Format(wxT("IsValidSimpleFlag - %d"), i),
                (Note::IsValidSimpleFlag(i) == (i <= Note::octave15mb))
            );
        }
    }
    
    // TEST CASE: SetSimpleFlag
    {
        Note chordName;
    
        wxWord i = 1;
        for (; i <= (2 * Note::octave15mb); i *= 2)
        {
            TEST(wxString::Format(wxT("SetSimpleFlag - %d"), i),
                (chordName.SetSimpleFlag(i) == (i <= Note::octave15mb)) &&
                ((i > Note::octave15mb) ? 1 : chordName.IsSimpleFlagSet(i)));
        
            TEST(wxString::Format(wxT("ClearSimpleFlag - %d"), i),
                (chordName.ClearSimpleFlag(i) == (i <= Note::octave15mb)) &&
                ((i > Note::octave15mb) ? 1 : !chordName.IsSimpleFlagSet(i)));
        }
    }
    
    return (true);
}

/// Tests the Slide Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseSlide()
{
    //------Last Checked------//
    // - Jan 21, 2005
    
    // TEST CASE: SetSlideInto
    {
        Note note;
        TEST(wxT("SetSlideInto - none"),
            (!note.SetSlideInto(Note::slideIntoNone)) &&
            (!note.HasSlide())
        );
        note.SetSlideInto(Note::slideIntoFromAbove);
        TEST(wxT("SetSlideInto - none 2"),
            (note.SetSlideInto(Note::slideIntoNone)) &&
            (!note.HasSlide())
        );
        
        wxByte i = Note::slideIntoFromBelow;
        for (; i <= (Note::slideIntoLegatoSlideDownwards + 1); i++)
        {
            Note note;
            bool set = note.SetSlideInto(i);
            wxByte type = 0;
            note.GetSlideInto(type);
            TEST(wxString::Format(wxT("SetSlideInto - %d"), i),
                ((set == (i <= Note::slideIntoLegatoSlideDownwards)) &&
                ((i > Note::slideIntoLegatoSlideUpwards) ? 1 : 
                    ((note.HasSlideInto()) && (type == i))
                ))
            );
        }
        
        {
            Note note(2,10);
            note.SetSlideInto(Note::slideIntoFromBelow);
            bool set = note.SetSlideInto(Note::slideIntoFromAbove);
            wxByte type = 0;
            note.GetSlideInto(type);
            TEST(wxT("SetSlideInto - update"),
                (set) &&
                (note.HasSlideInto()) &&
                (type == Note::slideIntoFromAbove)
            );
        }
    }
    
    // TEST CASE: ClearSlideInto
    {
        Note note;
        bool set = note.SetSlideInto(Note::slideIntoFromBelow);
        note.ClearSlideInto();
        TEST(wxT("ClearSlideInto"), 
            ((set) &&
            !note.HasSlideInto())
        );
        
        {
            Note note;
            set = note.SetSlideInto(Note::slideIntoFromBelow);
            note.SetSlideOutOf(Note::slideOutOfDownwards, 2);
            TEST(wxT("ClearSlideInto w/slide out of"),
                (note.ClearSlideInto()) &&
                (!note.HasSlideInto()) &&
                (note.HasSlideOutOf())
            );
        }
    }

    // TEST CASE: SetSlideOutOf
    {
        Note note;
        TEST(wxT("SetSlideOutOf - none"),
            !note.SetSlideOutOf(Note::slideOutOfNone, 0) &&
            !note.HasSlide());
        note.SetSlideOutOf(Note::slideOutOfShiftSlide, 2);
        TEST(wxT("SetSlideOutOf - none 2"),
            note.SetSlideOutOf(Note::slideOutOfNone, 0) &&
            !note.HasSlide());
            
        wxByte i = Note::slideOutOfShiftSlide;
        for (; i <= (Note::slideOutOfUpwards + 1); i++)
        {
            Note note;
            bool set = note.SetSlideOutOf(i, 2);
            wxByte type = 0;
            wxInt8 steps = 0;
            note.GetSlideOutOf(type, steps);
            TEST(wxString::Format(wxT("SetSlideOutOf - %d"), i),
                ((set == (i <= Note::slideOutOfUpwards)) &&
                ((i > Note::slideOutOfUpwards) ? 1 : 
                    ((note.HasSlideOutOf()) && (type == i))
                ))
            );
        }
        
        {
            Note note;
            note.SetSlideOutOf(Note::slideOutOfDownwards, 2);
            bool set = note.SetSlideOutOf(Note::slideOutOfUpwards, 4);
            wxByte type = 0;
            wxInt8 steps = 0;
            note.GetSlideOutOf(type, steps);
            
            TEST(wxT("SetSlideOutOf - update"),
                (set) &&
                (type == Note::slideOutOfUpwards) &&
                (steps == 4)
            );
        }
    }
    
    // TEST CASE: ClearSlideOutOf
    {
        Note note;
        bool set = note.SetSlideOutOf(Note::slideOutOfDownwards, 2);
        note.ClearSlideOutOf();
        TEST(wxT("ClearSlideOutOf"), 
            ((set) &&
            !note.HasSlideOutOf())
        );
        
        {
            Note note;
            set = note.SetSlideOutOf(Note::slideOutOfDownwards, 2);
            note.SetSlideInto(Note::slideIntoFromBelow);
            
            TEST(wxT("ClearSlideOutOf w/slide into"),
                (note.ClearSlideOutOf()) &&
                (!note.HasSlideOutOf()) &&
                (note.HasSlideInto())
            );
        }
    }
    
    return (true);
}

// Bend Functions
/// Tests the Bend Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseBend()
{
    //------Last Checked------//
    // - Jan 24, 2005
    
    // TEST CASE: IsValidBendType
    {
        wxByte i = Note::normalBend;
        for (; i <= (Note::immediateRelease); i++)
            TEST(wxString::Format(wxT("IsValidBendType - %d"), i), 
                (Note::IsValidBendType(i) == (i <= Note::immediateRelease))
            );
    }
    
    // TEST CASE: IsValidBentPitch
    {
        wxByte i = 0;
        for (; i <= (Note::MAX_BEND_PITCH + 1); i++)
            TEST(wxString::Format(wxT("IsValidBentPitch - %d"), i),
                (Note::IsValidBentPitch(i) == (i <= Note::MAX_BEND_PITCH))
            );
    }
    
    // TEST CASE: IsValidReleasePitch
    {
        wxByte i = 0;
        for (; i <= (Note::MAX_BEND_PITCH + 1); i++)
            TEST(wxString::Format(wxT("IsValidReleasePitch - %d"), i),
                (Note::IsValidReleasePitch(i) == (i <= Note::MAX_BEND_PITCH))
            );
    }
    
    // TEST CASE: IsValidDrawStartPoint
    {
        wxByte i = Note::lowPoint;
        for (; i <= (Note::highPoint + 1); i++)
            TEST(wxString::Format(wxT("IsValidDrawStartPoint - %d"), i),
                (Note::IsValidDrawStartPoint(i) == (i <= Note::highPoint))
            );
    }
    
    // TEST CASE: IsValidDrawEndPoint
    {
        wxByte i = Note::lowPoint;
        for (; i <= (Note::highPoint + 1); i++)
            TEST(wxString::Format(wxT("IsValidDrawEndPoint - %d"), i),
                (Note::IsValidDrawEndPoint(i) == (i <= Note::highPoint))
            );
    }
            
    // TEST CASE: IsValidBend
    // NOTE: Very slow, so its commented out - it worked last check, trust me
/*    {
        wxByte type = Note::normalBend;
        for (; type <= (Note::immediateRelease + 1); type++)
        {
            wxByte bentPitch = 0;
            for (; bentPitch <= (Note::MAX_BEND_PITCH + 1); bentPitch++)
            {
                wxByte releasePitch = 0;
                for (; releasePitch <= (Note::MAX_BEND_PITCH + 1); releasePitch++)
                {
                    wxByte duration = 0;
                    for (; duration <= (Note::MAX_BEND_DURATION + 1); duration++)
                    {
                        wxByte drawStartPoint = Note::lowPoint;
                        for (; drawStartPoint <= (Note::highPoint + 1); drawStartPoint++)
                        {
                            wxByte drawEndPoint = Note::lowPoint;
                            for (; drawEndPoint <= (Note::highPoint + 1); drawEndPoint++)
                            {
                                bool valid = ((Note::IsValidBendType(type)) &&
                                    (Note::IsValidBentPitch(bentPitch)) &&
                                    (Note::IsValidReleasePitch(releasePitch)) &&
                                    (Note::IsValidBendDuration(duration)) &&
                                    (Note::IsValidDrawStartPoint(drawStartPoint)) &&
                                    (Note::IsValidDrawEndPoint(drawEndPoint))
                                );
                                    
                                if ((type == Note::normalBend) || (type == Note::bendAndHold))
                                {
                                    // a) Bent pitch must be greater than zero
                                    // b) Release pitch must be zero
                                    // c) Duration may be any value
                                    // d) Draw start must be low or mid and end must be higher
                                    valid = (valid & ((bentPitch > 0) && (releasePitch == 0) && (drawStartPoint <= Note::midPoint) && (drawEndPoint > drawStartPoint)));
                                }
                                else if (type == Note::bendAndRelease)
                                {
                                    // a) Bent pitch must be greater than zero
                                    // b) Release pitch must be less than bent pitch
                                    // c) Duration must be zero
                                    // d) Draw start must be low or mid and drawEndPoint must be low or mid
                                    valid = (valid & ((bentPitch > 0) && (releasePitch < bentPitch) && (duration == 0) && (drawStartPoint <= Note::midPoint) && (drawEndPoint <= Note::midPoint)));
                                }
                                else if ((type == Note::preBend) || (type == Note::preBendAndHold))
                                {
                                    // a) Bent pitch must be greater than zero
                                    // b) Release pitch must be zero
                                    // c) Duration must be zero
                                    // d) Draw start must be low, and end must be higher
                                    valid = (valid & ((bentPitch > 0) && (releasePitch == 0) && (duration == 0) && (drawStartPoint == Note::lowPoint) && (drawEndPoint > drawStartPoint)));
                                }
                                else if (type == Note::preBendAndRelease)
                                {
                                    // a) Bent pitch must be greater than zero
                                    // b) Release pitch must be less than bent pitch
                                    // c) Duration must be zero
                                    // d) Draw start and end must be low
                                    valid = (valid & ((bentPitch > 0) && (releasePitch < bentPitch) && (duration == 0) && (drawStartPoint == Note::lowPoint) && (drawEndPoint == Note::lowPoint)));
                                }
                                else if (type == Note::gradualRelease)
                                {
                                    // a) Bent pitch must be zero
                                    // b) Release pitch must be standard to 2 3/4
                                    // c) Duration must be > 0
                                    // d) Draw start must be high or mid point, draw end must be lower
                                    valid = (valid & ((bentPitch == 0) && (releasePitch <= 11) && (duration > 0) && (drawStartPoint >= Note::midPoint) && (drawEndPoint < drawStartPoint)));
                                }
                                else if (type == Note::immediateRelease)
                                {
                                    // a) Bent pitch must be zero
                                    // b) Release pitch must be zero
                                    // c) Duration must be zero
                                    // d) Draw start must be high or mid, and match draw end
                                    valid = (valid & ((bentPitch == 0) && (releasePitch == 0) && (duration == 0) && (drawStartPoint >= Note::midPoint) && (drawStartPoint == drawEndPoint)));
                                }
                                
                                TEST(wxString::Format(wxT("IsValidBend - %d, %d, %d, %d, %d, %d"), type, bentPitch, releasePitch, duration, drawStartPoint, drawEndPoint),
                                    (Note::IsValidBend(type, bentPitch, releasePitch, duration, drawStartPoint, drawEndPoint) == valid)
                                );
                            }
                        }
                    }
                }
            }
        }
    }*/
    
    // TEST CASE: SetBend
    {
        Note note;
        TEST(wxT("SetBend - invalid type"),
            (!note.SetBend(255, 4, 0, 1, Note::lowPoint, Note::midPoint))
        );
        TEST(wxT("SetBend - invalid bent pitch"),
            (!note.SetBend(Note::bendAndHold, 0, 0, 1, Note::lowPoint, Note::midPoint))
        );
        TEST(wxT("SetBend - invalid release pitch"),
            (!note.SetBend(Note::bendAndHold, 4, 1, 1, Note::lowPoint, Note::midPoint))
        );
        TEST(wxT("SetBend - invalid duration"),
            (!note.SetBend(Note::bendAndHold, 4, 0, 255, Note::lowPoint, Note::midPoint))
        );
        TEST(wxT("SetBend - invalid draw start point"),
            (!note.SetBend(Note::bendAndHold, 4, 0, 1, 255, Note::midPoint))
        );
        TEST(wxT("SetBend - invalid draw end point"),
            (!note.SetBend(Note::bendAndHold, 4, 0, 1, Note::lowPoint, 255))
        );
        
        note.SetBend(Note::bendAndHold, 4, 0, 1, Note::lowPoint, Note::midPoint);
                
        wxByte type = 0;
        wxByte bentPitch = 0;
        wxByte releasePitch = 0;
        wxByte duration = 0;
        wxByte drawStart = 0;
        wxByte drawEnd = 0;
        note.GetBend(type, bentPitch, releasePitch, duration, drawStart, drawEnd);
        
        TEST(wxT("SetBend - valid"), 
            (type == Note::bendAndHold) &&
            (bentPitch == 4) &&
            (releasePitch == 0) &&
            (duration == 1) &&
            (drawStart == Note::lowPoint) &&
            (drawEnd == Note::midPoint) &&
            (note.HasBend())
        );
        
        {
            Note note;
            note.SetBend(Note::bendAndHold, 4, 0, 1, Note::lowPoint, Note::midPoint);
            
            bool set = note.SetBend(Note::normalBend, 2, 0, 2, Note::midPoint, Note::highPoint);
                
            wxByte type = 0;
            wxByte bentPitch = 0;
            wxByte releasePitch = 0;
            wxByte duration = 0;
            wxByte drawStart = 0;
            wxByte drawEnd = 0;
            note.GetBend(type, bentPitch, releasePitch, duration, drawStart, drawEnd);
            
            TEST(wxT("SetBend - update"), 
                (set) &&
                (type == Note::normalBend) &&
                (bentPitch == 2) &&
                (releasePitch == 0) &&
                (duration == 2) &&
                (drawStart == Note::midPoint) &&
                (drawEnd == Note::highPoint) &&
                (note.HasBend())
            );
        }
        
        {
            Note note;
            wxByte type = 0;
            wxByte bentPitch = 0;
            wxByte releasePitch = 0;
            wxByte duration = 0;
            wxByte drawStart = 0;
            wxByte drawEnd = 0;
            TEST(wxT("GetBend - false"),
                !note.GetBend(type, bentPitch, releasePitch, duration, drawStart, drawEnd)
            );
                
        }
    }
    
    // Clear Bend
    {
        Note note;
        note.SetBend(Note::bendAndHold, 4, 0, 1, Note::lowPoint, Note::midPoint);
        TEST(wxT("ClearBend"),
            (note.ClearBend()) &&
            (!note.HasBend())
        );
    }
    return (true);
}

/// Tests the Tapped Harmonic Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseTappedHarmonic()
{
    //------Last Checked------//
    // - Jan 19, 2005
    
    // TEST CASE: SetTappedHarmonic
    {
        wxByte i = 0;
        for (; i <= (Note::MAX_FRET_NUMBER + 1); i++)
        {
            Note note;
            bool set = note.SetTappedHarmonic(i);
            wxByte tappedFretNumber = 0;
            note.GetTappedHarmonic(tappedFretNumber);
            TEST(wxString::Format(wxT("SetTappedHarmonic - %d"), i),
                ((set == (i <= Note::MAX_FRET_NUMBER)) &&
                ((i > Note::MAX_FRET_NUMBER) ? 1 : 
                    ((note.HasTappedHarmonic()) && (tappedFretNumber == i))
                ))
            );
        }
    }
    
    // TEST CASE: ClearTappedHarmonic
    {
        Note note;
        bool set = note.SetTappedHarmonic(10);
        note.ClearTappedHarmonic();
        TEST(wxT("ClearTappedHarmonic"), 
            ((set) &&
            !note.HasTappedHarmonic())
        );
    }
    
    return (true);
}

/// Tests the Trill Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseTrill()
{
    //------Last Checked------//
    // - Jan 19, 2005
    
    // TEST CASE: SetTrill
    {
        wxByte i = 0;
        for (; i <= (Note::MAX_FRET_NUMBER + 1); i++)
        {
            Note note;
            bool set = note.SetTrill(i);
            wxByte trilledFretNumber = 0;
            note.GetTrill(trilledFretNumber);
            TEST(wxString::Format(wxT("SetTrill - %d"), i),
                ((set == (i <= Note::MAX_FRET_NUMBER)) &&
                ((i > Note::MAX_FRET_NUMBER) ? 1 : 
                    ((note.HasTrill()) && (trilledFretNumber == i))
                ))
            );
        }
    }
    
    // TEST CASE: ClearTrill
    {
        Note note;
        bool set = note.SetTrill(10);
        note.ClearTrill();
        TEST(wxT("ClearTrill"), 
            ((set) &&
            !note.HasTrill())
        );
    }
    
    return (true);
}

/// Tests the Artificial Harmonic Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseArtificialHarmonic()
{
    //------Last Checked------//
    // - Jan 20, 2005
    
    // TEST CASE: SetArtificialHarmonic
    {
        wxByte i = ChordName::C;
        for (; i <= ChordName::B; i++)
        {
            wxByte j = ChordName::variationDown;
            for (; j <= ChordName::variationUp; j++)
            {
                wxByte k = Note::artificialHarmonicOctaveLoco;
                for (; k <= (Note::artificialHarmonicOctave15ma + 1); k++)
                {
                    Note note;
                    bool set = note.SetArtificialHarmonic(i,j,k);
                    wxByte key = 0;
                    wxByte keyVariation = 0;
                    wxByte octave = 0;
                    note.GetArtificialHarmonic(key, keyVariation, octave);
                
                    TEST(wxString::Format(wxT("SetArtificialHarmonic - %d, %d, %d"), i, j, k), 
                        (set == (ChordName::IsValidKeyAndVariation(i,j) && (k <= Note::artificialHarmonicOctave15ma))) &&
                        (!ChordName::IsValidKeyAndVariation(i,j) || (k > Note::artificialHarmonicOctave15ma)) ? 1 : 
                        (key == i && keyVariation == j && octave == k)
                    );
                }
            }
        }
    }
    
    // TEST CASE: ClearArtificialHarmonic
    {
        Note note;
        bool set = note.SetArtificialHarmonic(ChordName::AFlat, ChordName::variationDefault, 1);
        note.ClearArtificialHarmonic();
        TEST(wxT("ClearArtificialHarmonic"), 
            ((set) &&
            !note.HasArtificialHarmonic())
        );
    }
    
    return (true);
}

/// Tests the Complex Symbol Functions
/// @return True if all tests were executed, false if not
bool NoteTestSuite::TestCaseComplexSymbol()
{
    //------Last Checked------//
    // - Jan 24, 2005
    
    // TEST CASE: IsValidComplexSymbolType
    {
        wxByte i = 0;
        for (;;i++)
        {
            TEST(wxString::Format(wxT("IsValidComplexSymbolType - %d"), i),
                (Note::IsValidComplexSymbolType(i) == ((i == Note::slide) || (i == Note::bend) || (i == Note::tappedHarmonic) || (i == Note::trill) || (i == Note::artificialHarmonic)))
            );

            // block overflow
            if (i == 255)
                break;
        }
    }
           
    // TEST CASE: AddComplexSymbol
    {
        Note note;
        TEST(wxT("AddComplexSymbol - invalid type"), !note.AddComplexSymbol(0));
        note.SetTappedHarmonic(13);
        
        note.SetTappedHarmonic(10);
        wxByte tappedFretNumber = 0;
        bool set = note.GetTappedHarmonic(tappedFretNumber);
        
        TEST(wxT("AddComplexSymbol - update"),
            (set) &&
            (tappedFretNumber == 10)
        );
        note.SetTrill(5);
        note.SetArtificialHarmonic(ChordName::C, ChordName::variationDefault, 1);
        
        TEST(wxT("AddComplexSymbol - full"), !note.SetSlideInto(Note::slideIntoFromBelow));
    }
    
    // TEST CASE: GetComplexSymbolCount
    {
        Note note;
        TEST(wxT("GetComplexSymbolCount - 0"),
            (note.GetComplexSymbolCount() == 0)
        );
        
        note.SetTappedHarmonic(13);
        note.SetTrill(5);
        note.SetArtificialHarmonic(ChordName::C, ChordName::variationDefault, 1);
        
        TEST(wxT("GetComplexSymbolCount - 3"), 
            (note.GetComplexSymbolCount() == 3)
        );
        
        note.ClearComplexSymbolArrayContents();
        TEST(wxT("GetComplexSymbolCount - 0"),
            (note.GetComplexSymbolCount() == 0)
        );
    }
    
    // TEST CASE: FindComplexSymbol
    {
        Note note;
        note.SetTappedHarmonic(13);
        note.SetTrill(5);
        note.SetArtificialHarmonic(ChordName::C, ChordName::variationDefault, 1);
        
        TEST(wxT("FindComplexSymbol - tapped harmonic"), (note.FindComplexSymbol(Note::tappedHarmonic) == 0));
        TEST(wxT("FindComplexSymbol - trill"), (note.FindComplexSymbol(Note::trill) == 1));
        TEST(wxT("FindComplexSymbol - artificial harmonic"), (note.FindComplexSymbol(Note::artificialHarmonic) == 2));
    }

    // TEST CASE: RemoveComplexSymbol
    {
        Note note;
        note.SetTappedHarmonic(13);
        note.SetTrill(5);
        note.SetArtificialHarmonic(ChordName::C, ChordName::variationDefault, 1);
        
        TEST(wxT("RemoveComplexSymbol - tapped harmonic"), 
            (note.RemoveComplexSymbol(Note::tappedHarmonic)) &&
            (!note.HasTappedHarmonic())
        );
        
        TEST(wxT("RemoveComplexSymbol - trill"), 
            (note.RemoveComplexSymbol(Note::trill)) &&
            (!note.HasTrill())
        );
        
        TEST(wxT("RemoveComplexSymbol - artificial harmonic"), 
            (note.RemoveComplexSymbol(Note::artificialHarmonic)) &&
            (!note.HasArtificialHarmonic())
        );
    }
        
    return (true);
}
