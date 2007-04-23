/////////////////////////////////////////////////////////////////////////////
// Name:            guitar.h
// Purpose:         Stores information about a guitar (tuning, effects, etc.)
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 8, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __GUITAR_H__
#define __GUITAR_H__

#include "powertabobject.h"
#include "tuning.h"

/// Stores information about a guitar (tuning, effects, etc.)
class Guitar : public PowerTabObject
{
friend class GuitarTestSuite;

// Constants
public:
    // Default constants
    static const wxByte         DEFAULT_NUMBER;         ///< Default value for the number member variable
    static const wxChar*        DEFAULT_DESCRIPTION;    ///< Default value for the description member variable
    static const wxByte         DEFAULT_PRESET;         ///< Default value for the preset member variable
    static const wxByte         DEFAULT_INITIAL_VOLUME; ///< Default value for the intial volume member variable
    static const wxByte         DEFAULT_PAN;            ///< Default value for the pan member variable
    static const wxByte         DEFAULT_REVERB;         ///< Default value for the reverb member variable
    static const wxByte         DEFAULT_CHORUS;         ///< Default value for the chorus member variable
    static const wxByte         DEFAULT_TREMOLO;        ///< Default value for the tremolo member variable
    static const wxByte         DEFAULT_PHASER;         ///< Default value for the phaser member variable
    static const wxByte         DEFAULT_CAPO;           ///< Default value for the capo member variable

    static const wxByte         MIN_PRESET;             ///< Minimum allowed value for the preset
    static const wxByte         MAX_PRESET;             ///< Maximum allowed value for the preset
    
    static const wxByte         MIN_INITIAL_VOLUME;     ///< Minimum allowed value for the initial volume
    static const wxByte         MAX_INITIAL_VOLUME;     ///< Maximum allowed value for the initial volume
    
    static const wxByte         MIN_PAN;                ///< Minimum allowed value for the pan level
    static const wxByte         MAX_PAN;                ///< Maximum allowed value for the pan level
    static const wxByte         PAN_HARD_LEFT;          ///< Value for the hard left pan setting
    static const wxByte         PAN_CENTER;             ///< Value for the center/middle pan setting
    static const wxByte         PAN_HARD_RIGHT;         ///< Value for the hard right pan setting
    
    static const wxByte         MIN_REVERB;             ///< Minimum allowed value for the reverb level
    static const wxByte         MAX_REVERB;             ///< Maximum allowed value for the reverb level

    static const wxByte         MIN_CHORUS;             ///< Minimum allowed value for the chorus level
    static const wxByte         MAX_CHORUS;             ///< Maximum allowed value for the chorus level
   
    static const wxByte         MIN_TREMOLO;            ///< Minimum allowed value for the tremolo level
    static const wxByte         MAX_TREMOLO;            ///< Maximum allowed value for the tremolo level
    
    static const wxByte         MIN_PHASER;             ///< Minimum allowed value for the phaser level
    static const wxByte         MAX_PHASER;             ///< Maximum allowed value for the phaser level

    static const wxByte         MIN_CAPO;               ///< Minimum allowed value for the capo number
    static const wxByte         MAX_CAPO;               ///< Maximum allowed value for the capo number
            
protected:
    wxByte      m_number;                   ///< Unique number used to identify the guitar (zero-based)
    wxString    m_description;              ///< Description of the guitar
    wxByte      m_preset;                   ///< MIDI preset to use during playback
    wxByte      m_initialVolume;            ///< Initial MIDI channel volume level for the guitar
    wxByte      m_pan;                      ///< Channel pan setting for the guitar
    wxByte      m_reverb;                   ///< Amount of reverb effect used by the guitar
    wxByte      m_chorus;                   ///< Amount of chorus effect used by the guitar
    wxByte      m_tremolo;                  ///< Amount of tremolo effect used by the guitar
    wxByte      m_phaser;                   ///< Amount of phaser effect used by the guitar
    wxByte      m_capo;                     ///< Capo placement (0 - no capo)
    Tuning      m_tuning;                   ///< Guitar tuning

public:
    // Constructor/Destructor
    Guitar();
    Guitar(wxByte number, const wxChar* description = DEFAULT_DESCRIPTION, wxByte preset = DEFAULT_PRESET, wxByte initialVolume = DEFAULT_INITIAL_VOLUME, wxByte pan = DEFAULT_PAN, wxByte reverb = DEFAULT_REVERB, wxByte chorus = DEFAULT_CHORUS, wxByte tremolo = DEFAULT_TREMOLO, wxByte phaser = DEFAULT_PHASER, wxByte capo = DEFAULT_CAPO);
    Guitar(const Guitar& guitar);
    ~Guitar();

    // Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                     
        {return (new Guitar(*this));}
    
    // Operators
    const Guitar& operator=(const Guitar& guitar);
    bool operator==(const Guitar& guitar) const;
    bool operator!=(const Guitar& guitar) const;
    
    // Serialization Functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

public:
    // MFC Class Functions
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const                        
        {return (wxT("CGuitar"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const                        
        {return ((wxWord)1);}
        
    // Number Functions
    /// Sets the number (id) used by the guitar
    /// @param number Number to set (zero based)
    void SetNumber(wxByte number)                           
        {m_number = number;}
    /// Gets the number (id) used by the guitar
    /// @return The number used by the guitar
    wxByte GetNumber() const                                
        {return (m_number);}

    // Description Functions
    /// Sets the description for the guitar
    /// @param description Description to set
    /// @return True if the description was set, false if not
    bool SetDescription(const wxChar* description)          
        {wxCHECK(description != NULL, false); m_description = description; return (true);}
    /// Gets the description for the guitar (i.e. Acoustic w/Chorus)
    /// @return The description for the guitar
    wxString GetDescription() const                         
        {return (m_description);}

    // Preset Functions
    static bool IsValidPreset(wxByte preset)                
        {return ((preset >= MIN_PRESET) && (preset <= MAX_PRESET));}
    /// Sets the preset (MIDI) used by the guitar
    /// @param preset Preset to set
    /// @return True if the preset was set, false if not
    bool SetPreset(wxByte preset)                           
        {wxCHECK(IsValidPreset(preset), false); m_preset = preset; return (true);}
    /// Gets the preset (MIDI) used by the guitar
    /// @return The preset used by the guitar
    wxByte GetPreset() const                                
        {return (m_preset);}

    // Initial Volume Functions
    static bool IsValidInitialVolume(wxByte initialVolume)  
        {return ((initialVolume >= MIN_INITIAL_VOLUME) && (initialVolume <= MAX_INITIAL_VOLUME));}
    /// Sets the initial volume level of the guitar
    /// @param initialVolume Initial volume to set
    /// @return True if the volume was set, false if not
    bool SetInitialVolume(wxByte initialVolume)             
        {wxCHECK(IsValidInitialVolume(initialVolume), false); m_initialVolume = initialVolume; return (true);}
    /// Gets the initial volume level of the guitar
    /// @return The initial volume level of the guitar
    wxByte GetInitialVolume() const                         
        {return (m_initialVolume);}

    // Pan Functions
    /// Determines if a pan level is valid
    /// @param pan Pan level to validate
    /// @return True if the pan level is valid, false if not
    static bool IsValidPan(wxByte pan)                      
        {return ((pan >= MIN_PAN) && (pan <= MAX_PAN));}
    /// Sets the pan level for the guitar
    /// @param pan Pan level to set (0 - hard left, 64 - center, 127 - hard right)
    /// @return True if the pan level was set, false if not
    bool SetPan(wxByte pan)                                 
        {wxCHECK(IsValidPan(pan), false); m_pan = pan; return (true);}
    /// Gets the pan level for the guitar
    /// @return The pan level for the guitar
    wxByte GetPan() const                                   
        {return (m_pan);}

    // Reverb Functions
    /// Determines if a reverb level is valid
    /// @param reverb Reverb level to validate
    /// @return True if the reverb level is valid, false if not
    static bool IsValidReverb(wxByte reverb)                
        {return ((reverb >= MIN_REVERB) && (reverb <= MAX_REVERB));}
    /// Sets the reverb level for the guitar
    /// @param reverb Reverb level to set (0 - none, 127 - max)
    /// @return True if the reverb level was set, false if not
    bool SetReverb(wxByte reverb)                           
        {wxCHECK(IsValidReverb(reverb), false); m_reverb = reverb; return (true);}
    /// Gets the reverb level for the guitar
    /// @return The reverb level for the guitar
    wxByte GetReverb() const                                
        {return (m_reverb);}

    // Chorus Functions
    /// Determines if a chorus level is valid
    /// @param chorus Chorus level to validate
    /// @return True if the chorus level is valid, false if not
    static bool IsValidChorus(wxByte chorus)                
        {return ((chorus >= MIN_CHORUS) && (chorus <= MAX_CHORUS));}
    /// Sets the chorus level for the guitar (0 - none, 127 - maximum chorus)
    /// @param chorus Chorus level to set
    /// @return True if the chorus level was set, false if not
    bool SetChorus(wxByte chorus)                           
        {wxCHECK(IsValidChorus(chorus), false); m_chorus = chorus; return (true);}
    /// Gets the chorus level for the guitar
    /// @return The chorus level for the guitar
    wxByte GetChorus() const                                
        {return (m_chorus);}

    // Tremolo Functions
    /// Determines if a tremolo level is valid
    /// @param tremolo Tremolo level to validate
    /// @return True if the tremolo level is valid, false if not
    static bool IsValidTremolo(wxByte tremolo)              
        {return ((tremolo >= MIN_TREMOLO) && (tremolo <= MAX_TREMOLO));}
    /// Sets the tremolo level for the guitar (0 - none, 127 - maximum tremolo)
    /// @param tremolo Tremolo level to set
    /// @return True if the tremolo level was set, false is not
    bool SetTremolo(wxByte tremolo)                         
        {wxCHECK(IsValidTremolo(tremolo), false); m_tremolo = tremolo; return (true);}
    /// Gets the tremolo level for the guitar
    /// @return The tremolo level for the guitar
    wxByte GetTremolo() const                               
        {return (m_tremolo);}

    // Phaser Functions
    /// Determines if a phaser level is valid
    /// @param phaser Phaser level to validate
    /// @return True if the phaser level is valid, false if not
    static bool IsValidPhaser(wxByte phaser)                
        {return ((phaser >= MIN_PHASER) && (phaser <= MAX_PHASER));}
    /// Sets the phaser level for the guitar (0 - none, 127 - maximum phaser)
    /// @param phaser Phaser level to set
    /// @return True if the phaser level was set, false is not
    bool SetPhaser(wxByte phaser)                           
        {wxCHECK(IsValidPhaser(phaser), false); m_phaser = phaser; return (true);}
    /// Gets the phaser level for the guitar
    /// @return The phaser level for the guitar
    wxByte GetPhaser() const                                
        {return (m_phaser);}

    // Capo Functions
    /// Determines if a capo value is valid
    /// @param capo Capo value to validate
    /// @return True if the capo value is valid, false if not
    static bool IsValidCapo(wxByte capo)                    
        {return ((capo >= MIN_CAPO) && (capo <= MAX_CAPO));}
    /// Sets the capo used by the guitar (0 - no capo, all other values represent the fret where the capo is placed)
    /// @param capo Capo value to set
    /// @return True if the capo was set, false if not
    bool SetCapo(wxByte capo)                               
        {wxCHECK(IsValidCapo(capo), false); m_capo = capo; return (true);}
    /// Gets the capo setting used by the guitar
    /// @return The capo used by the guitar
    wxByte GetCapo() const                                  
        {return (m_capo);}
    /// Determines if the guitar uses a capo
    /// @return True if the guitar uses a capo, false if not
    bool UsesCapo() const                                   
        {return (GetCapo() != MIN_CAPO);}

    // Tuning Functions
    /// Sets the tuning used by the guitar
    /// @param tuning Tuning to set
    /// @return True if the tuning was set, false if not
    bool SetTuning(const Tuning& tuning)                    
        {wxCHECK(tuning.IsValid(), false); m_tuning = tuning; return (true);}
    /// Gets the tuning used by the guitar
    /// @return The tuning used by the guitar
    Tuning GetTuning() const                                
        {return (m_tuning);}
    /// Gets a reference to the Tuning object used by the guitar
    /// @return A reference to the Tuning object used by the guitar
    Tuning& GetTuningRef()                                  
        {return (m_tuning);}
    /// Gets a constant reference to the Tuning object used by the guitar
    /// @return A constant reference to the Tuning object used by the guitar
    const Tuning& GetTuningConstRef() const                 
        {return (m_tuning);}
    /// Gets a pointer to the Tuning object used by the guitar
    /// @return A pointer to the Tuning object used by the guitar
    Tuning* GetTuningPtr()                                  
        {return (&m_tuning);}
    /// Gets the number of strings on the guitar (determined by the tuning)
    /// @return The number of strings on the guitar
    int GetStringCount() const                              
        {return (m_tuning.GetStringCount());}
    /// Gets the tuning spelling used by the guitar (i.e. E A D G B E)
    /// @return The tuning spelling used by the guitar
    wxString GetTuningSpelling() const                      
        {return (m_tuning.GetSpelling());}

    // Operations
    wxString GetLegendText() const;
};

// Array declarations
WX_DEFINE_POWERTABARRAY(Guitar*, GuitarArray);

#endif
