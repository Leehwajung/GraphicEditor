// �� MFC ���� �ҽ� �ڵ�� MFC Microsoft Office Fluent ����� �������̽�("Fluent UI")�� 
// ����ϴ� ����� ���� �ָ�, MFC C++ ���̺귯�� ����Ʈ��� ���Ե� 
// Microsoft Foundation Classes Reference �� ���� ���� ������ ���� 
// �߰������� �����Ǵ� �����Դϴ�.  
// Fluent UI�� ����, ��� �Ǵ� �����ϴ� �� ���� ��� ����� ������ �����˴ϴ�.  
// Fluent UI ���̼��� ���α׷��� ���� �ڼ��� ������ 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// Graphic Editor View Commands.cpp : CGraphicEditorView Ŭ������ ���� (��� �޽��� ó����)
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Graphic Editor.h"
#endif

#include "Graphic Editor Doc.h"
#include "Graphic Editor View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Text.h"


/*** CGraphicEditorView ��� �޽��� ó���� ***/

// void CGraphicEditorView::OnFilePrintPreview() {}
// �� ó����� "Graphic Editor View.cpp"���� ������. ("CGraphicEditorView �μ�" ����)

//void CGraphicEditorView::OnEditClear()
//{
//	clearInsertFlag();
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//}

//void CGraphicEditorView::OnEditClearAll()
//{
//	clearInsertFlag();
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//}


void CGraphicEditorView::OnEditCopy()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	
	CGraphicEditorDoc* pDoc = GetDocument();
	
	pDoc->m_BufferList.RemoveAll();//���簡 �Ͼ���� �׵��� ����Ǿ��ִ� ����Ʈ�� �����.
	if (m_CurrentFigures.hasOneFigure()){//�ϳ��� ���õ� ���
		// ���õ� ������ m_BufferList�� �����Ѵ�.
		//pDoc->m_BufferList.AddTail(); //��, m_FiguresList���� ��� ����
}

	else // ���� ���� case
	{
	}
	
	//
}

void CGraphicEditorView::OnEditCut()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CGraphicEditorDoc* pDoc = GetDocument();
	POSITION deletePos = pDoc->m_FiguresList.GetHeadPosition(); //��������ġ�� �������
	
	while (deletePos != NULL)
	{
		pDoc->m_FiguresList.GetNext(deletePos); // ������ ��ġ�� ã�� ������
		//if ()// deletepos�� ���õ� ������ ������ break;
	}
	//pDoc->m_BufferList.AddTail();//��������Ʈ���� ���۸���Ʈ�� ����
	pDoc->m_FiguresList.deleteAt(deletePos);//���� ����Ʈ���� ����

	Invalidate();//�߶󳻱⸦ �����Ƿ�, �信�� ������
}

//void CGraphicEditorView::OnEditFind()
//{
//	clearInsertFlag();
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//}

void CGraphicEditorView::OnEditPaste()//�ٿ��ֱ�
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CGraphicEditorDoc* pDoc = GetDocument();
	POSITION headpos = pDoc->m_BufferList.GetHeadPosition();
	
	//m_BufferList�� �ִ� �͵��� m_FigureList�� �߰��ؼ� �׸� ��.\

	Invalidate();
}

void CGraphicEditorView::OnEditDelete()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

//void CGraphicEditorView::OnEditRepeat()
//{
//	clearInsertFlag();
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//}

//void CGraphicEditorView::OnEditReplace()
//{
//	clearInsertFlag();
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//}

void CGraphicEditorView::OnEditSelectAll()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnEditUndo()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnEditRedo()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnImageCanvasSize()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertLine()
{
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = LINE;			// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	// �׽�Ʈ�Դϴ�!!
}

void CGraphicEditorView::OnUpdateInsertLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == LINE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertPolyline()
{
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = POLYLINE;		// ���� ����
	m_PolyCreatableFlag = TRUE;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertPolyline(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == POLYLINE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertPencil()
{
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = PENCIL;			// ���� ����
	m_PolyCreatableFlag = TRUE;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertPencil(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == PENCIL);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertCurve()
{
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = CURVE;			// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertCurve(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == CURVE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertEllipse()
{
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = ELLIPSE;			// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertEllipse(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == ELLIPSE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertRectangle()
{
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = RECTANGLE;		// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertRectangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == RECTANGLE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertString()
{
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = STRING;			// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertString(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == STRING);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertPolygon()	// �ﰢ�� ��ư
{
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = POLYGON;			// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertPolygon(CCmdUI *pCmdUI)	// �ﰢ�� ��ư
{
	pCmdUI->SetCheck(m_InsertFlag == POLYGON);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertClosedcurve()	// ���� ��ư
{
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = CLOSEDCURVE;		// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertClosedcurve(CCmdUI *pCmdUI)	// ���� ��ư
{
	pCmdUI->SetCheck(m_InsertFlag == CLOSEDCURVE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeOrder()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeBringFront()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeSendBack()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeBringForward()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeSendBackward()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeGrouping()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeGroup()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	//GetDocument()->m_FiguresList.AddHead(new CGroup(m_CurrentFigures));

	//for (POSITION pos = figurelist->GetTailPosition(); pos; figurelist->GetPrev(pos)) {
	//	m_CurrentFigures.InsertAfter(pos, figurelist->GetAt(subpos));
	//}

	//m_SelectedFigures.deselectAll();
	//m_CurrentFigures.AddTail(GetDocument()->m_FiguresList.GetHead());
}

void CGraphicEditorView::OnUpdateArrangeGroup(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeUngroup()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	//for (POSITION pos = m_CurrentFigures.GetHeadPosition(); pos; m_CurrentFigures.GetNext(pos)) {
	//	if (m_CurrentFigures.GetAt(pos)->IsKindOf(RUNTIME_CLASS(CGroup))) {
	//		CFigurePtrList* figurelist = &((CGroup*)m_CurrentFigures.GetAt(pos))->getFiguresList();

	//		for (POSITION subpos = figurelist->GetTailPosition(); subpos; figurelist->GetPrev(subpos)) {
	//			m_CurrentFigures.InsertAfter(pos, figurelist->GetAt(subpos));
	//		}
	//		
	//	}
	//}
}

void CGraphicEditorView::OnUpdateArrangeUngroup(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnZoomIn()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnZoomOut()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnZoom100()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateZoom100(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnPolylineIndividualDelete()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (m_SelectedFigures.hasOne() && m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CPolyLine))) {
		CPolyLine* polyLine = (CPolyLine*)m_SelectedFigures.getOneFigure();

		if (polyLine->GetPointsList().GetSize() == 1){
			polyLine->destroy();
		}
		else 
			(polyLine)->RemovePoint(m_RButtonPoint);
		Invalidate();
	}

}

void CGraphicEditorView::OnPolylineIndividualInsert()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (m_SelectedFigures.hasOne() && m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CPolyLine))) {
		((CPolyLine*)m_SelectedFigures.getOneFigure())->InsertPoint(m_RButtonPoint);
		Invalidate();
	}
}