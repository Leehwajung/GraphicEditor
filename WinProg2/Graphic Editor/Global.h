// Global.h : CGlobal 클래스의 인터페이스
// CGlobal : 전역 상수 및 전역 함수를 정의하는 클래스
// 

#pragma once
//#include <gdiplus.h>

using namespace Gdiplus;

// CGlobal 명령 대상입니다.

#ifndef defaultValue
#define defaultValue
#define defaultColor Color::Black
#define defaultPen Pen(Color::Black)
#define defaultBrush SolidBrush(Color::Black)  
#define defaultRectF RectF(0,0,0,0)
#endif // !defaultValue


static class CGlobal : public CObject
{
public:
	const static PointF CPointToPointF(const CPoint& point);
};


