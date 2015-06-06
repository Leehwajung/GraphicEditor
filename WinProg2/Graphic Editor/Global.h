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
#define NULLColor Color(0, 255, 255, 255)		// 투명색
#define NULLRectF RectF(0,0,0,0)
#endif // !defaultValue


class CGlobal : public CObject
{
public:
	static PointF CPointToPointF(const CPoint& point);
	static CPoint PointFToCPoint(const PointF& point);
	static CRect RectFToCRect(const RectF& rect);
	static RectF CRectToRectF(const CRect& rect);
};


