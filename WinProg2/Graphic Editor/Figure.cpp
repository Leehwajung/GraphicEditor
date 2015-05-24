// Figure.cpp : CFigure 클래스의 구현
// CFigure : 클라이언트 영역에서 볼 수 있는 개체를 정의하는 클래스 (모든 개체의 조상 클래스)
// @Author Lee Hwajung

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Figure.h"

using namespace Gdiplus;

// CFigure

CFigure::CFigure()
{
}

CFigure::CFigure(CDC* dc)
{
}

CFigure::~CFigure()
{
}


// CFigure 멤버 함수

/* 개체 생성 */
void CFigure::create(CPoint StartingPoint) {
	this->m_StartingPoint = StartingPoint;
}

/* 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지) */
CFigure::operationModeFlags CFigure::cursorPosition(CPoint point) {
	return None; 
}

/* 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지) */
CFigure::operationModeFlags CFigure::cursorPosition(CRect rect) {
	return None;
}

/* OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단) */
void CFigure::mouseMoveOperation(UINT nFlags, CPoint point) {

}

/* 생성 그리기 */
void CFigure::creating(UINT nFlags, CPoint point) {

}

/* 이동 그리기 */
void CFigure::moving(UINT nFlags, CPoint point) {

}

/* 크기 변경 그리기 */
void CFigure::resizing(UINT nFlags, CPoint point) {

}

/* 점 추가 */
void CFigure::addPoint(CPoint point) {

}

/* 개체 이동 */
void CFigure::move(CPoint Target) {

}

/* 개체 크기 변경 */
void CFigure::resize(CPoint Point, CPoint* anchorPoint /*= NULL*/, int resizeFlags /*= Free*/) {

	if (!anchorPoint) {
		anchorPoint = &m_StartingPoint;
	}
}

/* 설정된 값으로 개체 속성 설정 */
void CFigure::setProperties(CFigureProperties properties) {

}

/* 개체 그리기 */
void CFigure::draw() {

}

/* 개체 선택선 그리기 */
void CFigure::drawSelect() {
	
}

/* 개체 삭제 */
void CFigure::destroy() {

}

/* 윤곽선 색 설정 */
void CFigure::setLineColor(Color LineColor) {

}

/* 윤곽선 두께 설정 */
void CFigure::setLineWidth(int LineWidth) {

}

/* 윤곽선 패턴 설정 */
void CFigure::setLinePattern(int LinePattern) {

}

/* 칠하기 색 설정 */
void CFigure::setFillColor(Color FillColor) {

}

/* 칠하기 패턴 설정 */
void CFigure::setFillPattern(int FillPattern) {

}


/* Getter / Setter */

CDC* CFigure::getDC() {
	return this->m_lpdc;
}

void CFigure::setDC(CDC* dc) {
	this->m_lpdc = dc;
}

CPoint& CFigure::getStartingPoint() {
	return this->m_StartingPoint;
}

void CFigure::setStartingPoint(CPoint StartingPoint) {
	this->m_StartingPoint = StartingPoint;
}

CFigure::operationModeFlags CFigure::getOperationMode() {
	return this->m_OperationMode;
}

void CFigure::setOperationMode(operationModeFlags OperationMode) {
	this->m_OperationMode = OperationMode;
}