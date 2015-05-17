// FigureProperties.cpp : CFigureProperties 클래스의 구현
//

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
 * param LinePattern the LinePattern to set
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
 * param FillPattern the FillPattern to set
 */
void CFigureProperties::setFillPattern(int FillPattern) {
	this->m_FillPattern = FillPattern;
}

/**
 * return the FontName
 */
CString CFigureProperties::getFontName() {
	return m_FontName;
}

/**
 * param FontName the FontName to set
 */
void CFigureProperties::setFontName(CString FontName) {
	this->m_FontName = FontName;
}

/**
 * return the FontSize
 */
int CFigureProperties::getFontSize() {
	return m_FontSize;
}

/**
 * param FontSize the FontSize to set
 */
void CFigureProperties::setFontSize(int FontSize) {
	this->m_FontSize = FontSize;
}

/**
 * return the FontBold
 */
BOOL CFigureProperties::getFontBold() {
	return m_FontBold;
}

/**
 * param FontBold the FontBold to set
 */
void CFigureProperties::setFontBold(BOOL FontBold) {
	this->m_FontBold = FontBold;
}

/**
 * return the FontItalic
 */
BOOL CFigureProperties::getFontItalic() {
	return m_FontItalic;
}

/**
 * param FontItalic the FontItalic to set
 */
void CFigureProperties::setFontItalic(BOOL FontItalic) {
	this->m_FontItalic = FontItalic;
}

/**
 * return the FontUnderline
 */
BOOL CFigureProperties::getFontUnderline() {
	return m_FontUnderline;
}

/**
 * param FontUnderline the FontUnderline to set
 */
void CFigureProperties::setFontUnderline(BOOL FontUnderline) {
	this->m_FontUnderline = FontUnderline;
}