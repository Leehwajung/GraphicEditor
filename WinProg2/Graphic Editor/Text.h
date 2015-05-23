#pragma once
#include "Figure.h"
#include <gdiplus.h>

class CText : public CFigure 
{
public:
	CText();
	~CText();//소멸자
	CText(const CText& pCText);	//복사 생성자

	//
	virtual void FontDisplay();
	virtual void FontTransform();// 폰트변형
	virtual void SizeTransform();// 사이즈변경
	virtual void FontDestroy();// 제거

	// LButtonDown
	virtual void create(CPoint startingPoint);					// 개체 생성
	virtual operationModeFlags cursorPosition(CPoint point);	// 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지)

	// OnMouseMove
	void mouseMoveOperation(UINT nFlags, CPoint point);			// OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단)
	virtual void creating(UINT nFlags, CPoint point);			// 생성 그리기
	virtual void moving(UINT nFlags, CPoint point);				// 이동 그리기
	virtual void resizing(UINT nFlags, CPoint point);			// 크기 변경 그리기

	// LButtonUp / LButtonDlk
	virtual void addPoint(CPoint point);						// 점 추가
	virtual void move(CPoint target);							// 개체 이동
	virtual void resize(CPoint point, int resizeFlags);			// 개체 크기 변경

	// OnDraw / OnPaint
	virtual void draw();//CpaintDC 사용

	//Keyboard Focus
	virtual void OnKeyboardFocus();// 캐럿표시, WM_SETFOCUS 와 WM_KILLFOCUS메시지 핸들러추가

private://	CPoint points;
	// 글꼴
	//CArray <TCHAR, TCHAR> m_str;
	CString m_str;//문자열
	CFont Font; //폰트
	int m_FontName; // 사용자가 선택한 폰트번호저장
	int m_FontSize; // 사용자가 입력한 폰트 사이즈
	COLORREF m_bkColor; //배경색 http://shaeod.tistory.com/382
	COLORREF m_FontColor; //글자색
	LOGFONT m_LogFont; //폰트에 대한 정보들(글꼴, 색상)
	BOOL m_FontBold;// 볼드체
	BOOL m_FontItalic; // 이탤릭체
	BOOL m_FontUnderline;// 밑줄
};

