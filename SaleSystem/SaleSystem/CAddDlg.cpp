// CAddDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "CAddDlg.h"
#include "InfoFile.h"


// CAddDlg

IMPLEMENT_DYNCREATE(CAddDlg, CFormView)

CAddDlg::CAddDlg()
	: CFormView(DIALOG_ADD)
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
	DDX_Text(pDX, IDC_EDIT3, m_num1);
	DDX_Text(pDX, IDC_EDIT6, m_name2);
	DDX_Text(pDX, IDC_EDIT5, m_price2);
	DDX_Text(pDX, IDC_EDIT4, m_num2);
}

BEGIN_MESSAGE_MAP(CAddDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAddDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAddDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAddDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CAddDlg::OnBnClickedButton5)
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

	// TODO: 在此添加专用代码和/或调用基类

	// 初始化 下拉框
	{
		CInfoFile file;
		file.ReadDocline();
		for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
		{
			// 遍历商品容器，将容器名称放置到下拉框中
			// string: it->name
			// CComboBox::AddString(CString)
			m_combo.AddString(CString(it->name.c_str()));
		}

		// 默认选中第一个商品
		m_combo.SetCurSel(0);
	}

	// 初始化 控件中 默认商品信息
	OnCbnSelchangeCombo1();
}


void CAddDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码

	// 切换商品触发事件

	// 获取商品名称
	int index = m_combo.GetCurSel();
	// 根据索引获取到具体内容
	CString name;
	m_combo.GetLBText(index, name);
	// 根据商品名称获取到该商品的价格和库存信息
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (CString(it->name.c_str()) == name)
		{
			m_price1 = it->price;
			// 同步到控件上
			UpdateData(FALSE);
			return;
		}
	}
	return;
}


void CAddDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	// 添加已有商品 功能实现
	UpdateData(TRUE);

	if (m_num1 <= 0)
	{
		MessageBox(TEXT("添加数量需要大于0"));
		return;
	}

	// 获取到要添加的商品名称
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (CString(it->name.c_str()) == name)
		{
			// 同步库存量
			it->num += m_num1;
			UpdateData(FALSE);
			MessageBox(TEXT("添加成功"));
			break;
		}
	}

	// 将最新的数据写入文件中
	file.WirteDocline();

	// 清空数据
	m_num1 = 0;
	UpdateData(FALSE);
}


void CAddDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	m_num1 = 0;
	UpdateData(FALSE);
	// 默认选中第一个商品
	m_combo.SetCurSel(0);
	// 初始化 控件中 默认商品信息
	OnCbnSelchangeCombo1();
}


void CAddDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	// 添加新商品
	UpdateData(TRUE);
	if (m_name2.IsEmpty() || m_num2 <= 0 || m_price2 <= 0)
	{
		MessageBox(TEXT("输入信息有误"));
		return;
	}

	// TODO: 若是添加已有商品情况下如何处理

	// 添加
	CInfoFile file;
	file.ReadDocline();
	file.Addline(m_name2, m_num2, m_price2);
	file.ReadDocline();
	MessageBox(TEXT("新商品添加成功"));

	// 同步到左侧已有商品列表中
	m_combo.InsertString(0, m_name2);
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();

	// 数据清空
	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);
}


void CAddDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

	// 取消添加新商品按钮事件
	m_name2.Empty();
	m_price2 = 0;
	m_num2 = 0;
	UpdateData(FALSE);
}
