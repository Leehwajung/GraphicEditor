// PolyLine.h : CPolyLine 클래스의 인터페이스
// CPolyLine : 폴리라인 개체를 정의하는 클래스
//

#pragma once
#include "Line.h"

// CPolyLine 명령 대상입니다.

class CPolyLine : public CLine
{
public:
	CPolyLine();
	virtual ~CPolyLine();
};


