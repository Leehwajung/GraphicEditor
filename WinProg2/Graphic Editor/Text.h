#pragma once
#include "Figure.h"
#include <gdiplus.h>

class CText : public CFigure
{
public:
	CText();
	~CText();//�Ҹ���
	
	virtual void FontDisplay();
	virtual void FontTransform();// ��Ʈ����
	virtual void SizeTransform();// �������
	virtual void FontDestroy();// ����
private:
//	CPoint points;

};
