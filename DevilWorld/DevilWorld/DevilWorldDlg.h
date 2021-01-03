
// DevilWorldDlg.h: 头文件
//

#pragma once
#include "MyRole.h"

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
	void PaintRole(int x, int y); // 显示角色

	void Update();
	void Paint();

private:
	CMyRole m_myRole;
private:
	int m_nPosX;
	int m_nPosY;
public:
	afx_msg void OnOperateStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
