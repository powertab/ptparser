/////////////////////////////////////////////////////////////////////////////
// Name:            note.h
// Purpose:         Stores and renders a note
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 17, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __NOTE_H__
#define __NOTE_H__

#define MAX_NOTE_COMPLEX_SYMBOLS     3  ///< Maximum allowed number of complex symbols per note object
                                        // Note: needs to be #define so array works properly

#include "chordname.h"      // Needed for IsValidKeyAndVariation (Artificial Harmonics)

/// Stores and renders a note
class Note : public PowerTabObject
{
friend class NoteTestSuite;

// Constants
public:
    // Default Constants
    static const wxByte DEFAULT_STRING_DATA;            ///< Default value for the string data member variable
    static const wxWord DEFAULT_SIMPLE_DATA;            ///< Default value for the simple data member variable
    
    // String Constants
    static const wxByte MIN_STRING;                     ///< Minimum allowed string
    static const wxByte MAX_STRING;                     ///< Maximum allowed string
    
    // Fret Number Constants
    static const wxByte MIN_FRET_NUMBER;                ///< Minimum allowed fret number
    static const wxByte MAX_FRET_NUMBER;                ///< Maximum allowed fret number
    
    // Bend Constants
    static const wxByte MAX_BEND_PITCH;                 ///< Maximum allowed pitch for a bend, in quarter steps
    static const wxByte MAX_BEND_DURATION;              ///< Maximum allowed value for the bend duration
    
    enum flags
    {
        stringMask          = (wxByte)0xe0,             ///< Mask used to retrieve the string
        fretNumberMask      = (wxByte)0x1f              ///< Mask used to retrieve the fret number
    };
    
    enum simpleFlags
    {
        tied                        = (wxWord)0x01,
        muted                       = (wxWord)0x02,
        tieWrap                     = (wxWord)0x04,     ///< Used to wrap a tie around systems
        hammerOn                    = (wxWord)0x08,
        pullOff                     = (wxWord)0x10,
        hammerPullFromToNowhere     = (wxWord)0x20,
        hammerPullMask              = (wxWord)0x38,     ///< Mask that filters out mutually exclusive hammer on/pull off flags
        naturalHarmonic             = (wxWord)0x40,
        ghostNote                   = (wxWord)0x80,
        octave8va                   = (wxWord)0x100,
        octave15ma                  = (wxWord)0x200,
        octave8vb                   = (wxWord)0x400,
        octave15mb                  = (wxWord)0x800,
        octaveMask                  = (wxWord)0xf00,    ///< Mask that filters out mutually exclusive octave flags
        simpleFlagsMask             = (wxWord)0xfff     ///< Mask that filters out all possible simple flags
    };
	
    enum complexSymbolTypes
    {
        slide                   = (wxByte)'d',
        bend                    = (wxByte)'e',
        tappedHarmonic          = (wxByte)'f',
        trill                   = (wxByte)'g',
        artificialHarmonic      = (wxByte)'h',
        notUsed                 = (wxUint32)0
    };
    
    enum slideIntoTypes
    {
        slideIntoNone                       = (wxByte)0x00,
        slideIntoFromBelow                  = (wxByte)0x01,
        slideIntoFromAbove                  = (wxByte)0x02,
        slideIntoShiftSlideUpwards          = (wxByte)0x03,     ///< Used for wrapping shift slides around systems
        slideIntoShiftSlideDownwards        = (wxByte)0x04,     ///< Used for wrapping shift slides around systems
        slideIntoLegatoSlideUpwards         = (wxByte)0x05,     ///< Used for wrapping legato slides around systems
        slideIntoLegatoSlideDownwards       = (wxByte)0x06      ///< Used for wrapping legato slides around systems
    };
    
    enum slideOutOfTypes
    {
        slideOutOfNone                      = (wxByte)0x00,
        slideOutOfShiftSlide                = (wxByte)0x01,
        slideOutOfLegatoSlide               = (wxByte)0x02,
        slideOutOfDownwards                 = (wxByte)0x03,
        slideOutOfUpwards                   = (wxByte)0x04
    };
        
    enum slideFlags
    {
        slideIntoTypeMask       = (wxUint32)0xff0000,               ///< Mask used to retrieve the slide into type
        slideOutOfTypeMask      = (wxUint32)0xff00,                 ///< Mask used to retrieve the slide out of type
        slideOutOfStepsMask     = (wxUint32)0xff,                   ///< Mask used to retrieve the slide out of steps
    };
    
    enum bendTypes
    {
        normalBend              = (wxByte)0x00,
        bendAndRelease          = (wxByte)0x01,
        bendAndHold             = (wxByte)0x02,
        preBend                 = (wxByte)0x03,
        preBendAndRelease       = (wxByte)0x04,
        preBendAndHold          = (wxByte)0x05,
        gradualRelease          = (wxByte)0x06,
        immediateRelease        = (wxByte)0x07
    };
    
    enum bendDrawingPoints
    {
        lowPoint                = (wxByte)0x00,
        midPoint                = (wxByte)0x01,
        highPoint               = (wxByte)0x02
    };
    
    enum bendFlags
    {
        bendTypeMask            = (wxUint32)0xf00000,               ///< Mask used to retrieve the bend type
        drawStartMask           = (wxUint32)0xc0000,                ///< Mask used to retrieve the draw start value
        drawEndMask             = (wxUint32)0x30000,                ///< Mask used to retrieve the draw end value
        bendDurationMask        = (wxUint32)0xff00,                 ///< Mask used to retrieve the bend duration
        bentPitchMask           = (wxUint32)0xf0,                   ///< Mask used to retrieve the bent pitch value
        releasePitchMask        = (wxUint32)0xf                     ///< Mask used to retrieve the release pitch value
    };
    
    enum artificialHarmonicOctaves
    {
        artificialHarmonicOctaveLoco            = (wxByte)0x00,
        artificialHarmonicOctave8va             = (wxByte)0x01,
        artificialHarmonicOctave15ma            = (wxByte)0x02
    };
    
// Member Variables
protected:
    wxByte      m_stringData;                                       ///< Top 3 bits = string, bottom 5 bits = fret number
	wxWord      m_simpleData;						                ///< Contains simple symbol flags
	wxUint32    m_complexSymbolArray[MAX_NOTE_COMPLEX_SYMBOLS];	    ///< Complex symbol data (1 symbol per element)

// Constructor/Destructor
public:
	Note();
	Note(wxUint32 string, wxByte fretNumber);
	Note(const Note& note);
	~Note();
	
// Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                     
        {return (new Note(*this));}
    	
// Operators
	const Note& operator=(const Note& note);
	bool operator==(const Note& note) const;
	bool operator!=(const Note& note) const;

// Serialization Functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

// MFC Class Functions
public:
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const                        
        {return (wxT("CLineData"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const
        {return ((wxWord)1);}
    
// String Functions
    /// Determines if a string is valid
    /// @param string String to validate
    /// @return True if the string is valid, false if not
    static const bool IsValidString(wxUint32 string)
        {return (string <= MAX_STRING);}
    bool SetString(wxUint32 string);
    wxUint32 GetString() const;
     
// Fret Number Functions
    /// Determines if a fret number is valid
    /// @param fretNumber Fret number to validate
    /// @return True if the fret number is valid, false if not
    static const bool IsValidFretNumber(wxByte fretNumber)
        {return (fretNumber <= MAX_FRET_NUMBER);}
    bool SetFretNumber(wxByte fretNumber);
    wxByte GetFretNumber() const;
    
// Tied Functions
    /// Sets or clears a tie
    /// @param set True to set the tie, false to clear it
    /// @return True if the tie was set or cleared, false if not
    bool SetTied(bool set = true)
    {
        if (!set)
            return (ClearSimpleFlag(tied));
        return (SetSimpleFlag(tied));
    }
    /// Determines if the note is tied
    /// @return True if the note is tied, false if not
    bool IsTied() const
        {return (IsSimpleFlagSet(tied));}

// Muted Functions
    /// Sets or clears the muted effect
    /// @param set True to set the muted effect, false to clear it
    /// @return True if the muted effect was set or cleared, false if not
    bool SetMuted(bool set = true)
    {
        if (!set)
            return (ClearSimpleFlag(muted));
        return (SetSimpleFlag(muted));
    }
    /// Determines if the note is muted
    /// @return True if the note is muted, false if not
	bool IsMuted() const
	    {return (IsSimpleFlagSet(muted));}

// Tie Wrap Functions
    /// Sets or clears a tie wrap
    /// @param set True to set the tie wrap, false to clear it
    /// @return True if the tie wrap was set or cleared, false if not
    bool SetTieWrap(bool set = true)
    {
        if (!set)
            return (ClearSimpleFlag(tieWrap));
        return (SetSimpleFlag(tieWrap));
    }    
    /// Determines if the note has a tie wrap
    /// @return True if the note has a tie wrap, false if not
  	bool HasTieWrap() const
  	    {return (IsSimpleFlagSet(tieWrap));}
  	    
// Hammer On Functions
    /// Sets or clears a hammer on
    /// @param set True to set the hammer on, false to clear it
    /// @return True if the hammer on was set or cleared, false if not
    bool SetHammerOn(bool set = true)
    {
        if (!set)
            return (ClearSimpleFlag(hammerPullMask));
        return (SetSimpleFlag(hammerOn) &&
            ClearSimpleFlag(hammerPullFromToNowhere));
    }
	/// Determines if the note has a hammer on
	/// @return True if the note has a hammer on, false if not
	bool HasHammerOn() const
    {
        return (IsSimpleFlagSet(hammerOn) &&
            !IsSimpleFlagSet(hammerPullFromToNowhere));
    }
	/// Sets or clears a hammer on from nowhere
	/// @param set True to set the hammer on from nowhere, false to clear it
	/// @return True if the hammer on from nowhere was set or cleared, false if
    /// not
	bool SetHammerOnFromNowhere(bool set = true)
    {
        if (!set)
            return (ClearSimpleFlag(hammerPullMask));
        return (SetSimpleFlag(hammerOn | hammerPullFromToNowhere));
    }
    /// Determines if the note has a hammer on from nowhere
    /// @return True if the note has a hammer on from nowhere, false if not
    bool HasHammerOnFromNowhere() const
        {return (IsSimpleFlagSet(hammerOn | hammerPullFromToNowhere));}
        
// Pull Off Functions
	/// Sets or clears a pull off
    /// @param set True to set the pull off, false to clear it
    /// @return True if the pull off was set or cleared, false if not
    bool SetPullOff(bool set = true)
    {
        if (!set)
            return (ClearSimpleFlag(hammerPullMask));
        return (SetSimpleFlag(pullOff) &&
            ClearSimpleFlag(hammerPullFromToNowhere));
    }   
	/// Determines if the note has a pull off
	/// @return True if the note has a pull off, false if not    
	bool HasPullOff() const
    {
        return (IsSimpleFlagSet(pullOff) &&
            !IsSimpleFlagSet(hammerPullFromToNowhere));
    }
    /// Sets or clears a pull off to nowhere
    /// @param set True to set the pull off to nowhere, false to clear it
    /// @return True if the pull off to nowhere was set or cleared, false if not
	bool SetPullOffToNowhere(bool set = true)
	{
        if (!set)
            return (ClearSimpleFlag(hammerPullMask));
        return (SetSimpleFlag(pullOff | hammerPullFromToNowhere));
    }
    /// Determines if the note has a pull off to nowhere
    /// @return True if the note has a pull off to nowhere, false if not
    bool HasPullOffToNowhere() const
    {
        return (IsSimpleFlagSet(pullOff) &&
            IsSimpleFlagSet(hammerPullFromToNowhere));
    }
	
// Natural Harmonic Functions
	/// Sets or clears a natural harmonic
    /// @param set True to set the natural harmonic, false to clear it
    /// @return True if the natural harmonic was set or cleared, false if not
    bool SetNaturalHarmonic(bool set = true)
    {
        if (!set)
            return (ClearSimpleFlag(naturalHarmonic));
        return (SetSimpleFlag(naturalHarmonic));
    }
	/// Determines if the note is a natural harmonic
	/// @return True if the note is a natural harmonic, false if not
	bool IsNaturalHarmonic() const
	    {return (IsSimpleFlagSet(naturalHarmonic));}
	    
// Ghost Note Functions
	/// Sets or clears a ghost note
    /// @param set True to set the ghost note, false to clear it
    /// @return True if the ghost note was set or cleared, false if not
    bool SetGhostNote(bool set = true)
    {
        if (!set)
            return (ClearSimpleFlag(ghostNote));
        return (SetSimpleFlag(ghostNote));
    }
	/// Determines if the note is a ghost note
	/// @return True if the note is a ghost note, false if not    
	bool IsGhostNote() const
	    {return (IsSimpleFlagSet(ghostNote));}

// 8va Octave Functions
	/// Sets or clears an 8va octave marker
    /// @param set True to set the 8va octave marker, false to clear it
    /// @return True if the 8va octave marker was set or cleared, false if not
    bool SetOctave8va(bool set = true)
    {
        if (!set)
            return (ClearSimpleFlag(octave8va));
        return (SetSimpleFlag(octave8va));
    }
	/// Determines if the note is an 8va
	/// @return True if the note is an 8va, false if not    
	bool IsOctave8va() const
	    {return (IsSimpleFlagSet(octave8va));}

// 15ma Octave Functions
	/// Sets or clears an 15ma octave marker
    /// @param set True to set the 15ma octave marker, false to clear it
    /// @return True if the 15ma octave marker was set or cleared, false if not
    bool SetOctave15ma(bool set = true)
    {
        if (!set)
            return (ClearSimpleFlag(octave15ma));
        return (SetSimpleFlag(octave15ma));
    }
	/// Determines if the note is an 15ma
	/// @return True if the note is an 15ma, false if not    
	bool IsOctave15ma() const
	    {return (IsSimpleFlagSet(octave15ma));}

// 8vb Octave Functions
	/// Sets or clears an 8vb octave marker
    /// @param set True to set the 8vb octave marker, false to clear it
    /// @return True if the 8vb octave marker was set or cleared, false if not
    bool SetOctave8vb(bool set = true)
    {
        if (!set)
            return (ClearSimpleFlag(octave8vb));
        return (SetSimpleFlag(octave8vb));
    }
	/// Determines if the note is an 8vb
	/// @return True if the note is an 8vb, false if not    
	bool IsOctave8vb() const
	    {return (IsSimpleFlagSet(octave8vb));}

// 15mb Octave Functions
	/// Sets or clears an 15mb octave marker
    /// @param set True to set the 15mb octave marker, false to clear it
    /// @return True if the 15mb octave marker was set or cleared, false if not
    bool SetOctave15mb(bool set = true)
    {
        if (!set)
            return (ClearSimpleFlag(octave15mb));
        return (SetSimpleFlag(octave15mb));
    }
	/// Determines if the note is an 15mb
	/// @return True if the note is an 15mb, false if not    
	bool IsOctave15mb() const
	    {return (IsSimpleFlagSet(octave15mb));}
	    
// Simple Flag Functions
protected:
    // Determines if a simple flag is valid
    /// @param flag Flag to validate
    /// @return True if the flag is valid, false if not
    static bool IsValidSimpleFlag(wxWord flag)
    {
        return (((flag & simpleFlagsMask) != 0) &&
            ((flag & ~simpleFlagsMask) == 0));
    }
    bool SetSimpleFlag(wxWord flag);
    /// Clears a simple flag
    /// @param flag Flag to clear
    /// @return True if the flag was cleared, false if not
    bool ClearSimpleFlag(wxWord flag)
    {
        wxCHECK(IsValidSimpleFlag(flag), false);
        m_simpleData &= ~flag;
        return (true);
    }
    /// Determines if a simple flag is set
    /// @param flag Flag to test
    /// @return True if the flag is set, false if not
    bool IsSimpleFlagSet(wxWord flag) const
    {
        wxCHECK(IsValidSimpleFlag(flag), false);
        return ((m_simpleData & flag) == flag);
    }

// Slide Functions
public:
    /// Determines if the note has a slide (either in or out)
    /// @return True if the note has a slide, false if not
    bool HasSlide() const
        {return (HasSlideInto() || HasSlideOutOf());}
        
// Slide Into Functions
    /// Determines if a slide into type is valid
    /// @param type Type to validate
    /// @return True if the slide into type is valid, false if not
    static bool IsValidSlideIntoType(wxByte type)
        {return (type <= slideIntoLegatoSlideDownwards);}
    /// Determines if slide into data is valid
    /// @param type Type to validate
    /// @return True if slide into data is valid, false if not
    static bool IsValidSlideInto(wxByte type)
        {return (IsValidSlideIntoType(type));}
    bool SetSlideInto(wxByte type);
    bool GetSlideInto(wxByte& type) const;
    bool HasSlideInto() const;
    bool ClearSlideInto();
    
// Slide Out Of Functions
    /// Determines if a slide out of type is valid
    /// @param type Type to validate
    /// @return True if the slide out of type is valid, false if not
    static bool IsValidSlideOutOfType(wxByte type)
        {return (type <= slideOutOfUpwards);}
    /// Determines if slide out of data is valid
    /// @param type Type to validate
    /// @return True if the slide out of data is valid, false if not
    static bool IsValidSlideOutOf(wxByte type)
        {return (IsValidSlideOutOfType(type));}
    bool SetSlideOutOf(wxByte type, wxInt8 steps);
    bool GetSlideOutOf(wxByte& type, wxInt8& steps) const;
    bool HasSlideOutOf() const;
    bool ClearSlideOutOf();
    
// Bend Functions
    static bool IsValidBend(wxByte type, wxByte bentPitch, wxByte releasePitch,
        wxByte duration, wxByte drawStartPoint, wxByte drawEndPoint);
    /// Determines if a bend type is valid
    /// @param type Bend type to validate
    /// @return True if the bend type is valid, false if not
    static bool IsValidBendType(wxByte type)
        {return (type <= immediateRelease);}
    /// Determines if a bent pitch is valid
    /// @param bentPitch Bent pitch to validate
    /// @return True if the bent pitch is valid, false if not
    static bool IsValidBentPitch(wxByte bentPitch)
        {return (bentPitch <= MAX_BEND_PITCH);}
    /// Determines if a release pitch is valid
    /// @param releasePitch Release pitch to validate
    /// @return True if the release pitch is valid, false if not
    static bool IsValidReleasePitch(wxByte releasePitch)
        {return (releasePitch <= MAX_BEND_PITCH);}
    /// Determines if a bend duration is valid
    /// @param duration Duration to validate
    /// @return True if the duration is valid, false if not
    static bool IsValidBendDuration(wxByte duration)
        {return (duration <= MAX_BEND_DURATION);}
    /// Determines if a draw start point is valid
    /// @param drawStartPoint Draw start point to validate
    /// @return True if the draw start point is valid, false if not
    static bool IsValidDrawStartPoint(wxByte drawStartPoint)
        {return (drawStartPoint <= highPoint);}
    /// Determines if a draw end point is valid
    /// @param drawEndPoint Draw end point to validate
    /// @return True if the draw end point is valid, false if not
    static bool IsValidDrawEndPoint(wxByte drawEndPoint)
        {return (drawEndPoint <= highPoint);}
    bool SetBend(wxByte type, wxByte bentPitch, wxByte releasePitch,
        wxByte duration, wxByte drawStartPoint, wxByte drawEndPoint);
    bool GetBend(wxByte& type, wxByte& bentPitch, wxByte& releasePitch,
        wxByte& duration, wxByte& drawStartPoint, wxByte& drawEndPoint) const;
    bool HasBend() const;
    bool ClearBend();
    
// Tapped Harmonic Functions
    /// Determines if a tapped fret number is valid
    /// @param tappedFretNumber Tapped fret number to validate
    /// @return True if the tapped fret number is valid, false if not
    static bool IsValidTappedFretNumber(wxByte tappedFretNumber)
    {
        return ((tappedFretNumber >= MIN_FRET_NUMBER) &&
            (tappedFretNumber <= MAX_FRET_NUMBER));
    }
    /// Determines if tapped harmonic data is valid
    /// @param tappedFretNumber Tapped fret number to validate
    /// @return True if the tapped harmonic data is valid, false if not
    static bool IsValidTappedHarmonic(wxByte tappedFretNumber)
        {return (IsValidTappedFretNumber(tappedFretNumber));}
    bool SetTappedHarmonic(wxByte tappedFretNumber);
    bool GetTappedHarmonic(wxByte& tappedFretNumber) const;
    bool HasTappedHarmonic() const;
    bool ClearTappedHarmonic();
    
// Trill Functions
    /// Determines if a trilled fret number is valid
    /// @param trilledFretNumber Trilled fret number to validate
    /// @return True if the trilled fret number is valid, false if not
    static bool IsValidTrilledFretNumber(wxByte trilledFretNumber)
    {
        return ((trilledFretNumber >= MIN_FRET_NUMBER) &&
            (trilledFretNumber <= MAX_FRET_NUMBER));
    }
    /// Determines if trill data is valid
    /// @param trilledFretNumber Trilled fret number to validate
    /// @return True if the trill data is valid, false if not
    static bool IsValidTrill(wxByte trilledFretNumber)
        {return (IsValidTrilledFretNumber(trilledFretNumber));}
    bool SetTrill(wxByte trilledFretNumber);
    bool GetTrill(wxByte& trilledFretNumber) const;
    bool HasTrill() const;
    bool ClearTrill();
    	
// Artificial Harmonic Functions
    /// Determines if a artificial octave is valid
    /// @param octave Octave to validate
    /// @return True if the artificial harmonic octave is valid, false if not
    static bool IsValidArtificialHarmonicOctave(wxByte octave)
        {return (octave <= artificialHarmonicOctave15ma);}
    /// Determines if artificial harmonic data is valid
    /// @param key Key to validate
    /// @param keyVariation Key variation to validate
    /// @param octave Octave to validate
    /// @return True if the artificial harmonic data is valid, false if not
    static bool IsValidArtificialHarmonic(wxByte key, wxByte keyVariation,
        wxByte octave)
    {
        return (ChordName::IsValidKeyAndVariation(key, keyVariation) &&
            IsValidArtificialHarmonicOctave(octave));
    }
    bool SetArtificialHarmonic(wxByte key, wxByte keyVariation, wxByte octave);
    bool GetArtificialHarmonic(wxByte& key, wxByte& keyVariation,
        wxByte& octave) const;
    bool HasArtificialHarmonic() const;
    bool ClearArtificialHarmonic();

// Complex Symbol Array Functions
protected:
    /// Determines if a complex symbol type is valid
    /// @param type Symbol type to validate
    /// @return True if the symbol type is valid, false if not
    static bool IsValidComplexSymbolType(wxByte type)
    {
        return ((type == slide) || (type == bend) || (type == tappedHarmonic) ||
            (type == tappedHarmonic) || (type == trill) ||
            (type == artificialHarmonic));
    }
    bool AddComplexSymbol(wxUint32 symbolData);
    size_t GetComplexSymbolCount() const;
    wxUint32 FindComplexSymbol(wxByte type) const;
    bool RemoveComplexSymbol(wxByte type);
    void ClearComplexSymbolArrayContents();    
};

WX_DEFINE_POWERTABARRAY(Note*, NoteArray);

#endif
