#include "stdafx.h"
#include "Text.h"


CText::CText(){
}

CText::~CText(){//delete
}

///////////////////////////  Defalt 속성  //////////////////////////////////
void CText::FontDisplay(){//related information Derived from CFigureProperties
}
////////////////////////////////////////////////////////////////////////////

void CText::FontTransform( ){//Font transformation when setting values are changed

}

void CText::SizeTransform(){//Size transformation when when setting values are changed ex) click event

}
/////////////////

void  CText::FontDestroy(){// 제거

}


// LButtonDown
void  CText::create(CPoint startingPoint){
}				// 개체 리전생성

// OnMouseMove
void  CText::mouseMoveOperation(UINT nFlags, CPoint point){}// OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단)
void  CText::creating(UINT nFlags, CPoint point){		// 생성 그리기
}
void  CText::moving(UINT nFlags, CPoint point){}				// 이동 그리기
void  CText::resizing(UINT nFlags, CPoint point){}			// 크기 변경 그리기

// LButtonUp / LButtonDlk
// void addPoint(CPoint point){}						// 점 추가
void   CText::move(CPoint target){}							// 개체 이동
void   CText::resize(CPoint point, int resizeFlags){}			// 개체 크기 변경

// OnDraw / OnPaint
void   CText::draw(CDC * m_lpDC){
	CRect rect;
	CFont character;

}//CpaintDC 사용

//Keyboard Focus
void CText::OnKeyboardFocus(CPoint point){
	operationModeFlags region_check = cursorPosition(point);
	if (region_check == Create){//Create 상태면
		
	}
}// 캐럿표시, WM_SETFOCUS 와 WM_KILLFOCUS메시지 핸들러추가

//CString m_FontName;
//int m_FontSize;
//BOOL m_FontBold;
//BOOL m_FontItalic;
//BOOL m_FontUnderline;