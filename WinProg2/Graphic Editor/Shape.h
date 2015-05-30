// Shape.h : CShape 클래스의 인터페이스
// CShape : 2차원 도형 개체를 정의하는 클래스
// 

#pragma once
#include "Figure.h"

// CShape 명령 대상입니다.

class CShape : public CFigure
{
// 생성 및 소멸
public:
	CShape();
	CShape(IN CClientDC* lpClientDC);
	CShape(IN Graphics* lpGraphics);
	CShape(IN CClientDC* lpClientDC, IN Pen* pen, IN Brush* brush);
	CShape(IN Graphics* lpGraphics, IN Pen* pen, IN Brush* brush);
	DECLARE_DYNAMIC(CShape)
	virtual ~CShape();

// 작업
public:
	// 펜 획득
	Pen* getPen();

	// 브러시 획득
	Brush* getBrush();

	// 브러시 타입 획득
	BrushType getBrushType();

	// 윤곽선 색 획득
	Color getOutlineColor();

	// 윤곽선 두께 획득
	REAL getOutlineWidth();

	// 윤곽선 패턴 획득
	DashStyle getOutlinePattern();

	// 채우기 색 획득
	Color getFillColor();

	// 채우기 패턴 획득
	HatchStyle getFillPattern();
	
	// 펜 설정
	// 각 객체가 별도의 펜을 가지고 있어야 하므로 인자로 받은 Pen을 변경하지 않음
	void setPen(IN const Pen* pen);

	// 브러시 설정
	// 각 객체가 별도의 브러시를 가지고 있어야 하므로 인자로 받은 Brush를 변경하지 않음
	void setBrush(IN const Brush* brush);

// 재정의
public:
	// 윤곽선 색 설정
	virtual void setOutlineColor(IN const Color& outlineColor);

	// 윤곽선 두께 설정
	virtual void setOutlineWidth(IN const REAL outlineWidth);

	// 윤곽선 패턴 설정
	virtual void setOutlinePattern(IN const DashStyle outlinePattern);

	// 칠하기 색 설정
	virtual void setFillColor(IN const Color& fillColor);

	// 칠하기 패턴 설정
	virtual void setFillPattern(IN const HatchStyle fillPattern);

// 특성
protected:
	Pen* m_Pen;		// 그리기 펜
	Brush* m_Brush;	// 그리기 브러시
};


