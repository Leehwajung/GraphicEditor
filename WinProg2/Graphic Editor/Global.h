// Global.h : CGlobal Ŭ������ �������̽�
// CGlobal : ���� ��� �� ���� �Լ��� �����ϴ� Ŭ����
// 

#pragma once
//#include <gdiplus.h>

using namespace Gdiplus;

// CGlobal ��� ����Դϴ�.

#ifndef defaultValue
#define defaultValue
#define defaultColor Color::Black
#define defaultPen Pen(Color::Black)
#define defaultBrush SolidBrush(Color::Black)
#define NULLColor Color(0, 255, 255, 255)		// �����
#define NULLRectF RectF(0,0,0,0)
#endif // !defaultValue


class CGlobal : public CObject
{
public:
	const static PointF CPointToPointF(const CPoint& point);
	const static CPoint PointFToCPoint(const PointF& point);
};


