// Shape.cpp : CShape 클래스의 구현
// CShape : 2차원 도형 개체를 정의하는 클래스
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



// CShape 멤버 함수

void CShape::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}


// 펜 획득
Pen* CShape::getOutlinePen()
{
	return this->m_OutlinePen;
}

// 브러시 획득
Brush* CShape::getFillBrush()
{
	return m_FillBrush;
}

// 브러시 타입 획득
BrushType CShape::getBrushType()
{
	return m_FillBrush->GetType();
}

// 윤곽선 색 획득
Color CShape::getOutlineColor()
{
	Color result;
	m_OutlinePen->GetColor(&result);

	return result;
}

// 윤곽선 두께 획득
REAL CShape::getOutlineWidth()
{
	return m_OutlinePen->GetWidth();
}

// 윤곽선 패턴 획득
DashStyle CShape::getOutlinePattern()
{
	return m_OutlinePen->GetDashStyle();
}

// 주 채우기 색 획득
Color CShape::getFillColor()
{
	return getBrushColor(m_FillBrush);
}

// 보조 채우기 색 획득
Color CShape::getFillSubcolor()
{
	return getBrushSubcolor(m_FillBrush);
}

// 채우기 패턴 획득
HatchStyle CShape::getFillPattern()
{
	return getBrushPattern(m_FillBrush);
}

// 펜 설정
void CShape::setOutlinePen(IN const Pen* pen)
{
	// 기존 펜 제거
	if (m_OutlinePen) {
		m_OutlinePen->~Pen();
	}

	// 전달받은 펜 복사
	m_OutlinePen = pen->Clone();
}

// 브러시 설정
void CShape::setFillBrush(IN const Brush* brush, IN BOOL PropertyMaintenanceFlag)
{
	//// 기존 브러시 제거
	//if (m_FillBrush) {
	//	m_FillBrush->~Brush();
	//}
	//
	//// 전달받은 브러시 복사
	//m_FillBrush = brush->Clone();

	setBrush(m_FillBrush, (Brush*)brush, PropertyMaintenanceFlag);
}

// 윤곽선 색 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CShape::setOutlineColor(IN const Color& outlineColor)
{
	return m_OutlinePen->SetColor(outlineColor) ? TRUE : FALSE;
}

// 윤곽선 두께 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CShape::setOutlineWidth(IN const REAL outlineWidth)
{
	return m_OutlinePen->SetWidth(outlineWidth) ? TRUE : FALSE;
}

// 윤곽선 패턴 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CShape::setOutlinePattern(IN const DashStyle outlinePattern)
{
	return m_OutlinePen->SetDashStyle(outlinePattern) ? TRUE : FALSE;
}

// 주 채우기 색 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CShape::setFillColor(IN const Color& fillColor)
{
	return setBrushColor(m_FillBrush, fillColor);
}

// 보조 채우기 색 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CShape::setFillSubcolor(IN const Color& fillSubcolor)
{
	return setBrushSubcolor(m_FillBrush, fillSubcolor);
}

// 채우기 패턴 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CShape::setFillPattern(IN const HatchStyle fillPattern)
{
	return setBrushPattern(m_FillBrush, fillPattern);
}


/*** 보조 함수 ***/
// 주색 획득
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
			((HatchBrush*)brush)->GetBackgroundColor(&result);
			break;
		}

		case Gdiplus::BrushTypeTextureFill: {
			result = NULLColor;	// 텍스쳐 브러시는 색을 가지고 있지 않으므로 투명색 반환
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

// 보조색 획득
Color CShape::getBrushSubcolor(IN BrushPtr brush)
{
	Color result;

	switch (brush->GetType())
	{
		case Gdiplus::BrushTypeSolidColor: {
			result = NULLColor;		// 솔리드 브러시는 보조색이 없으므로 투명색 반환
			break;
		}

		case Gdiplus::BrushTypeHatchFill: {
			((HatchBrush*)brush)->GetBackgroundColor(&result);
			break;
		}

		case Gdiplus::BrushTypeTextureFill: {
			result = NULLColor;		// 텍스쳐 브러시는 색이 없으므로 투명색 반환
			break;
		}

		case Gdiplus::BrushTypePathGradient: {
			Color* colors = NULL;
			INT count = ((PathGradientBrush*)brush)->GetSurroundColorCount();
			((PathGradientBrush*)brush)->GetSurroundColors(colors, &count);
			result = colors[0];		// 색 시퀀스 중에 첫 번째 색 반환 (추후 전체 반환 가능하게 수정 필요)
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

// 패턴 획득
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
			return Gdiplus::HatchStyleHorizontal;	// 나머지 브러시는 패턴이 없으므로 가로 줄무늬 반환
		}
	}
}

// 주색 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
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
			Color foreColor;
			oldBrush->GetForegroundColor(&foreColor);
			brush = new HatchBrush(oldBrush->GetHatchStyle(), foreColor, fillColor);
			oldBrush->~HatchBrush();
			break;
		}

		case Gdiplus::BrushTypeTextureFill: {
			// 텍스쳐 브러시는 색이 없으므로 아무 동작도 하지 않음
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

// 보조색 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CShape::setBrushSubcolor(IN BrushPtr& brush, IN const Color& fillSubcolor)
{
	if (!brush) {
		return TRUE;
	}

	switch (brush->GetType())
	{
		case Gdiplus::BrushTypeSolidColor: {
			// 솔리드 브러시는 보조색이 없으므로 아무 동작도 하지 않음
		} break;

		case Gdiplus::BrushTypeHatchFill: {
			HatchBrush* oldBrush = (HatchBrush*)brush;
			Color backColor;
			oldBrush->GetBackgroundColor(&backColor);
			brush = new HatchBrush(oldBrush->GetHatchStyle(), fillSubcolor, backColor);
			oldBrush->~HatchBrush();
		} break;

		case Gdiplus::BrushTypeTextureFill: {
			// 텍스쳐 브러시는 색이 없으므로 아무 동작도 하지 않음
		} break;

		case Gdiplus::BrushTypePathGradient: {
			PathGradientBrush* pgbrush = ((PathGradientBrush*)brush);
			Color* colors = NULL;
			INT count = pgbrush->GetSurroundColorCount();
			pgbrush->GetSurroundColors(colors, &count);
			colors[0] = fillSubcolor;
			pgbrush->SetSurroundColors(colors, &count);	// 색 시퀀스 중에 첫 번째 색만 설정 (추후 전체 설정 가능하게 수정 필요)
		} break;

		case Gdiplus::BrushTypeLinearGradient: {
			Color* colors = NULL;
			((LinearGradientBrush*)brush)->GetLinearColors(colors);
			((LinearGradientBrush*)brush)->SetLinearColors(colors[0], fillSubcolor);
		} break;
	}

	return FALSE;
}

// 패턴 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
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
		} break;

		//case Gdiplus::BrushTypeSolidColor:
		//case Gdiplus::BrushTypeTextureFill:
		//case Gdiplus::BrushTypePathGradient:
		//case Gdiplus::BrushTypeLinearGradient:
		default: {
			// 나머지 브러시는 패턴을 가지고 있지 않으므로 아무 동작도 하지 않음
			//if (brush) {
			//	brush->~Brush();
			//}
			//brush = new HatchBrush(fillPattern, getBrushColor(brush), getBrushSubcolor(brush));
		} break;
	}

	return FALSE;
}

// 브러시 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CShape::setBrush(IN BrushPtr& brush, IN Brush* srcBrush, IN BOOL PropertyMaintenanceFlag)
{
	if (!brush) {
		return TRUE;
	}

	BrushPtr oldBrush = brush;
	
	// 전달받은 브러시 복사
	brush = srcBrush->Clone();

	// 이전 설정 복원 (설정 유지)
	if (PropertyMaintenanceFlag) {
		if (brush->GetType() != oldBrush->GetType()) {
			//setBrushColor(brush, getBrushColor(oldBrush));
			//setBrushSubcolor(brush, getBrushSubcolor(oldBrush));
			//setBrushPattern(brush, getBrushPattern(oldBrush));

			switch (oldBrush->GetType())
			{
			case Gdiplus::BrushTypeHatchFill:
				setBrushPattern(brush, getBrushPattern(oldBrush));

			case Gdiplus::BrushTypePathGradient:
			case Gdiplus::BrushTypeLinearGradient:
				setBrushSubcolor(brush, getBrushSubcolor(oldBrush));

			case Gdiplus::BrushTypeSolidColor:
				setBrushColor(brush, getBrushColor(oldBrush));

			//case Gdiplus::BrushTypeTextureFill:
				
			}
		}
		else {
			brush->~Brush();
			brush = oldBrush;
			return FALSE;
		}
	}

	// 기존 브러시 제거
	oldBrush->~Brush();

	return FALSE;
}