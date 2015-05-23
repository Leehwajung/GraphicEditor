#pragma once
#include "Figure.h"
#include <gdiplus.h>

class CText : public CFigure 
{
public:
	CText();
	~CText();//�Ҹ���
	CText(const CText& pCText);	//���� ������

	//
	virtual void FontDisplay();
	virtual void FontTransform();// ��Ʈ����
	virtual void SizeTransform();// �������
	virtual void FontDestroy();// ����

	// LButtonDown
	virtual void create(CPoint startingPoint);					// ��ü ����
	virtual operationModeFlags cursorPosition(CPoint point);	// Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ���)

	// OnMouseMove
	void mouseMoveOperation(UINT nFlags, CPoint point);			// OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�)
	virtual void creating(UINT nFlags, CPoint point);			// ���� �׸���
	virtual void moving(UINT nFlags, CPoint point);				// �̵� �׸���
	virtual void resizing(UINT nFlags, CPoint point);			// ũ�� ���� �׸���

	// LButtonUp / LButtonDlk
	virtual void addPoint(CPoint point);						// �� �߰�
	virtual void move(CPoint target);							// ��ü �̵�
	virtual void resize(CPoint point, int resizeFlags);			// ��ü ũ�� ����

	// OnDraw / OnPaint
	virtual void draw();//CpaintDC ���

	//Keyboard Focus
	virtual void OnKeyboardFocus();// ĳ��ǥ��, WM_SETFOCUS �� WM_KILLFOCUS�޽��� �ڵ鷯�߰�

private://	CPoint points;
	// �۲�
	//CArray <TCHAR, TCHAR> m_str;
	CString m_str;//���ڿ�
	CFont Font; //��Ʈ
	int m_FontName; // ����ڰ� ������ ��Ʈ��ȣ����
	int m_FontSize; // ����ڰ� �Է��� ��Ʈ ������
	COLORREF m_bkColor; //���� http://shaeod.tistory.com/382
	COLORREF m_FontColor; //���ڻ�
	LOGFONT m_LogFont; //��Ʈ�� ���� ������(�۲�, ����)
	BOOL m_FontBold;// ����ü
	BOOL m_FontItalic; // ���Ÿ�ü
	BOOL m_FontUnderline;// ����
};

