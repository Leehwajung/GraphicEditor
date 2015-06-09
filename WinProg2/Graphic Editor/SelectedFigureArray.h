// SelectedFigureArray.h : CSelectedFigureArray Ŭ������ �������̽�
// CSelectedFigureArray : CFigurePtrList ��ü�� �����ϴ� Ŭ����
// @Author Lee Hwajung

#pragma once
#include "FigurePtrList.h"

// CSelectedFigureArray ��� ����Դϴ�.

typedef CArray<POSITION, POSITION> CPositionArray;

class CSelectedFigureArray : public CObject
{
public:
	// �⺻ ������
	CSelectedFigureArray();

	// ������
	CSelectedFigureArray(CFigurePtrList* lpFigurePtrList);

	// �Ҹ���
	virtual ~CSelectedFigureArray();

	// ������ ��ü�� �ִ��� �˻�
	BOOL isEmpty();

	// ������ ��ü�� �� ������ �˻�
	BOOL hasOne();								// hasOneFigure

	// ������ ��ü �� �� ���� ��ü ȹ��
	CFigure* getOneFigure();

	// ���� ������ ��ü�� ��� �ִ��� Ȯ��
	CFigure::Position contains(PointF point);	// pointInFigure

	// �ֻ��� ��ü ����
	void select();

	// �������� ��ü ����
	void select(POSITION position);

	// point�� ��ġ�� �ִ� ��ü ����
	CFigure::Position select(PointF point);		// getFigure

	// rect �ȿ� �ִ� ��ü ����
	void select(RectF rect);					// getFigures

	// ��ü ��ü ����
	void selectAll();

	// �ֻ��� ��ü ���� ����
	void deselect();

	// �������� ��ü ���� ���� (����: FALSE, ����: TRUE)
	BOOL deselect(POSITION position);

	// point�� ��ġ�� �ִ� ��ü ���� ����
	void deselect(PointF point);

	// rect �ȿ� �ִ� ��ü ���� ����
	void deselect(RectF rect);

	// ��ü ��ü ���� ����
	void deselectAll();

	// ������ ��ü ����
	void Delete();

	// ��ü ��ü ����
	void DeleteAll ();

	// ���� ��ü �̵�
	void move(IN PointF originPoint, IN PointF targetPoint, IN CFigure::MoveFlag moveFlag = CFigure::FREEMOVE);
	
	// ���� ��ü ũ�� ����
	void resize(IN CFigure::Position selectedHandle, IN PointF originPoint, IN PointF targetPoint, IN CFigure::ResizeFlag resizeFlag = CFigure::FREERESIZE, IN PointF* anchorPoint = NULL);

	// ���� ��ü �� �׷� ����
	void unGroup();

	// ���� ��ü �׸���
	void draw(IN Graphics& graphics);

	// ���� ��ü���� ���� ���� �׸���
	void drawArea(IN Graphics& graphics);

	// ���� ��ü �̵� �׸���
	RectF moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN CFigure::MoveFlag moveFlag = CFigure::FREEMOVE);
	
	// ���� ��ü ũ�� ���� �׸���
	RectF resizing(IN Graphics& graphics, IN CFigure::Position selectedHandle, IN PointF targetPoint, IN CFigure::ResizeFlag resizeFlag = CFigure::FREERESIZE, IN PointF* anchorPoint = NULL);

	// ���� ��ü ������ �� ����
	BOOL setOutlineColor(IN const Color& outlineColor);

	// ���� ��ü ������ �β� ����
	BOOL setOutlineWidth(IN const REAL outlineWidth);

	// ���� ��ü ������ ���� ����
	BOOL setOutlinePattern(IN const DashStyle outlinePattern);

	// ���� ��ü ä��� �� ����
	BOOL setFillColor(IN const Color& fillColor);

	// ���� ��ü ä��� ������ ����
	BOOL setFillSubcolor(IN const Color& fillSubcolor);

	// ���� ��ü ä��� ���� ����
	BOOL setFillPattern(IN const HatchStyle fillPattern);

	// FigurePtrList ȹ��
	CFigurePtrList* getFigurePtrList();

	// FigurePtrList ����
	void setFigurePtrList(CFigurePtrList* lpFigurePtrList);

	// �������� ���� �迭�� ����
	const POSITION* getData();

	// �������� ���� �迭�� ���� ������ ����
	int getSize();

private:
	// �� ���� ������ ȹ��
	POSITION getForwardPos();

private:
	CPositionArray m_FigurePosArray;
	CFigurePtrList* m_FigurePtrList;
};


