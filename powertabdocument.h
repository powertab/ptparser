/////////////////////////////////////////////////////////////////////////////
// Name:            powertabdocument.h
// Purpose:         Loads and saves Power Tab files (.ptb)
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 3, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __POWERTABDOC_H__
#define __POWERTABDOC_H__

#include "powertabfileheader.h"
#include "score.h"
#include "fontsetting.h"

// compatibility classes
#include "oldrehearsalsign.h"
#include "oldtimesignature.h"

#define NUM_DOCUMENT_FONT_SETTINGS                  3                           ///< Number of document wide font settings
#define DOCUMENT_FONT_SETTING_CHORD_NAME            0                           ///< Font used to draw the chord name (chord text)
#define DOCUMENT_FONT_SETTING_TABLATURE_NUMBERS     1                           ///< Font used to draw the fret numbers on the tablature staff
#define DOCUMENT_FONT_LYRICS                        2                           ///< Unused

/// Loads and saves Power Tab files (.ptb)
class PowerTabDocument : public wxDocument
{
friend class PowerTabDocumentTestSuite;

    DECLARE_DYNAMIC_CLASS(PowerTabDocument)

// Constants
public:   
    // Default Constants
    static const wxInt32    DEFAULT_TABLATURE_STAFF_LINE_SPACING;               ///< Default value for the tablature staff line spacing member variable
    static const wxUint32   DEFAULT_FADE_IN;                                    ///< Default value for the fade in member variable    
    static const wxUint32   DEFAULT_FADE_OUT;                                   ///< Default value for the fade out member variable
    
    // Tablature Staff Line Spacing Constants
    static const wxInt32    MIN_TABLATURE_STAFF_LINE_SPACING;                   ///< Minimum allowed value for the tablature staff line spacing member variable
    static const wxInt32    MAX_TABLATURE_STAFF_LINE_SPACING;                   ///< Maximum allowed value for the tablature staff line spacing member variable

    // Score Constants
    static const wxByte     NUM_SCORES;                                         ///< Number of scores per document (guitar + bass)
    static const wxByte     GUITAR_SCORE;                                       ///< Index of the guitar score
    static const wxByte     BASS_SCORE;                                         ///< Index of the bass score
    
    // Guitar Constants
    static const wxByte     MAX_GUITARS;                                        ///< Maximum number of guitars allowed per document
    
// Member Variables
protected:
    PowerTabFileHeader  m_header;                                               ///< The one and only header (contains file information)
    ScoreArray          m_scoreArray;                                           ///< List of scores (zeroth element = guitar score, first element = bass score)
    
    FontSetting         m_fontSettingArray[NUM_DOCUMENT_FONT_SETTINGS];         ///< List of global font settings
    wxInt32             m_tablatureStaffLineSpacing;                            ///< Amount of space used between lines on the tablature staff
    wxUint32            m_fadeIn;                                               ///< Amount of fade in at the start of the song (in MIDI units - see generalmidi.h)
    wxUint32            m_fadeOut;                                              ///< Amount of fade out at the end of the song (in MIDI units - see generalmidi.h)

// Constructor/Destructor
public:
    PowerTabDocument();
    ~PowerTabDocument();
   
// Save Functions
    wxOutputStream& SaveObject(wxOutputStream& stream);
    
// Load Functions
    wxInputStream& LoadObject(wxInputStream& stream);
    bool Load(const wxChar* fileName);
    bool Load(PowerTabInputStream& stream);
    bool DeserializeFormat1_7(PowerTabInputStream& stream);
    bool DeserializeFormat1_5(PowerTabInputStream& stream);
    bool DeserializeFormat1_0(PowerTabInputStream& stream, wxWord version);
    
// Overrides
    virtual bool DeleteContents();

// Header Functions
    /// Gets a reference to the header
    /// @return A reference to the header
    PowerTabFileHeader& GetHeaderRef()      
        {return (m_header);}
    /// Gets a constant reference to the header
    /// @return A constant reference to the header
    const PowerTabFileHeader& GetHeaderConstRef() const
        {return (m_header);}
        
// Score Functions
    /// Gets a pointer to the guitar score
    /// @return A pointer to the guitar score
    Score* GetGuitarScore() const           
        {wxCHECK(!m_scoreArray.IsEmpty(), NULL); return (m_scoreArray[0]);}
    /// Gets a pointer to the bass score
    /// @return A pointer to the bass score
    Score* GetBassScore() const
        {wxCHECK(m_scoreArray.GetCount() >= 2, NULL); return (m_scoreArray[1]);}
    bool CanMergeGuitarScore(PowerTabDocument& document) const;
    bool MergeGuitarScore(PowerTabDocument& document);
    bool CanMergeBassScore(PowerTabDocument& document) const;    
    bool MergeBassScore(PowerTabDocument& document);
    void DeleteScoreArrayContents();

// Font Setting Functions
    /// Sets the font setting used by chord names
    /// @param fontSetting Font setting to set
    void SetChordNameFontSetting(const FontSetting& fontSetting)
        {m_fontSettingArray[DOCUMENT_FONT_SETTING_CHORD_NAME] = fontSetting;}
    /// Gets the font setting used by chord names
    /// @return The font setting used by chord names
    FontSetting GetChordNameFontSetting() const
        {return (m_fontSettingArray[DOCUMENT_FONT_SETTING_CHORD_NAME]);}
    /// Gets a reference to the font setting used by chord names
    /// @return A reference to the font setting used by chord names
    FontSetting& GetChordNameFontSettingRef()
        {return (m_fontSettingArray[DOCUMENT_FONT_SETTING_CHORD_NAME]);}
    /// Gets a constant reference to the font setting used by chord names
    /// @return A constant reference to the font setting used by chord names
    const FontSetting& GetChordNameFontSettingConstRef() const
        {return (m_fontSettingArray[DOCUMENT_FONT_SETTING_CHORD_NAME]);}

    /// Sets the font setting used by tablature numbers on the tablature staff
    /// @param fontSetting Font setting to set
    void SetTablatureNumbersFontSetting(const FontSetting& fontSetting)
        {m_fontSettingArray[DOCUMENT_FONT_SETTING_TABLATURE_NUMBERS] = fontSetting;}
    /// Gets the font setting used by tablature numbers on the tablature staff
    /// @return The font setting used by tablature numbers on the tablature
    /// staff
    FontSetting GetTablatureNumbersFontSetting() const
        {return (m_fontSettingArray[DOCUMENT_FONT_SETTING_TABLATURE_NUMBERS]);}
    /// Gets a reference to the font setting used by tablature numbers on the
    /// tablature staff
    /// @return A reference to the font setting used by tablature numbers on the
    /// tablature staff
    FontSetting& GetTablatureNumbersFontSettingRef()
        {return (m_fontSettingArray[DOCUMENT_FONT_SETTING_TABLATURE_NUMBERS]);}
    /// Gets a constant reference to the font setting used by tablature numbers
    /// on the tablature staff
    /// @return A constant reference to the font setting used by tablature
    /// numbers on the tablature staff
    const FontSetting& GetTablatureNumbersFontSettingConstRef() const
        {return (m_fontSettingArray[DOCUMENT_FONT_SETTING_TABLATURE_NUMBERS]);}
        
// Tablature Staff Line Spacing Functions
    /// Determines if a tablature staff line spacing value is valid
    /// @param tablatureStaffLineSpacing Tablature staff line spacing value to
    /// validate
    /// @return True if the tablature staff line spacing is valid, false if not
    static bool IsValidTablatureStaffLineSpacing(
        wxInt32 tablatureStaffLineSpacing)
    {
        return ((tablatureStaffLineSpacing >= MIN_TABLATURE_STAFF_LINE_SPACING) &&
            (tablatureStaffLineSpacing <= MAX_TABLATURE_STAFF_LINE_SPACING));
    }
    /// Sets the amount of spacing between tablature staff lines
    /// @param tablatureStaffLineSpacing Amount of spacing to set
    bool SetTablatureStaffLineSpacing(wxUint32 tablatureStaffLineSpacing)
    {
        wxCHECK(IsValidTablatureStaffLineSpacing(tablatureStaffLineSpacing), false);
        m_tablatureStaffLineSpacing = tablatureStaffLineSpacing;
        return (true);
    }
    /// Gets the amount of spacing between tablature staff lines
    /// @return The amount of spacing between tablature staff lines
    wxInt32 GetTablatureStaffLineSpacing() const
        {return (m_tablatureStaffLineSpacing);}
    
// Fade In Functions
    /// Sets the amount of fade in at the start of the song or lesson
    /// @param fadeIn Amount of fade in to set, in MIDI units
    /// (see generalmidi.h)
    void SetFadeIn(wxUint32 fadeIn)         
        {m_fadeIn = fadeIn;}
    /// Gets the amount of fade in at the start of the song or lesson
    /// @return The amount of fade in at the start of the song or lesson, in
    /// MIDI units (see generalmidi.h)
    wxUint32 GetFadeIn() const
        {return (m_fadeIn);}
    
// Fade Out Functions
    /// Sets the amount of fade out at the end of the song or lesson
    /// @param fadeOut Amount of fade out to set, in MIDI units
    /// (see generalmidi.h)
    void SetFadeOut(wxUint32 fadeOut)       
        {m_fadeOut = fadeOut;}
    /// Gets the amount of fade out at the end of the song or lesson
    /// @return The amount of fade out at the end of the song or lesson, in MIDI
    /// units (see generalmidi.h)
    wxUint32 GetFadeOut() const             
        {return (m_fadeOut);}
    
// Error Functions
    void DisplaySerializationError(const wxString& fileName, off_t offset,
        const wxString& errorMessage);
    void DisplayDeserializationError(const wxString& fileName, off_t offset,
        const wxString& errorMessage);
};

#endif
