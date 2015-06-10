// FigureSettings.h : CFigureSettings Ŭ������ �������̽�
// CFigureSettings : ���� ���� �� �Ӽ� ������ ���� �⺻ ������ �����ϴ� Ŭ����
// 

#pragma once

// CFigureSettings ��� ����Դϴ�.

class CFigureSettings : public CObject
{
public:
	CFigureSettings();
	~CFigureSettings();

	/** �Ӽ� ���� **/
public:
	// ������ �� ����
	void setOutlineColor(IN const Color& outlineColor);

	// ������ �β� ����
	void setOutlineWidth(IN const REAL outlineWidth);

	// ������ ���� ����
	void setOutlinePattern(IN const DashStyle outlinePattern);

	// �� ä��� �� ����
	void setFillColor(IN const Color& fillColor);

	// ���� ä��� �� ����
	void setFillSubcolor(IN const Color& fillSubcolor);

	// ä��� ���� ����
	void setFillPattern(IN const HatchStyle fillPattern);

	// �� �۲û� ����
	void setFontColor(IN const Color& fontColor);

	// ���� �۲û� ����
	void setFontSubcolor(IN const Color& fontSubcolor);

	// �۲û� ���� ����
	void setFontPattern(IN const HatchStyle fontPattern);

	// �۲� �Ӽ� ����
	void setFontLog(IN const LOGFONT fontLog);

	// ���ڿ� ���� ����
	void setStringFormat(IN const StringFormat& StringFormat);

	Pen* getOutlinePen(Pen* outlinepen);
	Brush* getFillBrush(Brush* fillBrush);
	Brush* getFontBrush(Brush* fontBrush);
	LOGFONT* getFontLog();
	StringFormat* getStringFormat();

public:
	Color m_OutlineColor;
	REAL m_OutlineWidth;
	DashStyle m_OutlinePattern;
	Color m_FillColor;
	Color m_FillSubcolor;
	HatchStyle m_FillPattern;
	Color m_FontColor;
	Color m_FontSubcolor;
	HatchStyle m_FontPattern;
	LOGFONT m_FontLog;
	CString m_FontName;
	REAL m_FontSize;
	StringFormat* m_StringFormat;
};


