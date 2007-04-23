/////////////////////////////////////////////////////////////////////////////
// Name:            mainframe.cpp
// Purpose:         Main frame for the application
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 3, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "mainframe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_CLASS(MainFrame, wxDocMDIParentFrame)

BEGIN_EVENT_TABLE(MainFrame, wxDocMDIParentFrame)
    EVT_MENU(IDM_HELP_ABOUT, MainFrame::OnHelpAbout)
    EVT_MENU(IDM_TOOLS_MERGE_SCORES, MainFrame::OnToolsMergeScores)
    EVT_MENU(IDM_TEST_TESTINGFRAMEWORK, MainFrame::OnTestTestingFramework)
    EVT_MENU(IDM_TEST_BATCHFILESERIALIZATION, MainFrame::OnTestBatchFileSerialization)
    EVT_MENU(IDM_TEST_STATISTICALANALYSIS, MainFrame::OnTestStatisticalAnalysis)
END_EVENT_TABLE()

// Constructor/Destructor
MainFrame::MainFrame(wxDocManager* manager, wxFrame* frame, const wxString& title, const wxPoint& pos, const wxSize& size, long type) :
    wxDocMDIParentFrame(manager, frame, -1, title, pos, size, type, wxT("MainFrame"))
{
    //------Last Checked------//
    // - Dec 31, 2004
}

// Operations
/// Creates a child frame for a view
/// @param document Document for the view that the frame is to be created for
/// @param view View that the frame is to be created for
/// @return A pointer to the newly created child frame, or NULL if the child frame could not be created
wxMDIChildFrame* MainFrame::CreateChildFrame(wxDocument* document, wxView* view)
{
    //------Last Checked------//
    // - Dec 31, 2004
    
    // Create the child frame
    wxDocMDIChildFrame* childframe =
        new wxDocMDIChildFrame(document, view, this, -1, wxT("Child Frame"),
            wxPoint(10,10), wxSize(300,300),
            wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE | wxMAXIMIZE);

    // Create the child frame menu
    // TODO: Add any menu items specific to a view here
        
    // File Menu
    wxMenu* file_menu = new wxMenu;
    file_menu->Append(wxID_OPEN, wxT("&Open...\tCtrl+O"));
    file_menu->Append(wxID_CLOSE, wxT("&Close"));
    
    // ** NOTE: Uncomment the following two lines to allow Save functionality **
    // This can be dangerous: i.e. don't overwrite your existing files!
    
    //file_menu->AppendSeparator();
    //file_menu->Append(wxID_SAVEAS, wxT("Save &As..."));
    
    file_menu->AppendSeparator();
    file_menu->Append(wxID_EXIT, wxT("E&xit"));

    // Test Menu
    wxMenu* test_menu = new wxMenu;
    test_menu->Append(IDM_TEST_PARSE_FILE, wxT("&Parse File"));
    
    // Help Menu
    wxMenu* help_menu = new wxMenu;
    help_menu->Append(IDM_HELP_ABOUT, wxT("&About"));

    // Menu Bar
    wxMenuBar* menu_bar = new wxMenuBar;
    menu_bar->Append(file_menu, wxT("&File"));
    menu_bar->Append(test_menu, wxT("&Test"));
    menu_bar->Append(help_menu, wxT("&Help"));

    // Attach the menu bar to the child frame
    childframe->SetMenuBar(menu_bar);

    return (childframe);
}
