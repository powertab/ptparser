/////////////////////////////////////////////////////////////////////////////
// Name:            guitarin.h
// Purpose:         Stores and renders guitar in symbols
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 16, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __GUITARIN_H__
#define __GUITARIN_H__

/// Stores and renders guitar in symbols
class GuitarIn : public PowerTabObject
{
friend class GuitarInTestSuite;

// Constants
public:
    // Default constants
    static const wxWord         DEFAULT_SYSTEM;                     ///< Default value for the system member variable
    static const wxByte         DEFAULT_STAFF;                      ///< Default value for the staff member variable
    static const wxByte         DEFAULT_POSITION;                   ///< Default value for the position member variable
    static const wxWord         DEFAULT_DATA;                       ///< Default value for the data member variable
    
    // System Constants
    static const wxUint32       MIN_SYSTEM;                         ///< Minimum allowed value for the system member variable
    static const wxUint32       MAX_SYSTEM;                         ///< Maximum allowed value for the system member variable

    // Staff Constants
    static const wxUint32       MIN_STAFF;                          ///< Minimum allowed value for the staff member variable
    static const wxUint32       MAX_STAFF;                          ///< Maximum allowed value for the staff member variable

    // Position Constants
    static const wxUint32       MIN_POSITION;                       ///< Minimum allowed value for the position member variable
    static const wxUint32       MAX_POSITION;                       ///< Maximum allowed value for the position member variable
    
// Member Variables
protected:
	wxWord      m_system;       ///< Zero-based index of the system where the guitar in is anchored
    wxByte      m_staff;        ///< Zero-based index of the staff within the system where the guitar in is anchored
    wxByte      m_position;     ///< Zero-based index of the position within the system where the guitar in is anchored
	wxWord      m_data;         ///< Bit map representing the guitar number of the active guitars (bit 1 = guitar 0, bit 2 = guitar 1, etc.)
	                            ///< High byte = staff guitars, low byte = rhythm slash guitars

// Constructor/Destructor
public:
	GuitarIn();
	GuitarIn(wxUint32 system, wxUint32 staff, wxUint32 position,
        wxByte staffGuitars, wxByte rhythmSlashGuitars);
	GuitarIn(const GuitarIn& guitarIn);
	~GuitarIn();
	
// Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                         
        {return (new GuitarIn(*this));}

// Operators
	const GuitarIn& operator=(const GuitarIn& guitarIn);
	bool operator==(const GuitarIn& guitarIn) const;
	bool operator!=(const GuitarIn& guitarIn) const;

// Serialize Functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

// MFC Class Functions
public:
    wxString GetMFCClassName() const                            
        {return (wxT("CGuitarIn"));}
    wxWord GetMFCClassSchema() const                            
        {return ((wxWord)1);}
    
// System Functions
    /// Determines whether a system is valid
    /// @param system System to validate
    /// @return True if the system is valid, false if not
    static bool IsValidSystem(wxUint32 system)
        {return ((system >= MIN_SYSTEM) && (system <= MAX_SYSTEM));}
    /// Sets the system within the system where the guitar in is anchored
    /// @param system Zero-based index of the system where the guitar in is
    /// anchored
    /// @return True if the system was set, false if not
    bool SetSystem(wxUint32 system)
    {
        wxCHECK(IsValidSystem(system), false);
        m_system = (wxWord)system;
        return (true);
    }
    /// Gets the system within the system where the guitar in is anchored
    /// @return The system within the system where the guitar in is anchored
    wxUint32 GetSystem() const                           
        {return (m_system);}
        
// Staff Functions
    /// Determines whether a staff is valid
    /// @param staff Staff to validate
    /// @return True if the staff is valid, false if not
    static bool IsValidStaff(wxUint32 staff)
        {return ((staff >= MIN_STAFF) && (staff <= MAX_STAFF));}
    /// Sets the staff within the system where the guitar in is anchored
    /// @param staff Zero-based index of the staff within the system where the
    /// guitar in is anchored
    /// @return True if the staff was set, false if not
    bool SetStaff(wxUint32 staff)
    {
        wxCHECK(IsValidStaff(staff), false);
        m_staff = (wxByte)staff;
        return (true);
    }
    /// Gets the staff within the system where the guitar in is anchored
    /// @return The staff within the system where the guitar in is anchored
    wxUint32 GetStaff() const                           
        {return (m_staff);}
        
// Position Functions
    /// Determines whether a position is valid
    /// @param position Position to validate
    /// @return True if the position is valid, false if not
    static bool IsValidPosition(wxUint32 position)
        {return ((position >= MIN_POSITION) && (position <= MAX_POSITION));}
    /// Sets the position within the system where the guitar in is anchored
    /// @param position Zero-based index of the position within the system where
    /// the guitar in is anchored
    /// @return True if the position was set, false if not
    bool SetPosition(wxUint32 position)
    {
        wxCHECK(IsValidPosition(position), false);
        m_position = (wxByte)position;
        return (true);
    }
    /// Gets the position within the system where the guitar in is anchored
    /// @return The position within the system where the guitar in is anchored
    wxUint32 GetPosition() const                           
        {return (m_position);}

// Staff Guitars Functions
    /// Sets the guitars active on the staff
    /// @param guitars A bit map representing the guitars to set
    /// (bit 1 = guitar 0, bit 2 = guitar 1, etc.)
    /// @return True if the guitars were set, false if not
    bool SetStaffGuitars(wxByte guitars)
        {return (SetGuitars(false, guitars));}
    /// Gets the staff guitars
    /// @return A bit map representing the active staff guitars
    /// (bit 1 = guitar 0, bit 2 = guitar 1, etc.)
    wxByte GetStaffGuitars() const
        {return (GetGuitars(false));}
    /// Determines if the staff guitars are set
    /// @return True if the staff guitars are set, false if not
    bool HasStaffGuitarsSet() const
        {return (HasGuitarsSet(false));}

// Rhythm Slash Functions
    /// Sets the guitars active for rhythm slashes
    /// @param guitars A bit map representing the guitars to set
    /// (bit 1 = guitar 0, bit 2 = guitar 1, etc.)
    /// @return True if the guitars were set, false if not
    bool SetRhythmSlashGuitars(wxByte guitars)
        {return (SetGuitars(true, guitars));}
    /// Gets the rhythm slash guitars
    /// @return A bit map representing the active rhythm slash guitars
    /// (bit 1 = guitar 0, bit 2 = guitar 1, etc.)
    wxByte GetRhythmSlashGuitars() const
        {return (GetGuitars(true));}
    /// Determines if the rhythm slash guitars are set
    /// @return True if the rhythm slash guitars are set, false if not
    bool HasRhythmSlashGuitarsSet() const
        {return (HasGuitarsSet(true));}
protected:
    bool SetGuitars(bool rhythmSlashes, wxByte guitars);
    wxByte GetGuitars(bool rhythmSlashes) const;
    bool HasGuitarsSet(bool rhythmSlashes) const;

// Operations
public:
    wxString GetText(bool rhythmSlashes) const;
};

WX_DEFINE_POWERTABARRAY(GuitarIn*, GuitarInArray);

#endif
