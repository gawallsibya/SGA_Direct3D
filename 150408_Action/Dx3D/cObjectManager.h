#pragma once

#define g_pObjectManager cObjectManager::GetInstance()

class cObjectManager
{
private:
	std::set<cObject*> m_setObject;

public:
	SINGLETONE(cObjectManager);

	void AddObject(cObject* pObject)
	{
		m_setObject.insert(pObject);
	}

	void RemoveObject(cObject* pObject)
	{
		m_setObject.erase(pObject);
	}

	void Destroy()
	{
		assert(m_setObject.empty() && "생성된 cObject를 상속받은 객체중 해제되지 않은 인스턴스가 있습니다.");
	}
};

