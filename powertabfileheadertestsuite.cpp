/////////////////////////////////////////////////////////////////////////////
// Name:            powertabfileheadertestsuite.cpp
// Purpose:         Performs unit testing on the PowerTabFileHeader class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 4, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "powertabfileheadertestsuite.h"

#include "powertabfileheader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(PowerTabFileHeaderTestSuite, TestSuite)

/// Default Constructor
PowerTabFileHeaderTestSuite::PowerTabFileHeaderTestSuite()
{
    //------Last Checked------//
    // - Dec 4, 2004
}

/// Destructor
PowerTabFileHeaderTestSuite::~PowerTabFileHeaderTestSuite()
{
    //------Last Checked------//
    // - Dec 4, 2004
}

/// Gets the total number of tests in the test suite
/// @return The total number of tests in the test suite
size_t PowerTabFileHeaderTestSuite::GetTestCount() const
{
    //------Last Checked------//
    // - Dec 29, 2004
    return (222);
}

/// Executes all test cases in the test suite
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::RunTestCases()
{
    //------Last Checked------//
    // - Dec 29, 2004
    if (!TestCaseConstructor())
        return (false);
    if (!TestCaseOperator())
        return (false);
    if (!TestCaseSerialize())
        return (false);	
    if (!TestCasePowerTabFileMarker())
        return (false);
    if (!TestCaseFileVersion())
        return (false);
    if (!TestCaseFileType())
        return (false);
    if (!TestCaseSongContentType())
        return (false);
    if (!TestCaseSongTitle())
        return (false);
    if (!TestCaseSongArtist())
        return (false);
    if (!TestCaseSongReleaseType())
        return (false);
    if (!TestCaseSongAudioReleaseTitle())
        return (false);
    if (!TestCaseSongAudioReleaseYear())
        return (false);
    if (!TestCaseSongAudioReleaseLive())
        return (false);
    if (!TestCaseSongVideoReleaseTitle())
        return (false);
    if (!TestCaseSongVideoReleaseLive())
        return (false);
    if (!TestCaseSongBootlegTitle())
        return (false);
    if (!TestCaseSongBootlegDate())
        return (false);
    if (!TestCaseSongAuthorType())
        return (false);
    if (!TestCaseSongComposer())
        return (false);
    if (!TestCaseSongLyricist())
        return (false);
    if (!TestCaseSongArranger())
        return (false);
    if (!TestCaseSongGuitarScoreTranscriber())
        return (false);
    if (!TestCaseSongBassScoreTranscriber())
        return (false);
    if (!TestCaseSongCopyright())
        return (false);
    if (!TestCaseSongLyrics())
        return (false);
    if (!TestCaseSongGuitarScoreNotes())
        return (false);
    if (!TestCaseSongBassScoreNotes())
        return (false);
    if (!TestCaseLessonTitle())
        return (false);
    if (!TestCaseLessonSubtitle())
        return (false);
    if (!TestCaseLessonMusicStyle())
        return (false);
    if (!TestCaseLessonLevel())
        return (false);
    if (!TestCaseLessonAuthor())
        return (false);
    if (!TestCaseLessonNotes())
        return (false);
    if (!TestCaseLessonCopyright())
        return (false);
    
    return (true);
}

/// Tests the Constructors
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseConstructor()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader powerTabFileHeader;
	TEST(_T("Default Constructor"), 
	(
	    (powerTabFileHeader.GetVersion() ==
            PowerTabFileHeader::FILEVERSION_CURRENT) &&
	    (powerTabFileHeader.IsSong()) &&
	    (powerTabFileHeader.GetSongContentType() ==
            PowerTabFileHeader::CONTENTTYPE_NONE) &&
	    (powerTabFileHeader.GetSongTitle().IsEmpty()) &&
	    (powerTabFileHeader.GetSongArtist().IsEmpty()) &&
	    (powerTabFileHeader.GetSongReleaseType() ==
            PowerTabFileHeader::RELEASETYPE_PUBLIC_AUDIO) &&
	    (powerTabFileHeader.GetSongReleaseTitle().IsEmpty()) &&
	    (powerTabFileHeader.GetSongAudioReleaseTitle().IsEmpty()) &&
	    (!powerTabFileHeader.IsSongAudioReleaseLive()) &&
	    (powerTabFileHeader.GetSongVideoReleaseTitle().IsEmpty()) &&
	    (!powerTabFileHeader.IsSongVideoReleaseLive()) &&
	    (powerTabFileHeader.GetSongBootlegTitle().IsEmpty()) &&
	    (powerTabFileHeader.GetSongAuthorType() ==
            PowerTabFileHeader::AUTHORTYPE_AUTHORKNOWN) &&
	    (powerTabFileHeader.GetSongComposer().IsEmpty()) &&
	    (powerTabFileHeader.GetSongLyricist().IsEmpty()) &&
	    (powerTabFileHeader.GetSongArranger().IsEmpty()) &&
	    (powerTabFileHeader.GetSongGuitarScoreTranscriber().IsEmpty()) &&
	    (powerTabFileHeader.GetSongBassScoreTranscriber().IsEmpty()) &&
	    (powerTabFileHeader.GetSongCopyright().IsEmpty()) &&
	    (powerTabFileHeader.GetSongLyrics().IsEmpty()) &&
	    (powerTabFileHeader.GetSongGuitarScoreNotes().IsEmpty()) &&
	    (powerTabFileHeader.GetSongBassScoreNotes().IsEmpty()) &&
	    (powerTabFileHeader.GetLessonTitle().IsEmpty()) &&
	    (powerTabFileHeader.GetLessonSubtitle().IsEmpty()) &&
	    (powerTabFileHeader.GetLessonMusicStyle() ==
            PowerTabFileHeader::MUSICSTYLE_GENERAL) &&
	    (powerTabFileHeader.GetLessonLevel() ==
            PowerTabFileHeader::LESSONLEVEL_INTERMEDIATE) &&
	    (powerTabFileHeader.GetLessonAuthor().IsEmpty()) &&
	    (powerTabFileHeader.GetLessonCopyright().IsEmpty())
	));

    // TEST CASE: Copy Constructor
    {
        PowerTabFileHeader header;
        powerTabFileHeader.SetVersion(PowerTabFileHeader::FILEVERSION_1_5);
        powerTabFileHeader.SetSongContentType(
            PowerTabFileHeader::CONTENTTYPE_BASS);
        powerTabFileHeader.SetSongTitle(wxT("title"));
        powerTabFileHeader.SetSongArtist(wxT("artist"));
        powerTabFileHeader.SetSongAudioReleaseTitle(wxT("audio release title"));
        powerTabFileHeader.SetSongAudioReleaseLive(true);
        
        PowerTabFileHeader header2(header);
        TEST(wxT("Copy Constructor"), (header2 == header));
    }
    return (true);
}

/// Tests the Operators
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseOperator()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header, header2, header3, header4, header5;
    header3.SetVersion(PowerTabFileHeader::FILEVERSION_1_0);
    header4.SetLesson();
    
    PowerTabFileHeader header10, header11, header12, header13;
    header10.SetSongContentType(PowerTabFileHeader::CONTENTTYPE_BASS);
    header11.SetSongTitle(wxT("a"));
    header12.SetSongArtist(wxT("b"));
    header13.SetSongReleaseType(PowerTabFileHeader::RELEASETYPE_BOOTLEG);
    
    PowerTabFileHeader header20, header21, header22, header23;
    header20.SetSongAudioReleaseType(
        PowerTabFileHeader::AUDIORELEASETYPE_BOXSET);
    header21.SetSongAudioReleaseTitle(wxT("a"));
    header22.SetSongAudioReleaseYear(1900);
    header23.SetSongAudioReleaseLive();
    
    PowerTabFileHeader header30, header31;
    header30.SetSongVideoReleaseTitle(wxT("a"));
    header31.SetSongVideoReleaseLive();
    
    PowerTabFileHeader header40, header41;
    header40.SetSongBootlegTitle(wxT("a"));
    header41.SetSongBootlegDate(wxDateTime::Now());
    
    PowerTabFileHeader header50, header51, header52, header53, header54,
        header55, header56, header57, header58, header59;
    
    header50.SetSongAuthorType(PowerTabFileHeader::AUTHORTYPE_TRADITIONAL);
    header51.SetSongComposer(wxT("c"));
    header52.SetSongLyricist(wxT("-"));
    header53.SetSongArranger(wxT("o"));
    header54.SetSongGuitarScoreTranscriber(wxT("b"));
    header55.SetSongBassScoreTranscriber(wxT("a"));
    header56.SetSongCopyright(wxT("p"));
    header57.SetSongLyrics(wxT("l"));
    header58.SetSongGuitarScoreNotes(wxT("t"));
    header59.SetSongBassScoreNotes(wxT("x"));

    PowerTabFileHeader header100, header101, header102, header103, header104,
        header105, header106;
    header100.SetLessonTitle(wxT("a"));
    header101.SetLessonSubtitle(wxT("b"));
    header102.SetLessonMusicStyle(PowerTabFileHeader::MUSICSTYLE_COUNTRY);
    header103.SetLessonLevel(PowerTabFileHeader::LESSONLEVEL_ADVANCED);
    header104.SetLessonAuthor(wxT("c"));
    header105.SetLessonNotes(wxT("d"));
    header106.SetLessonCopyright(wxT("e"));
    
    /// TEST CASE: Operator=
    {
        PowerTabFileHeader header200;
        header200 = header;
        TEST(wxT("Operator="), (header200 == header));
        
        // TEST CASE: Self assignment
        {
            PowerTabFileHeader header201;
            header201.SetLessonTitle(wxT("a"));
            header201.SetLessonSubtitle(wxT("b"));
            header201.SetLessonMusicStyle(
                PowerTabFileHeader::MUSICSTYLE_COUNTRY);
            header201.SetLessonLevel(PowerTabFileHeader::LESSONLEVEL_ADVANCED);
            header201.SetLessonAuthor(wxT("c"));
            header201.SetLessonNotes(wxT("d"));
            header201.SetLessonCopyright(wxT("e"));
            
            header201 = header201;
            
            TEST(wxT("Operator= (self-assignment)"), 
                (header201.GetLessonTitle() == wxT("a")) &&
                (header201.GetLessonSubtitle() == wxT("b")) &&
                (header201.GetLessonMusicStyle() ==
                    PowerTabFileHeader::MUSICSTYLE_COUNTRY) &&
                (header201.GetLessonLevel() ==
                    PowerTabFileHeader::LESSONLEVEL_ADVANCED) &&
                (header201.GetLessonAuthor() == wxT("c")) &&
                (header201.GetLessonNotes() == wxT("d")) &&
                (header201.GetLessonCopyright() == wxT("e"))
            );
        }
    }
    /// TEST CASE: Operator==
    {
        TEST(wxT("Operator== - header == header"), (header == header2));
        TEST(wxT("Operator== - header != header 2"), !(header == header3));
        TEST(wxT("Operator== - header != header 3"), !(header == header4));
        
        TEST(wxT("Operator== - header != header 10"), !(header == header10));
        TEST(wxT("Operator== - header != header 11"), !(header == header11));
        TEST(wxT("Operator== - header != header 12"), !(header == header12));
        TEST(wxT("Operator== - header != header 13"), !(header == header13));
        
        TEST(wxT("Operator== - header != header 20"), !(header == header20));
        TEST(wxT("Operator== - header != header 21"), !(header == header21));
        TEST(wxT("Operator== - header != header 22"), !(header == header22));
        TEST(wxT("Operator== - header != header 23"), !(header == header23));
        
        TEST(wxT("Operator== - header != header 30"), !(header == header30));
        TEST(wxT("Operator== - header != header 31"), !(header == header31));
        
        TEST(wxT("Operator== - header != header 40"), !(header == header40));
        TEST(wxT("Operator== - header != header 41"), !(header == header41));
        
        TEST(wxT("Operator== - header != header 40"), !(header == header40));
        TEST(wxT("Operator== - header != header 41"), !(header == header41));
        
        TEST(wxT("Operator== - header != header 50"), !(header == header50));
        TEST(wxT("Operator== - header != header 51"), !(header == header51));
        TEST(wxT("Operator== - header != header 52"), !(header == header52));
        TEST(wxT("Operator== - header != header 53"), !(header == header53));
        TEST(wxT("Operator== - header != header 54"), !(header == header54));
        TEST(wxT("Operator== - header != header 55"), !(header == header55));
        TEST(wxT("Operator== - header != header 56"), !(header == header56));
        TEST(wxT("Operator== - header != header 57"), !(header == header57));
        TEST(wxT("Operator== - header != header 58"), !(header == header58));
        TEST(wxT("Operator== - header != header 59"), !(header == header59));
        
        TEST(wxT("Operator== - header != header 100"), !(header == header100));
        TEST(wxT("Operator== - header != header 101"), !(header == header101));
        TEST(wxT("Operator== - header != header 102"), !(header == header102));
        TEST(wxT("Operator== - header != header 103"), !(header == header103));
        TEST(wxT("Operator== - header != header 104"), !(header == header104));
        TEST(wxT("Operator== - header != header 105"), !(header == header105));
        TEST(wxT("Operator== - header != header 106"), !(header == header106));
    }

    /// TEST CASE: Operator!=
    {
        TEST(wxT("Operator!= - header != header"), !(header != header2));
        TEST(wxT("Operator!= - header != header 2"), (header != header3));
        TEST(wxT("Operator!= - header != header 3"), (header != header4));
        
        TEST(wxT("Operator!= - header != header 10"), (header != header10));
        TEST(wxT("Operator!= - header != header 11"), (header != header11));
        TEST(wxT("Operator!= - header != header 12"), (header != header12));
        TEST(wxT("Operator!= - header != header 13"), (header != header13));
        
        TEST(wxT("Operator!= - header != header 20"), (header != header20));
        TEST(wxT("Operator!= - header != header 21"), (header != header21));
        TEST(wxT("Operator!= - header != header 22"), (header != header22));
        TEST(wxT("Operator!= - header != header 23"), (header != header23));
        
        TEST(wxT("Operator!= - header != header 30"), (header != header30));
        TEST(wxT("Operator!= - header != header 31"), (header != header31));
               
        TEST(wxT("Operator!= - header != header 40"), (header != header40));
        TEST(wxT("Operator!= - header != header 41"), (header != header41));
        
        TEST(wxT("Operator!= - header != header 50"), (header != header50));
        TEST(wxT("Operator!= - header != header 51"), (header != header51));
        TEST(wxT("Operator!= - header != header 52"), (header != header52));
        TEST(wxT("Operator!= - header != header 53"), (header != header53));
        TEST(wxT("Operator!= - header != header 54"), (header != header54));
        TEST(wxT("Operator!= - header != header 55"), (header != header55));
        TEST(wxT("Operator!= - header != header 56"), (header != header56));
        TEST(wxT("Operator!= - header != header 57"), (header != header57));
        TEST(wxT("Operator!= - header != header 58"), (header != header58));
        TEST(wxT("Operator!= - header != header 59"), (header != header59));
        
        TEST(wxT("Operator!= - header != header 100"), (header != header100));
        TEST(wxT("Operator!= - header != header 101"), (header != header101));
        TEST(wxT("Operator!= - header != header 102"), (header != header102));
        TEST(wxT("Operator!= - header != header 103"), (header != header103));
        TEST(wxT("Operator!= - header != header 104"), (header != header104));
        TEST(wxT("Operator!= - header != header 105"), (header != header105));
        TEST(wxT("Operator!= - header != header 106"), (header != header106));
    }
    
    return (true);
}

/// Tests the Serialization Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSerialize()
{
    //------Last Checked------//
    // - Dec 28, 2004
    
    // TEST CASE: Serialize Song Audio Release
    {
        bool ok = false;
        
        TestStream testStream;
        PowerTabOutputStream streamOut(testStream.GetOutputStream());
        
        // Write test data to stream
        PowerTabFileHeader headerOut;
        headerOut.SetSong();
        headerOut.SetSongTitle(wxT("Title"));
        headerOut.SetSongArtist(wxT("Artist"));
        headerOut.SetSongAudioReleaseTitle(wxT("Title2"));
        headerOut.SetSongAudioReleaseLive();
        headerOut.SetSongAudioReleaseYear(2010);
        headerOut.SetSongComposer(wxT("Composer"));
        headerOut.SetSongLyricist(wxT("Lyricist"));
        headerOut.SetSongArranger(wxT("Arranger"));
        headerOut.SetSongGuitarScoreTranscriber(wxT("Transcriber"));
        headerOut.SetSongBassScoreTranscriber(wxT("Transcriber"));
        headerOut.SetSongCopyright(wxT("Copyright"));
        headerOut.SetSongLyrics(wxT("Lyrics"));
        headerOut.SetSongGuitarScoreNotes(wxT("Notes"));
        headerOut.SetSongBassScoreNotes(wxT("Notes"));
                
        headerOut.Serialize(streamOut);

        // Output must be OK before using input
        if (testStream.CheckOutputState())
        {
            PowerTabInputStream streamIn(testStream.GetInputStream());
        
            // Read test data back from stream
            PowerTabFileHeader headerIn;
            headerIn.Deserialize(streamIn);
            
            ok = (headerIn == headerOut);
        }
        
        TEST(wxT("Serialize Song Audio Release"), ok);
    }
    
    // TEST CASE: Serialize Song Video Release
    {
        bool ok = false;
        
        TestStream testStream;
        PowerTabOutputStream streamOut(testStream.GetOutputStream());
        
        // Write test data to stream
        PowerTabFileHeader headerOut;
        headerOut.SetSong();
        headerOut.SetSongTitle(wxT("Title"));
        headerOut.SetSongArtist(wxT("Artist"));
        headerOut.SetSongReleaseType(
            PowerTabFileHeader::RELEASETYPE_PUBLIC_VIDEO);
        headerOut.SetSongVideoReleaseTitle(wxT("Title2"));
        headerOut.SetSongVideoReleaseLive();        
        headerOut.SetSongComposer(wxT("Composer"));
        headerOut.SetSongLyricist(wxT("Lyricist"));
        headerOut.SetSongArranger(wxT("Arranger"));
        headerOut.SetSongGuitarScoreTranscriber(wxT("Transcriber"));
        headerOut.SetSongBassScoreTranscriber(wxT("Transcriber"));
        headerOut.SetSongCopyright(wxT("Copyright"));
        headerOut.SetSongLyrics(wxT("Lyrics"));
        headerOut.SetSongGuitarScoreNotes(wxT("Notes"));
        headerOut.SetSongBassScoreNotes(wxT("Notes"));
                
        headerOut.Serialize(streamOut);

        // Output must be OK before using input
        if (testStream.CheckOutputState())
        {
            PowerTabInputStream streamIn(testStream.GetInputStream());
        
            // Read test data back from stream
            PowerTabFileHeader headerIn;
            headerIn.Deserialize(streamIn);
            
            ok = (headerIn == headerOut);
        }
        
        TEST(wxT("Serialize Song Video Release"), ok);
    }
    
    // TEST CASE: Serialize Song Bootleg
    {
        bool ok = false;
        
        TestStream testStream;
        PowerTabOutputStream streamOut(testStream.GetOutputStream());
        
        // Write test data to stream
        PowerTabFileHeader headerOut;
        headerOut.SetSong();
        headerOut.SetSongTitle(wxT("Title"));
        headerOut.SetSongArtist(wxT("Artist"));
        headerOut.SetSongReleaseType(PowerTabFileHeader::RELEASETYPE_BOOTLEG);
        headerOut.SetSongBootlegTitle(wxT("Title2"));
        headerOut.SetSongBootlegDate(wxDateTime::Now());
        headerOut.SetSongComposer(wxT("Composer"));
        headerOut.SetSongLyricist(wxT("Lyricist"));
        headerOut.SetSongArranger(wxT("Arranger"));
        headerOut.SetSongGuitarScoreTranscriber(wxT("Transcriber"));
        headerOut.SetSongBassScoreTranscriber(wxT("Transcriber"));
        headerOut.SetSongCopyright(wxT("Copyright"));
        headerOut.SetSongLyrics(wxT("Lyrics"));
        headerOut.SetSongGuitarScoreNotes(wxT("Notes"));
        headerOut.SetSongBassScoreNotes(wxT("Notes"));
                
        headerOut.Serialize(streamOut);

        // Output must be OK before using input
        if (testStream.CheckOutputState())
        {
            PowerTabInputStream streamIn(testStream.GetInputStream());
        
            // Read test data back from stream
            PowerTabFileHeader headerIn;
            headerIn.Deserialize(streamIn);
            
            ok = (headerIn == headerOut);
        }
        
        TEST(wxT("Serialize Song Bootleg"), ok);
    }
    
    // TEST CASE: Serialize Song Not Released
    {
        bool ok = false;
        
        TestStream testStream;
        PowerTabOutputStream streamOut(testStream.GetOutputStream());
        
        // Write test data to stream
        PowerTabFileHeader headerOut;
        headerOut.SetSong();
        headerOut.SetSongTitle(wxT("Title"));
        headerOut.SetSongArtist(wxT("Artist"));
        headerOut.SetSongReleaseType(
            PowerTabFileHeader::RELEASETYPE_NOTRELEASED);
        headerOut.SetSongAuthorType(PowerTabFileHeader::AUTHORTYPE_TRADITIONAL);
        headerOut.SetSongArranger(wxT("Arranger"));
        headerOut.SetSongGuitarScoreTranscriber(wxT("Transcriber"));
        headerOut.SetSongBassScoreTranscriber(wxT("Transcriber"));
        headerOut.SetSongCopyright(wxT("Copyright"));
        headerOut.SetSongLyrics(wxT("Lyrics"));
        headerOut.SetSongGuitarScoreNotes(wxT("Notes"));
        headerOut.SetSongBassScoreNotes(wxT("Notes"));
                
        headerOut.Serialize(streamOut);

        // Output must be OK before using input
        if (testStream.CheckOutputState())
        {
            PowerTabInputStream streamIn(testStream.GetInputStream());
        
            // Read test data back from stream
            PowerTabFileHeader headerIn;
            headerIn.Deserialize(streamIn);
            
            ok = (headerIn == headerOut);
        }
        
        TEST(wxT("Serialize Song Not Released"), ok);
    }
    
    // TEST CASE: Serialize Lesson
    {
        bool ok = false;
        
        TestStream testStream;
        PowerTabOutputStream streamOut(testStream.GetOutputStream());
        
        // Write test data to stream
        PowerTabFileHeader headerOut;
        headerOut.SetLesson();
        headerOut.SetLessonTitle(wxT("Title"));
        headerOut.SetLessonSubtitle(wxT("Subtitle"));
        headerOut.SetLessonMusicStyle(PowerTabFileHeader::MUSICSTYLE_BLUES);
        headerOut.SetLessonLevel(PowerTabFileHeader::LESSONLEVEL_ADVANCED);
        headerOut.SetLessonAuthor(wxT("Author"));
        headerOut.SetLessonNotes(wxT("Notes"));
        
        headerOut.Serialize(streamOut);

        // Output must be OK before using input
        if (testStream.CheckOutputState())
        {
            PowerTabInputStream streamIn(testStream.GetInputStream());
        
            // Read test data back from stream
            PowerTabFileHeader headerIn;
            headerIn.Deserialize(streamIn);
            
            ok = (headerIn == headerOut);
        }
        
        TEST(wxT("Serialize Lesson"), ok);
    }
    
	return (true);
}

/// Tests the Power Tab File Marker functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCasePowerTabFileMarker()
{
    //------Last Checked------//
    // - Dec 28, 2004
    TEST(wxT("IsValidPowerTabFileMarker - false"),
        !PowerTabFileHeader::IsValidPowerTabFileMarker(0));
    TEST(wxT("IsValidPowerTabFileMarker - true"),
        PowerTabFileHeader::IsValidPowerTabFileMarker(
        PowerTabFileHeader::POWERTABFILE_MARKER));
    return (true);
}

/// Tests the File Version Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseFileVersion()
{
    //------Last Checked------//
    // - Dec 28, 2004
    wxWord i = PowerTabFileHeader::FILEVERSION_1_0 - 1;
    for (; i <= PowerTabFileHeader::NUM_FILEVERSIONS; i++)
    {
        TEST(wxString::Format(wxT("IsValidFileVersion - %d"), i),
            (PowerTabFileHeader::IsValidFileVersion(i) ==
            (i >= PowerTabFileHeader::FILEVERSION_1_0 &&
            i <= PowerTabFileHeader::FILEVERSION_CURRENT)));
    }

    PowerTabFileHeader header;
    i = PowerTabFileHeader::FILEVERSION_1_0 - 1;
    for (; i <= PowerTabFileHeader::NUM_FILEVERSIONS; i++)
    {
        TEST(wxT("SetVersion - %d"), 
            (header.SetVersion(i) ==
            (i >= PowerTabFileHeader::FILEVERSION_1_0 &&
                i <= PowerTabFileHeader::FILEVERSION_CURRENT) &&
            ((i < PowerTabFileHeader::FILEVERSION_1_0 ||
                i > PowerTabFileHeader::FILEVERSION_CURRENT) ? 1 :
                (header.GetVersion() == i))
            )
        );
    }
        
    return (true);
}

/// Tests the File Type Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseFileType()
{
    //------Last Checked------//
    // - Dec 28, 2004
    wxByte i = PowerTabFileHeader::FILETYPE_SONG;
    for (; i <= PowerTabFileHeader::NUM_FILETYPES; i++)
        TEST(wxString::Format(wxT("IsValidFileType - %d"), i),
            (PowerTabFileHeader::IsValidFileType(i) ==
            (i >= PowerTabFileHeader::FILETYPE_SONG &&
            i <= PowerTabFileHeader::FILETYPE_LESSON)));
        
    PowerTabFileHeader header;
    i = PowerTabFileHeader::FILETYPE_SONG;
    for (; i <= PowerTabFileHeader::NUM_FILETYPES; i++)
        TEST(wxT("SetFileType - %d"),
            (header.SetFileType(i) ==
                (i >= PowerTabFileHeader::FILETYPE_SONG &&
                i <= PowerTabFileHeader::FILETYPE_LESSON) &&
            ((i >= PowerTabFileHeader::NUM_FILETYPES) ? 1 :
                (header.GetFileType() == i))
            )
        );
    
    // TEST CASE: SetSong
    {
        PowerTabFileHeader header;
        header.SetSong();
        TEST(wxT("SetSong"), header.IsSong());
    }
    
    // TEST CASE: SetLesson
    {
        PowerTabFileHeader header;
        header.SetLesson();
        TEST(wxT("SetLesson"), header.IsLesson());
    }
    
    return (true);
}

/// Tests the Song Content Type Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongContentType()
{
    //------Last Checked------//
    // - Dec 28, 2004            
    wxByte i = PowerTabFileHeader::CONTENTTYPE_NONE;
    for (; i <= (PowerTabFileHeader::CONTENTTYPE_ALL + 1); i++)
        TEST(wxString::Format(wxT("IsValidSongContentType - %d"), i),
        (PowerTabFileHeader::IsValidSongContentType(i) ==
            (i <= PowerTabFileHeader::CONTENTTYPE_ALL)));
        
    PowerTabFileHeader header;
    i = PowerTabFileHeader::CONTENTTYPE_NONE;
    for (; i <= (PowerTabFileHeader::CONTENTTYPE_ALL + 1); i++)
        TEST(wxT("SetSongContentType - %d"),
            (header.SetSongContentType(i) == (i <= PowerTabFileHeader::CONTENTTYPE_ALL) &&
            ((i > PowerTabFileHeader::CONTENTTYPE_ALL) ? 1 :
                (header.GetSongContentType() == i))
            )
        );
        
    return (true);
}

/// Tests the Song Title Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongTitle()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetSongTitle - invalid title"), !header.SetSongTitle(NULL));
    TEST(wxT("SetSongTitle - valid title"), header.SetSongTitle(wxT("Test")) &&
        header.GetSongTitle() == wxT("Test"));    
    return (true);
}

/// Tests the Song Artist Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongArtist()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetSongArtist - invalid artist"), !header.SetSongArtist(NULL));
    TEST(wxT("SetSongArtist - valid artist"),
        header.SetSongArtist(wxT("Test")) &&
        header.GetSongArtist() == wxT("Test"));    
    return (true);
}

/// Tests the Song Release Type Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongReleaseType()
{
    //------Last Checked------//
    // - Dec 28, 2004
    
    wxByte i = PowerTabFileHeader::RELEASETYPE_PUBLIC_AUDIO;
    for (; i <= PowerTabFileHeader::NUM_RELEASETYPES; i++)
        TEST(wxString::Format(wxT("IsValidSongReleaseType - %d"), i),
            (PowerTabFileHeader::IsValidSongReleaseType(i) ==
            (i >= PowerTabFileHeader::RELEASETYPE_PUBLIC_AUDIO &&
            i <= PowerTabFileHeader::RELEASETYPE_NOTRELEASED)));
        
    PowerTabFileHeader header;
    i = PowerTabFileHeader::RELEASETYPE_PUBLIC_AUDIO;
    for (; i <= PowerTabFileHeader::NUM_RELEASETYPES; i++)
        TEST(wxT("SetSongReleaseType - %d"),
            (header.SetSongReleaseType(i) ==
                (i >= PowerTabFileHeader::RELEASETYPE_PUBLIC_AUDIO &&
                i <= PowerTabFileHeader::RELEASETYPE_NOTRELEASED) &&
            ((i >= PowerTabFileHeader::NUM_RELEASETYPES) ? 1 :
            (header.GetSongReleaseType() == i))
            )
        );
    
    return (true);
}

/// Tests the Song Audio Release Title Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongAudioReleaseTitle()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetSongAudioReleaseTitle - invalid title"),
        !header.SetSongAudioReleaseTitle(NULL));
    TEST(wxT("SetSongAudioReleaseTitle - valid title"),
        header.SetSongAudioReleaseTitle(wxT("Test")) &&
        header.GetSongAudioReleaseTitle() == wxT("Test"));    
    return (true);
}

/// Tests the Song Audio Release Year Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongAudioReleaseYear()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    header.SetSongAudioReleaseYear(2010);
    TEST(wxT("SetSongAudioReleaseYear"),
        header.GetSongAudioReleaseYear() == 2010);
    return (true);
}

/// Tests the Song Audio Release Live Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongAudioReleaseLive()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    header.SetSongAudioReleaseLive();
    TEST(wxT("SetSongAudioReleaseLive - true"),
        header.IsSongAudioReleaseLive());
    header.SetSongAudioReleaseLive(false);
    TEST(wxT("SetSongAudioReleaseLive - false"),
        !header.IsSongAudioReleaseLive());        
    return (true);
}
    
/// Tests the Song Video Release Title Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongVideoReleaseTitle()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetSongVideoReleaseTitle - invalid title"),
        !header.SetSongVideoReleaseTitle(NULL));
    TEST(wxT("SetSongVideoReleaseTitle - valid title"),
        header.SetSongVideoReleaseTitle(wxT("Test")) &&
        header.GetSongVideoReleaseTitle() == wxT("Test"));    
    return (true);
}

/// Tests the Song Video Release Live Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongVideoReleaseLive()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    header.SetSongVideoReleaseLive();
    TEST(wxT("SetSongVideoReleaseLive - true"),
        header.IsSongVideoReleaseLive());
    header.SetSongVideoReleaseLive(false);
    TEST(wxT("SetSongVideoReleaseLive - false"),
        !header.IsSongVideoReleaseLive());        
    return (true);
}

/// Tests the Song Bootleg Title Functions
/// @return True if all tests were executed, false if not    
bool PowerTabFileHeaderTestSuite::TestCaseSongBootlegTitle()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetSongBootlegTitle - invalid title"),
        !header.SetSongBootlegTitle(NULL));
    TEST(wxT("SetSongBootlegTitle - valid title"),
        header.SetSongBootlegTitle(wxT("Test")) &&
        header.GetSongBootlegTitle() == wxT("Test"));    
    return (true);
}

/// Tests the Song Bootleg Date Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongBootlegDate()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    wxDateTime testDate(0, wxDateTime::Jan, 1999);
    TEST(wxT("SetSongBootlegDate - invalid date"),
        !header.SetSongBootlegDate(testDate));
    wxDateTime testDate2 = wxDateTime::Now();
    header.SetSongBootlegDate(testDate2);
    wxDateTime testDate3 = header.GetSongBootlegDate();
    TEST(wxT("SetSongBootlegDate - valid date"),
        ((testDate3.GetDay() == testDate2.GetDay()) &&
        (testDate3.GetMonth() == testDate2.GetMonth()) &&
        (testDate3.GetYear() == testDate2.GetYear())));
    return (true);
}
    
/// Tests the Song Author Type Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongAuthorType()
{
    //------Last Checked------//
    // - Dec 28, 2004
    wxByte i = PowerTabFileHeader::AUTHORTYPE_AUTHORKNOWN;
    for (; i <= PowerTabFileHeader::NUM_AUTHORTYPES; i++)
    {
        TEST(wxString::Format(wxT("IsValidAuthorType - %d"), i),
        (PowerTabFileHeader::IsValidAuthorType(i) ==
        (i >= PowerTabFileHeader::AUTHORTYPE_AUTHORKNOWN &&
        i <= PowerTabFileHeader::AUTHORTYPE_TRADITIONAL)));
    }
        
    PowerTabFileHeader header;
    i = PowerTabFileHeader::AUTHORTYPE_AUTHORKNOWN;
    for (; i <= PowerTabFileHeader::NUM_AUTHORTYPES; i++)
        TEST(wxT("SetSongAuthorType - %d"),
            (header.SetSongAuthorType(i) ==
                (i >= PowerTabFileHeader::AUTHORTYPE_AUTHORKNOWN &&
                i <= PowerTabFileHeader::AUTHORTYPE_TRADITIONAL) &&
            ((i >= PowerTabFileHeader::NUM_AUTHORTYPES) ? 1 :
                (header.GetSongAuthorType() == i))
            )
        );
    
    return (true);
}

/// Tests the Song Composer Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongComposer()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetSongComposer - invalid composer"),
        !header.SetSongComposer(NULL));
    TEST(wxT("SetSongComposer - valid composer"),
        header.SetSongComposer(wxT("Test")) && 
        header.GetSongComposer() == wxT("Test"));    
    return (true);
}

/// Tests the Song Lyricist Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongLyricist()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetSongLyricist - invalid lyricist"),
        !header.SetSongLyricist(NULL));
    TEST(wxT("SetSongLyricist - valid lyricist"),
        header.SetSongLyricist(wxT("Test")) &&
        header.GetSongLyricist() == wxT("Test"));    
    return (true);
}

/// Tests the Song Arranger Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongArranger()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetSongArranger - invalid arranger"),
        !header.SetSongArranger(NULL));
    TEST(wxT("SetSongArranger - valid arranger"),
        header.SetSongArranger(wxT("Test")) &&
        header.GetSongArranger() == wxT("Test"));    
    return (true);
}

/// Tests the Song Copyright Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongCopyright()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetSongCopyright - invalid copyright"),
        !header.SetSongCopyright(NULL));
    TEST(wxT("SetSongCopyright - valid copyright"),
        header.SetSongCopyright(wxT("Test")) && 
        header.GetSongCopyright() == wxT("Test"));   
    return (true);
}

/// Tests the Song Guitar Score Transcriber Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongGuitarScoreTranscriber()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetSongGuitarScoreTranscriber - invalid transcriber"),
        !header.SetSongGuitarScoreTranscriber(NULL));
    TEST(wxT("SetSongGuitarScoreTranscriber - valid transcriber"),
        header.SetSongGuitarScoreTranscriber(wxT("Test")) &&
        header.GetSongGuitarScoreTranscriber() == wxT("Test"));    
    return (true);
}

/// Tests the Song Bass Score Transcriber Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongBassScoreTranscriber()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetSongBassScoreTranscriber - invalid transcriber"),
        !header.SetSongBassScoreTranscriber(NULL));
    TEST(wxT("SetSongBassScoreTranscriber - valid transcriber"),
        header.SetSongBassScoreTranscriber(wxT("Test")) &&
        header.GetSongBassScoreTranscriber() == wxT("Test"));    
    return (true);
}

/// Tests the Song Lyrics Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongLyrics()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetSongLyrics - invalid lyrics"),
        !header.SetSongLyrics(NULL));
    TEST(wxT("SetSongLyrics - valid lyrics"),
        header.SetSongLyrics(wxT("Test")) &&
        header.GetSongLyrics() == wxT("Test"));   
    return (true);
}

/// Tests the Song Guitar Score Notes Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongGuitarScoreNotes()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetSongGuitarScoreNotes - invalid notes"),
        !header.SetSongGuitarScoreNotes(NULL));
    TEST(wxT("SetSongGuitarScoreNotes - valid notes"),
        header.SetSongGuitarScoreNotes(wxT("Test")) &&
        header.GetSongGuitarScoreNotes() == wxT("Test"));    
    return (true);
}

/// Tests the Song Bass Score Notes Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseSongBassScoreNotes()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetSongBassScoreNotes - invalid notes"),
        !header.SetSongBassScoreNotes(NULL));
    TEST(wxT("SetSongBassScoreNotes - valid notes"),
        header.SetSongBassScoreNotes(wxT("Test")) &&
        header.GetSongBassScoreNotes() == wxT("Test"));    
    return (true);
}
    
/// Tests the Lesson Title Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseLessonTitle()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetLessonTitle - invalid title"),
        !header.SetLessonTitle(NULL));
    TEST(wxT("SetLessonTitle - valid title"),
        header.SetLessonTitle(wxT("Test")) &&
        header.GetLessonTitle() == wxT("Test"));    
    return (true);
}

/// Tests the Lesson Subtitle Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseLessonSubtitle()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetLessonSubtitle - invalid subtitle"),
        !header.SetLessonSubtitle(NULL));
    TEST(wxT("SetLessonSubtitle - valid subtitle"),
        header.SetLessonSubtitle(wxT("Test")) &&
        header.GetLessonSubtitle() == wxT("Test"));    
    return (true);
}

/// Tests the Lesson Music Style Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseLessonMusicStyle()
{
    //------Last Checked------//
    // - Dec 28, 2004
    wxByte i = PowerTabFileHeader::MUSICSTYLE_ALTERNATIVE;
    for (; i <= PowerTabFileHeader::NUM_MUSICSTYLES; i++)
    {
        TEST(wxString::Format(wxT("IsValidMusicStyle - %d"), i),
        (PowerTabFileHeader::IsValidMusicStyle(i) ==
        (i < PowerTabFileHeader::NUM_MUSICSTYLES)));
    }
        
    PowerTabFileHeader header;
    i = PowerTabFileHeader::MUSICSTYLE_ALTERNATIVE;
    for (; i <= PowerTabFileHeader::NUM_MUSICSTYLES; i++)
    {
        TEST(wxT("SetMusicStyle - %d"),
            (header.SetLessonMusicStyle(i) ==
                (i < PowerTabFileHeader::NUM_MUSICSTYLES) &&
            ((i >= PowerTabFileHeader::NUM_MUSICSTYLES) ? 1 :
                (header.GetLessonMusicStyle() == i))
            )
        );
    }
    return (true);
}

/// Tests the Lesson Level Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseLessonLevel()
{
    //------Last Checked------//
    // - Dec 28, 2004
    wxByte i = PowerTabFileHeader::LESSONLEVEL_BEGINNER;
    for (; i <= PowerTabFileHeader::NUM_LESSONLEVELS; i++)
    {
        TEST(wxString::Format(wxT("IsValidLessonLevel - %d"), i),
        (PowerTabFileHeader::IsValidLessonLevel(i) ==
            (i < PowerTabFileHeader::NUM_LESSONLEVELS)));
    }
        
    PowerTabFileHeader header;
    i = PowerTabFileHeader::LESSONLEVEL_BEGINNER;
    for (; i <= PowerTabFileHeader::NUM_LESSONLEVELS; i++)
    {
        TEST(wxT("SetLessonLevel - %d"),
            (header.SetLessonLevel(i) == (i < PowerTabFileHeader::NUM_LESSONLEVELS) &&
            ((i >= PowerTabFileHeader::NUM_LESSONLEVELS) ? 1 : (header.GetLessonLevel() == i))
            )
        );
    }
    return (true);
}

/// Tests the Lesson Author Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseLessonAuthor()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetLessonAuthor - invalid author"),
        !header.SetLessonAuthor(NULL));
    TEST(wxT("SetLessonAuthor - valid author"),
        header.SetLessonAuthor(wxT("Test")) &&
        header.GetLessonAuthor() == wxT("Test"));    
    return (true);
}

/// Tests the Lesson Notes Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseLessonNotes()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetLessonNotes - invalid notes"),
        !header.SetLessonNotes(NULL));
    TEST(wxT("SetLessonNotes - valid notes"),
        header.SetLessonNotes(wxT("Test")) &&
        header.GetLessonNotes() == wxT("Test"));    
    return (true);
}

/// Tests the Lesson Copyright Functions
/// @return True if all tests were executed, false if not
bool PowerTabFileHeaderTestSuite::TestCaseLessonCopyright()
{
    //------Last Checked------//
    // - Dec 28, 2004
    PowerTabFileHeader header;
    TEST(wxT("SetLessonCopyright - invalid copyright"),
        !header.SetLessonCopyright(NULL));
    TEST(wxT("SetLessonCopyright - valid copyright"),
        header.SetLessonCopyright(wxT("Test")) &&
        header.GetLessonCopyright() == wxT("Test"));    
    return (true);
}
