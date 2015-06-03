// Global.cpp : CGlobal 클래스의 구현
// CGlobal : 전역 상수 및 전역 함수를 정의하는 클래스
//

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Global.h"


// CGlobal




// CGlobal 멤버 함수

PointF CGlobal::CPointToPointF(const CPoint& point)
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