// Text.cpp : CText Ŭ������ ����
// CText : ���ڿ� ��ü�� �����ϴ� Ŭ����
//

#include "stdafx.h"
#include "Text.h"


CText::CText(){
}

CText::~CText(){//delete
}

///////////////////////////  Defalt �Ӽ�  //////////////////////////////////
void CText::FontDisplay(){//related information Derived from CFigureProperties
}
////////////////////////////////////////////////////////////////////////////

void CText::FontTransform( ){//Font transformation when setting values are changed

}

void CText::SizeTransform(){//Size transformation when when setting values are changed ex) click event

}
/////////////////

void  CText::FontDestroy(){// ����

}


// LButtonDown
void  CText::create(PointF startingPoint){
}				// ��ü ��������

// OnMouseMove
void  CText::mouseMoveOperation(UINT nFlags, PointF point){}// OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�)
void  CText::creating(UINT nFlags, PointF point){		// ���� �׸���
}
void  CText::moving(UINT nFlags, PointF point){}				// �̵� �׸���
void  CText::resizing(UINT nFlags, PointF point){}			// ũ�� ���� �׸���

// LButtonUp / LButtonDlk
// void addPoint(PointF point){}						// �� �߰�
void   CText::move(PointF target){}							// ��ü �̵�
void   CText::resize(PointF point, int resizeFlags){}			// ��ü ũ�� ����

// OnDraw / OnPaint
void   CText::draw(CDC * m_lpDC){
	CRect rect;
	CFont character;

}//CpaintDC ���

//Keyboard Focus
void CText::OnKeyboardFocus(PointF point){
	operationModeFlags region_check = cursorPosition(point);
	if (region_check == Create){//Create ���¸�
		
	}
}// ĳ��ǥ��, WM_SETFOCUS �� WM_KILLFOCUS�޽��� �ڵ鷯�߰�

//CString m_FontName;
//int m_FontSize;
//BOOL m_FontBold;
//BOOL m_FontItalic;
//BOOL m_FontUnderline;