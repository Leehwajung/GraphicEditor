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
	REAL m_FillGradientAngle;
	Color m_FontColor;
	Color m_FontSubcolor;
	HatchStyle m_FontPattern;
	LOGFONT m_FontLog;
	CString m_FontName;
	REAL m_FontSize;
	StringFormat* m_StringFormat;
};


/* Logical Font
https://msdn.microsoft.com/en-us/library/windows/desktop/dd145037(v=vs.85).aspx

#define LF_FACESIZE         32
...
typedef struct tagLOGFONTW
{
LONG	lfHeight;					// �۲��ǳ���(�ȼ�����), ���밪�̹Ƿ� ��������
LONG	lfWidth;					// ����
LONG	lfEscapement;				// ���ڿ��� ����
LONG	lfOrientation;				// ������ ������ 0.1 �����θ��
LONG	lfWeight;					// �۲��� ���� ( = FW_BOLD)
BYTE	lfItalic;					// ���ڸ�(�ణ ������ ������ ����) ���� ���(true, false)
BYTE	lfUnderline;				// ����
BYTE	lfStrikeOut;				// ���ڰ����
BYTE	lfCharSet;					// ���������� ���.(�������� ������ ���ݾ� �ٸ� �� �ִ�)
BYTE	lfOutPrecision;				// �������� �������Ȯ����, ��¹��� ���������� �����ϴ°Ͱ� �۲� �׷��� ����ϴ°Ͱ� �������ִ�. (MSDN ����)

BYTE	lfClipPrecision;
BYTE	lfQuality;
BYTE	lfPitchAndFamily;
WCHAR	lfFaceName[LF_FACESIZE];	// ��Ʈ

} LOGFONTW, *PLOGFONTW, NEAR *NPLOGFONTW, FAR *LPLOGFONTW;
#ifdef UNICODE
typedef LOGFONTW LOGFONT;
typedef PLOGFONTW PLOGFONT;
typedef NPLOGFONTW NPLOGFONT;
typedef LPLOGFONTW LPLOGFONT;
#else
...
#endif // UNICODE

��쿡���� �ý��ۿ� � �۲��� ��ġ�Ǿ��ִ��� Ȯ���ϰ� �۲��̸��� ������ �ʿ䰡�ִµ�
�̶��� ::EnumFonts() api��, ::EnumFontFamiliesEx() APi �� ����ϸ�ȴ�.

[��ó] LOGFONT ����ü|�ۼ��� gunny http://blog.naver.com/reverse_ing/60137355395
*/