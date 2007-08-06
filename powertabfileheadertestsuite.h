/////////////////////////////////////////////////////////////////////////////
// Name:            powertabfileheadertestsuite.h
// Purpose:         Performs unit testing on the PowerTabFileHeader class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 4, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __POWERTABFILEHEADERTESTSUITE_H__
#define __POWERTABFILEHEADERTESTSUITE_H__

/// Performs unit testing on the PowerTabFileHeader class
class PowerTabFileHeaderTestSuite :
    public TestSuite
{
    DECLARE_DYNAMIC_CLASS(PowerTabFileHeaderTestSuite)

// Constructor/Destructor
public:
    PowerTabFileHeaderTestSuite();
    ~PowerTabFileHeaderTestSuite();
    
// Overrides
    size_t GetTestCount() const;
    bool RunTestCases();
    
// Test Case Functions
private:
    bool TestCaseConstructor();
    bool TestCaseOperator();
    bool TestCaseSerialize();
    bool TestCasePowerTabFileMarker();
    bool TestCaseFileVersion();
    bool TestCaseFileType();
    bool TestCaseSongContentType();
    bool TestCaseSongTitle();
    bool TestCaseSongArtist();
    bool TestCaseSongReleaseType();
    bool TestCaseSongAudioReleaseTitle();
    bool TestCaseSongAudioReleaseYear();
    bool TestCaseSongAudioReleaseLive();    
    bool TestCaseSongVideoReleaseTitle();
    bool TestCaseSongVideoReleaseLive();
    bool TestCaseSongBootlegTitle();
    bool TestCaseSongBootlegDate();
    bool TestCaseSongAuthorType();
    bool TestCaseSongComposer();
    bool TestCaseSongLyricist();
    bool TestCaseSongArranger();
    bool TestCaseSongGuitarScoreTranscriber();
    bool TestCaseSongBassScoreTranscriber();
    bool TestCaseSongCopyright();
    bool TestCaseSongLyrics();
    bool TestCaseSongGuitarScoreNotes();
    bool TestCaseSongBassScoreNotes();
    bool TestCaseLessonTitle();
    bool TestCaseLessonSubtitle();
    bool TestCaseLessonMusicStyle();
    bool TestCaseLessonLevel();
    bool TestCaseLessonAuthor();
    bool TestCaseLessonNotes();
    bool TestCaseLessonCopyright();
};   
#endif
