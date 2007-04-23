/////////////////////////////////////////////////////////////////////////////
// Name:            testingframework.h
// Purpose:         A framework for performing unit tests on classes
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 2, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "testingframework.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(TestingFramework, wxObject)

// TODO: add copy constructor + assignment operator

// Constructor/Destructor
/// Default Constructor
TestingFramework::TestingFramework()
{
	//------Last Checked------//
	// - Dec 2, 2004
}

/// Destructor
TestingFramework::~TestingFramework()
{
	//------Last Checked------//
	// - Dec 2, 2004
	
	// Clean-up the test suite array
	DeleteTestSuiteArrayContents();
}

// Test Suite Functions
/// Sorts the test suites by their name
/// @param sortAscending Indicates the direction of the sort: ascending or descending
void TestingFramework::SortTestSuitesByName(bool sortAscending)
{
    //------Last Checked------//
    // - Dec 2, 2004
	if (!sortAscending)
	    m_testSuiteArray.Sort(CompareTestSuiteNameDescending);
	else
	    m_testSuiteArray.Sort(CompareTestSuiteNameAscending);
}

/// Deletes the contents (and frees the memory) of the test suite array
void TestingFramework::DeleteTestSuiteArrayContents()
{
	//------Last Checked------//
	// - Dec 2, 2004

	// Free the memory used by each item, then clear the array
	size_t i = 0;
	size_t count = m_testSuiteArray.GetCount();
	for (i = 0; i < count; i++)
        delete m_testSuiteArray[i];
	m_testSuiteArray.Clear();
}
