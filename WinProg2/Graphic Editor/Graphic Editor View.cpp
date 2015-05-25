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

// Graphic Editor View.cpp : CGraphicEditorView 클래스의 구현
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


// CGraphicEditorView

IMPLEMENT_DYNCREATE(CGraphicEditorView, CView)

BEGIN_MESSAGE_MAP(CGraphicEditorView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphicEditorView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CGraphicEditorView 생성/소멸

CGraphicEditorView::CGraphicEditorView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_MouseButtonFlag = NULL;
}

CGraphicEditorView::~CGraphicEditorView()
{
}

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

	Graphics graphics(*pDC);	// gdi+ 그리기를 위한 객체 https://msdn.microsoft.com/en-us/library/windows/desktop/ms534453(v=vs.85).aspx

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

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
	SolidBrush dd(Color(255,255,0,0));
	graphics.FillRectangle(&dd, Rect(33, 44, 55, 66));

}


// CGraphicEditorView 인쇄

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


// CGraphicEditorView 메시지 처리기

void CGraphicEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_RBUTTON)) {
		/***** 이 부분은 변경하지 마시오. *****/
		m_LButtonPoint = point;			// 이벤트 발생 좌표
		m_MouseButtonFlag = MK_LBUTTON;	// 좌클릭 드래그 중
		/**************************************/

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		CView::OnLButtonDown(nFlags, point);

		CGraphicEditorDoc* pDoc = GetDocument();
	}
}

void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_MouseButtonFlag == MK_LBUTTON/* && !(nFlags & MK_RBUTTON)*/) {
		/***** 이 부분은 변경하지 마시오. *****/
		m_LButtonPoint = point;		// 이벤트 발생 좌표
		m_MouseButtonFlag = NULL;	// 비클릭 상태
		/**************************************/

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		CView::OnLButtonUp(nFlags, point);
	}
}

void CGraphicEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_RBUTTON)) {
		/***** 이 부분은 변경하지 마시오. *****/
		m_LButtonPoint = point;			// 이벤트 발생 좌표
		m_MouseButtonFlag = MK_LBUTTON;	// 좌클릭
		/**************************************/

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		CView::OnLButtonDblClk(nFlags, point);
	}
}

void CGraphicEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_LBUTTON)) {
		/***** 이 부분은 변경하지 마시오. *****/
		m_RButtonPoint = point;			// 이벤트 발생 좌표
		m_MouseButtonFlag = MK_RBUTTON;	// 우클릭 드래그 중
		/**************************************/

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		CView::OnRButtonDown(nFlags, point);
	}
}

void CGraphicEditorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (m_MouseButtonFlag == MK_RBUTTON/* && !(nFlags & MK_LBUTTON)*/) {
		/***** 이 부분은 변경하지 마시오. *****/
		m_RButtonPoint = point;		// 이벤트 발생 좌표
		m_MouseButtonFlag = NULL;	// 비클릭 상태
		/**************************************/

		ClientToScreen(&point);
		OnContextMenu(this, point);
	}
}

void CGraphicEditorView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_LBUTTON)) {
		/***** 이 부분은 변경하지 마시오. *****/
		m_RButtonPoint = point;			// 이벤트 발생 좌표
		m_MouseButtonFlag = MK_RBUTTON;	// 우클릭
		/**************************************/

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		CView::OnRButtonDblClk(nFlags, point);
	}
}

void CGraphicEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//CView::OnMouseMove(nFlags, point);

	if (!m_MouseButtonFlag) {		// 비클릭 상태 마우스 움직임
	
	}

	else if (m_MouseButtonFlag == MK_LBUTTON) {		// 마우스 왼쪽 버튼 드래그
		if (nFlags & MK_CONTROL) {		// Ctrl 누르고 드래그

		}
		else if (nFlags & MK_SHIFT) {	// Shift 누르고 드래그

		}
		else {							// 보조키 누르지 않고 드리그

		}
	}

	else if (m_MouseButtonFlag == MK_RBUTTON){	// 마우스 오른쪽 버튼 드래그
		if (nFlags & MK_CONTROL) {		// Ctrl 누르고 드래그

		}
		else if (nFlags & MK_SHIFT) {	// Shift 누르고 드래그

		}
		else {							// 보조키 누르지 않고 드리그

		}
	}
}

BOOL CGraphicEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CView::OnMouseWheel(nFlags, zDelta, point);
}

void CGraphicEditorView::OnContextMenu(CWnd* pWnd, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGraphicEditorView 진단

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


// CGraphicEditorView 추가로 생성된 명령, 메시지 처리기 및 재정의
