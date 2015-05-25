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
	virtual ~CStrap();
};


