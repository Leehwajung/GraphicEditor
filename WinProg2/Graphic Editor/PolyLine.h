// PolyLine.h : CPolyLine 클래스의 인터페이스
// CPolyLine : 폴리라인 개체를 정의하는 클래스
//

#pragma once
#include "Strap.h"

// CPolyLine 명령 대상입니다.

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


