// Polygon.h : CPolygon Ŭ������ �������̽�
// CPolygon : �ٰ��� ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "Shape.h"

// CPolygon ��� ����Դϴ�.

class CPolygon : public CShape
{
public:
	CPolygon();
	DECLARE_SERIAL(CPolygon)

	virtual ~CPolygon();
	virtual void Serialize(CArchive& ar);
};


