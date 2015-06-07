// Global.cpp : CGlobal Ŭ������ ����
// CGlobal : ���� ��� �� ���� �Լ��� �����ϴ� Ŭ����
//

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Global.h"


// CGlobal




// CGlobal ��� �Լ�

PointF CGlobal::CPointToPointF(const CPoint& point)
{
	PointF tmp_PointF;
	
	tmp_PointF.X = (REAL) point.x;
	tmp_PointF.Y = (REAL) point.y;

	return tmp_PointF;
}

CPoint CGlobal::PointFToCPoint(const PointF& point)
{
	CPoint tmp_CPoint;

	tmp_CPoint.x = (LONG) point.X;
	tmp_CPoint.y = (LONG) point.Y;

	return tmp_CPoint;
}

RectF CGlobal::CRectToRectF(const CRect& rect){
	RectF result;

	result.Height = (REAL)rect.Height();
	result.Width = (REAL)rect.Width();
	result.X = (REAL)rect.left;
	result.Y = (REAL)rect.top;

	return result;
}

CRect CGlobal::RectFToCRect(const RectF& rect)
{
	CRect result;

	result.top = (LONG) rect.GetTop();
	result.right = (LONG) rect.GetRight();
	result.bottom = (LONG) rect.GetBottom();
	result.left = (LONG) rect.GetLeft();

	return result;
}


Pen* CGlobal::crateIngPen(IN const Pen* originalPen)
{
	clearIngPen();

	m_BufPen = originalPen->Clone();
	m_BufPen->SetDashStyle(DashStyleCustom);
	REAL aDash[] = { 5.0f, 5.0f };
	m_BufPen->SetDashPattern(aDash, sizeof(aDash) / sizeof(aDash[0]));

	return m_BufPen;
}

Pen* CGlobal::getIngPen()
{
	return m_BufPen;
}

void CGlobal::clearIngPen()
{
	if (m_BufPen) {
		m_BufPen->~Pen();
	}
}

Brush* CGlobal::crateIngBrush(IN const Brush* originalBrush)
{
	clearIngBrush();

	m_BufBrush = originalBrush->Clone();

	const int dn = 2;

	switch (m_BufBrush->GetType())
	{
		case Gdiplus::BrushTypeSolidColor: {
			Color color;
			((SolidBrush*)m_BufBrush)->GetColor(&color);
			((SolidBrush*)m_BufBrush)->SetColor(Color(color.GetA() / dn, color.GetR(), color.GetG(), color.GetB()));
		} break;

		case Gdiplus::BrushTypeHatchFill: {
			HatchBrush* oldBrush = (HatchBrush*)m_BufBrush;
			Color foreColor;
			Color backColor;
			oldBrush->GetForegroundColor(&foreColor);
			oldBrush->GetBackgroundColor(&backColor);
			m_BufBrush = new HatchBrush(
				oldBrush->GetHatchStyle(), 
				Color(foreColor.GetA() / dn, foreColor.GetR(), foreColor.GetG(), foreColor.GetB()), 
				Color(backColor.GetA() / dn, backColor.GetR(), backColor.GetG(), backColor.GetB())
				);
			oldBrush->~HatchBrush();
		} break;

		case Gdiplus::BrushTypeTextureFill: {
			// �ؽ��� �귯�ô� ���� �����Ƿ� �ָ��� �귯�÷� �����Ͽ� ��ȯ
			// ��� �ÿ��� ���� �ؽ�Ʈ �귯�÷� �׸� ��, ���⼭ ��ȯ�Ǵ� �귯�÷� �ٽ� �׷��� ��
			Brush* oldBrush = m_BufBrush;
			m_BufBrush = new SolidBrush(Color(50, 255, 255, 255));
			oldBrush->~Brush();
		} break;

		case Gdiplus::BrushTypePathGradient: {
			Color color;
			((PathGradientBrush*)m_BufBrush)->GetCenterColor(&color);
			((PathGradientBrush*)m_BufBrush)->SetCenterColor(Color(color.GetA() / dn, color.GetR(), color.GetG(), color.GetB()));

			Color* colors = NULL;
			INT count = ((PathGradientBrush*)m_BufBrush)->GetSurroundColorCount();
			((PathGradientBrush*)m_BufBrush)->GetSurroundColors(colors, &count);
			for (int i = 0; i < count; i++){
				colors[i] = Color(colors[i].GetA() / dn, colors[i].GetR(), colors[i].GetG(), colors[i].GetB());
			}
			((PathGradientBrush*)m_BufBrush)->SetSurroundColors(colors, &count);
		} break;

		case Gdiplus::BrushTypeLinearGradient: {
			Color* colors = NULL;
			((LinearGradientBrush*)m_BufBrush)->GetLinearColors(colors);
			((LinearGradientBrush*)m_BufBrush)->SetLinearColors(
				Color(colors[0].GetA() / dn, colors[0].GetR(), colors[0].GetG(), colors[0].GetB()),
				Color(colors[1].GetA() / dn, colors[1].GetR(), colors[1].GetG(), colors[1].GetB())
				);
		} break;
	}

	return m_BufBrush;
}

Brush* CGlobal::getIngBrush()
{
	return m_BufBrush;
}

void CGlobal::clearIngBrush()
{
	if (m_BufBrush) {
		m_BufBrush->~Brush();
	}
}