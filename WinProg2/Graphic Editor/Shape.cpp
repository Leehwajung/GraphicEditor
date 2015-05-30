// Shape.cpp : CShape 클래스의 구현
// CShape : 2차원 도형 개체를 정의하는 클래스
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


// CShape 멤버 함수

// 펜 획득
Pen* CShape::getPen()
{
	return m_Pen;
}

// 브러시 획득
Brush* CShape::getBrush()
{
	return m_Brush;
}

// 브러시 타입 획득
BrushType CShape::getBrushType()
{
	return m_Brush->GetType();
}

// 윤곽선 색 획득
Color CShape::getOutlineColor()
{
	Color result;
	m_Pen->GetColor(&result);

	return result;
}

// 윤곽선 두께 획득
REAL CShape::getOutlineWidth()
{
	return m_Pen->GetWidth();
}

// 윤곽선 패턴 획득
DashStyle CShape::getOutlinePattern()
{
	return m_Pen->GetDashStyle();
}

// 채우기 색 획득
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
		result = Color(0, 255, 255, 255);	// 텍스쳐 브러시는 색을 가지고 있지 않으므로 투명색 반환
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

// 채우기 패턴 획득
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
		return Gdiplus::HatchStyleHorizontal;	// 나머지 브러시는 패턴을 가지고 있지 않으므로 가로 줄무늬 반환
	}
}

// 펜 설정
void CShape::setPen(IN const Pen* pen)
{
	// 기존 펜 제거
	if (m_Pen) {
		m_Pen->~Pen();
	}

	// 전달받은 펜 복사
	m_Pen = pen->Clone();
}

// 브러시 설정
void CShape::setBrush(IN const Brush* brush)
{
	// 기존 브러시 제거
	if (m_Brush) {
		m_Brush->~Brush();
	}

	// 전달받은 브러시 복사
	m_Brush->Clone();
}

// 윤곽선 색 설정
void CShape::setOutlineColor(IN const Color& outlineColor)
{
	m_Pen->SetColor(outlineColor);
}

// 윤곽선 두께 설정
void CShape::setOutlineWidth(IN const REAL outlineWidth)
{
	m_Pen->SetWidth(outlineWidth);
}

// 윤곽선 패턴 설정
void CShape::setOutlinePattern(IN const DashStyle outlinePattern)
{
	m_Pen->SetDashStyle(outlinePattern);
}

// 칠하기 색 설정
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
		// 텍스쳐 브러시는 색이 없으므로 아무 동작도 하지 않음
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

// 칠하기 패턴 설정
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
		// 나머지 브러시는 패턴을 가지고 있지 않으므로 아무 동작도 하지 않음
		break;
	}
}