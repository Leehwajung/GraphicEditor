// Strap.h : CStrap 클래스의 인터페이스
// CStrap : 선 개체를 정의하는 클래스
// 

#pragma once
#include "Figure.h"

// CStrap 명령 대상입니다.

class CStrap : public CFigure
{
public:
	CStrap();
	virtual ~CStrap();

	//// LButtonDown
	//virtual void create(PointF startingPoint);					// 끈 생성
	//virtual operationModeFlags cursorPosition(PointF point);	// 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지)
	//virtual operationModeFlags cursorPosition(RectF rect);		// 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지)

	//// OnMouseMove
	//void mouseMoveOperation(UINT nFlags, PointF point);			// OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단)
	//virtual void creating(UINT nFlags, PointF point);			// 생성 그리기
	//virtual void moving(UINT nFlags, PointF point);				// 이동 그리기
	//virtual void resizing(UINT nFlags, PointF point);			// 크기 변경 그리기

	//// LButtonUp / LButtonDlk
	//virtual void endCreate(PointF point);						// 생성 완료
	//virtual void move(PointF originPoint, PointF targetPoint);							// 개체 이동
	//virtual void resize(PointF point, PointF* anchorPoint = NULL, int resizeFlags = Free);			// 개체 크기 변경

	//// OnDraw / OnPaint
	//virtual void draw();										// 개체 그리기

	//// Menu Item
	//virtual void destroy();										// 개체 삭제

	//virtual void setLineColor(const Color& LineColor);					// 끈 색 설정
	//virtual void setLineWidth(const REAL& LineWidth);					// 끈 두께 설정
	//virtual void setLinePattern(const DashStyle& LinePattern);				// 끈 패턴 설정
	//virtual void setProperties(CFigureProperties properties);	// 설정된 값으로 개체 속성 설정

	// Getter / Setter
	Pen& getPen();
	void setPen(const Pen& pen);		// 각 객체가 별도의 펜을 가지고 있어야 하므로 인자로 받은 Pen을 변경하지 않음

// 특성
protected:
	//Pen m_Pen;
};


