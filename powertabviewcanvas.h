/////////////////////////////////////////////////////////////////////////////
// Name:            powertabviewcanvas.h
// Purpose:         Canvas used by the PowerTabView class
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 29, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __POWERTABVIEWCANVAS_H__
#define __POWERTABVIEWCANVAS_H__

class PowerTabViewCanvas: public wxScrolledWindow
{
protected:
    wxView* m_view;         ///< Pointer to the PowerTabView object associated with the canvas
    
public:
    // Constructor
    PowerTabViewCanvas(wxView* view, wxMDIChildFrame* frame, const wxPoint& pos, const wxSize& size, long style);
    
    // Overrides
    void OnDraw(wxDC& dc);

private:
    DECLARE_EVENT_TABLE()
};

#endif
