// Text.h : CText Ŭ������ �������̽�
// CText : ���ڿ� ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "Rectangle.h"
#include <afxtempl.h>	//CArray Ŭ���� �̿�

# define RESIZE_POINT 5 // ũ�⺯��� �⺻����

// CText ��� ����Դϴ�.

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
	CText(const CText& pCText);	//���� ������
	DECLARE_SERIAL(CText)
	virtual ~CText();	//�Ҹ���
	virtual void Serialize(CArchive& ar);	// ����ȭ
	virtual void increasewidth();
	virtual void decreasewidth();
	//cf. move�� rect�� �״�� ��. 
	// ������ �ؾ��� �κ�//
	
	//BOOL create(IN PointF startingPoint, IN PointF endingPoint, IN CreateFlag createFlag/* = FREECREATE*/);

	virtual BOOL create(void* param1, ...);

	// OnDraw
	virtual void draw(IN Graphics& graphics);//CpaintDC ���

	virtual void move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);

	// m_String�� ���� �߰�
	void addChar(TCHAR newchar);
	// [backspace] Ű �Է� �� �� ������ ���ڸ� �����Ѵ�.
	void delChar();
	//
	CView* getView();
	CString getString();
	Gdiplus::Font* getFont();
	StringFormat* getStringFormat();
	BrushPtr getFontBrush();	//
	Color getFontColor();			// �� �۲� �� ȹ��
	Color getFontSubcolor();		// ���� �۲� �� ȹ��
	HatchStyle getFontPattern();	// �۲� ���� ȹ��

	void setView(CView* lpView);
	void setString(CString& string);
	void setFont(Gdiplus::Font* font);
	void setStringFormat(StringFormat* stringFormat);
	void setFontBrush(BrushPtr fontBrush);
	BOOL setFontColor(IN const Color& fontColor);			// �� �۲� �� ���� (TRUE: ���� ����, FALSE: ���� ����)
	BOOL setFontSubcolor(IN const Color& fontSubcolor);		// ���� �۲� �� ���� (TRUE: ���� ����, FALSE: ���� ����)
	BOOL setFontPattern(IN const HatchStyle fontPattern);	// �۲� ���� ���� (TRUE: ���� ����, FALSE: ���� ����)

// Ư��
private:
	CArray <TCHAR, TCHAR> m_String;	// ���ڿ�
	Gdiplus::Font* m_Font;			// ���ڿ� ���� ����ü
	StringFormat* m_StringFormat;	// ���ڿ� ���� �������� etc.
	BrushPtr m_FontBrush;			// ���ڿ� �귯�� ���ڻ���
	CView *m_View;					// ��� ��� �� (ĳ�� ���)
	BOOL character_mode = FALSE;	// caret
	SizeF rectSize;
	POINT cur;
	PointF st_p;
	int count=0;
};

//Status DrawString(
//	[in]       const WCHAR *string,
//	[in]       INT length,
//	[in]       const Font *font,
//	[in, ref]  const PointF &origin,
//	[in]       const Brush *brush
//	);

