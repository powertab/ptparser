#ifndef __MACROS_H__
#define __MACROS_H__

// Defines a byte array (although it uses 4 bytes per element)
WX_DEFINE_ARRAY_INT(wxByte, wxByteArray);
// Defines a word array (although it uses 4 bytes per element)
WX_DEFINE_ARRAY_INT(wxWord, wxWordArray);
    
// Little-endian based LONG/WORD/BYTE macros
#ifndef MAKEWORD
#define MAKEWORD(a, b)      ((wxWord)(((wxByte)((wxUint32)(a) & 0xff)) | ((wxWord)((wxByte)((wxUint32)(b) & 0xff))) << 8))
#endif

#ifndef MAKELONG
#define MAKELONG(a, b)      ((wxUint32)(((wxWord)((wxUint32)(a) & 0xffff)) | ((wxUint32)((wxWord)((wxUint32)(b) & 0xffff))) << 16))
#endif

#ifndef LOWORD
#define LOWORD(l)           ((wxWord)((wxUint32)(l) & 0xffff))
#endif

#ifndef HIWORD
#define HIWORD(l)           ((wxWord)((wxUint32)(l) >> 16))
#endif

#ifndef LOBYTE
#define LOBYTE(w)           ((wxByte)((wxUint32)(w) & 0xff))
#endif

#ifndef HIBYTE
#define HIBYTE(w)           ((wxByte)((wxUint32)(w) >> 8))
#endif

// min/max macros
#ifndef NOMINMAX
#ifndef max
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif
#endif

#endif
