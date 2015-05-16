#include "stdafx.h"
#include "FigureSetting.h"


CFigureSetting::CFigureSetting()
{
}


CFigureSetting::~CFigureSetting()
{
}

/**
 * return the LineColor
 */
Color CFigureSetting::getLineColor() {
	return m_LineColor;
}

/**
 * param LineColor the LineColor to set
 */
void CFigureSetting::setLineColor(Color LineColor) {
	this->m_LineColor = LineColor;
}

/**
 * return the LinePattern
 */
int CFigureSetting::getLinePattern() {
	return m_LinePattern;
}

/**
 * param LinePattern the LinePattern to set
 */
void CFigureSetting::setLinePattern(int LinePattern) {
	this->m_LinePattern = LinePattern;
}

/**
 * return the LineWidth
 */
int CFigureSetting::getLineWidth() {
	return m_LineWidth;
}

/**
 * param LineWidth the LineWidth to set
 */
void CFigureSetting::setLineWidth(int LineWidth) {
	this->m_LineWidth = LineWidth;
}

/**
 * return the FillColor
 */
Color CFigureSetting::getFillColor() {
	return m_FillColor;
}

/**
 * param FillColor the FillColor to set
 */
void CFigureSetting::setFillColor(Color FillColor) {
	this->m_FillColor = FillColor;
}

/**
 * return the FillPattern
 */
int CFigureSetting::getFillPattern() {
	return m_FillPattern;
}

/**
 * param FillPattern the FillPattern to set
 */
void CFigureSetting::setFillPattern(int FillPattern) {
	this->m_FillPattern = FillPattern;
}

/**
 * return the FontName
 */
CString CFigureSetting::getFontName() {
	return m_FontName;
}

/**
 * param FontName the FontName to set
 */
void CFigureSetting::setFontName(CString FontName) {
	this->m_FontName = FontName;
}

/**
 * return the FontSize
 */
int CFigureSetting::getFontSize() {
	return m_FontSize;
}

/**
 * param FontSize the FontSize to set
 */
void CFigureSetting::setFontSize(int FontSize) {
	this->m_FontSize = FontSize;
}

/**
 * return the FontBold
 */
BOOL CFigureSetting::getFontBold() {
	return m_FontBold;
}

/**
 * param FontBold the FontBold to set
 */
void CFigureSetting::setFontBold(BOOL FontBold) {
	this->m_FontBold = FontBold;
}

/**
 * return the FontItalic
 */
BOOL CFigureSetting::getFontItalic() {
	return m_FontItalic;
}

/**
 * param FontItalic the FontItalic to set
 */
void CFigureSetting::setFontItalic(BOOL FontItalic) {
	this->m_FontItalic = FontItalic;
}

/**
 * return the FontUnderline
 */
BOOL CFigureSetting::getFontUnderline() {
	return m_FontUnderline;
}

/**
 * param FontUnderline the FontUnderline to set
 */
void CFigureSetting::setFontUnderline(BOOL FontUnderline) {
	this->m_FontUnderline = FontUnderline;
}