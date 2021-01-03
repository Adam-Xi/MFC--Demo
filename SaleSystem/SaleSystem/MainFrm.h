﻿
// MainFrm.h: CMainFrame 类的接口
//

#pragma once

// 自定义消息
#define NM_A  (WM_USER + 100)
#define NM_B  (WM_USER + 101)
#define NM_C  (WM_USER + 102)
#define NM_D  (WM_USER + 103)
#define NM_E  (WM_USER + 104)

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

private:
	CSplitterWnd m_spliter; /// 拆分窗口对象

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnExit();
	afx_msg void OnSelfInfo();
	afx_msg void OnSellManagement();
	afx_msg void OnLeftInfo();
	afx_msg void OnLeftAdd();
	afx_msg void OnLeftDelete();
};


