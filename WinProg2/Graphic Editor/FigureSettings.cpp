// FigureSettings.cpp : CFigureSettings Ŭ������ ����
// CFigureSettings : ���� ���� �� �Ӽ� ������ ���� �⺻ ������ �����ϴ� Ŭ����
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


// CFigureSettings ��� �Լ�

// ������ �� ����
void CFigureSettings::setOutlineColor(IN const Color& outlineColor)
{
	m_OutlineColor = outlineColor;
}

// ������ �β� ����
void CFigureSettings::setOutlineWidth(IN const REAL outlineWidth)
{
	m_OutlineWidth = outlineWidth;
}

// ������ ���� ����
void CFigureSettings::setOutlinePattern(IN const DashStyle outlinePattern)
{
	m_OutlinePattern = outlinePattern;
}

// �� ä��� �� ����
void CFigureSettings::setFillColor(IN const Color& fillColor)
{
	m_FillColor = fillColor;
}

// ���� ä��� �� ����
void CFigureSettings::setFillSubcolor(IN const Color& fillSubcolor)
{
	m_FillSubcolor = fillSubcolor;
}

// ä��� ���� ����
void CFigureSettings::setFillPattern(IN const HatchStyle fillPattern)
{
	m_FillPattern = fillPattern;
}

// �� �۲û� ����
void CFigureSettings::setFontColor(IN const Color& fontColor)
{
	m_FontColor = fontColor;
}

// ���� �۲û� ����
void CFigureSettings::setFontSubcolor(IN const Color& fontSubcolor)
{
	m_FontSubcolor = fontSubcolor;
}

// �۲û� ���� ����
void CFigureSettings::setFontPattern(IN const HatchStyle fontPattern)
{
	m_FontPattern = fontPattern;
}

// �۲� �Ӽ� ����
void CFigureSettings::setFontLog(IN const LOGFONT fontLog)
{
	m_FontLog = fontLog;
}

// ���ڿ� ���� ����
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