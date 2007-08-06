/////////////////////////////////////////////////////////////////////////////
// Name:            teststream.h
// Purpose:         Wrapper for memory streams used to perform serialization testing
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 24, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __TESTSTREAM_H__
#define __TESTSTREAM_H__

/// Wrapper for memory streams used to perform serialization testing
class TestStream
{
// Constants
protected:
    // Default Constants
    static const wxMemoryInputStream*   DEFAULT_INPUT_STREAM;           ///< Default value for the input stream member variable
    
// Member Variables
    wxMemoryInputStream*        m_inputStream;                          ///< Memory input stream (created on the fly due to constructor limitations)
    wxMemoryOutputStream        m_outputStream;                         ///< Memory output stream

// Constructor/Destructor
public:
    TestStream();
    ~TestStream();
    
// Input Stream Functions
    wxMemoryInputStream& GetInputStream();
protected:
    bool CreateInputStream();
    void DeleteInputStream();

// Output Stream Functions
public:
    /// Gets a reference to the output stream
    /// @return Reference to the output stream
    wxMemoryOutputStream& GetOutputStream()                             {return (m_outputStream);}
    
    /// Checks the current state of the output stream
    /// @return True if the stream is OK, false if an error has occurred
    bool CheckOutputState() const                                       {return (m_outputStream.IsOk() && (m_outputStream.GetOutputStreamBuffer() != NULL));}
};

#endif
