// Text.cpp : CText 클래스의 구현
// CText : 문자열 개체를 정의하는 클래스
//

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
void  CText::create(PointF startingPoint){
}				// 개체 리전생성

// OnMouseMove
void  CText::mouseMoveOperation(UINT nFlags, PointF point){}// OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단)
void  CText::creating(UINT nFlags, PointF point){		// 생성 그리기
}
void  CText::moving(UINT nFlags, PointF point){}				// 이동 그리기
void  CText::resizing(UINT nFlags, PointF point){}			// 크기 변경 그리기

// LButtonUp / LButtonDlk
// void addPoint(PointF point){}						// 점 추가
void   CText::move(PointF target){}							// 개체 이동
void   CText::resize(PointF point, int resizeFlags){}			// 개체 크기 변경

// OnDraw / OnPaint
void   CText::draw(CDC * m_lpDC){
	CRect rect;
	CFont character;

}//CpaintDC 사용

//Keyboard Focus
void CText::OnKeyboardFocus(PointF point){
	operationModeFlags region_check = cursorPosition(point);
	if (region_check == Create){//Create 상태면
		
	}
}// 캐럿표시, WM_SETFOCUS 와 WM_KILLFOCUS메시지 핸들러추가

//CString m_FontName;
//int m_FontSize;
//BOOL m_FontBold;
//BOOL m_FontItalic;
//BOOL m_FontUnderline;