/////////////////////////////////////////////////////////////////////////////
// Name:            powertabtuningdocument.h
// Purpose:         Loads and saves Power Tab tuning files
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 30, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __POWERTABTUNINGDOCUMENT_H__
#define __POWERTABTUNINGDOCUMENT_H__

#include "tuning.h"

/// Loads and saves Power Tab tuning files
class PowerTabTuningDocument : public wxDocument
{
    DECLARE_DYNAMIC_CLASS(PowerTabTuningDocument)

// Member Variables
protected:
    TuningArray     m_tuningArray;              ///< List of tunings
    
    bool            m_displayErrors;            ///< Determines whether error messages are displayed via message boxes during load/save

// Constructor/Destructor
public:
    PowerTabTuningDocument();
    ~PowerTabTuningDocument();
       
// Load/Save
#if wxUSE_STD_IOSTREAM
    wxSTD istream& LoadObject(wxSTD istream& text_stream);
    wxSTD ostream& SaveObject(wxSTD ostream& text_stream);
#else
    wxInputStream& LoadObject(wxInputStream& stream);
    wxOutputStream& SaveObject(wxOutputStream& stream);
#endif

// Overrides
    virtual bool DeleteContents();
    
// Error Functions
    void SetDisplayErrors(bool set = true)                  
        {m_displayErrors = set;}
    bool AreErrorsDisplayed() const                         
        {return (m_displayErrors);}
    void ReportLoadSaveError(const wxString& fileName, off_t offset,
        const wxString& errorMessage, bool saving);
    
// Tuning Functions
    /// Determines if a tuning index is valid
    /// @param index Tuning index to validate
    /// @return True if the tuning index is valid, false if not
    bool IsValidTuningIndex(wxUint32 index) const           
        {return (index < GetTuningCount());}
    /// Gets the number of tunings in the document
    /// @return The number of tunings in the document
    size_t GetTuningCount() const                           
        {return (m_tuningArray.GetCount());}
    /// Gets a pointer to the nth tuning in the document
    /// @param index Index of the tuning to retrieve
    /// @return A pointer to the nth tuning, or NULL if the index is invalid
    Tuning* GetTuning(wxUint32 index) const                 
    {
        wxCHECK(IsValidTuningIndex(index), NULL);
        return (m_tuningArray[index]);
    }
    void DeleteTuningArrayContents();        
};

#endif
