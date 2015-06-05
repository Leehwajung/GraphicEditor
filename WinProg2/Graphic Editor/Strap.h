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
	CStrap(IN Pen* pen);
	DECLARE_SERIAL(CStrap)
	virtual ~CStrap();

	virtual void Serialize(CArchive& ar);

	// 점 추가 (순수 가상)
	//virtual void addPoint(PointF point);

	// 개별 좌표 이동
	virtual void pointMove(IN PointF originPoint, IN PointF targetPoint);

	// 개별 좌표 이동 그리기
	virtual void pointMoving(Graphics* lpGraphics, IN PointF originPoint, IN PointF targetPoint);

	// 펜 획득
	Pen* getPen();

	// 윤곽선 색 획득
	Color getOutlineColor();

	// 윤곽선 두께 획득
	REAL getOutlineWidth();

	// 윤곽선 패턴 획득
	DashStyle getOutlinePattern();

	// 펜 설정
	// 각 객체가 별도의 펜을 가지고 있어야 하므로 인자로 받은 Pen을 변경하지 않음
	void setPen(IN const Pen* pen);

	// 재정의
public:
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
	//		FALSE: 채우기가 없으므로 고정값 반환 (성공으로 간주)
	virtual BOOL setFillColor(IN const Color& fillColor) { return FALSE; }

	// 보조 채우기 색 설정
	// - 반환 값 (BOOL)
	//		FALSE: 채우기가 없으므로 고정값 반환 (성공으로 간주)
	virtual BOOL setFillSubcolor(IN const Color& fillSubcolor) { return FALSE; }

	// 채우기 패턴 설정
	// - 반환 값 (BOOL)
	//		FALSE: 채우기가 없으므로 고정값 반환 (성공으로 간주)
	virtual BOOL setFillPattern(IN const HatchStyle fillPattern) { return FALSE; }


// 특성
protected:
	PenPtr m_OutlinePen;
};


