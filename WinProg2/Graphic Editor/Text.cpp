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
	//����ü ����
}

void CText::SizeTransform(){//Size transformation when when setting values are changed ex) click event
	//����ũ�� ����
}
/////////////////

void  CText::FontDestroy(){// ����
	DestroyCaret();//ĳ���ı�
}

//////////////////////////////////////////////////////////////////////

// LButtonDown
void  CText::create(PointF startingPoint){//Shape�� �ܰ��������� ������
	this->m_StartingPoint = startingPoint;
	
}				


// OnMouseMove
void  CText::mouseMoveOperation(UINT nFlags, PointF point){
	/* ���ۺз� 1. creating ��� 2. moving ��� 3. ���������*/
		
	operationModeFlags mode = cursorPosition(point);

	switch (mode){
		//1. Creating ���//
	case operationModeFlags::Create:
		creating(nFlags, point);
		break;
		//2. moving ���//
	case operationModeFlags::Move:
		moving(nFlags, point);
		break;
		//3. ��������� /
	case operationModeFlags::Resize:
		resizing(nFlags, point);
		break;
	case operationModeFlags::None:// ���õ��� ���� ����
		HideCaret(hWnd);//ĳ�������
		break;
	}
}

///// mouseMoveOperation�� ȣ�⿡ ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�)
void  CText::creating(UINT nFlags, PointF point){//���� �׸���
	// �ܰ��� �׸���� shape �Լ��� �̿� //
	OnKeyboardFocus(point);
	draw(tDC);
}
void  CText::moving(UINT nFlags, PointF point){// �̵� �׸���
	/*�����Ͱ� Rect�����ȿ� �ִ��� �������� üũ�� ��, Rect �ȿ� Ŭ���ȴٸ�*/

}		
void  CText::resizing(UINT nFlags, PointF point){// ũ�� ���� �׸���
	//�ϴ� ������ ���õ� ��, resizing ������ ���� ���콺Ŀ�� ��ü �� �����۾�

}			
///////////////////////////////////////////////////////////////////////
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
		//CreateSolidCaret();
		ShowCaret(hWnd);
	}
	else {//�̹� ��������ִ� ���·� �ٽ� showcaret

	}
}
//CString m_FontName;
//int m_FontSize;
//BOOL m_FontBold;
//BOOL m_FontItalic;

// http://lab.cliel.com/28  ���콺 ������ ����.