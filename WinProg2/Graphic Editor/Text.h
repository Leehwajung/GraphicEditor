#pragma once
#include "Shape.h"

using namespace Gdiplus;

class CText : public CShape 
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
	virtual void create(CPoint startingPoint);					// ��ü ��������
	

	// OnMouseMove
	void mouseMoveOperation(UINT nFlags, CPoint point);			// OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�)
	virtual void creating(UINT nFlags, CPoint point);			// ���� �׸���
	virtual void moving(UINT nFlags, CPoint point);				// �̵� �׸���
	virtual void resizing(UINT nFlags, CPoint point);			// ũ�� ���� �׸���

	// LButtonUp / LButtonDlk
	//virtual void addPoint(CPoint point);						// �� �߰�
	virtual void move(CPoint target);							// ��ü �̵�
	virtual void resize(CPoint point, int resizeFlags);			// ��ü ũ�� ����

	// OnDraw / OnPaint
	virtual void draw(CDC * m_lpDC);//CpaintDC ���

	//Keyboard Focus
	virtual void OnKeyboardFocus(CPoint point);//
// Ư��
private:
	CString m_String;	//�Է¹��� ���ڿ�

	Color m_FontColor;	// ���ڻ�
	LOGFONT m_FontLog;	// ��Ʈ�� ���� ������(�۲�, ����)

	//	CPoint points;
	// �۲�
	//CArray <TCHAR, TCHAR> m_str;
	//CFont m_Font;			//��Ʈ ()
	//int m_FontName;	// ����ڰ� ������ ��Ʈ��ȣ����
	//int m_FontSize;	// ����ڰ� �Է��� ��Ʈ ������
	//Color m_bkColor;	//���� http://shaeod.tistory.com/382
	//BOOL m_FontBold;	// ����ü
	//BOOL m_FontItalic; // ���Ÿ�ü
	//BOOL m_FontUnderline;// ����
};

