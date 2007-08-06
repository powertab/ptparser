/////////////////////////////////////////////////////////////////////////////
// Name:            powertabtuningviewwindow.h
// Purpose:         Window used by the PowerTabTuningView class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 30, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __POWERTABTUNINGVIEWWINDOW_H__
#define __POWERTABTUNINGVIEWWINDOW_H__

/// Window used by the PowerTabTuningView class
class PowerTabTuningViewWindow : public wxListCtrl
{
friend class PowerTabTuningView;

// Constants
public:
    // Column Constants
    static const int NUM_COLUMNS;                  ///< Number of columns in the list control
    static const int COLUMN_NAME;                  ///< Index of the Name column
    static const int COLUMN_STRINGS;               ///< Index of the Strings column
    static const int COLUMN_SPELLING;              ///< Index of the Spelling column
    
// Member Variables
protected:
    wxView* m_view;     ///< View associated with the window

// Constructor/Destructor
public:
    PowerTabTuningViewWindow(wxView* view, wxWindow* parent, const wxPoint& pos,
        const wxSize& size, long style = wxLC_REPORT);
    
// Operations
protected:
    bool InsertColumns();
};

#endif
