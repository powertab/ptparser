/////////////////////////////////////////////////////////////////////////////
// Name:            systemsymbol.h
// Purpose:         Base class for symbols residing on a system scope
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 13, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __SYSTEMSYMBOL_H__
#define __SYSTEMSYMBOL_H__

/// Base class for symbols residing on a system scope
class SystemSymbol : public PowerTabObject
{
friend class SystemSymbolTestSuite;

// Constants
public:
    // Default constants
    static const wxWord         DEFAULT_SYSTEM;             ///< Default value for the system member variable
    static const wxByte         DEFAULT_POSITION;           ///< Default value for the position member variable
    static const wxUint32       DEFAULT_DATA;               ///< Default value for the data member variable

    // System Constants
    static const wxUint32       MIN_SYSTEM;                 ///< Minimum allowed value for the system member variable
    static const wxUint32       MAX_SYSTEM;                 ///< Maximum allowed value for the system member variable

    // Position Constants
    static const wxUint32       MIN_POSITION;               ///< Minimum allowed value for the position member variable
    static const wxUint32       MAX_POSITION;               ///< Maximum allowed value for the position member variable

protected:
    wxWord      m_system;           ///< Zero-based index of the system the symbol is anchored
    wxByte      m_position;         ///< Zero-based index of the position within the system where the symbol is anchored
    wxUint32    m_data;             ///< Data used by the symbol (different for each symbol)

public:
    // Constructor/Destructor
    SystemSymbol();
    SystemSymbol(wxUint32 system, wxUint32 position, wxUint32 symbol);
    SystemSymbol(const SystemSymbol& systemSymbol);
    virtual ~SystemSymbol();
    
    // Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                         
        {return (new SystemSymbol(*this));}
        
    // Operators
    const SystemSymbol& operator=(const SystemSymbol& systemSymbol);
    bool operator==(const SystemSymbol& systemSymbol) const;
    bool operator!=(const SystemSymbol& systemSymbol) const;

    // Serialization functions
protected:
    virtual bool DoSerialize(PowerTabOutputStream& stream);
    virtual bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

public:
    // MFC Class Functions
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const                            
        {return (wxT("CSectionSymbol"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const                            
        {return ((wxWord)1);}
    
    // System Functions
    /// Determines whether a system is valid
    /// @param system System to validate
    /// @return True if the system is valid, false if not
    static bool IsValidSystem(wxUint32 system)
        {return ((system >= MIN_SYSTEM) && (system <= MAX_SYSTEM));}
    /// Sets the system within the system where the system symbol is anchored
    /// @param system Zero-based index of the system where the system symbol is anchored
    /// @return True if the system was set, false if not
    bool SetSystem(wxUint32 system)                         
        {wxCHECK(IsValidSystem(system), false); m_system = (wxWord)system; return (true);}
    /// Gets the system within the system where the system symbol is anchored
    /// @return The system within the system where the system symbol is anchored
    wxUint32 GetSystem() const                                
        {return (m_system);}

    // Position Functions
    /// Determines whether a position is valid
    /// @param position Position to validate
    /// @return True if the position is valid, false if not
    static bool IsValidPosition(wxUint32 position)              
        {return ((position >= MIN_POSITION) && (position <= MAX_POSITION));}
    /// Sets the position within the system where the system symbol is anchored
    /// @param position Zero-based index within the system where the system symbol is anchored
    /// @return True if the position was set, false if not
    bool SetPosition(wxUint32 position)                         
        {wxCHECK(IsValidPosition(position), false); m_position = (wxByte)position; return (true);}
    /// Gets the position within the system where the system symbol is anchored
    /// @return The position within the system where the system symbol is anchored
    wxUint32 GetPosition() const                                
        {return (m_position);}
    
    // Data Functions
    /// Sets the data associated with the object
    /// @param data Data to set
    void SetData(wxUint32 data)
        {m_data = data;}
    /// Gets the data associated with the object
    /// @return The data associated with the object
    wxUint32 GetData() const
        {return (m_data);}
};

#endif
