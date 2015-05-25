// FigureProperties.cpp : CFigureProperties 클래스의 구현
// CFigureProperties : 도형 생성을 위한 기본 속성 설정을 저장하는 클래스
// @Author Lee Hwajung
/***************이거 갈아 엎어야 함*************/
#include "stdafx.h"
#include "FigureProperties.h"

using namespace Gdiplus;


// CFigureProperties

IMPLEMENT_SERIAL(CFigureProperties, CObject, 1)

// CFigureProperties 생성/소멸

CFigureProperties::CFigureProperties()
{
}


CFigureProperties::~CFigureProperties()
{
}


// CFigureProperties 멤버 함수

void CFigureProperties::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

/**
 * return the LineColor
 */
Color CFigureProperties::getLineColor() {
	return this->m_LineColor;
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
	return this->m_LinePattern;
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
	return this->m_LineWidth;
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
	return this->m_FillColor;
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
	return this->m_FillPattern;
}

/**
 * param FillPattern the FillPattern to set
 */
void CFigureProperties::setFillPattern(int FillPattern) {
	this->m_FillPattern = FillPattern;
}

/**
* return the FontColor
*/
Color CFigureProperties::getFontColor() {
	return this->m_FontColor;
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
	return this->m_FontLog;
}

/**
 * param FontLog the m_FontLog to set
 */
void CFigureProperties::setFontLog(LOGFONT FontLog) {
	this->m_FontLog = FontLog;
}

/**
* return the FontName
*/
CString CFigureProperties::getFontName() {
	return this->m_FontLog.lfFaceName;
}

/**
* param FontName the FontName to set
*/
void CFigureProperties::setFontName(CString FontName) {
	_tcscpy_s(this->m_FontLog.lfFaceName, LF_FACESIZE/*_countof(this->m_FontLog.lfFaceName)*/, FontName);
}

/**
* return the FontSize
*/
LONG CFigureProperties::getFontSize() {
	return this->m_FontLog.lfHeight;
}

/**
* param FontSize the FontSize to set
*/
void CFigureProperties::setFontSize(LONG FontSize) {
	this->m_FontLog.lfHeight = FontSize;
}

/**
* return the FontBold
*/
BOOL CFigureProperties::getFontBold() {
	return this->m_FontLog.lfWeight;
}

/**
* param FontBold the FontBold to set
*/
void CFigureProperties::setFontBold(BOOL FontBold) {
	this->m_FontLog.lfWeight = FontBold;
}

/**
* return the FontItalic
*/
BOOL CFigureProperties::getFontItalic() {
	return this->m_FontLog.lfItalic;
}

/**
* param FontItalic the FontItalic to set
*/
void CFigureProperties::setFontItalic(BOOL FontItalic) {
	this->m_FontLog.lfItalic = FontItalic;
}

/**
* return the FontUnderline
*/
BOOL CFigureProperties::getFontUnderline() {
	return this->m_FontLog.lfUnderline;
}

/**
* param FontUnderline the FontUnderline to set
*/
void CFigureProperties::setFontUnderline(BOOL FontUnderline) {
	this->m_FontLog.lfUnderline = FontUnderline;
}

/**
* return the FontStrikeOut
*/
BOOL CFigureProperties::getFontStrikeOut() {
	return this->m_FontLog.lfStrikeOut;
}

/**
* param FontStrikeOut the FontStrikeOut to set
*/
void CFigureProperties::setFontStrikeOut(BOOL StrikeOut) {
	this->m_FontLog.lfStrikeOut = StrikeOut;
}