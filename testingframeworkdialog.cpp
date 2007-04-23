/////////////////////////////////////////////////////////////////////////////
// Name:            testingframeworkdialog.cpp
// Purpose:         GUI front end for the testing framework
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 2, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "powertabparser.h"             // Needed for wxGetApp
#include "testingframeworkdialog.h"
#include <wx/textfile.h>                // Needed for saving results file

// Resource includes
#include "rc/clipboardwithcheck_16x16.xpm"
#include "rc/timer_16x16.xpm"
#include "rc/greencheck_16x16.xpm"
#include "rc/yellowx_16x16.xpm"
#include "rc/redx_16x16.xpm"
#include "rc/timerdoc_16x16.xpm"
#include "rc/info3_16x16.xpm"
#include "rc/yellowexclamationpoint_16x16.xpm"
#include "rc/redexclamationpoint_16x16.xpm"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Results Tree Control Image Constants
const int TestingFrameworkDialog::RESULTSTREECTRL_IMAGE_TESTRESULTS                 = 0;
const int TestingFrameworkDialog::RESULTSTREECTRL_IMAGE_TIMER                       = 1;
const int TestingFrameworkDialog::RESULTSTREECTRL_IMAGE_TESTSUITE_OK                = 2;
const int TestingFrameworkDialog::RESULTSTREECTRL_IMAGE_TESTSUITE_WARNING           = 3;
const int TestingFrameworkDialog::RESULTSTREECTRL_IMAGE_TESTSUITE_FAILURE           = 4;
const int TestingFrameworkDialog::RESULTSTREECTRL_IMAGE_TIMERDOC                    = 5;
const int TestingFrameworkDialog::RESULTSTREECTRL_IMAGE_TEST_INFORMATION            = 6;
const int TestingFrameworkDialog::RESULTSTREECTRL_IMAGE_TEST_WARNING                = 7;
const int TestingFrameworkDialog::RESULTSTREECTRL_IMAGE_TEST_FAILURE                = 8;

// Static Member Variables
TestingFrameworkDialog* TestingFrameworkDialog::m_this = (TestingFrameworkDialog*)NULL;

// Constructor/Destructor
/// Default Constructor
TestingFrameworkDialog::TestingFrameworkDialog() :
    m_controlsInitialized(false), m_testingFramework(NULL), m_running(false),
    m_cancelTestRun(false), m_testsRun(0), m_testsFailed(0), m_startTime(0),
    m_totalTime(0), m_testSuiteCheckListBox(NULL), m_resultsTreeCtrl(NULL),
    m_testSuiteStaticText(NULL), m_totalProgressGauge(NULL),
    m_testSuiteProgressGauge(NULL), m_testsRunTextCtrl(NULL),
    m_testsFailedTextCtrl(NULL), m_runButton(NULL), m_selectAllButton(NULL),
    m_deselectAllButton(NULL), m_stopButton(NULL), m_exportButton(NULL),
    m_clearButton(NULL), m_OKButton(NULL)
{
    //------Last Checked------//
    // - Dec 13, 2004
    m_this = this;
    
    bool loaded = wxXmlResource::Get()->LoadDialog(this, NULL,
        wxT("IDD_TESTINGFRAMEWORK_DIALOG"));
    wxCHECK2(loaded, return);
}

/// Destructor
TestingFrameworkDialog::~TestingFrameworkDialog()
{
    //------Last Checked------//
    // - Apr 22, 2007
    
    // Automatically delete the testing framework
    if (m_testingFramework != NULL)
    {
        delete m_testingFramework;
        m_testingFramework = (TestingFramework*)NULL;
    }
}

// Event Table
// NOTE: If you ever add a Cancel button, be sure to add an event handler for wxID_CANCEL
// and make sure the user can't Cancel while the tests are running
BEGIN_EVENT_TABLE(TestingFrameworkDialog, wxDialog)
    EVT_INIT_DIALOG(TestingFrameworkDialog::OnInitDialog)
    EVT_UPDATE_UI(XRCID("IDC_TESTSUITE_CHECKLISTBOX"), TestingFrameworkDialog::OnUpdateTestSuiteCheckListBox)
    EVT_BUTTON(XRCID("IDC_RUN_BUTTON"), TestingFrameworkDialog::OnBnClickedRunButton)
    EVT_UPDATE_UI(XRCID("IDC_RUN_BUTTON"), TestingFrameworkDialog::OnUpdateRunButton)
    EVT_BUTTON(XRCID("IDC_SELECTALL_BUTTON"), TestingFrameworkDialog::OnBnClickedSelectAllButton)
    EVT_UPDATE_UI(XRCID("IDC_SELECTALL_BUTTON"), TestingFrameworkDialog::OnUpdateSelectAllButton)
    EVT_BUTTON(XRCID("IDC_DESELECTALL_BUTTON"), TestingFrameworkDialog::OnBnClickedDeselectAllButton)
    EVT_UPDATE_UI(XRCID("IDC_DESELECTALL_BUTTON"), TestingFrameworkDialog::OnUpdateDeselectAllButton)
    EVT_BUTTON(XRCID("IDC_STOP_BUTTON"), TestingFrameworkDialog::OnBnClickedStopButton)
    EVT_UPDATE_UI(XRCID("IDC_STOP_BUTTON"), TestingFrameworkDialog::OnUpdateStopButton)
    EVT_BUTTON(XRCID("IDC_EXPORT_BUTTON"), TestingFrameworkDialog::OnBnClickedExportButton)
    EVT_UPDATE_UI(XRCID("IDC_EXPORT_BUTTON"), TestingFrameworkDialog::OnUpdateExportButton)
    EVT_BUTTON(XRCID("IDC_CLEAR_BUTTON"), TestingFrameworkDialog::OnBnClickedClearButton)
    EVT_UPDATE_UI(XRCID("IDC_CLEAR_BUTTON"), TestingFrameworkDialog::OnUpdateClearButton)
    EVT_BUTTON(XRCID("wxID_OK"), TestingFrameworkDialog::OnOK)
    EVT_UPDATE_UI(XRCID("wxID_OK"), TestingFrameworkDialog::OnUpdateOKButton)
END_EVENT_TABLE()

void TestingFrameworkDialog::OnInitDialog(wxInitDialogEvent& WXUNUSED(event))
{
    //------Last Checked------//
    // - Apr 22, 2007
    m_controlsInitialized = InitializeDialogControls();
    InitializeResultsTreeCtrlImageList();
    PopulateTestSuiteListBox();
}

void TestingFrameworkDialog::OnUpdateTestSuiteCheckListBox(
    wxUpdateUIEvent& event)
{
    //------Last Verified------//
    // - Dec 2, 2004
    event.Enable(!m_running);
}

void TestingFrameworkDialog::OnBnClickedRunButton(
    wxCommandEvent& WXUNUSED(event))
{
    //------Last Checked------//
    // - Apr 22, 2007
    RunTestSuites();
}

void TestingFrameworkDialog::OnUpdateRunButton(wxUpdateUIEvent& event)
{
    //------Last Verified------//
    // - Dec 2, 2004
    event.Enable(!m_running && IsTestSuiteChecked());
}

void TestingFrameworkDialog::OnBnClickedSelectAllButton(
    wxCommandEvent& WXUNUSED(event))
{
    //------Last Checked------//
    // - Apr 22, 2007
    wxCHECK2(m_controlsInitialized, return);
    
    // Select (check) all the items in the test suite check list box
    int i = 0;
    int count = m_testSuiteCheckListBox->GetCount();
    for (; i < count; i++)
        m_testSuiteCheckListBox->Check(i);
}

void TestingFrameworkDialog::OnUpdateSelectAllButton(wxUpdateUIEvent& event)
{
    //------Last Verified------//
    // - Dec 2, 2004
    event.Enable(!m_running);
}

void TestingFrameworkDialog::OnBnClickedDeselectAllButton(
    wxCommandEvent& WXUNUSED(event))
{
    //------Last Verified------//
    // - Dec 2, 2004
    wxCHECK2(m_controlsInitialized, return);
    
    // Clear (uncheck) all the items in the test suite check list box
    int i = 0;
    int count = m_testSuiteCheckListBox->GetCount();
    for (; i < count; i++)
        m_testSuiteCheckListBox->Check(i, false);
}

void TestingFrameworkDialog::OnUpdateDeselectAllButton(wxUpdateUIEvent& event)
{
    //------Last Verified------//
    // - Dec 2, 2004
    event.Enable(!m_running);
}

void TestingFrameworkDialog::OnBnClickedStopButton(
    wxCommandEvent& WXUNUSED(event))
{
    //------Last Checked------//
    // - Apr 22, 2007

    // m_cancelTestRun is tested in the callback function
    m_cancelTestRun = true;
}

void TestingFrameworkDialog::OnUpdateStopButton(wxUpdateUIEvent& event)
{
    //------Last Verified------//
    // - Dec 2, 2004
    event.Enable(m_running && !m_cancelTestRun);
}

void TestingFrameworkDialog::OnBnClickedExportButton(
    wxCommandEvent& WXUNUSED(event))
{
    //------Last Checked------//
    // - Apr 22, 2007

    // Write the results to a text file
    wxFileDialog fileDialog(this, wxT("Save Results"), wxT(""),
        wxT("results.txt"), wxT("Text files (*.txt)|*.txt"),
        wxSAVE | /*wxHIDE_READONLY |*/ wxOVERWRITE_PROMPT);
    if (fileDialog.ShowModal() == wxID_OK)
    {
        wxString pathName = fileDialog.GetPath();
        
        // Create a new file
        wxTextFile file;
        file.Create(pathName);

        wxBusyCursor busyCursor;

        // Step - Write the header data
        file.AddLine(wxT("Testing Framework Test Results"));
        file.AddLine(wxT("------------------------------"));

        // TODO: add user system setup here; OS, CPU, etc.
        wxString text;
        text = wxString::Format(wxT("Total time       : %.3f seconds"),
            m_totalTime);
        file.AddLine(text);
        text = wxString::Format(wxT("Tests run        : %s"),
            m_testsRunTextCtrl->GetValue().c_str());
        file.AddLine(text);
        text = wxString::Format(wxT("Tests failed     : %s"),
            m_testsFailedTextCtrl->GetValue().c_str());
        file.AddLine(text);
        text = wxString::Format(wxT("Date             : %s"),
            wxGetLocaleShortDateTime(wxDateTime::Now()).c_str());
        file.AddLine(text);
        file.AddLine(wxT(""));

        wxTreeItemId rootTreeItemId = m_resultsTreeCtrl->GetRootItem();
        if (rootTreeItemId)
        {
            //long cookie = wxNewId();
            wxTreeItemIdValue cookie;
            wxTreeItemId testSuiteTreeItemId =
                m_resultsTreeCtrl->GetFirstChild(rootTreeItemId, cookie);
            for (; testSuiteTreeItemId.IsOk(); testSuiteTreeItemId =
                m_resultsTreeCtrl->GetNextSibling(testSuiteTreeItemId))
            {
                wxString strItemText =
                    m_resultsTreeCtrl->GetItemText(testSuiteTreeItemId);
                file.AddLine(strItemText);
                
                //long cookie2 = wxNewId();
                wxTreeItemIdValue cookie2;
                wxTreeItemId messageTreeItemId =
                    m_resultsTreeCtrl->GetFirstChild(testSuiteTreeItemId, cookie2);
                for (; messageTreeItemId.IsOk();
                    messageTreeItemId = m_resultsTreeCtrl->GetNextSibling(messageTreeItemId))
                {
                    wxString message = wxT("\t");
                    message += m_resultsTreeCtrl->GetItemText(messageTreeItemId);
                    file.AddLine(message);
                }
                
                file.AddLine(wxT(""));
            }
        }
       
        file.Write();
        file.Close();
    }
}

void TestingFrameworkDialog::OnUpdateExportButton(wxUpdateUIEvent& event)
{
    //------Last Verified------//
    // - Dec 2, 2004
    wxCHECK2(m_controlsInitialized, return);
    event.Enable((!m_running && (m_resultsTreeCtrl->GetCount() > 0)));
}

void TestingFrameworkDialog::OnBnClickedClearButton(
    wxCommandEvent& WXUNUSED(event))
{
    //------Last Checked------//
    // - Apr 22, 2007
    wxCHECK2(m_controlsInitialized, return);
    
    // Clear the stats and the results tree
    m_testsRunTextCtrl->SetValue(wxT("0"));
    m_testsFailedTextCtrl->SetValue(wxT("0"));
    m_resultsTreeCtrl->DeleteAllItems();
}

void TestingFrameworkDialog::OnUpdateClearButton(wxUpdateUIEvent& event)
{
    //------Last Verified------//
    // - Dec 2, 2004
    wxCHECK2(m_controlsInitialized, return);
    event.Enable((!m_running && (m_resultsTreeCtrl->GetCount() > 0)));
}

void TestingFrameworkDialog::OnOK(wxCommandEvent& event)
{
    //------Last Checked------//
    // - Apr 22, 2007
    
    // Don't allow dialog to close if tests are running
    if (m_running)
        return;

    // The "event.Skip()" call tells wxWidgets to continue processing the
    // default behavior
    event.Skip();
}

void TestingFrameworkDialog::OnUpdateOKButton(wxUpdateUIEvent& event)
{
    //------Last Verified------//
    // - Dec 2, 2004
    event.Enable(!m_running);
}

// Test Suite Functions
/// Runs all the selected test suites in the testing framework
void TestingFrameworkDialog::RunTestSuites()
{
    //------Last Verified------//
    // - Dec 2, 2004
    
    // Already running?
    if (m_running)
        return;

    // We need at least one test suite checked to run
    if (!IsTestSuiteChecked())
        return;

    wxCHECK2(m_controlsInitialized, return);
    wxCHECK2(m_testingFramework != NULL, return);

    // Disable all other windows save for this one
    wxWindowDisabler(this);
   
    m_totalTime = 0.0f;
    m_cancelTestRun = false;
    m_running = true;

    // Mark down the start time for the test run
    wxLongLong startTime = ::wxGetLocalTimeMillis();
    
    ::wxBeginBusyCursor();
    
    // Clean-up current results tree ctrl data
    m_resultsTreeCtrlHashMap.clear();
    m_resultsTreeCtrl->DeleteAllItems();

    // Update the execution status for each test suite
    size_t testSuiteIndex = 0;
    size_t testSuiteCount = m_testSuiteCheckListBox->GetCount();
    for (; testSuiteIndex < testSuiteCount; testSuiteIndex++)
    {
        bool execute = m_testSuiteCheckListBox->IsChecked(testSuiteIndex);
        
        TestSuite* testSuite = m_testSuiteCheckListBoxHashMap[testSuiteIndex];
        wxCHECK2(testSuite != NULL, continue);
        
        testSuite->SetExecute(execute);
    }

    // Reset the statistics and gauges
    m_testsRun = m_testsFailed = 0;
    m_testsRunTextCtrl->SetValue(wxT("0"));
    m_testsFailedTextCtrl->SetValue(wxT("0"));
    m_totalProgressGauge->SetRange(m_testingFramework->GetTestSuiteCount());
    m_totalProgressGauge->SetValue(0);

    // Insert the manditory root item
    wxTreeItemId rootItemId = m_resultsTreeCtrl->AddRoot(
        wxT("Test Run Results..."));
    
    // Run the test suites
    bool userAborted = false;
    testSuiteIndex = 0;
    testSuiteCount = m_testingFramework->GetTestSuiteCount();
    for (; testSuiteIndex < testSuiteCount; testSuiteIndex++)
    {
        TestSuite* testSuite = m_testingFramework->GetTestSuite(testSuiteIndex);
        wxCHECK2(testSuite != NULL, continue);

        // If test suite is marked for execution, run it
        if (testSuite->IsExecuted())
        {
            StartTestSuite(testSuite);
            bool cancelled = !testSuite->Run(TestSuiteCallback, this);
            EndTestSuite(testSuite);

            // User pushed cancel; break out of the loop
            if (cancelled)
            {
                userAborted = true;
                break;
            }
        }
    }
    
    m_resultsTreeCtrl->SelectItem(m_resultsTreeCtrl->GetRootItem());
    
    ::wxEndBusyCursor();
    
    // Mark down the total time for the test run
    wxLongLong totalTime = ::wxGetLocalTimeMillis() - startTime;
    m_totalTime = ((double)totalTime.ToLong()) / 1000.0;
        
    // Reset all the stats and gauges
    m_running = false;
    m_testSuiteStaticText->SetLabel(wxT(""));
    m_testSuiteProgressGauge->SetValue(0);
    m_totalProgressGauge->SetValue(0);    

    // Notify user that testing is done
    if (userAborted)
    {
        wxMessageBox(wxT("Test run aborted by user."), wxTheApp->GetAppName(),
            wxICON_EXCLAMATION);
    }
    else
    {
        wxMessageBox(wxString::Format(
            wxT("Test run completed in %.3f seconds."), m_totalTime),
            wxTheApp->GetAppName(), wxICON_INFORMATION);
    }
}

/// Initializes a TestSuite object prior to running
/// @param testSuite TestSuite object to start
void TestingFrameworkDialog::StartTestSuite(TestSuite* testSuite)
{
    //------Last Verified------//
    // - Dec 2, 2004
    wxCHECK2(m_controlsInitialized, return);
    wxCHECK2(testSuite != NULL, return);

    // Mark down the start time
    m_startTime = ::wxGetLocalTimeMillis();

    // Update the test suite name
    wxString strName = testSuite->GetName();
    m_testSuiteStaticText->SetLabel(strName);
    PumpEvents();

    // Reset the test suite gauge controls
    m_testSuiteProgressGauge->SetRange(testSuite->GetTestCount());
    m_testSuiteProgressGauge->SetValue(0);
    PumpEvents();
   
    // Add the test suite to the results tree ctrl
    wxTreeItemId treeItemId = m_resultsTreeCtrl->AppendItem(
        m_resultsTreeCtrl->GetRootItem(), strName, RESULTSTREECTRL_IMAGE_TIMER,
        RESULTSTREECTRL_IMAGE_TIMER);
    m_resultsTreeCtrl->Expand(m_resultsTreeCtrl->GetRootItem());
    if (treeItemId)
    {
        m_resultsTreeCtrl->SetItemBold(treeItemId);
        m_resultsTreeCtrlHashMap[testSuite] = treeItemId;
        PumpEvents();

        wxString text = wxString::Format(wxT("[%s] - Starting test suite."),
            wxGetLocaleShortDateTime(wxDateTime::Now()).c_str());
        m_resultsTreeCtrl->AppendItem(treeItemId, text,
            RESULTSTREECTRL_IMAGE_TIMERDOC, RESULTSTREECTRL_IMAGE_TIMERDOC);
        PumpEvents();
    }
}

/// Callback function used to receive the results of a test in a test suite
/// @param testSuite Test suite that the test belongs to
/// @param testName Name of the test
/// @param success Indicates the success/failure of the test
/// @param fileName Name of the file where the test occurred
/// @param lineNumber Line number in the file where the test occurred
/// @param record Indicates whether or note the results of the test should be
/// recorded to the results tree ctrl if the test was successful
/// @param executionTime Time it took to run the test (in seconds)
/// @param clientData Pointer to custom data (unused)
bool TestingFrameworkDialog::TestSuiteCallback(TestSuite* testSuite,
    const wxChar* testName, bool success, const wxChar* fileName,
    size_t lineNumber, bool record, double executionTime,
    void* WXUNUSED(clientData))
{
    //------Last Checked------//
    // - Apr 22, 2007
    wxCHECK(m_this != NULL, false);
    wxCHECK(m_this->m_controlsInitialized, false);
    wxCHECK(testSuite != NULL, false);

    // Update the tests run stat
    m_this->m_testsRun++;
    
    // Update the test suite progress
    m_this->m_testSuiteProgressGauge->SetValue(
        m_this->m_testSuiteProgressGauge->GetValue() + 1);
    m_this->PumpEvents();
        
    // Lookup the results tree ctrl treeItemId for the test suite
    wxTreeItemId treeItemId = m_this->m_resultsTreeCtrlHashMap[testSuite];
    m_this->PumpEvents();

    if (treeItemId)
    {
        // Test failed; add a failure message to the results tree ctrl
        if (!success)
        {
            wxString text = wxString::Format(
                wxT("[%s] - Test '%s' failed. %s(%d)"),
                wxGetLocaleShortDateTime(wxDateTime::Now()).c_str(), testName,
                fileName, lineNumber);
            wxTreeItemId error = m_this->m_resultsTreeCtrl->AppendItem(
                treeItemId, text, RESULTSTREECTRL_IMAGE_TEST_FAILURE,
                RESULTSTREECTRL_IMAGE_TEST_FAILURE);
            m_this->m_resultsTreeCtrl->SetItemTextColour(error,
                wxColour(0x7f, 0, 0));
            m_this->PumpEvents();
            m_this->m_testsFailed++;
        }
        // Test was successful and is set to be recorded, so record it
        else if (record)
        {
            wxString text = wxString::Format(
                wxT("[%s] - Test '%s' completed in %.3f seconds."),
                wxGetLocaleShortDateTime(wxDateTime::Now()).c_str(), testName,
                executionTime);
            wxTreeItemId ok = m_this->m_resultsTreeCtrl->AppendItem(treeItemId,
                text, RESULTSTREECTRL_IMAGE_TEST_INFORMATION,
                RESULTSTREECTRL_IMAGE_TEST_INFORMATION);
            m_this->m_resultsTreeCtrl->SetItemTextColour(ok, wxColor(0,0,0x7f));
            m_this->PumpEvents();
        }
    }

    // Update the # of tests run text ctrl
    m_this->m_testsRunTextCtrl->SetValue(wxString::Format(wxT("%d"),
        m_this->m_testsRun));
    m_this->PumpEvents();

    // If we had a failure, update the tests failed text ctrl
    if (!success)
    {
        m_this->m_testsFailedTextCtrl->SetValue(wxString::Format(wxT("%d"),
            m_this->m_testsFailed));
        m_this->PumpEvents();
    }

    // Everything has gone OK; return the results of the user triggered cancel
    // flag in case user pushed Stop button
    return (!m_this->m_cancelTestRun);
}

/// Performs maintenance after a TestSuite object has completed running
/// @param testSuite TestSuite object that has just completed running
void TestingFrameworkDialog::EndTestSuite(TestSuite* testSuite)
{   
    //------Last Verified------//
    // - Dec 2, 2004
    wxCHECK2(m_controlsInitialized, return);
    wxCHECK2(testSuite != NULL, return);
    
    // Step - Get the tree item for the test suite
    wxTreeItemId treeItemId = m_resultsTreeCtrlHashMap[testSuite];
    if (treeItemId)
    {
        int image = RESULTSTREECTRL_IMAGE_TESTSUITE_OK;
        
        // CASE: If the tests run total doesn't match the expected test count,
        // display an error
        if (testSuite->GetTestsRun() != testSuite->GetTestCount())
        {
            image = RESULTSTREECTRL_IMAGE_TESTSUITE_WARNING;
            wxString strTestCount = wxString::Format(wxT("%d"),
                testSuite->GetTestCount());
            wxString strTestsRun = wxString::Format(wxT("%d"),
                testSuite->GetTestsRun());

            wxString text = wxString::Format(
                wxT("[%s] - GetTestCount returns a different value than the") \
                wxT("actual test run count. (%s vs %s)"),
                wxGetLocaleShortDateTime(wxDateTime::Now()).c_str(),
                strTestCount.c_str(),
                strTestsRun.c_str());
            wxTreeItemId warning = m_resultsTreeCtrl->AppendItem(
                treeItemId, text, RESULTSTREECTRL_IMAGE_TEST_WARNING,
                RESULTSTREECTRL_IMAGE_TEST_WARNING);
            m_resultsTreeCtrl->SetItemTextColour(warning,
                wxColour(0x7f, 0x7f, 0));
            
            PumpEvents();
        }
        
        if (testSuite->HasFailed())
            image = RESULTSTREECTRL_IMAGE_TESTSUITE_FAILURE;

        // Step - Get the time taken to run the test suite
        double suiteTime = (double)(
            (::wxGetLocalTimeMillis() - m_startTime).ToLong()) / 1000.0f;
        wxString text = wxString::Format(
            wxT("[%s] - Test suite completed in %.3f seconds. Tests run: %d; ") \
            wxT("Tests failed: %d"),
            wxGetLocaleShortDateTime(wxDateTime::Now()).c_str(), suiteTime,
            testSuite->GetTestsRun(), testSuite->GetFailed());
        m_resultsTreeCtrl->AppendItem(treeItemId, text,
            RESULTSTREECTRL_IMAGE_TIMERDOC, RESULTSTREECTRL_IMAGE_TIMERDOC);
        PumpEvents();
        
        m_resultsTreeCtrl->SetItemImage(treeItemId, image);
        m_resultsTreeCtrl->SetItemImage(treeItemId, image,
            wxTreeItemIcon_Selected);
        
        if (image != RESULTSTREECTRL_IMAGE_TESTSUITE_OK)
            m_resultsTreeCtrl->Expand(treeItemId);
        PumpEvents();
    }

    // Step - Offset the test suite progress control
    m_totalProgressGauge->SetValue(m_totalProgressGauge->GetValue() + 1);
    PumpEvents();
}

// Operations
/// Initializes all of the controls used in the dialog box
bool TestingFrameworkDialog::InitializeDialogControls()
{
    //------Last Verified------//
    // - Dec 2, 2004
    
    m_testSuiteCheckListBox = XRCCTRL(*this, "IDC_TESTSUITE_CHECKLISTBOX",
        wxCheckListBox);
    wxCHECK(m_testSuiteCheckListBox != NULL, false);
    
    m_resultsTreeCtrl = XRCCTRL(*this, "IDC_RESULTS_TREECTRL", wxTreeCtrl);
    wxCHECK(m_resultsTreeCtrl != NULL, false);
    
    m_testSuiteStaticText = XRCCTRL(*this, "IDC_TESTSUITE_STATIC",
        wxStaticText);
    wxCHECK(m_testSuiteStaticText != NULL, false);
    
    m_totalProgressGauge = XRCCTRL(*this, "IDC_TOTAL_PROGRESS", wxGauge);
    wxCHECK(m_totalProgressGauge != NULL, false);
    
    m_testSuiteProgressGauge = XRCCTRL(*this, "IDC_TESTSUITE_PROGRESS",
        wxGauge);
    wxCHECK(m_testSuiteProgressGauge != NULL, false);
    
    m_testsRunTextCtrl = XRCCTRL(*this, "IDC_TESTSRUN_EDIT", wxTextCtrl);
    wxCHECK(m_testsRunTextCtrl != NULL, false);
    m_testsRunTextCtrl->SetEditable(false);
    
    m_testsFailedTextCtrl = XRCCTRL(*this, "IDC_TESTSFAILED_EDIT", wxTextCtrl);
    wxCHECK(m_testsFailedTextCtrl != NULL, false);
    m_testsFailedTextCtrl->SetEditable(false);
    
    m_runButton = XRCCTRL(*this, "IDC_RUN_BUTTON", wxButton);
    wxCHECK(m_runButton != NULL, false);
    
    m_selectAllButton = XRCCTRL(*this, "IDC_SELECTALL_BUTTON", wxButton);
    wxCHECK(m_selectAllButton != NULL, false);
    
    m_deselectAllButton = XRCCTRL(*this, "IDC_DESELECTALL_BUTTON", wxButton);
    wxCHECK(m_deselectAllButton != NULL, false);
    
    m_stopButton = XRCCTRL(*this, "IDC_STOP_BUTTON", wxButton);
    wxCHECK(m_stopButton != NULL, false);
    
    m_exportButton = XRCCTRL(*this, "IDC_EXPORT_BUTTON", wxButton);
    wxCHECK(m_exportButton != NULL, false);
    
    m_clearButton = XRCCTRL(*this, "IDC_CLEAR_BUTTON", wxButton);
    wxCHECK(m_clearButton != NULL, false);
    
    m_OKButton = XRCCTRL(*this, "wxID_OK", wxButton);
    wxCHECK(m_OKButton != NULL, false);
    
    return (true);
}

/// Populates the test suite list box with the names of the test suites in the
/// testing framework
void TestingFrameworkDialog::PopulateTestSuiteListBox()
{
    //------Last Verified------//
    // - Dec 2, 2004

    wxCHECK2(m_controlsInitialized, return);
    
    m_testingFramework->SortTestSuitesByName();
    m_testSuiteCheckListBox->Clear();
    
    // Add each test suite name to the list box
    size_t testSuiteIndex = 0;
    size_t testSuiteCount = m_testingFramework->GetTestSuiteCount();
    for (; testSuiteIndex < testSuiteCount; testSuiteIndex++)
    {
        TestSuite* testSuite = m_testingFramework->GetTestSuite(testSuiteIndex);
        wxCHECK2(testSuite != NULL, continue);

        m_testSuiteCheckListBox->Append(testSuite->GetName());
    
        // Associate the list box index with the test suite
        // Note: Couldn't use SetClientData with check box control
        m_testSuiteCheckListBoxHashMap[testSuiteIndex] = testSuite;
    }

    // By default, select all the test suites
    // FIX: initialize the event properly
    wxCommandEvent event;
    OnBnClickedSelectAllButton(event);
}

/// Initializes the imagelist used by the results tree control
void TestingFrameworkDialog::InitializeResultsTreeCtrlImageList()
{
    //------Last Verified------//
    // - Dec 1, 2004
    
    wxCHECK2(m_controlsInitialized, return);
    
    m_resultsTreeCtrlImageList.Create(16, 16);
    wxColor maskColour = wxColor(255,0,255);
    
    m_resultsTreeCtrlImageList.Add(wxIcon(clipboardwithcheck_16x16_xpm),
        maskColour);
    m_resultsTreeCtrlImageList.Add(wxIcon(timer_16x16_xpm), maskColour);
    m_resultsTreeCtrlImageList.Add(wxIcon(greencheck_16x16_xpm), maskColour);
    m_resultsTreeCtrlImageList.Add(wxIcon(yellowx_16x16_xpm), maskColour);
    m_resultsTreeCtrlImageList.Add(wxIcon(redx_16x16_xpm), maskColour);
    m_resultsTreeCtrlImageList.Add(wxIcon(timerdoc_16x16_xpm), maskColour);
    m_resultsTreeCtrlImageList.Add(wxIcon(info3_16x16_xpm), maskColour);
    m_resultsTreeCtrlImageList.Add(wxIcon(yellowexclamationpoint_16x16_xpm),
        maskColour);
    m_resultsTreeCtrlImageList.Add(wxIcon(redexclamationpoint_16x16_xpm),
        maskColour);
    
    m_resultsTreeCtrl->SetImageList(&m_resultsTreeCtrlImageList);
}

/// Determines if there is at least one test suite checked in the test suite
/// list box
bool TestingFrameworkDialog::IsTestSuiteChecked() const
{
    //------Last Verified------//
    // - Dec 2, 2004

    wxCHECK(m_controlsInitialized, false);
    
    // Test each list item to see if it's checked
    int i = 0;
    int count = m_testSuiteCheckListBox->GetCount();
    for (; i < count; i++)
    {
        // Item is checked; return true
        if (m_testSuiteCheckListBox->IsChecked(i))
            return (true);
    }

    // No items checked
    return (false);
}

/// Allows event processing to continue in the dialog box while the tests are
/// running
void TestingFrameworkDialog::PumpEvents()
{
    //------Last Verified------//
    // - Dec 2, 2004

    // TODO: replace these individual calls to UpdateWindowUI with
    // wxDialog::UpdateWindowUI using descending flag in wxWidgets 2.5        
    if (m_controlsInitialized)
    {
        m_testSuiteCheckListBox->UpdateWindowUI();
        m_resultsTreeCtrl->UpdateWindowUI();
        m_testSuiteStaticText->UpdateWindowUI();
        m_totalProgressGauge->UpdateWindowUI();
        m_testSuiteProgressGauge->UpdateWindowUI();
        m_testsRunTextCtrl->UpdateWindowUI();
        m_testsFailedTextCtrl->UpdateWindowUI();
        m_runButton->UpdateWindowUI();
        m_selectAllButton->UpdateWindowUI();
        m_deselectAllButton->UpdateWindowUI();
        m_stopButton->UpdateWindowUI();
        m_exportButton->UpdateWindowUI();
        m_clearButton->UpdateWindowUI();
        m_OKButton->UpdateWindowUI();
    }
    wxYield();    
}
