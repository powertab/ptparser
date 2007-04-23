/////////////////////////////////////////////////////////////////////////////
// Name:            keysignature.h
// Purpose:         Stores and renders a key signature
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 10, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __KEYSIGNATURE_H__
#define __KEYSIGNATURE_H__

/// Stores and renders a key signature
class KeySignature : public PowerTabObject
{
friend class KeySignatureTestSuite;

// Constants
public:
    // Default constants
    static const wxByte         DEFAULT_DATA;       ///< Default value for the data member variable

    enum flags
    {
        keyAccidentalsMask      = (wxByte)0x0f,     ///< Bit mask used to retrieve the key accidentals value
        show                    = (wxByte)0x10,     ///< Key signature is shown
        cancellation            = (wxByte)0x20,     ///< Key signature is a cancellation
        keyTypeMask             = (wxByte)0x40      ///< Bit mask used to retrieve the key type value
    };

    enum keyTypes
    {
        majorKey                = (wxByte)0,        ///< Key signature is a major key type (i.e. C major)
        minorKey                = (wxByte)1         ///< Key signature is a minor key type (i.e. A minor)
    };
    
    enum keyAccidentals
    {
        noAccidentals           = (wxByte)0,        ///< Key signature uses no accidentals
        oneSharp                = (wxByte)1,        ///< Key signature uses 1 sharp
        twoSharps               = (wxByte)2,        ///< Key signature uses 2 sharps
        threeSharps             = (wxByte)3,        ///< Key signature uses 3 sharps
        fourSharps              = (wxByte)4,        ///< Key signature uses 4 sharps
        fiveSharps              = (wxByte)5,        ///< Key signature uses 5 sharps
        sixSharps               = (wxByte)6,        ///< Key signature uses 6 sharps
        sevenSharps             = (wxByte)7,        ///< Key signature uses 7 sharps
        oneFlat                 = (wxByte)8,        ///< Key signature uses 1 flat
        twoFlats                = (wxByte)9,        ///< Key signature uses 2 flats
        threeFlats              = (wxByte)10,       ///< Key signature uses 3 flats
        fourFlats               = (wxByte)11,       ///< Key signature uses 4 flats
        fiveFlats               = (wxByte)12,       ///< Key signature uses 5 flats
        sixFlats                = (wxByte)13,       ///< Key signature uses 6 flats
        sevenFlats              = (wxByte)14        ///< Key signature uses 7 flats
    };
        
// Member variables
protected:
    wxByte m_data;      ///< Stores all data required by the key signature (see the flags enum for the meaning of the individual bits)

public:
    // Constructor/Destructor
    KeySignature();
    KeySignature(wxByte keyType, wxByte keyAccidentals);
    KeySignature(const KeySignature& keySignature);
    ~KeySignature();

    // Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                         
        {return (new KeySignature(*this));}
    
    // Operators
    const KeySignature& operator=(const KeySignature& keySignature);
    bool operator==(const KeySignature& keySignature) const;
    bool operator!=(const KeySignature& keySignature) const;

    // MFC Class Functions
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const                            
        {return (wxT("CKeySignature"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const                            
        {return ((wxWord)1);}
    
    // Serialization Functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

public:
    // Key Functions
    bool SetKey(wxByte keyType, wxByte keyAccidentals);
    void GetKey(wxByte & keyType, wxByte & keyAccidentals) const;
    /// Determines if the key (type + accidentals) is the same as that of another KeySignature object
    /// @param keySignature KeySignature object to compare with
    /// @return True if the key signatures have the same key, false if not
    bool IsSameKey(const KeySignature& keySignature) const              
        {return ((GetKeyType() == keySignature.GetKeyType()) && (GetKeyAccidentals() == keySignature.GetKeyAccidentals()));}
    bool GetDrawKey(wxByte& keyType, wxByte& keyAccidentals) const;
    
    // Type Functions
    /// Deteremines if a key type is valid
    /// @param keyType The key type to validate
    /// @return True if the key type is valid, false if not
    static bool IsValidKeyType(wxByte keyType)                          
        {return ((keyType == majorKey) || (keyType == minorKey));}
    bool SetKeyType(wxByte keyType);
    /// Gets the key type for the key signature (majorKey vs minorKey)
    /// @return majorKey (see enum) if the key signature is a majorKey key, minorKey (see enum) if the key signature is a minorKey key
    wxByte GetKeyType() const                                           
        {return (wxByte)((m_data & keyTypeMask) >> 6);}
    /// Determines if the key signature is a majorKey key
    /// @return True if the key signature is a majorKey key, false if not
    bool IsMajorKey() const                                             
        {return (GetKeyType() == majorKey);}
    /// Determines if the key signature is a minorKey key
    /// @return True if the key signature is a minorKey key, false if not
    bool IsMinorKey() const                                             
        {return (GetKeyType() == minorKey);}
    
    // Accidentals Functions
    /// Determines if a key accidentals value is valid
    /// @param keyAccidentals Key accidentals value to validate
    /// @return True if the key accidentals value is validate, false if not
    static bool IsValidKeyAccidentals(wxByte keyAccidentals)            
        {return (keyAccidentals <= sevenFlats);}
    bool SetKeyAccidentals(wxByte keyAccidentals);
    wxByte GetKeyAccidentals() const;
    /// Determines if the key signature uses no accidentals
    /// @return True if the key signature uses no accidentals, false if not
    bool HasNoKeyAccidentals() const                                    
        {return (GetKeyAccidentals() == noAccidentals);}
    /// Determines if the key signature has one sharp
    /// @return True if the key signature has one sharp, false if not
    bool HasOneSharp() const                                            
        {return (GetKeyAccidentals() == oneSharp);}
    /// Determines if the key signature has two sharps
    /// @return True if the key signature has two sharps, false if not
    bool HasTwoSharps() const                                           
        {return (GetKeyAccidentals() == twoSharps);}
    /// Determines if the key signature has three sharps
    /// @return True if the key signature has three sharps, false if not
    bool HasThreeSharps() const                                         
        {return (GetKeyAccidentals() == threeSharps);}
    /// Determines if the key signature has four sharps
    /// @return True if the key signature has four sharps, false if not
    bool HasFourSharps() const                                          
        {return (GetKeyAccidentals() == fourSharps);}
    /// Determines if the key signature has five sharps
    /// @return True if the key signature has five sharps, false if not
    bool HasFiveSharps() const                                          
        {return (GetKeyAccidentals() == fiveSharps);}
    /// Determines if the key signature has six sharps
    /// @return True if the key signature has six sharps, false if not
    bool HasSixSharps() const                                           
        {return (GetKeyAccidentals() == sixSharps);}
    /// Determines if the key signature has seven sharps
    /// @return True if the key signature has seven sharps, false if not
    bool HasSevenSharps() const                                         
        {return (GetKeyAccidentals() == sevenSharps);}
    /// Determines if the key signature has one flat
    /// @return True if the key signature has one flat, false if not
    bool HasOneFlat() const                                             
        {return (GetKeyAccidentals() == oneFlat);}
    /// Determines if the key signature has two flats
    /// @return True if the key signature has two flats, false if not
    bool HasTwoFlats() const                                            
        {return (GetKeyAccidentals() == twoFlats);}
    /// Determines if the key signature has three flats
    /// @return True if the key signature has three flats, false if not
    bool HasThreeFlats() const                                          
        {return (GetKeyAccidentals() == threeFlats);}
    /// Determines if the key signature has four flats
    /// @return True if the key signature has four flats, false if not
    bool HasFourFlats() const                                           
        {return (GetKeyAccidentals() == fourFlats);}
    /// Determines if the key signature has five flats
    /// @return True if the key signature has five flats, false if not
    bool HasFiveFlats() const                                           
        {return (GetKeyAccidentals() == fiveFlats);}
    /// Determines if the key signature has six flats
    /// @return True if the key signature has six flats, false if not
    bool HasSixFlats() const                                            
        {return (GetKeyAccidentals() == sixFlats);}
    /// Determines if the key signature has seven flats
    /// @return True if the key signature has seven flats, false if not
    bool HasSevenFlats() const                                          
        {return (GetKeyAccidentals() == sevenFlats);}
    
    // Show/Hide Functions
    /// Makes the key signature visible
    void Show()                                                         
        {SetFlag(show);}
    /// Makes the key signature invisible
    void Hide()                                                         
        {ClearFlag(show);}
    /// Determines if the key signature is shown
    /// @return True if the key signature is shown, false if not
    bool IsShown() const                                                
        {return (IsFlagSet(show));}

    // Cancellation Functions
    /// Sets or clears the cancellation on a key signature
    /// @param set If true, makes the key signature a cancellation, otherwise clears the cancellation
    void SetCancellation(bool set = true)                               
        {if (set) SetFlag(cancellation); else ClearFlag(cancellation);}
    /// Determines if the key signature is a cancellation
    /// @return True if the key signature is a cancellation, false if not
    bool IsCancellation() const                                         
        {return (IsFlagSet(cancellation));}
        
    // Operations
    wxString GetText() const;

    // Flag Functions
protected:
    /// Determines if a flag is valid
    /// @param flag Flag to validate
    /// @return True if the flag is valid, false if not
    static bool IsValidFlag(wxByte flag)                                
        {return ((flag == show) || (flag == cancellation));}
    /// Sets a flag used by the KeySignature object
    /// @param flag The flag to set
    bool SetFlag(wxByte flag)                                           
        {wxCHECK(IsValidFlag(flag), false); m_data |= flag; return (true);}
    /// Clears a flag used by the KeySignature object
    /// @param flag The flag to clear
    bool ClearFlag(wxByte flag)                                         
        {wxCHECK(IsValidFlag(flag), false); m_data &= ~flag; return (true);}
    /// Determines if a flag used by the KeySignature object is set
    /// @param flag The flag to test
    /// @return True if the flag is set, false if not
    bool IsFlagSet(wxByte flag) const                                   
        {wxCHECK(IsValidFlag(flag), false); return ((m_data & flag) == flag);}
};

#endif
