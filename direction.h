/////////////////////////////////////////////////////////////////////////////
// Name:            direction.h
// Purpose:         Stores and renders directions
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 9, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __DIRECTION_H__
#define __DIRECTION_H__

/// Stores and renders directions
class Direction : public PowerTabObject
{
friend class DirectionTestSuite;

// Constants
public:
    // Default Constants
    static const wxByte         DEFAULT_POSITION;       ///< Default value for the position member variable
    
    // Position Constants
    static const wxUint32       MIN_POSITION;           ///< Minimum allowed value for the position member variable
    static const wxUint32       MAX_POSITION;           ///< Maximum allowed value for the position member variable

    // Symbol Constants
    static const wxByte         MAX_SYMBOLS;            ///< Maximum allowed number of symbols in the symbol array
    static const wxByte         NUM_SYMBOL_TYPES;       ///< Number of direction symbol types
    
    // Repeat Number Constants
    static const wxByte         MIN_REPEAT_NUMBER;      ///< Minimum allowed value for the repeat number
    static const wxByte         MAX_REPEAT_NUMBER;      ///< Maximum allowed value for the repeat number

    enum symbolTypes
    {
        coda                            = (wxByte)0x00,
        doubleCoda                      = (wxByte)0x01,
        segno                           = (wxByte)0x02,
        segnoSegno                      = (wxByte)0x03,
        fine                            = (wxByte)0x04,
        daCapo                          = (wxByte)0x05,
        dalSegno                        = (wxByte)0x06,
        dalSegnoSegno                   = (wxByte)0x07,
        toCoda                          = (wxByte)0x08,
        toDoubleCoda                    = (wxByte)0x09,
        daCapoAlCoda                    = (wxByte)0x0a,
        daCapoAlDoubleCoda              = (wxByte)0x0b,
        dalSegnoAlCoda                  = (wxByte)0x0c,
        dalSegnoAlDoubleCoda            = (wxByte)0x0d,
        dalSegnoSegnoAlCoda             = (wxByte)0x0e,
        dalSegnoSegnoAlDoubleCoda       = (wxByte)0x0f,
        daCapoAlFine                    = (wxByte)0x10,
        dalSegnoAlFine                  = (wxByte)0x11,
        dalSegnoSegnoAlFine             = (wxByte)0x12
    };

    enum activeSymbols
    {
        activeNone                      = (wxByte)0x00,
        activeDaCapo                    = (wxByte)0x01,
        activeDalSegno                  = (wxByte)0x02,
        activeDalSegnoSegno             = (wxByte)0x03
    };

    enum flags
    {
        symbolTypeMask                  = (wxWord)0xff00,       ///< Mask used to retrieve the symbol type (coda, segno, etc.)
        activeSymbolMask                = (wxWord)0xc0,         ///< Mask used to retrieve the active symbol value
        repeatNumberMask                = (wxWord)0x3f,         ///< Mask used to retrieve the repeat number value
    };
    
protected:
    wxByte          m_position;         ///< Zero-based index of the position within the system where the direction is anchored
    wxWordArray     m_symbolArray;      ///< Array of direction symbols (symbol: top byte = symbol type, next 2 bits = active symbol, next 6 bits = repeat number)
    
public:
    // Constructor/Destructor
    Direction();
    Direction(wxUint32 position, wxByte symbolType, wxByte activeSymbol, wxByte repeatNumber);
    Direction(const Direction& direction);
    ~Direction();
    
    // Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                     
        {return (new Direction(*this));}
    
    // Operators
    const Direction& operator=(const Direction& direction);
    bool operator==(const Direction& direction) const;
    bool operator!=(const Direction& direction) const;

    // Serialization functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

public:
    // MFC Class Functions
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const                        
        {return (wxT("CDirection"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const                        
        {return ((wxWord)1);}
    
    // Position Functions
    /// Determines whether a position is valid
    /// @param position Position to validate
    /// @return True if the position is valid, false if not
    static bool IsValidPosition(wxUint32 position)
        {return ((position >= MIN_POSITION) && (position <= MAX_POSITION));}
    /// Sets the position within the system where the direction is anchored
    /// @param position Zero-based index within the system where the direction is anchored
    /// @return True if the position was set, false if not
    bool SetPosition(wxUint32 position)
        {wxCHECK(IsValidPosition(position), false); m_position = (wxByte)position; return (true);}
    /// Gets the position within the system where the direction is anchored
    /// @return The position within the system where the direction is anchored
    wxUint32 GetPosition() const                           
        {return (m_position);}
    
    /// Determines if a symbol type is valid
    /// @param symbolType Symbol type to validate
    /// @return True if the symbol is valid, false if not
    static bool IsValidSymbolType(wxByte symbolType)            
        {return (symbolType <= dalSegnoSegnoAlFine);}
    /// Determines if an active symbol is valid
    /// @param activeSymbol Active symbol to validate
    /// @return True if the active symbol is valid, false if not
    static bool IsValidActiveSymbol(wxByte activeSymbol)
        {return (activeSymbol <= activeDalSegnoSegno);}
    /// Determines if an repeat number is valid
    /// @param repeatNumber Repeat number to validate
    /// @return True if the repeat number is valid, false if not
    static bool IsValidRepeatNumber(wxByte repeatNumber)
        {return ((repeatNumber >= MIN_REPEAT_NUMBER) && (repeatNumber <= MAX_REPEAT_NUMBER));}
        
    // Symbol Array Functions
    /// Determines if a symbol index is valid
    /// @param index Index to validate
    /// @return True if the symbol index is valid, false if not
    bool IsValidSymbolIndex(wxUint32 index) const         
        {return (index < GetSymbolCount());}
    bool AddSymbol(wxByte symbolType, wxByte activeSymbol = activeNone, wxByte repeatNumber = 0);
    /// Gets the number of symbols in the symbol array
    /// @return The number of symbols in the symbol array
    size_t GetSymbolCount() const
        {return (m_symbolArray.GetCount());}
    bool SetSymbol(wxUint32 index, wxByte symbolType, wxByte activeSymbol, wxByte repeatNumber);
    bool GetSymbol(wxUint32 index, wxByte& symbolType, wxByte& activeSymbol, wxByte& repeatNumber) const;
    bool IsSymbolType(wxUint32 index, wxByte symbolType) const;
    bool RemoveSymbolAtIndex(wxUint32 index);
protected:
    void DeleteSymbolArrayContents();
    
    // Operations
public:
    wxString GetText(wxUint32 index) const;
};

WX_DEFINE_POWERTABARRAY(Direction*, DirectionArray);

#endif
