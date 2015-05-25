// Shape.cpp : CShape 클래스의 구현
// CShape : 2차원 도형 개체를 정의하는 클래스
// @Author Lee Hwajung 이하와중 니취팔로마
#include "stdafx.h"
#include "Graphic Editor.h"
#include "Shape.h"


// CShape

CShape::CShape()
{
}

CShape::~CShape()
{
}


// CShape 멤버 함수
Pen& CShape::getPen(){}

void CShape::setPen(const Pen& pen){

}// 각 객체가 별도의 펜을 가지고 있어야 하므로 인자로 받은 Pen을 변경하지 않음
Brush CShape::getBrush(){
}
void CShape::setBrush(const Brush& brush){

}