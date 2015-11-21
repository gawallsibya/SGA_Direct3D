#pragma once
class cMatrix
{
private:
	class cRow
	{
		friend class cMatrix;

	private:
		std::vector<float> m_vecData;

	public:
		cRow();
		cRow(int nDimension);
		float& operator[](int nIndex);
		void Resize(int nDimension);
		void Print()
		{
			for (int i = 0; i < m_vecData.size(); ++i)
			{
				printf("%8.2f", m_vecData[i]);
			}
			printf("\n");
		}
	};

public:
	cMatrix(void);
	cMatrix(int nDimension);
	~cMatrix(void);

private:
	std::vector<cRow> m_vecData;

public:
	cRow& operator[](int nIndex);
	cMatrix operator+(cMatrix mat);
	cMatrix operator-(cMatrix mat);
	cMatrix operator*(float f);
	friend cMatrix operator*(float f, cMatrix mat);
	
	cMatrix operator*(cMatrix mat);
	bool operator==(cMatrix mat);
	bool operator!=(cMatrix mat);
	
	cMatrix Transpose();
	cMatrix Inverse(float& fDeterminent);
	cMatrix Adjoint();
	float Determinent();
	float Cofactor(int nRow, int nCol);
	float Minor(int nRow, int nCol);

	int Dimension();

	void Print();
};

