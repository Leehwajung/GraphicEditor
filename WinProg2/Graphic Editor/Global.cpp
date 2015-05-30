// Global.cpp : CGlobal Ŭ������ ����
// CGlobal : ���� ��� �� ���� �Լ��� �����ϴ� Ŭ����
//

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Global.h"


// CGlobal




// CGlobal ��� �Լ�

const PointF CGlobal::CPointToPointF(const CPoint& point)
{
	PointF tmp_PointF;
	
	tmp_PointF.X = (REAL) point.x;
	tmp_PointF.Y = (REAL) point.y;

	return tmp_PointF;
}

const CPoint CGlobal::PointFToCPoint(const PointF& point)
{
	CPoint tmp_CPoint;

	tmp_CPoint.x = (LONG) point.X;
	tmp_CPoint.y = (LONG) point.Y;

	return tmp_CPoint;
}