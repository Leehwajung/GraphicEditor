// Shape.cpp : CShape Ŭ������ ����
// CShape : 2���� ���� ��ü�� �����ϴ� Ŭ����
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Shape.h"


// CShape

CShape::CShape()
	: m_Pen(Pe)
{
}

CShape::~CShape()
{
}


// CShape ��� �Լ�
Pen& CShape::getPen(){}

void CShape::setPen(const Pen& pen){

}// �� ��ü�� ������ ���� ������ �־�� �ϹǷ� ���ڷ� ���� Pen�� �������� ����
Brush CShape::getBrush(){
}
void CShape::setBrush(const Brush& brush){

}