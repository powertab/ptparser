/////////////////////////////////////////////////////////////////////////////
// Name:            chordtext.h
// Purpose:         Stores and renders chord text
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 3, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __CHORDTEXT_H__
#define __CHORDTEXT_H__

#include "chordname.h"

/// Stores and renders chord text
class ChordText : public PowerTabObject
{
friend class ChordTextTestSuite;

// Constants
public:
    // Default Constants
    static const wxByte DEFAULT_POSITION;       ///< Default value for the position member variable
    
protected:
    wxByte          m_position;                 ///< Zero-based index of the position within the system where the chord text is anchored
	ChordName       m_chordName;	            ///< Chord name data (see ChordName class for details)

public:
	// Constructor/Destructor
	ChordText();
	ChordText(wxUint32 position, const ChordName& chordName);
    ChordText(const ChordText& chordText);
	~ChordText();

    // Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                         
        {return (new ChordText(*this));}
    
    // Operators
	const ChordText& operator=(const ChordText& chordText);
	bool operator==(const ChordText& chordText) const;
	bool operator!=(const ChordText& chordText) const;

	// Serialization functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

public:
    // MFC Class Functions
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const                            
        {return (wxT("CChordText"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const                            
        {return ((wxWord)1);}
    
    // Position Functions
    /// Determines whether a position is valid
    /// @param position Position to validate
    /// @return True if the position is valid, false if not
    static bool IsValidPosition(wxUint32 position)              
        {return ((position >= 0) && (position <= 255));}
    /// Sets the position within the system where the chord text is anchored
    /// @param position Zero-based index within the system where the chord text is anchored
    /// @return True if the position was set, false if not
    bool SetPosition(wxUint32 position)                         
        {wxCHECK(IsValidPosition(position), false); m_position = (wxByte)position; return (true);}
    /// Gets the position within the system where the chord text is anchored
    /// @return The position within the system where the chord text is anchored
    wxUint32 GetPosition() const                                
        {return (m_position);}

	// Chord Name Functions
	/// Sets the chord name
    void SetChordName(const ChordName& chordName)               
        {m_chordName = chordName;}
    /// Gets the chord name
    /// @return The chord name
    ChordName GetChordName() const                              
        {return (m_chordName);}
    /// Gets a referenced to the chord name
    /// @return A reference to the chord name
    ChordName& GetChordNameRef()                                
        {return (m_chordName);}
    /// Gets a constant reference to the chord name
    /// @return A constant reference to the chord name
    const ChordName& GetChordNameConstRef() const               
        {return (m_chordName);}
    /// Gets a pointer to the chord name
    /// @return A pointer to the chord name
    ChordName* GetChordNamePtr()                                
        {return (&m_chordName);}
};

// Array Declarations
WX_DEFINE_POWERTABARRAY(ChordText*, ChordTextArray);

#endif
