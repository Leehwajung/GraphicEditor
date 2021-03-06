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
	CShape(IN Pen* pen, IN Brush* brush);
	DECLARE_SERIAL(CShape)
	virtual ~CShape();

public:
	// 직렬화
	virtual void Serialize(CArchive& ar);

// 작업
public:
	// 윤곽선 펜 획득
	Pen* getOutlinePen();

	// 채우기 브러시 획득
	Brush* getFillBrush();

	// 브러시 타입 획득
	BrushType getBrushType();

	// 윤곽선 색 획득
	Color getOutlineColor();

	// 윤곽선 두께 획득
	REAL getOutlineWidth();

	// 윤곽선 패턴 획득
	DashStyle getOutlinePattern();

	// 주 채우기 색 획득
	Color getFillColor();

	// 보조 채우기 색 획득
	Color getFillSubcolor();

	// 채우기 패턴 획득
	HatchStyle getFillPattern();
	
	// 윤곽선 펜 설정
	// 각 객체가 별도의 펜을 가지고 있어야 하므로 인자로 받은 Pen을 변경하지 않음
	void setOutlinePen(IN const Pen* pen);

// 재정의
public:
	// 채우기 브러시 설정
	// 각 객체가 별도의 브러시를 가지고 있어야 하므로 인자로 받은 Brush를 변경하지 않음
	virtual void setFillBrush(IN const Brush* brush, IN BOOL PropertyMaintenanceFlag = FALSE);


	// 윤곽선 색 설정
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setOutlineColor(IN const Color& outlineColor);

	// 윤곽선 두께 설정
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setOutlineWidth(IN const REAL outlineWidth);

	// 윤곽선 패턴 설정
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setOutlinePattern(IN const DashStyle outlinePattern);

	// 주 채우기 색 설정
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setFillColor(IN const Color& fillColor);

	// 보조 채우기 색 설정
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setFillSubcolor(IN const Color& fillSubcolor);

	// 채우기 패턴 설정
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setFillPattern(IN const HatchStyle fillPattern);
	


// 보조 작업
protected:
	// 주색 획득
	static Color getBrushColor(IN BrushPtr brush);

	// 보조색 획득
	static Color getBrushSubcolor(IN BrushPtr brush);

	// 패턴 획득
	static HatchStyle getBrushPattern(IN BrushPtr brush);

	// 주색 설정
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	static BOOL setBrushColor(IN BrushPtr& brush, IN const Color& fillColor);

	// 보조색 설정
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	static BOOL setBrushSubcolor(IN BrushPtr& brush, IN const Color& fillSubcolor);

	// 패턴 설정
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	static BOOL setBrushPattern(IN BrushPtr& brush, IN const HatchStyle fillPattern);

	// 브러시 설정
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	static BOOL setBrush(IN BrushPtr& brush, IN Brush* srcBrush, IN BOOL PropertyMaintenanceFlag = FALSE);

// 특성
protected:
	PenPtr m_OutlinePen;	// 그리기 펜
	BrushPtr m_FillBrush;	// 그리기 브러시
};


