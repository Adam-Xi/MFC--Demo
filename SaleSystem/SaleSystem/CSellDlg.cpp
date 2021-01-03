// CSellDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "CSellDlg.h"

#include "InfoFile.h"


// CSellDlg

IMPLEMENT_DYNCREATE(CSellDlg, CFormView)

CSellDlg::CSellDlg()
	: CFormView(DIALOG_SELL)
	, m_price(0)
	, m_left(0)
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
	DDX_Text(pDX, IDC_EDIT2, m_price);
	DDX_Text(pDX, IDC_EDIT4, m_left);
	DDX_Text(pDX, IDC_EDIT3, m_num);
	DDX_Text(pDX, IDC_EDIT5, m_sellInfo);
}

BEGIN_MESSAGE_MAP(CSellDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSellDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CSellDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSellDlg::OnBnClickedButton2)
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
	
	// 初始化 销售订单 窗口

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


void CSellDlg::OnCbnSelchangeCombo1()
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
			m_price = it->price;
			m_left = it->num;
			// 同步到控件上
			UpdateData(FALSE);
			return;
		}
	}
	return;
}


void CSellDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	// 购买 功能实现
	UpdateData(TRUE);

	if (m_num <= 0)
	{
		MessageBox(TEXT("购买数量需要大于0"));
		return;
	}
	if (m_num > m_left)
	{
		MessageBox(TEXT("购买数量不能大于库存量"));
		return;
	}

	// 获取到要买的商品名称
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
			it->num -= m_num;
			m_left = it->num;

			// 告诉用户具体购买信息
			CString str;
			str.Format(_T("商品：%s \r\n单价：%d \r\n个数：%d \r\n总价：%d"), name, m_price, m_num, m_num * m_price);
			m_sellInfo = str;
			UpdateData(FALSE);
			MessageBox(TEXT("购买成功"));
			break;
		}
	}

	// 将最新的数据写入文件中
	file.WirteDocline();

	// 清空数据
	m_num = 0;
	m_sellInfo.Empty();
	UpdateData(FALSE);

	return;
}


void CSellDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	// 取消按钮
	m_num = 0;
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}
