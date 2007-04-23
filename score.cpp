/////////////////////////////////////////////////////////////////////////////
// Name:            score.cpp
// Purpose:         Stores and renders a score
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 16, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "score.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/// Default Constructor
Score::Score()
{
    //------Last Checked------//
    // - Jan 5, 2005
}

/// Copy Constructor
Score::Score(const Score& score)
{
    //------Last Checked------//
    // - Jan 5, 2005
    *this = score;
}

/// Destructor
Score::~Score()
{
    //------Last Checked------//
    // - Jan 5, 2005
    m_guitarArray.DeleteContents();
    m_chordDiagramArray.DeleteContents();
    m_floatingTextArray.DeleteContents();
    m_guitarInArray.DeleteContents();
    m_tempoMarkerArray.DeleteContents();
    m_dynamicArray.DeleteContents();
    m_alternateEndingArray.DeleteContents();
    m_systemArray.DeleteContents();    
}

// Operators
/// Assignment Operator
const Score& Score::operator=(const Score& score)
{
    //------Last Checked------//
    // - Jan 5, 2005
    
    // Check for assignment to self
    if (this != &score)
    {
        m_guitarArray.Copy(score.m_guitarArray);
        m_chordDiagramArray.Copy(score.m_chordDiagramArray);
        m_floatingTextArray.Copy(score.m_floatingTextArray);
        m_guitarInArray.Copy(score.m_guitarInArray);
        m_tempoMarkerArray.Copy(score.m_tempoMarkerArray);
        m_dynamicArray.Copy(score.m_dynamicArray);
        m_alternateEndingArray.Copy(score.m_alternateEndingArray);
        m_systemArray.Copy(score.m_systemArray);
    }
    return (*this);
}

/// Equality Operator
bool Score::operator==(const Score& score) const
{
    //------Last Checked------//
    // - Jan 5, 2005
    return (
        (m_guitarArray.Equals(score.m_guitarArray)) &&
        (m_chordDiagramArray.Equals(score.m_chordDiagramArray)) &&
        (m_floatingTextArray.Equals(score.m_floatingTextArray)) &&
        (m_guitarInArray.Equals(score.m_guitarInArray)) &&
        (m_tempoMarkerArray.Equals(score.m_tempoMarkerArray)) &&
        (m_dynamicArray.Equals(score.m_dynamicArray)) &&
        (m_alternateEndingArray.Equals(score.m_alternateEndingArray)) &&
        (m_systemArray.Equals(score.m_systemArray))
    );
}

/// Inequality Operator
bool Score::operator!=(const Score& score) const
{
    //------Last Checked------//
    // - Jan 5, 2005
    return (!operator==(score));
}
    
// Serialization Functions
/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool Score::DoSerialize(PowerTabOutputStream& stream)
{
    //------Last Checked------//
    // - Jan 5, 2005
    m_guitarArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);

    m_chordDiagramArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_floatingTextArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_guitarInArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_tempoMarkerArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_dynamicArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_alternateEndingArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_systemArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);

    return (stream.CheckState());
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool Score::DoDeserialize(PowerTabInputStream& stream, wxWord version)
{
    //------Last Checked------//
    // - Jan 5, 2005
    m_guitarArray.Deserialize(stream, version);
    wxCHECK(stream.CheckState(), false);

    m_chordDiagramArray.Deserialize(stream, version);
    wxCHECK(stream.CheckState(), false);
    
    m_floatingTextArray.Deserialize(stream, version);
    wxCHECK(stream.CheckState(), false);
    
    m_guitarInArray.Deserialize(stream, version);
    wxCHECK(stream.CheckState(), false);
    
    m_tempoMarkerArray.Deserialize(stream, version);
    wxCHECK(stream.CheckState(), false);
    
    m_dynamicArray.Deserialize(stream, version);
    wxCHECK(stream.CheckState(), false);
    
    m_alternateEndingArray.Deserialize(stream, version);
    wxCHECK(stream.CheckState(), false);
    
    m_systemArray.Deserialize(stream, version);
    wxCHECK(stream.CheckState(), false);
        
    return (stream.CheckState());
}

// Operations
/// Gathers statistics about the score
/// @param statistics Holds the statistics return values
void Score::GetStatistics(SCORE_STATISTICS& statistics)
{
    statistics.guitars += GetGuitarCount();
    statistics.chordDiagrams += GetChordDiagramCount();
    statistics.guitarIns += GetGuitarInCount();

    for (int tempoMarker = 0, tempoMarkerCount = GetTempoMarkerCount();
        tempoMarker < tempoMarkerCount; ++tempoMarker)
    {
        TempoMarker* pTempoMarker = GetTempoMarker(tempoMarker);
        wxCHECK2(pTempoMarker != NULL, continue);

        if (pTempoMarker->IsAlterationOfPace())
            statistics.alterations++;
        else
            statistics.tempoMarkers++;
    }

    statistics.dynamics += GetDynamicCount();
    statistics.alternateEndings += GetAlternateEndingCount();

    for (int system = 0, systemCount = GetSystemCount(); system < systemCount;
        ++system)
    {
        System* pSystem = GetSystem(system);
        wxCHECK2(pSystem != NULL, continue);

        // Directions
        for (int direction = 0, directionCount = pSystem->GetDirectionCount();
            direction < directionCount; ++direction)
        {
            Direction* pDirection = pSystem->GetDirection(direction);
            wxCHECK2(pDirection != NULL, continue);

            statistics.directions += pDirection->GetSymbolCount();

            for (int symbol = 0, symbolCount = pDirection->GetSymbolCount();
                symbol < symbolCount; ++symbol)
            {
                wxString symbolText = pDirection->GetText(symbol);

                MapStringToInt::iterator iFind =
                        statistics.mapDirections.find(symbolText);
                    if (iFind == statistics.mapDirections.end())
                        statistics.mapDirections[symbolText] = 1;
                    else
                        (*iFind).second++;
            }
        }

        statistics.chordNames += pSystem->GetChordTextCount();

        BarlineArray barlines;
        pSystem->GetBarlines(barlines);

        for (int barline = 0, barlineCount = barlines.GetCount();
            barline < barlineCount; ++barline)
        {
            Barline* pBarline = barlines[barline];
            wxCHECK2(pBarline != NULL, continue);

            statistics.barlines++;

            // Barlines
            {
                wxString barlineText[6] = 
                {
                    wxT("Single"),
                    wxT("Double"),
                    wxT("Dashed"),
                    wxT("Repeat Start"),
                    wxT("Repeat End"),
                    wxT("Double Fine")
                };
                int type = pBarline->GetType();
                if (Barline::IsValidType(type))
                {
                    wxString typeText = barlineText[type];
                    MapStringToInt::iterator iFind =
                            statistics.mapBarlines.find(typeText);
                    if (iFind == statistics.mapBarlines.end())
                        statistics.mapBarlines[typeText] = 1;
                    else
                        (*iFind).second++;
                }
            }

            // Rehearsal signs
            const RehearsalSign& rehearsalSign =
                pBarline->GetRehearsalSignConstRef();

            if (rehearsalSign.IsSet())
            {
                statistics.rehearsalSigns++;

                /*wxString description = rehearsalSign.GetDescription();
                description.Trim();

                if (!description.IsEmpty())
                {
                    description.LowerCase();

                    MapStringToInt::iterator iFind =
                        statistics.mapRehearsalSignDescriptions.find(description);
                    if (iFind == statistics.mapRehearsalSignDescriptions.end())
                        statistics.mapRehearsalSignDescriptions[description] = 1;
                    else
                        (*iFind).second++;
                }*/
            }

            // Key signatures
            const KeySignature& keySignature =
                pBarline->GetKeySignatureConstRef();

            if (keySignature.IsShown())
            {
                statistics.keySignatures++;

                wxString signature = keySignature.GetText();

                MapStringToInt::iterator iFind =
                    statistics.mapKeySignatures.find(signature);
                if (iFind == statistics.mapKeySignatures.end())
                    statistics.mapKeySignatures[signature] = 1;
                else
                    (*iFind).second++;
            }

            // Time signatures
            const TimeSignature& timeSignature =
                pBarline->GetTimeSignatureConstRef();

            if (timeSignature.IsShown())
            {
                statistics.timeSignatures++;

                wxString meter;

                if (timeSignature.IsCutTime())
                    meter = wxT("Cut");
                else if (timeSignature.IsCommonTime())
                    meter = wxT("Common");
                else
                    meter = timeSignature.GetText(TimeSignature::textFull);

                MapStringToInt::iterator iFind =
                    statistics.mapTimeSignatures.find(meter);
                if (iFind == statistics.mapTimeSignatures.end())
                    statistics.mapTimeSignatures[meter] = 1;
                else
                    (*iFind).second++;
            }
        }

        // NOTE: Empty the barline array, or we'll get bad pointers
        barlines.Empty();

        // Chord Formulas
        for (int chordText = 0, chordTextCount = pSystem->GetChordTextCount();
            chordText < chordTextCount; ++chordText)
        {
            ChordText* pChordText = pSystem->GetChordText(chordText);
            wxCHECK2(pChordText != NULL, continue);

            wxString formula = 
                pChordText->GetChordNameConstRef().GetFormulaText();
            MapStringToInt::iterator iFind =
                statistics.mapChordFormulas.find(formula);
            if (iFind == statistics.mapChordFormulas.end())
                statistics.mapChordFormulas[formula] = 1;
            else
                (*iFind).second++;
        }

        // Rhythm Slashes
        for (int rhythmSlash = 0,
            rhythmSlashCount = pSystem->GetRhythmSlashCount();
            rhythmSlash < rhythmSlashCount; ++rhythmSlash)
        {
            RhythmSlash* pRhythmSlash = pSystem->GetRhythmSlash(rhythmSlash);
            wxCHECK2(pRhythmSlash != NULL, continue);

            if (pRhythmSlash->IsRest())
                statistics.rests++;
            else
            {
                statistics.rhythmSlashes++;

                if (pRhythmSlash->IsTied())
                    statistics.ties++;
                if (pRhythmSlash->IsStaccato())
                    statistics.staccatos++;
                if (pRhythmSlash->HasMarcato())
                    statistics.marcatos++;
                if (pRhythmSlash->HasSforzando())
                    statistics.sforzandos++;
                if (pRhythmSlash->IsMuted())
                    statistics.mutes++;
                if (pRhythmSlash->HasSlideIntoFromAbove() ||
                    pRhythmSlash->HasSlideIntoFromBelow() ||
                    pRhythmSlash->HasSlideOutOfDownwards() ||
                    pRhythmSlash->HasSlideOutOfUpwards())
                {
                    statistics.slides++;
                }
                if (pRhythmSlash->HasArpeggioUp() ||
                    pRhythmSlash->HasArpeggioDown())
                {
                    statistics.arpeggios++;
                }
                if (pRhythmSlash->HasPickStrokeUp() ||
                    pRhythmSlash->HasPickStrokeDown())
                {
                    statistics.pickstrokes++;
                }
            }
        }

        // Notes
        for (int staff = 0, staffCount = pSystem->GetStaffCount();
            staff < staffCount; ++staff)
        {
            Staff* pStaff = pSystem->GetStaff(staff);
            wxCHECK2(pStaff != NULL, continue);

            for (int voice = 0; voice < NUM_STAFF_VOICES; ++voice)
            {
                for (int position = 0,
                    positionCount = pStaff->m_positionArray[voice].GetCount();
                    position < positionCount; ++position)
                {
                    Position* pPosition = 
                        pStaff->m_positionArray[voice][position];
                    wxCHECK2(pPosition != NULL, continue);

                    if (pPosition->IsRest())
                    {
                        if (pPosition->HasMultibarRest())
                            statistics.multiBarRests++;
                        else
                            statistics.rests++;
                    }
                    else
                    {
                        statistics.notes += pPosition->GetNoteCount();

                        if (pPosition->IsStaccato())
                            statistics.staccatos++;
                        if (pPosition->HasMarcato())
                            statistics.marcatos++;
                        if (pPosition->HasSforzando())
                            statistics.sforzandos++;

                        if (pPosition->HasVibrato() ||
                            pPosition->HasWideVibrato())
                        {
                            statistics.vibratos++;
                        }
                        if (pPosition->HasArpeggioUp() ||
                            pPosition->HasArpeggioDown())
                        {
                            statistics.arpeggios++;
                        }
                        if (pPosition->HasPickStrokeUp() ||
                            pPosition->HasPickStrokeDown())
                        {
                            statistics.pickstrokes++;
                        }
                        if (pPosition->HasTremoloPicking())
                            statistics.tremolos++;

                        if (pPosition->HasPalmMuting())
                            statistics.palmMutes++;

                        if (pPosition->IsAcciaccatura())
                            statistics.acciaccaturas++;

                        if (pPosition->HasLetRing())
                            statistics.letRings++;

                        if (pPosition->HasFermata())
                            statistics.fermatas++;

                        if (pPosition->HasVolumeSwell())
                            statistics.volumeSwells++;

                        if (pPosition->HasTremoloBar())
                            statistics.tremoloBars++;

                        if (pPosition->HasTap())
                            statistics.taps++;

                        for (int note = 0,
                            noteCount = pPosition->GetNoteCount();
                            note < noteCount; ++note)
                        {
                            Note* pNote = pPosition->GetNote(note);
                            wxCHECK2(pNote != NULL, continue);

                            if (pNote->IsTied())
                                statistics.ties++;
                            if (pNote->IsMuted())
                                statistics.mutes++;
                            if (pNote->HasHammerOn())
                                statistics.hammerOns++;
                            if (pNote->HasPullOff())
                                statistics.pullOffs++;
                            if (pNote->IsNaturalHarmonic())
                                statistics.naturalHarmonics++;
                            if (pNote->IsGhostNote())
                                statistics.ghostNotes++;
                            if (pNote->IsOctave8va() || pNote->IsOctave15ma() ||
                                pNote->IsOctave8vb() || pNote->IsOctave15mb())
                            {
                                statistics.octaveSigns++;
                            }
                            if (pNote->HasSlide())
                                statistics.slides++;
                            if (pNote->HasBend())
                                statistics.bends++;
                            if (pNote->HasTappedHarmonic())
                                statistics.tappedHarmonics++;
                            if (pNote->HasTrill())
                                statistics.trills++;
                            if (pNote->HasArtificialHarmonic())
                                statistics.artificialHarmonics++;

                        }
                    }
                }
            }
        }
    }

    // Get tuning
    for (size_t guitar = 0, guitarCount = GetGuitarCount();
        guitar < guitarCount; ++guitar)
    {
        Guitar* pGuitar = GetGuitar(guitar);
        wxCHECK2(pGuitar != NULL, continue);

        wxString spelling = pGuitar->GetTuningSpelling();
        
        MapStringToInt::iterator iFind = statistics.mapTunings.find(spelling);
        if (iFind == statistics.mapTunings.end())
            statistics.mapTunings[spelling] = 1;
        else
            (*iFind).second++;
    }

    // Get chord diagram voicings
    for (size_t chordDiagram = 0, chordDiagramCount = GetChordDiagramCount();
        chordDiagram < chordDiagramCount; ++chordDiagram)
    {
        ChordDiagram* pChordDiagram = GetChordDiagram(chordDiagram);
        wxCHECK2(pChordDiagram != NULL, continue);

        wxString spelling = pChordDiagram->GetSpelling();
        MapStringToInt::iterator iFind =
            statistics.mapChordDiagrams.find(spelling);
        if (iFind == statistics.mapChordDiagrams.end())
            statistics.mapChordDiagrams[spelling] = 1;
        else
            (*iFind).second++;
    }

    // Get the tempo marker descriptions
    /*for (size_t tempoMarker = 0, tempoMarkerCount = GetTempoMarkerCount();
        tempoMarker < tempoMarkerCount; ++tempoMarker)
    {
        TempoMarker* pTempoMarker = GetTempoMarker(tempoMarker);
        wxCHECK2(pTempoMarker != NULL, continue);

        wxString description = pTempoMarker->GetDescription();
        description.Trim();

        if (!description.IsEmpty())
        {
            description.LowerCase();

            MapStringToInt::iterator iFind =
                statistics.mapTempoDescriptions.find(description);
            if (iFind == statistics.mapTempoDescriptions.end())
                statistics.mapTempoDescriptions[description] = 1;
            else
                (*iFind).second++;
        }
    }*/

    // Get the alternate endings
    for (size_t alternateEnding = 0,
        alternateEndingCount = GetAlternateEndingCount();
        alternateEnding != alternateEndingCount; ++alternateEnding)
    {
        AlternateEnding* pAlternateEnding = GetAlternateEnding(alternateEnding);
        wxCHECK2(pAlternateEnding != NULL, continue);

        wxString alternateEndingText = pAlternateEnding->GetText();

        MapStringToInt::iterator iFind =
            statistics.mapAlternateEndings.find(alternateEndingText);
        if (iFind == statistics.mapAlternateEndings.end())
            statistics.mapAlternateEndings[alternateEndingText] = 1;
        else
            (*iFind).second++;
    }
}
