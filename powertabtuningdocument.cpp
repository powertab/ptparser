/////////////////////////////////////////////////////////////////////////////
// Name:            powertabtuningdocument.cpp
// Purpose:         Loads and saves Power Tab tuning files
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 30, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "powertabtuningdocument.h"

#include "powertabfileheader.h"         // Needed for file version constants

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(PowerTabTuningDocument, wxDocument)

// Constructor/Destructor
/// Default Constructor
PowerTabTuningDocument::PowerTabTuningDocument() :
    m_displayErrors(true)
{
    //------Last Checked------//
    // - Dec 30, 2004
}

/// Destructor
PowerTabTuningDocument::~PowerTabTuningDocument()
{
    //------Last Checked------//
    // - Dec 30, 2004
}

// Load Functions
#if wxUSE_STD_IOSTREAM
wxSTD istream& PowerTabTuningDocument::LoadObject(wxSTD istream& stream)
{
    //------Last Checked------//
    // - Dec 30, 2004
    return (stream);
}
#else
/// Loads the document data from an input stream
/// @param stream Input stream to load from
/// @return Input stream
wxInputStream& PowerTabTuningDocument::LoadObject(wxInputStream& stream)
{
    //------Last Checked------//
    // - Dec 30, 2004
    PowerTabInputStream data_stream(stream);
    m_tuningArray.Deserialize(data_stream,
        PowerTabFileHeader::FILEVERSION_CURRENT);
    
    if (!data_stream.CheckState())
    {
        DeleteContents();
        if (AreErrorsDisplayed())
            ReportLoadSaveError(GetFilename(), data_stream.TellI(),
            data_stream.GetLastErrorMessage(), false);
    }
        
    return (stream);
}
#endif

// Save Functions
#if wxUSE_STD_IOSTREAM
wxSTD ostream& PowerTabTuningDocument::SaveObject(wxSTD ostream& stream)
{
    //------Last Checked------//
    // - Dec 30, 2004
    return (stream);
}
#else
/// Saves the document data to an output stream
/// @param stream Output stream to save to
/// @return Output stream
wxOutputStream& PowerTabTuningDocument::SaveObject(wxOutputStream& stream)
{
    //------Last Checked------//
    // - Dec 30, 2004
    PowerTabOutputStream data_stream(stream);
    m_tuningArray.Serialize(data_stream);

    if (!data_stream.CheckState())
    {
        if (AreErrorsDisplayed())
        {
            ReportLoadSaveError(GetFilename(), data_stream.TellO(),
                data_stream.GetLastErrorMessage(), true);
        }
    }
                  
    return (stream);
}
#endif

// Error Functions
/// Displays an error message related to a load or save operation
/// @param fileName Name of the file that experienced the error
/// @param offset Offset within the file where the error occurred
/// @param errorMessage Error message text
/// @param saving Determines whether the error occurred during a save operation
/// or a load operation
void PowerTabTuningDocument::ReportLoadSaveError(const wxString& fileName,
    off_t offset, const wxString& errorMessage, bool saving)
{
    //------Last Checked------//
    // - Dec 30, 2004
    wxString action = wxT("");
    if (saving)
        action = wxT("saving");
    else
        action = wxT("loading");
    wxMessageBox(
        wxString::Format(wxT("An error occurred at offset %lld while %s the file '%s'.\n\n%s"),
        offset, action.c_str(), fileName.c_str(), errorMessage.c_str()),
        wxTheApp->GetAppName().c_str(), wxICON_ERROR);
}

// Overrides
/// Deletes all data in the document
bool PowerTabTuningDocument::DeleteContents()
{
    //------Last Checked------//
    // - Dec 29, 2004
    DeleteTuningArrayContents();
    return (true);
}

// Tuning Functions
/// Removes all tunings from the tuning array
void PowerTabTuningDocument::DeleteTuningArrayContents()
{
    //------Last Checked------//
    // - Dec 29, 2004
	size_t i = 0;
	size_t count = m_tuningArray.GetCount();
	for (; i < count; i++)
        delete m_tuningArray[i];
	m_tuningArray.Clear();
}
