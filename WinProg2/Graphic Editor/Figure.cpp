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

CFigure::CFigure(CClientDC* lpClientDC/*, PointF startingPoint*/)
	: m_lpGraphics(new Graphics(*lpClientDC))
	//, m_StartingPoint(startingPoint)
{
}

CFigure::CFigure(Graphics* lpGraphics/*, PointF startingPoint*/)
	: m_lpGraphics(lpGraphics)
	//, m_StartingPoint(startingPoint)
{
}

CFigure::~CFigure()
{
}


// CFigure 멤버 함수

/* 개체 생성 */
void CFigure::create(PointF StartingPoint) {
	this->m_StartingPoint = StartingPoint;
}

/* 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지) */
CFigure::operationModeFlags CFigure::cursorPosition(PointF point) {
	return None; 
}

/* 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지) */
CFigure::operationModeFlags CFigure::cursorPosition(RectF rect) {
	return None;
}

/* OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단) */
void CFigure::mouseMoveOperation(UINT nFlags, PointF point) {

}

/* 생성 그리기 */
void CFigure::creating(UINT nFlags, PointF point) {

}

/* 이동 그리기 */
void CFigure::moving(UINT nFlags, PointF point) {

}

/* 크기 변경 그리기 */
void CFigure::resizing(UINT nFlags, PointF point) {

}

/* 생성 완료 */
void CFigure::endCreate(PointF point) {

}

/* 개체 이동 */
void CFigure::move(PointF originPoint, PointF targetPoint) {

}

/* 개체 크기 변경 */
void CFigure::resize(PointF Point, PointF* anchorPoint /*= NULL*/, int resizeFlags /*= Free*/) {

	//if (!anchorPoint) {
	//	anchorPoint = &m_StartingPoint;
	//}
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
void CFigure::setLineColor(const Color& LineColor) {

}

/* 윤곽선 두께 설정 */
void CFigure::setLineWidth(const REAL& LineWidth) {

}

/* 윤곽선 패턴 설정 */
void CFigure::setLinePattern(const DashStyle& LinePattern) {

}

/* 칠하기 색 설정 */
void CFigure::setFillColor(const Color& FillColor) {

}

/* 칠하기 패턴 설정 */
void CFigure::setFillPattern(const int FillPattern) {

}


/* Getter / Setter */

Graphics* CFigure::getGraphics() {
	return this->m_lpGraphics;
}

void CFigure::setGraphics(Graphics* lpGraphics) {
	this->m_lpGraphics = lpGraphics;
}

PointF& CFigure::getStartingPoint() {
	return this->m_StartingPoint;
}

void CFigure::setStartingPoint(PointF& StartingPoint) {
	this->m_StartingPoint = StartingPoint;	// 복사 생성자 불림
}

CFigure::operationModeFlags CFigure::getOperationMode() {
	return this->m_OperationMode;
}

void CFigure::setOperationMode(operationModeFlags OperationMode) {
	this->m_OperationMode = OperationMode;
}