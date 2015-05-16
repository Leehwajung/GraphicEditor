#include "stdafx.h"
#include "Text.h"


CText::CText(){
}


///////////////////////////  Defalt 속성  //////////////////////////////////

void CText::FontDisplay(){//related information Derived from CFigureProperties
}
////////////////////////////////////////////////////////////////////////////

void CText::FontTransform( ){//Font transformation when setting values are changed

}

void CText::SizeTransform(){//Size transformation when when setting values are changed ex) click event

}
/////////////////

void  CText::FontDestroy(){// 제거

}

CText::~CText(){//delete
}

//CString m_FontName;
//int m_FontSize;
//BOOL m_FontBold;
//BOOL m_FontItalic;
//BOOL m_FontUnderline;