/////////////////////////////////////////////////////////////////////////////
// Name:            powertabparser.cpp
// Purpose:         Application for parsing Power Tab files
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 29, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "powertabparser.h"

#include "mainframe.h"
#include "powertabdocument.h"
#include "powertabview.h"
#include "powertabtuningdocument.h"
#include "powertabtuningview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Global frame pointer
MainFrame* frame = (MainFrame*)NULL;

IMPLEMENT_APP(PowerTabParser)

// Constructor/Destructor
/// Default Constructor
PowerTabParser::PowerTabParser() : m_docManager((wxDocManager*)NULL)
{
    //------Last Checked------//
    // - Dec 30, 2004
}

// Overrides
bool PowerTabParser::OnInit()
{
    //------Last Checked------//
    // - Dec 30, 2004
    SetAppName(wxT("Power Tab Parser 1.1"));
    
    // Initialize and load the XML resources
    wxXmlResource::Get()->InitAllHandlers();
    if (!LoadXMLResources())
        return (false);        
       
    // Create a document manager
    m_docManager = new wxDocManager;

    // Add all the document templates used by the app
    AddDocumentTemplates();
       
    // Create the main frame window
    frame = new MainFrame((wxDocManager*) m_docManager, (wxFrame*)NULL,
                wxT("PowerTabParser 1.1"), wxPoint(0,0), wxSize(300,300),
                wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE | wxMAXIMIZE);

    // Create the main menu
    
    // File Menu
    wxMenu* file_menu = new wxMenu;
    file_menu->Append(wxID_OPEN, wxT("&Open...\tCtrl+O"));
    file_menu->AppendSeparator();
    file_menu->Append(wxID_EXIT, wxT("E&xit"));
    
    // File History
    m_docManager->FileHistoryUseMenu(file_menu);

    // Tools Menu
    wxMenu* tools_menu = new wxMenu;
    tools_menu->Append(IDM_TOOLS_MERGE_SCORES, wxT("&Merge Scores..."));
   
    // Test Menu
    wxMenu* test_menu = new wxMenu;
    test_menu->Append(IDM_TEST_TESTINGFRAMEWORK, wxT("Testing &Framework..."));
    test_menu->Append(IDM_TEST_BATCHFILESERIALIZATION, wxT("&Batch File Serialization..."));
    test_menu->Append(IDM_TEST_STATISTICALANALYSIS, wxT("&Statistical Analysis..."));
         
    // Help Menu
    wxMenu* help_menu = new wxMenu;
    help_menu->Append(IDM_HELP_ABOUT, wxT("&About\tF1"));
    
    // Main Menu Bar
    wxMenuBar* menu_bar = new wxMenuBar;
    menu_bar->Append(file_menu, wxT("&File"));
    menu_bar->Append(tools_menu, wxT("&Tools"));
    menu_bar->Append(test_menu, wxT("T&est"));
    menu_bar->Append(help_menu, wxT("&Help"));

    // Attach the menu bar to the main frame
    frame->SetMenuBar(menu_bar);
   
    // Display the frame
    frame->Show(true);
    SetTopWindow(frame);
    
    return (true);
}

int PowerTabParser::OnExit()
{
    //------Last Checked------//
    // - Dec 30, 2004
    
    // Clean-up the document manager
    if (m_docManager != NULL)
    {
        delete m_docManager;
        m_docManager = NULL;
    }
    
    return (0);
}

// Operations
/// Adds the templates used for each document type used in the program
void PowerTabParser::AddDocumentTemplates()
{
    //------Last Checked------//
    // - Dec 30, 2004
    
    // .ptb = Power Tab documents
    (void)new wxDocTemplate((wxDocManager*)m_docManager, 
        wxT("Power Tab Document v1.0-1.7"),
        wxT("*.ptb"),
        wxT(""),
        wxT("ptb"),
        wxT("PowerTab Document"),
        wxT("PowerTab View"),
        CLASSINFO(PowerTabDocument),
        CLASSINFO(PowerTabView));
    
    // .dat = Power Tab Tuning Database
    (void)new wxDocTemplate((wxDocManager*)m_docManager,
        wxT("Power Tab Tuning Database"),
        wxT("*.dat"), 
        wxT(""), 
        wxT("dat"), 
        wxT("Power Tab Tuning Document"), 
        wxT("Power Tab Tuning Document View"),
        CLASSINFO(PowerTabTuningDocument), 
        CLASSINFO(PowerTabTuningView));
}

/// Loads the XML resources used by the program
/// @return True if all of the XML resources were loaded, false if not
bool PowerTabParser::LoadXMLResources()
{
    //------Last Checked------//
    // - Dec 30, 2004
    
    // Note: #ifdef is a temporary fudge because I haven't figured out
    // how to update the include paths in KDevelop
    const wxUint32 resourceFileCount = 1;
    const wxChar* resourceFiles[resourceFileCount] = 
    {
    #ifdef __WXMSW__
        wxT("rc/resource.xrc")
    #else
        wxT("../../src/rc/resource.xrc")
    #endif
    };
    
    wxUint32 i = 0;
    for (; i < resourceFileCount; i++)
    {
        // Make sure the XML file exists
        if (!wxFileName::FileExists(resourceFiles[i]))
        {
            wxMessageBox(wxString::Format(wxT("Could not find the XML resource file '%s'."), resourceFiles[i]), GetAppName(), wxICON_ERROR);
            return (false);
        }

        if (!wxXmlResource::Get()->Load(resourceFiles[i]))
        {
            wxMessageBox(wxString::Format(wxT("Could not load the XML resource file '%s'."), resourceFiles[i]), GetAppName(), wxICON_ERROR);
            return (false);
        }
    }
    
    return (true);
}

/// Gets a pointer to the main frame in the program
/// @return A pointer to the main frame in the program
MainFrame* GetMainFrame()
{
    //------Last Checked------//
    // - Dec 30, 2004
    return (frame);
}
