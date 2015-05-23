// FigureProperties.cpp : CFigureProperties 클래스의 구현
// @Author Lee Hwajung

#include "stdafx.h"
#include "FigureProperties.h"

using namespace Gdiplus;

// CFigureProperties

CFigureProperties::CFigureProperties()
{
}


CFigureProperties::~CFigureProperties()
{
}

// CFigureProperties 멤버 함수

/**
 * return the LineColor
 */
Color CFigureProperties::getLineColor() {
	return m_LineColor;
}

/**
 * param LineColor the LineColor to set
 */
void CFigureProperties::setLineColor(Color LineColor) {
	this->m_LineColor = LineColor;
}

/**
 * return the LinePattern
 */
int CFigureProperties::getLinePattern() {
	return m_LinePattern;
}

/**
 * param Lineint the Lineint to set
 */
void CFigureProperties::setLinePattern(int LinePattern) {
	this->m_LinePattern = LinePattern;
}

/**
 * return the LineWidth
 */
int CFigureProperties::getLineWidth() {
	return m_LineWidth;
}

/**
 * param LineWidth the LineWidth to set
 */
void CFigureProperties::setLineWidth(int LineWidth) {
	this->m_LineWidth = LineWidth;
}

/**
 * return the FillColor
 */
Color CFigureProperties::getFillColor() {
	return m_FillColor;
}

/**
 * param FillColor the FillColor to set
 */
void CFigureProperties::setFillColor(Color FillColor) {
	this->m_FillColor = FillColor;
}

/**
 * return the FillPattern
 */
int CFigureProperties::getFillPattern() {
	return m_FillPattern;
}

/**
 * param Fillint the Fillint to set
 */
void CFigureProperties::setFillPattern(int FillPattern) {
	this->m_FillPattern = FillPattern;
}

/**
* return the FontColor
*/
Color CFigureProperties::getFontColor() {
	return m_FontColor;
}

/**
* param FontColor the FontColor to set
*/
void CFigureProperties::setFontColor(Color FontColor) {
	this->m_FontColor = FontColor;
}

/**
 * return the m_FontLog
 */
LOGFONT CFigureProperties::getFontLog() {
	return m_FontLog;
}

/**
 * param FontLog the m_FontLog to set
 */
void CFigureProperties::setFontLog(LOGFONT FontLog) {
	this->m_FontLog = FontLog;
}