/////////////////////////////////////////////////////////////////////////////
// Name:            FloatingText.cpp
// Purpose:         Stores and renders text annotations
// Author:          Brad Larsen
// Modified by:     
// Created:         Sat Nov 27 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// Licence:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "floatingtext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Default constants
const wxChar*   FloatingText::DEFAULT_TEXT          = wxT("Text");
const wxRect    FloatingText::DEFAULT_RECT          = wxRect(0,0,0,0);
const wxByte    FloatingText::DEFAULT_FLAGS         = DEFAULT_ALIGNMENT;
const wxByte    FloatingText::DEFAULT_ALIGNMENT     = FloatingText::alignLeft;

// Constructor/Destructor
/// Default Constructor
FloatingText::FloatingText() : 
    m_text(DEFAULT_TEXT), m_rect(DEFAULT_RECT), m_flags(DEFAULT_FLAGS)
{
    //------Last Checked------//
    // - Dec 7, 2004
}

/// Primary Constructor
/// @param text Text to set
/// @param rect Bounding rect for the text, in logical co-ordinates
/// @param flags Flags to set (see flags enum)
/// @param fontSetting FontSetting object to set
FloatingText::FloatingText(const wxChar* text, wxRect rect, wxByte flags,
    const FontSetting& fontSetting) : m_text(text), m_rect(rect),
    m_flags(flags), m_fontSetting(fontSetting)
{
    //------Last Checked------//
    // - Dec 7, 2004
    wxASSERT(text != NULL);
}

/// Copy Constructor
FloatingText::FloatingText(const FloatingText& floatingText) :
    m_text(DEFAULT_TEXT), m_rect(DEFAULT_RECT), m_flags(DEFAULT_FLAGS)
{
    //------Last Checked------//
    // - Dec 7, 2004
    *this = floatingText;
}

/// Destructor    
FloatingText::~FloatingText()
{
    //------Last Checked------//
    // - Dec 7, 2004
}

// Operators
/// Assignment Operator
const FloatingText& FloatingText::operator=(const FloatingText& floatingText)
{
    //------Last Checked------//
    // - Dec 7, 2004
    
    // Check for assignment to self
    if (this != &floatingText)
    {
        m_text = floatingText.m_text;
        m_rect = floatingText.m_rect;
        m_flags = floatingText.m_flags;
        m_fontSetting = floatingText.m_fontSetting;
    }
    return (*this);
}

/// Equality Operator
bool FloatingText::operator==(const FloatingText& floatingText) const
{
    //------Last Checked------//
    // - Dec 6, 2004
    return (
        (m_text == floatingText.m_text) &&
        (m_rect == floatingText.m_rect) &&
        (m_flags == floatingText.m_flags) &&
        (m_fontSetting == floatingText.m_fontSetting)
    );
}

/// Inequality Operator
bool FloatingText::operator!=(const FloatingText& floatingText) const
{
    //------Last Checked------//
    // - Dec 6, 2004
    return (!operator==(floatingText));
}

/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool FloatingText::DoSerialize(PowerTabOutputStream & stream)
{
    //------Last Checked------//
    // - Dec 7, 2004
    stream.WriteMFCString(m_text);
    wxCHECK(stream.CheckState(), false);
    
    stream.WriteMFCRect(m_rect);
    wxCHECK(stream.CheckState(), false);
    
    stream << m_flags;
    wxCHECK(stream.CheckState(), false);
    
    m_fontSetting.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    return (stream.CheckState());
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool FloatingText::DoDeserialize(PowerTabInputStream & stream, wxWord version)
{
    //------Last Checked------//
    // - Dec 7, 2004
    stream.ReadMFCString(m_text);
    wxCHECK(stream.CheckState(), false);
    
    stream.ReadMFCRect(m_rect);
    wxCHECK(stream.CheckState(), false);
    
    stream >> m_flags;
    wxCHECK(stream.CheckState(), false);
    
    m_fontSetting.Deserialize(stream, version);
    wxCHECK(stream.CheckState(), false);
    
    return (stream.CheckState());
}

// Flag Functions
/// Sets a flag used by the FloatingText object
/// @param flag The flag to set
void FloatingText::SetFlag(wxByte flag)
{
    //------Last Checked------//
    // - Dec 7, 2004
    
    // Clear old alignment flag if new flag is alignment flag
    if (((flag & alignLeft) == alignLeft) |
        ((flag & alignCenter) == alignCenter) |
        ((flag & alignRight) == alignRight))
    {
        ClearFlag(alignMask);
    }
    m_flags |= flag;
}

/// Gets the rect used to draw the border surrounding the text
/// @return The rect used to draw the border surrounding the text
wxRect FloatingText::GetBorderRect() const
{
    //------Last Checked------//
    // - Dec 7, 2004
    wxRect returnValue;
    returnValue.SetLeft(m_rect.GetLeft() - 2);
    returnValue.SetTop(m_rect.GetTop() - 1);
    returnValue.SetRight(m_rect.GetRight() + 1);
    returnValue.SetBottom(m_rect.GetBottom() + 1);
    return (returnValue);
}
