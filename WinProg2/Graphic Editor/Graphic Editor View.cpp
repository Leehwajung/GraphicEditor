// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를 
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된 
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해 
// 추가적으로 제공되는 내용입니다.  
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.  
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// Graphic Editor View.cpp : CGraphicEditorView 클래스의 구현 (작업, 재정의, (명령 메시지 이외의) 메시지 처리기)
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Graphic Editor.h"
#endif

#include "Graphic Editor Doc.h"
#include "Graphic Editor View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//#include "Text.h"

// CGraphicEditorView

IMPLEMENT_DYNCREATE(CGraphicEditorView, CView)

BEGIN_MESSAGE_MAP(CGraphicEditorView, CView)
	/* 메시지 처리기 */
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_KEYUP()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSCHAR()
	ON_WM_SYSKEYUP()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CONTEXTMENU()

	/* 명령 메시지 처리기 */
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphicEditorView::OnFilePrintPreview)

	//ON_COMMAND(ID_EDIT_COPY, &CGraphicEditorView::OnEditClear)
	//ON_COMMAND(ID_EDIT_COPY, &CGraphicEditorView::OnEditClearAll)
	ON_COMMAND(ID_EDIT_COPY, &CGraphicEditorView::OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, &CGraphicEditorView::OnEditCut)
	//ON_COMMAND(ID_EDIT_PASTE, &CGraphicEditorView::OnEditFind)
	ON_COMMAND(ID_EDIT_PASTE, &CGraphicEditorView::OnEditPaste)
	ON_COMMAND(ID_EDIT_DELETE, &CGraphicEditorView::OnEditDelete)
	//ON_COMMAND(ID_EDIT_DELETE, &CGraphicEditorView::OnEditRepeat)
	//ON_COMMAND(ID_EDIT_DELETE, &CGraphicEditorView::OnEditReplace)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CGraphicEditorView::OnEditSelectAll)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CGraphicEditorView::OnEditUndo)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CGraphicEditorView::OnEditRedo)
	ON_COMMAND(ID_IMAGE_CANVAS_SIZE, &CGraphicEditorView::OnImageCanvasSize)
	ON_COMMAND(ID_INSERT_LINE, &CGraphicEditorView::OnInsertLine)
	ON_UPDATE_COMMAND_UI(ID_INSERT_LINE, &CGraphicEditorView::OnUpdateInsertLine)
	ON_COMMAND(ID_INSERT_POLYLINE, &CGraphicEditorView::OnInsertPolyline)
	ON_UPDATE_COMMAND_UI(ID_INSERT_POLYLINE, &CGraphicEditorView::OnUpdateInsertPolyline)
	ON_COMMAND(ID_INSERT_PENCIL, &CGraphicEditorView::OnInsertPencil)
	ON_UPDATE_COMMAND_UI(ID_INSERT_PENCIL, &CGraphicEditorView::OnUpdateInsertPencil)
	ON_COMMAND(ID_INSERT_CURVE, &CGraphicEditorView::OnInsertCurve)
	ON_UPDATE_COMMAND_UI(ID_INSERT_CURVE, &CGraphicEditorView::OnUpdateInsertCurve)
	ON_COMMAND(ID_INSERT_ELLIPSE, &CGraphicEditorView::OnInsertEllipse)
	ON_UPDATE_COMMAND_UI(ID_INSERT_ELLIPSE, &CGraphicEditorView::OnUpdateInsertEllipse)
	ON_COMMAND(ID_INSERT_RECTANGLE, &CGraphicEditorView::OnInsertRectangle)
	ON_UPDATE_COMMAND_UI(ID_INSERT_RECTANGLE, &CGraphicEditorView::OnUpdateInsertRectangle)
	ON_COMMAND(ID_INSERT_STRING, &CGraphicEditorView::OnInsertString)
	ON_UPDATE_COMMAND_UI(ID_INSERT_STRING, &CGraphicEditorView::OnUpdateInsertString)
	ON_COMMAND(ID_INSERT_POLYGON, &CGraphicEditorView::OnInsertPolygon)
	ON_UPDATE_COMMAND_UI(ID_INSERT_POLYGON, &CGraphicEditorView::OnUpdateInsertPolygon)
	ON_COMMAND(ID_INSERT_CLOSEDCURVE, &CGraphicEditorView::OnInsertClosedcurve)
	ON_UPDATE_COMMAND_UI(ID_INSERT_CLOSEDCURVE, &CGraphicEditorView::OnUpdateInsertClosedcurve)
	ON_COMMAND(ID_ARRANGE_ORDER, &CGraphicEditorView::OnArrangeOrder)
	ON_COMMAND(ID_ARRANGE_BRING_FRONT, &CGraphicEditorView::OnArrangeBringFront)
	ON_COMMAND(ID_ARRANGE_SEND_BACK, &CGraphicEditorView::OnArrangeSendBack)
	ON_COMMAND(ID_ARRANGE_BRING_FORWARD, &CGraphicEditorView::OnArrangeBringForward)
	ON_COMMAND(ID_ARRANGE_SEND_BACKWARD, &CGraphicEditorView::OnArrangeSendBackward)
	ON_COMMAND(ID_ARRANGE_GROUPING, &CGraphicEditorView::OnArrangeGrouping)
	ON_COMMAND(ID_ARRANGE_GROUP, &CGraphicEditorView::OnArrangeGroup)
	ON_UPDATE_COMMAND_UI(ID_ARRANGE_GROUP, &CGraphicEditorView::OnUpdateArrangeGroup)
	ON_COMMAND(ID_ARRANGE_UNGROUP, &CGraphicEditorView::OnArrangeUngroup)
	ON_UPDATE_COMMAND_UI(ID_ARRANGE_UNGROUP, &CGraphicEditorView::OnUpdateArrangeUngroup)
	ON_COMMAND(ID_ZOOM_IN, &CGraphicEditorView::OnZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, &CGraphicEditorView::OnZoomOut)
	ON_COMMAND(ID_ZOOM_100, &CGraphicEditorView::OnZoom100)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_100, &CGraphicEditorView::OnUpdateZoom100)
END_MESSAGE_MAP()


/*** CGraphicEditorView 생성/소멸 ***/

CGraphicEditorView::CGraphicEditorView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_CurrentFigure = NULL;
	m_MouseButtonFlag = NBUTTON;
	m_InsertFlag = NONE;
}

CGraphicEditorView::~CGraphicEditorView()
{
}


/*** CGraphicEditorView 가상 함수 ***/

BOOL CGraphicEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGraphicEditorView 그리기
void CGraphicEditorView::OnDraw(CDC* pDC)
{
	// GDI+			https://msdn.microsoft.com/en-us/library/windows/desktop/ms533798(v=vs.85).aspx
	// GDI+ Ref.	https://msdn.microsoft.com/en-us/library/windows/desktop/ms533799(v=vs.85).aspx
	// GDI+ Classes	https://msdn.microsoft.com/en-us/library/windows/desktop/ms533958(v=vs.85).aspx

	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	m_pDC = (CClientDC*) pDC;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.


	//////////////////////////////////////////////// 여기서부터 예제 코드 ///////////////////////////////////////////////////////
	Graphics graphics(*pDC);	// gdi+ 그리기를 위한 객체 https://msdn.microsoft.com/en-us/library/windows/desktop/ms534453(v=vs.85).aspx
	//if (m_InsertFlag == LINE)

	if (m_CurrentFigure) {
		m_CurrentFigure->draw(&graphics);
	}


	/*int */m_mode = 0;// 일단 모드라고 해놓겠음. // 일단 컴파일 에러로 임의 값 설정해둠.
	switch(m_mode){
		case 1: // 폴리라인
			break;
		case 2: // 도형
			break;
		case 3 :// 텍스트
		
			break;
	// view 객체 넘겨서? 받아서 각각 함수에서 다 처리하는 방식으로 하자는 거지??
	// Graphics 포인터를 멤버 변수(m_lpGraphics)로 둬서 각 개체 클래스에서 그리기를 정의하고, 그 함수를 호출하는 방식으로 할거야

	}
	
	// GDI+ 예제 코드 (사각형 그리기)
	SolidBrush sb(Color(255,255,0,0));
	graphics.FillRectangle(&sb, Rect(33, 44, 55, 66));

	// Set up the arc.
	Pen redPen(Color(255, 255, 0, 0), 3);
	RectF ellipseRect(0, 0, 200, 100);
	REAL startAngle = 0.0f;
	REAL sweepAngle = 90.0f;

	// Draw the arc.
	graphics.DrawArc(&redPen, ellipseRect, startAngle, sweepAngle);

	// 문자열 출력 테스트
	// Create a string.
	WCHAR string[] = L"Sample Text";

	// Initialize arguments.
	FontFamily fontfamily(L"Arial");
	Gdiplus::Font myFont(&fontfamily, 16, FontStyleRegular, UnitPixel);
	RectF layoutRect(100.0f, 0.0f, 200.0f, 50.0f);
	StringFormat format;
	SolidBrush blackBrush(Color(255, 255, 0, 0));

	// Draw string.
	graphics.DrawString(
		string,
		11,
		&myFont,
		layoutRect,
		&format,
		&blackBrush);

	// Draw layoutRect.
	graphics.DrawRectangle(&Pen(Color::Blue, 3), layoutRect);
	///////////////////////////////// 여기까지 예제 코드 ///////////////////////////////////////////////////////////////
}


/*** CGraphicEditorView 메시지 처리기 ***/

void CGraphicEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_RBUTTON)) {

		const PointF currPoint = CGlobal::CPointToPointF(point);

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		
		Pen dd(Color(255, 0, 0));
		SolidBrush ff(Color(0, 255, 0));


		switch (m_InsertFlag)
		{
		case CGraphicEditorView::NONE: {

			if (m_CurrentFigure) {	// 개체가 선택된 경우
				m_selectedPosition = m_CurrentFigure->pointInFigure(currPoint);
				if (m_selectedPosition == CFigure::OUTSIDE) {
					m_CurrentFigure = NULL;
				}
			}
			else {					// 개체가 선택되지 않은 경우
				// 전체 개체 리스트(그룹)을 순차로 순회
				// 선택 도형 갱신 (OUTSIDE/INSIDE 두 개의 값으로만 m_selectedPosition 갱신)
				// Invalidate 호출 (선택 영역을 그리기 위해)
			}
			break;
		}
		case CGraphicEditorView::LINE:
			m_CurrentFigure = new CLine(&dd);
			break;
		case CGraphicEditorView::POLYLINE:
			m_CurrentFigure = new CPolyLine();
			break;
		case CGraphicEditorView::PENCIL:
			break;
		case CGraphicEditorView::CURVE:
			break;
		case CGraphicEditorView::ELLIPSE:
			m_CurrentFigure = new CEllipse(&dd, &ff);
			break;
		case CGraphicEditorView::RECTANGLE:
			m_CurrentFigure = new CRectangle(&dd, &ff);
			break;
		case CGraphicEditorView::STRING:
			break;
		case CGraphicEditorView::POLYGON:
			break;
		case CGraphicEditorView::CLOSEDCURVE:
			break;
		default:
			break;
		}

		

		//if (m_InsertFlag != NONE)
		//{
		//	m_CurrentFigure->create(&m_LButtonPoint);
		//}



		
		/*********** 이 부분은 변경하지 마시오. ***********/
		m_LButtonPoint = currPoint;		// 이벤트 발생 좌표
		m_MouseButtonFlag = LBUTTON;	// 좌클릭 드래그 중
		/**************************************************/

		CView::OnLButtonDown(nFlags, point);

		//CGraphicEditorDoc* pDoc = GetDocument();
	}
}

void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_MouseButtonFlag == LBUTTON/* && !(nFlags & MK_RBUTTON)*/) {

		const PointF currPoint = CGlobal::CPointToPointF(point);

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		switch (m_InsertFlag)
		{
		case CGraphicEditorView::NONE: {
			if (m_CurrentFigure) {
				if (m_selectedPosition == CFigure::INSIDE) {
					CFigure::MoveFlag moveFlag = CFigure::FREEMOVE;
					//if (nFlags & MK_SHIFT) {
					//	moveFlag = CFigure::;
					//}

					m_CurrentFigure->move(m_LButtonPoint, currPoint, moveFlag);
				}
				else if (m_selectedPosition & CFigure::ONHANDLE) {
					CFigure::ResizeFlag resizeFlag = CFigure::FREERESIZE;
					if (nFlags & MK_SHIFT) {
						resizeFlag = CFigure::PROPORTIONAL;
					}

					if (m_CurrentFigure->IsKindOf(RUNTIME_CLASS(CStrap))) {
						((CStrap*)m_CurrentFigure)->pointMove(m_LButtonPoint, currPoint);
					}
					else {
						m_CurrentFigure->resize(m_selectedPosition, currPoint, resizeFlag);
					}
				}
			}
		} break;
		case CGraphicEditorView::LINE:
			m_CurrentFigure->create(&m_LButtonPoint, &currPoint, CFigure::FREECREATE);
			break;
		case CGraphicEditorView::POLYLINE:
			break;
		case CGraphicEditorView::PENCIL:
			break;
		case CGraphicEditorView::CURVE:
			break;
		case CGraphicEditorView::ELLIPSE:
			m_CurrentFigure->create(&m_LButtonPoint, &currPoint, CFigure::FREECREATE);
			break;
		case CGraphicEditorView::RECTANGLE:
			m_CurrentFigure->create(&m_LButtonPoint, &currPoint, CFigure::FREECREATE);
			break;
		case CGraphicEditorView::STRING:
			break;
		case CGraphicEditorView::POLYGON:
			break;
		case CGraphicEditorView::CLOSEDCURVE:
			break;
		default:
			break;
		}


		//if (m_InsertFlag != NONE){
		//	m_CurrentFigure->create(&m_LButtonPoint);
		//	//m_InsertFlag = NONE;
			Invalidate();
		//	m_CurrentFigure->draw();
		//}

		/*********** 이 부분은 변경하지 마시오. ***********/
		m_LButtonPoint = currPoint;		// 이벤트 발생 좌표
		m_MouseButtonFlag = NBUTTON;	// 비클릭 상태
		/**************************************************/

		CView::OnLButtonUp(nFlags, point);
	}
}

void CGraphicEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_RBUTTON)) {

		const PointF currPoint = CGlobal::CPointToPointF(point);

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		

		/*********** 이 부분은 변경하지 마시오. ***********/
		m_LButtonPoint = currPoint;		// 이벤트 발생 좌표
		m_MouseButtonFlag = LBUTTON;	// 좌클릭
		/**************************************************/

		CView::OnLButtonDblClk(nFlags, point);
	}
}

void CGraphicEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_LBUTTON)) {

		const PointF currPoint = CGlobal::CPointToPointF(point);

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.



		/*********** 이 부분은 변경하지 마시오. ***********/
		m_RButtonPoint = currPoint;		// 이벤트 발생 좌표
		m_MouseButtonFlag = RBUTTON;	// 우클릭 드래그 중
		/**************************************************/

		CView::OnRButtonDown(nFlags, point);
	}
}

void CGraphicEditorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (m_MouseButtonFlag == RBUTTON/* && !(nFlags & MK_LBUTTON)*/) {

		const PointF currPoint = currPoint;

		ClientToScreen(&point);
		OnContextMenu(this, point);



		/*********** 이 부분은 변경하지 마시오. ***********/
		m_RButtonPoint = currPoint;		// 이벤트 발생 좌표
		m_MouseButtonFlag = NBUTTON;	// 비클릭 상태
		/**************************************************/
	}
}

void CGraphicEditorView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_LBUTTON)) {

		const PointF currPoint = CGlobal::CPointToPointF(point);

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.



		/*********** 이 부분은 변경하지 마시오. ***********/
		m_RButtonPoint = currPoint;		// 이벤트 발생 좌표
		m_MouseButtonFlag = RBUTTON;	// 우클릭
		/**************************************************/

		CView::OnRButtonDblClk(nFlags, point);
	}
}

void CGraphicEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//CView::OnMouseMove(nFlags, point);

	CClientDC dc(this);
	Graphics graphics(dc);

	if (!m_MouseButtonFlag) {		// 비클릭 상태 마우스 움직임
	
	}

	else if (m_MouseButtonFlag == LBUTTON) {		// 마우스 왼쪽 버튼 드래그
		if (nFlags & MK_CONTROL) {		// Ctrl 누르고 드래그

		}
		else if (nFlags & MK_SHIFT) {	// Shift 누르고 드래그

		}
		else {							// 보조키 누르지 않고 드래그
			if (m_InsertFlag == LINE){
				//m_CurrentFigure->creating(&graphics, &CGlobal::CPointToPointF(point));
				//Invalidate();
			}
		}
	}

	else if (m_MouseButtonFlag == RBUTTON){	// 마우스 오른쪽 버튼 드래그
		if (nFlags & MK_CONTROL) {		// Ctrl 누르고 드래그

		}
		else if (nFlags & MK_SHIFT) {	// Shift 누르고 드래그

		}
		else {							// 보조키 누르지 않고 드래그

		}
	}
}

BOOL CGraphicEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CView::OnMouseWheel(nFlags, zDelta, point);
}

void CGraphicEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)
	{
	case VK_ESCAPE:
	case VK_CANCEL:
	case VK_BACK:
		clearInsertFlag();
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CView::OnChar(nChar, nRepCnt, nFlags);
	//캐럿이 생성되어있고, 글자입력모드라면?
}

void CGraphicEditorView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnSysChar(nChar, nRepCnt, nFlags);
}


void CGraphicEditorView::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnContextMenu(CWnd* pWnd, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


/*** CGraphicEditorView 작업 ***/

void CGraphicEditorView::clearInsertFlag()
{
	m_InsertFlag = NONE;
}


/*** CGraphicEditorView 인쇄 ***/

void CGraphicEditorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGraphicEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGraphicEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGraphicEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


/*** CGraphicEditorView 진단 ***/

#ifdef _DEBUG
void CGraphicEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicEditorDoc* CGraphicEditorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicEditorDoc)));
	return (CGraphicEditorDoc*)m_pDocument;
}
#endif //_DEBUG


/*** CGraphicEditorView 추가로 생성된 명령, 메시지 처리기 및 재정의 ***/

