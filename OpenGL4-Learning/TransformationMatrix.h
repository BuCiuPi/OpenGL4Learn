#pragma once
#ifndef TRANSFORMARTION_MATRIX_H
#define TRANSFORMARTION_MATRIX_H

#include <iostream>
#define M_PI 3.141592653589793


const float indentityMatrix[]
{
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f,
};

float* mul_mat4(float* mat, float* mat2);
float* MatrixTranslation(float* matrix, float position[3]);
float* MatrixScaling(float* matrix, float scale[3]);
float* MatrixRotateX(float* matrix, float value);
float* MatrixRotateY(float* matrix, float value);
float* MatrixRotateZ(float* matrix, float value);
float* NewMatrix();
float ToRadian(float value);
float* NegateArray(float* array, int size);
void PrintMatrix4(float* array, int size);

#endif // !TRANSFORMARTION_MATRIX_H

