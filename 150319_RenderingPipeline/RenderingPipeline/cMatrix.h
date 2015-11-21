#pragma once
#include "cVector3.h"

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
			for (size_t i = 0; i < m_vecData.size(); ++i)
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
	cRow&	operator[](int nIndex);
	cMatrix operator+(cMatrix mat);
	cMatrix operator-(cMatrix mat);
	cMatrix operator*(float f);
	friend	cMatrix operator*(float f, cMatrix mat);
	
	cMatrix operator*(cMatrix mat);
	bool	operator==(cMatrix mat);
	bool	operator!=(cMatrix mat);
	
	cMatrix Transpose();
	cMatrix Inverse(float& fDeterminent);
	cMatrix Adjoint();
	float	Determinent();
	float	Cofactor(int nRow, int nCol);
	float	Minor(int nRow, int nCol);
	int		Dimension();
	static	cMatrix Identity(int nDimension);
	static	cMatrix Translation(float x, float y, float z);
	static	cMatrix Translation(cVector3& v);
	static	cMatrix RotationX(float fAngle);
	static	cMatrix RotationY(float fAngle);
	static	cMatrix RotationZ(float fAngle);
	static	cMatrix Scaling(float x, float y, float z);
	static	cMatrix Scaling(cVector3& v);
	static	cMatrix View(cVector3& vEye, cVector3& vLookAt, cVector3& vUp);
	static	cMatrix Projection(float fFovY, float fAspect, float fNearZ, float fFarZ);
	static	cMatrix Viewport(float fX, float fY, float fW, float fH, float fMinZ, float fMaxZ);
};

