// SellDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "SellDlg.h"
#include "CInfoFile.h"


// CSellDlg

IMPLEMENT_DYNCREATE(CSellDlg, CFormView)

CSellDlg::CSellDlg()
	: CFormView(DIALOG_SELL)
	, m_price(0)
	, m_store(0)
	, m_num(0)
	, m_sellInfo(_T(""))
{

}

CSellDlg::~CSellDlg()
{
}

void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT2, m_store);
	DDX_Text(pDX, IDC_EDIT4, m_num);
	DDX_Text(pDX, IDC_EDIT3, m_sellInfo);
}

BEGIN_MESSAGE_MAP(CSellDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSellDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CSellDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CSellDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CSellDlg 诊断

#ifdef _DEBUG
void CSellDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSellDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSellDlg 消息处理程序


void CSellDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//读取文件，获取商品名，给组合框添加字符串
	//需要包含#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		//string->CString
		m_combo.AddString((CString)it->name.c_str());
	}

	file.ls.clear(); //清空list的内容

	//将第一个商品名设为默认选中项
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CSellDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	//切换商品 触发的事件
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
			m_price = it->price;
			m_store = it->num;
			//同步到控件上
			UpdateData(FALSE);
		}
	}
}


void CSellDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// TODO:  在此添加控件通知处理程序代码
	//购买的功能实现
	if (m_num <= 0)
	{
		MessageBox(TEXT("购买数量要大于0"));
		return;
	}
	//购买的数量 不能大于库存
	if (m_num > m_store)
	{
		MessageBox(TEXT("购买数量不能大于库存量"));
		return;
	}

	//购买
	//获取到具体要买的商品名称
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if ((CString)it->name.c_str() == name)
		{
			//同步库存量
			it->num -= m_num;
			m_store = it->num; //控件上的库存量
			//告诉用户具体的购买信息

			CString str;
			str.Format(_T("商品：%s \r\n单价：%d \r\n个数：%d \r\n总价：%d"), name, m_price, m_num, m_price * m_num);
			m_sellInfo = str;
			UpdateData(FALSE);
			MessageBox(TEXT("购买成功"));
		}
	}

	//把最新的数据写到文件中
	file.WirteDocline();

	//清空数据
	m_num = 0;
	m_sellInfo.Empty();
	UpdateData(FALSE);
}


void CSellDlg::OnBnClickedButton3()
{
	//取消按钮
	m_num = 0;
	UpdateData(FALSE);
	//默认选中第一个
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();//更新第一个商品里的数据
}
