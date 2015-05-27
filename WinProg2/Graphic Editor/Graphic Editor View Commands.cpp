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

// Graphic Editor View.cpp : CGraphicEditorView Ŭ������ ���� (��� �޽��� ó����)
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
}

void CGraphicEditorView::OnEditCut()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

//void CGraphicEditorView::OnEditFind()
//{
//	clearInsertFlag();
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//}

void CGraphicEditorView::OnEditPaste()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	m_InsertFlag = LINE;	// ���� ����
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
	m_InsertFlag = POLYLINE;	// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertPolyline(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == POLYLINE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertPencil()
{
	m_InsertFlag = PENCIL;	// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertPencil(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == PENCIL);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertCurve()
{
	m_InsertFlag = CURVE;	// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertCurve(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == CURVE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertEllipse()
{
	m_InsertFlag = ELLIPSE;	// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertEllipse(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == ELLIPSE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertRectangle()
{
	m_InsertFlag = RECTANGLE;	// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertRectangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == RECTANGLE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertString()
{
	m_InsertFlag = STRING;	// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertString(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == STRING);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertPolygon()	// �ﰢ�� ��ư
{
	m_InsertFlag = POLYGON;	// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertPolygon(CCmdUI *pCmdUI)	// �ﰢ�� ��ư
{
	pCmdUI->SetCheck(m_InsertFlag == POLYGON);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertClosedcurve()	// ���� ��ư
{
	m_InsertFlag = CLOSEDCURVE;	// ���� ����
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
}

void CGraphicEditorView::OnUpdateArrangeGroup(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeUngroup()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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