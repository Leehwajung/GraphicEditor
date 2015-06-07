// Curve.h : CCurve 클래스의 인터페이스
// CCurve : 곡선 개체를 정의하는 클래스
// 

#pragma once
#include "PolyLine.h"

// CCurve 명령 대상입니다.

class CCurve : public CPolyLine
{
public:
	CCurve();
	DECLARE_SERIAL(CCurve)

	virtual ~CCurve();
	virtual void Serialize(CArchive& ar);
};


