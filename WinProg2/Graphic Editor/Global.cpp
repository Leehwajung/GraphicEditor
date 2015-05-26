// Global.cpp : CGlobal 클래스의 구현
// CGlobal : 전역 상수 및 전역 함수를 정의하는 클래스
//

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Global.h"


// CGlobal




// CGlobal 멤버 함수
const PointF CGlobal::getPointF(const CPoint& point){
	PointF tmp_PointF;
	
	tmp_PointF.X = (REAL) point.x;
	tmp_PointF.Y = (REAL) point.y;

	return tmp_PointF;
}
