/////////////////////////////////////////////////////////////////////////////
// Name:            powertabviewcanvas.cpp
// Purpose:         Canvas used by the PowerTabView class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 29, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "powertabviewcanvas.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(PowerTabViewCanvas, wxScrolledWindow)
END_EVENT_TABLE()

// Constructor/Destructor
/// Primary Constructor
PowerTabViewCanvas::PowerTabViewCanvas(wxView *view, wxMDIChildFrame *frame,
    const wxPoint& pos, const wxSize& size, long style):
    wxScrolledWindow(frame, -1, pos, size, style)
{
    //------Last Checked------//
    // - Jan 27, 2005
    wxASSERT(m_view != NULL);
    
    m_view = view;
    SetBackgroundColour(*wxWHITE);
}

// Overrides
void PowerTabViewCanvas::OnDraw(wxDC& dc)
{
    //------Last Checked------//
    // - Jan 27, 2005
    
    // If view member is valid, call its draw handler
    if (m_view)
        m_view->OnDraw(& dc);
}
