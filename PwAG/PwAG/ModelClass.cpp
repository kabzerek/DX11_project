#include "ModelClass.h"

//aiScene::~aiScene()
//{
//}

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
	m_TextureArray = 0;
}

ModelClass::ModelClass(const ModelClass& other)
{
}

ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename1, WCHAR* textureFilename2, 
							WCHAR* textureFilename3, aiVector3D modelPosition)
{
	bool result;

	// Load in the model data
	result = LoadModel(modelFilename);
	if(!result)
	{
		return false;
	}

	// Set position of the model
	SetInitialPosition(modelPosition);

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	// Load the texture for this model.
	
	//result = LoadTexture(device, textureFilename);
	result = LoadTextures(device, textureFilename1, textureFilename2, textureFilename3);
	if(!result)
	{
		return false;
	}

	return true;
}


void ModelClass::Shutdown()
{
	// Release the model texture.
	//ReleaseTexture();
	ReleaseTextures();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	// Release the model
	ReleaseModel();

	return;
}

ID3D11ShaderResourceView** ModelClass::GetTextureArray()
{
	return m_TextureArray->GetTextureArray();
}

bool ModelClass::LoadTextures(ID3D11Device* device, WCHAR* filename1, WCHAR* filename2, WCHAR* filename3)
{
	bool result;


	// Create the texture array object.
	m_TextureArray = new TextureArrayClass;
	if(!m_TextureArray)
	{
		return false;
	}

	// Initialize the texture array object.
	result = m_TextureArray->Initialize(device, filename1, filename2, filename3);
	if(!result)
	{
		return false;
	}

	return true;
}

void ModelClass::ReleaseTextures()
{
	// Release the texture array object.
	if(m_TextureArray)
	{
		m_TextureArray->Shutdown();
		delete m_TextureArray;
		m_TextureArray = 0;
	}

	return;
}

bool ModelClass::LoadModel(char* modelFilename)
{
	//Create a new instance of the Importer class
	m_importer = new Assimp::Importer();

	//if creating the importer failed, report it
	if(!m_importer)
	{
		return false;
	}

	//And have it read the given file with some example postprocessing
	unsigned int processFlags =
		aiProcess_CalcTangentSpace         | // calculate tangents and bitangents if possible
		//aiProcess_JoinIdenticalVertices    | // join identical vertices/ optimize indexing
		//aiProcess_ValidateDataStructure    | // perform a full validation of the loader's output
		aiProcess_Triangulate			   | // Ensure all verticies are triangulated (each 3 vertices are triangle)
		aiProcess_ConvertToLeftHanded      | // convert everything to D3D left handed space (by default right-handed, for OpenGL)
		//aiProcess_SortByPType              | // ?
		//aiProcess_ImproveCacheLocality     | // improve the cache locality of the output vertices
		//aiProcess_RemoveRedundantMaterials | // remove redundant materials
		//aiProcess_FindDegenerates          | // remove degenerated polygons from the import
		//aiProcess_FindInvalidData          | // detect invalid model data, such as invalid normal vectors
		aiProcess_GenUVCoords              | // convert spherical, cylindrical, box and planar mapping to proper UVs
		aiProcess_TransformUVCoords        | // preprocess UV transformations (scaling, translation ...)
		//aiProcess_FindInstances            | // search for instanced meshes and remove them by references to one master
		//aiProcess_LimitBoneWeights         | // limit bone weights to 4 per vertex
		//aiProcess_OptimizeMeshes           | // join small meshes, if possible;
		//aiProcess_SplitByBoneCount         | // split meshes with too many bones. Necessary for our (limited) hardware skinning shader
		0;

	m_model = m_importer->ReadFile(modelFilename, processFlags);

	//if the import failed, report it
	if(!m_model)
	{
		return false;
	}

	return true;
}

void ModelClass::ReleaseModel()
{
	//FreeScene is called automatically by destructor

	//if(m_model)
	//{
	//	delete m_model;
	//	m_model = 0;
	//}

	if(m_importer)
	{
		delete m_importer;
		m_importer = 0;
		m_model = 0;
	}
}

void ModelClass::SetInitialPosition(aiVector3D modelPosition)
{
	for(unsigned int m = 0; m < m_model->mNumMeshes; ++m)
			for(unsigned int v = 0; v < m_model->mMeshes[m]->mNumVertices; ++v)
				m_model->mMeshes[m]->mVertices[v] += modelPosition;

	SetPosition(aiVector3DtoD3DXVector3(modelPosition));
}

void ModelClass::SetPosition(D3DXVECTOR3 modelPosition)
{
	m_Position = modelPosition;
}

D3DXVECTOR3 ModelClass::GetPosition()
{
	return m_Position;
}

void ModelClass::GetPosition(float& x, float&y, float& z)
{
	x = m_Position.x;
	y = m_Position.y;
	z = m_Position.z;
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	//return m_Texture->GetTexture();
	return m_TextureArray->GetTextureArray()[0];
}

//bool ModelClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
//{
//	bool result;
//
//
//	// Create the texture object.
//	m_Texture = new TextureClass;
//	if(!m_Texture)
//	{
//		return false;
//	}
//
//	// Initialize the texture object.
//	result = m_Texture->Initialize(device, filename);
//	if(!result)
//	{
//		return false;
//	}
//
//	return true;
//}
//
//
//void ModelClass::ReleaseTexture()
//{
//	// Release the texture object.
//	if(m_Texture)
//	{
//		m_Texture->Shutdown();
//		delete m_Texture;
//		m_Texture = 0;
//	}
//
//	return;
//}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	
	// Set the number of vertices in the vertex array.
	m_vertexCount = 0;
	// Set the number of indices in the index array.
	m_indexCount = 0;

	for(int m = 0; m < m_model->mNumMeshes; ++m)
	{
		m_vertexCount += m_model->mMeshes[m]->mNumVertices;
		m_indexCount  += m_model->mMeshes[m]->mNumFaces * 3;
	}

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}
/*
	// Load the vertex array with data.
	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertices[0].texture = D3DXVECTOR2(0.0f, 1.0f);
	vertices[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);  // Top left.
	vertices[1].texture = D3DXVECTOR2(0.0f, 0.0f);
	vertices[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vertices[2].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);  // Top right.
	vertices[2].texture = D3DXVECTOR2(1.0f, 0.0f);
	vertices[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vertices[3].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[3].texture = D3DXVECTOR2(1.0f, 1.0f);
	vertices[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// Load the index array with data.
	indices[0] = 0;  // Bottom left
	indices[1] = 1;  // Top left
	indices[2] = 2;  // Top right
	indices[3] = 0;  // Bottom left
	indices[4] = 2; // Top right
	indices[5] = 3; // Bottom right
*/

	unsigned int ver = 0;
	unsigned int ind = 0;

	unsigned int idxOffset = 0;

	for(unsigned int m = 0; m < m_model->mNumMeshes; ++m)
	{
		for(unsigned int v = 0; v < m_model->mMeshes[m]->mNumVertices; ++v)
		{
			vertices[ver].position = aiVector3DtoD3DXVector3(m_model->mMeshes[m]->mVertices[v]);
			vertices[ver].normal = aiVector3DtoD3DXVector3(m_model->mMeshes[m]->mNormals[v]);
			vertices[ver].texture = aiVector3DtoD3DXVector2(m_model->mMeshes[m]->mTextureCoords[0][v]); 
			vertices[ver].tangent = aiVector3DtoD3DXVector3(m_model->mMeshes[m]->mTangents[v]); 
			vertices[ver].binormal = aiVector3DtoD3DXVector3(m_model->mMeshes[m]->mBitangents[v]); 
			
			ver++;
		}

		for(unsigned int face = 0; face < m_model->mMeshes[m]->mNumFaces; ++face)
		{
			for(unsigned int idx = 0; idx < 3; ++idx)
			{
				indices[ind] = m_model->mMeshes[m]->mFaces[face].mIndices[idx] + idxOffset;
				
				ind++;
			}
		}

		idxOffset += m_model->mMeshes[m]->mNumVertices;
	}

	// Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}



D3DXVECTOR3 ModelClass::aiVector3DtoD3DXVector3(aiVector3D aiVec)
{
	D3DXVECTOR3 dxVec;
	dxVec.x = aiVec.x;
	dxVec.y = aiVec.y;
	dxVec.z = aiVec.z;

	return dxVec;
}

D3DXVECTOR2 ModelClass::aiVector3DtoD3DXVector2(aiVector3D aiVec)
{
	D3DXVECTOR2 dxVec;
	dxVec.x = aiVec.x;
	dxVec.y = aiVec.y;

	return dxVec;
}