#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include<iostream>
#include "TransformationMatrix.h"

class Camera
{
public:
	float cam_speed = 1.0f;
	float cam_yaw_speed = 10.0f;
	float cam_pos[3] = { 0.0f, 0.0f, 2.0f };
	float cam_yaw = 0.0f;

	float near = 0.1f;
	float far = 100.0f;
	float fov = 67.0f;
	float aspect;

	bool cam_moved;
	
	float* GetViewMatrix();
	void SetAspect(int width, int height);
	float* GetProjectionMatrix();
};

#endif // !CAMERA_H