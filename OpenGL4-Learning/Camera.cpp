#include "Camera.h"

float* Camera::GetViewMatrix()
{
	float* T = MatrixTranslation(NewMatrix(), NegateArray(cam_pos, 3));
	float* R = MatrixRotateY(NewMatrix(), ToRadian(-cam_yaw));

	return mul_mat4(R, T);
}


void Camera::SetAspect(int width, int height)
{
	aspect = (float)width / height;
}

float* Camera::GetProjectionMatrix()
{
	float range = tan(ToRadian(fov / 2)) * near;
	float Sx = (2.0f * near) / (range * aspect + range * aspect);
	float Sy = near / range;
	float Sz = -(far + near) / (far - near);
	float Pz = -(2.0f * far * near) / (far - near);

	float* proj_mat = new float[16]
		{
			Sx, 0.0f, 0.0f, 0.0f,
				0.0f, Sy, 0.0f, 0.0f,
				0.0f, 0.0f, Sz, -1.0f,
				0.0f, 0.0f, Pz, 0.0f
		};

	return proj_mat;
}
