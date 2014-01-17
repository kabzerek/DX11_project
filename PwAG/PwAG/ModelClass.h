#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

#include <d3d11.h>
#include <d3dx10math.h>
#include <DirectXMath.h>

#include <assimp\Importer.hpp>	//C++ importer
#include <assimp\scene.h>		//Output data structures
#include <assimp\postprocess.h>	//Post processing flags

#include "TextureClass.h"
#include "TextureArrayClass.h"

class ModelClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
		D3DXVECTOR3 tangent;
		D3DXVECTOR3 binormal;
	};
	//struct TempVertexType
	//{
	//	float x, y, z;
	//	float tu, tv;
	//	float nx, ny, nz;
	//};

	struct VectorType
	{
		float x, y, z;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();
	
	bool Initialize(ID3D11Device*, char*, WCHAR*, WCHAR*, WCHAR*, aiVector3D, aiVector3D);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView** GetTextureArray();
	ID3D11ShaderResourceView* GetTexture();
	ID3D11ShaderResourceView* GetTexture(char);
	D3DXVECTOR3 GetPosition();
	D3DXQUATERNION GetRotation();
	D3DXVECTOR3 GetScale();
	void GetPosition(float&, float&, float&);
	void GetScale(float&, float&, float&);

	void SetInitialPosition(aiVector3D);
	void SetInitialRotation(aiVector3D);
	void SetPosition(D3DXVECTOR3);
	void SetRotation(D3DXVECTOR3);
	void SetRotation(D3DXQUATERNION);

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	//bool LoadTexture(ID3D11Device*, WCHAR*);
	//void ReleaseTexture();
	bool LoadTextures(ID3D11Device*, WCHAR*, WCHAR*, WCHAR*);
	void ReleaseTextures();

	bool LoadModel(char*);
	void ReleaseModel();

	D3DXVECTOR3 aiVector3DtoD3DXVector3(aiVector3D aiVec);
	D3DXVECTOR2 aiVector3DtoD3DXVector2(aiVector3D aiVec);

public:
	const aiScene* m_model;

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	TextureArrayClass* m_TextureArray;
	D3DXVECTOR3 m_Position;
	D3DXQUATERNION m_Rotation;
	D3DXVECTOR3 m_Scale;

	Assimp::Importer* m_importer;
};

#endif
