#pragma once

#ifndef TRANSFORMARTION_MATRIX_H
#define TRANSFORMARTION_MATRIX_H

#include <iostream>

const float indentityMatrix[]
{
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f,
};


float* mul_mat4(float* mat, float* mat2)
{
	float* returnedMatrix = new float[16];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float value = 0;
			for (int pos = 0; pos < 4; pos++)
			{
				float additionValue =  mat[i * 4 + pos] * mat2[j + pos * 4] ;
				value += additionValue;
			}
			returnedMatrix[i * 4 + j] = value; // set value for new mat
		}
	}
	return returnedMatrix;
}

float* MatrixTranslation(float* matrix, float position[3])
{
	float* returnedMatrix = new float[16];
	for (int i = 0; i < 16; i++)
	{
		if (i == 3)
		{
			returnedMatrix[i] = position[0];
			continue;
		}

		if (i == 7)
		{
			returnedMatrix[i] = position[1];
			continue;
		}

		if (i == 11)
		{
			returnedMatrix[i] = position[2];
			continue;
		}

		returnedMatrix[i] = indentityMatrix[i];
	}

	return mul_mat4(matrix, returnedMatrix);
}

float* MatrixScaling(float* matrix, float scale[3])
{

	float* returnedMatrix = new float[16];
	for (int i = 0; i < 16; i++)
	{
		if (i == 0)
		{
			returnedMatrix[i] = scale[0];
			continue;
		}

		if (i == 5)
		{
			returnedMatrix[i] = scale[1];
			continue;
		}

		if (i == 10)
		{
			returnedMatrix[i] = scale[2];
			continue;
		}

		returnedMatrix[i] = indentityMatrix[i];
	}
	return mul_mat4(matrix, returnedMatrix);
}
float* MatrixRotateX(float* matrix, float value)
{

	float* multipleMatrix = new float[16]
		{
			1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, cos(value), -sin(value), 0.0f,
				0.0f, sin(value), cos(value), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
		};
	return mul_mat4(matrix, multipleMatrix);
}

float* MatrixRotateY(float* matrix, float value)
{

	float* multipleMatrix = new float[16]
		{
			cos(value), 0.0f, sin(value), 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				-sin(value), 0.0f, cos(value), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
		};
	return mul_mat4(matrix, multipleMatrix);
}

float* MatrixRotateZ(float* matrix, float value)
{

	float* multipleMatrix = new float[16]
		{
			cos(value), -sin(value), 0.0f, 0.0f,
				sin(value), cos(value), 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
		};
	return mul_mat4(matrix, multipleMatrix);
}


float* NewMatrix() {
	float* indentityMatrix = new float[16]
		{
			1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
		};
	return indentityMatrix;
}

#endif // !TRANSFORMARTION_MATRIX_H

