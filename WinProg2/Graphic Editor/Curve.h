// Curve.h : CCurve Ŭ������ �������̽�
// CCurve : � ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "PolyLine.h"

// CCurve ��� ����Դϴ�.

class CCurve : public CPolyLine
{
public:
	CCurve();
	DECLARE_SERIAL(CCurve)

	virtual ~CCurve();
	virtual void Serialize(CArchive& ar);
};


