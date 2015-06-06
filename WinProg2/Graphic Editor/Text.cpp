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

CText::CText(CView *lpView)
	: m_Font(NULL)
	, m_StringFormat(NULL)
	, m_FontBrush(NULL)
	, m_View(lpView)
{
	
	//m_String.RemoveAll();
}

CText::CText(IN Pen* pen, IN BrushPtr fillbrush)
	: CRectangle(pen, fillbrush)
	, m_Font(NULL)
	, m_StringFormat(NULL)
	, m_FontBrush(NULL)
{


}
CText::CText(IN CView *lpView, IN Pen* pen, IN BrushPtr fillbrush)
	: CRectangle(pen, fillbrush)
	, m_Font(NULL)
	, m_StringFormat(NULL)
	, m_FontBrush(NULL)
	, m_View(lpView)
{
	//m_String.RemoveAll();
}

CText::CText(IN CView *lpView, IN Pen* pen, IN BrushPtr fillbrush, IN RectF layoutrect)
	: CRectangle(pen, fillbrush, layoutrect)
	, m_Font(NULL)
	, m_StringFormat(NULL)
	, m_FontBrush(NULL)
	, m_View(lpView)
{
	//m_String.RemoveAll();
}

CText::CText(IN CView *lpView, IN Pen* pen, IN BrushPtr fillbrush, IN RectF layoutrect, IN Gdiplus::Font* font, IN StringFormat* stringformat, IN BrushPtr fontbrush)
	: CRectangle(pen, fillbrush, layoutrect)
	, m_Font(font->Clone())
	, m_StringFormat(stringformat->Clone())
	, m_FontBrush(fontbrush->Clone())
	, m_View(lpView)
{
	//m_String.RemoveAll();
}

CText::CText(IN CView *lpView, IN Pen* pen, IN BrushPtr fillbrush, IN RectF layoutrect, IN Gdiplus::Font* font, IN StringFormat* stringformat, IN BrushPtr fontbrush, IN CString string)
	: CRectangle(pen, fillbrush, layoutrect)
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
//
//BOOL CText::create(IN PointF startingPoint, IN PointF endingPoint, IN CreateFlag createFlag/* = FREECREATE*/)
//{
//	return create(&startingPoint, &endingPoint, createFlag);	 // �ӽ� ��ȯ ��
//}

BOOL CText::create(void* param1, ...)
{
	va_list vaList;
	va_start(vaList, param1);
	PointF* startingPoint = (PointF*)param1;
	//PointF* endingPoint = va_arg(vaList, PointF*);
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);
	
	SizeF rectSize;
	rectSize.Width = m_Font->GetSize();
	rectSize.Height = m_Font->GetSize();
	//rectSize.Width = 50;
	//rectSize.Height = 50;
	m_Rect = RectF(*startingPoint, rectSize);

	resetArea();
	cur.x=startingPoint->X;
	cur.y = startingPoint->Y;
	m_View->CreateSolidCaret(2, m_String.GetSize());
	//m_View->CreateSolidCaret(5,50);
	m_View->SetCaretPos(cur);
	m_View->ShowCaret();
	return FALSE;
}

void  CText::increasewidth(){
	PointF startingPoint;
	
	rectSize.Width += m_Font->GetSize();
	rectSize.Height = m_Font->GetSize();

	m_Rect = RectF(startingPoint, rectSize);
	resetArea();
	cur.x = cur.x + m_Font->GetSize();
	m_View->SetCaretPos(cur);
	m_View->ShowCaret(); // Ŀ���̵�

}
void  CText::decreasewidth(){
	PointF startingPoint;

	rectSize.Width = rectSize.Width-m_Font->GetSize();
	rectSize.Height = m_Font->GetSize();

	m_Rect = RectF(startingPoint, rectSize);
	resetArea();
	if (cur.x > 0)
		cur.x = cur.x - m_Font->GetSize();
	m_View->SetCaretPos(cur);
	m_View->ShowCaret(); // Ŀ���̵�
}
// 
void CText::draw(IN Graphics* lpGraphics){
	
	lpGraphics->DrawString(
		m_String.GetData(),//�迭�� ù��°�� ���� wchar�� ��ȯ
		m_String.GetSize(),
		m_Font,
		m_Rect,
		m_StringFormat,
		m_FontBrush);
	
}//CpaintDC ���



// m_String�� ���� �߰�
void CText::addChar(TCHAR newchar) {
	m_String.Add(newchar);
	increasewidth();
}

// m_String�� ���� ����
void CText::delChar() {
	if (m_String.GetSize() > 0) {
		m_String.RemoveAt(m_String.GetSize() - 1);
		decreasewidth();
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

CFigure::Position CRectangle::pointInFigure(IN PointF point)
{
	RectF handleRect;

	for (int handleIndex = TOPLEFT; handleIndex <= LEFT; handleIndex++) {

		getHandleRect((Position)handleIndex, &handleRect);
		if (handleRect.Contains(point)) {
			return (Position)handleIndex;
		}
	}

	if (m_Rect.Contains(point)) {
		return INSIDE;
	}

	return OUTSIDE;
}

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
//		//3. ��������� /e
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
//void CText::endCreate(PointF point){
//	OnKeyboardFocus(point); // <- �̰Ÿ� EndCReate�� �ű��.
//	CDC *pDC = m_View->GetDC();
//	Graphics graphics(*pDC);
//	WCHAR string;
//	//graphics.DrawString(WCHAR * string, int length, FONT * font, POINTF &origin, BRUSH *brush);
//
//}

//Keyboard Focus
//void CText::OnKeyboardFocus(PointF point){
//	//CPoint cur(startingPoint.X, startingPoint.Y);
//	PointF startingPoint;
//	m_Rect.GetLocation(&startingPoint);
//	CPoint cur = CGlobal::PointFToCPoint(startingPoint);
//
//		m_View->CreateSolidCaret(10,20);// ĳ�� ������
//		m_View->SetCaretPos(cur);
//		m_View->ShowCaret();
//	
//}

// http://lab.cliel.com/28  ���콺 ������ ����.
