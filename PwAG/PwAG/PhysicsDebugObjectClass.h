#ifndef _PHYSICSDEBUGOBJECTCLASS_H_
#define _PHYSICSDEBUGOBJECTCLASS_H_

#include <d3d11.h>
#include <d3dx10math.h>
#include <DirectXMath.h>

class PhysicsDebugObjectClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR3 color;
	};

public:
	PhysicsDebugObjectClass(void);
	PhysicsDebugObjectClass(const PhysicsDebugObjectClass&);
	~PhysicsDebugObjectClass(void);

	bool Initialize(ID3D11Device*, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

private:
	bool InitializeBuffers(ID3D11Device*, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
};

#endif
