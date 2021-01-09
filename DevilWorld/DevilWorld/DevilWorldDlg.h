
// DevilWorldDlg.h: 头文件
//

#pragma once
#include "MyRole.h"

#define GAME_WIDTH 778
#define GAME_HEIGHT 640

#define MAP_WIDTH 2500
#define MAP_HEIGHT 640

#define SNOW_NUM 100

#define WALL_NUM 3
#define WALL_WIDTH 160
#define WALL_HEIGHT 200

// 粒子系统（雪花）数据结构
typedef struct _SNOW
{
	int x;
	int y;
	int type;
	BOOL exist;
}SNOW;


// CDevilWorldDlg 对话框
class CDevilWorldDlg : public CDialogEx
{
// 构造
public:
	CDevilWorldDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEVILWORLD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHelpAbout();
	afx_msg void OnOperateBitmap();
	afx_msg void OnOperateTransparent1();
	afx_msg void OnOperateTransparent2();
	afx_msg void OnOperateTransparent3();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

public:
	void Init();

	void PaintBG(int x, int y); // 显示背景
	void PaintBG(HDC hDC, int x, int y); // 显示背景
	void PaintRole(int x, int y); // 显示角色

	void PaintRollingBG(HDC hDC, int iRolePosX, int iRolePosY);
	void PaintRollingRole(HDC hDC, int x, int y);

	void Update();
	void Paint();

	void PaintSnow(HDC hDC);
	void PainWall(HDC hDC);

	// 碰撞检测
	BOOL IsCollision(RECT rcRole, RECT rcWall);

	void KeyDown();

private:
	CMyRole m_myRole;

	// 雪花
	SNOW m_Snow[SNOW_NUM];
	// 墙
	RECT m_rcWall[3];

private:
	int m_nPosX;
	int m_nPosY;
public:
	afx_msg void OnOperateStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
