// Pencil.h : CPencil 클래스의 인터페이스
// CPencil : 자유 곡선(연필) 개체를 정의하는 클래스
// 

#pragma once
#include "PolyLine.h"

// CPencil 명령 대상입니다.

class CPencil : public CPolyLine
{
public:
	CPencil();
	CPencil(IN Pen* pen);
	CPencil(IN Pen* pen, CList <PointF, PointF&>& list);
	DECLARE_SERIAL(CPencil)
	~CPencil();
	CFigure* clone();
	/* LButtonDown */
	// 좌표 위치 확인
	// 점이 직선 안에 있는지 확인하고 그 위치를 반환함
	// - IN 매개변수
	//		PointF point: 확인할 좌표
	// - 반환 값 (Position)
	//		Position: 직선 상의 점의 위치
	virtual Position pointInFigure(IN PointF point);
public:
	/* Menu Item */
	// 삭제
	// 곡선을 삭제하고 메모리를 해제
	virtual void destroy();
};