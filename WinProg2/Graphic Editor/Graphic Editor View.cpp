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

#include "MainFrm.h"
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
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_SETCURSOR()
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
	//m_CurrentFigure = NULL;
	m_MouseVKFlags = 0;
	m_MouseButtonFlag = NBUTTON;
	m_InsertFlag = NONE;
	m_PolyCreatableFlag = FALSE;
	//// m_OperationModeFlag = SELECTABLE;
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

void CGraphicEditorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	////dc를 만듬
	//m_psMemDC = new CDC();
	//m_psMemDC->CreateCompatibleDC(GetDC());

	////비트맵을 만듬
	//m_psBitmap = new CBitmap();
	//int width = GetSystemMetrics(SM_CXSCREEN); //화면 폭을 구함
	//int height = GetSystemMetrics(SM_CYSCREEN); //화면 높이를 구함
	//m_psBitmap->CreateCompatibleBitmap(GetDC(), width, height);
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
	
	//더블 버퍼링	
	//CRect rect;
	//GetClientRect(rect); //현재 클라이언트의 크기를 구함

	//Bitmap bmp(rect.right, rect.bottom);
	//Graphics* graphics = Graphics::FromImage(&bmp);



	//m_psBitmap->SetBitmapDimension(rect.Width(), rect.Height());
	//m_psOldBitmap = m_psMemDC->SelectObject(m_psBitmap); //생성한 비트맵을 선택
	////생성한 비트맵은 검은색이므로 흰색 배경을 그림
	//CGdiObject* psOldBrush = m_psMemDC->SelectStockObject(WHITE_BRUSH);
	//CGdiObject* psOldPen = m_psMemDC->SelectStockObject(WHITE_PEN);
	//m_psMemDC->Rectangle(rect);
	////이전 펜과 브러쉬로 되돌림
	//m_psMemDC->SelectObject(psOldBrush);
	//m_psMemDC->SelectObject(psOldPen);

	Graphics graphics(*pDC);	// gdi+ 그리기를 위한 객체 https://msdn.microsoft.com/en-us/library/windows/desktop/ms534453(v=vs.85).aspx

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	// 현재까지 생성된 모든 개체를 그림
	if (!pDoc->m_FiguresList.IsEmpty()) {
		pDoc->m_FiguresList.draw(graphics);
	}

	//if (!m_CurrentFigures.IsEmpty()) {
	//	m_CurrentFigures.drawHandles(graphics);
	//}

	if (m_MouseButtonFlag == NBUTTON) {		// 비클릭 상태 마우스 움직임
		if (m_CurrentFigures.hasOneFigure() && getOperationModeFlag() == CREATE 
			&& m_InsertFlag == POLYLINE && m_PolyCreatableFlag == FALSE) {
			((CPolyLine*)m_CurrentFigures.GetHead())->draw(graphics);
			/*m_drawnArea = CGlobal::RectFToCRect(*/((CPolyLine*)m_CurrentFigures.GetHead())->creating(graphics, m_CurrPoint);
		}
	}

	else if (m_MouseButtonFlag == LBUTTON) {		// 마우스 왼쪽 버튼 드래그
		if (m_MouseVKFlags & MK_CONTROL) {		// Ctrl 누르고 드래그

		}
		else if (m_MouseVKFlags & MK_SHIFT) {	// Shift 누르고 드래그

		}
		else {							// 보조키 누르지 않고 드래그
			switch (getOperationModeFlag())
			{
				//case CGraphicEditorView::SELECTABLE: {
				//} break;

				//case CGraphicEditorView::SELECTED: {
				//} break;

				case CGraphicEditorView::CREATE: {
					switch (m_InsertFlag)
					{
					//case CGraphicEditorView::NONE:
					//	break;

					case CGraphicEditorView::LINE:
					//case CGraphicEditorView::POLYLINE:
					case CGraphicEditorView::PENCIL:
					case CGraphicEditorView::CURVE:
						/*m_DrawnArea = CGlobal::RectFToCRect(*/m_CurrentFigures.GetHead()->creating(graphics, &m_LButtonPoint, &m_CurrPoint);
						break;

					case CGraphicEditorView::ELLIPSE:
					case CGraphicEditorView::RECTANGLE:
					case CGraphicEditorView::STRING:

						break;

					case CGraphicEditorView::POLYGON:
					case CGraphicEditorView::CLOSEDCURVE:

						break;

					default:
						break;
			}
				} break;

				case CGraphicEditorView::MOVE: {
					m_CurrentFigures.moving(graphics, m_LButtonPoint, m_CurrPoint);
				} break;

				case CGraphicEditorView::RESIZE: {
					if (m_CurrentFigures.hasOneFigure()) {
						if (m_CurrentFigures.GetHead()->IsKindOf(RUNTIME_CLASS(CLine))){
							((CLine*)m_CurrentFigures.GetHead())->pointMoving(graphics, m_LButtonPoint, m_CurrPoint);
				}
						else if (m_CurrentFigures.GetHead()->IsKindOf(RUNTIME_CLASS(CPolyLine))){
							((CPolyLine*)m_CurrentFigures.GetHead())->pointMoving(graphics, m_LButtonPoint, m_CurrPoint);
			}
						else {
							m_CurrentFigures.GetHead()->resizing(graphics, m_selectedPosition, m_CurrPoint);
				}
				}
					else {
						m_CurrentFigures.resizing(graphics, m_selectedPosition, m_CurrPoint);
			}
				} break;

				default: {

				} break;
		}
	}
	}

	else if (m_MouseButtonFlag == RBUTTON){	// 마우스 오른쪽 버튼 드래그
		if (m_MouseVKFlags & MK_CONTROL) {		// Ctrl 누르고 드래그

		}
		else if (m_MouseVKFlags & MK_SHIFT) {	// Shift 누르고 드래그

		}
		else {							// 보조키 누르지 않고 드래그

		}
	}
	

	//////////////////////////////////////////////////////////////////////////
	///*int */m_mode = 0;// 일단 모드라고 해놓겠음. // 일단 컴파일 에러로 임의 값 설정해둠.
	//switch(m_mode){
	//	case 1: // 폴리라인
	//		break;
	//	case 2: // 도형
	//		break;
	//	case 3 :// 텍스트
	//	
	//		break;
	// view 객체 넘겨서? 받아서 각각 함수에서 다 처리하는 방식으로 하자는 거지??
	// Graphics 포인터를 멤버 변수(m_graphics)로 둬서 각 개체 클래스에서 그리기를 정의하고, 그 함수를 호출하는 방식으로 할거야
	//
	//}
	//////////////////////////////////////////////// 여기서부터 예제 코드 ///////////////////////////////////////////////////////
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
	
	//pDC->BitBlt(0, 0, rect.Width(), rect.Height(), m_psMemDC, 0, 0, SRCCOPY);
	//graph.DrawImage(&bmp, rect.left, rect.top, rect.right, rect.bottom);
}


/*** CGraphicEditorView 메시지 처리기 ***/

void CGraphicEditorView::OnDestroy()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	////더블 버퍼링을 위한 변수 해제
	//m_psBitmap->DeleteObject();
	//m_psMemDC->DeleteDC();

	//CMainFrame* pMainFrame = (CMainFrame *)GetParentFrame();

	//CView::OnDestroy();
}

void CGraphicEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	if (!m_MouseButtonFlag && !(nFlags & MK_RBUTTON)) {

		m_CurrPoint = CGlobal::CPointToPointF(point);
		m_MouseVKFlags = nFlags;

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		
		Pen dd(Color(255, 0, 0));			// 테스트용 펜
		SolidBrush ff(Color::DarkGreen);	// 테스트용 브러시


		switch (getOperationModeFlag())
		{
			case CGraphicEditorView::SELECTABLE: {
				m_selectedPosition = GetDocument()->m_FiguresList.getFigure(m_CurrPoint, m_CurrentFigures);		// 전체 개체 리스트(그룹)을 순차로 순회
				// 선택 도형 갱신 (OUTSIDE/INSIDE 두 개의 값으로만 m_selectedPosition 갱신)
				// Invalidate 호출 (선택 영역을 그리기 위해)
			} break;

			case CGraphicEditorView::SELECTED: {
				m_selectedPosition = m_CurrentFigures.pointInFigure(m_CurrPoint);
				if (m_selectedPosition == CFigure::OUTSIDE) {
					if (m_CurrentFigures.GetHead()->IsKindOf(RUNTIME_CLASS(CText)))
						HideCaret();
					m_CurrentFigures.RemoveAll();		// SELECTABLE 상태로 전환
					m_selectedPosition = GetDocument()->m_FiguresList.getFigure(m_CurrPoint, m_CurrentFigures);
				}
			} break;

			case CGraphicEditorView::CREATE: {
				switch (m_InsertFlag)
				{
					/* CREATE 상태 */
				case CGraphicEditorView::LINE:
					preInsert();								// 이전 선택 개체 제거
					m_CurrentFigures.AddTail(new CLine(&dd));	// 새로운 생성 개체 선택
					break;

				case CGraphicEditorView::POLYLINE:
					if (m_PolyCreatableFlag) {							// CPolyLine 객체 생성 가능 상태
						preInsert();									// 이전 선택 개체 제거
						m_CurrentFigures.AddTail(new CPolyLine(&dd));	// 객체 생성
						m_PolyCreatableFlag = FALSE;					// CPolyLine 객체 생성 불가능 상태로 변경
					}

					((CPolyLine*)m_CurrentFigures.GetHead())->addPoint(m_CurrPoint, CFigure::FREECREATE);	// 점 추가

					//if (m_CurrentFigures.IsEmpty()/* || ((CPolyLine*)m_CurrentFigures.GetHead())->GetCreatedFlag()*/) {
					//	m_CurrentFigures.AddTail(new CPolyLine(&dd));
					//	((CPolyLine*)m_CurrentFigures.GetHead())->addPoint(m_CurrPoint, CFigure::FREECREATE);
					//}
					//else if (m_CurrentFigures.hasOneFigure()) {
					//	((CPolyLine*)m_CurrentFigures.GetHead())->addPoint(m_CurrPoint, CFigure::FREECREATE);
					//}
					break;

				case CGraphicEditorView::PENCIL:
					break;

				case CGraphicEditorView::CURVE:
					break;

				case CGraphicEditorView::ELLIPSE:
					preInsert();								// 이전 선택 개체 제거
					m_CurrentFigures.AddTail(new CEllipse(&dd, &ff));
					break;

				case CGraphicEditorView::RECTANGLE:
					preInsert();								// 이전 선택 개체 제거
					m_CurrentFigures.AddTail(new CRectangle(&dd, &ff));
					break;

				case CGraphicEditorView::STRING:
					preInsert();								// 이전 선택 개체 제거
					m_CurrentFigures.AddTail(new CText(this, &dd, &ff));
					break;

				case CGraphicEditorView::POLYGON:
					break;

				case CGraphicEditorView::CLOSEDCURVE:
					break;
				}

			} break;

			case CGraphicEditorView::MOVE: {

			} break;

			case CGraphicEditorView::RESIZE: {

			} break;
		}

		/*********** 이 부분은 변경하지 마시오. ***********/
		m_LButtonPoint = m_CurrPoint;		// 이벤트 발생 좌표
		m_MouseButtonFlag = LBUTTON;	// 좌클릭 드래그 중
		/**************************************************/

		CView::OnLButtonDown(nFlags, point);

		//CGraphicEditorDoc* pDoc = GetDocument();
	}
}

void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_MouseButtonFlag == LBUTTON/* && !(nFlags & MK_RBUTTON)*/) {

		m_CurrPoint = CGlobal::CPointToPointF(point);
		m_MouseVKFlags = nFlags;

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		switch (getOperationModeFlag())
		{
			//case CGraphicEditorView::SELECTABLE: {
			//} break;

			//case CGraphicEditorView::SELECTED: {
			//} break;

			/* CREATE 상태 */
			case CGraphicEditorView::CREATE: {
				switch (m_InsertFlag)
				{
				case CGraphicEditorView::LINE:
					m_CurrentFigures.GetHead()->create(&m_LButtonPoint, &m_CurrPoint, CFigure::FREECREATE);
					postInsert();
					break;

				case CGraphicEditorView::POLYLINE:
					// 아무 동작도 하지 않음 //((CPolyLine*)m_CurrentFigure)->addPoint(m_CurrPoint, CFigure::FREECREATE);
					break;

				case CGraphicEditorView::PENCIL:
					break;

				case CGraphicEditorView::CURVE:
					break;

				case CGraphicEditorView::ELLIPSE:
					m_CurrentFigures.GetHead()->create(&m_LButtonPoint, &m_CurrPoint, CFigure::FREECREATE);
					postInsert();
					break;

				case CGraphicEditorView::RECTANGLE:
					m_CurrentFigures.GetHead()->create(&m_LButtonPoint, &m_CurrPoint, CFigure::FREECREATE);
					postInsert();
					break;

				case CGraphicEditorView::STRING:
					m_CurrentFigures.GetHead()->create(&m_LButtonPoint, &m_CurrPoint, CFigure::FREECREATE);
					postInsert();
					break;

				case CGraphicEditorView::POLYGON:
					break;

				case CGraphicEditorView::CLOSEDCURVE:
					break;
				}
			} break;

			case CGraphicEditorView::MOVE: {
				CFigure::MoveFlag moveFlag = CFigure::FREEMOVE;
				//if (nFlags & MK_SHIFT) {
				//	moveFlag = CFigure::;
				//}

				m_CurrentFigures.move(m_LButtonPoint, m_CurrPoint, moveFlag);
				m_selectedPosition = CFigure::OUTSIDE;
			} break;

			case CGraphicEditorView::RESIZE: {
				CFigure::ResizeFlag resizeFlag = CFigure::FREERESIZE;
				if (nFlags & MK_SHIFT) {
					resizeFlag = CFigure::PROPORTIONAL;
				}

				if (m_CurrentFigures.hasOneFigure() && m_CurrentFigures.GetHead()->IsKindOf(RUNTIME_CLASS(CStrap))) {
					((CStrap*)m_CurrentFigures.GetHead())->pointMove(m_LButtonPoint, m_CurrPoint);
				}
				else {
					m_CurrentFigures.resize(m_selectedPosition, m_CurrPoint, resizeFlag);
				}
				m_selectedPosition = CFigure::OUTSIDE;
			} break;
		}

		Invalidate();

		/*********** 이 부분은 변경하지 마시오. ***********/
		m_LButtonPoint = m_CurrPoint;		// 이벤트 발생 좌표
		m_MouseButtonFlag = NBUTTON;	// 비클릭 상태
		/**************************************************/

		CView::OnLButtonUp(nFlags, point);
	}
}

void CGraphicEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_RBUTTON)) {

		m_CurrPoint = CGlobal::CPointToPointF(point);
		m_MouseVKFlags = nFlags;

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		// 더블클릭하면 폴리라인 생성 완료
		if (m_InsertFlag == CGraphicEditorView::POLYLINE/* && m_CurrentFigures.hasOneFigure()*/) {
			((CPolyLine*)m_CurrentFigures.GetHead())->create(CFigure::FREECREATE);
			
			m_PolyCreatableFlag = TRUE;
			postInsert();
			//clearInsertFlag();
		}

		/*********** 이 부분은 변경하지 마시오. ***********/
		m_LButtonPoint = m_CurrPoint;		// 이벤트 발생 좌표
		//m_MouseButtonFlag = NBUTTON;	// 좌클릭
		/**************************************************/

		CView::OnLButtonDblClk(nFlags, point);
	}
}

void CGraphicEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_LBUTTON)) {

		m_CurrPoint = CGlobal::CPointToPointF(point);
		m_MouseVKFlags = nFlags;

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.



		/*********** 이 부분은 변경하지 마시오. ***********/
		m_RButtonPoint = m_CurrPoint;		// 이벤트 발생 좌표
		m_MouseButtonFlag = RBUTTON;	// 우클릭 드래그 중
		/**************************************************/

		CView::OnRButtonDown(nFlags, point);
	}
}

void CGraphicEditorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (m_MouseButtonFlag == RBUTTON/* && !(nFlags & MK_LBUTTON)*/) {

		m_CurrPoint = CGlobal::CPointToPointF(point);
		m_MouseVKFlags = nFlags;

		ClientToScreen(&point);
		OnContextMenu(this, point);



		/*********** 이 부분은 변경하지 마시오. ***********/
		m_RButtonPoint = m_CurrPoint;		// 이벤트 발생 좌표
		m_MouseButtonFlag = NBUTTON;	// 비클릭 상태
		/**************************************************/
	}
}

void CGraphicEditorView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_LBUTTON)) {

		m_CurrPoint = CGlobal::CPointToPointF(point);
		m_MouseVKFlags = nFlags;

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.



		/*********** 이 부분은 변경하지 마시오. ***********/
		m_RButtonPoint = m_CurrPoint;		// 이벤트 발생 좌표
		m_MouseButtonFlag = NBUTTON;	// 우클릭
		/**************************************************/

		CView::OnRButtonDblClk(nFlags, point);
	}
}

void CGraphicEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//CView::OnMouseMove(nFlags, point);

	m_CurrPoint = CGlobal::CPointToPointF(point);
	m_MouseVKFlags = nFlags;

	switch (getOperationModeFlag())
	{
	//case CGraphicEditorView::SELECTABLE:
	//	break;

	//case CGraphicEditorView::SELECTED:
	//	break;

	case CGraphicEditorView::CREATE:
	case CGraphicEditorView::MOVE:
	case CGraphicEditorView::RESIZE:
		Invalidate/*Rect*/(/*m_DrawnArea*/);
		break;

	default:
		break;
	}
}

BOOL CGraphicEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CView::OnMouseWheel(nFlags, zDelta, point);
}

BOOL CGraphicEditorView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nHitTest == HTCLIENT) {
		CPoint point;
		::GetCursorPos(&point);		// 스크린좌표
		ScreenToClient(&point);		// 클라이언트좌표로변환

		//if (m_CurrentFigures.GetSize() == 1){
		//	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HELP));
		//	return true;
		//}

		switch (getOperationModeFlag())
		{
		case CGraphicEditorView::SELECTABLE:
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
			break;
		case CGraphicEditorView::SELECTED:
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
			break;
		case CGraphicEditorView::CREATE:
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
			break;
		case CGraphicEditorView::MOVE:
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
			break;
		case CGraphicEditorView::RESIZE:
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENESW));
			break;
		}
		//CRgn rgn;
		//rgn.CreateEllipticRgn(50, 50, 500, 200);
		//if (rgn.PtInRegion(point))
		//	::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR1);
		//else
		//	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS);
		return TRUE;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CGraphicEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)
	{
	case VK_ESCAPE:
	case VK_CANCEL:
	case VK_BACK:
		cancelInsert();
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (m_CurrentFigures.hasOneFigure() && m_CurrentFigures.GetHead()->IsKindOf((RUNTIME_CLASS(CText)))) {
		switch (nChar) {
			// 백스페이스 입력시
		case VK_BACK:
			((CText*)m_CurrentFigures.GetHead())->delChar(); // 문자삭제
			break;
			// 한줄 입력이므로 엔터키는 배열에 들어가지 않아도됨
		case VK_RETURN:
		case VK_CONTROL:
			break;
			// 위의 케이스를 제외한 문자저장
		default:
			((CText*)m_CurrentFigures.GetHead())->addChar(nChar);
		}
	CView::OnChar(nChar, nRepCnt, nFlags);
	}

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

void CGraphicEditorView::preInsert()	// 삽입(생성) 작업 전에 해야 할 작업
{
	m_CurrentFigures.RemoveAll();	// 선택 개체 제거
}

void CGraphicEditorView::postInsert()	// 삽입(생성) 작업 후에 해야 할 작업
{
	GetDocument()->m_FiguresList.AddHead(m_CurrentFigures.GetHead());	// 전체 개체 리스트에 추가
	//m_selectedPosition = CFigure::OUTSIDE;
}

void CGraphicEditorView::cancelInsert()	// 삽입(생성) 작업 취소 시에 해야 할 작업
{
	setOperationModeFlag(SELECTABLE);
	Invalidate();
}

void CGraphicEditorView::clearInsertFlag()
{
	// m_OperationModeFlag = SELECTABLE;
	m_InsertFlag = NONE;
}

CGraphicEditorView::OperationModeFlag CGraphicEditorView::getOperationModeFlag()
{
	/*
		### Comments about OperationModeFlag ###
		
	 $	m_InsertFlag, m_CurrentFigures, m_selectedPosition에 종속적이다.

	 $	SELECTABLE:	CREATE 상태가 아니면서 선택된 개체가 없는 상태이다.
		SELECTED:	개체가 선택된 상태로 연산을 하지 않고 있는 상태이다.
		CREATE:		삽입 버튼이 눌려있는 상태이다.
		MOVE:		선택한 개체가 있으면서 개체 내부의 점을 선택한 상태이다. 
		RESIZE:		선택한 개체가 있으면서 개체의 핸들을 선택한 상태이다.
		//WRITE:		CText 객체에 문자열을 입력하는 상태이다.

	 $	선택한 개체가 없을 경우 m_selectedPosition을 "핸들 위"로 갱신하지 않도록 하여,
		임의 개체의 첫 번째 클릭에서 크기 변경을 막는다.

	 $	ButtonDown에서 m_selectedPosition을 "핸들 위(선택한 개체가 있을 경우만)"
		또는 "CFigure::INSIDE"로 갱신하고,
		ButtonUp에서 m_selectedPosition을 "CFigure::OUTSIDE"로 갱신하여,
		SELECTED 상태를 얻을 수 있도록 한다.
	 */

	// 삽입 버튼이 눌려있으면,
	if (m_InsertFlag != NONE) {
		return CREATE;	// CREATE 상태
	}

	// 선택된 개체가 있을 때,
	if (!m_CurrentFigures.IsEmpty()) {
		if (m_selectedPosition & CFigure::ONHANDLE) {		// 선택 위치가 핸들이면,
			return RESIZE;									// RESIZE 상태
		}

		else if (m_selectedPosition == CFigure::INSIDE) {	// 선택 위치가 내부면,
			return MOVE;									// MOVE 상태
		}

		//else if (m_selectedPosition == CFigure::OUTSIDE) {
		//	return SELECTED;
		//}
		//
		//else if (m_CurrentFigures.hasOneFigure() && m_CurrentFigures.GetHead()->IsKindOf((RUNTIME_CLASS(CText)))) {
		//
		//}

		return SELECTED;									// 이외의 경우, SELECTED 상태
	}

	// 삽입 버튼이 눌려있지 않으면서, 선택된 개체가 없으면,
	return SELECTABLE;	// SELECTABLE 상태
}

void CGraphicEditorView::setOperationModeFlag(OperationModeFlag operationModeFlag/* = SELECTABLE*/)
{
	switch (operationModeFlag)
	{
	case CGraphicEditorView::SELECTABLE:
	m_InsertFlag = NONE;
		m_selectedPosition = CFigure::OUTSIDE;
		m_CurrentFigures.RemoveAll();
		break;

	case CGraphicEditorView::SELECTED:
		break;

	case CGraphicEditorView::CREATE:
		break;

	case CGraphicEditorView::MOVE:
		break;

	case CGraphicEditorView::RESIZE:
		break;
	}
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










