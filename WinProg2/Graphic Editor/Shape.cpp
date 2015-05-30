// Shape.cpp : CShape Ŭ������ ����
// CShape : 2���� ���� ��ü�� �����ϴ� Ŭ����
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Shape.h"
#include "Global.h"


// CShape

IMPLEMENT_DYNAMIC(CShape, CFigure)

CShape::CShape()
	: CFigure()
	, m_Pen(NULL)
	, m_Brush(NULL)
{
}

CShape::CShape(IN CClientDC* lpClientDC)
	: CFigure(lpClientDC)
	, m_Pen(NULL)
	, m_Brush(NULL)
{
}

CShape::CShape(IN Graphics* lpGraphics)
	: CFigure(lpGraphics)
	, m_Pen(NULL)
	, m_Brush(NULL)
{
}

CShape::CShape(IN CClientDC* lpClientDC, IN Pen* pen, IN Brush* brush)
	: CFigure(lpClientDC)
	, m_Pen(pen->Clone())
	, m_Brush(brush->Clone())
{
}

CShape::CShape(IN Graphics* lpGraphics, IN Pen* pen, IN Brush* brush)
	: CFigure(lpGraphics)
	, m_Pen(pen->Clone())
	, m_Brush(brush->Clone())
{

}

CShape::~CShape()
{
	if (m_Pen) {
		m_Pen->~Pen();
	}

	if (m_Brush) {
		m_Brush->~Brush();
	}
}


// CShape ��� �Լ�

// �� ȹ��
Pen* CShape::getPen()
{
	return m_Pen;
}

// �귯�� ȹ��
Brush* CShape::getBrush()
{
	return m_Brush;
}

// �귯�� Ÿ�� ȹ��
BrushType CShape::getBrushType()
{
	return m_Brush->GetType();
}

// ������ �� ȹ��
Color CShape::getOutlineColor()
{
	Color result;
	m_Pen->GetColor(&result);

	return result;
}

// ������ �β� ȹ��
REAL CShape::getOutlineWidth()
{
	return m_Pen->GetWidth();
}

// ������ ���� ȹ��
DashStyle CShape::getOutlinePattern()
{
	return m_Pen->GetDashStyle();
}

// ä��� �� ȹ��
Color CShape::getFillColor()
{
	Color result;

	switch (m_Brush->GetType())
	{
	case Gdiplus::BrushTypeSolidColor:
		((SolidBrush*)m_Brush)->GetColor(&result);
		break;
		
	case Gdiplus::BrushTypeHatchFill:
		((HatchBrush*)m_Brush)->GetForegroundColor(&result);
		break;

	case Gdiplus::BrushTypeTextureFill:
		result = Color(0, 255, 255, 255);	// �ؽ��� �귯�ô� ���� ������ ���� �����Ƿ� ����� ��ȯ
		break;

	case Gdiplus::BrushTypePathGradient:
		((PathGradientBrush*)m_Brush)->GetCenterColor(&result);
		break;

	case Gdiplus::BrushTypeLinearGradient:
		Color* firstColor;
		((LinearGradientBrush*)m_Brush)->GetLinearColors(firstColor);
		result = firstColor[0];
		break;
	}

	return result;
}

// ä��� ���� ȹ��
HatchStyle CShape::getFillPattern()
{
	switch (m_Brush->GetType())
	{
	case Gdiplus::BrushTypeHatchFill:
		return ((HatchBrush*)m_Brush)->GetHatchStyle();

	//case Gdiplus::BrushTypeSolidColor:
	//case Gdiplus::BrushTypeTextureFill:
	//case Gdiplus::BrushTypePathGradient:
	//case Gdiplus::BrushTypeLinearGradient:
	default:
		return Gdiplus::HatchStyleHorizontal;	// ������ �귯�ô� ������ ������ ���� �����Ƿ� ���� �ٹ��� ��ȯ
	}
}

// �� ����
void CShape::setPen(IN const Pen* pen)
{
	// ���� �� ����
	if (m_Pen) {
		m_Pen->~Pen();
	}

	// ���޹��� �� ����
	m_Pen = pen->Clone();
}

// �귯�� ����
void CShape::setBrush(IN const Brush* brush)
{
	// ���� �귯�� ����
	if (m_Brush) {
		m_Brush->~Brush();
	}

	// ���޹��� �귯�� ����
	m_Brush->Clone();
}

// ������ �� ����
void CShape::setOutlineColor(IN const Color& outlineColor)
{
	m_Pen->SetColor(outlineColor);
}

// ������ �β� ����
void CShape::setOutlineWidth(IN const REAL outlineWidth)
{
	m_Pen->SetWidth(outlineWidth);
}

// ������ ���� ����
void CShape::setOutlinePattern(IN const DashStyle outlinePattern)
{
	m_Pen->SetDashStyle(outlinePattern);
}

// ĥ�ϱ� �� ����
void CShape::setFillColor(IN const Color& fillColor)
{
	switch (m_Brush->GetType())
	{
	case Gdiplus::BrushTypeSolidColor:
		((SolidBrush*)m_Brush)->SetColor(fillColor);
		break;

	case Gdiplus::BrushTypeHatchFill:
		HatchBrush* oldBrush = (HatchBrush*) m_Brush;
		Color backColor;
		oldBrush->GetBackgroundColor(&backColor);
		m_Brush = new HatchBrush(oldBrush->GetHatchStyle(), fillColor, backColor);
		oldBrush->~HatchBrush();
		break;

	case Gdiplus::BrushTypeTextureFill:
		// �ؽ��� �귯�ô� ���� �����Ƿ� �ƹ� ���۵� ���� ����
		break;

	case Gdiplus::BrushTypePathGradient:
		((PathGradientBrush*)m_Brush)->SetCenterColor(fillColor);
		break;

	case Gdiplus::BrushTypeLinearGradient:
		Color* colors;
		((LinearGradientBrush*)m_Brush)->GetLinearColors(colors);
		((LinearGradientBrush*)m_Brush)->SetLinearColors(fillColor, colors[1]);
		break;
	}
}

// ĥ�ϱ� ���� ����
void CShape::setFillPattern(IN const HatchStyle fillPattern)
{
	switch (m_Brush->GetType())
	{
	case Gdiplus::BrushTypeHatchFill:
		HatchBrush* oldBrush = (HatchBrush*)m_Brush;
		Color foreColor;
		Color backColor;
		oldBrush->GetForegroundColor(&foreColor);
		oldBrush->GetBackgroundColor(&backColor);
		m_Brush = new HatchBrush(fillPattern, foreColor, backColor);
		oldBrush->~HatchBrush();
		break;

	//case Gdiplus::BrushTypeSolidColor:
	//case Gdiplus::BrushTypeTextureFill:
	//case Gdiplus::BrushTypePathGradient:
	//case Gdiplus::BrushTypeLinearGradient:
	default:
		// ������ �귯�ô� ������ ������ ���� �����Ƿ� �ƹ� ���۵� ���� ����
		break;
	}
}