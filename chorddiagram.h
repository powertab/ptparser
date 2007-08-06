/////////////////////////////////////////////////////////////////////////////
// Name:            chorddiagram.h
// Purpose:         Stores and renders a chord diagram
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 16, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __CHORDDIAGRAM_H__
#define __CHORDDIAGRAM_H__

#include "chordname.h"
#include "tuning.h"

/// Stores and renders a chord diagram
class ChordDiagram : public PowerTabObject
{
friend class ChordDiagramTestSuite;

// Constants
    // Default Constants
    static const wxByte DEFAULT_TOP_FRET;       ///< Default value for the top fret member variable

    // Top Fret Constants
    static const wxByte MIN_TOP_FRET;           ///< Minimum allowed value for the top fret member variable
    static const wxByte MAX_TOP_FRET;           ///< Maximum allowed value for the top fret member variable
    
    // Fret Number Constants
    static const wxByte MIN_FRET_NUMBER;        ///< Minimum allowed fret number
    static const wxByte MAX_FRET_NUMBER;        ///< Maximum allowed fret number

    enum flags
    {
        stringMuted = (wxByte)0xfe,             ///< String is muted "x"
        notUsed     = (wxByte)0xff              ///< String is not used
    };

// Member Variables
protected:
    ChordName       m_chordName;                ///< Chord name that appears above the chord diagram
    wxByte          m_topFret;                  ///< Fret represented at the top of the chord diagram
    wxByteArray     m_fretNumberArray;          ///< List of fret number offsets

// Constructor/Destructor
public:
    ChordDiagram();
    ChordDiagram(const ChordName& chordName, wxByte topFret, wxByte fretNumber1,
        wxByte fretNumber2, wxByte fretNumber3, wxByte fretNumber4 = notUsed,
        wxByte fretNumber5 = notUsed, wxByte fretNumber6 = notUsed,
        wxByte fretNumber7 = notUsed);
    ChordDiagram(wxByte topFret, wxByte fretNumber1, wxByte fretNumber2,
        wxByte fretNumber3, wxByte fretNumber4 = notUsed,
        wxByte fretNumber5 = notUsed, wxByte fretNumber6 = notUsed,
        wxByte fretNumber7 = notUsed);
    ChordDiagram(const ChordDiagram& chordDiagram);
    ~ChordDiagram();

// Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                 
        {return (new ChordDiagram(*this));}
    
// Operators
    const ChordDiagram& operator=(const ChordDiagram& chordDiagram);
    bool operator==(const ChordDiagram& chordDiagram) const;
    bool operator!=(const ChordDiagram& chordDiagram) const;
    // TODO: Add operator[]
    
// Serialize Functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

// MFC Class Functions
public:    
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const                        
        {return (wxT("CChordDiagram"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const                        
        {return ((wxWord)1);}
    
// Chord Diagram Functions
    bool SetChordDiagram(const ChordName& chordName, wxByte topFret,
        wxByte fretNumber1, wxByte fretNumber2, wxByte fretNumber3,
        wxByte fretNumber4 = notUsed, wxByte fretNumber5 = notUsed,
        wxByte fretNumber6 = notUsed, wxByte fretNumber7 = notUsed);
    
// Chord Name Functions
    /// Sets the chord name
    /// @param chordName Chord name to set
    void SetChordName(const ChordName& chordName)       
        {m_chordName = chordName;}
    /// Gets the chord name
    /// @return The chord name
    ChordName GetChordName() const                      
        {return (m_chordName);}
    /// Gets a reference to the chord name
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
    
// Top Fret Functions
    /// Determines if a top fret value is valid
    /// @param topFret Top fret to validate
    /// @return True if the top fret value is valid, false if not
    static bool IsValidTopFret(wxByte topFret)
        {return (topFret <= MAX_TOP_FRET);}
    /// Sets the top fret
    /// @param topFret Top fret to set
    /// @return True if the top fret was set, false if not
    bool SetTopFret(wxByte topFret)
    {
        wxCHECK(IsValidTopFret(topFret), false);
        m_topFret = topFret;
        return (true);
    }
    /// Gets the top fret value
    /// @return The top fret
    wxByte GetTopFret() const
        {return (m_topFret);}

// String Functions
    /// Determines if a string is valid
    /// @param string String to validate
    /// @return True if the string is valid, false if not
    bool IsValidString(wxUint32 string) const
        {return (string < GetStringCount());}
    /// Gets the number of strings used in the chord diagram
    /// @return The number of strings used in the chord diagram
    size_t GetStringCount() const
        {return (m_fretNumberArray.GetCount());}
    
// Fret Number Functions    
    /// Determines if a fret number is valid
    /// @param fretNumber Fret number to validate
    /// @return True if the fret number is valid, false if not
    static bool IsValidFretNumber(wxByte fretNumber)
    {
        return ((fretNumber <= MAX_FRET_NUMBER) ||
            (fretNumber == stringMuted) ||
            (fretNumber == notUsed));
    }
    bool SetFretNumber(wxUint32 string, wxByte fretNumber);
    wxByte GetFretNumber(wxUint32 string) const;
protected:
    bool AddFretNumbers(wxByte fretNumber1, wxByte fretNumber2,
        wxByte fretNumber3, wxByte fretNumber4, wxByte fretNumber5,
        wxByte fretNumber6, wxByte fretNumber7);
    /// Deletes the contents (and frees the memory) of the fret number array
    void DeleteFretNumberArrayContents()
        {m_fretNumberArray.Clear();}

// Voicing Functions
public:
    bool IsSameVoicing(const ChordDiagram& chordDiagram) const;
    bool IsSameVoicing(wxByte fretNumber1, wxByte fretNumber2,
        wxByte fretNumber3, wxByte fretNumber4 = notUsed,
        wxByte fretNumber5 = notUsed, wxByte fretNumber6 = notUsed,
        wxByte fretNumber7 = notUsed) const;
    
// Operations
    wxString GetSpelling() const;
};

// Array declarations
WX_DEFINE_POWERTABARRAY(ChordDiagram*, ChordDiagramArray);

#endif
