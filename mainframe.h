/////////////////////////////////////////////////////////////////////////////
// Name:            mainframe.h
// Purpose:         Main frame for the application
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 3, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

// Menu Command Ids
enum mainFrameMenuCommandIds
{
    IDM_HELP_ABOUT                       = 100,
    
    IDM_TOOLS_MERGE_SCORES,
    
    IDM_TEST_TESTINGFRAMEWORK,
    IDM_TEST_BATCHFILESERIALIZATION,
    IDM_TEST_STATISTICALANALYSIS
};

// Menu Command Ids
enum powerTabViewMenuCommandIds
{
    IDM_TEST_PARSE_FILE = 500
};

/// Main frame for the application
class MainFrame: public wxDocMDIParentFrame
{
    DECLARE_CLASS(MainFrame)
    
public:
    // Constructor/Destructor
    MainFrame(wxDocManager* manager, wxFrame* frame, const wxString& title,
        const wxPoint& pos, const wxSize& size, long type);

    // Command Events
    void OnHelpAbout(wxCommandEvent& event);
    void OnToolsMergeScores(wxCommandEvent& event);
    void OnTestTestingFramework(wxCommandEvent& event);
    void OnTestBatchFileSerialization(wxCommandEvent& event);
    void OnTestStatisticalAnalysis(wxCommandEvent& event);
    
    // Operations
    wxMDIChildFrame* CreateChildFrame(wxDocument* document, wxView* view);

    DECLARE_EVENT_TABLE()
};

#endif
