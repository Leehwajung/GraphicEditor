// Text.h : CText Ŭ������ �������̽�
// CText : ���ڿ� ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "Rectangle.h"
# define RESIZE_POINT 5 // ũ�⺯��� �⺻����
// CText ��� ����Դϴ�.

class CText : public CRectangle
{
public:
	CText(CView *view);
	~CText();//�Ҹ���
	CText(const CText& pCText);	//���� ������

	//
	virtual void FontDisplay();
	virtual void FontTransform();// ��Ʈ����
	virtual void SizeTransform();// �������
	virtual void FontDestroy();// ����

	// LButtonDown
	virtual void create(PointF startingPoint);					// ��ü ��������
	
	// OnMouseMove
	void mouseMoveOperation(UINT nFlags, PointF point);			// OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�)
	virtual void creating(UINT nFlags, PointF point);			// ���� �׸���
	virtual void moving(UINT nFlags, PointF point);				// �̵� �׸���
	virtual void resizing(UINT nFlags, PointF point);			// ũ�� ���� �׸���

	// LButtonUp / LButtonDlk
	//virtual void endCreate(PointF point);						// ���� �Ϸ�
	virtual void move(PointF originPoint, PointF targetPoint);							// ��ü �̵�
	virtual void resize(PointF point, int resizeFlags);			// ��ü ũ�� ����

	// OnDraw / OnPaint
	virtual void draw(CDC * m_lpDC);//CpaintDC ���

	//Keyboard Focus
	virtual void OnKeyboardFocus(PointF point);//

	void getview(CView* view);
	//static void getview(cview* view) {	// ĳ�� �׽�Ʈ (�׽�Ʈ�� ���� static���� ����)
	//	view->createsolidcaret(10, 20);
	//	view->setcaretpos(cpoint(50, 50));
	//	view->showcaret();
	//}
// Ư��
private:
	CString m_String;	// �Է¹��� ���ڿ�
	CView *m_View;
	Color m_FontColor;	// ���ڻ�
	LOGFONT m_FontLog;	// ��Ʈ�� ���� ������ (�۲�, ũ��, ����, ���Ÿ�, ����, ��Ҽ� ��)

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
protected :
	enum { NONE, HORZ, VERT, DIAG  }m_RESIZE;// ũ�⺯������
	//
	//HWND hWnd = ::GetActiveWindow();//�ڵ鷯
	//HDC* hdc = ::GetDC(hWnd);
	//CDC *tDC = CDC::FromHandle(hdc);
	//HWND hWnd = ::GetActiveWindow();//�ڵ鷯

};

