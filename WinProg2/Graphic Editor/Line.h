#pragma once
#include "Figure.h"
class CLine : public CFigure
{
public:
	CLine();
	~CLine();

	/* 선 생성*/
	virtual void Create(CPoint startingPoint);

	/* 선 색 변경 */
	virtual void setLineColor(Color lineColor);

	/* 선 두께*/
	virtual void setLineWidth(int lineWidth);

	/* 선 패턴*/
	virtual void setLinePattern(int linePattern);

	/* 전체 이동*/
	virtual void move(CPoint target);

	/* 크기 변경 */
	virtual void resize(CPoint point);

	/* 정비례 크기*/
	virtual void propResize(CPoint point);

	/* 삭제 */
	virtual void destroy();

	/**/
	CList<CPoint, CPoint&>& GetPointsList();

private:

	/* 두 개의 좌표 */
	CList <CPoint, CPoint&> m_PointsList;

	/* 그리기 위한 펜 */
	CPen m_LinePen;


};

   