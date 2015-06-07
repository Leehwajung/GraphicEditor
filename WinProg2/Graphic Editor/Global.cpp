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

	return NULL;
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