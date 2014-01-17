#include "RagdollClass.h"


RagdollClass::RagdollClass(void)
{
	m_model = 0;
	m_rigidBodys = new btRigidBody*[num_bones];
	m_collisionShapes = new btCollisionShape*[num_bones];
	m_bones = new aiBone*[num_bones];
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
	m_shaderType = shaderType;

	for(int i = 0; i < m_model->m_model->mMeshes[0]->mNumBones; ++i)
	{
		if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("Head"))
		{
			m_bones[bones::Head] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("Neck"))
		{
			m_bones[bones::Neck] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("Spine2"))
		{
			m_bones[bones::Spine2] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("Spine1"))
		{
			m_bones[bones::Spine1] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("Spine0"))
		{
			m_bones[bones::Spine0] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("RArm0"))
		{
			m_bones[bones::RArm0] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("RArm1"))
		{
			m_bones[bones::RArm1] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("RArm2"))
		{
			m_bones[bones::RArm2] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("RHand"))
		{
			m_bones[bones::RHand] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("LArm0"))
		{
			m_bones[bones::LArm0] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("LArm1"))
		{
			m_bones[bones::LArm1] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("LArm2"))
		{
			m_bones[bones::LArm2] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("LHand"))
		{
			m_bones[bones::LHand] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("RLeg0"))
		{
			m_bones[bones::RLeg0] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("RLeg1"))
		{
			m_bones[bones::RLeg1] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("RLeg2"))
		{
			m_bones[bones::RLeg2] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("RFoot"))
		{
			m_bones[bones::RFoot] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("LLeg0"))
		{
			m_bones[bones::LLeg0] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("LLeg1"))
		{
			m_bones[bones::LLeg1] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("LLeg2"))
		{
			m_bones[bones::LLeg2] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
		else if(m_model->m_model->mMeshes[0]->mBones[i]->mName == aiString("LFoot"))
		{
			m_bones[bones::LFoot] = m_model->m_model->mMeshes[0]->mBones[i];
			continue;
		}
	}

	// Head
	float radius = 1.0f;
	float height = 1.0f;
	float mass = 1.0;
	btVector3 inertia(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::Head] = new btCapsuleShape(radius, height);

	aiMatrix4x4 boneMatrix = m_bones[bones::Head]->mOffsetMatrix;
	aiMatrix4x4 rootMatrix = m_model->m_model->mRootNode->mTransformation;
	//rootMatrix.Inverse();
	aiMatrix4x4 boneWorldMatrix = rootMatrix * boneMatrix;
	aiVector3D position = boneWorldMatrix * modelPosition;
	aiVector3D rotation = modelRotation;	

	Initialize(bones::Head, position, rotation, mass, inertia.x(), inertia.y(), inertia.z());

	return true;
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

bool RagdollClass::Initialize(int bone, aiVector3D modelPosition, aiVector3D modelRotation, btScalar mass, btScalar inertiax, btScalar inertiay, btScalar inertiaz)
{
	btDefaultMotionState* m_motionState = new btDefaultMotionState(btTransform(btQuaternion(modelRotation.y, modelRotation.x, modelRotation.z), btVector3(modelPosition.x, modelPosition.y, modelPosition.z)));
	if(!m_motionState)
		return false;
	btVector3 m_inertia(inertiax, inertiay, inertiaz);
	if(mass > 0.0f)		
		m_collisionShapes[bone]->calculateLocalInertia(mass, m_inertia);

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, m_motionState, m_collisionShapes[bone], m_inertia);
	m_rigidBodys[bone] = new btRigidBody(rigidBodyCI);
	if(!m_rigidBodys[bone])
		return false;

	return true;
}
