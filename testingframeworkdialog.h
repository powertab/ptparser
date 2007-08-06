/////////////////////////////////////////////////////////////////////////////
// Name:            testingframeworkdialog.h
// Purpose:         GUI front end for the testing framework
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 2, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __TESTINGFRAMEWORKDIALOG_H__
#define __TESTINGFRAMEWORKDIALOG_H__

/// GUI front end for the testing framework
class TestingFrameworkDialog : public wxDialog
{
// Constants
public:
    // Results Tree Ctrl Imagelist
    static const int RESULTSTREECTRL_IMAGE_TESTRESULTS;
    static const int RESULTSTREECTRL_IMAGE_TIMER;
    static const int RESULTSTREECTRL_IMAGE_TESTSUITE_OK;
    static const int RESULTSTREECTRL_IMAGE_TESTSUITE_WARNING;
    static const int RESULTSTREECTRL_IMAGE_TESTSUITE_FAILURE;
    static const int RESULTSTREECTRL_IMAGE_TIMERDOC;
    static const int RESULTSTREECTRL_IMAGE_TEST_INFORMATION;
    static const int RESULTSTREECTRL_IMAGE_TEST_WARNING;
    static const int RESULTSTREECTRL_IMAGE_TEST_FAILURE;

// Member Variables
protected:
    static TestingFrameworkDialog*      m_this;                             ///< Pointer to the dialog (used by the callback function)
    bool                                m_controlsInitialized;              ///< Indicates whether or not the dialog controls have been successfully initialized
    
    TestingFramework*                   m_testingFramework;                 ///< TestingFramework object containing all the test suites to run
    bool                                m_running;                          ///< Indicates whether or not the testing framework is running
    bool                                m_cancelTestRun;                    ///< Indicates whether or not the test run has been cancelled by the user
    int                                 m_testsRun;                         ///< Number of tests performed in the active tests run
    int                                 m_testsFailed;                      ///< Number of tests that have failed in the active test run
    WX_DECLARE_HASH_MAP(int, TestSuite*, wxIntegerHash, wxIntegerEqual, TestSuiteHashMap);
    TestSuiteHashMap                    m_testSuiteCheckListBoxHashMap;     ///< Maps list box indices to test suites
    WX_DECLARE_HASH_MAP(TestSuite*, wxTreeItemId, wxPointerHash, wxPointerEqual, ResultsTreeCtrlHashMap);
    ResultsTreeCtrlHashMap              m_resultsTreeCtrlHashMap;           ///< Maps tests suites to tree item ids
    wxLongLong                          m_startTime;                        ///< Stores the start time for a given test suite
    double                              m_totalTime;                        ///< Total time taken to perform the active test run

// Constructor/Destructor
public:
    TestingFrameworkDialog();
    ~TestingFrameworkDialog();

// Testing Framework Functions
    /// Sets the testing framework
    /// @param testingFramework Pointer to the testing framework to set
    /// @return True if the testing framework was set, false if not
    bool SetTestingFramework(TestingFramework* testingFramework)
    {
        wxCHECK(testingFramework != NULL, false);
        m_testingFramework = testingFramework;
        return (true);
    }
       
// Test Suite Functions
    void RunTestSuites();
    void StartTestSuite(TestSuite* testSuite);
    static bool TestSuiteCallback(TestSuite* testSuite, const wxChar* testName,
        bool success, const wxChar* fileName, size_t lineNumber, bool record,
        double executionTime, void* clientData);
    void EndTestSuite(TestSuite* testSuite);
    
// Operations
    bool InitializeDialogControls();
    void PopulateTestSuiteListBox();
    void InitializeResultsTreeCtrlImageList();
    bool IsTestSuiteChecked() const;
    void PumpEvents();
       
// Dialog Controls
    wxCheckListBox*     m_testSuiteCheckListBox;
    wxTreeCtrl*         m_resultsTreeCtrl;
    wxStaticText*       m_testSuiteStaticText;
    wxGauge*            m_totalProgressGauge;
    wxGauge*            m_testSuiteProgressGauge;
    wxTextCtrl*         m_testsRunTextCtrl;
    wxTextCtrl*         m_testsFailedTextCtrl;
    wxButton*           m_runButton;
    wxButton*           m_selectAllButton;
    wxButton*           m_deselectAllButton;
    wxButton*           m_stopButton;
    wxButton*           m_exportButton;
    wxButton*           m_clearButton;
    wxButton*           m_OKButton;   
    wxImageList         m_resultsTreeCtrlImageList;

// Events
    void OnInitDialog(wxInitDialogEvent& event);
    void OnUpdateTestSuiteCheckListBox(wxUpdateUIEvent& event);
    void OnBnClickedRunButton(wxCommandEvent& event);
    void OnUpdateRunButton(wxUpdateUIEvent& event);
    void OnBnClickedSelectAllButton(wxCommandEvent& event);
    void OnUpdateSelectAllButton(wxUpdateUIEvent& event);
    void OnBnClickedDeselectAllButton(wxCommandEvent& event);
    void OnUpdateDeselectAllButton(wxUpdateUIEvent& event);
    void OnBnClickedStopButton(wxCommandEvent& event);
    void OnUpdateStopButton(wxUpdateUIEvent& event);
    void OnBnClickedExportButton(wxCommandEvent& event);
    void OnUpdateExportButton(wxUpdateUIEvent& event);
    void OnBnClickedClearButton(wxCommandEvent& event);
    void OnUpdateClearButton(wxUpdateUIEvent& event);
    void OnOK(wxCommandEvent& event);
    void OnUpdateOKButton(wxUpdateUIEvent& event);
    DECLARE_EVENT_TABLE()
};

#endif
