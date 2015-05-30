// PolyLine.h : CPolyLine Ŭ������ �������̽�
// CPolyLine : �������� ��ü�� �����ϴ� Ŭ����
//

#pragma once
#include "Strap.h"

// CPolyLine ��� ����Դϴ�.

class CPolyLine : public CStrap
{
public:
	CPolyLine();
	DECLARE_SERIAL(CPolyLine)
	virtual ~CPolyLine();

public:
	virtual void Serialize(CArchive& ar);

	// Getter
	CList <PointF, PointF&>& GetPointsList();

private:
	CList <PointF, PointF&> m_PointsList;
};


