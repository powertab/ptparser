/////////////////////////////////////////////////////////////////////////////
// Name:            powertabtuningview.cpp
// Purpose:         Displays the PowerTabTuningDocument-based data
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 29, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "powertabtuningview.h"

#include "powertabparser.h"                     // Needed for GetMainFrame
#include "mainframe.h"
#include "powertabtuningdocument.h"
#include "powertabtuningviewwindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(PowerTabTuningView, wxView)

BEGIN_EVENT_TABLE(PowerTabTuningView, wxView)
END_EVENT_TABLE()

// Constructor/Destructor
/// Default Constructor
PowerTabTuningView::PowerTabTuningView() : m_frame((wxMDIChildFrame*)NULL),
    m_window((PowerTabTuningViewWindow*)NULL)
{
    //------Last Checked------//
    // - Dec 30, 2004
}

/// Destructor
PowerTabTuningView::~PowerTabTuningView() 
{
    //------Last Checked------//
    // - Dec 30, 2004
}

// Overrides
bool PowerTabTuningView::OnCreate(wxDocument* doc, long WXUNUSED(flags))
{
    //------Last Checked------//
    // - Apr 22, 2007
    MainFrame* mainFrame = GetMainFrame();
    wxCHECK(mainFrame != NULL, false);
    
    m_frame = mainFrame->CreateChildFrame(doc, this);
    wxCHECK(m_frame != NULL, false);
    
    m_window = CreateViewWindow();
    wxCHECK(m_window != NULL, false);
    
#ifdef __X__
    // X seems to require a forced resize
    int x, y;
    m_frame->GetSize(&x, &y);
    m_frame->SetSize(-1, -1, x, y);
#endif
    
    m_frame->Show(true);
    Activate(true);
    
    return (true);
}

void PowerTabTuningView::OnDraw(wxDC* WXUNUSED(dc))
{
    // Note: Drawing is handled by the window class
    //------Last Checked------//
    // - Apr 22, 2007
}

void PowerTabTuningView::OnUpdate(wxView* sender, wxObject* WXUNUSED(hint))
{
    //------Last Checked------//
    // - Apr 22, 2007
    wxCHECK2(m_window != NULL, return);

    if ((sender != this) && (sender != NULL))
        return;
            
    wxBusyCursor wait;
    
    // Add all the tunings from the document to the list control
    PowerTabTuningDocument* document = (PowerTabTuningDocument*)GetDocument();
    wxCHECK2(document != NULL, return);
    
    m_window->DeleteAllItems();
        
    size_t i = 0;
    size_t count = document->GetTuningCount();
    for (; i < count; i++)
    {
        Tuning* tuning = document->GetTuning(i);
        wxCHECK2(tuning != NULL, continue);
        
        long index = m_window->InsertItem(m_window->GetItemCount(),
            tuning->GetName());
        wxCHECK2(index != -1, continue);
        
        m_window->SetItem(index, PowerTabTuningViewWindow::COLUMN_STRINGS,
            wxString::Format(wxT("%d"), tuning->GetStringCount()));
        m_window->SetItem(index, PowerTabTuningViewWindow::COLUMN_SPELLING,
            tuning->GetSpelling()); 
    }
    
    // Adjust the column widths
    int column = 0;
    for (; column < PowerTabTuningViewWindow::NUM_COLUMNS; column++)
        m_window->SetColumnWidth(column, wxLIST_AUTOSIZE_USEHEADER);
}

bool PowerTabTuningView::OnClose(bool deleteWindow)
{
    //------Last Checked------//
    // - Dec 30, 2004
    
    // Close the document
    wxDocument* document = GetDocument();
    wxCHECK(document != NULL, false);  
    if (!document->Close())
        return (false);
    
    Activate(false);
    
    // Delete the frame
    if (deleteWindow && (m_frame != NULL))
    {
        delete m_frame;
        m_frame = NULL;
    }
    
    return (true);
}

// Operations
/// Creates the window used by the view
/// @return A pointer to the newly created window, or NULL if the window could
/// not be created
PowerTabTuningViewWindow* PowerTabTuningView::CreateViewWindow()
{
    //------Last Checked------//
    // - Dec 30, 2004
    wxCHECK(m_frame != NULL, false);
    
    // Get the dimensions of the frame and use them to size the window
    int width = 0;
    int height = 0;
    m_frame->GetClientSize(&width, &height);

    // Create the view window
    PowerTabTuningViewWindow* window = new PowerTabTuningViewWindow(this,
        m_frame, wxPoint(0,0), wxSize(width, height));

    return (window);
}
