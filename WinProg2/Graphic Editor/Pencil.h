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
	virtual ~CPencil();
};


