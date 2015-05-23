// FigureProperties.h : CFigureProperties Ŭ������ �������̽�
// @Author Lee Hwajung

#pragma once

#include "afx.h"
//#include <gdiplus.h>

using namespace Gdiplus;

// CFigureProperties ��� ����Դϴ�.

class CFigureProperties : public CObject
{
	
public:
	CFigureProperties();
	virtual ~CFigureProperties();

public:
	// ������
	Color getLineColor();
	void setLineColor(Color LineColor);
	int getLinePattern();
	void setLinePattern(int LinePattern);
	int getLineWidth();
	void setLineWidth(int LineWidth);

	// ä���
	Color getFillColor();
	void setFillColor(Color FillColor);
	int getFillPattern();
	void setFillPattern(int FillPattern);

	// �۲�
	Color getFontColor();
	void setFontColor(Color FontColor);
	LOGFONT getFontLog();
	void setFontLog(LOGFONT FontLog);

private:
	// ������
	Color m_LineColor;		// ������ ����
	int m_LinePattern;		// ������ ����
	int m_LineWidth;		// ������ ����

	// ä���
	Color m_FillColor;		// ä��� ����
	int m_FillPattern;		// ä��� ����

	// �۲�
	Color m_FontColor;		// �۲� ����
	LOGFONT m_FontLog;		// �۲� �̸�, ũ��, ����, ���Ÿ�, ����, ��Ҽ� ��
};

