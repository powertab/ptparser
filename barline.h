/////////////////////////////////////////////////////////////////////////////
// Name:            barline.h
// Purpose:         Stores and renders barlines
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 4, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __BARLINE_H__
#define __BARLINE_H__

#include "rehearsalsign.h"
#include "timesignature.h"
#include "keysignature.h"

/// Stores and renders barlines
class Barline : public PowerTabObject
{
// Constants
public:
    // Default Constants
    static const wxByte DEFAULT_POSITION;           ///< Default value for the position member variable
    static const wxByte DEFAULT_DATA;               ///< Default value for the data member variable
    
    // Repeat Count Constants
    static const wxByte MIN_REPEAT_COUNT;           ///< Minimum allowed value for the repeat count
    static const wxByte MAX_REPEAT_COUNT;           ///< Maximum allowed value for the repeat count
    
    enum barTypes
    {
        bar                 = (wxByte)0,
        doubleBar           = (wxByte)1,
        freeTimeBar         = (wxByte)2,
        repeatStart         = (wxByte)3,
        openBar             = (wxByte)3,
        repeatEnd           = (wxByte)4,
        doubleBarFine       = (wxByte)5
    };
    
    enum flags
    {
        typeMask            = (wxByte)0xe0,         ///< Mask used to retrieve the type
        repeatCountMask     = (wxByte)0x1f          ///< Mask used to retrieve the repeat count
    };

protected:
    wxByte          m_position;                     ///< Zero-based index of the position within the system where the barline is anchored
    wxByte          m_data;                         ///< Top 3 bits = type, bottom 5 = repeat number

    KeySignature    m_keySignature;                 ///< Key signature
    TimeSignature   m_timeSignature;                ///< Time signature
    RehearsalSign   m_rehearsalSign;                ///< Rehearsal sign

public:
    // Constructor/Destructor
    Barline();
    Barline(wxUint32 position, wxByte type, wxByte repeatCount = 0);
    Barline(const Barline& barline);
    ~Barline();

    // Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                         
        {return (new Barline(*this));}
        
    // Operators
    const Barline& operator=(const Barline& barline);
    bool operator==(const Barline& barline) const;
    bool operator!=(const Barline& barline) const;

    // Serialization Functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

public:
    // MFC Class Functions
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const                            
        {return (wxT("CMusicBar"));}
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
    /// Sets the position within the system where the barline is anchored
    /// @param position Zero-based index within the system where the barline is anchored
    /// @return True if the position was set, false if not
    bool SetPosition(wxUint32 position)                         
        {wxCHECK(IsValidPosition(position), false); m_position = (wxByte)position; return (true);}
    /// Gets the position within the system where the barline is anchored
    /// @return The position within the system where the barline is anchored
    wxUint32 GetPosition() const                                
        {return (m_position);}
   
    // Barline Data Functions
    bool SetBarlineData(wxByte type, wxByte repeatCount);
    void GetBarlineData(wxByte& type, wxByte& repeatCount) const;
     
    // Type Functions
    /// Determines if a type is valid
    /// @param type Type to validate
    /// @return True if the type is valid, false if not
    static bool IsValidType(wxByte type)                        
        {return (type <= doubleBarFine);}
    bool SetType(wxByte type);
    /// Gets the type of barline (see barTypes enum for values)
    /// @return The type of barline
    wxByte GetType() const                                      
        {return ((wxByte)((m_data & typeMask) >> 5));}
    /// Determines if the barline type is a standard bar
    /// @return True if the barline type is a standard bar, false if not
    bool IsBar() const                                          
        {return (GetType() == bar);}
    /// Determines if the barline type is a double bar
    /// @return True if the barline type is a double bar, false if not
    bool IsDoubleBar() const                                    
        {return (GetType() == doubleBar);}
    /// Determines if the barline type is a freetime bar
    /// @return True if the barline type is a freetime bar, false if not
    bool IsFreeTimeBar() const                                  
        {return (GetType() == freeTimeBar);}
    /// Determines if the barline type is a repeat start bar
    /// @return True if the barline type is a repeat start bar, false if not
    bool IsRepeatStart() const                                  
        {return (GetType() == repeatStart);}
    /// Determines if the barline type is a repeat end bar
    /// @return True if the barline type is a repeat end bar, false if not
    bool IsRepeatEnd() const                                    
        {return (GetType() == repeatEnd);}
    /// Determines if the barline type is a double bar (fine) bar
    /// @return True if the barline type is a double bar (fine) bar, false if not
    bool IsDoubleBarFine() const                                
        {return (GetType() == doubleBarFine);}
    
    // Repeat Count Functions
    /// Determines if a repeat count is valid
    /// @param repeatCount Repeat count to validate
    /// @return True if the repeat count is valid, false if not
    static bool IsValidRepeatCount(wxUint32 repeatCount)        
        {return (((repeatCount >= MIN_REPEAT_COUNT) && (repeatCount <= MAX_REPEAT_COUNT)) || (repeatCount == 0));}
    bool SetRepeatCount(wxUint32 repeatCount);
    /// Gets the repeat count (used by repeat end bars)
    /// @return The repeat count
    wxUint32 GetRepeatCount() const                             
        {return ((wxUint32)(m_data & repeatCountMask));}
   
    // Key Signature Functions
    /// Sets the key signature
    void SetKeySignature(const KeySignature& keySignature)      
        {m_keySignature = keySignature;}
    /// Gets the key signature
    /// @return The key signature
    KeySignature GetKeySignature() const                        
        {return (m_keySignature);}
    /// Gets a reference to the key signature
    /// @return A reference to the key signature
    KeySignature& GetKeySignatureRef()                          
        {return (m_keySignature);}
    /// Gets a constant reference to the key signature
    /// @return A constant reference to the key signature
    const KeySignature& GetKeySignatureConstRef() const         
        {return (m_keySignature);}
    /// Gets a pointer to the key signature
    /// @return A pointer to the key signature
    KeySignature* GetKeySignaturePtr()                          
        {return (&m_keySignature);}
    
    // Time Signature Functions
    /// Sets the time signature
    void SetTimeSignature(const TimeSignature& timeSignature)   
        {m_timeSignature = timeSignature;}
    /// Gets the time signature
    /// @return The time signature
    TimeSignature GetTimeSignature() const                      
        {return (m_timeSignature);}
    /// Gets a reference to the time signature
    /// @return A reference to the time signature
    TimeSignature& GetTimeSignatureRef()                        
        {return (m_timeSignature);}
    /// Gets a constant reference to the time signature
    /// @return A constant reference to the time signature
    const TimeSignature& GetTimeSignatureConstRef() const       
        {return (m_timeSignature);}
    /// Gets a pointer to the time signature
    /// @return A pointer to the time signature
    TimeSignature* GetTimeSignaturePtr()                        
        {return (&m_timeSignature);}
    
    // Rehearsal Sign Functions
    /// Sets the rehearsal sign
    void SetRehearsalSign(const RehearsalSign& rehearsalSign)   
        {m_rehearsalSign = rehearsalSign;}
    /// Gets the rehearsal sign
    /// @return The rehearsal sign
    RehearsalSign GetRehearsalSign() const                      
        {return (m_rehearsalSign);}
    /// Gets a reference to the rehearsal sign
    /// @return A reference to the rehearsal sign
    RehearsalSign& GetRehearsalSignRef()                        
        {return (m_rehearsalSign);}
    /// Gets a constant reference to the rehearsal sign
    /// @return A constant reference to the rehearsal sign
    const RehearsalSign& GetRehearsalSignConstRef() const       
        {return (m_rehearsalSign);}
    /// Gets a pointer to the rehearsal sign
    /// @return A pointer to the rehearsal sign
    RehearsalSign* GetRehearsalSignPtr()                        
        {return (&m_rehearsalSign);}
};

WX_DEFINE_POWERTABARRAY(Barline*, BarlineArray);

#endif
