#pragma once

class cGameObject;
class cAction;

class iActionDelegate
{
public:
	virtual void OnActionFinish(cAction* pSender) = 0;
};

class cAction : public cObject
{
private:
	SYNTHESIZE(cGameObject*, m_pOwner, Owner);
	SYNTHESIZE(iActionDelegate*, m_pDelegate, Delegate);

public:
	cAction(void);
	virtual ~cAction(void);

	virtual void Start() {}
	virtual void Update() {}
};

