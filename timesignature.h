/////////////////////////////////////////////////////////////////////////////
// Name:            timesignature.h
// Purpose:         Stores and renders time signatures
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 12, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __TIMESIGNATURE_H__
#define __TIMESIGNATURE_H__

/// Stores and renders time signatures
class TimeSignature : public PowerTabObject
{
friend class TimeSignatureTestSuite;

// Constants
public:
    // Default Constants
    static const wxUint32   DEFAULT_DATA;           ///< Default value for the data member variable
    static const wxByte     DEFAULT_PULSES;         ///< Default value for the pulses data member variable

    static const wxByte     MIN_BEATSPERMEASURE;    ///< Minimum allowed value for beats per measure
    static const wxByte     MAX_BEATSPERMEASURE;    ///< Maximum allowed value for beats per measure
    
    static const wxByte     MIN_BEATAMOUNT;         ///< Minimum allowed value for the beat amount
    static const wxByte     MAX_BEATAMOUNT;         ///< Maximum allowed value for the beat amount
    
    static const wxByte     MIN_PULSES;             ///< Minimum allowed value for pulses
    static const wxByte     MAX_PULSES;             ///< Maximum allowed value for pulses
        
    enum flags
    {
        meterMask                   = (wxUint32)0xff000000,     ///< Bit mask used to retrieve the meter
        beatsPerMeasureMask         = (wxUint32)0xf8000000,     ///< Bit mask used to retrieve the beats per measure value
        beatAmountMask              = (wxUint32)0x07000000,     ///< Bit mask used to retrieve the beat amount value
        beamingPatternMask          = (wxUint32)0xfffff,        ///< Bit mask used to retrieve the beaming pattern
        beamingPatternBeat1Mask     = (wxUint32)0xf8000,        ///< Bit mask used to retrieve beat 1 of the beaming pattern
        beamingPatternBeat2Mask     = (wxUint32)0x7c00,         ///< Bit mask used to retrieve beat 2 of the beaming pattern
        beamingPatternBeat3Mask     = (wxUint32)0x3e0,          ///< Bit mask used to retrieve beat 3 of the beaming pattern
        beamingPatternBeat4Mask     = (wxUint32)0x1f,           ///< Bit mask used to retrieve beat 4 of the beaming pattern
        show                        = (wxUint32)0x100000,       ///< Show the time signature
        brackets                    = (wxUint32)0x200000,       ///< Place brackets around the time signature
        commonTime                  = (wxUint32)0x400000,       ///< Use common time symbol
        cutTime                     = (wxUint32)0x800000        ///< Use cut time symbol
    };

    enum textFlags
    {
        textBeatsPerMeasure     = 0,                            ///< Numerator text
        textBeatAmount          = 1,                            ///< Denominator text
        textFull                = 2                             ///< Full fractional text 4/4
    };
    
protected:
    wxUint32    m_data;             ///< Stores the meter, beaming pattern and any flags (see flags enum for bit breakdown)
    wxByte      m_pulses;           ///< Number of pulses in a measure

public:
    // Constructor/Destructor
    TimeSignature();
    TimeSignature(wxByte beatsPerMeasure, wxByte beatAmount);
    TimeSignature(const TimeSignature& timeSignature);
    ~TimeSignature();

    // Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                         
        {return (new TimeSignature(*this));}
    
    // Operators
    const TimeSignature& operator=(const TimeSignature& timeSignature);
    bool operator==(const TimeSignature& timeSignature) const;
    bool operator!=(const TimeSignature& timeSignature) const;
    
    // MFC Class Functions
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const                            
        {return (wxT("CTimeSignature2"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const                            
        {return ((wxWord)1);}
    
    // Serialize Functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);
    
public:
    // Meter Functions
    bool SetMeter(wxByte beatsPerMeasure, wxByte beatAmount);
    void GetMeter(wxByte & beatsPerMeasure, wxByte & beatAmount) const;
    /// Determines if the meter is the same as that of another TimeSignature object
    /// @param timeSignature TimeSignature object to compare with
    /// @return True if the time signatures have the same meter, false if not
    bool IsSameMeter(const TimeSignature& timeSignature) const
        {return ((GetBeatsPerMeasure() == timeSignature.GetBeatsPerMeasure()) && (GetBeatAmount() == timeSignature.GetBeatAmount()));}
    // Sets the time signature to use the cut time symbol and meter
    void SetCutTime()                               
        {SetMeter(2,2); SetFlag(cutTime); /* note: Flag must be set after call to SetMeter, cause it clears both cut and common flags) */}
    /// Determines if the time signature is in cut time
    /// @return True if the time signature is in cut time, false if not
    bool IsCutTime() const                          
        {return (IsFlagSet(cutTime));}
    /// Sets the time signature to use common time symbol and meter
    void SetCommonTime()                            
        {SetMeter(4,4); SetFlag(commonTime); /* see note above */}
    /// Determines if the time signature is in common time
    /// @return True if the time signature is in common time, false if not
    bool IsCommonTime() const                       
        {return (IsFlagSet(commonTime));}
    bool IsCompoundTime() const;
    bool IsQuadrupleTime() const;
    wxUint32 GetBasicBeat() const;
    wxUint32 GetMeasureTotal() const;

    // Beats Per Measure Functions
    /// Determines if a beats per measure value is valid
    /// @param beatsPerMeasure Beats per measure value to validate
    /// @return True if the beats per measure value is valid, false if not
    static bool IsValidBeatsPerMeasure(wxByte beatsPerMeasure)      
        {return ((beatsPerMeasure >= MIN_BEATSPERMEASURE) && (beatsPerMeasure <= MAX_BEATSPERMEASURE));}
    bool SetBeatsPerMeasure(wxByte beatsPerMeasure);
    wxByte GetBeatsPerMeasure() const;
    
    // Beat Amount Functions
    /// Determines if a beat amount is valid
    /// @param beatAmount Beat amount to validate
    /// @return True if the beat amount is valid, false if not
    static bool IsValidBeatAmount(wxByte beatAmount)                
        {return ((beatAmount == 2) || (beatAmount == 4) || (beatAmount == 8) || (beatAmount == 16) || (beatAmount == 32));}
    bool SetBeatAmount(wxByte beatAmount);
    wxByte GetBeatAmount() const;
    
    // Beaming Pattern Functions
    /// Determines if a beaming pattern beat value is valid
    /// @param beat Beaming pattern beat value to validate
    /// @param beat1 True if the beat value is the first beat in the beaming pattern
    /// @return True if the beaming pattern beat value is valid, false if not
    static bool IsValidBeamingPatternBeat(wxByte beat, bool beat1)  
        {return ((beat <= MAX_BEATAMOUNT) && ((beat1) ? (beat > 0) : 1));}
    bool SetBeamingPattern(wxByte beat1, wxByte beat2 = 0, wxByte beat3 = 0, wxByte beat4 = 0);
    void GetBeamingPattern(wxByte & beat1, wxByte & beat2, wxByte & beat3, wxByte & beat4) const;
    bool SetBeamingPatternFromwxUint32(wxUint32 beamingPattern);
    wxUint32 GetBeamingPatternAswxUint32() const;

    // Show Functions
    /// Makes the time signature visible
    void Show()                                     
        {SetFlag(show);}
    /// Makes the time signature invisible
    void Hide()                                     
        {ClearFlag(show);}
    /// Determines if the time signature is shown
    /// @return True if the time signature is shown, false if not
    bool IsShown() const                            
        {return (IsFlagSet(show));}
        
    // Pulse Functions
    /// Determines if a pulses value is valid
    /// @param pulses Pulses value to validate
    /// @return True if the pulses value is valid, false if not
    static bool IsValidPulses(wxByte pulses)        
        {return ((pulses >= MIN_PULSES) && (pulses <= MAX_PULSES));}
    /// Sets the number of pulses in a measure
    /// @param pulses Number of pulses to set
    /// @return True if the pulses value was set, false if not
    bool SetPulses(wxByte pulses)                   
        {wxCHECK(IsValidPulses(pulses), false); m_pulses = pulses; return (true);}
    /// Gets the number of pulses in a measure
    /// @return The number of pulses in a measure
    wxByte GetPulses() const                        
        {return (m_pulses);}
    
    // Flag Functions
protected:
    /// Determines if a flag is valid
    /// @param flag Flag to validate
    /// @return True if the flag is valid, false if not
    static bool IsValidFlag(wxUint32 flag)          
        {return ((flag >= show) && (flag <= (show | brackets | commonTime | cutTime)));}
    bool SetFlag(wxUint32 flag);
    /// Clears a flag used by the TimeSignature object
    /// @param flag The flag to clear
    bool ClearFlag(wxUint32 flag)                   
        {wxCHECK(IsValidFlag(flag), false); m_data &= ~flag; return (true);}
    /// Determines if a flag used by the TimeSignature object is set
    /// @param flag The flag to test
    /// @return True if the flag is set, false if not
    bool IsFlagSet(wxUint32 flag) const             
        {wxCHECK(IsValidFlag(flag), false); return ((m_data & flag) == flag);}

    // Operations    
public:
    wxString GetText(wxUint32 type) const;
};

#endif
