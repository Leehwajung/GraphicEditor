// Sine.h : CSine 클래스의 인터페이스
// CSine : Sine 그래프 형 곡선 개체를 정의하는 클래스
// 

#pragma once
#include "PolyLine.h"

// CSine 명령 대상입니다.

class CSine : public CPolyLine
{
public:
	CSine();
	virtual ~CSine();
};


