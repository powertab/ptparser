/////////////////////////////////////////////////////////////////////////////
// Name:            floatingtext.h
// Purpose:         Stores and renders text annotations
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 6, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __FLOATINGTEXT_H__
#define __FLOATINGTEXT_H__

#include "fontsetting.h"

/// Stores and renders text annotations
class FloatingText : public PowerTabObject
{
friend class FloatingTextTestSuite;

// Constants
public:
    // Default constants
    static const wxChar*        DEFAULT_TEXT;               ///< Default value for the text member variable
    static const wxRect         DEFAULT_RECT;               ///< Default value for the rect member variable
    static const wxByte         DEFAULT_FLAGS;              ///< Default value for the flags member variable
    static const wxByte         DEFAULT_ALIGNMENT;          ///< Default alignment value

    enum flags
    {
        alignLeft   = (wxByte)0x01,             ///< Text aligned left
        alignCenter = (wxByte)0x02,             ///< Text aligned center
        alignRight  = (wxByte)0x04,             ///< Text aligned right
        alignMask   = (wxByte)0x07,             ///< Mask used to extract alignment value
        border      = (wxByte)0x08              ///< Text surrounded by border
    };
    
protected:
    wxString        m_text;                     ///< Text to be output
    wxRect          m_rect;                     ///< Bounding rectangle for the text
    wxByte          m_flags;                    ///< Flags representing alignment and borders (see flags below)
    FontSetting     m_fontSetting;              ///< Font setting (format) to use when drawing the text

public:
    // Constructor/Destructor
    FloatingText();
    FloatingText(const wxChar* text, wxRect rect, wxByte flags, const FontSetting& fontSetting);
    FloatingText(const FloatingText& floatingText);
    ~FloatingText();

    // Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                         
        {return (new FloatingText(*this));}
    
    // Operators
    const FloatingText& operator=(const FloatingText& floatingText);
    bool operator==(const FloatingText& floatingText) const;
    bool operator!=(const FloatingText& floatingText) const;

    // Serialize Functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

public:
    // MFC Class Functions
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const                            
        {return (wxT("CFloatingText"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const                            
        {return ((wxWord)1);}
    
    // Text Functions
    /// Sets the text used by the FloatingText object
    /// @param text Text to set
    /// @return True if the text was set, false if not
    bool SetText(const wxChar* text)                                
        {wxCHECK(text != NULL, false); m_text = text; return (true);}
    /// Gets the text used by the FloatingText object
    /// @return The text used by the FloatingText object
    wxString GetText() const                                        
        {return (m_text);}

    // Rect Functions
    /// Sets the bounding rect for the text in the FloatingText object
    /// @param rect Rect to set
    void SetRect(wxRect rect)                                       
        {m_rect = rect;}
    /// Gets the bounding rect for the text in the FloatingText object
    /// @return The rect that bounds the text in the FloatingText object
    wxRect GetRect() const                                          
        {return (m_rect);}
    /// Determines if the bounding rect is empty
    bool IsEmpty() const                                            
        {return ((m_rect.width == 0) && (m_rect.height == 0));}

    // Flag Functions
protected:
    void SetFlag(wxByte flag);
    /// Clears a flag used by the FloatingText object
    /// @param flag The flag to clear
    void ClearFlag(wxByte flag)                                     
        {m_flags &= ~flag;}
    /// Determines if a flag is set in the FloatingText object
    /// @param flag The flag to test
    /// @return True if the flag is set, false if not
    bool IsFlagSet(wxByte flag) const                               
        {return ((m_flags & flag) == flag);}
    
public:
    // Alignment Functions
    /// Determines if a alignment value is valid
    /// @param alignment Text alignment to validate
    static bool IsValidAlignment(wxByte alignment)                  
        {return ((alignment == alignLeft) || (alignment == alignCenter) || (alignment == alignRight));}
    /// Sets the alignment used by the FloatingText object
    /// @param alignment Text alignment to set
    /// @return True if the alignment was successfully set, false if not
    bool SetAlignment(wxByte alignment)                             
        {wxCHECK(IsValidAlignment(alignment), false); ClearFlag(alignMask); SetFlag(alignment); return (true);}
    /// Gets the alignment used by the FloatingText object
    /// @return The alignment used by the FloatingText object
    wxByte GetAlignment() const                                     
        {return (wxByte)(m_flags & FloatingText::alignMask);}
    /// Determines if the alignment used by the FloatingText object is in a particular alignment
    /// @param alignment Alignment to test
    /// @return True if the alignment used by the FloatingText object matches the one given by alignment, false if not
    bool IsAligned(wxByte alignment) const                          
        {wxCHECK(IsValidAlignment(alignment), false); return (IsFlagSet(alignment));}
    /// Determines if the alignment used by the FloatingText object is left aligned
    /// @return True if the alignment used by the FloatingText object is left aligned, false if not
    bool IsAlignedLeft() const                                      
        {return (IsAligned(FloatingText::alignLeft));}
    /// Determines if the alignment used by the FloatingText object is centered
    /// @return True if the alignment used by the FloatingText object is centered, false if not
    bool IsAlignedCenter() const                                    
        {return (IsAligned(FloatingText::alignCenter));}
    /// Determines if the alignment used by the FloatingText object is right aligned
    /// @return True if the alignment used by the FloatingText object is right aligned, false if not
    bool IsAlignedRight() const                                     
        {return (IsAligned(FloatingText::alignRight));}

    /// Sets the border
    /// @param set True sets the border, false clears it
    void SetBorder(bool set = true)                                 
        {if (set) SetFlag(border); else ClearFlag(border);}
    /// Determines if a border is drawn around the text
    /// @return True if a border is drawn around the text, false if not
    bool HasBorder() const                                          
        {return (IsFlagSet(FloatingText::border));}
    wxRect GetBorderRect() const;
        
    // Font Setting Functions
    /// Sets the font setting used by the FloatingText object
    /// @param fontSetting FontSetting object to set
    void SetFontSetting(const FontSetting& fontSetting)             
        {m_fontSetting = fontSetting;}
    /// Gets the font setting used by the FloatingText object
    /// @return The font setting used by the FloatingText object
    FontSetting GetFontSetting() const                              
        {return (m_fontSetting);}
    /// Gets a reference to the FontSetting object used by the FloatingText object
    /// @return Reference to the FontSetting object used by the FloatingText object
    FontSetting& GetFontSettingRef()                                
        {return (m_fontSetting);}
    /// Gets a constant reference to the FontSetting object used by the FloatingText object
    /// @return Constant reference to the FontSetting object used by the FloatingText object
    const FontSetting& GetFontSettingConstRef() const               
        {return (m_fontSetting);}
};

// Array declarations
WX_DEFINE_POWERTABARRAY(FloatingText*, FloatingTextArray);

#endif
