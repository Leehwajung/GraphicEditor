// Text.cpp : CText 클래스의 구현
// CText : 문자열 개체를 정의하는 클래스
//

#include "stdafx.h"
#include "Text.h"

// http://warmz.tistory.com/862 CDC
CText::CText(){
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
void  CText::create(CDC *pDC, PointF startingPoint){//Shape의 외곽선생성과 동일함
	this->m_StartingPoint = startingPoint;
}				

// OnMouseMove
void  CText::mouseMoveOperation(UINT nFlags, PointF point){
	/* 동작분류 1. creating 모드 2. moving 모드 3. 사이즈변경모드*/
	
	operationModeFlags mode = m_OperationMode; // 오페레이션모드에 따라 동작

	switch (mode){
		//1. Creating 모드//
	case operationModeFlags::Create:
		creating(nFlags, point);
		break;
		//2. moving 모드//
	case operationModeFlags::Move:
		moving(nFlags, point);
		break;
		//3. 사이즈변경모드 /
	case operationModeFlags::Resize:
		resizing(nFlags, point);
		break;
	case operationModeFlags::None:// 선택되지 않은 상태
		HideCaret(hWnd);//캐럿숨기기
		break;
	}
}

///// mouseMoveOperation이 호출에 사용할 함수 (생성 / 이동 / 크기 변경 판단)
void  CText::creating(UINT nFlags, PointF point){//생성 그리기
	// 외곽선 그리기는 shape 함수를 이용 //
	OnKeyboardFocus(point);
	//draw(tDC);
}
void  CText::moving(UINT nFlags, PointF point){// 이동 그리기
	/*포인터가 Rect영역안에 있는지 없는지를 체크한 후, Rect 안에 클릭된다면*/

}		
void  CText::resizing(UINT nFlags, PointF point){// 크기 변경 그리기
	//일단 도형이 선택된 후, resizing 영역에 들어가면 마우스커서 교체 및 변경작업

}			
///////////////////////////////////////////////////////////////////////
// LButtonUp / LButtonDlk
// void addPoint(PointF point){}						// 점 추가
void   CText::move(PointF target){// 개체 이동
}							
void   CText::resize(PointF point, int resizeFlags){// 개체 크기 변경
}			

// OnDraw / OnPaint
void   CText::draw(CDC * m_lpDC){
	RectF rect;
	CFont character;

}//CpaintDC 사용


//Keyboard Focus
void CText::OnKeyboardFocus(PointF point){
	operationModeFlags region_check = cursorPosition(point);
	
	if (region_check == Create){//Create 상태면
		//CreateSolidCaret();
		ShowCaret(hWnd);
	}
	else {//이미 만들어져있는 상태로 다시 showcaret

	}
}
//CString m_FontName;
//int m_FontSize;
//BOOL m_FontBold;
//BOOL m_FontItalic;

// http://lab.cliel.com/28  마우스 움직임 제한.