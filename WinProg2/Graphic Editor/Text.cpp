// Text.cpp : CText 클래스의 구현
// CText : 문자열 개체를 정의하는 클래스
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

///////////////////////////  Defalt 속성  //////////////////////////////////
void CText::FontDisplay(){

}
////////////////////////////////////////////////////////////////////////////

void CText::FontTransform( ){
	//글자체 변경
}

void CText::SizeTransform(){//글자크기 변경

}
/////////////////

void  CText::FontDestroy(){// 제거
	//외각선 사각형도 파괴
	DestroyCaret();//캐럿파괴
}

//////////////////////////////////////////////////////////////////////

// LButtonDown
void  CText::create(PointF startingPoint){//Shape의 외곽선생성과 동일함
	this->m_StartingPoint = startingPoint;

}				

// OnMouseMove
void  CText::mouseMoveOperation(UINT nFlags, PointF point){// 드래그 중이어야//
	/* 동작분류 1. creating 모드 2. moving 모드 3. 사이즈변경모드*/
	
	operationModeFlags mode = m_OperationMode; // 오페레이션모드에 따라 동작

	switch (mode){
		//1. Creating 모드//
	case operationModeFlags::Create:
		creating(nFlags, point);
		break;
		//2. moving 모드//
	case operationModeFlags::Move:
		m_View->HideCaret();
		moving(nFlags, point);
		break;
		//3. 사이즈변경모드 /
	case operationModeFlags::Resize:
		m_View->HideCaret();
		resizing(nFlags, point);
		break;
	case operationModeFlags::None:// 선택되지 않은 상태
		m_View->HideCaret();//캐럿숨기기
		break;
	}
}

///// mouseMoveOperation이 호출에 사용할 함수 (생성 / 이동 / 크기 변경 판단)
void  CText::creating(UINT nFlags, PointF point){//생성 그리기
	// 외곽선 그리기는 shape 함수를 이용 //

}
void  CText::moving(UINT nFlags, PointF point){// 이동 그리기
	
	/*포인터가 Rect영역안에 있는지 없는지를 체크한 후, Rect 안에 클릭된다면*/
	::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));// 4방향커서로 셋
	
	PointF RelativePoint = PointF(point - m_StartingPoint);
	/* 원래 좌표에서 상대 좌표만큼 연산해 이동 결과 좌표를 구한다. */
		 
}		
void  CText::resizing(UINT nFlags, PointF point){// 크기 변경 그리기
	//일단 도형이 선택된 후, resizing 영역에 들어가면 마우스커서 교체 및 변경작업
	CRect rect;
	m_View->GetClientRect(rect);
	::ClipCursor(rect); // 렉트 영역으로 커서 제한
	CRect rectHORZ(rect), rectVERT(rect);
	rectHORZ.DeflateRect(RESIZE_POINT, 0);
	rectVERT.DeflateRect(0, RESIZE_POINT);
	CPoint tp;
	tp.x = point.X;
	tp.y = point.Y;
	if (rectHORZ.PtInRect(tp)==FALSE){//CPoint 변수를 받아, 영역안에 좌표가 들어와있는 지 체크
		::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));//west, east 커서
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
// void addPoint(PointF point){}						// 점 추가
void   CText::move(PointF target){// 개체 이동

}							
void   CText::resize(PointF point, int resizeFlags){// 개체 크기 변경

}			
// LButtonUp
void CText::endCreate(PointF point){
	OnKeyboardFocus(point); // <- 이거를 EndCReate로 옮기기.
	CDC *pDC = m_View->GetDC();
	Graphics graphics(*pDC);
	WCHAR string;
	//graphics.DrawString(WCHAR * string, int length, FONT * font, POINTF &origin, BRUSH *brush);

}

// OnDraw / OnPaint
void   CText::draw(CDC * m_lpDC){
	RectF rect;
	CFont character;

}//CpaintDC 사용


//Keyboard Focus
void CText::OnKeyboardFocus(PointF point){
	CPoint cur(m_StartingPoint.X, m_StartingPoint.Y);
		m_View->CreateSolidCaret(10,20);// 캐럿 사이즈
		m_View->SetCaretPos(cur);
		m_View->ShowCaret();
		character_mode = TRUE; // 캐릭터 입력모드
}

// http://lab.cliel.com/28  마우스 움직임 제한.