
// DevilWorldDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DevilWorld.h"
#include "DevilWorldDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDevilWorldDlg 对话框



CDevilWorldDlg::CDevilWorldDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEVILWORLD_DIALOG, pParent)
	, m_nPosX(0)
	, m_nPosY(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDevilWorldDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDevilWorldDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_HELP_ABOUT, &CDevilWorldDlg::OnHelpAbout)
	ON_COMMAND(ID_OPERATE_BITMAP, &CDevilWorldDlg::OnOperateBitmap)
	ON_COMMAND(ID_OPERATE_TRANSPARENT1, &CDevilWorldDlg::OnOperateTransparent1)
	ON_COMMAND(ID_OPERATE_TRANSPARENT2, &CDevilWorldDlg::OnOperateTransparent2)
	ON_COMMAND(ID_OPERATE_TRANSPARENT3, &CDevilWorldDlg::OnOperateTransparent3)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_OPERATE_START, &CDevilWorldDlg::OnOperateStart)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDevilWorldDlg 消息处理程序

BOOL CDevilWorldDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDevilWorldDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDevilWorldDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDevilWorldDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDevilWorldDlg::OnHelpAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CDevilWorldDlg::OnOperateBitmap()
{
	// TODO: 在此添加命令处理程序代码

	// 获取主窗口的内部窗口区域（获取DC）
	HDC hDC = ::GetDC(this->m_hWnd);
	// 获取位图并调用LoadImage装在图标、光标或位图
	HBITMAP hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP3, IMAGE_BITMAP, 0, 0, NULL);
	// 定义并创建一个内存设备环境DC，调用 CreateCompatibleDC 创建兼容的DC
	HDC hMDC = ::CreateCompatibleDC(hDC);
	// 调用 SelectObject 将位图选入兼容内存设备环境DC中
	::SelectObject(hMDC, hBmp);
	// 将兼容的DC中的位图填到当前DC中，调用函数显示图像
	::BitBlt(hDC, 0, 0, 612, 342, hMDC, 0, 0, SRCCOPY);
	// 回复临时DC的位图，删除内存中的位图，删除兼容的DC，释放系统资源
	::DeleteDC(hMDC);
	::ReleaseDC(this->m_hWnd, hDC);
}

void CDevilWorldDlg::OnOperateTransparent1()
{
	// TODO: 在此添加命令处理程序代码
	
	{
		HDC hDC = ::GetDC(this->m_hWnd);

		HBITMAP hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP1, IMAGE_BITMAP, 0, 0, NULL);

		HDC hMDC = ::CreateCompatibleDC(hDC);

		::SelectObject(hMDC, hBmp);

		//   ::BitBlt(hDC, 0, 0, 400, 200, hMDC, 0, 0, SRCCOPY);
		::TransparentBlt(hDC, 0, 0, 47, 57, hMDC, 0, 0, 47, 57, RGB(34, 177, 76)); // 指定过滤颜色对背景进行过滤

		::DeleteDC(hMDC);
		::ReleaseDC(this->m_hWnd, hDC);
	}
}


void CDevilWorldDlg::OnOperateTransparent2()
{
	// TODO: 在此添加命令处理程序代码

	{
		HDC hDC = ::GetDC(this->m_hWnd);

		HBITMAP hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP2, IMAGE_BITMAP, 0, 0, NULL);

		HDC hMDC = ::CreateCompatibleDC(hDC);

		::SelectObject(hMDC, hBmp);

		// ::TransparentBlt(hDC, 0, 0, 47, 57, hMDC, 0, 0, 47, 57, RGB(34, 177, 76));
		::BitBlt(hDC, 0, 0, 52, 62, hMDC, 0, 0, SRCAND); // 与操作
		::BitBlt(hDC, 0, 0, 52, 62, hMDC, 0, 63, SRCPAINT); // 或操作

		::DeleteDC(hMDC);
		::ReleaseDC(this->m_hWnd, hDC);
	}
}


void CDevilWorldDlg::OnOperateTransparent3()
{
	// TODO: 在此添加命令处理程序代码

	{
		HDC hDC = ::GetDC(this->m_hWnd);

		HBITMAP hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP2, IMAGE_BITMAP, 0, 0, NULL);

		HDC hMDC = ::CreateCompatibleDC(hDC);

		::SelectObject(hMDC, hBmp);

		// ::BitBlt(hDC, 0, 0, 52, 62, hMDC, 0, 0, SRCAND); // 与操作
		// ::BitBlt(hDC, 0, 0, 52, 62, hMDC, 0, 62, SRCPAINT); // 或操作
		// StretchBlt 相比较 BitBlt 函数来说可以对指定区域进行拉伸和压缩
		::StretchBlt(hDC, 0, 0, 52, 62, hMDC, 0, 0, 52, 62, SRCAND); // 与
		::StretchBlt(hDC, 0, 0, 52, 62, hMDC, 0, 63, 52, 62, SRCPAINT); // 或

		::DeleteDC(hMDC);
		::ReleaseDC(this->m_hWnd, hDC);
	}
}


void CDevilWorldDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_myRole.SetSpeedX(0);
	m_myRole.SetSpeedY(0);

	if ('W' == nChar)
	{
		m_nPosY -= 10;
		// m_myRole.SetSpeedY(-5);
		// m_myRole.SetDirection(0);
	}
	else if ('S' == nChar)
	{
		m_nPosY += 10;
		// m_myRole.SetSpeedY(5);
		// m_myRole.SetDirection(1);
	}
	else if ('A' == nChar)
	{
		m_nPosX -= 10;
		// m_myRole.SetSpeedX(-5);
		// m_myRole.SetDirection(2);
	}
	else if ('D' == nChar)
	{
		m_nPosX += 10;
		// m_myRole.SetSpeedX(5);
		// m_myRole.SetDirection(3);
	}

	// 绘制背景
	PaintBG(0, 0);
	// 绘制角色
	PaintRole(m_nPosX, m_nPosY);

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CDevilWorldDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_nPosX = point.x;
	m_nPosY = point.y;

	// 绘制背景
	PaintBG(0, 0);
	// 绘制角色
	PaintRole(point.x, point.y);

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CDevilWorldDlg::Init()
{
	m_myRole.Init(IDB_BITMAP2, 52, 62, 3, 0, 0);
}

void CDevilWorldDlg::PaintBG(int x, int y)
{
	HDC hDC = ::GetDC(m_hWnd);
	HBITMAP hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP3, IMAGE_BITMAP, 0, 0, NULL);
	HDC hMDC = ::CreateCompatibleDC(hDC);
	::SelectObject(hMDC, hBmp);
	::BitBlt(hDC, x, y, 1024, 685, hMDC, 0, 0, SRCCOPY);
	::DeleteDC(hMDC);
	::ReleaseDC(m_hWnd, hDC);
}

void CDevilWorldDlg::PaintRole(int x, int y)
{
	HDC hDC = ::GetDC(this->m_hWnd);
	HBITMAP hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP2, IMAGE_BITMAP, 0, 0, NULL);
	HDC hMDC = ::CreateCompatibleDC(hDC);
	::SelectObject(hMDC, hBmp);
	::BitBlt(hDC, x, y, 52, 62, hMDC, 0, 0, SRCAND);
	::BitBlt(hDC, x, y, 52, 62, hMDC, 0, 63, SRCPAINT);
	::DeleteDC(hMDC);
	::ReleaseDC(this->m_hWnd, hDC);
}

void CDevilWorldDlg::Update()
{
	m_myRole.Update();
}

void CDevilWorldDlg::Paint()
{
	HDC hDC = ::GetDC(this->m_hWnd);
	// 绘制背景
	PaintBG(0, 0);
	// 绘制人物
	m_myRole.Draw(hDC, m_myRole.GetPosX(), m_myRole.GetPosY());

	::ReleaseDC(this->m_hWnd, hDC);
}

VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, DWORD dwTimer)
{
	::MessageBox(NULL, "不关联窗口定时器方法", "我的标题", MB_OK);
}

void CDevilWorldDlg::OnOperateStart()
{
	// TODO: 在此添加命令处理程序代码

	// 定时器设置
#if 0
	// 不关联窗口方法
	// UINT_PTR iTimer = ::SetTimer(NULL, 0, 5000, (TIMERPROC)TimerProc);
	// ::KillTimer(NULL, iTimer);
#else
	// 关联窗口方法
	// ::SetTimer(this->m_hWnd, 1, 3000, NULL); // 要响应 WM_TIMER 消息
	// ::KillTimer(this->m_hWnd, 1);
#endif

	Init();
	// ::SetTimer(this->m_hWnd, 10, 50, NULL);
	
}


void CDevilWorldDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch (nIDEvent)
	{
	case 1:
		::MessageBox(NULL, "关联窗口定时器方法", "我的标题", MB_OK);
		break;
	case 10:
		Update();
		Paint();
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}
