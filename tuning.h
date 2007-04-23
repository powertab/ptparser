/////////////////////////////////////////////////////////////////////////////
// Name:            tuning.h
// Purpose:         Stores a tuning used by a stringed instrument
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 14, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __TUNING_H__
#define __TUNING_H__

/// Stores a tuning used by a stringed instrument                            
class Tuning : public PowerTabObject
{
friend class TuningTestSuite;

public:
    static const wxChar*        DEFAULT_NAME;                       ///< Default value for the name member variable
    static const wxByte         DEFAULT_DATA;                       ///< Default value for the data member variable 
    
    static const wxInt8         MIN_MUSIC_NOTATION_OFFSET;          ///< Minimum allowed value for the music notation offset
    static const wxInt8         MAX_MUSIC_NOTATION_OFFSET;          ///< Maximum allowed value for the music notation offset
    
    static const wxUint32       MIN_STRING_COUNT;                   ///< Minimum number of strings in a tuning
    static const wxUint32       MAX_STRING_COUNT;                   ///< Maximum number of strings in a tuning
    
    enum flags
    {
        sharpsMask                      = (wxByte)0x01,             ///< Mask used to retrieve the sharp setting (display tuning name using sharps or flats)
        musicNotationOffsetMask         = (wxByte)0xfe,             ///< Mask used to retrieve the music notation offset (sign + value)
        musicNotationOffsetSignMask     = (wxByte)0x80,             ///< Mask used to retrieve the music notation offset sign (+/-)
        musicNotationOffsetValueMask    = (wxByte)0x7e,             ///< Mask used to retrieve the music notation offset value
        notUsed                         = (wxByte)0xff              ///< Marker that signifies an unused string
    };
    
protected:
    wxString    m_name;                             ///< Name (or description) of the tuning
    wxByte      m_data;                             ///< bit 7 = Music notation offset sign, bits 6 to 1 = Music notation offset value, bit 0 = display sharps or flats
    wxByteArray m_noteArray;                        ///< Array of bytes representing the MIDI notes of the tuning, ordered from high string to low string
   
public:
    // Constructor/Destructor
    Tuning();
    Tuning(const wxChar* name, wxInt8 musicNotationOffset, bool sharps, wxByte note1, wxByte note2, wxByte note3, wxByte note4 = notUsed, wxByte note5 = notUsed, wxByte note6 = notUsed, wxByte note7 = notUsed);
    Tuning(const Tuning& tuning);
    ~Tuning();

    // Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                         
        {return (new Tuning(*this));}
    
    // Operators
    const Tuning& operator=(const Tuning& tuning);
    bool operator==(const Tuning& tuning) const;
    bool operator!=(const Tuning& tuning) const;

    // MFC Class Functions
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const                            
        {return (wxT("CTuning"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const                            
        {return ((wxWord)1);}
    
    // Serialize Functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

public:
    // Tuning Functions
    bool SetTuning(const wxChar* name, wxInt8 musicNotationOffset, bool sharps, wxByte note1, wxByte note2, wxByte note3, wxByte note4 = notUsed, wxByte note5 = notUsed, wxByte note6 = notUsed, wxByte note7 = notUsed);
    bool SetTuningFromString(const wxChar* string);
    bool IsSameTuning(const Tuning& tuning) const;
    bool IsSameTuning(wxByte note1, wxByte note2, wxByte note3, wxByte note4 = notUsed, wxByte note5 = notUsed, wxByte note6 = notUsed, wxByte note7 = notUsed) const;
    
    // Name Functions
    /// Sets the tuning name (i.e. "Open G")
    /// @param name Name to set
    /// @return True if the name was successfully set, false if not
    bool SetName(const wxChar* name)                        
        {wxCHECK(name != NULL, false); m_name = name; return (true);}
    /// Gets the tuning name (i.e. "Open G")
    /// @return The tuning name
    wxString GetName() const                                
        {return (m_name);}

    // Music Notation Offset Functions
    /// Determines if a music notation offset value is valid
    /// @param musicNotationOffset Music notation offset to validate
    /// @return True if the music notation offset is valid, false if not
    static bool IsValidMusicNotationOffset(wxInt8 musicNotationOffset)  
        {return ((musicNotationOffset >= MIN_MUSIC_NOTATION_OFFSET) && ((musicNotationOffset <= MAX_MUSIC_NOTATION_OFFSET)));}
    bool SetMusicNotationOffset(wxInt8 musicNotationOffset);
    wxInt8 GetMusicNotationOffset() const;
    
    // Sharps Functions
    void SetSharps(bool set = true);
    /// Determines if the tuning notes are displayed using sharps, or flats
    /// @return True if the tuning notes are displayed using sharps, false if flats
    bool UsesSharps() const                                 
        {return ((m_data & sharpsMask) == sharpsMask);}
        
    // String Functions
    /// Determines if a string count is valid
    /// @param stringCount String count to validate
    /// @return True if the string count is valid, false if not
    static bool IsValidStringCount(size_t stringCount)      
        {return ((stringCount >= MIN_STRING_COUNT) && (stringCount <= MAX_STRING_COUNT));}
    /// Determines if a string is valid
    /// @param string String to validate
    /// @return True if the string is valid, false if not
    bool IsValidString(wxUint32 string) const               
        {return ((string >= 0) && (string < GetStringCount()));}
    /// Gets the number of strings used by the tuning
    /// @return The number of strings used by the tuning
    size_t GetStringCount() const                           
        {return (m_noteArray.GetCount());}

    // Note Functions
    bool SetNote(wxUint32 string, wxByte note);
    wxByte GetNote(wxUint32 string, bool includeMusicNotationOffset = false) const;
    wxString GetNoteText(wxUint32 string) const;
    bool IsOpenStringNote(wxByte note) const;
    wxSize GetNoteRange(wxByte capo) const;
protected:
    bool AddTuningNotes(wxByte note1, wxByte note2, wxByte note3, wxByte note4, wxByte note5, wxByte note6, wxByte note7);
    void DeleteNoteArrayContents();
    
public:    
    // Operations
    /// Determines if a tuning is valid (has a valid number of strings)
    /// @return True if the tuning is valid, false if not
    bool IsValid() const                                    
        {return (IsValidStringCount(GetStringCount()));}
    wxString GetSpelling() const;
};

WX_DEFINE_POWERTABARRAY(Tuning*, TuningArray);

#endif
