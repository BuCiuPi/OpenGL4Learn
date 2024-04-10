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


void mul_mat4(float* mat, float* mat2)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float value = 0;
			for (int pos = 0; pos < 4; pos++)
			{
				float additionValue = mat[i * 4 + pos] * mat2[j + pos * 4];
				value += additionValue;
			}
			mat[i * 4 + j] = value;
		}
	}
	for (int i = 0; i < 16; i++)
	{
		std::cout << mat[i] << " | ";
	}
	std::cout << std::endl;
}

void MatrixTranslation(float* matrix, float position[3])
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
	
	mul_mat4(matrix, returnedMatrix);
}

void MatrixScaling(float* matrix, float scale[3])
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
	mul_mat4(matrix, returnedMatrix);
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

