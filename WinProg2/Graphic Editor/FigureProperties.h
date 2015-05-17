// FigureProperties.h : CFigureProperties Ŭ������ �������̽�
//

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
	CString getFontName();
	void setFontName(CString FontName);
	int getFontSize();
	void setFontSize(int FontSize);
	BOOL getFontBold();
	void setFontBold(BOOL FontBold);
	BOOL getFontItalic();
	void setFontItalic(BOOL FontItalic);
	BOOL getFontUnderline();
	void setFontUnderline(BOOL FontUnderline);

private:
	// ������
	Color m_LineColor;
	int m_LinePattern;
	int m_LineWidth;

	// ä���
	Color m_FillColor;
	int m_FillPattern;

	// �۲�
	CString m_FontName;
	int m_FontSize;
	BOOL m_FontBold;
	BOOL m_FontItalic;
	BOOL m_FontUnderline;
};

