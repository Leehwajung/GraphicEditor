#pragma once
#include "Figure.h"

class CLine : public CFigure
{
public:
	CLine();
	~CLine();

	/* �� ����*/
	virtual void Create(CPoint startingPoint);

	/* �� �� ���� */
	virtual void setLineColor(Color lineColor);

	/* �� �β�*/
	virtual void setLineWidth(int lineWidth);

	/* �� ����*/
	virtual void setLinePattern(int linePattern);

	/* ��ü �̵�*/
	virtual void move(CPoint target);

	/* ũ�� ���� */
	virtual void resize(CPoint point);

	/* ����� ũ��*/
	virtual void propResize(CPoint point);

	/* ���� */
	virtual void destroy();

	/**/
	CList<CPoint, CPoint&>& GetPointsList();

private:

	/* �� ���� ��ǥ */
	CList <CPoint, CPoint&> m_PointsList;

	/* �׸��� ���� �� */
	CPen m_LinePen;


};

   