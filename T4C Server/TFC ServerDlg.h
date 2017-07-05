// TFC ServerDlg.h : header file
//

#if !defined(AFX_TFCSERVERDLG_H__BC8F3068_A74F_11D0_9B9E_444553540000__INCLUDED_)
#define AFX_TFCSERVERDLG_H__BC8F3068_A74F_11D0_9B9E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CTFCServerDlg dialog
class CTFCServerDlg : public CDialog
{
// Dialog Data
	//{{AFX_DATA(CTFCServerDlg)
	enum { IDD = IDD_TFCMAIN_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTFCServerDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
// Construction
public:
	CTFCServerDlg(CWnd* pParent = NULL);	// standard constructor	

    void TerminateServer( bool boExit = true );

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTFCServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
public:
    afx_msg void OnClose();
protected:
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TFCSERVERDLG_H__BC8F3068_A74F_11D0_9B9E_444553540000__INCLUDED_)
