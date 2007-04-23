/////////////////////////////////////////////////////////////////////////////
// Name:            powertabobject.cpp
// Purpose:         Provides support for polymorphic reading/writing of Power Tab objects
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 20, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "powertabobject.h"

#include "powertabfileheader.h"
#include "guitar.h"
#include "chorddiagram.h"
#include "floatingtext.h"
#include "guitarin.h"
#include "tempomarker.h"
#include "dynamic.h"
#include "alternateending.h"
#include "system.h"
#include "oldrehearsalsign.h"
#include "oldtimesignature.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Constructor/Destructor
/// Default Constructor
PowerTabObject::PowerTabObject()
{
    //------Last Checked------//
    // - Dec 21, 2004
}

/// Destructor
PowerTabObject::~PowerTabObject()
{
    //------Last Checked------//
    // - Dec 21, 2004
}

// Creation Functions
/// Creates a new object based on the class id
/// @param classId Class id for the object to create
/// @return Pointer to object if it was created, NULL if the object couldn't be created
PowerTabObject* PowerTabObject::CreateObject(const wxString& classId)
{
    // TODO: add all classes
    PowerTabObject* returnValue = NULL;
    if (strcmp(wxT("CGuitar-1"), classId) == 0)
        returnValue = new Guitar;
    else if (strcmp(wxT("CTuning-1"), classId) == 0)
        returnValue = new Tuning;
    else if (strcmp(wxT("CChordDiagram-1"), classId) == 0)
        returnValue = new ChordDiagram;
    else if (strcmp(wxT("CFloatingText-1"), classId) == 0)
        returnValue = new FloatingText;
    else if (strcmp(wxT("CGuitarIn-1"), classId) == 0)
        returnValue = new GuitarIn;
    else if (strcmp(wxT("CTempoMarker-1"), classId) == 0)
        returnValue = new TempoMarker;
    else if (strcmp(wxT("CDynamic-1"), classId) == 0)
        returnValue = new Dynamic;
    else if (strcmp(wxT("CSectionSymbol-1"), classId) == 0)
        returnValue = new AlternateEnding;
    else if (strcmp(wxT("CSection-1"), classId) == 0)
        returnValue = new System;
    else if (strcmp(wxT("CDirection-1"), classId) == 0)
        returnValue = new Direction;
    else if (strcmp(wxT("CChordText-1"), classId) == 0)
        returnValue = new ChordText;
    else if (strcmp(wxT("CRhythmSlash-1"), classId) == 0)
        returnValue = new RhythmSlash;
    else if (strcmp(wxT("CStaff-1"), classId) == 0)
        returnValue = new Staff;
    else if (strcmp(wxT("CMusicBar-1"), classId) == 0)
        returnValue = new Barline;
    else if (strcmp(wxT("CPosition-1"), classId) == 0)
        returnValue = new Position;
    else if (strcmp(wxT("CLineData-1"), classId) == 0)
        returnValue = new Note;
    else if (strcmp(wxT("CRehearsalSign-old-1"), classId) == 0)
        returnValue = new OldRehearsalSign;
    else if (strcmp(wxT("CTimeSignature-old-1"), classId) == 0)
        returnValue = new OldTimeSignature;
    wxASSERT(returnValue != NULL);
    return (returnValue);    
}

// MFC Class Functions
/// Writes the MFC class information for the object to an output stream
/// @param stream Output stream to write to
/// @return True if the class information was written, false if not
bool PowerTabObject::WriteMFCClassInformation(wxOutputStream& stream) const
{
    //------Last Checked------//
    // - Dec 24, 2004
    PowerTabOutputStream data_stream(stream);
    return (WriteMFCClassInformation(data_stream));
}

/// Writes the MFC class information for the object to a Power Tab output stream
/// @param stream Power Tab output stream to write to
/// @return True if the class information was written, false if not
bool PowerTabObject::WriteMFCClassInformation(PowerTabOutputStream& stream) const
{
    //------Last Checked------//
    // - Dec 24, 2004
    wxString className = GetMFCClassName();
    wxWord schema = GetMFCClassSchema();
    wxWord classNameLength = (wxWord)className.Length();
    
    // Write the schema and the length of the class name
    stream << schema << classNameLength;
    wxCHECK(stream.CheckState(), false);
    
    // Write the class name
    // Note: all MFC class names are stored as ANSI text
    if (!stream.WriteAnsiText(className))
        return (false);
    
    return (stream.CheckState());
}

/// Reads the MFC class information for an object from an input stream
/// @param stream Input stream to read from
/// @param version File version
/// @param classId Class id for the object
/// @return True if the object's class information was read, false if not
bool PowerTabObject::ReadMFCClassInformation(wxInputStream& stream, wxWord version, wxString& classId)
{
    //------Last Checked------//
    // - Dec 24, 2004
    PowerTabInputStream data_stream(stream);
    return (ReadMFCClassInformation(data_stream, version, classId));
}

/// Reads the MFC class information for an object from a Power Tab input stream
/// @param stream Power Tab input stream to read from
/// @param version File version
/// @param classId Class id for the object
/// @return True if the object's class information was read, false if not
bool PowerTabObject::ReadMFCClassInformation(PowerTabInputStream& stream, wxWord version, wxString& classId)
{
    //------Last Checked------//
    // - Dec 24, 2004
    classId.Clear();

    // Read the schema
	wxWord schema;
	stream >> schema;
	wxCHECK(stream.CheckState(), false);
	
	// Read the length of the class name
	wxWord length;
	stream >> length;
	wxCHECK(stream.CheckState(), false);

    if (length >= MAX_CLASSNAME_LENGTH)
    {
        stream.m_lastPowerTabError = POWERTABSTREAM_BAD_CLASS;
        return (false);
    }
    
    if (!stream.ReadAnsiText(length, classId))
    {
        stream.m_lastPowerTabError = POWERTABSTREAM_BAD_CLASS;
        return (false);
    }
    
    // Add "old" tag for outdated classes used in v1.0-1.0.2
    if (version <= PowerTabFileHeader::FILEVERSION_1_0_2)
    {
        if ((classId == wxT("CRehearsalSign")) ||
            (classId == wxT("CTimeSignature")))
            classId += wxT("-old");
    }
    
    // Attach the schema to the class id
    classId += wxString::Format(wxT("-%d"), schema);
    
    // TODO: Add class validation here?
	
    return (stream.CheckState());
}

// Serialization Functions
/// Saves a Power Tab object to an output stream
/// @param stream Output stream to save to
/// @return True if the object was saved, false if not
bool PowerTabObject::Serialize(wxOutputStream& stream)
{
    //------Last Checked------//
    // - Dec 21, 2004
    PowerTabOutputStream data_stream(stream);
    return (Serialize(data_stream));
}

/// Saves a Power Tab object to a Power Tab output stream
/// @param stream Power Tab output stream to save to
/// @return True if the object was saved, false if not
bool PowerTabObject::Serialize(PowerTabOutputStream& stream)                               
{
    //------Last Checked------//
    // - Dec 27, 2004
    return (DoSerialize(stream));
}

/// Loads a Power Tab object from an input stream
/// @param stream Input stream to load from
/// @param version File version
/// @return True if the object was loaded, false if not
bool PowerTabObject::Deserialize(wxInputStream& stream, wxWord version)
{
    //------Last Checked------//
    // - Dec 21, 2004
    PowerTabInputStream data_stream(stream);
    return (Deserialize(data_stream, version));
}

/// Loads a Power Tab object from a Power Tab input stream
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was loaded, false if not
bool PowerTabObject::Deserialize(PowerTabInputStream& stream, wxWord version)               
{
    //------Last Checked------//
    // - Dec 27, 2004
    return (DoDeserialize(stream, version));
}
