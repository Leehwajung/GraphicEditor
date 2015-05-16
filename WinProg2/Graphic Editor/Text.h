#pragma once
#include "Figure.h"
#include <gdiplus.h>

class CText : public CFigure
{
public:
	CText();
	~CText();//소멸자
	
	virtual void FontDisplay();
	virtual void FontTransform();// 폰트변형
	virtual void SizeTransform();// 사이즈변경
	virtual void FontDestroy();// 제거
private:
//	CPoint points;

};

