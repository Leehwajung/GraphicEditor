#pragma once
#include "Figure.h"
#include <gdiplus.h>

class CText : public CFigure
{
public:
	CText();
	~CText();//소멸자
	
	virtual void FontTransform();// 폰트변형
	virtual void SizeTransform();// 사이즈변경

private:
//	CPoint points;

};

