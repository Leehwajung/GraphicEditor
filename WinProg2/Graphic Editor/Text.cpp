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
void  CText::create(CPoint startingPoint){
}				// ��ü ��������

// OnMouseMove
void  CText::mouseMoveOperation(UINT nFlags, CPoint point){}// OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�)
void  CText::creating(UINT nFlags, CPoint point){		// ���� �׸���
}
void  CText::moving(UINT nFlags, CPoint point){}				// �̵� �׸���
void  CText::resizing(UINT nFlags, CPoint point){}			// ũ�� ���� �׸���

// LButtonUp / LButtonDlk
// void addPoint(CPoint point){}						// �� �߰�
void   CText::move(CPoint target){}							// ��ü �̵�
void   CText::resize(CPoint point, int resizeFlags){}			// ��ü ũ�� ����

// OnDraw / OnPaint
void   CText::draw(){}//CpaintDC ���

//Keyboard Focus
void CText::OnKeyboardFocus(){}// ĳ��ǥ��, WM_SETFOCUS �� WM_KILLFOCUS�޽��� �ڵ鷯�߰�

//CString m_FontName;
//int m_FontSize;
//BOOL m_FontBold;
//BOOL m_FontItalic;
//BOOL m_FontUnderline;