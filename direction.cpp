/////////////////////////////////////////////////////////////////////////////
// Name:            direction.cpp
// Purpose:         Stores and renders directions
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 12, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "direction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Default constants
const wxByte        Direction::DEFAULT_POSITION                 = 0;

// Position Constants
const wxUint32      Direction::MIN_POSITION                     = 0;
const wxUint32      Direction::MAX_POSITION                     = 255;

// Symbol Constants
const wxByte        Direction::MAX_SYMBOLS                      = 3;
const wxByte        Direction::NUM_SYMBOL_TYPES                 = 19;

// Repeat Number Constants
const wxByte        Direction::MIN_REPEAT_NUMBER                = 0;
const wxByte        Direction::MAX_REPEAT_NUMBER                = 24;

static wxChar* directionText[Direction::NUM_SYMBOL_TYPES] = 
{
    wxT("Coda"), wxT("Double Coda"), wxT("Segno"), wxT("Segno Segno"),
    wxT("Fine"), wxT("D.C."), wxT("D.S."), wxT("D.S.S."), wxT("To Coda"),
    wxT("To Dbl. Coda"), wxT("D.C. al Coda"), wxT("D.C. al Dbl. Coda"),
    wxT("D.S. al Coda"), wxT("D.S. al Dbl. Coda"), wxT("D.S.S. al Coda"),
    wxT("D.S.S. al Dbl. Coda"), wxT("D.C. al Fine"), wxT("D.S. al Fine"),
    wxT("D.S.S. al Fine")
};

// Constructor/Destructor
/// Default Constructor
Direction::Direction() : 
    m_position(DEFAULT_POSITION)
{
    //------Last Checked------//
    // - Jan 11, 2005
}

/// Primary Constructor
/// @param position Zero-based index of the position within the system where the
/// barline is anchored
/// @param symbolType Type of symbol to add (see symbolTypes enum for values)
/// @param activeSymbol Symbol that must be active for the symbol to be
/// triggered (see activeSymbols enum for values)
/// @param repeatNumber Repeat number that must be active for the symbol to be
/// triggered (0 = none)
Direction::Direction(wxUint32 position, wxByte symbolType, wxByte activeSymbol,
    wxByte repeatNumber) : m_position(position)
{
    //------Last Checked------//
    // - Jan 11, 2005
    wxASSERT(IsValidPosition(position));
    AddSymbol(symbolType, activeSymbol, repeatNumber);   
}

/// Copy constructor
Direction::Direction(const Direction& direction) :
    m_position(DEFAULT_POSITION)
{
    //------Last Checked------//
    // - Jan 11, 2005
    *this = direction;
}

/// Destructor
Direction::~Direction()
{
    //------Last Checked------//
    // - Jan 11, 2005
    DeleteSymbolArrayContents();
}

/// Assignment Operator
const Direction& Direction::operator=(const Direction& direction)
{
    //------Last Checked------//
    // - Jan 11, 2005

    // Check for assignment to self
    if (this != &direction)
    {
        m_position = direction.m_position;
    
        DeleteSymbolArrayContents();
        
        size_t i = 0;
        size_t count = direction.m_symbolArray.GetCount();
        for (; i < count; i++)
            m_symbolArray.Add(direction.m_symbolArray[i]);
    }
    return (*this);
}

/// Equality Operator
bool Direction::operator==(const Direction& direction) const
{
    //------Last Checked------//
    // - Jan 11, 2005
    
    size_t thisSymbolCount = GetSymbolCount();
    size_t otherSymbolCount = direction.GetSymbolCount();
    
    // Directions have differing number of symbols
    if (thisSymbolCount != otherSymbolCount)
        return (false);

    // All symbols must match
    size_t i = 0;
    for (; i < thisSymbolCount; i++)
    {
        if (m_symbolArray[i] != direction.m_symbolArray[i])
            return (false);
    }

    return (m_position == direction.m_position);
}

/// Inequality Operator
bool Direction::operator!=(const Direction& direction) const
{
    //------Last Checked------//
    // - Jan 5, 2005
    return (!operator==(direction));
}

// Serialize Functions
/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool Direction::DoSerialize(PowerTabOutputStream& stream)
{
    //------Last Checked------//
    // - Jan 11, 2005
    stream << m_position;
    wxCHECK(stream.CheckState(), false);
           
    size_t symbolCount = GetSymbolCount();
    stream << (wxByte)symbolCount;
    wxCHECK(stream.CheckState(), false);

    size_t i = 0;
    for (; i < symbolCount; i++)
    {
        stream << m_symbolArray[i];
        wxCHECK(stream.CheckState(), false);
    }

    return (stream.CheckState());
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool Direction::DoDeserialize(PowerTabInputStream& stream,
    wxWord WXUNUSED(version))
{
    //------Last Checked------//
    // - Apr 22, 2007
    stream >> m_position;
    wxCHECK(stream.CheckState(), false);
    
    wxByte symbolCount;
    stream >> symbolCount;
    wxCHECK(stream.CheckState(), false);

    size_t i = 0;
    for (i = 0; i < symbolCount; i++)
    {
        wxWord symbol = 0;
        stream >> symbol;
        wxCHECK(stream.CheckState(), false);
        
        m_symbolArray.Add(symbol);
    }

    return (stream.CheckState());
}

// Symbol Functions
/// Adds a symbol to the symbol array
/// @param symbolType Type of symbol to add (see symbolTypes enum for values)
/// @param activeSymbol Symbol that must be active for the symbol to be
/// triggered (see activeSymbols enum for values)
/// @param repeatNumber Repeat number that must be active for the symbol to be
/// triggered (0 = none)
/// @return True if the symbol was added, false if not
bool Direction::AddSymbol(wxByte symbolType, wxByte activeSymbol,
    wxByte repeatNumber)
{
    //------Last Checked------//
    // - Jan 11, 2005
    wxCHECK(IsValidSymbolType(symbolType), false);
    wxCHECK(IsValidActiveSymbol(activeSymbol), false);
    wxCHECK(IsValidRepeatNumber(repeatNumber), false);
    
    // Can't add anymore symbols
    if (GetSymbolCount() == MAX_SYMBOLS)
        return (false);

    // Add a symbol to the end of the array, then set the data    
    m_symbolArray.Add(0);
    return (SetSymbol(GetSymbolCount() - 1, symbolType, activeSymbol,
        repeatNumber));
}

/// Sets the data for an existing symbol in the symbol array
/// @param index Index of the symbol to set the data for
/// @param symbolType Type of symbol (see symbolTypes enum for values)
/// @param activeSymbol Symbol that must be active for the symbol to be
/// triggered (see activeSymbols enum for values)
/// @param repeatNumber Repeat number that must be active for the symbol to be
/// triggered (0 = none)
/// @return True if the symbol data was set, false if not
bool Direction::SetSymbol(wxUint32 index, wxByte symbolType,
    wxByte activeSymbol, wxByte repeatNumber)
{
    //------Last Checked------//
    // - Jan 11, 2005
    wxCHECK(IsValidSymbolIndex(index), false);
    wxCHECK(IsValidSymbolType(symbolType), false);
    wxCHECK(IsValidActiveSymbol(activeSymbol), false);
    wxCHECK(IsValidRepeatNumber(repeatNumber), false);
    
    wxWord symbol = (wxWord)(symbolType << 8);
    symbol |= (wxWord)(activeSymbol << 6);
    symbol |= (wxWord)repeatNumber;
   
    m_symbolArray[index] = symbol;
    
    return (true);
}

/// Gets the symbol stored in the nth index of the symbol array
/// @param index Index of the symbol to get
/// @param symbolType Holds the symbol type return value
/// @param activeSymbol Holds the active symbol return value
/// @param repeatNumber Holds the repeat number return value
/// @return True if the direction data was retrieved, false if not
bool Direction::GetSymbol(wxUint32 index, wxByte& symbolType,
    wxByte& activeSymbol, wxByte& repeatNumber) const
{
    //------Last Checked------//
    // - Jan 11, 2005
    wxCHECK(IsValidSymbolIndex(index), false);
   
    symbolType = activeSymbol = repeatNumber = 0;
    
    symbolType = (wxByte)((m_symbolArray[index] & symbolTypeMask) >> 8);
    activeSymbol = (wxByte)((m_symbolArray[index] & activeSymbolMask) >> 6);
    repeatNumber = (wxByte)(m_symbolArray[index] & repeatNumberMask);
    
    return (true);
}

/// Determines if a symbol in the symbol array is a given type
/// @param index Index of the symbol
/// @param symbolType Type of symbol to test against
/// @return True if the symbol is of the type, false if not
bool Direction::IsSymbolType(wxUint32 index, wxByte symbolType) const
{
    //------Last Checked------//
    // - Jan 11, 2005
    wxCHECK(IsValidSymbolIndex(index), false);
    wxCHECK(IsValidSymbolType(symbolType), false);
    
    wxByte type = 0;
    wxByte activeSymbol = 0;
    wxByte repeatNumber = 0;
    if (!GetSymbol(index, type, activeSymbol, repeatNumber))
        return (false);
        
    return (type == symbolType);
}

/// Removes a symbol from the symbol array
/// @param index Index of the symbol to remove
/// @return True if the symbol was removed, false if not
bool Direction::RemoveSymbolAtIndex(wxUint32 index)
{
    //------Last Checked------//
    // - Jan 11, 2005
    wxCHECK(IsValidSymbolIndex(index), false);
 
    m_symbolArray.RemoveAt(index);
    
    return (true);
}

/// Deletes the contents (and frees the memory) of the symbol array
void Direction::DeleteSymbolArrayContents()
{
    //------Last Checked------//
    // - Jan 11, 2005
    m_symbolArray.Clear();
}

/// Gets a text representation of a symbol
/// @param index Index of the symbol to get the text for
/// @return Text representation of the symbol
wxString Direction::GetText(wxUint32 index) const
{
    //------Last Checked------//
    // - Jan 11, 2005
    wxByte symbolType = 0;
    wxByte activeSymbol = 0;
    wxByte repeatNumber = 0;
    if (!GetSymbol(index, symbolType, activeSymbol, repeatNumber))
        return (wxT(""));

    wxCHECK(IsValidSymbolType(symbolType), wxT(""));
    
    return (directionText[symbolType]);
}
