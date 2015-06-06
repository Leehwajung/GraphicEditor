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
	CText(CView *lpView);
	CText(IN Pen* pen, IN BrushPtr fillbrush);
	CText(IN CView *lpView, IN Pen* pen, IN BrushPtr fillbrush);
	CText(IN CView *lpView, IN Pen* pen, IN BrushPtr fillbrush, IN RectF layoutrect);
	CText(IN CView *lpView, IN Pen* pen, IN BrushPtr fillbrush, IN RectF layoutrect, IN Gdiplus::Font* font, IN StringFormat* stringformat, IN BrushPtr fontbrush);
	CText(IN CView *lpView, IN Pen* pen, IN BrushPtr fillbrush, IN RectF layoutrect, IN Gdiplus::Font* font, IN StringFormat* stringformat, IN BrushPtr fontbrush, IN CString string);
	CText(const CText& pCText);	//복사 생성자
	DECLARE_SERIAL(CText)
	virtual ~CText();	//소멸자
	virtual void Serialize(CArchive& ar);	// 직렬화
	virtual void increasewidth();
	virtual void decreasewidth();
	//cf. move는 rect꺼 그대로 씀. 
	// 재정의 해야할 부분//
	
	//BOOL create(IN PointF startingPoint, IN PointF endingPoint, IN CreateFlag createFlag/* = FREECREATE*/);

	virtual BOOL create(void* param1, ...);

	// OnDraw
	virtual void draw(IN Graphics* lpGraphics);//CpaintDC 사용


	// m_String에 문자 추가
	void addChar(TCHAR newchar);
	// [backspace] 키 입력 시 맨 마지막 글자를 삭제한다.
	void delChar();
	//
	CView* getView();
	CString getString();
	Gdiplus::Font* getFont();
	StringFormat* getStringFormat();
	BrushPtr getFontBrush();	//
	Color getFontColor();			// 주 글꼴 색 획득
	Color getFontSubcolor();		// 보조 글꼴 색 획득
	HatchStyle getFontPattern();	// 글꼴 패턴 획득

	void setView(CView* lpView);
	void setString(CString& string);
	void setFont(Gdiplus::Font* font);
	void setStringFormat(StringFormat* stringFormat);
	void setFontBrush(BrushPtr fontBrush);
	BOOL setFontColor(IN const Color& fontColor);			// 주 글꼴 색 설정 (TRUE: 설정 실패, FALSE: 설정 성공)
	BOOL setFontSubcolor(IN const Color& fontSubcolor);		// 보조 글꼴 색 설정 (TRUE: 설정 실패, FALSE: 설정 성공)
	BOOL setFontPattern(IN const HatchStyle fontPattern);	// 글꼴 패턴 설정 (TRUE: 설정 실패, FALSE: 설정 성공)

// 특성
private:
	CArray <TCHAR, TCHAR> m_String;	// 문자열
	Gdiplus::Font* m_Font;			// 문자열 정보 글자체
	StringFormat* m_StringFormat;	// 문자열 포맷 문자정렬 etc.
	BrushPtr m_FontBrush;			// 문자열 브러시 문자색상
	CView *m_View;					// 출력 대상 뷰 (캐럿 출력)
	BOOL character_mode = FALSE;	// caret
	SizeF rectSize;
	POINT cur;
};

//Status DrawString(
//	[in]       const WCHAR *string,
//	[in]       INT length,
//	[in]       const Font *font,
//	[in, ref]  const PointF &origin,
//	[in]       const Brush *brush
//	);

