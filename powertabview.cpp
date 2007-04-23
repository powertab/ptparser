/////////////////////////////////////////////////////////////////////////////
// Name:            powertabview.cpp
// Purpose:         Displays the PowerTabDocument-based data
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 29, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "powertabview.h"

#include "powertabparser.h"             // Needed for GetMainFrame
#include "mainframe.h"
#include "powertabdocument.h"
#include "powertabviewcanvas.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(PowerTabView, wxView)

BEGIN_EVENT_TABLE(PowerTabView, wxView)
    EVT_MENU(IDM_TEST_PARSE_FILE, PowerTabView::OnTestParseFile)
END_EVENT_TABLE()

// Constructor/Destructor
/// Primary Constructor
PowerTabView::PowerTabView()
    : m_frame((wxMDIChildFrame*)NULL), m_canvas((PowerTabViewCanvas*)NULL)
{
    //------Last Checked------//
    // - Jan 27, 2005
}

/// Destructor
PowerTabView::~PowerTabView()
{
    //------Last Checked------//
    // - Jan 27, 2005
}

// Overrides
bool PowerTabView::OnCreate(wxDocument *doc, long WXUNUSED(flags))
{
    //------Last Checked------//
    // - Apr 22, 2007
    MainFrame* mainFrame = GetMainFrame();
    wxCHECK(mainFrame != NULL, false);
    
    m_frame = mainFrame->CreateChildFrame(doc, this);
    wxCHECK(m_frame != NULL, false);
    
    m_frame->SetTitle(wxT("PowerTabView"));

    m_canvas = CreateCanvas(this, m_frame);
    wxCHECK(m_canvas != NULL, false);
    
#ifdef __X__
    // X seems to require a forced resize
    int x, y;
    m_frame->GetSize(&x, &y);
    m_frame->SetSize(-1, -1, x, y);
#endif

    m_frame->Show(true);
    Activate(true);

    return (true);
}

void PowerTabView::OnDraw(wxDC* dc)
{
    //------Last Checked------//
    // - Jan 27, 2005
    
    // Get a pointer to the document
    PowerTabDocument* document = (PowerTabDocument*)GetDocument();
    wxCHECK2(document != NULL, return);
    
    // Simply draw the title and artist
    dc->SetFont(*wxNORMAL_FONT);
    dc->SetPen(*wxBLACK_PEN);
    
    PowerTabFileHeader& header = document->GetHeaderRef();
    dc->DrawText(header.GetSongTitle(), 0, 0);
    dc->DrawText(header.GetSongArtist(), 0, 20);
}

void PowerTabView::OnUpdate(wxView* WXUNUSED(sender), wxObject* WXUNUSED(hint))
{
    //------Last Checked------//
    // - Apr 22, 2007
}

bool PowerTabView::OnClose(bool deleteWindow)
{
    //------Last Checked------//
    // - Jan 27, 2005
    
    // This code is taken from wxWidgets examples...
    
    if (!GetDocument()->Close())
        return (false);

    // Clear the canvas in  case we're in single-window mode,
    // and the canvas stays.
    /*  canvas->Clear();
    canvas->view = (wxView *) NULL;
    canvas = (MyCanvas *) NULL;*/

    wxString title(wxTheApp->GetAppName());
    if (m_frame)
        m_frame->SetTitle(title);

    SetFrame((wxFrame*)NULL);

    Activate(false);
        
    if (deleteWindow)
    {
        delete m_frame;
        return (true);
    }
    return (true);
}

// Warning wrapper
#ifdef __WXMSW__
#pragma warning(push)
#pragma warning(disable:4189)   // Disable local variable is initialized but not referenced warning
#endif

/// Command Events
///< This code demonstrates how to parse a loaded Power Tab document
///< You could also load a document directly using Load
void PowerTabView::OnTestParseFile(wxCommandEvent& WXUNUSED(event))
{
    // Menu Test -> Parse File
    //------Last Checked------//
    // - Apr 22, 2007
    
    // Get the active document
    PowerTabDocument* document = (PowerTabDocument*)GetDocument();
    wxCHECK2(document != NULL, return);
    
    wxLongLong startTime = ::wxGetLocalTimeMillis();
    
    // Get the header
    PowerTabFileHeader& header = document->GetHeaderRef();
    
    // File version that the file was saved as; the document automatically
    // converts to the latest version during deserialization
    wxWord version = header.GetVersion();

    // In Power Tab Editor v1.7, most of the header data is accessable via the Song Property Sheet:
    // Menu View -> File Information
    // Menu View -> Performance Notes
    // Menu View -> Lyrics
    
    // File is a song
    if (header.IsSong())
    {              
        wxByte contentType = header.GetSongContentType();
        wxString title = header.GetSongTitle();
        wxString artist = header.GetSongArtist();
        
        wxByte releaseType = header.GetSongReleaseType();

        // Audio release     
        if (releaseType == PowerTabFileHeader::RELEASETYPE_PUBLIC_AUDIO)
        {
            wxByte releaseType = header.GetSongAudioReleaseType();
            wxString releaseTitle = header.GetSongAudioReleaseTitle();
            wxWord year = header.GetSongAudioReleaseYear();
            bool live = header.IsSongAudioReleaseLive();
        }
        // Video release
        else if (releaseType == PowerTabFileHeader::RELEASETYPE_PUBLIC_VIDEO)
        {
            wxString releaseTitle = header.GetSongVideoReleaseTitle();
            bool live = header.IsSongVideoReleaseLive();
        }
        // Bootleg
        else if (releaseType == PowerTabFileHeader::RELEASETYPE_BOOTLEG)
        {
            wxString releaseTitle = header.GetSongBootlegTitle();
            wxDateTime bootlegDate = header.GetSongBootlegDate();
        }
        // Not released
        else if (releaseType == PowerTabFileHeader::RELEASETYPE_NOTRELEASED)
        {
            // no extra data for this data
        }
                        
        // If author is known, get the composer and lyricist; otherwise, song is traditional
        if (header.GetSongAuthorType() == PowerTabFileHeader::AUTHORTYPE_AUTHORKNOWN)
        {
            wxString composer = header.GetSongComposer();
            wxString lyricist = header.GetSongLyricist();
        }
        
        wxString arranger = header.GetSongArranger();
        
        wxString guitarScoreTranscriber = header.GetSongGuitarScoreTranscriber();
        wxString bassScoreTranscriber = header.GetSongBassScoreTranscriber();
        
        wxString copyright = header.GetSongCopyright();
                   
        wxString lyrics = header.GetSongLyrics();
        
        wxString guitarScoreNotes = header.GetSongGuitarScoreNotes();
        wxString bassScoreNotes = header.GetSongBassScoreNotes();
    }
    // File is a lesson
    else if (header.IsLesson())
    {
        wxString title = header.GetLessonTitle();
        wxString subtitle = header.GetLessonSubtitle();
        wxWord musicStyle = header.GetLessonMusicStyle();
        wxByte level = header.GetLessonLevel();
        wxString author = header.GetLessonAuthor();
        wxString notes = header.GetLessonNotes();
        wxString copyright = header.GetLessonCopyright();
    }
    
    wxUint8 scoreIndex = 0;
    // There are two scores in each document:
    // 1) Guitar score
    // 2) Bass score
    for (; scoreIndex < 2; scoreIndex++)
    {
        // Get the score
        Score* score = NULL;
        
        if (scoreIndex == 0)
            score = document->GetGuitarScore();
        else
            score = document->GetBassScore();
        
        wxCHECK2(score != NULL, continue);
        
        // Parse the guitars in the score
        // In Power Tab Editor v1.7, the guitar data can be accessed via the Guitar Property Sheet:
        // Menu Guitar -> Setup
        wxUint32 guitarIndex = 0;
        wxUint32 guitarCount = score->GetGuitarCount();
        for (; guitarIndex < guitarCount; guitarIndex++)
        {
            Guitar* guitar = score->GetGuitar(guitarIndex);
            wxCHECK2(guitar != NULL, continue);
    
            wxByte number = guitar->GetNumber();        
            wxString description = guitar->GetDescription();
            wxByte preset = guitar->GetPreset();
            wxByte initialVolume = guitar->GetInitialVolume();
            wxByte pan = guitar->GetPan();
            wxByte reverb = guitar->GetReverb();
            wxByte chorus = guitar->GetChorus();
            wxByte tremolo = guitar->GetTremolo();
            wxByte phaser = guitar->GetPhaser();
            wxByte capo = guitar->GetCapo();
            
            const Tuning& tuning = guitar->GetTuning();
            wxString name = tuning.GetName();
            wxInt8 musicNotationOffset = tuning.GetMusicNotationOffset();
            bool usesSharps = tuning.UsesSharps();
            
            // Get the MIDI note pitch for each string, starting with the highest string
            // Highest string = High E on standard guitar tuning
            size_t string = 0;
            size_t stringCount = tuning.GetStringCount();
            for (; string < stringCount; string++)
            {
                // MIDI note pitch (see MIDI_NOTE_xx constants in generalmidi.h)
                wxByte note = tuning.GetNote(string);
            }
        }
        
        // Parse the chord diagrams in the score
        // In Power Tab Editor v1.7, chord diagrams can be accessed via the Guitar Property Sheet:
        // Menu Guitar -> Chord Diagram List
        
        // The chord diagrams appear in the Chord Diagram List in the order they are stored in the chord diagram
        // array in the score
        wxUint32 chordDiagramIndex = 0;
        wxUint32 chordDiagramCount = score->GetChordDiagramCount();
        for (; chordDiagramIndex < chordDiagramCount; chordDiagramIndex++)
        {
            ChordDiagram* chordDiagram = score->GetChordDiagram(chordDiagramIndex);
            wxCHECK2(chordDiagram != NULL, continue);
            
            // In Power Tab Editor v1.7, chord name data can be accessed via the Chord Name dialog:
            // Menu Text -> Chord Name
            const ChordName& chordName = chordDiagram->GetChordNameConstRef();
            wxByte tonicKey = 0;
            wxByte tonicKeyVariation = 0;
            chordName.GetTonic(tonicKey, tonicKeyVariation);
            wxByte bassNoteKey = 0;
            wxByte bassNoteKeyVariation = 0;
            chordName.GetBassNote(bassNoteKey, bassNoteKeyVariation);
            
            wxByte formula = chordName.GetFormula();
            bool brackets = chordName.HasBrackets();
            bool noChord = chordName.IsNoChord();
            
            wxWord formulaModificationFlag = ChordName::extended9th;
            for (; formulaModificationFlag <= ChordName::suspended4th; formulaModificationFlag *= 2)
            {
                if (chordName.IsFormulaModificationFlagSet(formulaModificationFlag))
                {
                    
                }
                
                // Block overflow
                if (formulaModificationFlag == ChordName::suspended4th)
                    break;
            }
            
            if (chordName.IsFretPositionUsed())
            {
                wxByte fretPosition = chordName.GetFretPosition();
            }
            
            if (chordName.IsTypeUsed())
            {
                wxByte type = chordName.GetType();   
            }

            wxByte topFret = chordDiagram->GetTopFret();
            
            size_t string = 0;
            size_t stringCount = chordDiagram->GetStringCount();
            for (; string < stringCount; string++)
            {
                wxByte fretNumber = chordDiagram->GetFretNumber(string);
            }
        }
        
        // Parse the floating text items in the score
        // In Power Tab Editor v1.7, floating text items are created using:
        // Menu Text -> Insert
        
        // Floating text items are stored in the array by order of their rect.top and
        // rect.left values
        // i.e. An item at left = 40, top = 100 is stored prior to left = 10, top = 120
        wxUint32 floatingTextIndex = 0;
        wxUint32 floatingTextCount = score->GetFloatingTextCount();
        for (; floatingTextIndex < floatingTextCount; floatingTextIndex++)
        {
            FloatingText* floatingText = score->GetFloatingText(floatingTextIndex);
            wxCHECK2(floatingText != NULL, continue);
            
            wxString text = floatingText->GetText();
            wxRect rect = floatingText->GetRect();
            wxByte alignment = floatingText->GetAlignment();
            bool border = floatingText->HasBorder();
            
            // Font setting for the text
            const FontSetting& fontSetting = floatingText->GetFontSettingConstRef();
            wxString faceName = fontSetting.GetFaceName();
            wxInt32 pointSize = fontSetting.GetPointSize();
            wxInt32 weight = fontSetting.GetWeight();
            bool italic = fontSetting.IsItalic();
            bool underline = fontSetting.IsUnderline();
            bool strikeOut = fontSetting.IsStrikeOut();
            wxColor color = fontSetting.GetColor();
        }
        
        // Parse the guitar ins in the score
        // In Power Tab Editor v1.7, guitar ins can be accessed via the Guitar In dialog:
        // Menu Guitar -> Guitar In
        
        // Guitar Ins are stored in the array by order of their system, position and 
        // staff values
        wxUint32 guitarInIndex = 0;
        wxUint32 guitarInCount = score->GetGuitarInCount();
        for (; guitarInIndex < guitarInCount; guitarInIndex++)
        {
            GuitarIn* guitarIn = score->GetGuitarIn(guitarInIndex);
            wxCHECK2(guitarIn != NULL, continue);
            
            wxWord system = guitarIn->GetSystem();
            wxByte staff = guitarIn->GetStaff();
            wxByte position = guitarIn->GetPosition();
            
            if (guitarIn->HasStaffGuitarsSet())
            {
                wxByte staffGuitars = guitarIn->GetStaffGuitars();
            }
            
            if (guitarIn->HasRhythmSlashGuitarsSet())
            {
                wxByte rhythmSlashGuitars = guitarIn->GetRhythmSlashGuitars();
            }
        }
        
        // Parse the tempo markers in the score
        // In Power Tab Editor v1.7, tempo markers can be accessed via the Tempo Marker dialog:
        // Menu Music Symbols -> Tempo Marker
        // and the Alteration of Pace dialog:
        // Menu Music Symbols -> Alteration of Pace
        
        // Tempo Markers are stored in the array by order of their system, position and 
        // staff values
        wxUint32 tempoMarkerIndex = 0;
        wxUint32 tempoMarkerCount = score->GetTempoMarkerCount();
        for (; tempoMarkerIndex < tempoMarkerCount; tempoMarkerIndex++)
        {
            TempoMarker* tempoMarker = score->GetTempoMarker(tempoMarkerIndex);
            wxCHECK2(tempoMarker != NULL, continue);
            
            if (tempoMarker->IsStandardMarker())
            {
                wxByte beatType = tempoMarker->GetBeatType();
                wxUint32 beatsPerMinute = tempoMarker->GetBeatsPerMinute();
            }
            else if (tempoMarker->IsListesso())
            {
                wxByte beatType = tempoMarker->GetBeatType();
                wxByte listessoBeatType = tempoMarker->GetBeatType();
            }
            else if (tempoMarker->IsAlterationOfPace())
            {
                if (tempoMarker->IsAccelerando())
                {
                }
                else if (tempoMarker->IsRitardando())
                {
                }
            }
            
            if (tempoMarker->HasTripletFeel())
            {
                wxByte tripletFeelType = tempoMarker->GetTripletFeelType();
            }
            
            wxString description = tempoMarker->GetDescription();            
        }
        
        // Parse the dynamics in the score
        // In Power Tab Editor v1.7, dynamics can be accessed via the Dynamic dialog:
        // Menu Music Symbols -> Dynamic
        
        // Dynamics are stored in the array by order of their system, position and
        // staff values
        wxUint32 dynamicIndex = 0;
        wxUint32 dynamicCount = score->GetDynamicCount();
        for (; dynamicIndex < dynamicCount; dynamicIndex++)
        {
            Dynamic* dynamic = score->GetDynamic(dynamicIndex);
            wxCHECK2(dynamic != NULL, continue);
            
            wxWord system = dynamic->GetSystem();
            wxByte staff = dynamic->GetStaff();
            wxByte position = dynamic->GetPosition();
            
            // Staff volume is set
            if (dynamic->IsStaffVolumeSet())
            {
                wxByte staffVolume = dynamic->GetStaffVolume();
            }
            
            // Rhythm slash volume is set
            if (dynamic->IsRhythmSlashVolumeSet())
            {
                wxByte rhythmSlashVolume = dynamic->GetRhythmSlashVolume();
            }
        }
        
        // Parse the alternate endings in the score
        // In Power Tab Editor v1.7, alternate endings can be accessed via the Repeat Ending dialog:
        // Menu Music Symbols -> Repeat Ending
        
        // Alternate endings are stored in the array by order of their system and
        // position values
        wxUint32 alternateEndingIndex = 0;
        wxUint32 alternateEndingCount = score->GetAlternateEndingCount();
        for (; alternateEndingIndex < alternateEndingCount; alternateEndingIndex++)
        {
            AlternateEnding* alternateEnding = score->GetAlternateEnding(alternateEndingIndex);
            wxCHECK2(alternateEnding != NULL, continue);
            
            wxWord system = alternateEnding->GetSystem();
            wxByte position = alternateEnding->GetPosition();
            
            // Determine which numbers are set
            wxWord number = 1;            
            for (; number <= AlternateEnding::dalSegnoSegno; number++)
            {
                if (alternateEnding->IsNumberSet(number))
                {
                    // Number is set
                }
            }
        }
        
        // Parse the systems in the score
        // In Power Tab Editor v1.7, systems can be accessed via the Section menu:
        // Menu Section -> New Section
        
        // Systems are stored in the array by order they are drawn in the score
        wxUint32 systemIndex = 0;
        wxUint32 systemCount = score->GetSystemCount();
        for (; systemIndex < systemCount; systemIndex++)
        {
            System* system = score->GetSystem(systemIndex);
            wxCHECK2(system != NULL, continue);
    
            wxRect rect = system->GetRect();
            wxByte positionSpacing = system->GetPositionSpacing();

            // Parse the directions in the system
            // In Power Tab Editor v1.7, directions can be accessed via the Musical Direction dialog:
            // Menu Music Symbols -> Musical Direction
            wxUint32 directionIndex = 0;
            wxUint32 directionCount = system->GetDirectionCount();
            for (; directionIndex < directionCount; directionIndex++)
            {
                Direction* direction = system->GetDirection(directionIndex);
                wxCHECK2(direction != NULL, continue);
                
                wxUint32 position = direction->GetPosition();
                
                // There may be up to 3 symbols per object
                size_t symbolIndex = 0;
                size_t symbolCount = direction->GetSymbolCount();
                for (; symbolIndex < symbolCount; symbolIndex++)
                {
                    wxByte symbolType = 0;
                    wxByte activeSymbol = 0;
                    wxByte repeatNumber = 0;
                    direction->GetSymbol(symbolIndex, symbolType, activeSymbol, repeatNumber);
                }
            }
            
            // Parse the chord text items in the system
            // In Power Tab Editor v1.7, chord text/chord name data can be accessed via the Chord Name dialog:
            // Menu Text -> Chord Name
            wxUint32 chordTextIndex = 0;
            wxUint32 chordTextCount = system->GetChordTextCount();
            for (; chordTextIndex < chordTextCount; chordTextIndex++)
            {
                ChordText* chordText = system->GetChordText(chordTextIndex);
                wxCHECK2(chordText != NULL, continue);
                
                wxUint32 positon = chordText->GetPosition();
                
                const ChordName& chordName = chordText->GetChordNameConstRef();
                wxByte tonicKey = 0;
                wxByte tonicKeyVariation = 0;
                chordName.GetTonic(tonicKey, tonicKeyVariation);
                wxByte bassNoteKey = 0;
                wxByte bassNoteKeyVariation = 0;
                chordName.GetBassNote(bassNoteKey, bassNoteKeyVariation);
                
                wxByte formula = chordName.GetFormula();
                bool brackets = chordName.HasBrackets();
                bool noChord = chordName.IsNoChord();
                
                wxWord formulaModificationFlag = ChordName::extended9th;
                for (; formulaModificationFlag <= ChordName::suspended4th; formulaModificationFlag *= 2)
                {
                    if (chordName.IsFormulaModificationFlagSet(formulaModificationFlag))
                    {
                        
                    }
                    
                    // Block overflow
                    if (formulaModificationFlag == ChordName::suspended4th)
                        break;
                }
                
                if (chordName.IsFretPositionUsed())
                {
                    wxByte fretPosition = chordName.GetFretPosition();
                }
                
                if (chordName.IsTypeUsed())
                {
                    wxByte type = chordName.GetType();   
                }
            }

            // Parse the rhythm slashes in the system
            // In Power Tab Editor v1.7, rhythm slash data can be accessed via the Rhy. Slashes menu
            wxUint32 rhythmSlashIndex = 0;
            wxUint32 rhythmSlashCount = system->GetRhythmSlashCount();
            for (; rhythmSlashIndex < rhythmSlashCount; rhythmSlashIndex++)
            {
                RhythmSlash* rhythmSlash = system->GetRhythmSlash(rhythmSlashIndex);
                wxCHECK2(rhythmSlash != NULL, continue);
                
                wxUint32 position = rhythmSlash->GetPosition();
                wxByte durationType = rhythmSlash->GetDurationType();
                wxByte previousDurationType = rhythmSlash->GetPreviousBeamDurationType();
                
                bool beamStart = rhythmSlash->IsBeamStart();
                bool fractionalBeam = rhythmSlash->HasFractionalBeam();
                bool beamEnd = rhythmSlash->IsBeamEnd();
                
                bool tripletStart = rhythmSlash->IsTripletStart();
                bool tripletMiddle = rhythmSlash->IsTripletMiddle();
                bool tripletEnd = rhythmSlash->IsTripletEnd();
                
                bool dotted = rhythmSlash->IsDotted();
                bool doubleDotted = rhythmSlash->IsDoubleDotted();
                bool rest = rhythmSlash->IsRest();
                bool tied = rhythmSlash->IsTied();
                bool muted = rhythmSlash->IsMuted();
                bool staccato = rhythmSlash->IsStaccato();
                bool pickstrokeUp = rhythmSlash->HasPickStrokeUp();
                bool pickstrokeDown = rhythmSlash->HasPickStrokeDown();
                bool arpeggioUp = rhythmSlash->HasArpeggioUp();
                bool arpeggioDown = rhythmSlash->HasArpeggioDown();
                bool tripletFeel1st = rhythmSlash->IsTripletFeel1st();
                bool tripletFeel2nd = rhythmSlash->IsTripletFeel2nd();
                bool marcato = rhythmSlash->HasMarcato();
                bool sforzando = rhythmSlash->HasSforzando();
                bool slideIntoFromAbove = rhythmSlash->HasSlideIntoFromAbove();
                bool slideIntoFromBelow = rhythmSlash->HasSlideIntoFromBelow();
                bool slideOutOfDownwards = rhythmSlash->HasSlideOutOfDownwards();
                bool slideOutOfUpwards = rhythmSlash->HasSlideOutOfUpwards();
                
                // TODO: If has single note
                {
                    wxByte stringNumber = 0;
                    wxByte fretNumber = 0;
                    rhythmSlash->GetSingleNoteData(stringNumber, fretNumber);
                }
            }
            
            // Parse the barline at the start of the system
            {
                const Barline& startBar = system->GetStartBarConstRef();
                wxByte type = startBar.GetType();
                if (startBar.IsRepeatEnd())
                {
                    wxUint32 repeatCount = startBar.GetRepeatCount();
                }
                const KeySignature& keySignature = startBar.GetKeySignatureConstRef();
                wxByte keyType = 0;
                wxByte keyAccidentals = 0;
                keySignature.GetKey(keyType, keyAccidentals);
                if (keySignature.IsShown())
                {
                }
                if (keySignature.IsCancellation())
                {
                }
                
                const TimeSignature& timeSignature = startBar.GetTimeSignatureConstRef();
                wxByte beatsPerMeasure = 0;
                wxByte beatAmount = 0;
                timeSignature.GetMeter(beatsPerMeasure, beatAmount);
                if (timeSignature.IsCutTime())
                {
                }
                if (timeSignature.IsCommonTime())
                {
                }
                
                wxByte beat1 = 0;
                wxByte beat2 = 0;
                wxByte beat3 = 0;
                wxByte beat4 = 0;
                timeSignature.GetBeamingPattern(beat1, beat2, beat3, beat4);
                if (timeSignature.IsShown())
                {
                }
                wxByte pulses = timeSignature.GetPulses();
                
                const RehearsalSign& rehearsalSign = startBar.GetRehearsalSignConstRef();
                if (rehearsalSign.IsSet())
                {
                    wxInt8 letter = rehearsalSign.GetLetter();
                    wxString description = rehearsalSign.GetDescription();
                }
            }
            
            // Parse the barlines within the system
            wxUint32 barlineIndex = 0;
            wxUint32 barlineCount = system->GetBarlineCount();
            for (; barlineIndex < barlineCount; barlineIndex++)
            {
                Barline* barline = system->GetBarline(barlineIndex);
                wxCHECK2(barline != NULL, continue);
                
                wxUint32 position = barline->GetPosition();
                
                const KeySignature& keySignature = barline->GetKeySignatureConstRef();
                wxByte keyType = 0;
                wxByte keyAccidentals = 0;
                keySignature.GetKey(keyType, keyAccidentals);
                if (keySignature.IsShown())
                {
                }
                if (keySignature.IsCancellation())
                {
                }
                
                const TimeSignature& timeSignature = barline->GetTimeSignatureConstRef();
                wxByte beatsPerMeasure = 0;
                wxByte beatAmount = 0;
                timeSignature.GetMeter(beatsPerMeasure, beatAmount);
                if (timeSignature.IsCutTime())
                {
                }
                if (timeSignature.IsCommonTime())
                {
                }
                
                wxByte beat1 = 0;
                wxByte beat2 = 0;
                wxByte beat3 = 0;
                wxByte beat4 = 0;
                timeSignature.GetBeamingPattern(beat1, beat2, beat3, beat4);
                if (timeSignature.IsShown())
                {
                }
                wxByte pulses = timeSignature.GetPulses();
                
                const RehearsalSign& rehearsalSign = barline->GetRehearsalSignConstRef();
                if (rehearsalSign.IsSet())
                {
                    wxInt8 letter = rehearsalSign.GetLetter();
                    wxString description = rehearsalSign.GetDescription();
                }
            }
            
            // Parse the barline at the end of the system
            {
                const Barline& endBar = system->GetEndBarConstRef();
                wxByte type = endBar.GetType();
                if (endBar.IsRepeatEnd())
                {
                    wxUint32 repeatCount = endBar.GetRepeatCount();
                }
                const KeySignature& keySignature = endBar.GetKeySignatureConstRef();
                wxByte keyType = 0;
                wxByte keyAccidentals = 0;
                keySignature.GetKey(keyType, keyAccidentals);
                if (keySignature.IsShown())
                {
                }
                if (keySignature.IsCancellation())
                {
                }
                
                const TimeSignature& timeSignature = endBar.GetTimeSignatureConstRef();
                wxByte beatsPerMeasure = 0;
                wxByte beatAmount = 0;
                timeSignature.GetMeter(beatsPerMeasure, beatAmount);
                if (timeSignature.IsCutTime())
                {
                }
                if (timeSignature.IsCommonTime())
                {
                }
                
                wxByte beat1 = 0;
                wxByte beat2 = 0;
                wxByte beat3 = 0;
                wxByte beat4 = 0;
                timeSignature.GetBeamingPattern(beat1, beat2, beat3, beat4);
                if (timeSignature.IsShown())
                {
                }
                wxByte pulses = timeSignature.GetPulses();
                
                const RehearsalSign& rehearsalSign = endBar.GetRehearsalSignConstRef();
                if (rehearsalSign.IsSet())
                {
                    wxInt8 letter = rehearsalSign.GetLetter();
                    wxString description = rehearsalSign.GetDescription();
                }
            }
            
            // Parse the staves in the system
            // In Power Tab Editor v1.7, staves can be accessed via the Section menu:
            // Menu Section -> Attach Staff
            // and by clicking the clef on the standard notation standard staff and
            // by clicking the "TAB" clef on the tablature staff
            wxUint32 staffIndex = 0;
            wxUint32 staffCount = system->GetStaffCount();
            for (; staffIndex < staffCount; staffIndex++)
            {
                Staff* staff = system->GetStaff(staffIndex);
                wxCHECK2(staff != NULL, continue);
                
                wxByte clef = staff->GetClef();
                wxByte tablatureStaffType = staff->GetTablatureStaffType();
                
                // Parse the positions in each voice
                wxUint32 voice = 0;
                for (; voice < NUM_STAFF_VOICES; voice++)
                {
                    wxUint32 positionIndex = 0;
                    wxUint32 positionCount = staff->GetPositionCount(voice);
                    for (; positionIndex < positionCount; positionIndex++)
                    {
                        Position* position = staff->GetPosition(voice, positionIndex);
                        wxCHECK2(position != NULL, continue);
                    
                        wxUint32 positionIndex = 0;
                        wxUint32 positionCount = staff->GetPositionCount(voice);
                        for (; positionIndex < positionCount; positionIndex++)
                        {
                            Position* position = staff->GetPosition(voice, positionIndex);
                            wxCHECK2(position != NULL, continue);
                            
                            wxUint32 position2 = position->GetPosition();
                            wxByte durationType = position->GetDurationType();
                            if (position->HasIrregularGroupingTiming())
                            {
                                wxByte notesPlayed = 0;
                                wxByte notesPlayedOver = 0;
                                position->GetIrregularGroupingTiming(notesPlayed, notesPlayedOver);
                            }
                            wxByte previousBeamDurationType = position->GetPreviousBeamDurationType();
                            bool beamStart = position->IsBeamStart();
                            bool fractionalLeftBeam = position->HasFractionalLeftBeam();
                            bool fractionalRightBeam = position->HasFractionalRightBeam();
                            bool beamEnd = position->IsBeamEnd();
                            
                            bool dotted = position->IsDotted();
                            bool doubleDotted = position->IsDoubleDotted();
                            bool rest = position->IsRest();
                            bool vibrato = position->HasVibrato();
                            bool wideVibrato = position->HasWideVibrato();
                            bool arpeggioUp = position->HasArpeggioUp();
                            bool arpeggioDown = position->HasArpeggioDown();
                            bool pickstrokeUp = position->HasPickStrokeUp();
                            bool pickstrokeDown = position->HasPickStrokeDown();
                            bool staccato = position->IsStaccato();
                            bool marcato = position->HasMarcato();
                            bool sforzando = position->HasSforzando();
                            bool tremoloPicking = position->HasTremoloPicking();
                            bool palmMuting = position->HasPalmMuting();
                            bool tap = position->HasTap();
                            bool acciaccatura = position->IsAcciaccatura();
                            bool tripletFeel1st = position->IsTripletFeel1st();
                            bool tripletFeel2nd = position->IsTripletFeel2nd();
                            bool letRing = position->HasLetRing();
                            bool fermata = position->HasFermata();
                            bool irregularGroupingStart = position->IsIrregularGroupingStart();
                            bool irregularGroupingMiddle = position->IsIrregularGroupingMiddle();
                            bool irregularGroupingEnd = position->IsIrregularGroupingEnd();
                            
                            if (position->HasVolumeSwell())
                            {
                                wxByte startVolume = 0;
                                wxByte endVolume = 0;
                                wxByte duration = 0;
                                position->GetVolumeSwell(startVolume, endVolume, duration);
                            }
                            
                            if (position->HasTremoloBar())
                            {
                                wxByte type = 0;
                                wxByte duration = 0;
                                wxByte pitch = 0;
                                position->GetTremoloBar(type, duration, pitch);
                            }
                            
                            // Parse the notes
                            // In Power Tab Editor v1.7, note data can be accessed via the Notes menu, as well as
                            // the Tab Symbols menu
                            wxUint32 noteIndex = 0;
                            wxUint32 noteCount = position->GetNoteCount();
                            for (; noteIndex < noteCount; noteIndex++)
                            {
                                Note* note = position->GetNote(noteIndex);
                                wxCHECK2(note != NULL, continue);
                                
                                wxUint32 string = note->GetString();
                                wxUint32 fretNumber = note->GetFretNumber();
                                bool tied = note->IsTied();
                                bool muted = note->IsMuted();
                                bool tieWrap = note->HasTieWrap();
                                bool hammerOn = note->HasHammerOn();
                                bool hammerOnFromNowhere = note->HasHammerOnFromNowhere();
                                bool pullOff = note->HasPullOff();
                                bool pullOffToNowhere = note->HasPullOffToNowhere();
                                bool naturalHarmonic = note->IsNaturalHarmonic();
                                bool ghostNote = note->IsGhostNote();
                                bool octave8va = note->IsOctave8va();
                                bool octave15ma = note->IsOctave15ma();
                                bool octave8vb = note->IsOctave8vb();
                                bool octave15mb = note->IsOctave15mb();
                                
                                if (note->HasSlideInto())
                                {
                                    wxByte type = 0;
                                    note->GetSlideInto(type);
                                }
                                
                                if (note->HasSlideOutOf())
                                {
                                    wxByte type = 0;
                                    wxInt8 steps = 0;
                                    note->GetSlideOutOf(type, steps);
                                }
                                
                                if (note->HasBend())
                                {
                                    wxByte type = 0;
                                    wxByte bentPitch = 0;
                                    wxByte releasePitch = 0;
                                    wxByte duration = 0;
                                    wxByte drawStartPoint = 0;
                                    wxByte drawEndPoint = 0;
                                    note->GetBend(type, bentPitch, releasePitch, duration, drawStartPoint, drawEndPoint);
                                }
                                
                                if (note->HasTappedHarmonic())
                                {
                                    wxByte tappedFretNumber = 0;
                                    note->GetTappedHarmonic(tappedFretNumber);
                                }
                                
                                if (note->HasTrill())
                                {
                                    wxByte trilledFretNumber = 0;
                                    note->GetTrill(trilledFretNumber);
                                }
                                
                                if (note->HasArtificialHarmonic())
                                {
                                    wxByte key = 0;
                                    wxByte keyVariation = 0;
                                    wxByte octave = 0;
                                    note->GetArtificialHarmonic(key, keyVariation, octave);
                                }
                            }
                        }
                    }
                }
            }
        }
    }   
    
    // In Power Tab Editor v1.7, font settings can be accessed via the Song
    // Property Sheet:
    // Menu View -> Fonts
    {
        const FontSetting& chordNameFontSetting =
            document->GetChordNameFontSettingConstRef();
        wxString faceName = chordNameFontSetting.GetFaceName();
        wxInt32 pointSize = chordNameFontSetting.GetPointSize();
        wxInt32 weight = chordNameFontSetting.GetWeight();
        bool italic = chordNameFontSetting.IsItalic();
        bool underline = chordNameFontSetting.IsUnderline();
        bool strikeOut = chordNameFontSetting.IsStrikeOut();
        wxColor color = chordNameFontSetting.GetColor();
    }
    
    {            
        const FontSetting& tablatureNumbersFontSetting =
            document->GetTablatureNumbersFontSettingConstRef();
        wxString faceName = tablatureNumbersFontSetting.GetFaceName();
        wxInt32 pointSize = tablatureNumbersFontSetting.GetPointSize();
        wxInt32 weight = tablatureNumbersFontSetting.GetWeight();
        bool italic = tablatureNumbersFontSetting.IsItalic();
        bool underline = tablatureNumbersFontSetting.IsUnderline();
        bool strikeOut = tablatureNumbersFontSetting.IsStrikeOut();
        wxColor color = tablatureNumbersFontSetting.GetColor();
    }
    
    // In Power Tab Editor v1.7, tablature line spacing values can be accessed
    // via the Line Height submenu on the Section menu
    wxUint32 tablatureStaffLineSpacing = document->GetTablatureStaffLineSpacing();
    
    // In Power Tab Editor v1.7, fade values can be accessed via the Fade dialog:
    // Menu Music Symbols -> Fade
    wxUint32 fadeIn = document->GetFadeIn();
    wxUint32 fadeOut = document->GetFadeOut();
    
    wxLongLong totalTime = ::wxGetLocalTimeMillis() - startTime;
    double milliseconds = ((double)totalTime.ToLong()) / 1000.0;
        
    wxMessageBox(wxString::Format(wxT("File parsed in %.3f seconds."),
        milliseconds), wxTheApp->GetAppName(), wxICON_INFORMATION);
}

// Warning wrapper
#ifdef __WXMSW__
#pragma warning(pop)
#endif

// Operations
/// Creates the canvas used by the view
/// @param view View to be associated with the canvas
/// @param parent Frame that will hold the view
/// @return Pointer to new canvas if created, NULL if creation failed
PowerTabViewCanvas* PowerTabView::CreateCanvas(wxView* view, wxMDIChildFrame* parent)
{
    //------Last Checked------//
    // - Jan 27, 2005

    // Get the dimensions of the frame and use them to size the window
    int width = 0;
    int height = 0;
    parent->GetClientSize(&width, &height);

    // Create the canvas
    PowerTabViewCanvas* canvas = new PowerTabViewCanvas(view, parent,
        wxPoint(0, 0), wxSize(width, height), 0);
    wxCHECK(canvas != NULL, false);
    
    // Assign the cursor and give it scrollbars
    canvas->SetCursor(wxCursor(wxCURSOR_PENCIL));
    canvas->SetScrollbars(20, 20, 50, 50);

    return (canvas);
}
