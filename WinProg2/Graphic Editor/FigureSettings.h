// FigureSettings.h : CFigureSettings Ŭ������ �������̽�
// CFigureSettings : ���� ���� �� �Ӽ� ������ ���� �⺻ ������ �����ϴ� Ŭ����
// @Author Lee Hwajung

#pragma once

// CFigureSettings ��� ����Դϴ�.

class CFigureSettings : public CObject
{
public:
	CFigureSettings();
	~CFigureSettings();

	/** �Ӽ� ���� **/
public:
	// ������ �� ���� (���� ����)
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	BOOL setOutlineColor(IN const Color& outlineColor);

	// ������ �β� ���� (���� ����)
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	BOOL setOutlineWidth(IN const REAL outlineWidth);

	// ������ ���� ���� (���� ����)
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	BOOL setOutlinePattern(IN const DashStyle outlinePattern);

	// �� ä��� �� ���� (���� ����)
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	BOOL setFillColor(IN const Color& fillColor);

	// ���� ä��� �� ���� (���� ����)
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	BOOL setFillSubcolor(IN const Color& fillSubcolor);

	// ä��� ���� ���� (���� ����)
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	BOOL setFillPattern(IN const HatchStyle fillPattern);

	Pen* getOutlinePen() { return m_OutlinePen; }
	Brush* getFontBrush() { return m_FillSolidBrush; }

private:
	Pen* m_OutlinePen;
	SolidBrush* m_FillSolidBrush;

	Brush* m_FontBrush;
};


