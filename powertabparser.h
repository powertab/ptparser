/////////////////////////////////////////////////////////////////////////////
// Name:            powertabparser.h
// Purpose:         Application for parsing Power Tab files
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 29, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __POWERTABPARSER_H__
#define __POWERTABPARSER_H__

class wxDocManager;
class MainFrame;

/// Application for parsing Power Tab files
class PowerTabParser : public wxApp
{
// Member Variables
protected:
    wxDocManager*   m_docManager;                   ///< Document manager

// Constructor/Destructor
public:
    PowerTabParser();
    
// Overrides
    bool OnInit();
    int OnExit();

// Document Manager Functions
    /// Gets a pointer to the document manager
    /// @return A pointer to the document manager
    wxDocManager* GetDocManager() const             
        {return (m_docManager);}
    
// Operations
protected:
    void AddDocumentTemplates();
    bool LoadXMLResources();
};

DECLARE_APP(PowerTabParser)

// Global access to the main frame
extern MainFrame* GetMainFrame();

#endif
