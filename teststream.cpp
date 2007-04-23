/////////////////////////////////////////////////////////////////////////////
// Name:            teststream.cpp
// Purpose:         Wrapper for memory streams used to perform serialization testing
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 24, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "teststream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Default constants
const wxMemoryInputStream*   TestStream::DEFAULT_INPUT_STREAM = NULL;

// Constructor/Destructor
/// Default Constructor
TestStream::TestStream() : m_inputStream((wxMemoryInputStream*)DEFAULT_INPUT_STREAM)
{
    //------Last Checked------//
    // - Dec 24, 2004
}

/// Destructor
TestStream::~TestStream()
{
    //------Last Checked------//
    // - Dec 24, 2004
    DeleteInputStream();
}

/// Gets a reference to the input stream (must be called after all output has been written)
/// @return A reference to the input stream
wxMemoryInputStream& TestStream::GetInputStream()
{
    //------Last Checked------//
    // - Dec 24, 2004

    // Input stream doesn't exist, create it    
    if (m_inputStream == NULL)
    {
        // If create fails, create an empty stream 
        // (we need to ensure the reference returned is valid)
        if (!CreateInputStream())
            m_inputStream = new wxMemoryInputStream(NULL, 0);
    }

    wxASSERT(m_inputStream != NULL);
    return (*m_inputStream);
}

/// Creates the input stream using the output stream buffer data
/// @return True if the input stream was created, false if not
bool TestStream::CreateInputStream()
{
    //------Last Checked------//
    // - Dec 24, 2004
    
    // Delete the current stream (if any)
    DeleteInputStream();
    
    // Make sure the output stream buffer is valid
    wxStreamBuffer* streamBuffer = m_outputStream.GetOutputStreamBuffer();
    wxCHECK(streamBuffer != NULL, false);
    
    // Create the input stream
    m_inputStream = new wxMemoryInputStream(streamBuffer->GetBufferStart(), streamBuffer->GetBufferSize());
    
    return (true);
}

/// Deletes the input stream
void TestStream::DeleteInputStream()
{
    //------Last Checked------//
    // - Dec 24, 2004
    if (m_inputStream != NULL)
    {
        delete m_inputStream;
        m_inputStream = NULL;
    }
}
