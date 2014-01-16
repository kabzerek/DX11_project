#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

#include <d3d11.h>
#include <d3dx10math.h>

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

	struct InstanceType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 rotation;
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
	D3DXVECTOR3 GetRotation();
	void GetPosition(float&, float&, float&);
	void GetRotation(float&, float&, float&);
	void GetRotation(D3DXQUATERNION&);

	void SetInitialPosition(aiVector3D);
	void SetInitialRotation(aiVector3D);
	void SetPosition(D3DXVECTOR3);
	void SetRotation(D3DXVECTOR3);
	void SetRotation(D3DXQUATERNION);
	void Move(aiVector3D);

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

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	TextureArrayClass* m_TextureArray;
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;

	Assimp::Importer* m_importer;
	const aiScene* m_model;
};

#endif
