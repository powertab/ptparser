/////////////////////////////////////////////////////////////////////////////
// Name:            powertabview.h
// Purpose:         Displays the PowerTabDocument-based data
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 29, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __POWERTABVIEW_H__
#define __POWERTABVIEW_H__

class PowerTabViewCanvas;

/// Displays the PowerTabDocument-based data
class PowerTabView: public wxView
{
// Member Variables
public:
    wxMDIChildFrame*        m_frame;            ///< Frame that holds the view
    PowerTabViewCanvas*     m_canvas;           ///< Canvas associated with the view
  
// Constructor/Destructor
    PowerTabView();
    ~PowerTabView();

// Overrides
    bool OnCreate(wxDocument* doc, long flags);
    void OnDraw(wxDC* dc);
    void OnUpdate(wxView* sender, wxObject* hint = (wxObject*) NULL);
    bool OnClose(bool deleteWindow = TRUE);
    
// Command Events
    void OnTestParseFile(wxCommandEvent& event);
    
// Operations
    PowerTabViewCanvas* CreateCanvas(wxView* view, wxMDIChildFrame* parent);

private:
    DECLARE_DYNAMIC_CLASS(PowerTabView)
    DECLARE_EVENT_TABLE()
};

#endif
