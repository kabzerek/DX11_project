#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_

#include <d3dx10math.h>

class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	void Render();
	void GetViewMatrix(D3DXMATRIX&);

	void RenderBaseViewMatrix();
	void GetBaseViewMatrix(D3DXMATRIX&);
	//D3DXVECTOR3 GetPickRay(float x, float y, int screen_w, int screen_h);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	D3DXMATRIX m_viewMatrix, m_baseViewMatrix;
};

#endif