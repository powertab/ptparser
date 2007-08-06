/////////////////////////////////////////////////////////////////////////////
// Name:            stdwx.h
// Purpose:         Includes files that are frequently used, but rarely changed
// Author:          Brad Larsen
// Modified by:     
// Created:         Nov 26, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __STDWX_H__
#define __STDWX_H__

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

// Debug helpers
#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK ,__FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif 

// wxWidgets
#include <wx/datetime.h>            // wxDateTime support
#include <wx/dynarray.h>            // wxArray support
#include <wx/listimpl.cpp>          // wxList support
#include <wx/hashmap.h>             // wxHashMap support
#include <wx/wfstream.h>            // wxFileStream support
#include <wx/datstrm.h>             // wxDataStream support
#include <wx/mstream.h>             // wxMemoryStream support
#include <wx/mdi.h>
#include <wx/docview.h>
#include <wx/docmdi.h>
#include <wx/imaglist.h>            // wxImageList control support
#include <wx/listctrl.h>            // wxListCtrl control support
#include <wx/treectrl.h>            // wxTreeCtrl control support
#include <wx/checklst.h>            // wxCheckListBox control support
#include <wx/gauge.h>               // wxGauge control support
#include <wx/xrc/xmlres.h>          // XML resource support

#include "macros.h"                 // Contains macros such as LOBYTE

// Testing
#include "testingframework.h"
#include "testingframeworkdialog.h"

// MIDI
#include "generalmidi.h"

// Power Tab related
#include "powertabobject.h"
#include "powertabstream.h"
#include "powertabinputstream.h"
#include "powertaboutputstream.h"

// Global Functions
extern bool wxExtractSubString(wxString& string, const wxChar* fullString,
    wxUint32 subString, wxChar separator);
extern int wxCompareIntegers(int* n1, int* n2);

// Date/Time
extern wxString wxGetLocaleDateTime(const wxDateTime& dateTime);
extern wxString wxGetLocaleShortDateTime(const wxDateTime& dateTime);
extern wxString wxGetLocaleLongDateTime(const wxDateTime& dateTime);

// Number
extern wxString wxArabicToRoman(wxInt32 number, bool uppercase = true);

#endif
