/////////////////////////////////////////////////////////////////////////////
// Name:            powertabdocument.cpp
// Purpose:         Loads and saves Power Tab files (.ptb)
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 29, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "powertabdocument.h"

#include "powertabinputstream.h"
#include "powertabstream.h"
#include <math.h>                   // Needed for pow

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(PowerTabDocument, wxDocument)

// Default Constants
const wxInt32   PowerTabDocument::DEFAULT_TABLATURE_STAFF_LINE_SPACING      = 9;
const wxUint32  PowerTabDocument::DEFAULT_FADE_IN                           = 0;
const wxUint32  PowerTabDocument::DEFAULT_FADE_OUT                          = 0;

// Tablature Staff Line Spacing Constants
const wxInt32   PowerTabDocument::MIN_TABLATURE_STAFF_LINE_SPACING          = 6;
const wxInt32   PowerTabDocument::MAX_TABLATURE_STAFF_LINE_SPACING          = 14;

// Score Constants
const wxByte    PowerTabDocument::NUM_SCORES                                = 2;
const wxByte    PowerTabDocument::GUITAR_SCORE                              = 0;
const wxByte    PowerTabDocument::BASS_SCORE                                = 1;

// Guitar Constants
const wxByte    PowerTabDocument::MAX_GUITARS                               = 7;
    
// Constructor/Destructor
/// Default Constructor
PowerTabDocument::PowerTabDocument() :
    m_tablatureStaffLineSpacing(DEFAULT_TABLATURE_STAFF_LINE_SPACING), m_fadeIn(DEFAULT_FADE_IN), m_fadeOut(DEFAULT_FADE_OUT)
{
    //------Last Checked------//
    // - Jan 26, 2005
}

/// Destructor
PowerTabDocument::~PowerTabDocument()
{
    //------Last Checked------//
    // - Jan 26, 2005
    DeleteContents();
}

// Save Functions
/// Serializes the document to an output stream (in v1.7 format)
/// @param stream Output stream to save to
/// @return The output stream
wxOutputStream& PowerTabDocument::SaveObject(wxOutputStream& stream)
{
    //------Last Checked------//
    // - Jan 26, 2005
    
    // Create our special Power Tab stream
    PowerTabOutputStream data_stream(stream);
    
    // Write the header
    m_header.Serialize(data_stream);
    if (!data_stream.CheckState())
    {
        DisplaySerializationError(GetFilename(), stream.TellO(), data_stream.GetLastErrorMessage());
        return (stream);
    }
    
    // Write the scores
    size_t i = 0;
    size_t count = m_scoreArray.GetCount();
    for (; i < count; i++)
    {
        m_scoreArray[i]->Serialize(data_stream);
        if (!data_stream.CheckState())
        {
            DisplaySerializationError(GetFilename(), stream.TellO(), data_stream.GetLastErrorMessage());
            return (stream);
        }
    }
    
    // Write the document font settings    
    wxUint32 fontSettingIndex = 0;
	for (; fontSettingIndex < NUM_DOCUMENT_FONT_SETTINGS; fontSettingIndex++)
	{
	    m_fontSettingArray[fontSettingIndex].Serialize(data_stream);
	    if (!data_stream.CheckState())
        {
            DisplaySerializationError(GetFilename(), stream.TellO(), data_stream.GetLastErrorMessage());
            return (stream);
        }
    }
    
    // Write the line spacing and fade values
	data_stream << m_tablatureStaffLineSpacing << m_fadeIn << m_fadeOut;
	if (!data_stream.CheckState())
    {
        DisplaySerializationError(GetFilename(), stream.TellO(), data_stream.GetLastErrorMessage());
        return (stream);
    }
	               
    return (stream);
}

// Load Functions
/// Deserializes the document from an input stream
/// @param stream Input stream to load from
/// @return Input stream
wxInputStream& PowerTabDocument::LoadObject(wxInputStream& stream)
{
    //------Last Checked------//
    // - Jan 26, 2005
    
    // Create our special Power Tab stream
    PowerTabInputStream data_stream(stream);
    
    // Read the header
    m_header.Deserialize(data_stream);
    if (!data_stream.CheckState())
    {
        DeleteContents();
        DisplayDeserializationError(GetFilename(), stream.TellI(), data_stream.GetLastErrorMessage());
        return (stream);
    }
    
    // Get the file version
    const wxWord version = m_header.GetVersion();
    
    // v1.0 or v1.0.2
    if ((version == PowerTabFileHeader::FILEVERSION_1_0) || (version == PowerTabFileHeader::FILEVERSION_1_0_2))
        DeserializeFormat1_0(data_stream, version);
    // v1.5
    else if (version == PowerTabFileHeader::FILEVERSION_1_5)
        DeserializeFormat1_5(data_stream);
    // v1.7
    else
        DeserializeFormat1_7(data_stream);
    
    if (!data_stream.CheckState())
    {
        DeleteContents();
        DisplayDeserializationError(GetFilename(), stream.TellI(), data_stream.GetLastErrorMessage());
        return (stream);
    }
    
    return (stream);
}

/// Loads a power tab file
/// @param fileName Full path of the file to load
/// @return True if the file was loaded, false if not
bool PowerTabDocument::Load(const wxChar* fileName)
{
    //------Last Checked------//
    // - Jan 27, 2005
    wxCHECK(fileName != NULL, false);
    
    // Create a stream
    wxFileInputStream stream(fileName);
    if (!stream.IsOk())
        return (false);
    
    // Create our special Power Tab stream, then call the sibling function
    PowerTabInputStream data_stream(stream);
    return (Load(data_stream));
}

/// Loads a power tab file from an input stream
/// @param stream Input stream to load from
/// @return True if the file was loaded, false if not
bool PowerTabDocument::Load(PowerTabInputStream& stream)
{
    //------Last Checked------//
    // - Jan 27, 2005
    wxCHECK(stream.CheckState(), false);
    DeleteContents();
    
    // Read the header
    m_header.Deserialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    const wxWord version = m_header.GetVersion();
    
    // v1.0 or v1.0.2
    if (version == PowerTabFileHeader::FILEVERSION_1_0 || version == PowerTabFileHeader::FILEVERSION_1_0_2)
        DeserializeFormat1_0(stream, version);
    // v1.5
    else if (version == PowerTabFileHeader::FILEVERSION_1_5)
        DeserializeFormat1_5(stream);
    // v1.7
    else
        DeserializeFormat1_7(stream);
        
    return (stream.CheckState());
}

/// Deserializes Version 1.7 Files from an input stream
/// @param stream Input stream to read from
/// @return True if the document was deserialized, false if not
bool PowerTabDocument::DeserializeFormat1_7(PowerTabInputStream& stream)
{
    //------Last Checked------//
    // - Jan 27, 2005
    
    // Set the version
    const wxWord version = PowerTabFileHeader::FILEVERSION_1_7;
    
    // Read the guitar score
	Score* guitarScore = new Score;
	guitarScore->Deserialize(stream, version);
	if (!stream.CheckState())
	{
        delete guitarScore;
	    return (false);
	}
	m_scoreArray.Add(guitarScore);
    	
	// Read the bass score
	Score* bassScore = new Score;
	bassScore->Deserialize(stream, version);
	if (!stream.CheckState())
	{
	    delete bassScore;
	    return (false);
	}
	m_scoreArray.Add(bassScore);

    // Read the document font settings
    wxUint32 fontSettingIndex = 0;
	for (; fontSettingIndex < NUM_DOCUMENT_FONT_SETTINGS; fontSettingIndex++)
	{
	    FontSetting fontSetting;
	    fontSetting.Deserialize(stream, version);
	    wxCHECK(stream.CheckState(), false);
	    
	    m_fontSettingArray[fontSettingIndex] = fontSetting;
	}
    
    // Read the line spacing and fade values
	stream >> m_tablatureStaffLineSpacing >> m_fadeIn >> m_fadeOut;
	wxCHECK(stream.CheckState(), false);
	    
    return (true);
}

/// Deserializes Version 1.5 Files from an input stream
/// @param stream Input stream to read from
/// @return True if the document was deserialized, false if not
bool PowerTabDocument::DeserializeFormat1_5(PowerTabInputStream& stream)
{
    //------Last Checked------//
    // - Jan 26, 2005

    // Set the version
    const wxWord version = PowerTabFileHeader::FILEVERSION_1_5;
    
    // Deserialize both scores
    size_t scoreIndex = 0;
	for (; scoreIndex < 2; scoreIndex++)
	{
	    // Don't create the score on the heap, the checks will cause memory leaks
	    Score score;
	    
	    // Read the transcriber for the score (stored in the header in v1.7)
	    wxString transcriber = wxT("");
	    stream.ReadMFCString(transcriber);
	    wxCHECK(stream.CheckState(), false);
	    
	    if (!transcriber.IsEmpty())
	    {
	        if (scoreIndex == 0)
	            m_header.SetSongGuitarScoreTranscriber(transcriber);
	        else if (scoreIndex == 1)
	            m_header.SetSongBassScoreTranscriber(transcriber);
	    }
	    
	    // Read the notes for the score (stored in the header in v1.7)
	    wxString notes = wxT("");
	    stream.ReadMFCString(notes);
	    wxCHECK(stream.CheckState(), false);
	    
	    if (!notes.IsEmpty())
	    {
	        if (scoreIndex == 0)
	            m_header.SetSongGuitarScoreNotes(notes);
	        else if (scoreIndex == 1)
	            m_header.SetSongBassScoreNotes(notes);
        }
        
        score.m_guitarArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        score.m_chordDiagramArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        score.m_floatingTextArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        score.m_guitarInArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        score.m_tempoMarkerArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        score.m_dynamicArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
		score.m_alternateEndingArray.Deserialize(stream, version);
		wxCHECK(stream.CheckState(), false);

        score.m_systemArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        // Add the score to the document
        m_scoreArray.Add((Score*)score.CloneObject());
	}

    // Read the document font settings
    wxUint32 fontSettingIndex = 0;
	for (; fontSettingIndex < NUM_DOCUMENT_FONT_SETTINGS; fontSettingIndex++)
    {
        FontSetting fontSetting;
        fontSetting.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
        
        m_fontSettingArray[fontSettingIndex] = fontSetting;
    }
    
    // Read the line spacing and fade values
    stream >> m_tablatureStaffLineSpacing >> m_fadeIn >> m_fadeOut;
    wxCHECK(stream.CheckState(), false);
    
    return (true);
}

/// Deserializes Version 1.0 and 1.0.2 files from an input stream
/// @param stream Input stream to read from
/// @param version File version
/// @return True if the document was deserialized, false if not
bool PowerTabDocument::DeserializeFormat1_0(PowerTabInputStream& stream, wxWord version)
{
    //------Last Checked------//
    // - Jan 26, 2005
    
    // Read the line spacing value
    stream >> m_tablatureStaffLineSpacing;
    wxCHECK(stream.CheckState(), false);

    // Read the document font settings
    wxUint32 fontSettingIndex = 0;
	for (; fontSettingIndex < NUM_DOCUMENT_FONT_SETTINGS; fontSettingIndex++)
	{
	    FontSetting fontSetting;
	    fontSetting.Deserialize(stream, version);
	    wxCHECK(stream.CheckState(), false);
	    
	    m_fontSettingArray[fontSettingIndex] = fontSetting;
    }
    
    wxUint32 scoreIndex = 0;
	for (; scoreIndex < 2; scoreIndex++)
	{
	    // Don't create the score on the heap, the checks will cause memory leaks
	    Score score;
	    
	    score.m_guitarArray.Deserialize(stream, version);
	    wxCHECK(stream.CheckState(), false);
	    
	    score.m_chordDiagramArray.Deserialize(stream, version);
	    wxCHECK(stream.CheckState(), false);

        score.m_floatingTextArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);

        score.m_guitarInArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);

        score.m_tempoMarkerArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
                        	    
        OldTimeSignatureArray oldTimeSignatureArray;
        oldTimeSignatureArray.Deserialize(stream, version);
        wxCHECK(stream.CheckState(), false);
		
		score.m_dynamicArray.Deserialize(stream, version);
		wxCHECK(stream.CheckState(), false);
		
		score.m_alternateEndingArray.Deserialize(stream, version);
		wxCHECK(stream.CheckState(), false);
	
	    OldRehearsalSignArray oldRehearsalSignArray;
	    oldRehearsalSignArray.Deserialize(stream, version);	
	    wxCHECK(stream.CheckState(), false);
		
		score.m_systemArray.Deserialize(stream, version);
		wxCHECK(stream.CheckState(), false);

		// Move all time signatures to the appropriate barlines
		while (!oldTimeSignatureArray.IsEmpty())
		{
		    // Get the first element in the array
		    OldTimeSignature* oldTimeSignature = oldTimeSignatureArray[0];
		    oldTimeSignatureArray.RemoveAt(0);
		    wxCHECK(oldTimeSignature != NULL, false);
		    
		    // Update the data to the new format
		    wxUint32 data = oldTimeSignature->m_data;
			wxByte temp = HIBYTE(HIWORD(data));

			wxByte beatsPerMeasure = (wxByte)(((temp >> 3) & 0x1f) + 1);	    // Top 5 bits = bpm, where 0 = 1, 1 = 2, etc.
			wxByte beatAmount = (wxByte)pow((double)2, (double)(temp & 0x07));	// Bottom 3 bits = ba in power of 2, TimeSignature doesn't use pow

			bool commonTime = ((data & 0x400000) == 0x400000);
			bool cutTime = ((data & 0x800000) == 0x800000);

            // Get the beaming information (all beam values are zero-based and 5 bits each)
            wxByte beat1 = (wxByte)((data & 0xf8000) >> 15);
            wxByte beat2 = (wxByte)((data & 0x7c00) >> 10);
            wxByte beat3 = (wxByte)((data & 0x3e0) >> 5);
			wxByte beat4 = (wxByte)(data & 0x1f);
			if (beat1 > 0)
			    beat1++;
		    if (beat2 > 0)
		        beat2++;
		    if (beat3 > 0)
		        beat3++;
		    if (beat4 > 0)
		        beat4++;
			
			// Get the location of the object
			wxWord systemIndex = oldTimeSignature->m_system;
			wxByte positionIndex = oldTimeSignature->m_position;

			// Get the system the sign belongs to
			System* system = score.GetSystem(systemIndex);
            wxCHECK(system != NULL, false);

            TimeSignature* timeSignature = NULL;

			// First position in system
			if (positionIndex == 0)
			    timeSignature = system->GetStartBarRef().GetTimeSignaturePtr();
			else
			{
			    // Get barline where time sign is located
			    Barline* barline = system->GetBarlineAtPosition(positionIndex);

				// Exists
				if (barline != NULL)
				    timeSignature = barline->GetTimeSignaturePtr();
				// Doesn't exist - bug
			}

            // Update the time signature
			if (timeSignature != NULL)
			{
				// Set the meter
				timeSignature->SetMeter(beatsPerMeasure, beatAmount);

				// All time signatures are shown
				timeSignature->Show();

				// Cut time
				if (cutTime)
				    timeSignature->SetCutTime();
				// Common time
				else if (commonTime)
					timeSignature->SetCommonTime();

                timeSignature->SetBeamingPattern(beat1, beat2, beat3, beat4);
			}

			// Free memory
			delete oldTimeSignature;
		}

		// We must update all bars in between v1.0 time signs, because unlike v1.0
		// the time is stored with each bar in the score
		// Setup the default values for 4/4 time
		wxByte beatsPerMeasure = 4;
		wxByte beatAmount = 4;
		wxByte beat1 = 4;
		wxByte beat2 = 0;
		wxByte beat3 = 0;
		wxByte beat4 = 0;
		bool cutTime = false;
		bool commonTime = false;
		bool processedFirst = false;
        
        size_t systemIndex = 0;
        size_t systemCount = score.GetSystemCount();
        for (; systemIndex < systemCount; systemIndex++)
		{
		    // Get the system
		    System* system = score.GetSystem(systemIndex);
		    wxCHECK2(system != NULL, continue);
		    
		    // Update the time signature for all non-shown time signatures

            // Check each barline in the system
            // We don't check the end bar, because the key/time data is not maintained in that barline
			size_t barlineIndex = 0;
			size_t barlineCount = system->GetBarlineCount();
			for (; barlineIndex <= barlineCount; barlineIndex++)
            {
                Barline* barline = NULL;
                
                // For the first index, use the starting barline
                // That's why we iterate for <= barlineCount and not < barlineCount
                if (barlineIndex == 0)
                    barline = &system->GetStartBarRef();
                else
                    barline = system->GetBarline(barlineIndex - 1);
                wxCHECK2(barline != NULL, continue);
                
                // Process the time signature at the start of the system
			    TimeSignature& timeSignature = barline->GetTimeSignatureRef();
    			
			    // Starting time signature is shown, update the time signature data
			    if (timeSignature.IsShown())
			    {
			        timeSignature.GetMeter(beatsPerMeasure, beatAmount);
			        cutTime = timeSignature.IsCutTime();
                    commonTime = timeSignature.IsCommonTime();
                    timeSignature.GetBeamingPattern(beat1, beat2, beat3, beat4);
				    processedFirst = true;
			    }
			    // Starting time signature is not shown; update using the previous time signature data
			    else if (processedFirst)
			    {
			        if (cutTime)
			            timeSignature.SetCutTime();
			        else if (commonTime)
			            timeSignature.SetCommonTime();
			        else
			            timeSignature.SetMeter(beatsPerMeasure, beatAmount);

                    timeSignature.SetBeamingPattern(beat1, beat2, beat3, beat4);
			    }
			}
		}

		// Move all rehearsal signs to the appropriate barlines
		while (!oldRehearsalSignArray.IsEmpty())
		{
		    // Get the first element in the array
		    OldRehearsalSign* oldRehearsalSign = oldRehearsalSignArray[0];
            oldRehearsalSignArray.RemoveAt(0);
            wxCHECK(oldRehearsalSign != NULL, false);
            
            // Get the location of the object
            wxWord systemIndex = oldRehearsalSign->m_system;
            wxByte positionIndex = oldRehearsalSign->m_position;

			// Get the system the sign belongs to
			System* system = score.GetSystem(systemIndex);
            wxCHECK(system != NULL, false);

            RehearsalSign* rehearsalSign = NULL;

			// First position in system
			if (positionIndex == 0)
			    rehearsalSign = system->GetStartBarRef().GetRehearsalSignPtr();
			else
			{
			    // Get the barline where the rehearsal sign is anchored
			    Barline* barline = system->GetBarlineAtPosition(positionIndex);

				// Exists
				if (barline != NULL)
				    rehearsalSign = barline->GetRehearsalSignPtr();
				// Doesn't exist - bug
			}

            // Update the rehearsal sign
            if (rehearsalSign != NULL)
			{
			    rehearsalSign->SetLetter(oldRehearsalSign->m_letter);
			    rehearsalSign->SetDescription(oldRehearsalSign->m_description);
			}

			// Free memory
			delete oldRehearsalSign;
		}
		
		// Add the score to the document
        m_scoreArray.Add((Score*)score.CloneObject());
	}

    wxByte fadeIn = 0;
    wxByte fadeOut = 0;
    stream >> fadeIn >> fadeOut;
    wxCHECK(stream.CheckState(), false);
    
    // Fades were stored as measures in v1.0
    // We can just fudge this and assume it's 4/4 time, since there will be
    // very few v1.0 files on the Web
    m_fadeIn = fadeIn * MIDI_PPQN * 4;
    m_fadeOut = fadeOut * MIDI_PPQN * 4;

	// Must refresh note beaming due to redesign to beaming strategy
	// Note: Beaming algorithm is not included; manually running the score polisher 
	// should rebeam the score; There are very few 1.0 files on the Web anyways
/*	for (int w = 0; w < 2; w++)
	{
		RefreshBeaming((BYTE)w);
		ToolScorePolisher(SP_FULL, FALSE, (BYTE)w);
	}*/	
	
	return (true);
}

// Overrides
bool PowerTabDocument::DeleteContents()
{
    //------Last Checked------//
    // - Jan 26, 2005
    m_header.LoadDefaults();
    DeleteScoreArrayContents();
    m_tablatureStaffLineSpacing = DEFAULT_TABLATURE_STAFF_LINE_SPACING;
    wxUint32 i = 0;
    for (; i < NUM_DOCUMENT_FONT_SETTINGS; i++)
        m_fontSettingArray[i] = FontSetting();
    m_fadeIn = DEFAULT_FADE_IN;
    m_fadeOut = DEFAULT_FADE_OUT;
    return (true);
}

// Score Functions
/// Determines if the guitar score in another document can be merged into the current document
/// @param document Document who's guitar score we want to merge with
/// @return True if the guitar score can be merged, false if not
bool PowerTabDocument::CanMergeGuitarScore(PowerTabDocument& document) const
{
    //------Last Checked------//
    // - Jan 9, 2005
    
    // In order to merge, we must meet three requirements:
    // 1) Line spacing on the tablature staff must be the same
    // 2) All document font settings must be the same
    // 3) We must not have more than seven guitars total after the merge

    // 1)
    if (m_tablatureStaffLineSpacing != document.m_tablatureStaffLineSpacing)
        return (false);

    // 2)
    wxUint32 fontSettingIndex = 0;
    for (; fontSettingIndex < NUM_DOCUMENT_FONT_SETTINGS; fontSettingIndex++)
    {
        if (m_fontSettingArray[fontSettingIndex] != document.m_fontSettingArray[fontSettingIndex])
            return (false);
    }
    
    // 3)
    Score* guitarScore = GetGuitarScore();
    wxCHECK(guitarScore != NULL, false);
    Score* bassScore = document.GetBassScore();
    wxCHECK(bassScore != NULL, false);
    
    if ((guitarScore->GetGuitarCount() + bassScore->GetGuitarCount()) > MAX_GUITARS)
        return (false);
    
    return (true);
}

/// Merges the guitar score of another document into the current document
/// @param document The document who's guitar score will be merged
/// @return True if the document's guitar score was merged, false if not
bool PowerTabDocument::MergeGuitarScore(PowerTabDocument& document)
{
    //------Last Checked------//
    // - Jan 26, 2005
    
    // If we can't merge, bail out
    if (!CanMergeGuitarScore(document))
        return (false);
    
    // Get a pointer to the score we're merging
    Score* fromGuitarScore = document.GetGuitarScore();
    wxCHECK(fromGuitarScore != NULL, false);
    
    // Get the current guitar score
    Score* oldGuitarScore = GetGuitarScore();
    wxCHECK(oldGuitarScore != NULL, false);
    
    // Make a copy of the score
    Score* mergeGuitarScore = (Score*)fromGuitarScore->CloneObject();
    wxCHECK(mergeGuitarScore != NULL, false);
    
    // Update the guitar score
    m_scoreArray[0] = mergeGuitarScore;
    
    // Delete the old guitar score
    delete oldGuitarScore;
        
    return (true);
}

/// Determines if the bass score in another document can be merged into the current document
/// @param document Document who's bass score we want to merge with
/// @return True if the bass score can be merged, false if not
bool PowerTabDocument::CanMergeBassScore(PowerTabDocument& document) const
{
    //------Last Checked------//
    // - Jan 9, 2005
    
    // In order to merge, we must meet three requirements:
    // 1) Line spacing on the tablature staff must be the same
    // 2) All document font settings must be the same
    // 3) We must not have more than seven guitars total after the merge

    // 1)
    if (m_tablatureStaffLineSpacing != document.m_tablatureStaffLineSpacing)
        return (false);

    // 2)
    wxUint32 i = 0;
    for (; i < NUM_DOCUMENT_FONT_SETTINGS; i++)
    {
        if (m_fontSettingArray[i] != document.m_fontSettingArray[i])
            return (false);
    }
    
    // 3)
    Score* guitarScore = GetGuitarScore();
    wxCHECK(guitarScore != NULL, false);
    Score* bassScore = document.GetBassScore();
    wxCHECK(bassScore != NULL, false);
    
    if ((guitarScore->GetGuitarCount() + bassScore->GetGuitarCount()) > MAX_GUITARS)
        return (false);
        
    return (true);
}

/// Merges the bass score of another document into the current document
/// @param document The document who's bass score will be merged
/// @return True if the document's bass score was merged, false if not
bool PowerTabDocument::MergeBassScore(PowerTabDocument& document)
{
    //------Last Checked------//
    // - Jan 26, 2005
    
    // If we can't merge, bail out
    if (!CanMergeBassScore(document))
        return (false);
    
    // Get a pointer to the score we're merging
    Score* fromBassScore = document.GetBassScore();
    wxCHECK(fromBassScore != NULL, false);
    
    // Get the current bass score
    Score* oldBassScore = GetBassScore();
    wxCHECK(oldBassScore != NULL, false);
    
    // Make a copy of the score
    Score* mergeBassScore = (Score*)fromBassScore->CloneObject();
    wxCHECK(mergeBassScore != NULL, false);
    
    // Update the bass score
    m_scoreArray[1] = mergeBassScore;
    
    // Delete the old bass score
    delete oldBassScore;
    
    return (true);
}

/// Deletes the contents (and frees the memory) of the score array
void PowerTabDocument::DeleteScoreArrayContents()
{
    //------Last Checked------//
    // - Dec 16, 2004
   
	size_t i = 0;
	size_t count = m_scoreArray.GetCount();
	for (i = 0; i < count; i++)
        delete m_scoreArray[i];
	m_scoreArray.Clear();
}

// Error Functions
/// Displays an error message during serialiation
/// @param fileName Name of the file that was loading during the error
/// @param offset The offset within the file where the error occurred
/// @param errorMessage Error message to display
void PowerTabDocument::DisplaySerializationError(const wxString& fileName, off_t offset, const wxString& errorMessage)
{
    //------Last Checked------//
    // - Jan 27, 2005
    wxMessageBox(wxString::Format(wxT("An error occurred at offset %lld while loading the file '%s'.\n\n%s"), offset, fileName.c_str(), errorMessage.c_str()), wxT("Serialize Error"), wxICON_ERROR);
}

/// Displays an error message during deserialiation
/// @param fileName Name of the file that was loading during the error
/// @param offset The offset within the file where the error occurred
/// @param errorMessage Error message to display
void PowerTabDocument::DisplayDeserializationError(const wxString& fileName, off_t offset, const wxString& errorMessage)
{
    //------Last Checked------//
    // - Jan 27, 2005
    wxMessageBox(wxString::Format(wxT("An error occurred at offset %lld while saving the file '%s'.\n\n%s"), offset, fileName.c_str(), errorMessage.c_str()), wxT("Deserialize Error"), wxICON_ERROR);
}
