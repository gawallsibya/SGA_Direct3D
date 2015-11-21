#include "StdAfx.h"
#include "cMatrix.h"


cMatrix::cMatrix(void)
{
}

cMatrix::cMatrix( int nDimension )
{
	m_vecData.resize(nDimension);
	for (int i = 0; i < nDimension; ++i)
	{
		m_vecData[i].Resize(nDimension);
	}
}


cMatrix::~cMatrix(void)
{
}

cMatrix::cRow& cMatrix::operator[]( int nIndex )
{
	return m_vecData[nIndex];
}

cMatrix cMatrix::operator+( cMatrix mat )
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] + mat[i][j];
		}
	}

	return matRet;
}

int cMatrix::Dimension()
{
	return m_vecData.size();
}

cMatrix cMatrix::operator-( cMatrix mat )
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] - mat[i][j];
		}
	}

	return matRet;
}

cMatrix cMatrix::operator*( float f )
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] * f;
		}
	}

	return matRet;
}

cMatrix cMatrix::operator*( cMatrix mat )
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = 0;
			for (int k = 0; k < Dimension(); ++k)
			{
				matRet[i][j] += ((*this)[i][k] * mat[k][j]);
			}
		}
	}
	return matRet;
}

bool cMatrix::operator==( cMatrix mat )
{
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			if(fabs((*this)[i][j] - mat[i][j]) > 0.00001f) 
				return false;
		}
	}
	return true;
}

bool cMatrix::operator!=( cMatrix mat )
{
	return !((*this) == mat);
}

cMatrix cMatrix::Transpose()
{
	cMatrix matRet(Dimension());
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[j][i];
		}
	}
	return matRet;
}

cMatrix cMatrix::Inverse( float& fDeterminent )
{
	fDeterminent = Determinent();
	if(fabs(fDeterminent) < 0.00001f)
		return (*this);
	return (1.0f / fDeterminent) * Adjoint();
}

cMatrix cMatrix::Adjoint()
{
	cMatrix matRet(Dimension());
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = Cofactor(j, i);
		}
	}
	return matRet;
}

float cMatrix::Determinent()
{
	if(Dimension() == 2)
	{
		return (*this)[0][0] * (*this)[1][1] -
			(*this)[1][0] * (*this)[0][1];
	}

	float fDeterminent = 0.0f;
	for (int i = 0; i < Dimension(); ++i)
	{
		fDeterminent += ((*this)[i][0] * Cofactor(i, 0));
	}
	return fDeterminent;
}

float cMatrix::Cofactor(int nRow, int nCol)
{
	int nConst = (nRow + nCol) % 2 == 1 ? -1 : 1;
	return nConst * Minor(nRow, nCol);
}

float cMatrix::Minor( int nRow, int nCol )
{
	cMatrix mat(Dimension() - 1);

	int nMinorRow = 0;
	int nMinorCol = 0;

	for (int i = 0; i < Dimension(); ++i)
	{
		if (nRow == i)
		{
			continue;
		}
		
		nMinorCol = 0;

		for (int j = 0; j < Dimension(); ++j)
		{
			if (nCol == j)
			{
				continue;
			}
			mat[nMinorRow][nMinorCol] = (*this)[i][j];
			++nMinorCol;
		}

		++nMinorRow;
	}

	return mat.Determinent();
}

cMatrix cMatrix::Identity( int nDimension )
{
	cMatrix matRet(nDimension);
	for (int i = 0; i < nDimension; ++i)
	{
		for (int j = 0; j < nDimension; ++j)
		{
			matRet[i][j] = (i == j) ? 1.0f : 0.0f;
		}
	}
	return matRet;
}

cMatrix cMatrix::Translation( float x, float y, float z )
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[3][0] = x;
	matRet[3][1] = y;
	matRet[3][2] = z;
	return matRet;
}

cMatrix cMatrix::Translation( cVector3& v )
{
	return cMatrix::Translation(v.x, v.y, v.z);
}

cMatrix cMatrix::RotationX( float fAngle )
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[1][1] = cosf(fAngle);
	matRet[1][2] = sinf(fAngle);
	matRet[2][1] = -sinf(fAngle);
	matRet[2][2] = cosf(fAngle);
	return matRet;
}

cMatrix cMatrix::RotationY( float fAngle )
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = cosf(fAngle);
	matRet[0][2] = -sinf(fAngle);
	matRet[2][0] = sinf(fAngle);
	matRet[2][2] = cosf(fAngle);
	return matRet;
}

cMatrix cMatrix::RotationZ( float fAngle )
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = cosf(fAngle);
	matRet[0][1] = sinf(fAngle);
	matRet[1][0] = -sinf(fAngle);
	matRet[1][1] = cosf(fAngle);
	return matRet;
}

cMatrix cMatrix::Scaling( float x, float y, float z )
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = x;
	matRet[1][1] = y;
	matRet[2][2] = z;
	return matRet;
}

cMatrix cMatrix::Scaling( cVector3& v )
{
	return cMatrix::Scaling(v.x, v.y, v.z);
}

cMatrix cMatrix::View( cVector3& vEye, cVector3& vLookAt, cVector3& vUp )
{
	cVector3 e = vEye;

	cVector3 l = (vLookAt - vEye).Normalize();
	
	cVector3 r = (cVector3::Cross(vUp, l)).Normalize();

	cVector3 u = (cVector3::Cross(l, r)).Normalize();

	cMatrix matRet = cMatrix::Identity(4);

	matRet[0][0] = r.x; matRet[0][1] = u.x; matRet[0][2] = l.x;
	matRet[1][0] = r.y; matRet[1][1] = u.y; matRet[1][2] = l.y;
	matRet[2][0] = r.z; matRet[2][1] = u.z; matRet[2][2] = l.z;
	matRet[3][0] = -cVector3::Dot(r, e);
	matRet[3][1] = -cVector3::Dot(u, e);
	matRet[3][2] = -cVector3::Dot(l, e);
	matRet[3][3] = 1.0f;

	return matRet;
}

cMatrix cMatrix::Projection( float fFovY, float fAspect, float fNearZ, float fFarZ )
{
	cMatrix matRet = cMatrix::Identity(4);

	float fScaleY = 1.0f / tanf(fFovY / 2.0f);
	float fScaleX = fScaleY / fAspect;

	matRet[0][0] = fScaleX;
	matRet[1][1] = fScaleY;
	matRet[2][2] = fFarZ / (fFarZ - fNearZ);
	matRet[2][3] = 1.0f;
	matRet[3][2] = -(fNearZ * fFarZ) / (fFarZ - fNearZ);
	matRet[3][3] = 0.0f;

	return matRet;
}

cMatrix cMatrix::Viewport( float fX, float fY, float fW, float fH, float fMinZ, float fMaxZ )
{
	cMatrix matRet = cMatrix::Identity(4);

	matRet[0][0] = fW / 2.0f;
	matRet[1][1] = -fH / 2.0f;
	matRet[2][2] = fMaxZ - fMinZ;
	matRet[3][0] = fX + (fW / 2.0f);
	matRet[3][1] = fY + (fH / 2.0f);
	matRet[3][2] = fMinZ;
	
	return matRet;
}

cMatrix operator*( float f, cMatrix mat )
{
	return mat * f;
}



cMatrix::cRow::cRow()
{

}

cMatrix::cRow::cRow( int nDimension )
{

}

float& cMatrix::cRow::operator[]( int nIndex )
{
	return m_vecData[nIndex];
}

void cMatrix::cRow::Resize( int nDimension )
{
	m_vecData.resize(nDimension);
}
