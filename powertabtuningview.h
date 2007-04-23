/////////////////////////////////////////////////////////////////////////////
// Name:            powertabtuningview.h
// Purpose:         Displays the PowerTabTuningDocument-based data
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 29, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __POWERTABTUNINGVIEW_H__
#define __POWERTABTUNINGVIEW_H__

class PowerTabTuningViewWindow;

/// Displays the PowerTabTuningDocument-based data
class PowerTabTuningView : public wxView
{
protected:
    wxMDIChildFrame*                m_frame;        ///< Frame that holds the view
    PowerTabTuningViewWindow*       m_window;       ///< Window associated with the view

public:
    // Constructor/Destructor
    PowerTabTuningView();
    ~PowerTabTuningView();

    // Overrides
    bool OnCreate(wxDocument* doc, long flags);
    void OnDraw(wxDC* dc);
    void OnUpdate(wxView* sender, wxObject* hint = (wxObject*)NULL);
    bool OnClose(bool deleteWindow = true);
    
    // Operations
protected:
    PowerTabTuningViewWindow* CreateViewWindow();

private:
    DECLARE_DYNAMIC_CLASS(PowerTabTuningView)
    DECLARE_EVENT_TABLE()
};

#endif
