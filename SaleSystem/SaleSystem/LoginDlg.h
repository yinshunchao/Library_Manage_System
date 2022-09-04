#pragma once


// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_user;
	CString m_pwd;
	virtual BOOL OnInitDialog();
	//afx_msg void OnBnClickedButtonCancel();
	//afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnClose();
	virtual void OnOK();
};
