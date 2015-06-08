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

// Graphic Editor View Commands.cpp : CGraphicEditorView 클래스의 구현 (명령 메시지 처리기)
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
#include "Text.h"


/*** CGraphicEditorView 명령 메시지 처리기 ***/

// void CGraphicEditorView::OnFilePrintPreview() {}
// 이 처리기는 "Graphic Editor View.cpp"에서 구현됨. ("CGraphicEditorView 인쇄" 참고)

//void CGraphicEditorView::OnEditClear()
//{
//	clearInsertFlag();
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//}

//void CGraphicEditorView::OnEditClearAll()
//{
//	clearInsertFlag();
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//}


void CGraphicEditorView::OnEditCopy()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//https://msdn.microsoft.com/ko-kr/library/cc451491(v=vs.71).aspx
	//https://msdn.microsoft.com/ko-kr/library/cc451492(v=vs.71).aspx

	
	CSharedFile file;
	//CShareFile 객체에 저장하는 아카이브 선언
	CArchive ar(&file, CArchive::store);
	

	CGraphicEditorDoc* pDoc = GetDocument();
	pDoc->m_FiguresList.Serialize(ar);
	ar.Close();

	if (!OpenClipboard())//클립보드 오픈실패시
	{
		AfxMessageBox(_T("Cannot open the Clipboard"));
		return;
	}
	//Create an OLE data source on the heap
	COleDataSource* pDataSource = new COleDataSource;
	
	//등록된 포멧형식
	TRY
	{
		pDataSource->CacheGlobalData(m_cfsDraw, file.Detach());
		OleInitialize(NULL);
		pDataSource->SetClipboard(); 
	}
		CATCH_ALL(e)
	{
		delete pDataSource;
		THROW_LAST();
	}
	END_CATCH_ALL
}

void CGraphicEditorView::OnEditCut()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

//void CGraphicEditorView::OnEditFind()
//{
//	clearInsertFlag();
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//}

void CGraphicEditorView::OnEditPaste()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	COleDataObject dataObject;

	//클립보드 내용을 가져옴
	dataObject.AttachClipboard();
	if (m_CurrentFigures.hasOneFigure()){//하나의 개체
	//클립보드 내용이 이 프로그램에 맞는 형식일 경우만 가능
		if (dataObject.IsDataAvailable(m_cfsDraw))
		{
			CFile* pFile = dataObject.GetFileData(m_cfsDraw);
			if (pFile == NULL)
				return;

			CArchive ar(pFile, CArchive::load); //pFile의 내용을 로드하는 아카이브 선언
			TRY
			{
				//선택 리스트로 직렬화를 수행하여 클립보드의 내용을 선택리스트로 저장
				//ar.m_pDocument = GetDocument();
				//	pDoc->m_sSelectedList.Serialize(ar);
			}
			CATCH_ALL(e)
			{
				ar.Close();
				delete pFile;
				THROW_LAST();
			}
			END_CATCH_ALL

				ar.Close();
			delete pFile;
		}
		Invalidate();
	}
}

void CGraphicEditorView::OnEditDelete()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

//void CGraphicEditorView::OnEditRepeat()
//{
//	clearInsertFlag();
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//}

//void CGraphicEditorView::OnEditReplace()
//{
//	clearInsertFlag();
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//}

void CGraphicEditorView::OnEditSelectAll()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnEditUndo()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnEditRedo()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnImageCanvasSize()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertLine()
{
	//m_CurrentFigures.RemoveAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = LINE;			// 수정 금지
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	// 테스트입니다!!
}

void CGraphicEditorView::OnUpdateInsertLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == LINE);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertPolyline()
{
	//m_CurrentFigures.RemoveAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = POLYLINE;		// 수정 금지
	m_PolyCreatableFlag = TRUE;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateInsertPolyline(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == POLYLINE);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertPencil()
{
	//m_CurrentFigures.RemoveAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = PENCIL;			// 수정 금지
	m_PolyCreatableFlag = TRUE;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateInsertPencil(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == PENCIL);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertCurve()
{
	//m_CurrentFigures.RemoveAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = CURVE;			// 수정 금지
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateInsertCurve(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == CURVE);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertEllipse()
{
	//m_CurrentFigures.RemoveAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = ELLIPSE;			// 수정 금지
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateInsertEllipse(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == ELLIPSE);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertRectangle()
{
	//m_CurrentFigures.RemoveAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = RECTANGLE;		// 수정 금지
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateInsertRectangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == RECTANGLE);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertString()
{
	//m_CurrentFigures.RemoveAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = STRING;			// 수정 금지
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateInsertString(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == STRING);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertPolygon()	// 삼각형 버튼
{
	//m_CurrentFigures.RemoveAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = POLYGON;			// 수정 금지
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateInsertPolygon(CCmdUI *pCmdUI)	// 삼각형 버튼
{
	pCmdUI->SetCheck(m_InsertFlag == POLYGON);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertClosedcurve()	// 도형 버튼
{
	//m_CurrentFigures.RemoveAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = CLOSEDCURVE;		// 수정 금지
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateInsertClosedcurve(CCmdUI *pCmdUI)	// 도형 버튼
{
	pCmdUI->SetCheck(m_InsertFlag == CLOSEDCURVE);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeOrder()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeBringFront()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeSendBack()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeBringForward()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeSendBackward()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeGrouping()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeGroup()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	//GetDocument()->m_FiguresList.AddHead(new CGroup(m_CurrentFigures));

	//for (POSITION pos = figurelist->GetTailPosition(); pos; figurelist->GetPrev(pos)) {
	//	m_CurrentFigures.InsertAfter(pos, figurelist->GetAt(subpos));
	//}

	//m_CurrentFigures.RemoveAll();
	//m_CurrentFigures.AddTail(GetDocument()->m_FiguresList.GetHead());
}

void CGraphicEditorView::OnUpdateArrangeGroup(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeUngroup()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	for (POSITION pos = m_CurrentFigures.GetHeadPosition(); pos; m_CurrentFigures.GetNext(pos)) {
		if (m_CurrentFigures.GetAt(pos)->IsKindOf(RUNTIME_CLASS(CGroup))) {
			CFigurePtrList* figurelist = &((CGroup*)m_CurrentFigures.GetAt(pos))->getFiguresList();

			for (POSITION subpos = figurelist->GetTailPosition(); subpos; figurelist->GetPrev(subpos)) {
				m_CurrentFigures.InsertAfter(pos, figurelist->GetAt(subpos));
			}
			
		}
	}
}

void CGraphicEditorView::OnUpdateArrangeUngroup(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnZoomIn()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnZoomOut()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnZoom100()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateZoom100(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}