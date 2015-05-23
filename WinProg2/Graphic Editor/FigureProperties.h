// FigureProperties.h : CFigureProperties 클래스의 인터페이스
// @Author Lee Hwajung

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
	Color getFontColor();
	void setFontColor(Color FontColor);
	LOGFONT getFontLog();
	void setFontLog(LOGFONT FontLog);

private:
	// 윤곽선
	Color m_LineColor;		// 윤곽선 색상
	int m_LinePattern;		// 윤곽선 패턴
	int m_LineWidth;		// 윤곽선 굵기

	// 채우기
	Color m_FillColor;		// 채우기 색상
	int m_FillPattern;		// 채우기 패턴

	// 글꼴
	Color m_FontColor;		// 글꼴 색상
	LOGFONT m_FontLog;		// 글꼴 이름, 크기, 굵게, 이탤릭, 밑줄, 취소선 등
};

