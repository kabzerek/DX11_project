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
	btVector3 he(0.5f, 0.5f, 0.5f);
	float mass = 1.0;
	btVector3 in(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::Head] = new btBoxShape(he);
	Initialize(bones::Head, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// Neck
	he = btVector3(0.2f, 0.3f, 0.2f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::Neck] = new btBoxShape(he);
	Initialize(bones::Neck, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());
	
	// Spine2
	he = btVector3(0.1f, 0.6f, 0.1f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::Spine2] = new btBoxShape(he);
	Initialize(bones::Spine2, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// Spine1
	he = btVector3(0.1f, 0.4f, 0.1f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::Spine1] = new btBoxShape(he);
	Initialize(bones::Spine1, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// Spine0
	he = btVector3(0.0f, 0.0f, 0.0f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::Spine0] = new btBoxShape(he);
	Initialize(bones::Spine0, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// RArm0
	he = btVector3(0.3f, 0.3f, 0.3f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::RArm0] = new btBoxShape(he);
	Initialize(bones::RArm0, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// RArm1
	he = btVector3(0.3f, 0.6f, 0.3f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::RArm1] = new btBoxShape(he);
	Initialize(bones::RArm1, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// RArm2
	he = btVector3(0.3f, 0.4f, 0.3f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::RArm2] = new btBoxShape(he);
	Initialize(bones::RArm2, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// RHand
	he = btVector3(0.4f, 0.6f, 0.4f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::RHand] = new btBoxShape(he);
	Initialize(bones::RHand, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// LArm0
	he = btVector3(0.3f, 0.3f, 0.3f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::LArm0] = new btBoxShape(he);
	Initialize(bones::LArm0, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// LArm1
	he = btVector3(0.3f, 0.6f, 0.3f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::LArm1] = new btBoxShape(he);
	Initialize(bones::LArm1, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// LArm2
	he = btVector3(0.3f, 0.4f, 0.3f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::LArm2] = new btBoxShape(he);
	Initialize(bones::LArm2, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// LHand
	he = btVector3(0.4f, 0.6f, 0.4f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::LHand] = new btBoxShape(he);
	Initialize(bones::LHand, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// RLeg0
	he = btVector3(0.0f, 0.0f, 0.0f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::RLeg0] = new btBoxShape(he);
	Initialize(bones::RLeg0, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// RLeg1
	he = btVector3(0.3f, 0.6f, 0.3f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::RLeg1] = new btBoxShape(he);
	Initialize(bones::RLeg1, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// RLeg2
	he = btVector3(0.3f, 0.4f, 0.3f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::RLeg2] = new btBoxShape(he);
	Initialize(bones::RLeg2, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// RFoot
	he = btVector3(0.1f, 0.5f, 0.1f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::RFoot] = new btBoxShape(he);
	Initialize(bones::RFoot, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// LLeg0
	he = btVector3(0.0f, 0.0f, 0.0f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::LLeg0] = new btBoxShape(he);
	Initialize(bones::LLeg0, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// LLeg1
	he = btVector3(0.3f, 0.6f, 0.3f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::LLeg1] = new btBoxShape(he);
	Initialize(bones::LLeg1, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// LLeg2
	he = btVector3(0.3f, 0.4f, 0.3f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::LLeg2] = new btBoxShape(he);
	Initialize(bones::LLeg2, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

	// LFoot
	he = btVector3(0.1f, 0.5f, 0.1f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::LFoot] = new btBoxShape(he);
	Initialize(bones::LFoot, he.x(), he.y(), he.z(), modelPosition, modelRotation, mass, in.x(), in.y(), in.z());

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
}

void RagdollClass::Update()
{

}

bool RagdollClass::Initialize(int bone, btScalar size_x, btScalar size_y, btScalar size_z, aiVector3D position, aiVector3D rotation, btScalar mass, btScalar inertia_x, btScalar inertia_y, btScalar inertia_z)
{
	

	aiMatrix4x4 rotationMatrix, XrotationMatrix, YrotationMatrix, ZrotationMatrix;
	aiMatrix4x4 translationMatrix;// offsetMatrix;

	translationMatrix = aiMatrix4x4::Translation(position, translationMatrix);

	//offsetMatrix = aiMatrix4x4::Translation( aiVector3D(size_x/2,size_y/2,size_z/2), offsetMatrix);
	//translationMatrix = offsetMatrix*translationMatrix;

	XrotationMatrix = XrotationMatrix.FromEulerAnglesXYZ(rotation.x, 0.0f, 0.0f);
	YrotationMatrix = YrotationMatrix.FromEulerAnglesXYZ(0.0f, rotation.y, 0.0f);
	ZrotationMatrix = ZrotationMatrix.FromEulerAnglesXYZ(0.0f, 0.0f, rotation.z);
	aiMatrix4x4 boneMatrix = m_bones[bone]->mOffsetMatrix;

	rotationMatrix = ZrotationMatrix * XrotationMatrix * YrotationMatrix;

	aiMatrix4x4 boneWorldMatrix =  translationMatrix * rotationMatrix.Inverse() * boneMatrix.Inverse();

	aiVector3D bonePosition;
	aiQuaternion boneRotation;
	aiVector3D scaling;
	boneWorldMatrix.Decompose(scaling, boneRotation, bonePosition);

	btDefaultMotionState* m_motionState = new btDefaultMotionState(btTransform(btQuaternion(boneRotation.x, boneRotation.y, boneRotation.z, boneRotation.w), btVector3(bonePosition.x, bonePosition.y, bonePosition.z)));
	if(!m_motionState)
		return false;
	btVector3 m_inertia(inertia_x, inertia_y, inertia_z);
	if(mass > 0.0f)	
		m_collisionShapes[bone]->calculateLocalInertia(mass, m_inertia);

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, m_motionState, m_collisionShapes[bone], m_inertia);
	m_rigidBodys[bone] = new btRigidBody(rigidBodyCI);
	if(!m_rigidBodys[bone])
		return false;

	return true;
}
