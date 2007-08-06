/////////////////////////////////////////////////////////////////////////////
// Name:            fontsetting.h
// Purpose:         Stores information about a font format (facename, point size, weight, style, etc.)
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 5, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "fontsetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Default constants
const wxChar*   FontSetting::DEFAULT_FACENAME           = wxT("Times New Roman");
const wxInt32   FontSetting::DEFAULT_POINTSIZE          = 8;
const wxInt32   FontSetting::DEFAULT_WEIGHT             = FontSetting::weightNormal;
const bool      FontSetting::DEFAULT_ITALIC             = false;
const bool      FontSetting::DEFAULT_UNDERLINE          = false;
const bool      FontSetting::DEFAULT_STRIKEOUT          = false;
const wxColor   FontSetting::DEFAULT_COLOR              = wxColor(0,0,0);

// Point Size constants
const wxInt32   FontSetting::MIN_POINTSIZE              = 1;
const wxInt32   FontSetting::MAX_POINTSIZE              = 72;
    
/// Default Constructor
FontSetting::FontSetting() : m_faceName(DEFAULT_FACENAME),
    m_pointSize(DEFAULT_POINTSIZE), m_weight(DEFAULT_WEIGHT),
    m_italic(DEFAULT_ITALIC), m_underline(DEFAULT_UNDERLINE),
    m_strikeOut(DEFAULT_STRIKEOUT), m_color(DEFAULT_COLOR)
{
    //------Last Checked------//
    // - Dec 6, 2004
}

/// Primary Constructor
/// @param faceName Face name of the font
/// @param pointSize Height of the font, in points
/// @param weight Weight of the font (see .h for values)
/// @param italic Make the font italic style
/// @param underline Make the font underline style
/// @param strikeOut Make the font strikeout style
/// @param color Color to draw the font with
FontSetting::FontSetting(const wxChar* faceName, wxInt32 pointSize,
    wxInt32 weight, bool italic, bool underline, bool strikeOut, wxColor color) :
    m_faceName(faceName), m_pointSize(pointSize), m_weight(weight),
    m_italic(italic), m_underline(underline), m_strikeOut(strikeOut),
    m_color(color)
{
    //------Last Checked------//
    // - Dec 6, 2004
    wxASSERT(faceName != NULL);
    wxASSERT(IsValidPointSize(pointSize));
    wxASSERT(IsValidWeight(weight));
}

/// Copy Constructor
FontSetting::FontSetting(const FontSetting& fontSetting) :
    m_faceName(DEFAULT_FACENAME), m_pointSize(DEFAULT_POINTSIZE),
    m_weight(DEFAULT_WEIGHT), m_italic(DEFAULT_ITALIC),
    m_underline(DEFAULT_UNDERLINE), m_strikeOut(DEFAULT_STRIKEOUT),
    m_color(DEFAULT_COLOR)
{
    //------Last Checked------//
    // - Dec 6, 2004
    *this = fontSetting;
}

/// Destructor
FontSetting::~FontSetting()
{
    //------Last Checked------//
    // - Dec 6, 2004
}

/// Assignment operator
const FontSetting& FontSetting::operator=(const FontSetting& fontSetting)
{
    //------Last Checked------//
    // - Dec 6, 2004

    // Check for assignment to self
    if (this != &fontSetting)
    {
        m_faceName = fontSetting.m_faceName;
        m_pointSize = fontSetting.m_pointSize;
        m_weight = fontSetting.m_weight;
        m_italic = fontSetting.m_italic;
        m_underline = fontSetting.m_underline;
        m_strikeOut = fontSetting.m_strikeOut;
        m_color = fontSetting.m_color;
    }
    return (*this);
}

/// Equality Operator
bool FontSetting::operator==(const FontSetting& fontSetting) const
{
    //------Last Checked------//
    // - Dec 6, 2004
    return (
        (m_faceName == fontSetting.m_faceName) &&
        (m_pointSize == fontSetting.m_pointSize) &&
        (m_weight == fontSetting.m_weight) &&
        (m_italic == fontSetting.m_italic) &&
        (m_underline == fontSetting.m_underline) &&
        (m_strikeOut == fontSetting.m_strikeOut) &&
        (m_color == fontSetting.m_color)
    );
}

/// Inequality Operator
bool FontSetting::operator!=(const FontSetting& fontSetting) const
{
    //------Last Checked------//
    // - Dec 6, 2004
    return (!operator==(fontSetting));
}

/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool FontSetting::DoSerialize(PowerTabOutputStream& stream)
{
    //------Last Checked------//
    // - Dec 5, 2004
    stream.WriteMFCString(m_faceName);
    wxCHECK(stream.CheckState(), false);
    
    stream << m_pointSize << m_weight << m_italic << m_underline << m_strikeOut;
    wxCHECK(stream.CheckState(), false);
    
    stream.WriteWin32ColorRef(m_color);
    wxCHECK(stream.CheckState(), false);
    
    return (stream.CheckState());
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool FontSetting::DoDeserialize(PowerTabInputStream& stream,
    wxWord WXUNUSED(version))
{
    //------Last Checked------//
    // - Dec 5, 2004
    stream.ReadMFCString(m_faceName);
    wxCHECK(stream.CheckState(), false);
    
    stream >> m_pointSize >> m_weight >> m_italic >> m_underline >> m_strikeOut;
    wxCHECK(stream.CheckState(), false);
    
    stream.ReadWin32ColorRef(m_color);
    wxCHECK(stream.CheckState(), false);
    
    return (stream.CheckState());
}

/// Updates the contents of the FontSetting object
/// @param faceName Face name of the font
/// @param pointSize Height of the font, in points
/// @param weight Weight of the font (see .h for values)
/// @param italic Make the font italic style
/// @param underline Make the font underline style
/// @param strikeOut Make the font strikeout style
/// @param color Color to draw the font with
/// @return success or failure
bool FontSetting::SetFontSetting(const wxChar* faceName, wxInt32 pointSize,
    wxInt32 weight, bool italic, bool underline, bool strikeOut, wxColor color)
{
    //------Last Checked------//
    // - Dec 6, 2004
    if (!SetFaceName(faceName))
        return (false);
    if (!SetPointSize(pointSize))
        return (false);
    if (!SetWeight(weight))
        return (false);
    SetItalic(italic);
    SetUnderline(underline);
    SetStrikeOut(strikeOut);
    SetColor(color);
    
    return (true);
}

/// Updates the contents of the FontSetting object using a delimited string
/// containing the font settings
/// @param string Comma delimited string containing the font settings
/// (FaceName,PointSize,Weight,Italic(T/F),Underline(T/F),StrikeOut(T/F),Color)
/// @return success or failure
bool FontSetting::SetFontSettingFromString(const wxChar* string)
{
    //------Last Checked------//
    // - Dec 6, 2004
    wxCHECK(string != NULL, false);
    
    wxString temp;

    // Extract the face name
    wxExtractSubString(temp, string, 0, wxT(','));
    temp.Trim(false);
    temp.Trim();
    m_faceName = temp;
    if (m_faceName.IsEmpty())
        m_faceName = DEFAULT_FACENAME;

    // Extract the point size
    wxExtractSubString(temp, string, 1, wxT(','));
    temp.Trim(false);
    temp.Trim();
    m_pointSize = wxAtoi(temp);
    if (m_pointSize == 0)
        m_pointSize = DEFAULT_POINTSIZE;

    // Extract the weight
    wxExtractSubString(temp, string, 2, wxT(','));
    temp.Trim(false);
    temp.Trim();
    m_weight = wxAtoi(temp);
    if ((m_weight % 100) != 0)
        m_weight = DEFAULT_WEIGHT;
    
    // Extract the italic setting
    wxExtractSubString(temp, string, 3, wxT(','));
    temp.Trim(false);
    temp.Trim();
    m_italic = (wxByte)((::wxStricmp(temp, wxT("T")) == 0) ? true : false);
    
    // Extract the underline setting
    wxExtractSubString(temp, string, 4, wxT(','));
    temp.Trim(false);
    temp.Trim();
    m_underline = (wxByte)((::wxStricmp(temp, wxT("T")) == 0) ? true : false);

    // Extract the strikeout setting
    wxExtractSubString(temp, string, 5, wxT(','));
    temp.Trim(false);
    temp.Trim();
    m_strikeOut = (wxByte)((::wxStricmp(temp, wxT("T")) == 0) ? true : false);

    // Extract the color
    wxExtractSubString(temp, string, 6, wxT(','));
    temp.Trim(false);
    temp.Trim();
    wxUint32 color = wxAtoi(temp);
    m_color = wxColor(LOBYTE(LOWORD(color)), HIBYTE(LOWORD(color)),
        LOBYTE(HIWORD(color)));
    
    return (true);
}

/// Initializes a wxFont object using the FontSetting data
/// @param font wxFont object to initialize
void FontSetting::GetFont(wxFont& font) const
{
    //------Last Checked------//
    // - Dec 6, 2004
    font.SetPointSize(GetPointSize());
    font.SetFamily(wxDEFAULT);
    font.SetStyle(((IsItalic()) ? wxITALIC : wxNORMAL));
    
    if (m_weight <= weightLight)
        font.SetWeight(wxLIGHT);
    else if (m_weight < weightBold)
        font.SetWeight(wxNORMAL);
    else
        font.SetWeight(wxBOLD);
    font.SetUnderlined(IsUnderline());
    font.SetFaceName(GetFaceName());
}
