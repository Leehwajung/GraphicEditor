// Text.cpp : CText Ŭ������ ����
// CText : ���ڿ� ��ü�� �����ϴ� Ŭ����
//

#include "stdafx.h"
#include "Text.h"

// http://warmz.tistory.com/862 CDC
CText::CText(CView *view)
	: m_View(view)
{

}

CText::~CText(){//delete
}

///////////////////////////  Defalt �Ӽ�  //////////////////////////////////
void CText::FontDisplay(){

}
////////////////////////////////////////////////////////////////////////////

void CText::FontTransform( ){
	//����ü ����
}

void CText::SizeTransform(){//����ũ�� ����

}
/////////////////

void  CText::FontDestroy(){// ����
	//�ܰ��� �簢���� �ı�
	DestroyCaret();//ĳ���ı�
}

//////////////////////////////////////////////////////////////////////

// LButtonDown
void  CText::create(PointF startingPoint){//Shape�� �ܰ��������� ������
	this->m_StartingPoint = startingPoint;

}				

// OnMouseMove
void  CText::mouseMoveOperation(UINT nFlags, PointF point){// �巡�� ���̾��//
	/* ���ۺз� 1. creating ��� 2. moving ��� 3. ���������*/
	
	operationModeFlags mode = m_OperationMode; // ���䷹�̼Ǹ�忡 ���� ����

	switch (mode){
		//1. Creating ���//
	case operationModeFlags::Create:
		creating(nFlags, point);
		break;
		//2. moving ���//
	case operationModeFlags::Move:
		m_View->HideCaret();
		moving(nFlags, point);
		break;
		//3. ��������� /
	case operationModeFlags::Resize:
		m_View->HideCaret();
		resizing(nFlags, point);
		break;
	case operationModeFlags::None:// ���õ��� ���� ����
		m_View->HideCaret();//ĳ�������
		break;
	}
}

///// mouseMoveOperation�� ȣ�⿡ ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�)
void  CText::creating(UINT nFlags, PointF point){//���� �׸���
	// �ܰ��� �׸���� shape �Լ��� �̿� //
	OnKeyboardFocus(point); // <- �̰Ÿ� EndCReate�� �ű��.
}
void  CText::moving(UINT nFlags, PointF point){// �̵� �׸���
	
	/*�����Ͱ� Rect�����ȿ� �ִ��� �������� üũ�� ��, Rect �ȿ� Ŭ���ȴٸ�*/
	::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));// 4����Ŀ���� ��
	
	PointF RelativePoint = PointF(point - m_StartingPoint);
	/* ���� ��ǥ���� ��� ��ǥ��ŭ ������ �̵� ��� ��ǥ�� ���Ѵ�. */
		
}		
void  CText::resizing(UINT nFlags, PointF point){// ũ�� ���� �׸���
	//�ϴ� ������ ���õ� ��, resizing ������ ���� ���콺Ŀ�� ��ü �� �����۾�
	CRect rect;
	m_View->GetClientRect(rect);
	::ClipCursor(rect); // ��Ʈ �������� Ŀ�� ����
	CRect rectHORZ(rect), rectVERT(rect);
	rectHORZ.DeflateRect(RESIZE_POINT, 0);
	rectVERT.DeflateRect(0, RESIZE_POINT);
	CPoint tp;
	tp.x = point.X;
	tp.y = point.Y;
	if (rectHORZ.PtInRect(tp)==FALSE){//CPoint ������ �޾�, �����ȿ� ��ǥ�� �����ִ� �� üũ
		::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));//west, east Ŀ��
		m_RESIZE = HORZ;
	}
	else if (rectVERT.PtInRect(tp) == FALSE){
		::SetCursor(::LoadCursor(NULL, IDC_SIZENS));
		m_RESIZE = VERT;
	}
	else
	{
		m_RESIZE = NONE;
	}

	PointF RelativePoint = PointF(point - m_StartingPoint);
	m_View->ClientToScreen(rect);
	switch (m_RESIZE){
	case NONE:
		rect.OffsetRect(RelativePoint.X, RelativePoint.Y);
		break;
	case HORZ:
		rect.InflateRect(RelativePoint.X, 0);
		break;
	case VERT:
		rect.InflateRect(0, RelativePoint.Y);
		break;
	}
	rect.NormalizeRect();
}			

///////////////////////////////////////////////////////////////////////
// LButtonUp / LButtonDlk
// void addPoint(PointF point){}						// �� �߰�
void   CText::move(PointF target){// ��ü �̵�

}							
void   CText::resize(PointF point, int resizeFlags){// ��ü ũ�� ����

}			

// OnDraw / OnPaint
void   CText::draw(CDC * m_lpDC){
	RectF rect;
	CFont character;

}//CpaintDC ���


//Keyboard Focus
void CText::OnKeyboardFocus(PointF point){
	operationModeFlags region_check = cursorPosition(point);
	
	if (region_check == Create){//Create ���¸�
		m_View->CreateSolidCaret(m_StartingPoint.X+10, m_StartingPoint.Y-10);
		m_View->ShowCaret();
	}
	else {//�̹� ��������ִ� ���·� �ٽ� showcaret

	}
}

// http://lab.cliel.com/28  ���콺 ������ ����.