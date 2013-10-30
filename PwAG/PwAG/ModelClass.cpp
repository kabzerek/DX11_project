#include "ModelClass.h"

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}


bool ModelClass::Initialize(ID3D11Device* device, WCHAR* textureFilename)
{
	bool result;


	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if(!result)
	{
		return false;
	}

	return true;
}


void ModelClass::Shutdown()
{
	// Release the model texture.
	ReleaseTexture();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	return;
}


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


ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_Texture->GetTexture();
}


bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	std::string pFile = "data/teapots.DAE";

	//Create an instance of the Importer class
	Assimp::Importer importer;

	//And have it read the given file with some example postprocessing
	unsigned int processFlags =
		//aiProcess_CalcTangentSpace         | // calculate tangents and bitangents if possible
		//aiProcess_JoinIdenticalVertices    | // join identical vertices/ optimize indexing
		//aiProcess_ValidateDataStructure    | // perform a full validation of the loader's output
		//aiProcess_Triangulate              | // Ensure all verticies are triangulated (each 3 vertices are triangle)
		//aiProcess_ConvertToLeftHanded      | // convert everything to D3D left handed space (by default right-handed, for OpenGL)
		//aiProcess_SortByPType              | // ?
		//aiProcess_ImproveCacheLocality     | // improve the cache locality of the output vertices
		//aiProcess_RemoveRedundantMaterials | // remove redundant materials
		//aiProcess_FindDegenerates          | // remove degenerated polygons from the import
		//aiProcess_FindInvalidData          | // detect invalid model data, such as invalid normal vectors
		//aiProcess_GenUVCoords              | // convert spherical, cylindrical, box and planar mapping to proper UVs
		//aiProcess_TransformUVCoords        | // preprocess UV transformations (scaling, translation ...)
		//aiProcess_FindInstances            | // search for instanced meshes and remove them by references to one master
		//aiProcess_LimitBoneWeights         | // limit bone weights to 4 per vertex
		//aiProcess_OptimizeMeshes           | // join small meshes, if possible;
		//aiProcess_SplitByBoneCount         | // split meshes with too many bones. Necessary for our (limited) hardware skinning shader
		0;

	const aiScene* scene = importer.ReadFile(pFile, processFlags);

	//if the import failed, report it
	if(!scene)
	{
		return false;
	}
	
	// Set the number of vertices in the vertex array.
	//m_vertexCount = 4;
	m_vertexCount = scene->mMeshes[0]->mNumVertices;

	// Set the number of indices in the index array.
	//m_indexCount = 6;
	m_indexCount = scene->mMeshes[0]->mNumFaces * 3;

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
*/
	for(unsigned int v = 0; v < m_vertexCount; ++v)
	{
		vertices[v].position = aiVector3DtoD3DXVector3(scene->mMeshes[0]->mVertices[v]);
		vertices[v].normal = aiVector3DtoD3DXVector3(scene->mMeshes[0]->mNormals[v]);
		vertices[v].texture = D3DXVECTOR2(1.0f, 0.0f);
		//vertices[v].texture = aiVector3DtoD3DXVector2(scene->mMeshes[0]->mTextureCoords[v]);
	}
/*
	// Load the index array with data.
	indices[0] = 0;  // Bottom left
	indices[1] = 1;  // Top left
	indices[2] = 2;  // Top right
	indices[3] = 0;  // Bottom left
	indices[4] = 2; // Top right
	indices[5] = 3; // Bottom right
*/
	for(unsigned int face = 0; face < scene->mMeshes[0]->mNumFaces; ++face)
	{
		for(unsigned int idx = 0; idx < 3; ++idx)
		{
			indices[face*3+idx] = scene->mMeshes[0]->mFaces[face].mIndices[idx];
		}
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


bool ModelClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;


	// Create the texture object.
	m_Texture = new TextureClass;
	if(!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, filename);
	if(!result)
	{
		return false;
	}

	return true;
}


void ModelClass::ReleaseTexture()
{
	// Release the texture object.
	if(m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

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

//D3DXVECTOR2 ModelClass::aiVector3DtoD3DXVector2(aiVector3D** aiVec)
//{
//	D3DXVECTOR2 dxVec;
//	dxVec.x = aiVec.x;
//	dxVec.y = aiVec.y;
//
//	return dxVec;
//}