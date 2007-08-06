/////////////////////////////////////////////////////////////////////////////
// Name:            tempomarker.h
// Purpose:         Stores and renders tempo markers
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 13, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __TEMPOMARKER_H__
#define __TEMPOMARKER_H__

#include "systemsymbol.h"

/// Stores and renders tempo markers
class TempoMarker : public SystemSymbol
{
friend class TempoMarkerTestSuite;

// Constants
public:
    // Default constants
    static const wxChar*        DEFAULT_DESCRIPTION;            ///< Default value for the description member variable
    static const wxByte         DEFAULT_BEAT_TYPE;              ///< Default value for the beat type value
    static const wxUint32       DEFAULT_BEATS_PER_MINUTE;       ///< Default value for the beats per minute value
    
    // Beats Per Minute Constants
    static const wxUint32       MIN_BEATS_PER_MINUTE;          ///< Minimum allowed value for the beats per minute
    static const wxUint32       MAX_BEATS_PER_MINUTE;          ///< Maximum allowed value for the beats per minute
    
    enum types
    {
        notShown                = (wxByte)0x00,         ///< Metronome marker is not shown
        standardMarker          = (wxByte)0x01,         ///< Standard beats per minute marker (i.e. quarter note = 120)
        listesso                = (wxByte)0x02,         ///< Listesso marker (i.e. quarter note = half note)
        alterationOfPace        = (wxByte)0x03          ///< Alteration of pace (accel. or rit.)
    };

	enum beatTypes
	{
		half						    = (wxByte)0x00,
		halfDotted				        = (wxByte)0x01,
		quarter					        = (wxByte)0x02,
		quarterDotted				    = (wxByte)0x03,
		eighth	    			        = (wxByte)0x04,
		eighthDotted			        = (wxByte)0x05,
		sixteenth				        = (wxByte)0x06,
		sixteenDotted			        = (wxByte)0x07,
		thirtySecond			        = (wxByte)0x08,
		thirtySecondDotted              = (wxByte)0x09
	};
	
    enum tripletFeelTypes
    {
        noTripletFeel                   = (wxByte)0x00,
        tripletFeelEighth               = (wxByte)0x01,
        tripletFeelSixteenth            = (wxByte)0x02,
        tripletFeelEighthOff            = (wxByte)0x03,
        tripletFeelSixteenthOff         = (wxByte)0x04
    };

    enum flags
    {
        beatsPerMinuteMask              = (wxUint32)0xffff,         ///< Mask used to retrieve the beats per minute value
        tripletFeelTypeMask             = (wxUint32)0x70000,        ///< Mask used to retrieve the triplet feel type
        listessoBeatTypeMask            = (wxUint32)0x780000,       ///< Mask used to retrieve the listesso beat type
        beatTypeMask                    = (wxUint32)0x7800000,      ///< Mask used to retrieve the beat type
        typeMask                        = (wxUint32)0x18000000      ///< Mask used to retrieve the tempo marker type
    };

// Member Variables
protected:
    wxString m_description;

// Constructor/Destructor
public:
    TempoMarker();
    TempoMarker(wxUint32 system, wxUint32 position, wxByte beatType,
        wxUint32 beatsPerMinute, const wxChar* description,
        wxByte tripletFeelType);
    TempoMarker(wxUint32 system, wxUint32 position, wxByte beatType,
        wxByte listessoBeatType, const wxChar* description);
    TempoMarker(wxUint32 system, wxUint32 position, bool accelerando);
    TempoMarker(const TempoMarker& tempoMarker);
    ~TempoMarker();

// Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                         
        {return (new TempoMarker(*this));}
    
// Operators
    const TempoMarker& operator=(const TempoMarker& tempoMarker);
    bool operator==(const TempoMarker& tempoMarker) const;
    bool operator!=(const TempoMarker& tempoMarker) const;

// Serialize Functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

// MFC Class Functions
public:
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const                            
        {return (wxT("CTempoMarker"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const                            
        {return ((wxWord)1);}
     
// Type Functions
    /// Determines if a type is valid
    /// @param type Type to validate
    /// @return True if the type is valid, false if not
    static bool IsValidType(wxByte type)
        {return (type <= alterationOfPace);}
    bool SetType(wxByte type);
    wxByte GetType() const;
    
    /// Determines if the metronome marker is shown
    /// @return True if the metronome marker is shown, false if not
    bool IsMetronomeMarkerShown() const     
        {return (GetType() != notShown);}
    
// Standard Marker Functions
    bool SetStandardMarker(wxByte beatType, wxUint32 beatsPerMinute,
        const wxChar* description, wxByte tripletFeelType = noTripletFeel);
    /// Determines if the tempo marker is a standard marker
    /// @return True if the tempo marker is a standard marker, false if not
    bool IsStandardMarker() const           
        {return (GetType() == standardMarker);}
    
// Listesso Functions
    bool SetListesso(wxByte beatType, wxByte listessoBeatType,
        const wxChar* description = wxT(""));
    /// Determines if the tempo marker is a listesso
    /// @return True if the tempo marker is a listesso, false if not
    bool IsListesso() const                 
        {return (GetType() == listesso);}
    
// Alteration Of Pace Functions
    /// Determines if the tempo marker is an alteration of pace
    /// @return True if the tempo marker is an alteration of pace, false if not
    bool IsAlterationOfPace() const               
        {return (GetType() == alterationOfPace);}
    bool SetAlterationOfPace(bool accelerando);
    /// Determines if the tempo marker is an accelerando marker
    /// @return True if the tempo marker is an accelerando marker, false if not
    bool IsAccelerando() const
        {return ((IsAlterationOfPace()) && (GetBeatType() == 0));}
    /// Determines if the tempo marker is a ritardando marker
    /// @return True if the tempo marker is a ritardando marker, false if not
    bool IsRitardando() const
        {return ((IsAlterationOfPace()) && (GetBeatType() == 1));}
    
// Beat Type Functions
    /// Determines if a beat type is valid
    /// @param beatType Beat type to validate
    /// @return True if the beat type is valid, false if not
    static bool IsValidBeatType(wxByte beatType)
        {return (beatType <= thirtySecondDotted);}        
    bool SetBeatType(wxByte beatType);
    wxByte GetBeatType() const;
                    
// Listesso Beat Type Functions
    bool SetListessoBeatType(wxByte beatType);
    wxByte GetListessoBeatType() const;
            
// Triplet Feel Functions
    /// Determines if a triplet feel type is valid
    /// @param tripletFeelType Triplet feel type to validate
    /// @return True if the triplet feel type is valid, false if not
    static bool IsValidTripletFeelType(wxByte tripletFeelType)
        {return (tripletFeelType <= tripletFeelSixteenthOff);}
    bool SetTripletFeelType(wxByte tripletFeelType);
    wxByte GetTripletFeelType() const;
    /// Determines if the tempo marker has a triplet feel effect
    /// @return True if the tempo marker has a triplet feel effect, false if not
    bool HasTripletFeel() const
        {return (GetTripletFeelType() != noTripletFeel);}
    
// Beats Per Minute Functions
    /// Determines if a beats per minute value is valid
    /// @param beatsPerMinute Beats per minute value to validate
    /// @return True if the beats per minute value is valid, false if not
    static bool IsValidBeatsPerMinute(wxUint32 beatsPerMinute)
    {
        return ((beatsPerMinute >= MIN_BEATS_PER_MINUTE) &&
            ((beatsPerMinute <= MAX_BEATS_PER_MINUTE)));
    }
    /// Sets the beats per minute
    /// @param beatsPerMinute Beats per minute value to set
    /// @return True if the beats per minute value was set, false if not
    bool SetBeatsPerMinute(wxUint32 beatsPerMinute);
    /// Gets the beats per minute
    /// @return The beats per minute
    wxUint32 GetBeatsPerMinute() const                     
        {return ((wxUint32)(m_data & beatsPerMinuteMask));}
    
// Description Functions
    /// Sets the description
    /// @param description Description to set
    /// @return True if the description was set, false if not
    bool SetDescription(const wxChar* description)      
    {
        wxCHECK(description != NULL, false);
        m_description = description;
        return (true);
    }
    /// Gets the description
    /// @return The description
    wxString GetDescription() const                     
        {return (m_description);}
};

WX_DEFINE_POWERTABARRAY(TempoMarker*, TempoMarkerArray);

#endif
