#include "RagdollClass.h"


RagdollClass::RagdollClass(void)
{
	m_model = 0;
	m_rigidBodys = new btRigidBody* [num_bones];
	m_collisionShapes = new btCollisionShape* [num_bones];
	m_bones = new "bone"* [num_bones];
}

RagdollClass::RagdollClass(const RagdollClass& other)
{
}

RagdollClass::~RagdollClass(void)
{
}

bool RagdollClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename1, WCHAR* textureFilename2, 
								   WCHAR* textureFilename3, aiVector3D modelPosition, aiVector3D modelRotation, std::string name, 
								   int shaderType)
{
	m_model = new ModelClass;
	m_model->Initialize(device, modelFilename, textureFilename1, textureFilename2, textureFilename3, modelPosition, modelRotation);

	do
	{
		if(m_model->m_model->mMeshes[0]->mBones...name == "Head")
		{

		}
	} while (m_model->m_model->mMeshes[0]->mBones...child);

	// Head
	float radius = 0.0f;
	float height = 0.0f;
	m_collisionShapes[bones::Head] = new btCapsuleShape(radius, height);

	m_model->m_model->mMeshes[0]->mBones
}
	
void RagdollClass::Shutdown()
{
	if(m_model)
	{
		m_model->Shutdown();
		delete m_model;
	}
	m_model = 0;

	for(int i = 0; i < num_bones; ++i)
	{
		if(m_rigidBodys[i])
			delete m_rigidBodys[i];
		if(m_collisionShapes[i])
			delete m_collisionShapes[i];
		if(m_bones[i])
			delete m_bones[i];
	}

	delete m_rigidBodys;
	delete m_collisionShapes;
	delete m_bones;

	//std::vector<btRigidBody*>::iterator rIt;
	//for(rIt = m_rigidBodys.begin(); rIt != m_rigidBodys.end(); ++rIt)
	//	delete (*rIt);
	//m_rigidBodys.clear();

	//std::vector<btCollisionShape*>::iterator cIt;
	//for(cIt = m_collisionShapes.begin(); cIt != m_collisionShapes.end(); ++cIt)
	//	delete (*cIt);
	//m_collisionShapes.clear();
}

void RagdollClass::Update()
{

}

bool RagdollClass::Initialize(aiVector3D modelPosition, aiVector3D modelRotation, btScalar mass, btScalar inertiax, btScalar inertiay, btScalar inertiaz, int shaderType)
{

}
