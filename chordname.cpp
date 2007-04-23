/////////////////////////////////////////////////////////////////////////////
// Name:            chordname.cpp
// Purpose:         Stores and renders a chord name
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 16, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "chordname.h"

#include <math.h>                       // Needed for pow()
#include "powertabfileheader.h"         // Needed for FILEVERSION constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Default Constants
const wxWord ChordName::DEFAULT_KEY                         = (wxWord)((variationDefault << 12) | (C << 8) | (variationDefault << 4) | C); // C/C
const wxByte ChordName::DEFAULT_FORMULA                     = (wxByte)(major << 4);     // Major
const wxWord ChordName::DEFAULT_FORMULA_MODIFICATIONS       = 0;
const wxByte ChordName::DEFAULT_EXTRA                       = 0;

// Type Constants
const wxByte ChordName::MIN_TYPE                            = 2;
const wxByte ChordName::MAX_TYPE                            = 8;

// Fret Position Constants
const wxByte ChordName::MIN_FRET_POSITION                   = 0;
const wxByte ChordName::MAX_FRET_POSITION                   = 24;

/// Default Constructor
ChordName::ChordName() :
    m_key(DEFAULT_KEY), m_formula(DEFAULT_FORMULA), m_formulaModifications(DEFAULT_FORMULA_MODIFICATIONS), m_extra(DEFAULT_EXTRA)
{
    //------Last Checked------//
    // - Jan 4, 2005
}

/// Primary Constructor
/// @param tonicKey Key to set (see keys enum for values)
/// @param tonicKeyVariation Key variation to set (see keyVariation enum for values)
/// @param formula Formula to set (see formula enum for values)
/// @param formulaModifications Formula modifications to set (see formulaModifications enum for values)
/// @param fretPosition Fret position to set (0 through 30 + not used)
/// @param type Type to set
ChordName::ChordName(wxByte tonicKey, wxByte tonicKeyVariation, wxByte formula, wxWord formulaModifications, wxByte fretPosition, wxByte type) :
    m_key(DEFAULT_KEY), m_formula(DEFAULT_FORMULA), m_formulaModifications(DEFAULT_FORMULA_MODIFICATIONS), m_extra(DEFAULT_EXTRA)
{
    //------Last Checked------//
    // - Jan 4, 2005
    SetTonic(tonicKey, tonicKeyVariation);
    SetFormula(formula);
    SetFormulaModifications(formulaModifications);
    SetFretPosition(fretPosition);
    SetType(type);
}

/// Copy Constructor
ChordName::ChordName(const ChordName& chordName) :
    m_key(DEFAULT_KEY), m_formula(DEFAULT_FORMULA), m_formulaModifications(DEFAULT_FORMULA_MODIFICATIONS), m_extra(DEFAULT_EXTRA)
{
    //------Last Checked------//
    // - Dec 16, 2004
    *this = chordName;
}

/// Destructor
ChordName::~ChordName()
{
    //------Last Checked------//
    // - Dec 16, 2004
}

/// Assignment Operator
const ChordName& ChordName::operator=(const ChordName& chordName)
{
    //------Last Checked------//
    // - Jan 4, 2005
    
    // Check for assignment to self
    if (this != &chordName)
    {
    	m_key = chordName.m_key;
	    m_formula = chordName.m_formula;
	    m_formulaModifications = chordName.m_formulaModifications;
	    m_extra = chordName.m_extra;
    }
	return (*this);
}

/// Equality Operator
bool ChordName::operator==(const ChordName& chordName) const
{
	//------Last Checked------//
	// - Jan 4, 2005
	return (
	    (m_key == chordName.m_key) &&
	    (m_formula == chordName.m_formula) &&
	    (m_formulaModifications == chordName.m_formulaModifications) &&
	    (m_extra == chordName.m_extra)
    );
}

/// Inequality Operator
bool ChordName::operator!=(const ChordName& chordName) const
{
    //------Last Checked------//
    // - Dec 16, 2004
    return (!operator==(chordName));
}

// Serialize Functions
/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool ChordName::DoSerialize(PowerTabOutputStream& stream)
{
    //------Last Checked------//
    // - Jan 4, 2005
    stream << m_key << m_formula << m_formulaModifications << m_extra;
    wxCHECK(stream.CheckState(), false);
    return (stream.CheckState());
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool ChordName::DoDeserialize(PowerTabInputStream& stream, wxWord version)
{
    //------Last Checked------//
    // - Dec 14, 2004
    
    // Version 1.0 or 1.0.2
	if (version == PowerTabFileHeader::FILEVERSION_1_0 || version == PowerTabFileHeader::FILEVERSION_1_0_2)
	{
		wxByte key;
		stream >> key >> m_formula >> m_formulaModifications >> m_extra;
		wxCHECK(stream.CheckState(), false);

		wxByte tonicKey = (wxByte)((key >> 4) & 0xf);
		wxByte bassKey = (wxByte)(key & 0xf);
		bool tonicSharp = ((m_formula & tonicSharps) == tonicSharps);
		bool bassSharp = ((m_formula & bassNoteSharps) == bassNoteSharps);

		wxByte keyVariation = 1;

		// CASE: Chord uses sharp
		if (tonicSharp && (tonicKey == 3 || tonicKey == 8 || tonicKey == 10))
			keyVariation = 0;
		else if (!tonicSharp && (tonicKey == 1 || tonicKey == 6))
			keyVariation = 2;

		SetTonic(tonicKey, keyVariation);

		keyVariation = 1;

		// CASE: Bass note uses sharp
		if (bassSharp && (bassKey == 3 || bassKey == 8 || bassKey == 10))
			keyVariation = 0;
		else if (!bassSharp && (bassKey == 1 || bassKey == 6))
			keyVariation = 2;

		SetBassNote(bassKey, keyVariation);
	}
	// Version 1.5 and up
	else
	{
		stream >> m_key >> m_formula >> m_formulaModifications >> m_extra;
		wxCHECK(stream.CheckState(), false);
	}
			
    return (stream.CheckState());
}

// Tonic Functions
/// Sets the tonic key (i.e. For Cm/E, C is the tonic)
/// @param key Key to set (see keys enum for values)
/// @param keyVariation Key variation to set (see keyVariation enum for values)
/// @return True if the tonic was set, false if not
bool ChordName::SetTonic(wxByte key, wxByte keyVariation)
{
    //------Last Checked------//
    // - Jan 17, 2005
    wxCHECK(IsValidKeyAndVariation(key, keyVariation), false);

	m_key &= ~tonicKeyAndVariationMask;

    m_key |= (wxWord)(key << 8);
	m_key |= (wxWord)(keyVariation << 12);
	
	return (true);
}

/// Gets the tonic key
/// @param key Holds the key return value
/// @param keyVariation Holds the key variation return value
void ChordName::GetTonic(wxByte& key, wxByte& keyVariation) const
{
    //------Last Checked------//
    // - Jan 17, 2005
    key = (wxByte)((m_key & tonicKeyMask) >> 8);
    keyVariation = (wxByte)((m_key & tonicKeyVariationMask) >> 12);
}

/// Determines if the tonic matches a given key and variation
/// @param key Key to match
/// @param keyVariation Key variation to match
/// @return True if tonic matches the key and variation, false if not
bool ChordName::IsSameTonic(wxByte key, wxByte keyVariation) const
{
    //------Last Checked------//
    // - Jan 17, 2005
    wxByte thisKey = 0;
    wxByte thisKeyVariation = 0;
    GetTonic(thisKey, thisKeyVariation);
    return ((thisKey == key) && (thisKeyVariation == keyVariation));
}

// Bass Note Functions
/// Sets the bass note key (i.e. For Cm/E, E is the bass note)
/// @param key Key to set (see keys enum for values)
/// @param keyVariation Key variation to set (see keyVariation enum for values)
/// @return True if the bass note was set, false if not
bool ChordName::SetBassNote(wxByte key, wxByte keyVariation)
{
    //------Last Checked------//
    // - Jan 17, 2005
    wxCHECK(IsValidKeyAndVariation(key, keyVariation), false);

	m_key &= ~bassNoteKeyAndVariationMask;

    m_key |= (wxWord)key;
	m_key |= (wxWord)(keyVariation << 4);
	
	return (true);
}

/// Gets the bass note key
/// @param key Holds the key return value
/// @param keyVariation Holds the key variation return value
void ChordName::GetBassNote(wxByte& key, wxByte& keyVariation) const
{
    //------Last Checked------//
    // - Jan 17, 2005
    key = (wxByte)(m_key & bassNoteKeyMask);
    keyVariation = (wxByte)((m_key & bassNoteKeyVariationMask) >> 4);
}

/// Determines if the bass note matches a given key and variation
/// @param key Key to match
/// @param keyVariation Key variation to match
/// @return True if bass note matches the key and variation, false if not
bool ChordName::IsSameBassNote(wxByte key, wxByte keyVariation) const
{
    //------Last Checked------//
    // - Jan 17, 2005
    wxByte thisKey = 0;
    wxByte thisKeyVariation = 0;
    GetBassNote(thisKey, thisKeyVariation);
    return ((thisKey == key) && (thisKeyVariation == keyVariation));
}

// Formula Functions
/// Sets the formula
/// @param formula Formula to set (see formula enum for values)
/// @return True if the formula was set, false if not
bool ChordName::SetFormula(wxByte formula)
{
    //------Last Checked------//
    // - Jan 4, 2005
    wxCHECK(IsValidFormula(formula), false);
    
	m_formula &= ~formulaMask;
	m_formula |= formula;
	return (true);
}

/// Gets the formula
/// @return The formula
wxByte ChordName::GetFormula() const
{
    //------Last Checked------//
    // - Jan 4, 2005
	return ((wxByte)(m_formula & formulaMask));
}

/// Gets a text representation of the formula
/// @return A text representation of the formula
wxString ChordName::GetFormulaText() const
{
    wxString returnValue;

    // Get extensions
	// Add any extension to the chord name
	int nFormula = GetFormula();
	BOOL bExtension = FALSE;
	wxWord wExtension[3] = {extended9th, extended11th, extended13th};
	wxString strExtension[3] = {_T("9"), _T("11"), _T("13")};

    wxString chordAbbreviations[10] =
    {
        wxT("maj"),
        wxT("m"),
        wxT("+"),
        wxT("o"),
        wxT("5"),
        wxT("add"),
        wxT("sus2"),
        wxT("sus4"),
        wxT("#"),
        wxT("b")
    };

	for (int j = 0; j < 3; j++)
	{
		if (m_formulaModifications & wExtension[j])
		{
			if (nFormula >= 8)
			{
				returnValue += (
					(nFormula == 8) ? chordAbbreviations[0] :
					(nFormula == 9) ? chordAbbreviations[1] :
					(nFormula == 10) ? chordAbbreviations[2] :
					(nFormula == 11) ? chordAbbreviations[3] :
					(nFormula == 12) ? (chordAbbreviations[1] + _T("/") + chordAbbreviations[0]) :
					(chordAbbreviations[1] + strExtension[j] + _T("b5"))
				);

				if (nFormula < 13)
					returnValue += strExtension[j];
			}
			else if (nFormula == 7)
				returnValue += strExtension[j];
			bExtension = TRUE;
		}
	}

    // Chord suffixes
	wxString strSuffixList[14] =
	{
		_T(""),
		chordAbbreviations[1],
		chordAbbreviations[2],
		chordAbbreviations[3],
		chordAbbreviations[4],
		_T("6"),
		chordAbbreviations[1] + _T("6"),
		_T("7"),
		chordAbbreviations[0] + _T("7"),
		chordAbbreviations[1] + _T("7"),
		chordAbbreviations[2] + _T("7"),
		chordAbbreviations[3] + _T("7"),
		chordAbbreviations[1] + _T("/") + chordAbbreviations[0] + _T("7"),
		_T("m7") + chordAbbreviations[9] + _T("5")
	};

	// If not an extension, add the suffix
	if (!bExtension && nFormula != 0)
		returnValue += strSuffixList[nFormula];

	wxString strText;
	WORD wFormulaBit[13] = {suspended2nd, suspended4th, added2nd, added4th, added6th, added9th, added11th, flatted13th, raised11th, flatted9th, raised9th, flatted5th, raised5th};
	wxString strAddition[13] = {chordAbbreviations[6], chordAbbreviations[7], chordAbbreviations[5] + _T("2"), chordAbbreviations[5] + _T("4"),
		chordAbbreviations[5] + _T("6"), chordAbbreviations[5] + _T("9"), chordAbbreviations[5] + _T("11"),
		chordAbbreviations[9] + _T("13"), chordAbbreviations[8] + _T("11"), chordAbbreviations[9] + _T("9"),
		chordAbbreviations[8] + _T("9"), chordAbbreviations[9] + _T("5"), chordAbbreviations[8] + _T("5")};

	for (int j = 0; j < 13; j++)
	{			
		if (m_formulaModifications & wFormulaBit[j])
			returnValue += strAddition[j];
	}

    return (returnValue);
}

// Formula Modifications Functions
/// Gets the number of formula modifications in the chord name
/// @return The number of formula modifications in the chord name
wxUint32 ChordName::GetFormulaModificationsCount() const
{
    //------Last Checked------//
    // - Jan 4, 2005
    wxUint32 returnValue = 0;
    
    wxWord i = extended9th;
	for (; i <= suspended4th; i = 2 * i)
	{
	    if (IsFormulaModificationFlagSet(i))
	        returnValue++;
	    
	    // Wraparound break
	    if (i == suspended4th)
	        break;
	}

	return (returnValue);
}

// Fret Position Functions
/// Sets the fret position
/// @param fretPosition Fret position to set (0 through 30 + not used)
/// @return True if the fret position was set, false if not
bool ChordName::SetFretPosition(wxByte fretPosition)
{
    //------Last Checked------//
    // - Jan 4, 2005
    wxCHECK(IsValidFretPosition(fretPosition), false);
 
    // Note: Fret position is stored as values 0 to 31; 0 = not used, 1 to 31 = open to 30th fret
    if (fretPosition == fretPositionNotUsed)
        fretPosition = 0;
    else
        fretPosition++;
        
	m_extra &= ~fretPositionMask;
	m_extra |= fretPosition;
	
	return (true);
}

/// Gets the fret position
/// @return The fret position
wxByte ChordName::GetFretPosition() const
{
    //------Last Checked------//
    // - Jan 4, 2005
	wxByte returnValue = (wxByte)(m_extra & fretPositionMask);
	return (wxByte)((returnValue == 0) ? fretPositionNotUsed : (returnValue - 1));
}

// Type Functions
/// Sets the type (Type 2, Type 4, etc.)
/// @param type Type to set
/// @return True if the type was set, false if not
bool ChordName::SetType(wxByte type)
{
    //------Last Checked------//
    // - Jan 4, 2005
    wxCHECK(IsValidType(type), false);
    
	// Note: Type is stored as values 0 to 7; 0 = not used, 1 to 7 = types 2 to 8
	if (type == typeNotUsed)
        type = 0;
	else
		type--;
    
	m_extra &= ~typeMask;
	m_extra |= (wxByte)(type << 5);
	return (true);
}

/// Gets the type (Type 2, Type 4, etc.)
/// @return The type
wxByte ChordName::GetType() const
{
    //------Last Checked------//
    // - Jan 4, 2005
	wxByte returnValue = (wxByte)(m_extra >> 5);
	return (wxByte)((returnValue == 0) ? typeNotUsed : (returnValue + 1));
}
