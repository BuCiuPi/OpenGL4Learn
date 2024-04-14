#include "TransformationMatrix.h"

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
				int mat1Index = j + pos * 4;
				int mat2Index = i * 4 + pos;
				float additionValue = mat[mat1Index] * mat2[mat2Index];
				//std::cout << "+" << mat1Index + 1 << "*" << mat2Index + 1;
				value += additionValue;
			}
			//std::cout << std::endl;
			int currentIndex = i * 4 + j;
			returnedMatrix[currentIndex] = value; // set value for new mat
		}
	}
	return returnedMatrix;
}

float* MatrixTranslation(float* matrix, float position[3])
{
	float* returnedMatrix = new float[16];
	for (int i = 0; i < 16; i++)
	{
		if (i == 12)
		{
			returnedMatrix[i] = position[0];
			continue;
		}

		if (i == 13)
		{
			returnedMatrix[i] = position[1];
			continue;
		}

		if (i == 14)
		{
			returnedMatrix[i] = position[2];
			continue;
		}

		returnedMatrix[i] = indentityMatrix[i];
	}

	float* resultMatrix = mul_mat4(matrix, returnedMatrix);

	return resultMatrix;
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
				0.0f, cos(value), sin(value), 0.0f,
				0.0f, -sin(value), cos(value), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
		};
	return mul_mat4(matrix, multipleMatrix);
}

float* MatrixRotateY(float* matrix, float value)
{

	float* multipleMatrix = new float[16]
		{
			cos(value), 0.0f, -sin(value), 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				sin(value), 0.0f, cos(value), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
		};
	return mul_mat4(matrix, multipleMatrix);
}

float* MatrixRotateZ(float* matrix, float value)
{

	float* multipleMatrix = new float[16]
		{
			cos(value), sin(value), 0.0f, 0.0f,
				-sin(value), cos(value), 0.0f, 0.0f,
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

float ToRadian(float value) {
	return value * (M_PI / 180);
}

float* NegateArray(float* array, int size) {

	float* returnedArray = new float[size];
	for (int i = 0; i < size; i++)
	{
		returnedArray[i] = array[i] * (-1);
	}
	return returnedArray;
}

void PrintMatrix4(float* array, int size)
{
	std::cout << "-----------------" << std::endl;;
	for (int i = 0; i < size; i++)
	{
		std::cout << array[i] << " | ";
		if ((i + 1) % 4 == 0)
		{
			std::cout << std::endl;
		}
	}
	std::cout << "-----------------" << std::endl;;
}


