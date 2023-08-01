#pragma once
#include "Obj.h"
class CMouse :
    public CObj
{
public:
	CMouse();
	virtual ~CMouse();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

public:
	void OffSet(void);


private:
	POINT m_Point;

};

