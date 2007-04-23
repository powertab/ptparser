/////////////////////////////////////////////////////////////////////////////
// Name:            system.cpp
// Purpose:         Stores and renders a system
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 16, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "system.h"

#include "powertabfileheader.h"                     // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Default Constants
const wxRect System::DEFAULT_RECT                                   = wxRect(0,0,0,0);
const wxByte System::DEFAULT_POSITION_SPACING                       = 20;
const wxByte System::DEFAULT_RHYTHM_SLASH_SPACING_ABOVE             = 0;
const wxByte System::DEFAULT_RHYTHM_SLASH_SPACING_BELOW             = 0;
const wxByte System::DEFAULT_EXTRA_SPACING                          = 0;
    
// Constructor/Destructor
/// Default Constructor
System::System() :
    m_rect(DEFAULT_RECT), m_positionSpacing(DEFAULT_POSITION_SPACING), 
    m_rhythmSlashSpacingAbove(DEFAULT_RHYTHM_SLASH_SPACING_ABOVE), 
    m_rhythmSlashSpacingBelow(DEFAULT_RHYTHM_SLASH_SPACING_BELOW),
    m_extraSpacing(DEFAULT_EXTRA_SPACING)
{
    //------Last Checked------//
    // - Jan 14, 2005
}

/// Copy Constructor
System::System(const System& system) :
    m_rect(DEFAULT_RECT), m_positionSpacing(DEFAULT_POSITION_SPACING), 
    m_rhythmSlashSpacingAbove(DEFAULT_RHYTHM_SLASH_SPACING_ABOVE), 
    m_rhythmSlashSpacingBelow(DEFAULT_RHYTHM_SLASH_SPACING_BELOW),
    m_extraSpacing(DEFAULT_EXTRA_SPACING)
{
    //------Last Checked------//
    // - Dec 16, 2004
    *this = system;
}

/// Destructor
System::~System()
{
    //------Last Checked------//
    // - Jan 14, 2005
    m_directionArray.DeleteContents();
    m_chordTextArray.DeleteContents();
    m_rhythmSlashArray.DeleteContents();
    m_staffArray.DeleteContents();
    m_barlineArray.DeleteContents();
}

/// Assignment Operator
const System& System::operator=(const System& system)
{	
    //------Last Checked------//
    // - Jan 14, 2005
    
    // Check for assignment to self
    if (this != &system)
    {
	    m_rect = system.m_rect;
	    m_positionSpacing = system.m_positionSpacing;
	    m_rhythmSlashSpacingAbove = system.m_rhythmSlashSpacingAbove;
	    m_rhythmSlashSpacingBelow = system.m_rhythmSlashSpacingBelow;
	    m_extraSpacing = system.m_extraSpacing;
	    m_startBar = system.m_startBar;
	    m_directionArray.Copy(system.m_directionArray);
	    m_chordTextArray.Copy(system.m_chordTextArray);
	    m_rhythmSlashArray.Copy(system.m_rhythmSlashArray);
	    m_staffArray.Copy(system.m_staffArray);
	    m_barlineArray.Copy(system.m_barlineArray);
        m_endBar = system.m_endBar;
    }
	return (*this);
}

/// Equality Operator
bool System::operator==(const System& system) const
{
    //------Last Checked------//
    // - Jan 14, 2005
    return (
        (m_rect == system.m_rect) &&
        (m_positionSpacing == system.m_positionSpacing) &&
        (m_rhythmSlashSpacingAbove == system.m_rhythmSlashSpacingAbove) &&
        (m_rhythmSlashSpacingBelow == system.m_rhythmSlashSpacingBelow) &&
        (m_extraSpacing == system.m_extraSpacing) &&
        (m_startBar == system.m_startBar) &&
        (m_directionArray.Equals(system.m_directionArray)) &&
        (m_chordTextArray.Equals(system.m_chordTextArray)) &&
        (m_rhythmSlashArray.Equals(system.m_rhythmSlashArray)) &&
        (m_staffArray.Equals(system.m_staffArray)) &&
        (m_barlineArray.Equals(system.m_barlineArray)) &&
        (m_endBar == system.m_endBar)
    );
}

/// Inequality Operator
bool System::operator!=(const System& system) const
{
    //------Last Checked------//
    // - Jan 5, 2005
    return (!operator==(system));
}
    
// Serialize Functions
/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool System::DoSerialize(PowerTabOutputStream& stream)
{
    //------Last Checked------//
    // - Jan 14, 2005
    stream.WriteMFCRect(m_rect);
    wxCHECK(stream.CheckState(), false);
    
    // Note: End bar is stored as a byte; we use Barline class to make it easier for the user
    wxByte endBar = (wxByte)((m_endBar.GetType() << 5) | (m_endBar.GetRepeatCount()));
    stream << endBar << m_positionSpacing << m_rhythmSlashSpacingAbove << m_rhythmSlashSpacingBelow << m_extraSpacing;
    wxCHECK(stream.CheckState(), false);
    
    m_startBar.Serialize(stream);
    wxCHECK(stream.CheckState(), false);

    m_directionArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_chordTextArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_rhythmSlashArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_staffArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_barlineArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);

    return (stream.CheckState());
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool System::DoDeserialize(PowerTabInputStream& stream, wxWord version)
{
    //------Last Checked------//
    // - Jan 14, 2005
    
    // Version 1.0 and 1.0.2
	if (version == PowerTabFileHeader::FILEVERSION_1_0 || version == PowerTabFileHeader::FILEVERSION_1_0_2)
	{
		wxByte key;
		wxWord endBar;

        stream.ReadMFCRect(m_rect);
        wxCHECK(stream.CheckState(), false);
                
		stream >> key >> endBar >> m_positionSpacing >> m_rhythmSlashSpacingAbove >> m_rhythmSlashSpacingBelow >> m_extraSpacing;
		wxCHECK(stream.CheckState(), false);

		// Update the key signature at start of section (always shown)
		wxByte keyType = (wxByte)((key >> 4) & 0xf);
		wxByte keyAccidentals = (wxByte)(key & 0xf);

        m_startBar.GetKeySignatureRef().Show();

		// Cancellation
		if (keyType > 2)
		    m_startBar.GetKeySignatureRef().SetCancellation();

		keyType = (wxByte)(((keyType % 2) == 1) ? KeySignature::majorKey : KeySignature::minorKey);

        m_startBar.GetKeySignatureRef().SetKey(keyType, keyAccidentals);

		// Update the ending bar
		wxByte barType = HIBYTE(endBar);
		wxByte repeatCount = LOBYTE(endBar);

        m_endBar.SetBarlineData(barType, repeatCount);
		//SetEndBar(barType, repeatCount);

        m_directionArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        m_chordTextArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        m_rhythmSlashArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        m_staffArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        m_barlineArray.Deserialize(stream, version);	
        wxCHECK(stream.CheckState(), false);

		// Any barline at position zero is now stored in the section m_startBar
		if (GetBarlineCount() > 0)
		{
		    Barline* barline = m_barlineArray[0];
	        if (barline != NULL)
	        {
	            if (barline->GetPosition() == 0)
	            {
		            m_startBar = *barline;
		            delete barline;
		            m_barlineArray.RemoveAt(0);
		        }
	        }
	    }

		// Update key signs that aren't show to match active key sign
		KeySignature* activeKeySignature = m_startBar.GetKeySignaturePtr();

        size_t i = 0;
        size_t count = m_barlineArray.GetCount();
        for (; i < count; i++)
		{
		    KeySignature& keySignature = m_barlineArray[i]->GetKeySignatureRef();
		    
			// Key on bar doesn't match active
		    if (keySignature != *activeKeySignature)
			{
				// Key isn't shown, update key to match
				if (!keySignature.IsShown())
				{
				    keySignature = *activeKeySignature;
				    keySignature.Hide();
				    keySignature.SetCancellation(false);
				}
				
				// Update active key
				activeKeySignature = m_barlineArray[i]->GetKeySignaturePtr();
			}
		}
	}
	// Version 1.5 and up
	else
	{
	    stream.ReadMFCRect(m_rect);
        wxCHECK(stream.CheckState(), false);
        
        wxByte endBar = 0;
        stream >> endBar >> m_positionSpacing >> m_rhythmSlashSpacingAbove >> m_rhythmSlashSpacingBelow >> m_extraSpacing;
        wxCHECK(stream.CheckState(), false);
        
        // Update end bar (using Barline class is easier to use)
        m_endBar.SetBarlineData((wxByte)((endBar & 0xe0) >> 5), (wxByte)(endBar & 0x1f));
        
        m_startBar.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);

        m_directionArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        m_chordTextArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        m_rhythmSlashArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        m_staffArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        m_barlineArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
	}
	    
    return (stream.CheckState());
}

// Barline Array Functions
/// Gets the barline at a given position
/// @param position Position to get the barline for
/// @return A pointer to the barline at the position, or NULL if the barline doesn't exist
Barline* System::GetBarlineAtPosition(wxUint32 position) const
{
    //------Last Checked------//
    // - Jan 26, 2005
    if (position == 0)
        return ((Barline*)&m_startBar);
    
    // Iterate through the barlines
    size_t barlineIndex = 0;
    size_t barlineCount = GetBarlineCount();
    for (; barlineIndex < barlineCount; barlineIndex++)
    {
        Barline* barline = GetBarline(barlineIndex);
        wxCHECK2(barline != NULL, continue);

        // Found it; return the barline        
        if (barline->GetPosition() == position)
            return (barline);
    }
 
    // Barline not found at position   
    return (NULL);
}

/// Gets a list of barlines in the system
/// @param barlineArray Holds the barline return values
void System::GetBarlines(BarlineArray& barlineArray)
{
    //------Last Checked------//
    // - Apr 25, 2006
    barlineArray.Empty();
    barlineArray.Add(&m_startBar);

    for (int barline = 0, barlineCount = m_barlineArray.GetCount();
        barline < barlineCount; ++barline)
    {
        barlineArray.Add(m_barlineArray[barline]);
    }

    barlineArray.Add(&m_endBar);
}
