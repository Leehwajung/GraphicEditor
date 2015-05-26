// Shape.h : CShape 클래스의 인터페이스
// CShape : 2차원 도형 개체를 정의하는 클래스
// 

#pragma once
#include "Figure.h"

// CShape 명령 대상입니다.

class CShape : public CFigure
{
public:
	CShape();
	CShape(CClientDC* lpClientDC/*, PointF startingPoint*/);
	CShape(Graphics* lpGraphics/*, PointF startingPoint*/);
	CShape(CClientDC* lpClientDC/*, PointF startingPoint*/, Pen* pen, SolidBrush* brush);
	virtual ~CShape();

// 작업
public:
	Pen* getPen();
	void setPen(const Pen* pen);		// 각 객체가 별도의 펜을 가지고 있어야 하므로 인자로 받은 Pen을 변경하지 않음
	SolidBrush* getBrush();
	void setBrush(const SolidBrush* brush);	// 각 객체가 별도의 브러시를 가지고 있어야 하므로 인자로 받은 Brush를 변경하지 않음

// 재정의
	virtual void setLineColor(const Color& lineColor);			// 윤곽선 색 설정
	virtual void setLineWidth(const REAL& LineWidth);			// 윤곽선 두께 설정
	virtual void setLinePattern(const DashStyle& LinePattern);	// 윤곽선 패턴 설정
	virtual void setFillColor(const Color& FillColor);			// 칠하기 색 설정
	virtual void setFillPattern(const int fillPattern);			// 칠하기 패턴 설정 (아직 구현 안함)

// 특성
protected:
	Pen* m_Pen;
	SolidBrush* m_Brush;	// 빠른 구현을 위해 SolidBrush로 함, 나중에 Brush로 바꿀 것임 (다른 브러시 지원을 위해)

	
};


