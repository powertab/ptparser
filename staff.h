/////////////////////////////////////////////////////////////////////////////
// Name:            staff.h
// Purpose:         Stores and renders a staff
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 16, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __STAFF_H__
#define __STAFF_H__

#include "position.h"

#define NUM_STAFF_VOICES 2    ///< Number of voices in a staff

/// Stores and renders a staff
class Staff : public PowerTabObject
{
friend class StaffTestSuite;

// Constants
public:
    // Default Constants
    static const wxByte DEFAULT_DATA;                                   ///< Default value for the data member variable
    static const wxByte DEFAULT_CLEF;                                   ///< Default clef type
    static const wxByte DEFAULT_TABLATURE_STAFF_TYPE;                   ///< Default tablature staff type
    static const wxByte DEFAULT_STANDARD_NOTATION_STAFF_ABOVE_SPACING;  ///< Default value for the standard notation staff above spacing member variable
    static const wxByte DEFAULT_STANDARD_NOTATION_STAFF_BELOW_SPACING;  ///< Default value for the standard notation staff below spacing member variable
    static const wxByte DEFAULT_SYMBOL_SPACING;                         ///< Default value for the symbol spacing member variable
    static const wxByte DEFAULT_TABLATURE_STAFF_BELOW_SPACING;          ///< Default value for the tablature staff below spacing member variable
    
    // Clef Constants
    static const wxByte TREBLE_CLEF;                                ///< Treble clef
    static const wxByte BASS_CLEF;                                  ///< Bass clef

    // Tablature Staff Type Constants    
    static const wxByte MIN_TABLATURE_STAFF_TYPE;                   ///< Minimum allowed value for tablature staff type
    static const wxByte MAX_TABLATURE_STAFF_TYPE;                   ///< Maximum allowed value for tablature staff type
    
    enum flags
    {
        clefMask                    = (wxByte)0xf0,                 ///< Mask used to retrieve the clef type
        tablatureStaffTypeMask      = (wxByte)0xf                   ///< Mask used to retrieve the tablature type (3 - 7 string)
    };
    
// Member Variables
protected:
	wxByte m_data;											        ///< Top 4 bits = clef type, bottom 4 bits = tablature type
	wxByte m_standardNotationStaffAboveSpacing;                     ///< Amount of space alloted from the top line of the standard notation staff
	wxByte m_standardNotationStaffBelowSpacing;                     ///< Amount of space alloted from the last line of the standard notation staff
	wxByte m_symbolSpacing;                                         ///< Amount of space alloted for symbols located between the standard notation and tablature staff
	wxByte m_tablatureStaffBelowSpacing;                            ///< Amount of space alloted from the last line of the tablature staff

public:
    PositionArray m_positionArray[NUM_STAFF_VOICES];                ///< Array of positions; one for each voice - 0 = high melody, 1 = low melody

// Constructor/Destructor
public:
	Staff();
	Staff(wxByte tablatureStaffType, wxByte clef);
	Staff(const Staff& staff);
	~Staff();

// Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                     
        {return (new Staff(*this));}
    
// Operators
	const Staff& operator=(const Staff& staff);
	bool operator==(const Staff& staff) const;
	bool operator!=(const Staff& staff) const;

// Serialize Functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

// MFC Class Functions
public:
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const                        
        {return (wxT("CStaff"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const                        
        {return ((wxWord)1);}
    
// Clef Functions
    /// Determines if a Clef is valid
    /// @param clef Clef to validate
    /// @return True if the clef is valid, false if not
    static bool IsValidClef(wxByte clef)                    
        {return ((clef >= TREBLE_CLEF) && (clef <= BASS_CLEF));}
    bool SetClef(wxByte type);
    /// Gets the clef used on the standard notation staff
    /// @return The clef used on the standard notation staff
    wxByte GetClef() const                                  
        {return ((wxByte)((m_data & clefMask) >> 4));}
    
// Tablature Staff Type Functions
    /// Determines if a Tablature Staff Type is valid
    /// @param type Tablature staff type to validate
    /// @return True if the tablature staff type is valid, false if not
    static bool IsValidTablatureStaffType(wxByte type)      
    {
        return ((type >= MIN_TABLATURE_STAFF_TYPE) &&
            ((type <= MAX_TABLATURE_STAFF_TYPE)));
    }
    bool SetTablatureStaffType(wxByte type);
    /// Gets the tablature staff type (3-7 strings)
    /// @return The tablature staff type
    wxByte GetTablatureStaffType() const                     
        {return ((wxByte)(m_data & tablatureStaffTypeMask));}
    
// Standard Notation Staff Above Spacing Functions
    /// Sets the amount of spacing above the standard notation staff
    /// @param spacing Spacing to set
    void SetStandardNotationStaffAboveSpacing(wxByte spacing)
        {m_standardNotationStaffAboveSpacing = spacing;}
    /// Gets the amount of spacing above the standard notation staff
    /// @return The amount of spacing above the standard notation staff
    wxByte GetStandardNotationStaffAboveSpacing() const         
        {return (m_standardNotationStaffAboveSpacing);}
    
// Standard Notation Staff Below Spacing Functions
    /// Sets the amount of spacing below the standard notation staff
    /// @param spacing Spacing to set
    void SetStandardNotationStaffBelowSpacing(wxByte spacing)   
        {m_standardNotationStaffBelowSpacing = spacing;}
    /// Gets the amount of spacing below the standard notation staff
    /// @return The amount of spacing below the standard notation staff
    wxByte GetStandardNotationStaffBelowSpacing() const         
        {return (m_standardNotationStaffBelowSpacing);}
    
// Symbol Spacing Functions
    /// Sets the amount of spacing used by symbols in between the standard
    /// notation and tablature staves
    /// @param spacing Spacing to set
    void SetSymbolSpacing(wxByte spacing)                   
        {m_symbolSpacing = spacing;}
    /// Gets the amount of spacing used by symbols in between the standard
    /// notation and tablature staves
    /// @return The amount of spacing used by symbols in between the standard
    /// notation and tablature staves
    wxByte GetSymbolSpacing() const                         
        {return (m_symbolSpacing);}
    
// Tablature Staff Below Spacing Functions
    /// Sets the amount of spacing below the tablature staff
    /// @param spacing Spacing to set
    void SetTablatureStaffBelowSpacing(wxByte spacing)      
        {m_tablatureStaffBelowSpacing = spacing;}
    /// Gets the amount of spacing below the tablature staff
    /// @return The amount of spacing below the tablature staff
    wxByte GetTablatureStaffBelowSpacing() const            
        {return (m_tablatureStaffBelowSpacing);}
    
// Voice Functions
    /// Determines if a voice is valid
    /// @param voice Voice to validate
    /// @return True if the voice is valid, false if not
    static bool IsValidVoice(wxUint32 voice)
        {return (voice < NUM_STAFF_VOICES);}
        
// Position Functions
    /// Determines if a position index is valid
    /// @param voice Voice the position belongs to
    /// @param index position index to validate
    /// @return True if the position index is valid, false if not
    bool IsValidPositionIndex(wxUint32 voice, wxUint32 index) const
    {
        wxCHECK(IsValidVoice(voice), false);
        return (index < GetPositionCount(voice));
    }
    /// Gets the number of positions in the staff
    /// @param voice Voice of the positions to get the count of
    /// @return The number of positions in the staff
    size_t GetPositionCount(wxUint32 voice) const
    {
        wxCHECK(IsValidVoice(voice), 0);
        return (m_positionArray[voice].GetCount());
    }
    /// Gets the nth position in the staff
    /// @param voice Voice the position belongs to
    /// @param index Index of the position to get
    /// @return The nth position in the staff
    Position* GetPosition(wxUint32 voice, wxUint32 index) const
    {
        wxCHECK(IsValidPositionIndex(voice, index), NULL);
        return (m_positionArray[voice][index]);
    }
};

WX_DEFINE_POWERTABARRAY(Staff*, StaffArray);

#endif
