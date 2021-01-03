#pragma once

/**
 * 人物动态显示效果的角色类
 */

class CMyRole
{
public:
	CMyRole();
	~CMyRole();
public:
	void Init(UINT uiID, int iperFrameWidth, int iperFrameHeight, int iFrameNum, int iPosX = 0, int iPosY = 0);
	void Update();
	void Draw(HDC hDC, int x, int y);

	int GetPosX() { return m_iPosX; }
	int GetPosY() { return m_iPosY; }
	void SetSpeedX(int iSpeedX) { m_iSpeedX = iSpeedX; }
	void SetSpeedY(int iSpeedY) { m_iSpeedY = iSpeedY; }
	void SetDirection(int iDirection) { m_iDirection = iDirection; }




private:
	HBITMAP m_hBmp;
	int m_iPerFrameWidth, m_iPerFrameHeight;
	int m_iPosX, m_iPosY;
	int m_iSpeedX, m_iSpeedY;
	int m_iFrameNum;
	int m_iCurFrame;
	int m_iDirection;  // Up-0 Down-1 Left-2 Right-3
};

