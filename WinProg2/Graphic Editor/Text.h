// Text.h : CText 클래스의 인터페이스
// CText : 문자열 개체를 정의하는 클래스
// 

#pragma once
#include "Rectangle.h"
#include <afxtempl.h>	//CArray 클래스 이용

# define RESIZE_POINT 5 // 크기변경시 기본단위

// CText 명령 대상입니다.

class CText : public CRectangle
{
public:
	CText();
	CText(IN CClientDC* lpClientDC);
	//CText(IN Graphics* lpGraphics);
	//CText(IN CClientDC* lpClientDC, IN Pen* pen, IN Brush* fillbrush);
	//CText(IN Graphics* lpGraphics, IN Pen* pen, IN Brush* fillbrush);
	//CText(IN CClientDC* lpClientDC, IN Pen* pen, IN Brush* fillbrush, IN RectF layoutrect);
	//CText(IN Graphics* lpGraphics, IN Pen* pen, IN Brush* fillbrush, IN RectF layoutrect);
	CText(CView *lpView);
	CText(IN CView *lpView, IN Pen* pen, IN Brush* fillbrush);
	CText(IN CView *lpView, IN Pen* pen, IN Brush* fillbrush, IN RectF layoutrect);
	CText(IN CView *lpView, IN Pen* pen, IN Brush* fillbrush, IN RectF layoutrect, IN Gdiplus::Font* font, IN StringFormat* stringformat, IN Brush* fontbrush);
	CText(IN CView *lpView, IN Pen* pen, IN Brush* fillbrush, IN RectF layoutrect, IN Gdiplus::Font* font, IN StringFormat* stringformat, IN Brush* fontbrush, IN CString string);
	CText(const CText& pCText);	//복사 생성자
	DECLARE_SERIAL(CText)
	virtual ~CText();	//소멸자

	virtual void Serialize(CArchive& ar);	// 직렬화


	// OnDraw
	virtual void draw(/*CDC * m_lpDC*/);//CpaintDC 사용


	virtual void FontDisplay();
	virtual void FontTransform();// 폰트변형
	virtual void SizeTransform();// 사이즈변경
	virtual void FontDestroy();// 제거

	// LButtonDown
	//virtual void create(PointF startingPoint);					// 개체 리전생성
	
	// OnMouseMove
	//void mouseMoveOperation(UINT nFlags, PointF point);			// OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단)
	virtual void creating(...);										// 생성 그리기
	virtual void moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);	// 이동 그리기
	virtual void resizing(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);	// 크기 변경 그리기

	// LButtonUp / LButtonDlk
	virtual void endCreate(PointF point);							// 생성 완료
	//virtual void move(PointF originPoint, PointF targetPoint);	// 개체 이동
	//virtual void resize(PointF point, int resizeFlags);			// 개체 크기 변경


	//Keyboard Focus
	virtual void OnKeyboardFocus(PointF point);	//
	
	//void getview(CView* view);
	//static void getview(cview* view) {		// 캐럿 테스트 (테스트를 위해 static으로 선언)
	//	view->createsolidcaret(10, 20);
	//	view->setcaretpos(cpoint(50, 50));
	//	view->showcaret();
	//}

	void addChar(TCHAR newchar);	// m_String에 문자 추가

	CView* getView();
	CString getString();
	Gdiplus::Font* getFont();
	StringFormat* getStringFormat();
	Brush* getFontBrush();
	Color getFontColor();			// 주 글꼴 색 획득
	Color getFontSubcolor();		// 보조 글꼴 색 획득
	HatchStyle getFontPattern();	// 글꼴 패턴 획득

	void setView(CView* lpView);
	void setString(CString& string);
	void setFont(Gdiplus::Font* font);
	void setStringFormat(StringFormat* stringFormat);
	void setFontBrush(Brush* fontBrush);
	BOOL setFontColor(IN const Color& fontColor);			// 주 글꼴 색 설정 (TRUE: 설정 실패, FALSE: 설정 성공)
	BOOL setFontSubcolor(IN const Color& fontSubcolor);		// 보조 글꼴 색 설정 (TRUE: 설정 실패, FALSE: 설정 성공)
	BOOL setFontPattern(IN const HatchStyle fontPattern);	// 글꼴 패턴 설정 (TRUE: 설정 실패, FALSE: 설정 성공)

// 특성
private:
	CArray <TCHAR, TCHAR> m_String;	// 문자열
	Gdiplus::Font* m_Font;			// 문자열 정보
	StringFormat* m_StringFormat;	// 문자열 포맷
	Brush* m_FontBrush;				// 문자열 브러시
	CView *m_View;					// 출력 대상 뷰 (캐럿 출력)

	//Color m_FontColor;	// 글자색
	//LOGFONT m_FontLog;	// 폰트에 대한 정보들 (글꼴, 크기, 굵게, 이탤릭, 밑줄, 취소선 등)

	//	PointF points;
	// 글꼴
	//CArray <TCHAR, TCHAR> m_str;
	//CFont m_Font;			//폰트 ()
	//int m_FontName;	// 사용자가 선택한 폰트번호저장
	//int m_FontSize;	// 사용자가 입력한 폰트 사이즈
	//Color m_bkColor;	//배경색 http://shaeod.tistory.com/382
	//BOOL m_FontBold;	// 볼드체
	//BOOL m_FontItalic; // 이탤릭체
	//BOOL m_FontUnderline;// 밑줄
	BOOL character_mode = FALSE;
protected :
	enum { NONE, HORZ, VERT, DIAG  }m_RESIZE;// 크기변경인자
	//

	//HWND hWnd = ::GetActiveWindow();//핸들러
	//HDC* hdc = ::GetDC(hWnd);
	//CDC *tDC = CDC::FromHandle(hdc);
	//HWND hWnd = ::GetActiveWindow();//핸들러

};

