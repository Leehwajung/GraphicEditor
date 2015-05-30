// Group.h : CGroup 클래스의 인터페이스
// CGroup : 그룹화된 도형 개체들을 저장하는 클래스
// @Author Lee Hwajung

#pragma once
#include "Figure.h"

// CGroup 명령 대상입니다.

class CGroup : public CFigure
{
public:
	CGroup();
	DECLARE_SERIAL(CGroup)
	virtual ~CGroup();

public:
	virtual void Serialize(CArchive& ar);

// 특성
private:
	//CTypedPtrList<CFigure, CFigure*> m_FiguresList;
};


