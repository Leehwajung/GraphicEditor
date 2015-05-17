// FigureProperties.h : CFigureProperties 클래스의 인터페이스
//

#pragma once

#include "afx.h"
//#include <gdiplus.h>

using namespace Gdiplus;

// CFigureProperties 명령 대상입니다.

class CFigureProperties : public CObject
{
	
public:
	CFigureProperties();
	virtual ~CFigureProperties();

public:
	// 윤곽선
	Color getLineColor();
	void setLineColor(Color LineColor);
	int getLinePattern();
	void setLinePattern(int LinePattern);
	int getLineWidth();
	void setLineWidth(int LineWidth);

	// 채우기
	Color getFillColor();
	void setFillColor(Color FillColor);
	int getFillPattern();
	void setFillPattern(int FillPattern);

	// 글꼴
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
	// 윤곽선
	Color m_LineColor;
	int m_LinePattern;
	int m_LineWidth;

	// 채우기
	Color m_FillColor;
	int m_FillPattern;

	// 글꼴
	CString m_FontName;
	int m_FontSize;
	BOOL m_FontBold;
	BOOL m_FontItalic;
	BOOL m_FontUnderline;
};

