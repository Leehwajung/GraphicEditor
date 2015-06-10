// FigureSettings.cpp : CFigureSettings 클래스의 구현
// CFigureSettings : 도형 생성 및 속성 변경을 위한 기본 설정을 저장하는 클래스
// @Author Lee Hwajung

#include "stdafx.h"
#include "Graphic Editor.h"
#include "FigureSettings.h"


// CFigureSettings

CFigureSettings::CFigureSettings()
{
	m_StringFormat = new StringFormat();
}

CFigureSettings::~CFigureSettings()
{
	if (m_StringFormat) {
		m_StringFormat->~StringFormat();
	}
}


// CFigureSettings 멤버 함수

// 윤곽선 색 설정
void CFigureSettings::setOutlineColor(IN const Color& outlineColor)
{
	m_OutlineColor = outlineColor;
}

// 윤곽선 두께 설정
void CFigureSettings::setOutlineWidth(IN const REAL outlineWidth)
{
	m_OutlineWidth = outlineWidth;
}

// 윤곽선 패턴 설정
void CFigureSettings::setOutlinePattern(IN const DashStyle outlinePattern)
{
	m_OutlinePattern = outlinePattern;
}

// 주 채우기 색 설정
void CFigureSettings::setFillColor(IN const Color& fillColor)
{
	m_FillColor = fillColor;
}

// 보조 채우기 색 설정
void CFigureSettings::setFillSubcolor(IN const Color& fillSubcolor)
{
	m_FillSubcolor = fillSubcolor;
}

// 채우기 패턴 설정
void CFigureSettings::setFillPattern(IN const HatchStyle fillPattern)
{
	m_FillPattern = fillPattern;
}

// 주 글꼴색 설정
void CFigureSettings::setFontColor(IN const Color& fontColor)
{
	m_FontColor = fontColor;
}

// 보조 글꼴색 설정
void CFigureSettings::setFontSubcolor(IN const Color& fontSubcolor)
{
	m_FontSubcolor = fontSubcolor;
}

// 글꼴색 패턴 설정
void CFigureSettings::setFontPattern(IN const HatchStyle fontPattern)
{
	m_FontPattern = fontPattern;
}

// 글꼴 속성 설정
void CFigureSettings::setFontLog(IN const LOGFONT fontLog)
{
	m_FontLog = fontLog;
}

// 문자열 포맷 설정
void CFigureSettings::setStringFormat(IN const StringFormat& StringFormat)
{
	if (m_StringFormat) {
		m_StringFormat->~StringFormat();
	}
	m_StringFormat = StringFormat.Clone();
}

Pen* CFigureSettings::getOutlinePen(Pen* outlinepen)
{
	outlinepen->SetColor(m_OutlineColor);
	outlinepen->SetWidth(m_OutlineWidth);
	outlinepen->SetDashStyle(m_OutlinePattern);

	return outlinepen;
}

Brush* CFigureSettings::getFillBrush(Brush* fillBrush)
{
	switch (fillBrush->GetType())
	{
	case Gdiplus::BrushTypeSolidColor:

		break;

	case Gdiplus::BrushTypeHatchFill:

		break;

	case Gdiplus::BrushTypeTextureFill:

		break;

	case Gdiplus::BrushTypePathGradient:

		break;

	case Gdiplus::BrushTypeLinearGradient:

		break;
	}

	return NULL;
}

Brush* CFigureSettings::getFontBrush(Brush* fontBrush)
{
	switch (fontBrush->GetType())
	{
	case Gdiplus::BrushTypeSolidColor:

		break;

	case Gdiplus::BrushTypeHatchFill:

		break;

	case Gdiplus::BrushTypeTextureFill:

		break;

	case Gdiplus::BrushTypePathGradient:

		break;

	case Gdiplus::BrushTypeLinearGradient:

		break;
	}

	return NULL;
}

LOGFONT* CFigureSettings::getFontLog()
{
	return &m_FontLog;
}

StringFormat* CFigureSettings::getStringFormat()
{
	return m_StringFormat;
}