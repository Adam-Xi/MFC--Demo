#include "pch.h"
#include "MyRole.h"

CMyRole::CMyRole()
{

}

CMyRole::~CMyRole()
{
}

void CMyRole::Init(UINT uiID, int iperFrameWidth, int iperFrameHeight, int iFrameNum, int iPosX /*= 0*/, int iPosY /*= 0*/)
{
	m_hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)uiID, IMAGE_BITMAP, 0, 0, NULL);
	m_iPerFrameWidth = iperFrameWidth;
	m_iPerFrameHeight = iperFrameHeight;
	m_iFrameNum = iFrameNum;
	m_iPosX = iPosX;
	m_iPosY = iPosY;
	m_iSpeedX = 0;
	m_iSpeedY = 0;
	m_iCurFrame = 0;
	m_iDirection = 1; // ���򣺴����¿�ʼ
}

void CMyRole::Update()
{
	m_iPosX += m_iSpeedX;
	m_iPosY += m_iSpeedY;
}

void CMyRole::Draw(HDC hDC, int x, int y)
{
	HDC hBufDC = ::CreateCompatibleDC(hDC);
	::SelectObject(hBufDC, m_hBmp);
	// ::BitBlt(hDC, x, y, m_iPerFrameWidth, m_iPerFrameHeight, hBufDC, \
		m_iDirection * m_iPerFrameWidth, m_iCurFrame * m_iPerFrameHeight, SRCAND);
	// ::BitBlt(hDC, x, y, m_iPerFrameWidth, m_iPerFrameHeight, hBufDC, \
		m_iDirection * m_iPerFrameWidth, m_iCurFrame * m_iPerFrameHeight, SRCPAINT);

	::BitBlt(hDC, x, y, 52, 62, hBufDC, 0, 0, SRCAND);
	::BitBlt(hDC, x, y, 52, 62, hBufDC, 0, 63, SRCPAINT);

	// m_iCurFrame = (m_iCurFrame + 1) % m_iFrameNum;

	::DeleteDC(hBufDC);
}
