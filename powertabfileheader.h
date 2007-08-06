/////////////////////////////////////////////////////////////////////////////
// Name:            powertabfileheader.h
// Purpose:         Stores all of the information found in the header of a Power Tab file
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 4, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __POWERTABFILEHEADER_H__
#define __POWERTABFILEHEADER_H__

/// Stores all of the information found in the header of a Power Tab file
class PowerTabFileHeader
{
// Constants
public:
    static const wxUint32 POWERTABFILE_MARKER;                      ///< Special marker that appears at the start of every Power Tab file

    static const wxWord NUM_FILEVERSIONS;                           ///< Number of power tab file formats
    static const wxWord FILEVERSION_1_0;                            ///< Version 1.0        Feb. 6, 2000
    static const wxWord FILEVERSION_1_0_2;                          ///< Version 1.0.2      Feb. 21, 2000
    static const wxWord FILEVERSION_1_5;                            ///< Version 1.5        May. 22, 2000
    static const wxWord FILEVERSION_1_7;                            ///< Version 1.7        Aug. 30, 2000
    static const wxWord FILEVERSION_CURRENT;                        ///< Current version of power tab file format
    
    static const wxByte NUM_FILETYPES;                              ///< Number of file types
    static const wxByte FILETYPE_SONG;                              ///< File is a song
    static const wxByte FILETYPE_LESSON;                            ///< File is a lesson

    static const wxByte CONTENTTYPE_NONE;                           ///< File contains no content
    static const wxByte CONTENTTYPE_GUITAR;                         ///< File contains guitar score content
    static const wxByte CONTENTTYPE_BASS;                           ///< File contains bass score content
    static const wxByte CONTENTTYPE_PERCUSSION;                     ///< File contains percussion score content
    static const wxByte CONTENTTYPE_ALL;                            ///< File contains guitar score & bass score & percussion score content

    static const wxByte NUM_RELEASETYPES;                           ///< Number of release types
    static const wxByte RELEASETYPE_PUBLIC_AUDIO;                   ///< Song was released to the public in an audio format (cd, tape, etc.)
    static const wxByte RELEASETYPE_PUBLIC_VIDEO;                   ///< Song was released to the public in a video format (video tape, dvd, etc.)
    static const wxByte RELEASETYPE_BOOTLEG;                        ///< Song is a bootleg
    static const wxByte RELEASETYPE_NOTRELEASED;                    ///< Song was never released (self-composition)
    
    static const wxByte NUM_AUDIORELEASETYPES;                      ///< Number of audio release types
    static const wxByte AUDIORELEASETYPE_SINGLE;                    ///< Song was released on a single
    static const wxByte AUDIORELEASETYPE_EP;                        ///< Song was released on an EP 
    static const wxByte AUDIORELEASETYPE_ALBUM;                     ///< Song was released on a "normal" album
    static const wxByte AUDIORELEASETYPE_DOUBLEALBUM;               ///< Song was released on a double album
    static const wxByte AUDIORELEASETYPE_TRIPLEALBUM;               ///< Song was released on a triple album
    static const wxByte AUDIORELEASETYPE_BOXSET;                    ///< Song was released on a boxset compilation
    
    static const wxByte NUM_AUTHORTYPES;                            ///< Number of author types
    static const wxByte AUTHORTYPE_AUTHORKNOWN;                     ///< The author of the song is known
    static const wxByte AUTHORTYPE_TRADITIONAL;                     ///< The author of the song is unknown (i.e. Greensleeves)
    
    static const wxWord NUM_MUSICSTYLES;                            ///< Number of music styles (used by lessons)
    static const wxWord MUSICSTYLE_ALTERNATIVE;
    static const wxWord MUSICSTYLE_BLUEGRASS;
    static const wxWord MUSICSTYLE_BLUES;
    static const wxWord MUSICSTYLE_COUNTRY;
    static const wxWord MUSICSTYLE_FINGERPICK;
    static const wxWord MUSICSTYLE_FLAMENCO;
    static const wxWord MUSICSTYLE_FOLK;
    static const wxWord MUSICSTYLE_FUNK;
    static const wxWord MUSICSTYLE_FUSION;
    static const wxWord MUSICSTYLE_GENERAL;
    static const wxWord MUSICSTYLE_JAZZ;
    static const wxWord MUSICSTYLE_METAL;
    static const wxWord MUSICSTYLE_OTHER;
    static const wxWord MUSICSTYLE_POP;
    static const wxWord MUSICSTYLE_PROGRESSIVE;
    static const wxWord MUSICSTYLE_PUNK;
    static const wxWord MUSICSTYLE_REGGAE;
    static const wxWord MUSICSTYLE_ROCK;
    static const wxWord MUSICSTYLE_SWING;
    
    static const wxByte NUM_LESSONLEVELS;                           ///< Number of lesson difficulty levels
    static const wxByte LESSONLEVEL_BEGINNER;                       ///< Easy
    static const wxByte LESSONLEVEL_INTERMEDIATE;                   ///< Average
    static const wxByte LESSONLEVEL_ADVANCED;                       ///< Difficult

    // Compatibility Constants (used by v1.0-v1.5 formats)
protected:
    static const wxByte NUM_RELEASEDONS;
    static const wxByte RO_SINGLE;
    static const wxByte RO_EP;
    static const wxByte RO_LP;
    static const wxByte RO_DOUBLELP;
    static const wxByte RO_TRIPLELP;
    static const wxByte RO_BOXSET;
    static const wxByte RO_BOOTLEG;
    static const wxByte RO_DEMO;
    static const wxByte RO_SOUNDTRACK;
    static const wxByte RO_VIDEO;
    static const wxByte RO_NONE;
    
// Member Variables
protected:
    wxWord      m_version;                                          ///< Version number of the file format
    wxByte      m_fileType;                                         ///< Type of file
    
    // Song type data
    struct SONG_DATA
    {
        wxByte      contentType;                                    ///< Type of content in the file (guitar score, bass score, percussion score)
        wxString    title;                                          ///< Title of the song
        wxString    artist;                                         ///< Artist who performed song
        wxByte      releaseType;                                    ///< How the song was released (if released)

        struct AUDIO_DATA
        {
            wxByte      type;                                       ///< Type of audio release the song was released on (single, EP, LP, double LP, etc)
            wxString    title;                                      ///< Title of the audio release
            wxWord      year;                                       ///< Year the audio release was released
            wxByte      live;                                       ///< Determines whether the song is a live performance
        } audioData;

        struct  VIDEO_DATA
        {
            wxString    title;                                      ///< Title of video the song was released on
            wxByte      live;                                       ///< Determines whether the song is a live performance
        } videoData;

        struct BOOTLEG_DATA
        {
            wxString title;                                         ///< Title of the bootleg
            wxWord  month;                                          ///< Date of bootleg (month is one based)
            wxWord  day;
            wxWord  year;
        } bootlegData;

        wxByte authorType;                                          ///< Author type (known or unknown/traditional)

        struct AUTHOR_DATA
        {
            wxString composer;                                      ///< Author of the song's music
            wxString lyricist;                                      ///< Author of the song's lyrics
        } authorData;
        
        wxString arranger;                                          ///< Performer who arranged the version of the song
        
        wxString guitarScoreTranscriber;                            ///< Transcriber of the guitar score
        wxString bassScoreTranscriber;                              ///< Transcriber of the bass score
        
        wxString copyright;                                         ///< Copyright notice
        
        wxString lyrics;                                            ///< Song lyrics
        
        wxString guitarScoreNotes;                                  ///< Notes for the guitar score
        wxString bassScoreNotes;                                    ///< Notes for the base score
    } m_songData;

    // Lesson type data
    struct LESSON_DATA
    {
        wxString    title;                                          ///< Title of the lesson
        wxString    subtitle;                                       ///< Subtitle for the lesson
        wxWord      musicStyle;                                     ///< Style of the music the lesson encompasses
        wxByte      level;                                          ///< Level of difficulty for the lesson
        wxString    author;                                         ///< Author of the lesson
        wxString    notes;                                          ///< Notes for the lesson
        wxString    copyright;                                      ///< Copyright for lesson
    } m_lessonData;

// Constructor/Destructor
public:
    PowerTabFileHeader();
    PowerTabFileHeader(const PowerTabFileHeader& header);
    ~PowerTabFileHeader();

// Operators
    const PowerTabFileHeader& operator=(const PowerTabFileHeader& header);
    bool operator==(const PowerTabFileHeader& header) const;
    bool operator!=(const PowerTabFileHeader& header) const;

// Serialization Functions
    bool Serialize(wxOutputStream& stream);
    bool Serialize(PowerTabOutputStream& stream);
    bool Deserialize(wxInputStream& stream);
    bool Deserialize(PowerTabInputStream& stream);
    bool DeserializeVersion1_7(PowerTabInputStream& stream);
    bool DeserializeVersion1_5(PowerTabInputStream& stream);
    bool DeserializeVersion1_0(PowerTabInputStream& stream);
    
// Header Functions
    /// Determines if a marker is a valid Power Tab file marker
    static bool IsValidPowerTabFileMarker(wxUint32 marker)          
        {return (marker == POWERTABFILE_MARKER);}
    
// Version Functions
    /// Determines if a file version is valid
    /// @param version File version to validate
    /// @return True if the file version is valid, false if not
    static bool IsValidFileVersion(wxWord version)                  
    {
        return ((version >= FILEVERSION_1_0) &&
            (version <= FILEVERSION_CURRENT));
    }
    /// Sets the file version (see FILEVERSION_ constants for values)
    /// @param version File version to set
    /// @return True if the file version was set, false if not
    bool SetVersion(wxWord version)                                 
    {
        wxCHECK(IsValidFileVersion(version), false);
        m_version = version;
        return (true);
    }
    /// Gets the file version
    /// @return The file version
    wxWord GetVersion() const                                       
        {return (m_version);}

// File Type Functions
    /// Determines if a file type is valid
    /// @param fileType File type to validate
    /// @return True if the file type is valid, false if not
    static bool IsValidFileType(wxByte fileType)                    
        {return (fileType < NUM_FILETYPES);}
    /// Sets the file type (see FILETYPE_ constants for values)
    /// @param fileType File type to set
    /// @return True if the file type was set, false if not
    bool SetFileType(wxByte fileType)                               
    {
        wxCHECK(IsValidFileType(fileType), false);
        m_fileType = fileType;
        return (true);
    }
    /// Gets the file type
    /// @return The file type
    wxByte GetFileType() const                                      
        {return (m_fileType);}
    /// Sets the file type to be a song
    void SetSong()                                                  
        {SetFileType(FILETYPE_SONG);}
    /// Determines if the file type is a song
    /// @return True if the file type is a song, false if not
    bool IsSong() const                                             
        {return (GetFileType() == FILETYPE_SONG);}
    /// Sets the file type to be a lesson
    void SetLesson()                                                
        {SetFileType(FILETYPE_LESSON);}
    /// Determines if the file type is a lesson
    /// @return True if the file type is a lesson, false if not
    bool IsLesson() const                                           
        {return (GetFileType() == FILETYPE_LESSON);}

// Song Functions
    /// Determines if a content type is valid
    /// @param contentType Content type to validate
    /// @return True if the content type is valid, false if not
    static bool IsValidSongContentType(wxByte contentType)          
        {return (contentType <= CONTENTTYPE_ALL);}
    /// Sets the song content type (see CONTENTTYPE_ constants for values)
    /// @param contentType Content type to set
    /// @return True if the content type was set, false if not
    bool SetSongContentType(wxByte contentType)                     
    {
        wxCHECK(IsValidSongContentType(contentType), false);
        m_songData.contentType = contentType;
        return (true);
    }
    /// Gets the song content type
    /// @return The song content type
    wxByte GetSongContentType() const                               
        {return (m_songData.contentType);}

    /// Sets the song title
    /// @param title Song title to set
    /// @return True if the song title was set, false if not
    bool SetSongTitle(const wxChar* title)                          
    {
        wxCHECK(title != NULL, false);
        m_songData.title = title;
        return (true);
    }
    /// Gets the song title
    /// @return The song title
    wxString GetSongTitle() const                                   
        {return (m_songData.title);}

    /// Sets the song artist
    /// @param artist Song artist to set
    /// @return True if the song artist was set, false if not
    bool SetSongArtist(const wxChar* artist)                        
    {
        wxCHECK(artist != NULL, false);
        m_songData.artist = artist;
        return (true);
    }
    /// Gets the song artist
    /// @return The song artist
    wxString GetSongArtist() const                                  
        {return (m_songData.artist);}

    /// Determines if a song release type is valid
    /// @param releaseType Release type to validate
    /// @return True if the release type is valid, false if not
    static bool IsValidSongReleaseType(wxByte releaseType)          
        {return (releaseType < NUM_RELEASETYPES);}
    /// Sets the song release type (see RELEASETYPE_ constants for values)
    /// @param releaseType Release type to set
    /// @return True if the song release type was set, false if not
    bool SetSongReleaseType(wxByte releaseType)                     
    {
        wxCHECK(IsValidSongReleaseType(releaseType), false);
        m_songData.releaseType = releaseType;
        return (true);
    }
    /// Gets the song release type
    /// @return The song release type
    wxByte GetSongReleaseType() const                               
        {return (m_songData.releaseType);}
    wxString GetSongReleaseTitle() const;

    /// Determines if an audio release type is valid
    /// @param audioReleaseType Audio release type to validate
    /// @return True if the album type is valid, false if not
    static bool IsValidAudioReleaseType(wxByte audioReleaseType)    
        {return (audioReleaseType < NUM_AUDIORELEASETYPES);}
    /// Sets the song audio release type (see AUDIORELEASETYPE_ constants for
    /// values)
    /// @param type Audio release type to set
    /// @return True if the song audio release type was set, false if not
    bool SetSongAudioReleaseType(wxByte type)                       
    {
        wxCHECK(IsValidAudioReleaseType(type), false);
        m_songData.audioData.type = type;
        return (true);
    }
    /// Gets the song audio release type
    /// @return The song audio release type
    wxByte GetSongAudioReleaseType() const                          
        {return (m_songData.audioData.type);}

    /// Sets the song audio release title
    /// @param title Title to set
    /// @return True if the song audio release title was set, false if not
    bool SetSongAudioReleaseTitle(const wxChar* title)              
    {
        wxCHECK(title != NULL, false);
        m_songData.audioData.title = title;
        return (true);
    }
    /// Gets the song audio release title
    /// @return The song audio release title
    wxString GetSongAudioReleaseTitle() const                       
        {return (m_songData.audioData.title);}

    /// Sets the song audio release year
    /// @param year Year to set
    void SetSongAudioReleaseYear(wxWord year)                       
        {m_songData.audioData.year = year;}
    /// Gets the song audio release year
    /// @return The audio release year
    wxWord GetSongAudioReleaseYear() const                          
        {return (m_songData.audioData.year);}

    /// Sets the song audio release live status
    /// @param set True to set the live status, false to clear it
    void SetSongAudioReleaseLive(bool set = true)                   
        {m_songData.audioData.live = ((set) ? 1 : 0);}
    /// Determines if the song audio release is live
    /// @return True if the song audio release is live, false if not
    bool IsSongAudioReleaseLive() const                             
        {return ((m_songData.audioData.live == 1) ? true : false);}

    /// Sets the song video release title
    /// @param title Title to set
    /// @return True if the video release title was set, false if not
    bool SetSongVideoReleaseTitle(const wxChar* title)              
    {
        wxCHECK(title != NULL, false);
        m_songData.videoData.title = title;
        return (true);
    }
    /// Gets the song video release title
    /// @return The song video release title
    wxString GetSongVideoReleaseTitle() const                       
        {return (m_songData.videoData.title);}

    /// Sets the song video release live status
    /// @param set True to set the live status, false to clear it
    void SetSongVideoReleaseLive(bool set = true)                   
        {m_songData.videoData.live = ((set) ? 1 : 0);}
    /// Determines if the song video release is live
    /// @return True if the song video release is live, false if not
    bool IsSongVideoReleaseLive() const                             
        {return ((m_songData.videoData.live == 1) ? true : false);}

    /// Sets the song bootleg title
    /// @param title Title to set
    /// @return True if the song bootleg title was set, false if not
    bool SetSongBootlegTitle(const wxChar* title)                   
    {
        wxCHECK(title != NULL, false);
        m_songData.bootlegData.title = title;
        return (true);
    }
    /// Gets the song bootleg title
    /// @return The song bootleg title
    wxString GetSongBootlegTitle() const                            
        {return (m_songData.bootlegData.title);}

    bool SetSongBootlegDate(const wxDateTime& date);
    wxDateTime GetSongBootlegDate() const;

    /// Determines if an author type is valid
    /// @param authorType Author type to validate
    /// @return True if the author type is valid, false if not
    static bool IsValidAuthorType(wxByte authorType)                
        {return (authorType < NUM_AUTHORTYPES);}
    /// Sets the song author type (see AUTHORTYPE_ constants for values)
    /// @param authorType Author type to set
    /// @return True if the song author type was set, false if not
    bool SetSongAuthorType(wxByte authorType)                       
    {
        wxCHECK(IsValidAuthorType(authorType), false);
        m_songData.authorType = authorType;
        return (true);
    }
    /// Gets the song author type
    /// @return The song author type
    wxByte GetSongAuthorType() const                                
        {return (m_songData.authorType);}

    /// Sets the song composer
    /// @param composer Composer to set
    /// @return True if the song composer was set, false if not
    bool SetSongComposer(const wxChar* composer)                    
    {
        wxCHECK(composer != NULL, false);
        m_songData.authorData.composer = composer;
        return (true);
    }
    /// Gets the song composer
    /// @return The song composer
    wxString GetSongComposer() const                                
        {return (m_songData.authorData.composer);}
    
    /// Sets the song lyricist
    /// @param lyricist Lyricist to set
    /// @return True if the song lyricist was set, false if not
    bool SetSongLyricist(const wxChar* lyricist)                    
    {
        wxCHECK(lyricist != NULL, false);
        m_songData.authorData.lyricist = lyricist;
        return (true);
    }
    /// Gets the song lyricist
    /// @return The song lyricist
    wxString GetSongLyricist() const                                
        {return (m_songData.authorData.lyricist);}

    /// Sets the song arranger
    /// @param arranger Arranger to set
    /// @return True if the song arranger was set, false if not
    bool SetSongArranger(const wxChar* arranger)                    
    {
        wxCHECK(arranger != NULL, false);
        m_songData.arranger = arranger;
        return (true);
    }
    /// Gets the song arranger
    /// @return The song arranger
    wxString GetSongArranger() const                                
        {return (m_songData.arranger);}
    
    /// Sets the song guitar score transcriber
    /// @param transcriber Transcriber to set
    /// @return True if the song guitar score transcriber was set, false if not
    bool SetSongGuitarScoreTranscriber(const wxChar* transcriber)   
    {
        wxCHECK(transcriber != NULL, false);
        m_songData.guitarScoreTranscriber = transcriber;
        return (true);
    }
    /// Gets the song guitar score transcriber
    /// @return The song guitar score transcriber
    wxString GetSongGuitarScoreTranscriber() const                  
        {return (m_songData.guitarScoreTranscriber);}

    /// Sets the song bass score transcriber
    /// @param transcriber Transcriber to set
    /// @return True if the song bass score transcriber was set, false if not
    bool SetSongBassScoreTranscriber(const wxChar* transcriber)     
    {
        wxCHECK(transcriber != NULL, false);
        m_songData.bassScoreTranscriber = transcriber;
        return (true);
    }
    /// Gets the song bass score transcriber
    /// @return The song bass score transcriber
    wxString GetSongBassScoreTranscriber() const                    
        {return (m_songData.bassScoreTranscriber);}

    /// Sets the song copyright
    /// @param copyright Copyright to set
    /// @return True if the song copyright was set, false if not
    bool SetSongCopyright(const wxChar* copyright)                  
    {
        wxCHECK(copyright != NULL, false);
        m_songData.copyright = copyright;
        return (true);
    }
    /// Gets the song copyright
    /// @return The song copyright
    wxString GetSongCopyright() const                               
        {return (m_songData.copyright);}

    /// Sets the song lyrics
    /// @param lyrics Lyrics to set
    /// @return True if the lyrics were set, false if not
    bool SetSongLyrics(const wxChar* lyrics)                        
    {
        wxCHECK(lyrics != NULL, false);
        m_songData.lyrics = lyrics;
        return (true);
    }
    /// Gets the song lyrics
    /// @return The song lyrics
    wxString GetSongLyrics() const                                  
        {return (m_songData.lyrics);}

    /// Sets the song guitar score notes
    /// @param notes Notes to set
    /// @return True if the song guitar score notes were set, false if not
    bool SetSongGuitarScoreNotes(const wxChar* notes)               
    {
        wxCHECK(notes != NULL, false);
        m_songData.guitarScoreNotes = notes;
        return (true);
    }
    /// Gets the song guitar score notes
    /// @return The song guitar score notes
    wxString GetSongGuitarScoreNotes() const                        
        {return (m_songData.guitarScoreNotes);}

    /// Sets the song bass score notes
    /// @param notes Notes to set
    /// @return True if the song bass score notes were set, false if not
    bool SetSongBassScoreNotes(const wxChar* notes)                 
    {
        wxCHECK(notes != NULL, false);
        m_songData.bassScoreNotes = notes;
        return (true);
    }
    /// Gets the song bass score notes
    /// @return The song bass score notes
    wxString GetSongBassScoreNotes() const                          
        {return (m_songData.bassScoreNotes);}
    
// Lesson Functions
    /// Sets the lesson title
    /// @param title Title to set
    /// @return True if the title was set, false if not
    bool SetLessonTitle(const wxChar* title)                        
    {
        wxCHECK(title != NULL, false);
        m_lessonData.title = title;
        return (true);
    }
    /// Gets the lesson title
    /// @return The lesson title
    wxString GetLessonTitle() const                                 
        {return (m_lessonData.title);}

    /// Sets the lesson subtitle
    /// @param subtitle Subtitle to set
    /// @return True if the subtitle was set, false if not
    bool SetLessonSubtitle(const wxChar* subtitle)                  
    {
        wxCHECK(subtitle != NULL, false);
        m_lessonData.subtitle = subtitle;
        return (true);
    }
    /// Gets the lesson subtitle
    /// @return The lesson subtitle
    wxString GetLessonSubtitle() const                              
        {return (m_lessonData.subtitle);}

    /// Determines if a music musicStyle is valid
    /// @param musicStyle Music musicStyle to validate
    /// @return True if the music musicStyle is valid, false if not
    static bool IsValidMusicStyle(wxWord musicStyle)                
        {return (musicStyle < NUM_MUSICSTYLES);}
    /// Sets the lesson music musicStyle
    /// @param musicStyle Music musicStyle to set
    /// @return True if the music musicStyle was set, false if not
    bool SetLessonMusicStyle(wxWord musicStyle)                     
    {
        wxCHECK(IsValidMusicStyle(musicStyle), false);
        m_lessonData.musicStyle = musicStyle;
        return (true);
    }
    /// Gets the lesson music musicStyle
    /// @return The lesson music musicStyle
    wxWord GetLessonMusicStyle() const                              
        {return (m_lessonData.musicStyle);}

    /// Determines if a lesson level is valid
    /// @param level Lesson level to validate
    /// @return True if the lesson level is valid, false if not
    static bool IsValidLessonLevel(wxByte level)                    
        {return (level < NUM_LESSONLEVELS);}
    /// Sets the lesson level
    /// @param level Lesson level to set
    /// @return True if the lesson level was set, false if not
    bool SetLessonLevel(wxByte level)                               
    {
        wxCHECK(IsValidLessonLevel(level), false);
        m_lessonData.level = level;
        return (true);
    }
    /// Gets the lesson level
    /// @return The lesson level
    wxByte GetLessonLevel() const                                   
        {return (m_lessonData.level);}

    /// Sets the lesson author
    /// @param author Lesson author to set
    /// @return True if the lesson author was set, false if not
    bool SetLessonAuthor(const wxChar* author)                      
    {
        wxCHECK(author != NULL, false);
        m_lessonData.author = author;
        return (true);
    }
    /// Gets the lesson author
    /// @return The lesson author
    wxString GetLessonAuthor() const                                
        {return (m_lessonData.author);}
    
    /// Sets the lesson notes
    /// @param notes Lesson notes to set
    /// @return True if the lesson notes were set, false if not
    bool SetLessonNotes(const wxChar* notes)                        
    {
        wxCHECK(notes != NULL, false);
        m_lessonData.notes = notes;
        return (true);
    }
    /// Gets the lesson notes
    /// @return The lesson notes
    wxString GetLessonNotes() const                                 
        {return (m_lessonData.notes);}
    
    /// Sets the lesson copyright
    /// @param copyright Lesson copyright to set
    /// @return True if the lesson copyright was set, false if not
    bool SetLessonCopyright(const wxChar* copyright)                
    {
        wxCHECK(copyright != NULL, false);
        m_lessonData.copyright = copyright;
        return (true);
    }
    /// Gets the lesson copyright
    /// @return The lesson copyright
    wxString GetLessonCopyright() const                             
        {return (m_lessonData.copyright);}

// Operations
    void LoadDefaults();
};

#endif
