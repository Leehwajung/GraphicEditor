// Text.h : CText 클래스의 인터페이스
// CText : 문자열 개체를 정의하는 클래스
// 

#pragma once
#include "Shape.h"

//using Gdiplus::Color;

class CText : public CShape 
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
	virtual void create(CPoint startingPoint);					// 개체 리전생성
	

	// OnMouseMove
	void mouseMoveOperation(UINT nFlags, CPoint point);			// OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단)
	virtual void creating(UINT nFlags, CPoint point);			// 생성 그리기
	virtual void moving(UINT nFlags, CPoint point);				// 이동 그리기
	virtual void resizing(UINT nFlags, CPoint point);			// 크기 변경 그리기

	// LButtonUp / LButtonDlk
	//virtual void addPoint(CPoint point);						// 점 추가
	virtual void move(CPoint target);							// 개체 이동
	virtual void resize(CPoint point, int resizeFlags);			// 개체 크기 변경

	// OnDraw / OnPaint
	virtual void draw(CDC * m_lpDC);//CpaintDC 사용

	//Keyboard Focus
	virtual void OnKeyboardFocus(CPoint point);//

// 특성
private:
	CString m_String;	//입력받을 문자열

	Color m_FontColor;	// 글자색
	LOGFONT m_FontLog;	// 폰트에 대한 정보들 (글꼴, 크기, 굵게, 이탤릭, 밑줄, 취소선 등)

	//	CPoint points;
	// 글꼴
	//CArray <TCHAR, TCHAR> m_str;
	//CFont m_Font;			//폰트 ()
	//int m_FontName;	// 사용자가 선택한 폰트번호저장
	//int m_FontSize;	// 사용자가 입력한 폰트 사이즈
	//Color m_bkColor;	//배경색 http://shaeod.tistory.com/382
	//BOOL m_FontBold;	// 볼드체
	//BOOL m_FontItalic; // 이탤릭체
	//BOOL m_FontUnderline;// 밑줄
};

