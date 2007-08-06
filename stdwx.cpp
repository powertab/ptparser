/////////////////////////////////////////////////////////////////////////////
// Name:            stdwx.cpp
// Purpose:         Includes files that are frequently used, but rarely changed
// Author:          Brad Larsen
// Modified by:     
// Created:         Nov 26, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/// Extracts the nth substring from a delimited string
/// This is a wxWidgets port of MFC's AfxExtractSubString
/// @param string Holds the returned substring
/// @param fullString String to extract the substring from
/// @param subString Zero-based index of the substring to extract
/// @param separator Character used to separator the substrings
/// @return True if the substring was extracted, false if not
bool wxExtractSubString(wxString& string, const wxChar* fullString,
    wxUint32 subString, wxChar separator)
{
    //------Last Verified------//
    // - Nov 27, 2004
    wxCHECK(fullString != (wxChar*)NULL, false);
    
    string.Clear();

    while (subString--)
    {
        fullString = wxStrchr(fullString, separator);
        if (fullString == NULL)
        {
            string.Clear();        // return empty string as well
            return (false);
        }
        fullString++;       // point past the separator
    }
    const wxChar* end = wxStrchr(fullString, separator);
    wxInt32 length = (end == NULL) ? wxStrlen_(fullString) :
        (wxInt32)(end - fullString);
    wxASSERT(length >= 0);
    memcpy(string.GetWriteBuf(length), fullString, length * sizeof(wxChar));
    string.UngetWriteBuf();     // Need to call ReleaseBuffer 
                                // after calling GetBufferSetLength
    return (true);
}

/// Compares two integers (used for sorting arrays)
/// @param n1 First integer
/// @param n2 Second integer
/// @return Negative if n1 < n2, positive is n1 > n2, zero if n1 == n2
int wxCompareIntegers(int* n1, int* n2)
{
    //------Last Checked------//
    // - Jan 24, 2005
    return (*n1 - *n2);
}

// Date/Time Functions
/// Formats a wxDateTime value using the format representation of the user's
/// locale
/// @param dateTime wxDateTime value to format
/// @return Formatted string
wxString wxGetLocaleDateTime(const wxDateTime& dateTime)
{
    //------Last Verified------//
    // - Nov 29, 2004
    return (dateTime.Format());
}

/// Formats a wxDateTime value using the short format representation of the
/// user's locale
/// @param dateTime wxDateTime value to format
/// @return Formatted string
wxString wxGetLocaleShortDateTime(const wxDateTime& dateTime)
{
    //------Last Verified------//
    // - Nov 29, 2004
    return (dateTime.Format());
}

/// Formats a wxDateTime value using the long format representation of the
/// user's locale
/// @param dateTime wxDateTime value to format
/// @return Formatted string
wxString wxGetLocaleLongDateTime(const wxDateTime& dateTime)
{
    //------Last Verified------//
    // - Nov 29, 2004
    return (dateTime.Format(wxT("%#c")));
}

// Number Functions
/// Converts an arabic number to it's roman numeral equivalent
/// @param number Number to convert
/// @param upperCase If true, forces the roman numeral to upper case
/// @return Roman numeral
wxString wxArabicToRoman(wxInt32 number, bool upperCase)
{
    //------Last Checked------//
    // - Dec 7, 2004
    
	// Can only convert 1 to 5999
	wxCHECK(((number > 0) && (number < 6000)), wxT(""));

	wxString returnValue;
	while (number >= 1000)	{number -= 1000; returnValue += wxT("m");}
    while (number >= 900)	{number -= 900; returnValue += wxT("cm");}
    while (number >= 500)	{number -= 500; returnValue += wxT("d");}
    while (number >= 400)	{number -= 400; returnValue += wxT("cd");}
    while (number >= 100)	{number -= 100; returnValue += wxT("c");}
    while (number >= 90)	{number -= 90; returnValue += wxT("xc");}
    while (number >= 50)	{number -= 50; returnValue += wxT("l");}
    while (number >= 40)	{number -= 40; returnValue += wxT("xl");}
    while (number >= 10)	{number -= 10; returnValue += wxT("x");}
    while (number >= 9)	    {number -= 9; returnValue += wxT("ix");}
    while (number >= 5)	    {number -= 5; returnValue += wxT("v");}
    while (number >= 4)	    {number -= 4; returnValue += wxT("iv");}
    while (number >= 1)	    {number -= 1; returnValue += wxT("i");}

	// Force the text to upper case
	if (upperCase)
	    returnValue.MakeUpper();

    return (returnValue);
}
