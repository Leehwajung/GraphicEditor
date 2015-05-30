// Ellipse.h : CEllipse 클래스의 인터페이스
// CEllipse : 타원 개체를 정의하는 클래스
// 

#pragma once
#include "Shape.h"

// CEllipse 명령 대상입니다.

class CEllipse : public CShape
{
public:
	CEllipse();
	DECLARE_SERIAL(CEllipse)
	virtual ~CEllipse();

public:
	virtual void Serialize(CArchive& ar);
};


