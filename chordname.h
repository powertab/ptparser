/////////////////////////////////////////////////////////////////////////////
// Name:            chordname.h
// Purpose:         Stores and renders a chord name
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 16, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __CHORDNAME_H__
#define __CHORDNAME_H__

/// Stores and renders a chord name
class ChordName : public PowerTabObject
{
friend class ChordNameTestSuite;

// Constants
public:
    static const wxWord DEFAULT_KEY;                        ///< Default value for the key member variable
    static const wxByte DEFAULT_FORMULA;                    ///< Default value for the formula member variable
    static const wxWord DEFAULT_FORMULA_MODIFICATIONS;      ///< Default value for the formula modifications member variable
    static const wxByte DEFAULT_EXTRA;                      ///< Default value for the extra member variable
    
    static const wxByte MIN_TYPE;                           ///< Minimum allowed value for the type
    static const wxByte MAX_TYPE;                           ///< Maximum allowed value for the type
    
    static const wxByte MIN_FRET_POSITION;                  ///< Minimum allowed value for the fret position
    static const wxByte MAX_FRET_POSITION;                  ///< Maximum allowed value for the fret position

    enum keys
    {
        C                   = (wxByte)0x00,
        CSharp              = (wxByte)0x01,
        D                   = (wxByte)0x02,
        EFlat               = (wxByte)0x03,
        E                   = (wxByte)0x04,
        F                   = (wxByte)0x05,
        FSharp              = (wxByte)0x06,
        G                   = (wxByte)0x07,
        AFlat               = (wxByte)0x08,
        A                   = (wxByte)0x09,
        BFlat               = (wxByte)0x0a,
        B                   = (wxByte)0x0b
    };
    	
    // Key variations (homonyms)
    enum keyVariations
    {
        variationDown       = (wxByte)0x00,                 ///< B#, Bx, Cx, D#, Dx, E#, Ex, Fx, G#, Gx, A#, Ax
        variationDefault    = (wxByte)0x01,                 ///< C, C#, D, Eb, E, F, F#, G, Ab, A, Bb, B
        variationUp         = (wxByte)0x02                  ///< Dbb, Db, Ebb, Fbb, Fb, Gbb, Gb, Abb, , Bbb, Cbb, Cb
    };
    
    enum keyFlags
    {
        tonicKeyMask                = (wxWord)0xf00,        ///< Mask used to retrieve the tonic key
        tonicKeyVariationMask       = (wxWord)0x3000,       ///< Mask used to retrieve the tonic key variation
        tonicKeyAndVariationMask    = (wxWord)0x3f00,       ///< Mask used to retrieve the tonic key and variation
        bassNoteKeyMask             = (wxWord)0xf,          ///< Mask used to retrieve the bass note key
        bassNoteKeyVariationMask    = (wxWord)0x30,         ///< Mask used to retrieve the bass note key variation
        bassNoteKeyAndVariationMask = (wxWord)0x3f          ///< Mask used to retrieve the bass note key and variation
    };
    
	enum formulaFlags
	{
	    noChord             = (wxByte)0x10,                 ///< No Chord symbol
        brackets            = (wxByte)0x20,                 ///< Places brackets around the chord name
        bassNoteSharps      = (wxByte)0x40,                 ///< Bass note uses sharps vs flats (used for compatibility only)
        tonicSharps         = (wxByte)0x80,                 ///< Tonic uses sharps vs flats (used for compatibility only)
        formulaFlagsMask    = (wxByte)0xf0,                 ///< Mask used to retrieve all formula flags
		formulaMask         = (wxByte)0x0f                  ///< Mask used to retrieve the formula
	};

	enum formula
	{
		major                       = (wxByte)0x00,
		minor                       = (wxByte)0x01,
		augmented                   = (wxByte)0x02,
		diminished                  = (wxByte)0x03,
		powerChord                  = (wxByte)0x04,
		major6th                    = (wxByte)0x05,
		minor6th                    = (wxByte)0x06,
		dominant7th                 = (wxByte)0x07,
		major7th                    = (wxByte)0x08,
		minor7th                    = (wxByte)0x09,
		augmented7th                = (wxByte)0x0a,
		diminished7th               = (wxByte)0x0b,
		minorMajor7th               = (wxByte)0x0c,
		minor7thFlatted5th          = (wxByte)0x0d
	};

	enum formulaModifications
	{
		extended9th	    = (wxWord)0x01,
		extended11th	= (wxWord)0x02,
		extended13th	= (wxWord)0x04,
		added2nd	    = (wxWord)0x08,
		added4th	    = (wxWord)0x10,
		added6th	    = (wxWord)0x20,
		added9th	    = (wxWord)0x40,
		added11th	    = (wxWord)0x80,
		flatted5th	    = (wxWord)0x100,
		raised5th	    = (wxWord)0x200,
		flatted9th	    = (wxWord)0x400,
		raised9th	    = (wxWord)0x800,
		raised11th	    = (wxWord)0x1000,
		flatted13th	    = (wxWord)0x2000,
		suspended2nd	= (wxWord)0x4000,
		suspended4th	= (wxWord)0x8000
	};

    enum extraFlags
    {
        fretPositionNotUsed     = (wxByte)0xff,             ///< Value to indicate the fret position is not used
        fretPositionMask        = (wxByte)0x1f,             ///< Mask used to retrieve the fret position
        typeNotUsed             = (wxByte)0xff,             ///< Value to indicate the type is not used
        typeMask                = (wxByte)0xe0              ///< Mask used to retrieve the type
    };
    
protected:
    wxWord m_key;                                           ///< Chord key and bass note (hiword = tonic, loword = bass note; bits 5-6 = variation, bottom 4 bits = key)
    wxByte m_formula;                                       ///< Core formula + flags (see formula and formulaFlags enums for values)
    wxWord m_formulaModifications;                          ///< Stores the formula modifications (see formulaModifications enum for values)
    wxByte m_extra;                                         ///< Stores the type and fret position data (top 3 bits = type, bottom 5 bits = position)
    
public:
    // Constructor/Destructor
	ChordName();
	ChordName(wxByte tonicKey, wxByte tonicKeyVariation, wxByte formula, wxWord formulaAdditions, wxByte fretPosition = fretPositionNotUsed, wxByte type = typeNotUsed);
	ChordName(const ChordName& chordName);
	~ChordName();

    // Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                             
        {return (new ChordName(*this));}
    
	// Operators
	const ChordName& operator=(const ChordName& chordName);
	bool operator==(const ChordName& chordName) const;
	bool operator!=(const ChordName& chordName) const;

	// Serialize Functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

public:    	    
    // MFC Class Functions
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const
        {return (wxT("CChordName"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const
        {return ((wxWord)1);}
    
    // Key Functions
    /// Determines if a key is valid
    /// @param key Key to validate
    /// @return True if the key is valid, false if not
    static bool IsValidKey(wxByte key)
        {return (key <= B);}
    /// Determines if a key variation is valid
    /// @param keyVariation Key variation to validate
    /// @return True if the key variation is valid, false if not
    static bool IsValidKeyVariation(wxByte keyVariation)
        {return (keyVariation <= variationUp);}
    /// Determines if a key and key variation are valid
    /// @param key Key to validate
    /// @param keyVariation Key variation to validate
    /// @return True if the key and key variation are valid, false if not
    static bool IsValidKeyAndVariation(wxByte key, wxByte keyVariation)
        {return ((IsValidKey(key) && IsValidKeyVariation(keyVariation)) && !(key == AFlat && keyVariation == variationUp));}

    // Tonic Functions
    bool SetTonic(wxByte key, wxByte keyVariation);
    void GetTonic(wxByte& key, wxByte& keyVariation) const;
    bool IsSameTonic(wxByte key, wxByte keyVariation) const;
        
    // Bass Note Functions
    bool SetBassNote(wxByte key, wxByte keyVariation);    
	void GetBassNote(wxByte& key, wxByte& keyVariation) const;
	bool IsSameBassNote(wxByte key, wxByte keyVariation) const;
	
    // Formula Functions
    /// Determines if a formula is valid
    /// @param formula Formula to validate
    /// @return True if the formula is valid, false if not
    static bool IsValidFormula(wxByte formula)                      
        {return (formula <= minor7thFlatted5th);}
    bool SetFormula(wxByte formula);
    wxByte GetFormula() const;
    wxString GetFormulaText() const;

    // Brackets Functions
    /// Sets or clears the brackets
    /// @return True if the brackets were set or cleared, false if not
	bool SetBrackets(bool set = true)
	    {if (!set) return (ClearFormulaFlag(brackets)); return (SetFormulaFlag(brackets));}
	/// Determines if the chord name is bracketed
	/// @return True if the chord name is bracketed, false if not
	bool HasBrackets() const                                        
	    {return (IsFormulaFlagSet(brackets));}
    
    // No Chord Functions
    /// Sets or clears the no chord (N.C.) type
    /// @param set True to set the no chord type, false to clear it
    /// @return True if the no chord type was set or cleared, false if not
	bool SetNoChord(bool set = true)
	    {if (!set) return (ClearFormulaFlag(noChord)); return (SetFormulaFlag(noChord));}	
	/// Determines if the chord name is the "no chord" (N.C.)
	/// @return True if the chord name is the "no chord"
    bool IsNoChord() const                                          
        {return (IsFormulaFlagSet(noChord));}
        
    // Formula Flag Functions
protected:
    /// Determines if a formula flag is valid
    /// @param flag Flag to validate
    /// @return True if the flag is valid, false if not
    static bool IsValidFormulaFlag(wxByte flag)                     
        {return (((flag & formulaFlagsMask) != 0) && ((flag & ~formulaFlagsMask) == 0));}
    /// Sets a formula flag
    /// @param flag Flag to set
    /// @return True if the flag was set, false if not
    bool SetFormulaFlag(wxByte flag)                                
        {wxCHECK(IsValidFormulaFlag(flag), false); m_formula |= flag; return (true);}
    /// Clears a formula flag
    /// @param flag Flag to clear
    /// @return True if the flag was cleared, false if not
    bool ClearFormulaFlag(wxByte flag)                              
        {wxCHECK(IsValidFormulaFlag(flag), false); m_formula &= ~flag; return (true);}
    /// Determines if a formula flag is set
    /// @param flag Flag to test
    /// @return True if the flag is set, false if not
    bool IsFormulaFlagSet(wxByte flag) const                        
        {return ((m_formula & flag) == flag);}
        	
public:
	// Formula Modifications Functions
	/// Sets the Formula Modifications (see formulaModifications enum for values)
	/// @param formulaModifications Formula modifications to set
	void SetFormulaModifications(wxWord formulaModifications)
        {m_formulaModifications = formulaModifications;}
	wxUint32 GetFormulaModificationsCount() const;
	/// Clears all formula modifications
	void ClearFormulaModifications()
	    {m_formulaModifications = 0;}
    /// Determines if a formula modification flag is set
    /// @param flag Formula modification flag to test
    /// @return True if the formula modification flag is set, false if not
    bool IsFormulaModificationFlagSet(wxWord flag) const
        {return ((m_formulaModifications & flag) == flag);}
protected:
    /// Sets a formula modifications flag
    /// @param flag Flag to set
    void SetFormulaModificationFlag(wxWord flag)
        {m_formulaModifications |= flag;}
    /// Clears a formula modifications flag
    /// @param flag Flag to clear
    void ClearFormulaModificationFlag(wxWord flag)
        {m_formulaModifications &= ~flag;}
        
public:			
	// Fret Position Functions
	/// Determines if a fret position is valid
	/// @param fretPosition Fret position to validate
	/// @return True if the fret position is valid, false is not
	static bool IsValidFretPosition(wxByte fretPosition)        
	    {return (((fretPosition >= MIN_FRET_POSITION) && (fretPosition <= MAX_FRET_POSITION)) || (fretPosition == fretPositionNotUsed));}
	bool SetFretPosition(wxByte fretPosition);
	wxByte GetFretPosition() const;
	/// Determines if the fret position is being used
	/// @return True if the fret position is being used, false if not
	bool IsFretPositionUsed() const                                 
	    {return (GetFretPosition() != fretPositionNotUsed);}
	
	// Type Functions
	/// Determines if a type is valid
	/// @param type Type to validate
	/// @return True if the type is valid, false if not
	static bool IsValidType(wxByte type)                            
	    {return (((type >= MIN_TYPE) && (type <= MAX_TYPE)) || (type == typeNotUsed));}
	bool SetType(wxByte type);
	wxByte GetType() const;
	/// Determines if the type is being used
	/// @return True if the type is being used, false if not
	bool IsTypeUsed() const                                         
	    {return (GetType() != typeNotUsed);}
};

#endif
