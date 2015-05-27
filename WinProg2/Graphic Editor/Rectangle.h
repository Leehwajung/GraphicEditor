// Rectangle.h : CRectangle 클래스의 인터페이스
// CRectangle : 직사각형 개체를 정의하는 클래스
// 

#pragma once
#include "Shape.h"

// CRectangle 명령 대상입니다.

class CRectangle : public CShape
{
public:
	CRectangle();
	CRectangle(CClientDC* lpClientDC/*, PointF startingPoint*/);
	CRectangle(Graphics* lpGraphics/*, PointF startingPoint*/);
	//CRectangle(CClientDC* lpClientDC, RectF& rect);
	CRectangle(CClientDC* lpClientDC/*, PointF startingPoint*/, /*RectF& rect,*/ Pen* pen, SolidBrush* brush);
	virtual ~CRectangle();

	// LButtonDown
	virtual void create(PointF startingPoint);					// 개체 생성
	virtual operationModeFlags cursorPosition(PointF point);	// 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지)


	// OnMouseMove
	void mouseMoveOperation(UINT nFlags, PointF point);			// OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단)
	virtual void creating(UINT nFlags, PointF point);			// 생성 그리기
	virtual void moving(UINT nFlags, PointF point);				// 이동 그리기
	virtual void resizing(UINT nFlags, PointF point);			// 크기 변경 그리기

	// LButtonUp
	virtual void endCreate(PointF point);						// 생성 완료
	virtual void move(PointF originPoint, PointF targetPoint);							// 개체 이동
	virtual void resize(PointF point, PointF* anchorPoint = NULL, int resizeFlags = Free);			// 개체 크기 변경
	virtual operationModeFlags cursorPosition(RectF rect);		// 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지)

	// OnDraw / OnPaint
	virtual void draw();										// 개체 그리기
	virtual void drawSelect();

	// Menu Item
	virtual void destroy();										// 개체 삭제

// 특성
protected:
	RectF m_Rect;	// 사각형
};

