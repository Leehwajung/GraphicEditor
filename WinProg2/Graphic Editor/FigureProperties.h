#pragma once
#include "afx.h"
#include <gdiplus.h>

using namespace Gdiplus;

class CFigureProperties : public CObject
{
public:
	CFigureProperties();
	~CFigureProperties();

public:
	Color getLineColor();
	void setLineColor(Color LineColor);
	int getLinePattern();
	void setLinePattern(int LinePattern);
	int getLineWidth();
	void setLineWidth(int LineWidth);

	Color getFillColor();
	void setFillColor(Color FillColor);
	int getFillPattern();
	void setFillPattern(int FillPattern);

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
	Color m_LineColor;
	int m_LinePattern;
	int m_LineWidth;

	Color m_FillColor;
	int m_FillPattern;

	CString m_FontName;
	int m_FontSize;
	BOOL m_FontBold;
	BOOL m_FontItalic;
	BOOL m_FontUnderline;
};

