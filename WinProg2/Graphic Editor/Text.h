#pragma once
#include "Figure.h"
#include <gdiplus.h>

class CText : public CFigure
{
public:
	CText();
	~CText();//�Ҹ���
	
	virtual void FontTransform();// ��Ʈ����
	virtual void SizeTransform();// �������

private:
//	CPoint points;

};

