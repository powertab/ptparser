/////////////////////////////////////////////////////////////////////////////
// Name:            system.h
// Purpose:         Stores and renders a system
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 16, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "direction.h"
#include "chordtext.h"
#include "rhythmslash.h"
#include "staff.h"
#include "barline.h"

/// Stores and renders a system
class System : public PowerTabObject
{
friend class SystemTestSuite;

// Constants
public:
    // Default Constants
    static const wxRect DEFAULT_RECT;
    static const wxByte DEFAULT_POSITION_SPACING;
    static const wxByte DEFAULT_RHYTHM_SLASH_SPACING_ABOVE;
    static const wxByte DEFAULT_RHYTHM_SLASH_SPACING_BELOW;
    static const wxByte DEFAULT_EXTRA_SPACING;
    
    // Position Spacing Constants
    static const wxByte MIN_POSITION_SPACING;

 // Member Variables
protected:
	wxRect  m_rect;												///< Bounding rect for the system
	wxByte  m_positionSpacing;									///< Spacing between each position in the system
	wxByte  m_rhythmSlashSpacingAbove;							///< Spacing above the rhythm slashes
	wxByte  m_rhythmSlashSpacingBelow;						    ///< Spacing below the rhythm slashes				
	wxByte  m_extraSpacing;									    ///< Extra spacing used within the system (for rehearsal signs + tempo markers)

public:
    Barline             m_startBar;                             ///< Barline at the start of the system
    DirectionArray      m_directionArray;                       ///< List of directions used within the system
    ChordTextArray      m_chordTextArray;                       ///< List of chord text items used within the system
    RhythmSlashArray    m_rhythmSlashArray;                     ///< List of rhythm slashes used within the system
    StaffArray          m_staffArray;                           ///< List of staves used within the system
    BarlineArray        m_barlineArray;                         ///< List of barlines (not including start and end bars) used within the system
    Barline             m_endBar;                               ///< Barline at the end of the system (time and key signature are not used in this barline)

// Constructor/Destructor
public:
	System();
	System(const System& system);
	~System();

// Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const
        {return (new System(*this));}
    
// Operators
	const System& operator=(const System& system);
    bool operator==(const System& system) const;
    bool operator!=(const System& system) const;
   
// Serialzation Functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

// MFC Class Functions
public:
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const                            
        {return (wxT("CSection"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const                            
        {return ((wxWord)1);}
    
// Rect Functions
    /// Gets the bounding rect for the system
    /// @return The bounding rect for the system
    wxRect GetRect() const
        {return (m_rect);}
        
// Position Spacing Functions
    /// Determines if a position spacing is valid
    /// @param positionSpacing Position spacing to validate
    /// @return True if the position spacing is valid, false if not
    bool IsValidPositionSpacing(int positionSpacing) const
        {return (positionSpacing >= MIN_POSITION_SPACING);}
    /// Gets the amount of spacing between positions
    /// @return The amount of spacing between positions
    wxUint32 GetPositionSpacing() const
        {return (m_positionSpacing);}
    
// Rhythm Slash Spacing Above Functions
    /// Gets the amount of spacing above the rhythm slashes (when slashes are
    /// used)
    /// @return The amount of spacing above the rhythm slashes
    wxUint32 GetRhythmSlashSpacingAbove() const
        {return (m_rhythmSlashSpacingAbove);}
    
// Rhythm Slash Spacing Below Functions
    /// Gets the amount of spacing below the rhythm slashes (when slashes are
    /// used)
    /// @return The amount of spacing below the rhythm slashes
    wxUint32 GetRhythmSlashSpacingBelow() const
        {return (m_rhythmSlashSpacingBelow);}
        
// Extra Spacing Functions
    /// Gets the extra spacing (used by rehearsal signs, tempo markers, etc.)
    /// @return The amount of extra spacing
    wxUint32 GetExtraSpacing() const
        {return (m_extraSpacing);}
     
// Start Bar Functions
    /// Gets the bar at the start of the system
    /// @return The start bar
    Barline GetStartBar() const
        {return (m_startBar);}
    /// Gets a reference to the bar at the start of the system
    /// @return A reference to the bar at the start of the system
    Barline& GetStartBarRef()
        {return (m_startBar);}
    /// Gets a constant reference to the bar at the start of the system
    /// @return A constant reference to the bar at the start of the system
    const Barline& GetStartBarConstRef() const
        {return (m_startBar);}
                
// Direction Functions
    /// Determines if a staff index is valid
    /// @param index staff index to validate
    /// @return True if the staff index is valid, false if not
    bool IsValidDirectionIndex(wxUint32 index) const
        {return (index < GetDirectionCount());}
    /// Gets the number of staffs in the system
    /// @return The number of staffs in the system
    size_t GetDirectionCount() const
        {return (m_directionArray.GetCount());}
    /// Gets the nth staff in the system
    /// @param index Index of the staff to get
    /// @return The nth staff in the system
    Direction* GetDirection(wxUint32 index) const
    {
        wxCHECK(IsValidDirectionIndex(index), NULL);
        return (m_directionArray[index]);
    }
        
// Chord Text Functions
    /// Determines if a chord text index is valid
    /// @param index chord text index to validate
    /// @return True if the chord text index is valid, false if not
    bool IsValidChordTextIndex(wxUint32 index) const
        {return (index < GetChordTextCount());}
    /// Gets the number of chord text items in the system
    /// @return The number of chord text items in the system
    size_t GetChordTextCount() const
        {return (m_chordTextArray.GetCount());}
    /// Gets the nth chord text item in the system
    /// @param index Index of the chord text to get
    /// @return The nth chord text item in the system
    ChordText* GetChordText(wxUint32 index) const
    {
        wxCHECK(IsValidChordTextIndex(index), NULL);
        return (m_chordTextArray[index]);
    }

// Rhythm Slash Functions
    /// Determines if a rhythm slash index is valid
    /// @param index rhythm slash index to validate
    /// @return True if the rhythm slash index is valid, false if not
    bool IsValidRhythmSlashIndex(wxUint32 index) const
        {return (index < GetRhythmSlashCount());}
    /// Gets the number of rhythm slashes in the system
    /// @return The number of rhythm slashes in the system
    size_t GetRhythmSlashCount() const
        {return (m_rhythmSlashArray.GetCount());}
    /// Gets the nth rhythm slash in the system
    /// @param index Index of the rhythm slash to get
    /// @return The nth rhythm slash in the system
    RhythmSlash* GetRhythmSlash(wxUint32 index) const
    {
        wxCHECK(IsValidRhythmSlashIndex(index), NULL);
        return (m_rhythmSlashArray[index]);
    }
    
// Staff Functions
    /// Determines if a staff index is valid
    /// @param index staff index to validate
    /// @return True if the staff index is valid, false if not
    bool IsValidStaffIndex(wxUint32 index) const
        {return (index < GetStaffCount());}
    /// Gets the number of staffs in the system
    /// @return The number of staffs in the system
    size_t GetStaffCount() const
        {return (m_staffArray.GetCount());}
    /// Gets the nth staff in the system
    /// @param index Index of the staff to get
    /// @return The nth staff in the system
    Staff* GetStaff(wxUint32 index) const
        {wxCHECK(IsValidStaffIndex(index), NULL); return (m_staffArray[index]);}

// Barline Functions
    /// Determines if a barline index is valid
    /// @param index barline index to validate
    /// @return True if the barline index is valid, false if not
    bool IsValidBarlineIndex(wxUint32 index) const
        {return (index < GetBarlineCount());}
    /// Gets the number of barlines in the system
    /// @return The number of barlines in the system
    size_t GetBarlineCount() const
        {return (m_barlineArray.GetCount());}
    /// Gets the nth barline in the system
    /// @param index Index of the barline to get
    /// @return The nth barline in the system
    Barline* GetBarline(wxUint32 index) const
    {
        wxCHECK(IsValidBarlineIndex(index), NULL);
        return (m_barlineArray[index]);
    }
    Barline* GetBarlineAtPosition(wxUint32 position) const;
    void GetBarlines(BarlineArray& barlineArray);
    
// End Bar Functions
    /// Gets the bar at the end of the system
    /// @return The end bar
    Barline GetEndBar() const
        {return (m_endBar);}
    /// Gets a reference to the bar at the end of the system
    /// @return A reference to the bar at the end of the system
    Barline& GetEndBarRef()
        {return (m_endBar);}
    /// Gets a constant reference to the bar at the end of the system
    /// @return A constant reference to the bar at the end of the system
    const Barline& GetEndBarConstRef() const
        {return (m_endBar);}        

// Position Functions
    bool IsValidPosition(int position) const;
    int CalculatePositionCount(int nPositionSpacing) const;
    int GetPositionCount() const;
    int GetFirstPositionX() const;
    int GetPositionX(int position) const;

// Operations
    int GetCumulativeInternalKeyAndTimeSignatureWidth(int position = -1) const;
};

WX_DEFINE_POWERTABARRAY(System*, SystemArray);

#endif
