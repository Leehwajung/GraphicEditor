// Text.cpp : CText 클래스의 구현
// CText : 문자열 개체를 정의하는 클래스
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

// 직렬화
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
//	return create(&startingPoint, &endingPoint, createFlag);	 // 임시 반환 값
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
	//rectSize.Width = m_Font->GetSize();
	//rectSize.Height = m_Font->GetSize();
	rectSize.Width = 60;
	rectSize.Height = 30;
	m_Rect = RectF(*startingPoint, rectSize);
	resetArea();
	cur.x= startingPoint->X;
	cur.y =startingPoint->Y;
	//m_View->CreateSolidCaret(2, m_String.GetSize());
	m_View->CreateSolidCaret(5,25);
	m_View->SetCaretPos(cur);
	m_View->ShowCaret();
	return FALSE;
}

void  CText::increasewidth(){

	//rectSize.Width += m_Font->GetSize();
	//rectSize.Height = m_Font->GetSize();

	rectSize.Width = m_Rect.Width + 20;
	rectSize.Height = 30;

	PointF sp;
	m_Rect.GetLocation(&sp);
	m_Rect = RectF(sp, rectSize);
	resetArea();
	//cur.x = cur.x + m_Font->GetSize();
	cur.x = cur.x + 20;

	m_View->SetCaretPos(cur);
	m_View->ShowCaret(); // 커서이동
}
void CText::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{
	// originPoint: ButtonDown
	// targetPoint: ButtonUp
	PointF offset = targetPoint - originPoint;
	m_Rect.Offset(offset);
	resetArea();
	
	PointF sp;
	m_Rect.GetLocation(&sp);
	m_Rect = RectF(sp, rectSize);
	cur.x = m_Rect.X + m_String.GetSize() * 20;
	cur.y = m_Rect.Y;
	

	m_View->SetCaretPos(cur);
	m_View->ShowCaret(); // 커서이동

}
void  CText::decreasewidth(){
	//rectSize.Width = rectSize.Width-m_Font->GetSize();
	//rectSize.Height = m_Font->GetSize();
	rectSize.Width = rectSize.Width - 20;
	rectSize.Height = 30;

	PointF sp;
	m_Rect.GetLocation(&sp);
	m_Rect = RectF(sp, rectSize);
	resetArea();
	if (cur.x > 0){
		//	cur.x = cur.x - m_Font->GetSize();
		cur.x = cur.x - 20;
	}
	m_View->SetCaretPos(cur);
	m_View->ShowCaret(); // 커서이동
}
// 
void CText::draw(IN Graphics& graphics){
	//FontFamily fontfamily(L"Arial");
	//Gdiplus::Font m_Font(&fontfamily, 16, FontStyleRegular, UnitPixel);
	StringFormat m_StringFormat;
	//SolidBrush blackBrush(Color(255, 0,0, 0));

	// Draw string.
	if (m_String.GetSize() > 0){
		graphics.DrawString(
			m_String.GetData(),
			m_String.GetSize(),
			m_Font,
			m_Rect,
			&m_StringFormat,
			m_FontBrush);
	}
}//CpaintDC 사용


// m_String에 문자 추가
void CText::addChar(TCHAR newchar) {
	m_String.Add(newchar);
	increasewidth();
}

// m_String에 문자 삭제
void CText::delChar() {
	if (m_String.GetSize() > 0) {
		m_String.RemoveAt(m_String.GetSize() - 1);
		decreasewidth();
	}

}

// 뷰 획득
CView* CText::getView() {

	return m_View;
}

// 문자열 획득
CString CText::getString() {

	CString result;
	
	for (int i = 0; i < m_String.GetSize(); i++) {
		result.AppendChar(m_String.GetAt(i));
	}

	return result;
}

// 폰트 획득
Gdiplus::Font* CText::getFont() {

	return m_Font;
}

// 문자열 포맷 획득
StringFormat* CText::getStringFormat() {

	return m_StringFormat;
}

// 글꼴 브러시 획득
BrushPtr CText::getFontBrush() {

	return m_FontBrush;
}

// 주 글꼴 색 획득
Color CText::getFontColor() {

	return getBrushColor(m_FontBrush);
}

// 보조 글꼴 색 획득
Color CText::getFontSubcolor() {

	return getBrushSubcolor(m_FontBrush);
}

// 글꼴 패턴 획득
HatchStyle CText::getFontPattern() {

	return getBrushPattern(m_FontBrush);
}

// 뷰 설정
void CText::setView(CView* lpView) {

	m_View = lpView;
}

// 문자열 설정
void CText::setString(CString& string) {

	m_String.RemoveAll();

	for (int i = 0; i < string.GetLength(); i++) {
		m_String.Add(string.GetAt(i));
	}
}

// 폰트 설정
void CText::setFont(Gdiplus::Font* font) {

	// 이전 Font 객체 삭제
	if (m_Font) {
		m_Font->~Font();
	}

	// Font 객체 복제
	m_Font = font->Clone();
}

// 문자열 포맷 설정
void CText::setStringFormat(StringFormat* stringFormat) {

	// 이전 StringFormat 객체 삭제
	if (m_StringFormat) {
		m_StringFormat->~StringFormat();
	}

	// StringFormat 객체 복제
	m_StringFormat = stringFormat->Clone();
}

// 글꼴 브러시 설정
void CText::setFontBrush(BrushPtr fontBrush) {

	// 이전 Brush 객체 삭제
	if (m_FontBrush) {
		m_FontBrush->~Brush();
	}

	// Brush 객체 복제
	m_FontBrush = fontBrush->Clone();
}

// 주 글꼴 색 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패 (m_FontBrush가 가리키는 객체 없음)
//		FALSE: 설정 성공
BOOL CText::setFontColor(IN const Color& fontColor) {

	return setBrushColor(m_FontBrush, fontColor);
}

// 보조 글꼴 색 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패 (m_FontBrush가 가리키는 객체 없음)
//		FALSE: 설정 성공
BOOL CText::setFontSubcolor(IN const Color& fontSubcolor) {

	return setBrushSubcolor(m_FontBrush, fontSubcolor);
}

// 글꼴 패턴 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패 (m_FontBrush가 가리키는 객체 없음)
//		FALSE: 설정 성공
BOOL CText::setFontPattern(IN const HatchStyle fontPattern) {

	return setBrushPattern(m_FontBrush, fontPattern);
}



//////////////////////////////////////////////////////////////////////

// LButtonDown
//void  CText::create(PointF startingPoint){//Shape의 외곽선생성과 동일함
//	this->startingPoint = startingPoint;
//
//}				

// OnMouseMove
//void  CText::mouseMoveOperation(UINT nFlags, PointF point){// 드래그 중이어야//
//	/* 동작분류 1. creating 모드 2. moving 모드 3. 사이즈변경모드*/
//	
//	operationModeFlags mode = m_OperationMode; // 오페레이션모드에 따라 동작
//
//	switch (mode){
//		//1. Creating 모드//
//	case operationModeFlags::Create:
//		creating(nFlags, point);
//		break;
//		//2. moving 모드//
//	case operationModeFlags::Move:
//		m_View->HideCaret();
//		moving(nFlags, point);
//		break;
//		//3. 사이즈변경모드 /e
//	case operationModeFlags::Resize:
//		m_View->HideCaret();
//		resizing(nFlags, point);
//		break;
//	case operationModeFlags::None:// 선택되지 않은 상태
//		m_View->HideCaret();//캐럿숨기기
//		break;
//	}
//}

///// mouseMoveOperation이 호출에 사용할 함수 (생성 / 이동 / 크기 변경 판단)
//void  CText::creating(void* param1, ...){//생성 그리기
//	// 외곽선 그리기는 shape 함수를 이용 //
//
//}
//void  CText::moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/){// 이동 그리기
//	
//	m_View->HideCaret();//캐럿숨기기
//
//	/*포인터가 Rect영역안에 있는지 없는지를 체크한 후, Rect 안에 클릭된다면*/
//	::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));// 4방향커서로 셋
//	
//	PointF startingPoint;
//	m_Rect.GetLocation(&startingPoint);
//	PointF RelativePoint = PointF(targetPoint - startingPoint);
//	/* 원래 좌표에서 상대 좌표만큼 연산해 이동 결과 좌표를 구한다. */
//		
//}		
//
//void  CText::resizing(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/){// 크기 변경 그리기
//	
//	m_View->HideCaret();//캐럿숨기기
//
//	//일단 도형이 선택된 후, resizing 영역에 들어가면 마우스커서 교체 및 변경작업
//	CRect rect;
//	m_View->GetClientRect(rect);
//	::ClipCursor(rect); // 렉트 영역으로 커서 제한
//	CRect rectHORZ(rect), rectVERT(rect);
//	rectHORZ.DeflateRect(RESIZE_POINT, 0);
//	rectVERT.DeflateRect(0, RESIZE_POINT);
//	CPoint tp;
//	tp.x = targetPoint.X;
//	tp.y = targetPoint.Y;
//	if (rectHORZ.PtInRect(tp)==FALSE){//CPoint 변수를 받아, 영역안에 좌표가 들어와있는 지 체크
//		::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));//west, east 커서
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
// void endCreate(PointF point){}						// 생성 완료
//void   CText::move(PointF originPoint, PointF targetPoint){// 개체 이동
//}							
//void   CText::resize(PointF point, int resizeFlags){// 개체 크기 변경
//
//}			
// LButtonUp
//void CText::endCreate(PointF point){
//	OnKeyboardFocus(point); // <- 이거를 EndCReate로 옮기기.
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
//		m_View->CreateSolidCaret(10,20);// 캐럿 사이즈
//		m_View->SetCaretPos(cur);
//		m_View->ShowCaret();
//	
//}

// http://lab.cliel.com/28  마우스 움직임 제한.
