/////////////////////////////////////////////////////////////////////////////
// Name:            alternateending.h
// Purpose:         Stores and renders alternate ending symbols
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 3, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __ALTERNATEENDING_H__
#define __ALTERNATEENDING_H__

#include "systemsymbol.h"

/// Stores and renders alternate ending symbols
class AlternateEnding : public SystemSymbol
{
friend class AlternateEndingTestSuite;

// Constants
public:
    enum alternateEndingFlags
    {
        daCapo              =   (wxWord)9,
        dalSegno            =   (wxWord)10,
        dalSegnoSegno       =   (wxWord)11,
        numbersMask         =   (wxWord)0x7ff           ///< Mask used to retrieve all allowable numbers
    };
    
public:
    // Constructor/Destructor
    AlternateEnding();
    AlternateEnding(wxUint32 system, wxUint32 position, wxWord numbers);
    AlternateEnding(const AlternateEnding& alternateEnding);
    ~AlternateEnding();
   
    // Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                         
        {return (new AlternateEnding(*this));}
   
    // Operators
    const AlternateEnding& operator=(const AlternateEnding& alternateEnding);
    bool operator==(const AlternateEnding& alternateEnding) const;
    bool operator!=(const AlternateEnding& alternateEnding) const;
    
    // Serialization Functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

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
    
    // Number Functions
    /// Deteremines if a numbers bit map is valid
    /// @param numbers Numbers bit map to validate
    /// @return True if the numbers bit map is valid, false if not
    static bool IsValidNumbers(wxWord numbers)
        {return ((numbers == 0) || (((numbers & numbersMask) != 0) && ((numbers & ~numbersMask) == 0)));}
    /// Determines if a number is valid
    /// @param number Number to validate
    /// @return True if the number is valid, false if not
    static bool IsValidNumber(wxUint32 number)
        {return ((number >= 1) && (number <= dalSegnoSegno));}
    bool SetNumbers(wxWord numbers);
    wxWord GetNumbers() const;
    bool SetNumber(wxUint32 number);
    bool IsNumberSet(wxUint32 number) const;
    bool ClearNumber(wxUint32 number);
    
    // Da Capo Functions
    void SetDaCapo()                                            
        {SetNumber(daCapo);}
    bool IsDaCapoSet() const                                    
        {return (IsNumberSet(daCapo));}
    void ClearDaCapo()                                          
        {ClearNumber(daCapo);}
    
    // Dal Segno Functions
    void SetDalSegno()                                          
        {SetNumber(dalSegno);}
    bool IsDalSegnoSet() const                                  
        {return (IsNumberSet(dalSegno));}
    void ClearDalSegno()                                        
        {ClearNumber(dalSegno);}
    
    // Dal Segno Segno Functions
    void SetDalSegnoSegno()
        {SetNumber(dalSegnoSegno);}
    bool IsDalSegnoSegnoSet() const
        {return (IsNumberSet(dalSegnoSegno));}
    void ClearDalSegnoSegno()
        {ClearNumber(dalSegnoSegno);}
    
    // Operations
    wxString GetText() const;
protected:
    static wxString GetNumberText(wxUint32 number);
};

WX_DEFINE_POWERTABARRAY(AlternateEnding*, AlternateEndingArray);

#endif
