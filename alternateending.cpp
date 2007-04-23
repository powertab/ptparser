/////////////////////////////////////////////////////////////////////////////
// Name:            alternateending.cpp
// Purpose:         Stores and renders alternate ending symbols
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 3, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "alternateending.h"

#include <math.h>               // Needed for pow function

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Constructor/Destructor
/// Default Constructor
AlternateEnding::AlternateEnding()
{
    //------Last Checked------//
    // - Dec 4, 2004
}

/// Primary Constructor
/// @param system Zero-based index of the system where the alternate ending is anchored
/// @param position Zero-based index of the position within the system where the alternate ending is anchored
/// @param numbers Bits indicating which numbers are to be set (1st bit = 1., 2nd bit = 2., etc.)
AlternateEnding::AlternateEnding(wxUint32 system, wxUint32 position, wxWord numbers)
{
    //------Last Checked------//
    // - Dec 4, 2004
    SetSystem(system);
    SetPosition(position);
    SetNumbers(numbers);
}

/// Copy Constructor
AlternateEnding::AlternateEnding(const AlternateEnding& alternateEnding)
{
    //------Last Checked------//
    // - Dec 3, 2004
    *this = alternateEnding;
}

/// Destructor
AlternateEnding::~AlternateEnding()
{
    //------Last Checked------//
    // - Dec 3, 2004
}

// Operators
/// Assignment Operator
const AlternateEnding& AlternateEnding::operator=(const AlternateEnding& alternateEnding)
{
    //------Last Checked------//
    // - Dec 3, 2004
    
    // Check for assignment to self
    if (this != &alternateEnding)
        SystemSymbol::operator=(alternateEnding);
    return (*this);
}

/// Equality Operator
bool AlternateEnding::operator==(const AlternateEnding& alternateEnding) const
{
    //------Last Checked------//
    // - Jan 12, 2005
    return (SystemSymbol::operator==(alternateEnding));
}

/// Inequality Operator
bool AlternateEnding::operator!=(const AlternateEnding& alternateEnding) const
{
    //------Last Checked------//
    // - Jan 5, 2005
    return (!operator==(alternateEnding));
}
    
// Serialize Functions
/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool AlternateEnding::DoSerialize(PowerTabOutputStream& stream)
{
    //------Last Checked------//
    // - Dec 27, 2004
    return (SystemSymbol::DoSerialize(stream));
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool AlternateEnding::DoDeserialize(PowerTabInputStream& stream, wxWord version)
{
    //------Last Checked------//
    // - Dec 27, 2004
    return (SystemSymbol::DoDeserialize(stream, version));
}

// Number Functions
/// Sets the numbers using a bit map
/// @param numbers Bit map of the numbers to set (bit 0 = 1, bit 1 = 2, bit 2 = 3, etc.)
/// @return True if the numbers were set, false if not
bool AlternateEnding::SetNumbers(wxWord numbers)
{
    //------Last Checked------//
    // - Jan 12, 2005
    wxCHECK(IsValidNumbers(numbers), false);
    m_data = MAKELONG(0, numbers);
    return (true);
}

/// Gets a bit map representing the numbers
/// @return Bit map representing the numbers
wxWord AlternateEnding::GetNumbers() const
{
    //------Last Checked------//
    // - Jan 12, 2005
    return (HIWORD(m_data));
}
        
/// Sets a number
/// @param number The number to set (one based)
/// @return True if the number was set, false if not
bool AlternateEnding::SetNumber(wxUint32 number)
{
    //------Last Checked------//
    // - Jan 12, 2005
    wxCHECK(IsValidNumber(number), false);
    
    // Note: Numbers are stored in zero-based form
    wxWord numbers = GetNumbers();
    numbers |= (wxWord)(pow((double)2, (double)(number - 1)));
    
    return (SetNumbers(numbers));
}

/// Determines if a number is set
/// @param number A one-based index of the number to test
/// @return True if the number is set, false if not
bool AlternateEnding::IsNumberSet(wxUint32 number) const
{
    //------Last Checked------//
    // - Jan 12, 2005
    wxCHECK(IsValidNumber(number), false);

    // Number is one based, so subtract one
    number--;

    // Determine if bit is set
    wxWord numbers = GetNumbers();
    wxWord power = (wxWord)pow((double)2, (double)number);
    return ((numbers & power) == power);
}

/// Clears a number
/// @param number The number to clear (one based)
/// @return True if the number was cleared, false if not
bool AlternateEnding::ClearNumber(wxUint32 number)
{
    //------Last Checked------//
    // - Jan 12, 2005
    wxCHECK(IsValidNumber(number), false);
    
    wxWord numbers = GetNumbers(); 
    numbers &= ~(wxWord)(pow((double)2, (double)(number - 1)));
    SetNumbers(numbers);
    return (true);
}

/// Gets the alternate ending text (numbers + D.C./D.S./D.S.S.)
/// @return Text representation of the alternate ending
wxString AlternateEnding::GetText() const
{
    //------Last Checked------//
    // - Dec 3, 2004
	wxString returnValue;

    wxInt32 groupStart = -1;
    wxInt32 groupEnd = -1;
        
	// Construct the numbers
	wxUint32 i = 1;
	wxUint32 lastNumber = 8;
	for (; i <= lastNumber; i++)
	{
		bool numberSet = IsNumberSet(i);

		if (numberSet)
		{
		    // Starting a new group of numbers
			if (groupStart == -1)
				groupStart = groupEnd = i;
            // Continuing existing group
			else
				groupEnd = i;
		}
		
		// Always treat the last number like the end of a group
		if (i == lastNumber)
			numberSet = false;

		// We've reached the end of a group, if groupStart != -1, then we have a group
		if (!numberSet && groupStart != -1)
		{
		    // Add a separator
		    if (!returnValue.IsEmpty())
                returnValue += wxT(", ");
                
			wxString temp;

			// Single number
			if (groupStart == groupEnd)
				temp = wxString::Format(wxT("%s."), GetNumberText(groupStart).c_str());
			// 2 numbers
			else if (groupStart == (groupEnd - 1))
				temp = wxString::Format(wxT("%s., %s."), GetNumberText(groupStart).c_str(), GetNumberText(groupEnd).c_str());
			// > 2 numbers
			else 
				temp = wxString::Format(wxT("%s.-%s."), GetNumberText(groupStart).c_str(), GetNumberText(groupEnd).c_str());
			    
			returnValue += temp;
                
			// Reset the group data
			groupStart = groupEnd = -1;
		}
	}
	
	// Construct the special symbols
	i = daCapo;
	for (; i <= dalSegnoSegno; i++)
	{
	    if (IsNumberSet(i))
	    {
	        if (!returnValue.IsEmpty())
	            returnValue += wxT(", ");
	        returnValue += GetNumberText(i).c_str();
	    }
	}

	return (returnValue);
}

/// Gets the text for a number
/// @param number Number to get the text for (one based)
/// @return Text representation of the number
wxString AlternateEnding::GetNumberText(wxUint32 number)
{
    //------Last Checked------//
    // - Dec 3, 2004
    wxCHECK(IsValidNumber(number), wxT(""));
    
    if (number == daCapo)
        return wxT("D.C.");
    else if (number == dalSegno)
        return wxT("D.S.");
    else if (number == dalSegnoSegno)
        return wxT("D.S.S.");
    return (wxString::Format(wxT("%d"), number));
}
