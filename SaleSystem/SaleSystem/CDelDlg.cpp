// CDelDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "CDelDlg.h"
#include "InfoFile.h"


// CDelDlg

IMPLEMENT_DYNCREATE(CDelDlg, CFormView)

CDelDlg::CDelDlg()
	: CFormView(DIALOG_DELETE)
	, m_price(0)
	, m_left(0)
	, m_num(0)
{

}

CDelDlg::~CDelDlg()
{
}

void CDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT2, m_price);
	DDX_Text(pDX, IDC_EDIT4, m_left);
	DDX_Text(pDX, IDC_EDIT3, m_num);
}

BEGIN_MESSAGE_MAP(CDelDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDelDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDelDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDelDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDelDlg 诊断

#ifdef _DEBUG
void CDelDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDelDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDelDlg 消息处理程序


void CDelDlg::OnInitialUpdate()
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


void CDelDlg::OnCbnSelchangeCombo1()
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


void CDelDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	// 删除商品按钮事件

	UpdateData(TRUE);

	if (m_num <= 0 || m_num > m_left)
	{
		MessageBox(TEXT("商品删除数目不正确"));
		return;
	}

	// 获取要删除的商品信息
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (CString(it->name.c_str()) == name)
		{
			it->num -= m_num;
			CString str;
			str.Format(_T("删除商品：%s\r\n个数：%d"), name, m_num);
			MessageBox(str);

			m_num = 0;
			UpdateData(FALSE);
			file.WirteDocline();
			break;
		}
	}

	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
	return;
}


void CDelDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	m_num = 0;
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}
