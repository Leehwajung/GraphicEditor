// Text.cpp : CText Ŭ������ ����
// CText : ���ڿ� ��ü�� �����ϴ� Ŭ����
//

#include "stdafx.h"
#include "Text.h"

// http://warmz.tistory.com/862 CDC

// CText

IMPLEMENT_SERIAL(CText, CRectangle, 1)

CText::CText()
	: CRectangle()
	, m_Font(NULL)
	, m_StringFormat(NULL)
	, m_FontBrush()
{
	//m_String.RemoveAll();
}

CText::CText(IN CClientDC* lpClientDC)
	: CRectangle(lpClientDC)
	, m_Font(NULL)
	, m_StringFormat(NULL)
	, m_FontBrush()
{
	//m_String.RemoveAll();
}

//CText::CText(IN Graphics* lpGraphics)
//	: CRectangle(lpGraphics)
//	, m_Font(NULL)
//	, m_StringFormat(NULL)
//	, m_FontBrush()
//{
//	//m_String.RemoveAll();
//}
//
//CText::CText(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr fillbrush)
//	: CRectangle(lpClientDC, pen, fillbrush)
//	, m_Font(NULL)
//	, m_StringFormat(NULL)
//	, m_FontBrush()
//{
//	//m_String.RemoveAll();
//}
//
//CText::CText(IN Graphics* lpGraphics, IN Pen* pen, IN BrushPtr fillbrush)
//	: CRectangle(lpGraphics, pen, fillbrush)
//	, m_Font(NULL)
//	, m_StringFormat(NULL)
//	, m_FontBrush()
//{
//	//m_String.RemoveAll();
//}
//
//CText::CText(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr fillbrush, IN RectF layoutrect)
//	: CRectangle(lpClientDC, pen, fillbrush, layoutrect)
//	, m_Font(NULL)
//	, m_StringFormat(NULL)
//	, m_FontBrush()
//{
//	//m_String.RemoveAll();
//}
//
//CText::CText(IN Graphics* lpGraphics, IN Pen* pen, IN BrushPtr fillbrush, IN RectF layoutrect)
//	: CRectangle(lpGraphics, pen, fillbrush, layoutrect)
//	, m_Font(NULL)
//	, m_StringFormat(NULL)
//	, m_FontBrush()
//{
//	//m_String.RemoveAll();
//}

CText::CText(CView *lpView)
	: CRectangle(&CClientDC(lpView))
	, m_Font(NULL)
	, m_StringFormat(NULL)
	, m_FontBrush(NULL)
	, m_View(lpView)
{
	
	//m_String.RemoveAll();
}

CText::CText(IN CView *lpView, IN Pen* pen, IN BrushPtr fillbrush)
	: CRectangle(&CClientDC(lpView), pen, fillbrush)
	, m_Font(NULL)
	, m_StringFormat(NULL)
	, m_FontBrush(NULL)
	, m_View(lpView)
{
	//m_String.RemoveAll();
}

CText::CText(IN CView *lpView, IN Pen* pen, IN BrushPtr fillbrush, IN RectF layoutrect)
	: CRectangle(&CClientDC(lpView), pen, fillbrush, layoutrect)
	, m_Font(NULL)
	, m_StringFormat(NULL)
	, m_FontBrush(NULL)
	, m_View(lpView)
{
	//m_String.RemoveAll();
}

CText::CText(IN CView *lpView, IN Pen* pen, IN BrushPtr fillbrush, IN RectF layoutrect, IN Gdiplus::Font* font, IN StringFormat* stringformat, IN BrushPtr fontbrush)
	: CRectangle(&CClientDC(lpView), pen, fillbrush, layoutrect)
	, m_Font(font->Clone())
	, m_StringFormat(stringformat->Clone())
	, m_FontBrush(fontbrush->Clone())
	, m_View(lpView)
{
	//m_String.RemoveAll();
}

CText::CText(IN CView *lpView, IN Pen* pen, IN BrushPtr fillbrush, IN RectF layoutrect, IN Gdiplus::Font* font, IN StringFormat* stringformat, IN BrushPtr fontbrush, IN CString string)
	: CRectangle(&CClientDC(lpView), pen, fillbrush, layoutrect)
	, m_Font(font->Clone())
	, m_StringFormat(stringformat->Clone())
	, m_FontBrush(fontbrush->Clone())
	, m_View(lpView)
{
	for (int i = 0; i < string.GetLength(); i++) {
		m_String.Add(string.GetAt(i));
	}
}

CText::~CText()//delete
{
	if (m_Font) {
		m_Font->~Font();
	}

	if (m_StringFormat) {
		m_StringFormat->~StringFormat();
	}

	if (m_FontBrush) {
		m_FontBrush->~Brush();
	}
}

// ����ȭ
void CText::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

// OnDraw / OnPaint
void CText::draw(){
	RectF rect;
	CFont character;
	CClientDC* lpDC = getClientDC();

}//CpaintDC ���


//////////////////////////////////////////////////////////////////////

// LButtonDown
//void  CText::create(PointF startingPoint){//Shape�� �ܰ��������� ������
//	this->startingPoint = startingPoint;
//
//}				

// OnMouseMove
//void  CText::mouseMoveOperation(UINT nFlags, PointF point){// �巡�� ���̾��//
//	/* ���ۺз� 1. creating ��� 2. moving ��� 3. ���������*/
//	
//	operationModeFlags mode = m_OperationMode; // ���䷹�̼Ǹ�忡 ���� ����
//
//	switch (mode){
//		//1. Creating ���//
//	case operationModeFlags::Create:
//		creating(nFlags, point);
//		break;
//		//2. moving ���//
//	case operationModeFlags::Move:
//		m_View->HideCaret();
//		moving(nFlags, point);
//		break;
//		//3. ��������� /
//	case operationModeFlags::Resize:
//		m_View->HideCaret();
//		resizing(nFlags, point);
//		break;
//	case operationModeFlags::None:// ���õ��� ���� ����
//		m_View->HideCaret();//ĳ�������
//		break;
//	}
//}

///// mouseMoveOperation�� ȣ�⿡ ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�)
//void  CText::creating(void* param1, ...){//���� �׸���
//	// �ܰ��� �׸���� shape �Լ��� �̿� //
//
//}
//void  CText::moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/){// �̵� �׸���
//	
//	m_View->HideCaret();//ĳ�������
//
//	/*�����Ͱ� Rect�����ȿ� �ִ��� �������� üũ�� ��, Rect �ȿ� Ŭ���ȴٸ�*/
//	::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));// 4����Ŀ���� ��
//	
//	PointF startingPoint;
//	m_Rect.GetLocation(&startingPoint);
//	PointF RelativePoint = PointF(targetPoint - startingPoint);
//	/* ���� ��ǥ���� ��� ��ǥ��ŭ ������ �̵� ��� ��ǥ�� ���Ѵ�. */
//		
//}		
//
//void  CText::resizing(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/){// ũ�� ���� �׸���
//	
//	m_View->HideCaret();//ĳ�������
//
//	//�ϴ� ������ ���õ� ��, resizing ������ ���� ���콺Ŀ�� ��ü �� �����۾�
//	CRect rect;
//	m_View->GetClientRect(rect);
//	::ClipCursor(rect); // ��Ʈ �������� Ŀ�� ����
//	CRect rectHORZ(rect), rectVERT(rect);
//	rectHORZ.DeflateRect(RESIZE_POINT, 0);
//	rectVERT.DeflateRect(0, RESIZE_POINT);
//	CPoint tp;
//	tp.x = targetPoint.X;
//	tp.y = targetPoint.Y;
//	if (rectHORZ.PtInRect(tp)==FALSE){//CPoint ������ �޾�, �����ȿ� ��ǥ�� �����ִ� �� üũ
//		::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));//west, east Ŀ��
//		m_RESIZE = HORZ;
//	}
//	else if (rectVERT.PtInRect(tp) == FALSE){
//		::SetCursor(::LoadCursor(NULL, IDC_SIZENS));
//		m_RESIZE = VERT;
//	}
//	else
//	{
//		m_RESIZE = NONE;
//	}
//	
//	PointF startingPoint;
//	m_Rect.GetLocation(&startingPoint);
//	PointF RelativePoint = PointF(targetPoint - startingPoint);
//	m_View->ClientToScreen(rect);
//	switch (m_RESIZE){
//	case NONE:
//		rect.OffsetRect(RelativePoint.X, RelativePoint.Y);
//		break;
//	case HORZ:
//		rect.InflateRect(RelativePoint.X, 0);
//		break;
//	case VERT:
//		rect.InflateRect(0, RelativePoint.Y);
//		break;
//	}
//	rect.NormalizeRect();
//}			

///////////////////////////////////////////////////////////////////////
// LButtonUp / LButtonDlk
// void endCreate(PointF point){}						// ���� �Ϸ�
//void   CText::move(PointF originPoint, PointF targetPoint){// ��ü �̵�
//}							
//void   CText::resize(PointF point, int resizeFlags){// ��ü ũ�� ����
//
//}			
// LButtonUp
void CText::endCreate(PointF point){
	OnKeyboardFocus(point); // <- �̰Ÿ� EndCReate�� �ű��.
	CDC *pDC = m_View->GetDC();
	Graphics graphics(*pDC);
	WCHAR string;
	//graphics.DrawString(WCHAR * string, int length, FONT * font, POINTF &origin, BRUSH *brush);

}

//Keyboard Focus
void CText::OnKeyboardFocus(PointF point){
	//CPoint cur(startingPoint.X, startingPoint.Y);
	PointF startingPoint;
	m_Rect.GetLocation(&startingPoint);
	CPoint cur = CGlobal::PointFToCPoint(startingPoint);

		m_View->CreateSolidCaret(10,20);// ĳ�� ������
		m_View->SetCaretPos(cur);
		m_View->ShowCaret();
		character_mode = TRUE; // ĳ���� �Է¸��
}

// http://lab.cliel.com/28  ���콺 ������ ����.


// m_String�� ���� �߰�
void CText::addChar(TCHAR newchar) {
	// [backspace] Ű �Է� �� �� ������ ���ڸ� �����Ѵ�.
	if (newchar == _T('\b')) {
		if (m_String.GetSize() > 0) {
			m_String.RemoveAt(m_String.GetSize() - 1);
		}
	}

	// �� ���� ��쿡�� ���� �迭�� ���ڸ� �߰��Ѵ�.
	else {
		m_String.Add(newchar);
	}
	
}

// �� ȹ��
CView* CText::getView() {

	return m_View;
}

// ���ڿ� ȹ��
CString CText::getString() {

	CString result;
	
	for (int i = 0; i < m_String.GetSize(); i++) {
		result.AppendChar(m_String.GetAt(i));
	}

	return result;
}

// ��Ʈ ȹ��
Gdiplus::Font* CText::getFont() {

	return m_Font;
}

// ���ڿ� ���� ȹ��
StringFormat* CText::getStringFormat() {

	return m_StringFormat;
}

// �۲� �귯�� ȹ��
BrushPtr CText::getFontBrush() {

	return m_FontBrush;
}

// �� �۲� �� ȹ��
Color CText::getFontColor() {

	return getBrushColor(m_FontBrush);
}

// ���� �۲� �� ȹ��
Color CText::getFontSubcolor() {

	return getBrushSubcolor(m_FontBrush);
}

// �۲� ���� ȹ��
HatchStyle CText::getFontPattern() {

	return getBrushPattern(m_FontBrush);
}

// �� ����
void CText::setView(CView* lpView) {

	m_View = lpView;
}

// ���ڿ� ����
void CText::setString(CString& string) {

	m_String.RemoveAll();

	for (int i = 0; i < string.GetLength(); i++) {
		m_String.Add(string.GetAt(i));
	}
}

// ��Ʈ ����
void CText::setFont(Gdiplus::Font* font) {

	// ���� Font ��ü ����
	if (m_Font) {
		m_Font->~Font();
	}

	// Font ��ü ����
	m_Font = font->Clone();
}

// ���ڿ� ���� ����
void CText::setStringFormat(StringFormat* stringFormat) {

	// ���� StringFormat ��ü ����
	if (m_StringFormat) {
		m_StringFormat->~StringFormat();
	}

	// StringFormat ��ü ����
	m_StringFormat = stringFormat->Clone();
}

// �۲� �귯�� ����
void CText::setFontBrush(BrushPtr fontBrush) {

	// ���� Brush ��ü ����
	if (m_FontBrush) {
		m_FontBrush->~Brush();
	}

	// Brush ��ü ����
	m_FontBrush = fontBrush->Clone();
}

// �� �۲� �� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ���� (m_FontBrush�� ����Ű�� ��ü ����)
//		FALSE: ���� ����
BOOL CText::setFontColor(IN const Color& fontColor) {

	return setBrushColor(m_FontBrush, fontColor);
}

// ���� �۲� �� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ���� (m_FontBrush�� ����Ű�� ��ü ����)
//		FALSE: ���� ����
BOOL CText::setFontSubcolor(IN const Color& fontSubcolor) {

	return setBrushSubcolor(m_FontBrush, fontSubcolor);
}

// �۲� ���� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ���� (m_FontBrush�� ����Ű�� ��ü ����)
//		FALSE: ���� ����
BOOL CText::setFontPattern(IN const HatchStyle fontPattern) {

	return setBrushPattern(m_FontBrush, fontPattern);
}

