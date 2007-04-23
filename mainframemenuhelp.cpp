/////////////////////////////////////////////////////////////////////////////
// Name:            mainframemenuhelp.cpp
// Purpose:         Event handlers for the Help menu
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 31, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "mainframe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void MainFrame::OnHelpAbout(wxCommandEvent& WXUNUSED(event))
{
    // Menu Help -> About
    //------Last Checked------//
    // - Apr 22, 2007
    wxString aboutCaption = wxString::Format(wxT("About %s"),
        wxTheApp->GetAppName().c_str());
    wxMessageBox(wxT("Power Tab Parser 1.1.0.0\nA wxWidgets application that ") \
        wxT("can load and save Power Tab (.ptb) files.\n\nWritten by Brad Larsen") \
        wxT("\nCopyright (c) 2005-2007 by Brad Larsen. All rights reserved."),
        aboutCaption, wxICON_INFORMATION);
}
