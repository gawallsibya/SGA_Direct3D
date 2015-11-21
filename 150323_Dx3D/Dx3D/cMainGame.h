#pragma once
// 
// class cEBookReader
// {
// 	virtual void Open(file) = 0;
// 	virtual void ScrollDown() = 0;
// 	virtual void ScrollUp() = 0;
// 	virtual void NextPage() = 0;
// 	virtual void PrevPage() = 0;
// 	virtual void BookMark() = 0;
// 	virtual void Underline() = 0;
// 	
// };
// 
// class TxtReader : public cEBookReader
// {
// 	virtual void Open(file) override
// 	{
// 
// 	}
// 	virtual void ScrollDown() override;
// 	virtual void ScrollUp() override;
// 	virtual void NextPage() override;
// 	virtual void PrevPage() override;
// 	virtual void BookMark() override;
// 	virtual void Underline() override;
// };
// 
// class HwpReader : public cEBookReader
// {
// 	virtual void Open(file) override;
// 	virtual void ScrollDown() override;
// 	virtual void ScrollUp() override;
// 	virtual void NextPage() override;
// 	virtual void PrevPage() override;
// 	virtual void BookMark() override;
// 	virtual void Underline() override;
// };
// 
// class DocReader : public cEBookReader
// {
// 	virtual void Open(file) override;
// 	virtual void ScrollDown() override;
// 	virtual void ScrollUp() override;
// 	virtual void NextPage() override;
// 	virtual void PrevPage() override;
// 	virtual void BookMark() override;
// 	virtual void Underline() override;
// };
// 
// class PdfReader : public cEBookReader
// {
// 	virtual void Open(file) override;
// 	virtual void ScrollDown() override;
// 	virtual void ScrollUp() override;
// 	virtual void NextPage() override;
// 	virtual void PrevPage() override;
// 	virtual void BookMark() override;
// 	virtual void Underline() override;
// };

class cMainGame
{
private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;

public:
	cMainGame(void);
	~cMainGame(void);

// 	cEBookReader* m_pBookReader;
// 
// 	void Open(file);
// 	void ScrollDown();
	void Setup();
	void Update();
	void Render();
	//virtual void Func() = 0;
};

