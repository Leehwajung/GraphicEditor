// Shape.cpp : CShape Ŭ������ ����
// CShape : 2���� ���� ��ü�� �����ϴ� Ŭ����
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Shape.h"
#include "Global.h"


// CShape

IMPLEMENT_SERIAL(CShape, CFigure, 1)

CShape::CShape()
	: CFigure()
	, m_OutlinePen(NULL)
	, m_FillBrush(NULL)
{
}

CShape::CShape(IN Pen* pen, IN Brush* brush)
	: m_OutlinePen(pen->Clone())
	, m_FillBrush(brush->Clone())
{
}

CShape::~CShape()
{
	if (m_OutlinePen) {
		m_OutlinePen->~Pen();
	}

	if (m_FillBrush) {
		m_FillBrush->~Brush();
	}
}



// CShape ��� �Լ�

void CShape::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}


// �� ȹ��
Pen* CShape::getPen()
{
	return this->m_OutlinePen;
}

// �귯�� ȹ��
Brush* CShape::getBrush()
{
	return m_FillBrush;
}

// �귯�� Ÿ�� ȹ��
BrushType CShape::getBrushType()
{
	return m_FillBrush->GetType();
}

// ������ �� ȹ��
Color CShape::getOutlineColor()
{
	Color result;
	m_OutlinePen->GetColor(&result);

	return result;
}

// ������ �β� ȹ��
REAL CShape::getOutlineWidth()
{
	return m_OutlinePen->GetWidth();
}

// ������ ���� ȹ��
DashStyle CShape::getOutlinePattern()
{
	return m_OutlinePen->GetDashStyle();
}

// �� ä��� �� ȹ��
Color CShape::getFillColor()
{
	return getBrushColor(m_FillBrush);
}

// ���� ä��� �� ȹ��
Color CShape::getFillSubcolor()
{
	return getBrushSubcolor(m_FillBrush);
}

// ä��� ���� ȹ��
HatchStyle CShape::getFillPattern()
{
	return getBrushPattern(m_FillBrush);
}

// �� ����
void CShape::setPen(IN const Pen* pen)
{
	// ���� �� ����
	if (m_OutlinePen) {
		m_OutlinePen->~Pen();
	}

	// ���޹��� �� ����
	m_OutlinePen = pen->Clone();
}

// �귯�� ����
void CShape::setBrush(IN const Brush* brush)
{
	// ���� �귯�� ����
	if (m_FillBrush) {
		m_FillBrush->~Brush();
	}

	// ���޹��� �귯�� ����
	m_FillBrush = brush->Clone();
}

// ������ �� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CShape::setOutlineColor(IN const Color& outlineColor)
{
	return m_OutlinePen->SetColor(outlineColor) ? TRUE : FALSE;
}

// ������ �β� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CShape::setOutlineWidth(IN const REAL outlineWidth)
{
	return m_OutlinePen->SetWidth(outlineWidth) ? TRUE : FALSE;
}

// ������ ���� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CShape::setOutlinePattern(IN const DashStyle outlinePattern)
{
	return m_OutlinePen->SetDashStyle(outlinePattern) ? TRUE : FALSE;
}

// �� ä��� �� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CShape::setFillColor(IN const Color& fillColor)
{
	return setBrushColor(m_FillBrush, fillColor);
}

// ���� ä��� �� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CShape::setFillSubcolor(IN const Color& fillSubcolor)
{
	return setBrushSubcolor(m_FillBrush, fillSubcolor);
}

// ä��� ���� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CShape::setFillPattern(IN const HatchStyle fillPattern)
{
	return setBrushPattern(m_FillBrush, fillPattern);
}


/*** ���� �Լ� ***/
// �ֻ� ȹ��
Color CShape::getBrushColor(IN BrushPtr brush)
{
	Color result;

	switch (brush->GetType())
	{
		case Gdiplus::BrushTypeSolidColor: {
			((SolidBrush*)brush)->GetColor(&result);
			break;
		}

		case Gdiplus::BrushTypeHatchFill: {
			((HatchBrush*)brush)->GetForegroundColor(&result);
			break;
		}

		case Gdiplus::BrushTypeTextureFill: {
			result = NULLColor;	// �ؽ��� �귯�ô� ���� ������ ���� �����Ƿ� ����� ��ȯ
			break;
		}

		case Gdiplus::BrushTypePathGradient: {
			((PathGradientBrush*)brush)->GetCenterColor(&result);
			break;
		}

		case Gdiplus::BrushTypeLinearGradient: {
			Color* colors = NULL;
			((LinearGradientBrush*)brush)->GetLinearColors(colors);
			result = colors[0];
			break;
		}
	}

	return result;
}

// ������ ȹ��
Color CShape::getBrushSubcolor(IN BrushPtr brush)
{
	Color result;

	switch (brush->GetType())
	{
		case Gdiplus::BrushTypeSolidColor: {
			result = NULLColor;		// �ָ��� �귯�ô� �������� �����Ƿ� ����� ��ȯ
			break;
		}

		case Gdiplus::BrushTypeHatchFill: {
			((HatchBrush*)brush)->GetBackgroundColor(&result);
			break;
		}

		case Gdiplus::BrushTypeTextureFill: {
			result = NULLColor;		// �ؽ��� �귯�ô� ���� �����Ƿ� ����� ��ȯ
			break;
		}

		case Gdiplus::BrushTypePathGradient: {
			Color* colors = NULL;
			INT count = ((PathGradientBrush*)brush)->GetSurroundColorCount();
			((PathGradientBrush*)brush)->GetSurroundColors(colors, &count);
			result = colors[0];		// �� ������ �߿� ù ��° �� ��ȯ (���� ��ü ��ȯ �����ϰ� ���� �ʿ�)
			break;
		}

		case Gdiplus::BrushTypeLinearGradient: {
			Color* colors = NULL;
			((LinearGradientBrush*)brush)->GetLinearColors(colors);
			result = colors[1];
			break;
		}
	}

	return result;
}

// ���� ȹ��
HatchStyle CShape::getBrushPattern(IN BrushPtr brush)
{
	switch (brush->GetType())
	{
		case Gdiplus::BrushTypeHatchFill: {
			return ((HatchBrush*)brush)->GetHatchStyle();
		}

		//case Gdiplus::BrushTypeSolidColor:
		//case Gdiplus::BrushTypeTextureFill:
		//case Gdiplus::BrushTypePathGradient:
		//case Gdiplus::BrushTypeLinearGradient:
		default: {
			return Gdiplus::HatchStyleHorizontal;	// ������ �귯�ô� ������ �����Ƿ� ���� �ٹ��� ��ȯ
		}
	}
}

// �ֻ� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CShape::setBrushColor(IN BrushPtr& brush, IN const Color& fillColor)
{
	if (!brush) {
		return TRUE;
	}

	switch (brush->GetType())
	{
		case Gdiplus::BrushTypeSolidColor: {
			((SolidBrush*)brush)->SetColor(fillColor);
			break;
		}

		case Gdiplus::BrushTypeHatchFill: {
			HatchBrush* oldBrush = (HatchBrush*)brush;
			Color backColor;
			oldBrush->GetBackgroundColor(&backColor);
			brush = new HatchBrush(oldBrush->GetHatchStyle(), fillColor, backColor);
			oldBrush->~HatchBrush();
			break;
		}

		case Gdiplus::BrushTypeTextureFill: {
			// �ؽ��� �귯�ô� ���� �����Ƿ� �ƹ� ���۵� ���� ����
			break;
		}

		case Gdiplus::BrushTypePathGradient: {
			((PathGradientBrush*)brush)->SetCenterColor(fillColor);
			break;
		}

		case Gdiplus::BrushTypeLinearGradient: {
			Color* colors = NULL;
			((LinearGradientBrush*)brush)->GetLinearColors(colors);
			((LinearGradientBrush*)brush)->SetLinearColors(fillColor, colors[1]);
			break;
		}
	}

	return FALSE;
}

// ������ ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CShape::setBrushSubcolor(IN BrushPtr& brush, IN const Color& fillSubcolor)
{
	if (!brush) {
		return TRUE;
	}

	switch (brush->GetType())
	{
		case Gdiplus::BrushTypeSolidColor: {
			// �ָ��� �귯�ô� �������� �����Ƿ� �ƹ� ���۵� ���� ����
			break;
		}

		case Gdiplus::BrushTypeHatchFill: {
			HatchBrush* oldBrush = (HatchBrush*)brush;
			Color foreColor;
			oldBrush->GetForegroundColor(&foreColor);
			brush = new HatchBrush(oldBrush->GetHatchStyle(), foreColor, fillSubcolor);
			oldBrush->~HatchBrush();
			break;
		}

		case Gdiplus::BrushTypeTextureFill: {
			// �ؽ��� �귯�ô� ���� �����Ƿ� �ƹ� ���۵� ���� ����
			break;
		}

		case Gdiplus::BrushTypePathGradient: {
			PathGradientBrush* pgbrush = ((PathGradientBrush*)brush);
			Color* colors = NULL;
			INT count = pgbrush->GetSurroundColorCount();
			pgbrush->GetSurroundColors(colors, &count);
			colors[0] = fillSubcolor;
			pgbrush->SetSurroundColors(colors, &count);	// �� ������ �߿� ù ��° ���� ���� (���� ��ü ���� �����ϰ� ���� �ʿ�)
			break;
		}

		case Gdiplus::BrushTypeLinearGradient: {
			Color* colors = NULL;
			((LinearGradientBrush*)brush)->GetLinearColors(colors);
			((LinearGradientBrush*)brush)->SetLinearColors(colors[0], fillSubcolor);
			break;
		}
	}

	return FALSE;
}

// ���� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CShape::setBrushPattern(IN BrushPtr& brush, IN const HatchStyle fillPattern)
{
	if (!brush) {
		return TRUE;
	}

	switch (brush->GetType())
	{
		case Gdiplus::BrushTypeHatchFill: {
			HatchBrush* oldBrush = (HatchBrush*)brush;
			Color foreColor;
			Color backColor;
			oldBrush->GetForegroundColor(&foreColor);
			oldBrush->GetBackgroundColor(&backColor);
			brush = new HatchBrush(fillPattern, foreColor, backColor);
			oldBrush->~HatchBrush();
			break;
		}

		//case Gdiplus::BrushTypeSolidColor:
		//case Gdiplus::BrushTypeTextureFill:
		//case Gdiplus::BrushTypePathGradient:
		//case Gdiplus::BrushTypeLinearGradient:
		default: {
			// ������ �귯�ô� ������ ������ ���� �����Ƿ� �ƹ� ���۵� ���� ����
			break;
		}
	}

	return FALSE;
}
