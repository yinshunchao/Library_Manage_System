// LoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "CInfoFile.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_LOGIN, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLoginDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CLoginDlg::OnBnClickedButtonCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_user = TEXT("test");	//用户名
	m_pwd = TEXT("123456");//密码
	UpdateData(FALSE); //内容更新到对应的控件


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}




void CLoginDlg::OnBnClickedButtonLogin()
{
	// TODO:  在此添加控件通知处理程序代码
	//登陆按钮点击事件

	UpdateData(TRUE);

	if (m_user.IsEmpty() || m_pwd.IsEmpty())
	{
		MessageBox(TEXT("输入内容不能为空"));
		return;
	}

	//获取正确的值
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	if (name == m_user) //用户名一致
	{
		if (pwd == m_pwd) //密码一致
		{
			//关闭当前对话框
			CDialog::OnCancel();
		}
		else
		{
			MessageBox(TEXT("密码有误"));
		}
	}
	else
	{
		MessageBox(TEXT("用户名有误"));
	}

}


void CLoginDlg::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);	//结束整个程序
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	exit(0);	//结束整个程序
	//CDialogEx::OnClose();
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}
