// Global.h : CGlobal 클래스의 인터페이스
// CGlobal : 전역 상수 및 전역 함수를 정의하는 클래스
// 

#pragma once
#include <gdiplus.h>

using namespace Gdiplus;

// CGlobal 명령 대상입니다.

#define defaultPen Pen(Color(255,0,0,0))
#define defaultBrush SolidBrush(Color(255, 0, 0, 0))

static class CGlobal : public CObject
{
public:
	
};


