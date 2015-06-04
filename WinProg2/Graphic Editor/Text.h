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
	CText(IN CClientDC* lpClientDC);
	//CText(IN Graphics* lpGraphics);
	//CText(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr fillbrush);
	//CText(IN Graphics* lpGraphics, IN Pen* pen, IN BrushPtr fillbrush);
	//CText(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr fillbrush, IN RectF layoutrect);
	//CText(IN Graphics* lpGraphics, IN Pen* pen, IN BrushPtr fillbrush, IN RectF layoutrect);
	CText(CView *lpView);
	CText(IN CView *lpView, IN Pen* pen, IN BrushPtr fillbrush);
	CText(IN CView *lpView, IN Pen* pen, IN BrushPtr fillbrush, IN RectF layoutrect);
	CText(IN CView *lpView, IN Pen* pen, IN BrushPtr fillbrush, IN RectF layoutrect, IN Gdiplus::Font* font, IN StringFormat* stringformat, IN BrushPtr fontbrush);
	CText(IN CView *lpView, IN Pen* pen, IN BrushPtr fillbrush, IN RectF layoutrect, IN Gdiplus::Font* font, IN StringFormat* stringformat, IN BrushPtr fontbrush, IN CString string);
	CText(const CText& pCText);	//���� ������
	DECLARE_SERIAL(CText)
	virtual ~CText();	//�Ҹ���

	virtual void Serialize(CArchive& ar);	// ����ȭ


	// OnDraw
	virtual void draw(/*CDC * m_pDC*/);//CpaintDC ���


	virtual void FontDisplay();
	virtual void FontTransform();// ��Ʈ����
	virtual void SizeTransform();// �������
	virtual void FontDestroy();// ����

	// LButtonDown
	//virtual void create(PointF startingPoint);					// ��ü ��������
	
	// OnMouseMove
	//void mouseMoveOperation(UINT nFlags, PointF point);			// OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�)
	virtual void creating(void* param1, ...);										// ���� �׸���
	virtual void moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);	// �̵� �׸���
	virtual void resizing(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);	// ũ�� ���� �׸���

	// LButtonUp / LButtonDlk
	virtual void endCreate(PointF point);							// ���� �Ϸ�
	//virtual void move(PointF originPoint, PointF targetPoint);	// ��ü �̵�
	//virtual void resize(PointF point, int resizeFlags);			// ��ü ũ�� ����


	//Keyboard Focus
	virtual void OnKeyboardFocus(PointF point);	//
	
	//void getview(CView* view);
	//static void getview(cview* view) {		// ĳ�� �׽�Ʈ (�׽�Ʈ�� ���� static���� ����)
	//	view->createsolidcaret(10, 20);
	//	view->setcaretpos(cpoint(50, 50));
	//	view->showcaret();
	//}

	void addChar(TCHAR newchar);	// m_String�� ���� �߰�

	CView* getView();
	CString getString();
	Gdiplus::Font* getFont();
	StringFormat* getStringFormat();
	BrushPtr getFontBrush();
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
	Gdiplus::Font* m_Font;			// ���ڿ� ����
	StringFormat* m_StringFormat;	// ���ڿ� ����
	BrushPtr m_FontBrush;			// ���ڿ� �귯��
	CView *m_View;					// ��� ��� �� (ĳ�� ���)

	//Color m_FontColor;	// ���ڻ�
	//LOGFONT m_FontLog;	// ��Ʈ�� ���� ������ (�۲�, ũ��, ����, ���Ÿ�, ����, ��Ҽ� ��)

	//	PointF points;
	// �۲�
	//CArray <TCHAR, TCHAR> m_str;
	//CFont m_Font;			//��Ʈ ()
	//int m_FontName;	// ����ڰ� ������ ��Ʈ��ȣ����
	//int m_FontSize;	// ����ڰ� �Է��� ��Ʈ ������
	//Color m_bkColor;	//���� http://shaeod.tistory.com/382
	//BOOL m_FontBold;	// ����ü
	//BOOL m_FontItalic; // ���Ÿ�ü
	//BOOL m_FontUnderline;// ����
	BOOL character_mode = FALSE;
protected :
	enum { NONE, HORZ, VERT, DIAG  }m_RESIZE;// ũ�⺯������
	//

	//HWND hWnd = ::GetActiveWindow();//�ڵ鷯
	//HDC* hdc = ::GetDC(hWnd);
	//CDC *tDC = CDC::FromHandle(hdc);
	//HWND hWnd = ::GetActiveWindow();//�ڵ鷯

};

