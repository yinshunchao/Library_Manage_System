﻿// AddDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "AddDlg.h"
#include "afxdialogex.h"
#include "AddDlg.h"
#include "CInfoFile.h"

// CAddDlg

IMPLEMENT_DYNCREATE(CAddDlg, CFormView)

CAddDlg::CAddDlg()
	: CFormView(CAddDlg::IDD)
	, m_price1(0)
	, m_num1(0)
	, m_name2(_T(""))
	, m_price2(0)
	, m_num2(0)
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT2, m_price1);
	DDX_Text(pDX, IDC_EDIT4, m_num1);
	DDX_Text(pDX, IDC_EDIT5, m_name2);
	DDX_Text(pDX, IDC_EDIT6, m_price2);
	DDX_Text(pDX, IDC_EDIT7, m_num2);
}

BEGIN_MESSAGE_MAP(CAddDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddDlg::OnCbnSelchangeCombo1)

	//ON_BN_CLICKED(IDC_BUTTON6, &CAddDlg::OnBnClickedButton6)
	//ON_EN_CHANGE(IDC_EDIT6, &CAddDlg::OnEnChangeEdit6)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CAddDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAddDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CAddDlg 诊断

#ifdef _DEBUG
void CAddDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddDlg 消息处理程序


void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CInfoFile file;
	//把商品读到file对象中
	file.ReadDocline();

	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		//遍历商品容器  把容器名称放到下拉框中

		//it->name 是 string  AddString(CString )
		// string  -> CString

		m_combo.AddString(CString(it->name.c_str()));
	}

	//默认选中第一个商品
	m_combo.SetCurSel(0);

	OnCbnSelchangeCombo1();//更新第一个商品里的数据

	// TODO:  在此添加专用代码和/或调用基类
}


void CAddDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	//先获取到商品的名称

	int index = m_combo.GetCurSel();
	//根据索引获取到具体内容
	CString name;
	m_combo.GetLBText(index, name);

	//根据商品名称获取到该商品的价格和库存 并且显示到控件中
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if ((CString)it->name.c_str() == name)
		{
			m_price1 = it->price;
			//同步到控件上
			UpdateData(FALSE);
		}
	}

}



void CAddDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加商品的功能实现
	UpdateData(TRUE);
	if (m_num1 <= 0)
	{
		MessageBox(TEXT("添加的数量要大于0"));
		return;
	}
	//获取想要的添加商品的名称
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if((CString)it->name.c_str()==name)
		{
			//添加库存
			it->num += m_num1;
			m_num1 = 0;
			UpdateData(FALSE);
			MessageBox(TEXT("添加成功"));
		}
		file.WirteDocline();
	}

}


void CAddDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_num1 = 0;
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CAddDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加新商品
	//验证数据的有效性
	UpdateData(TRUE);
	if (m_name2.IsEmpty() || m_num2 <= 0 || m_price2 <= 0)
	{
		MessageBox(TEXT("输入商品信息错误"));
		return;
	}
	CInfoFile file;
	file.ReadDocline();
	file.Addline(m_name2, m_num2, m_price2);
	file.WirteDocline();
	MessageBox(TEXT("添加商品成功"));

	//同步到左侧下拉框中
	m_combo.InsertString(0, m_name2);
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();

	//清空添加的新数据
	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);

}
