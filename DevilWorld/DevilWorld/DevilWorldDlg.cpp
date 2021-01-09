
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
	::BitBlt(hDC, 0, 0, 778, 640, hMDC, 0, 0, SRCCOPY);
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
//		m_nPosY -= 10;
		m_myRole.SetSpeedY(-5);
		m_myRole.SetDirection(3);
	}
	else if ('S' == nChar)
	{
//		m_nPosY += 10;
		m_myRole.SetSpeedY(5);
		m_myRole.SetDirection(0);
	}
	else if ('A' == nChar)
	{
//		m_nPosX -= 10;
		m_myRole.SetSpeedX(-5);
		m_myRole.SetDirection(1);
	}
	else if ('D' == nChar)
	{
//		m_nPosX += 10;
		m_myRole.SetSpeedX(5);
		m_myRole.SetDirection(2);
	}

	// 绘制背景
//	PaintBG(0, 0);
	// 绘制角色
//	PaintRole(m_nPosX, m_nPosY);

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
	m_myRole.Init(IDB_BITMAP2, 25, 38, 4, 0, 300);

	for (int i = 0; i < SNOW_NUM; i++)
	{
		m_Snow[i].x = 0;
		m_Snow[i].y = 0;
		m_Snow[i].type = 0;
		m_Snow[i].exist = FALSE;
	}

	m_rcWall[0].left = 300;
	m_rcWall[0].top = 200;
	m_rcWall[0].right = m_rcWall[0].left + WALL_WIDTH;
	m_rcWall[0].bottom = m_rcWall[0].top + WALL_HEIGHT;

	m_rcWall[1].left = 2 * 300;
	m_rcWall[1].top = 200;
	m_rcWall[1].right = m_rcWall[1].left + WALL_WIDTH;
	m_rcWall[1].bottom = m_rcWall[1].top + WALL_HEIGHT;

	m_rcWall[2].left = 3 * 300;
	m_rcWall[2].top = 200;
	m_rcWall[2].right = m_rcWall[2].left + WALL_WIDTH;
	m_rcWall[2].bottom = m_rcWall[2].top + WALL_HEIGHT;
}

void CDevilWorldDlg::PaintBG(int x, int y)
{
	HDC hDC = ::GetDC(m_hWnd);
	HBITMAP hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP3, IMAGE_BITMAP, 0, 0, NULL);
	HDC hMDC = ::CreateCompatibleDC(hDC);
	::SelectObject(hMDC, hBmp);
	::BitBlt(hDC, x, y, GAME_WIDTH, GAME_HEIGHT, hMDC, 0, 0, SRCCOPY);
	::DeleteDC(hMDC);
	::ReleaseDC(m_hWnd, hDC);
}

void CDevilWorldDlg::PaintBG(HDC hDC, int x, int y)
{
	HBITMAP hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP3, IMAGE_BITMAP, 0, 0, NULL);
	HDC hMDC = ::CreateCompatibleDC(hDC);
	HBITMAP hTmpBmp = (HBITMAP)::SelectObject(hMDC, hBmp);
	::BitBlt(hDC, x, y, GAME_WIDTH, GAME_HEIGHT, hMDC, 0, 0, SRCCOPY);

	::SelectObject(hMDC, hTmpBmp);
	::DeleteDC(hMDC);
}

void CDevilWorldDlg::PaintRole(int x, int y)
{
	HDC hDC = ::GetDC(this->m_hWnd);
	HBITMAP hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP1, IMAGE_BITMAP, 0, 0, NULL);
	HDC hMDC = ::CreateCompatibleDC(hDC);
	HBITMAP hTmpBmp = (HBITMAP)::SelectObject(hMDC, hBmp);
	::BitBlt(hDC, x, y, 52, 62, hMDC, 0, 0, SRCAND);
	::BitBlt(hDC, x, y, 52, 62, hMDC, 0, 63, SRCPAINT);

	::SelectObject(hMDC, hTmpBmp);
	::DeleteObject(hBmp);
	::DeleteDC(hMDC);
	::ReleaseDC(this->m_hWnd, hDC);
}

void CDevilWorldDlg::PaintRollingBG(HDC hDC, int iRolePosX, int iRolePosY)
{
	int x = 0, y = 0;

	HDC hBufDC = ::CreateCompatibleDC(hDC);
	HBITMAP hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP4, IMAGE_BITMAP, 0, 0, NULL);
	HBITMAP hTmpBmp = (HBITMAP)::SelectObject(hBufDC, hBmp);

	// 在游戏地图中绘制墙
	PainWall(hBufDC);
	// 在游戏地图中绘制雪花
	PaintSnow(hBufDC);

	// 判断位置
	if ((GAME_WIDTH / 2) > iRolePosX)
	{
		x = y = 0;
	}
	else if ((GAME_WIDTH / 2) <= iRolePosX && iRolePosX < (MAP_WIDTH - GAME_WIDTH / 2))
	{
		x = iRolePosX - (GAME_WIDTH / 2);
		y = 0;
	}
	else if ((MAP_WIDTH - GAME_WIDTH / 2) <= iRolePosX)
	{
		x = MAP_WIDTH - GAME_WIDTH;
		y = 0;
	}

	// 显示
	::BitBlt(hDC, 0, 0, GAME_WIDTH, GAME_HEIGHT, hBufDC, x, y, SRCCOPY);

	::SelectObject(hBufDC, hTmpBmp);
	::DeleteObject(hBmp);
	::DeleteDC(hBufDC);
}

void CDevilWorldDlg::PaintRollingRole(HDC hDC, int iRolePosX, int iRolePosY)
{
	int x = 0, y = 0;

	if ((GAME_WIDTH / 2) > iRolePosX)
	{
		x = iRolePosX;
		y = iRolePosY;
	}
	else if ((GAME_WIDTH / 2) <= iRolePosX && iRolePosX < (MAP_WIDTH - GAME_WIDTH / 2))
	{
		x = GAME_WIDTH / 2;
		y = iRolePosY;
	}
	else if ((MAP_WIDTH - GAME_WIDTH / 2) <= iRolePosX)
	{
		x = iRolePosX - (MAP_WIDTH - GAME_WIDTH);
		y = iRolePosY;
	}

	m_myRole.Draw(hDC, x, y);
}

void CDevilWorldDlg::Update()
{
	// 预判断 是否碰撞
	BOOL bCollision = FALSE;
	int nX = m_myRole.GetPosX() + m_myRole.GetSpeedX();
	int nY = m_myRole.GetPosY() + m_myRole.GetSpeedY();
	RECT rcRole = { nX, nY, nX + m_myRole.GetFrameWidth(), nY + m_myRole.GetFrameHeight() };
	for (int i = 0; i < WALL_NUM; i++)
	{
		if (IsCollision(rcRole, m_rcWall[i]))
		{
			bCollision = TRUE;
			break;
		}
	}

	if (FALSE == bCollision)
	{
		m_myRole.Update();
	}

	// 更新雪花数据
	srand(time(NULL));
	for (int i = 0; i < SNOW_NUM; i++)
	{
		if (FALSE == m_Snow[i].exist)
		{
			// 随机存在 2%
			if (2 > (rand() % 100))
			{
				m_Snow[i].exist = TRUE;
				m_Snow[i].x = rand() % MAP_WIDTH;
				m_Snow[i].y = 0;
				m_Snow[i].type = rand() % 2;
			}
		}
		else
		{
			m_Snow[i].y += (3 + rand() % 2);  // 随机下落3-4像素
			m_Snow[i].y += (-2 + rand() % 4);  // 随机飘动左右2像素

			// 判断雪花是否落出屏幕
			if (m_Snow[i].y > GAME_HEIGHT)
			{
				m_Snow[i].exist = FALSE;
			}
		}
	}
}

void CDevilWorldDlg::Paint()
{
#if 0
	HDC hDC = ::GetDC(this->m_hWnd);
	// 绘制背景
	PaintBG(0, 0);
	// 绘制人物
	m_myRole.Draw(hDC, m_myRole.GetPosX(), m_myRole.GetPosY());

	::ReleaseDC(this->m_hWnd, hDC);
#else
	// 双缓冲绘制技术：
	//     将背景和人物先绘制在内存中，然后一次性拷贝到屏幕上，这样避免人物和画面的闪动及不一致情况

	// 为屏幕 DC 创建兼容的内存 DC ，使用函数 CreateCompatibleDC()
	HDC hDC = ::GetDC(this->m_hWnd);
	HDC hMDC = ::CreateCompatibleDC(hDC);
	// 创建内存位图：CreateCompatibleBitmap()
	HBITMAP hBmp = ::CreateCompatibleBitmap(hDC, GAME_WIDTH, GAME_HEIGHT);
	// 把内存位图选入设备环境中：SelectObject()
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMDC, hBmp);

	// 绘制背景
	// PaintBG(hMDC, 0, 0);
	PaintRollingBG(hMDC, m_myRole.GetPosX(), m_myRole.GetPosY());
	// 绘制人物
	// m_myRole.Draw(hMDC, m_myRole.GetPosX(), m_myRole.GetPosY());
	PaintRollingRole(hMDC, m_myRole.GetPosX(), m_myRole.GetPosY());

	// 把绘制好的图形 拷贝 到屏幕上：BitBlt()
	::BitBlt(hDC, 0, 0, GAME_WIDTH, GAME_HEIGHT, hMDC, 0, 0, SRCCOPY);
#endif
}

void CDevilWorldDlg::PaintSnow(HDC hDC)
{
	HDC hBufDC = ::CreateCompatibleDC(hDC);
	HBITMAP hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP5, IMAGE_BITMAP, 0, 0, NULL);
	HBITMAP hTmpBmp = (HBITMAP)::SelectObject(hBufDC, hBmp);

	for (int i = 0; i < SNOW_NUM; i++)
	{
		if (m_Snow[i].exist)
		{
			// 绘制
			::TransparentBlt(hDC, m_Snow[i].x, m_Snow[i].y, 32, 32, hBufDC, m_Snow[i].type * 128, m_Snow[i].type * 128, 128, 128, RGB(255, 255, 255));
		}
	}

	::SelectObject(hBufDC, hTmpBmp);
	::DeleteObject(hBmp);
	::DeleteDC(hBufDC);
}

void CDevilWorldDlg::PainWall(HDC hDC)
{
	HDC hBufDC = ::CreateCompatibleDC(hDC);
	HBITMAP hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP6, IMAGE_BITMAP, 0, 0, NULL);
	HBITMAP hTmpBmp = (HBITMAP)::SelectObject(hBufDC, hBmp);

	// 绘制
	//::BitBlt()
	for (int i = 0; i < WALL_NUM; i++)
	{
		::TransparentBlt(hDC, m_rcWall[i].left, m_rcWall[i].top, WALL_WIDTH, WALL_HEIGHT, hBufDC, 0, 0, WALL_WIDTH, WALL_HEIGHT, RGB(255, 255, 255));
	}

	::SelectObject(hBufDC, hTmpBmp);
	::DeleteObject(hBmp);
	::DeleteDC(hBufDC);
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
	::SetTimer(this->m_hWnd, 10, 50, NULL);
	
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

BOOL CDevilWorldDlg::IsCollision(RECT rcRole, RECT rcWall)
{
	POINT ptLeftTop = { 0 };
	ptLeftTop.x = rcRole.left;
	ptLeftTop.y = rcRole.top;
	POINT ptLeftBottom = { 0 };
	ptLeftBottom.x = rcRole.left;
	ptLeftBottom.y = rcRole.bottom;
	POINT ptRightTop = { 0 };
	ptRightTop.x = rcRole.right;
	ptRightTop.y = rcRole.top;

	POINT ptRightBottom = { 0 };
	ptRightBottom.x = rcRole.right;
	ptRightBottom.y = rcRole.bottom;

	if (::PtInRect(&rcWall, ptLeftTop)
		&& ::PtInRect(&rcWall, ptLeftBottom)
		&& ::PtInRect(&rcWall, ptRightTop)
		&& ::PtInRect(&rcWall, ptRightBottom))
	{
		return TRUE;
	}
	return FALSE;
}