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
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, char*, WCHAR*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView** GetTextureArray();
	//ID3D11ShaderResourceView* GetTexture();


private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	//bool LoadTexture(ID3D11Device*, WCHAR*);
	//void ReleaseTexture();
	bool LoadTextures(ID3D11Device*, WCHAR*, WCHAR*);
	void ReleaseTextures();

	bool LoadModel(char* modelFilename);
	void ReleaseModel();

	D3DXVECTOR3 aiVector3DtoD3DXVector3(aiVector3D aiVec);
	//D3DXVECTOR2 aiVector3DtoD3DXVector2(aiVector3D** aiVec);

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	TextureArrayClass* m_TextureArray;
	Assimp::Importer* m_importer;
	const aiScene* m_model;
};

#endif