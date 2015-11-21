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

void cMatrix::Print()
{
	for (int i = 0; i < Dimension(); ++i)
	{
		m_vecData[i].Print();
	}
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
