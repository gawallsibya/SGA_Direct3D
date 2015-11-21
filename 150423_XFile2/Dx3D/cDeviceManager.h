#pragma once

#define g_pDeviceManager cDeviceManager::GetInstance()
#define g_pD3DDevice cDeviceManager::GetInstance()->GetDevice()

class cDeviceManager
{
	SINGLETONE(cDeviceManager);

private:
	LPDIRECT3D9					m_pD3D;
	LPDIRECT3DDEVICE9			m_pD3DDevice;

public:
	LPDIRECT3DDEVICE9 GetDevice()
	{
		return m_pD3DDevice;
	}

	void Destroy()
	{
		SAFE_RELEASE(m_pD3D);
		
		unsigned long ul = m_pD3DDevice->Release();
#ifdef _DEBUG
		assert(ul == 0 && "디바이스를 이용해 생성한 객체 중 해제되지 않은 객체가 있습니다.");
#endif
	}

};

