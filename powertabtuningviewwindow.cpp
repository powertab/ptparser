/////////////////////////////////////////////////////////////////////////////
// Name:            powertabtuningviewwindow.cpp
// Purpose:         Window used by the PowerTabTuningView class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 30, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "powertabtuningviewwindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Constants
// Column Constants
const int PowerTabTuningViewWindow::NUM_COLUMNS            = 3;
const int PowerTabTuningViewWindow::COLUMN_NAME            = 0;
const int PowerTabTuningViewWindow::COLUMN_STRINGS         = 1;
const int PowerTabTuningViewWindow::COLUMN_SPELLING        = 2;

// Constructor/Destructor
/// Primary Constructor
PowerTabTuningViewWindow::PowerTabTuningViewWindow(wxView* view,
    wxWindow* parent, const wxPoint& pos, const wxSize& size, long style) :
    wxListCtrl(parent, -1, pos, size, style), m_view(view)
{
    //------Last Checked------//
    // - Dec 30, 2004
    wxASSERT(m_view != NULL);
  
    // Add the list control columns
    InsertColumns();
}

/// Inserts the columns used by the list control
/// @return True if the columns were inserted, false if not
bool PowerTabTuningViewWindow::InsertColumns()
{
    //------Last Checked------//
    // - Dec 30, 2004
    
    InsertColumn(COLUMN_NAME, wxT("Name"));
    wxCHECK(GetColumnCount() == 1, false);
    
    InsertColumn(COLUMN_STRINGS, wxT("Strings"), wxLIST_FORMAT_CENTER);
    wxCHECK(GetColumnCount() == 2, false);
    
    InsertColumn(COLUMN_SPELLING, wxT("Spelling"));
    wxCHECK(GetColumnCount() == 3, false);
    
    return (true);
}
