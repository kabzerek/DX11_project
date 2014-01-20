#include "RagdollClass.h"


RagdollClass::RagdollClass(void)
{
	m_model = 0;
	m_rigidBodys = new btRigidBody*[num_bones];
	m_collisionShapes = new btCollisionShape*[num_bones];
	m_bones = new aiBone*[num_bones];
	m_joints = new btTypedConstraint*[num_joints];
	m_prevTransforms = new btTransform[num_bones];
	m_transformations = new aiMatrix4x4[num_bones];
	m_models = new ModelClass*[num_bones];
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
	btConeTwistConstraint* coneC;
	m_model = new ModelClass;
	m_model->Initialize(device, modelFilename, textureFilename1, textureFilename2, textureFilename3, modelPosition, modelRotation);
	m_shaderType = shaderType;

	m_vertexInfos = new vertexInfo[m_model->m_model->mMeshes[0]->mNumVertices];

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
	btVector3 halfSize(0.7f, 0.9f, 0.7f);
	btVector3 offset(0.0f, 0.9f, 0.0f);
	float mass = 1.0;
	btVector3 in(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::Head] = new btBoxShape(halfSize);
	Initialize(bones::Head, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);
	
// Neck
	halfSize = btVector3(0.3f, 0.3f, 0.4f);
	offset = btVector3(0.0f, 0.3f, 0.08f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::Neck] = new btBoxShape(halfSize);
	Initialize(bones::Neck, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	btTransform localA, localB;
	localA.setIdentity();
	localB.setIdentity();
	//localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(0.0f, -0.85f, 0.0f));
	//localB.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localB.setOrigin(btVector3(0.0f, 0.25f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::Head], *m_rigidBodys[bones::Neck], localA, localB);
	coneC->setLimit(M_PI_8 * 0.9f, M_PI_8 * 0.9f, M_PI_4 * 0.9f, 0.9f);
	m_joints[joints::Head_to_Neck] = coneC;
	
// Spine2
	halfSize = btVector3(0.3f, 0.2f, 0.45f);
	offset = btVector3(0.0f, 0.3f, 0.05f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::Spine2] = new btBoxShape(halfSize);
	Initialize(bones::Spine2, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	//localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(0.0f, -0.3f, 0.0f));
	//localB.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localB.setOrigin(btVector3(0.0f, 0.1f, 0.05f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::Neck], *m_rigidBodys[bones::Spine2], localA, localB);
	coneC->setLimit(M_PI_8 * 0.9f, M_PI_8 * 0.9f, M_PI_4 * 0.9f, 0.9f);
	m_joints[joints::Neck_to_Spine2] = coneC;

// Spine1
	halfSize = btVector3(1.0f, 0.8f, 0.7f);
	offset = btVector3(0.0f, 0.6f, 0.1f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::Spine1] = new btBoxShape(halfSize);
	Initialize(bones::Spine1, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	//localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(0.0f, -0.2f, 0.0f));
	//localB.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localB.setOrigin(btVector3(0.0f, 0.8f, -0.05f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::Spine2], *m_rigidBodys[bones::Spine1], localA, localB);
	coneC->setLimit(M_PI_8 * 0.9f, M_PI_8 * 0.9f, 0.0f, 0.9f);
	m_joints[joints::Spine2_to_Spine1] = coneC;

// Spine0
	halfSize = btVector3(0.9f, 0.6f, 0.6f);
	offset = btVector3(0.0f, 0.0f, -0.1f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::Spine0] = new btBoxShape(halfSize);
	Initialize(bones::Spine0, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	//localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(0.0f, -0.75f, 0.0f));
	localB.getBasis().setEulerZYX(0.0f, M_PI, 0.0f);
	localB.setOrigin(btVector3(0.0f, 0.55f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::Spine1], *m_rigidBodys[bones::Spine0], localA, localB);
	coneC->setLimit(M_PI_16 * 0.9f, M_PI_16 * 0.9f, M_PI_8, 0.9f);
	m_joints[joints::Spine1_to_Spine0] = coneC;

// RArm0
	halfSize = btVector3(0.4f, 0.4f, 0.5f);
	offset = btVector3(-0.225f, 1.0f, 0.0f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::RArm0] = new btBoxShape(halfSize);
	Initialize(bones::RArm0, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	//localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(0.6f, 0.4f, 0.0f));
	localB.getBasis().setEulerZYX(0.0f, M_PI, -M_PI_2);
	localB.setOrigin(btVector3(0.0f, -0.5f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::Spine1], *m_rigidBodys[bones::RArm0], localA, localB);
	coneC->setLimit(M_PI_4 * 0.9f, M_PI_4 * 0.9f, 0.0f, 0.9f);
	m_joints[joints::Spine1_to_RArm0] = coneC;

// RArm1
	halfSize = btVector3(0.1f, 0.5f, 0.1f);
	offset = btVector3(-0.05f, 0.7f, 0.0f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::RArm1] = new btBoxShape(halfSize);
	Initialize(bones::RArm1, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(0.0f, 0.25f, 0.0f));
	localB.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localB.setOrigin(btVector3(-0.05f, -0.5f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::RArm0], *m_rigidBodys[bones::RArm1], localA, localB);
	coneC->setLimit(M_PI_4 * 0.9f, M_PI_4 * 0.9f, M_PI_4 * 0.9f);
	m_joints[joints::RArm0_to_RArm1] = coneC;

// RArm2
	halfSize = btVector3(0.1f, 0.5f, 0.1f);
	offset = btVector3(0.0f, 0.35f, 0.0f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::RArm2] = new btBoxShape(halfSize);
	Initialize(bones::RArm2, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(0.0f, 0.45f, 0.0f));
	localB.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localB.setOrigin(btVector3(0.0f, -0.45f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::RArm1], *m_rigidBodys[bones::RArm2], localA, localB);
	coneC->setLimit(M_PI_4 * 0.9f, M_PI_4 * 0.9f, M_PI_4 * 0.9f);
	m_joints[joints::RArm1_to_RArm2] = coneC;

// RHand
	halfSize = btVector3(0.3f, 0.4f, 0.3f);
	offset = btVector3(0.0f, 0.45f, 0.0f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::RHand] = new btBoxShape(halfSize);
	Initialize(bones::RHand, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(0.0f, 0.3f, 0.0f));
	localB.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localB.setOrigin(btVector3(0.0f, -0.3f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::RArm2], *m_rigidBodys[bones::RHand], localA, localB);
	coneC->setLimit(M_PI_4 * 0.9f, M_PI_4 * 0.9f, M_PI_4 * 0.9f);
	m_joints[joints::RArm2_to_RHand] = coneC;

// LArm0
	halfSize = btVector3(0.4f, 0.4f, 0.5f);
	offset = btVector3(0.225f, 1.0f, 0.0f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::LArm0] = new btBoxShape(halfSize);
	Initialize(bones::LArm0, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	//localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(-0.6f, 0.4f, 0.0f));
	localB.getBasis().setEulerZYX(0.0f, M_PI, M_PI_2);
	localB.setOrigin(btVector3(0.0f, -0.5f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::Spine1], *m_rigidBodys[bones::LArm0], localA, localB);
	coneC->setLimit(M_PI_4 * 0.9f, M_PI_4 * 0.9f, 0.0f, 0.9f);
	m_joints[joints::Spine1_to_LArm0] = coneC;

// LArm1
	halfSize = btVector3(0.1f, 0.5f, 0.1f);
	offset = btVector3(0.05f, 0.7f, 0.0f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::LArm1] = new btBoxShape(halfSize);
	Initialize(bones::LArm1, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(0.0f, 0.25f, 0.0f));
	localB.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localB.setOrigin(btVector3(0.05f, -0.5f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::LArm0], *m_rigidBodys[bones::LArm1], localA, localB);
	coneC->setLimit(M_PI_4 * 0.9f, M_PI_4 * 0.9f, M_PI_4 * 0.9f);
	m_joints[joints::LArm0_to_LArm1] = coneC;

// LArm2
	halfSize = btVector3(0.1f, 0.5f, 0.1f);
	offset = btVector3(0.0f, 0.35f, 0.0f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::LArm2] = new btBoxShape(halfSize);
	Initialize(bones::LArm2, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);
	
	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(0.0f, 0.45f, 0.0f));
	localB.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localB.setOrigin(btVector3(0.0f, -0.45f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::LArm1], *m_rigidBodys[bones::LArm2], localA, localB);
	coneC->setLimit(M_PI_4 * 0.9f, M_PI_4 * 0.9f, M_PI_4 * 0.9f);
	m_joints[joints::LArm1_to_LArm2] = coneC;

// LHand
	halfSize = btVector3(0.3f, 0.4f, 0.3f);
	offset = btVector3(0.0f, 0.45f, 0.0f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::LHand] = new btBoxShape(halfSize);
	Initialize(bones::LHand, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(0.0f, 0.3f, 0.0f));
	localB.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localB.setOrigin(btVector3(0.0f, -0.3f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::LArm2], *m_rigidBodys[bones::LHand], localA, localB);
	coneC->setLimit(M_PI_4 * 0.9f, M_PI_4 * 0.9f, M_PI_4 * 0.9f);
	m_joints[joints::LArm2_to_LHand] = coneC;

// RLeg0
	halfSize = btVector3(0.3f, 0.45f, 0.7f);
	offset = btVector3(-0.6f, 0.7f, -0.1f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::RLeg0] = new btBoxShape(halfSize);
	Initialize(bones::RLeg0, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(-0.6f, -0.6f, 0.0f));
	localB.getBasis().setEulerZYX(0.0f, 0.0f, -M_PI_2);
	localB.setOrigin(btVector3(0.1f, 0.0f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::Spine0], *m_rigidBodys[bones::RLeg0], localA, localB);
	coneC->setLimit(M_PI_4 * 0.9f, M_PI_4 * 0.9f, M_PI_16 * 0.01f);
	m_joints[joints::Spine0_to_RLeg0] = coneC;

// RLeg1
	halfSize = btVector3(0.3f, 0.7f, 0.3f);
	offset = btVector3(0.0f, 1.5f, 0.0f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::RLeg1] = new btBoxShape(halfSize);
	Initialize(bones::RLeg1, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(-0.2f, 0.0f, 0.0f));
	localB.getBasis().setEulerZYX(0.0f, 0.0f, -M_PI_2);
	localB.setOrigin(btVector3(0.0f, -0.7f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::RLeg0], *m_rigidBodys[bones::RLeg1], localA, localB);
	coneC->setLimit(M_PI_4 * 0.9f, M_PI_4 * 0.9f, M_PI_16 * 0.01f);
	m_joints[joints::RLeg0_to_RLeg1] = coneC;

// RLeg2
	halfSize = btVector3(0.3f, 0.7f, 0.3f);
	offset = btVector3(0.0f, 0.5f, 0.0f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::RLeg2] = new btBoxShape(halfSize);
	Initialize(bones::RLeg2, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(0.0f, 0.6f, 0.0f));
	localB.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localB.setOrigin(btVector3(0.0f, -0.6f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::RLeg1], *m_rigidBodys[bones::RLeg2], localA, localB);
	coneC->setLimit(M_PI_4 * 0.9f, M_PI_4 * 0.9f, M_PI_16 * 0.01f);
	m_joints[joints::RLeg1_to_RLeg2] = coneC;

// RFoot
	halfSize = btVector3(0.3f, 0.9f, 0.3f);
	offset = btVector3(0.0f, 0.35f, -0.1f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::RFoot] = new btBoxShape(halfSize);
	Initialize(bones::RFoot, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(-M_PI_2, 0.0f, 0.0f);
	localA.setOrigin(btVector3(0.0f, 0.7f, 0.0f));
	localB.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localB.setOrigin(btVector3(0.0f, -0.3f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::RLeg2], *m_rigidBodys[bones::RFoot], localA, localB);
	coneC->setLimit(M_PI_4 * 0.9f, M_PI_4 * 0.9f, M_PI_16 * 0.01f);
	m_joints[joints::RLeg2_to_RFoot] = coneC;

// LLeg0
	halfSize = btVector3(0.3f, 0.45f, 0.7f);
	offset = btVector3(0.6f, 0.7f, -0.1f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::LLeg0] = new btBoxShape(halfSize);
	Initialize(bones::LLeg0, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(0.6f, -0.6f, 0.0f));
	localB.getBasis().setEulerZYX(0.0f, 0.0f, M_PI_2);
	localB.setOrigin(btVector3(-0.1f, 0.0f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::Spine0], *m_rigidBodys[bones::LLeg0], localA, localB);
	coneC->setLimit(M_PI_4 * 0.9f, M_PI_4 * 0.9f, M_PI_16 * 0.01f);
	m_joints[joints::Spine0_to_LLeg0] = coneC;

// LLeg1
	halfSize = btVector3(0.3f, 0.7f, 0.3f);
	offset = btVector3(0.0f, 1.5f, 0.0f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::LLeg1] = new btBoxShape(halfSize);
	Initialize(bones::LLeg1, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(0.2f, 0.0f, 0.0f));
	localB.getBasis().setEulerZYX(0.0f, 0.0f, M_PI_2);
	localB.setOrigin(btVector3(0.0f, -0.7f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::LLeg0], *m_rigidBodys[bones::LLeg1], localA, localB);
	coneC->setLimit(M_PI_4 * 0.9f, M_PI_4 * 0.9f, M_PI_16 * 0.01f);
	m_joints[joints::LLeg0_to_LLeg1] = coneC;

// LLeg2
	halfSize = btVector3(0.3f, 0.7f, 0.3f);
	offset = btVector3(0.0f, 0.5f, 0.0f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::LLeg2] = new btBoxShape(halfSize);
	Initialize(bones::LLeg2, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localA.setOrigin(btVector3(0.0f, 0.6f, 0.0f));
	localB.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localB.setOrigin(btVector3(0.0f, -0.6f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::LLeg1], *m_rigidBodys[bones::LLeg2], localA, localB);
	coneC->setLimit(M_PI_4 * 0.9f, M_PI_4 * 0.9f, M_PI_16 * 0.01f);
	m_joints[joints::LLeg1_to_LLeg2] = coneC;

// LFoot
	halfSize = btVector3(0.3f, 0.9f, 0.3f);
	offset = btVector3(0.0f, 0.35f, -0.1f);
	mass = 1.0;
	in = btVector3(1.0f, 1.0f, 1.0f);
	m_collisionShapes[bones::LFoot] = new btBoxShape(halfSize);
	Initialize(bones::LFoot, halfSize.x(), halfSize.y(), halfSize.z(), modelPosition, offset.x(), offset.y(), offset.z(), modelRotation, mass, in.x(), in.y(), in.z(), device);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(-M_PI_2, 0.0f, 0.0f);
	localA.setOrigin(btVector3(0.0f, 0.7f, 0.0f));
	localB.getBasis().setEulerZYX(0.0f, 0.0f, 0.0f);
	localB.setOrigin(btVector3(0.0f, -0.3f, 0.0f));

	coneC = new btConeTwistConstraint(*m_rigidBodys[bones::LLeg2], *m_rigidBodys[bones::LFoot], localA, localB);
	coneC->setLimit(M_PI_4 * 0.9f, M_PI_4 * 0.9f, M_PI_16 * 0.01f);
	m_joints[joints::LLeg2_to_LFoot] = coneC;

	btTransform trans;
	for(int i = 0; i < num_bones; ++i)
	{
		m_rigidBodys[i]->getMotionState()->getWorldTransform(trans);
		m_prevTransforms[i] = trans;

		for(int w = 0; w < m_bones[i]->mNumWeights; ++w)
			m_vertexInfos[m_bones[i]->mWeights[w].mVertexId].m_boneWeights.push_back(new boneWeight(i, m_bones[i]->mWeights[w].mWeight));
	}

	return true;
}
	
void RagdollClass::Shutdown()
{
	for(int i = 0; i < m_model->m_model->mMeshes[0]->mNumVertices; ++i)
		m_vertexInfos[i].m_boneWeights.clear();
	//delete m_vertexInfos;
	delete m_transformations;
	delete m_prevTransforms;

	for(int i = 0; i < num_bones; ++i)
	{
		if(m_rigidBodys[i])
			delete m_rigidBodys[i];
		if(m_collisionShapes[i])
			delete m_collisionShapes[i];
		//if(m_bones[i])
		//	delete m_bones[i];
	}

	delete m_bones;
	delete m_collisionShapes;
	delete m_rigidBodys;

	if(m_model)
	{
		m_model->Shutdown();
		delete m_model;
	}
	m_model = 0;
}

void RagdollClass::Update()
{
	//for(int bone = 0; bone < num_bones; ++bone)
	//{
	//	//if(bone == 123456)
	//	//{
	//		// calculate tranformation
	//		btVector3 move;
	//		btVector3 prev_rot;
	//		btVector3 rot;
	//		btMatrix3x3 prev_rotMat;
	//		btMatrix3x3 rotMat;

	//		btTransform actual;
	//		m_rigidBodys[bone]->getMotionState()->getWorldTransform(actual);

	//		move.setX(actual.getOrigin().x() - m_prevTransforms[bone].getOrigin().x());
	//		move.setY(actual.getOrigin().y() - m_prevTransforms[bone].getOrigin().y());
	//		move.setZ(actual.getOrigin().z() - m_prevTransforms[bone].getOrigin().z());
	//		rotMat = actual.getBasis();
	//		prev_rotMat = m_prevTransforms[bone].getBasis();

	//		float r11 = prev_rotMat.getColumn(0).x();
	//		float r21 = prev_rotMat.getColumn(0).y();
	//		float r31 = prev_rotMat.getColumn(0).z();
	//		float r32 = prev_rotMat.getColumn(1).z();
	//		float r33 = prev_rotMat.getColumn(2).z();
	//		prev_rot.setX(atan2f(r32, r33));
	//		prev_rot.setY(atan2f(-r31, sqrtf(powf(r32, 2.0f) + powf(r33, 2.0f))));
	//		prev_rot.setZ(atan2f(r21, r11));

	//		r11 = rotMat.getColumn(0).x();
	//		r21 = rotMat.getColumn(0).y();
	//		r31 = rotMat.getColumn(0).z();
	//		r32 = rotMat.getColumn(1).z();
	//		r33 = rotMat.getColumn(2).z();

	//		rot.setX(atan2f(r32, r33) - prev_rot.x());
	//		rot.setY(atan2f(-r31, sqrtf(powf(r32, 2.0f) + powf(r33, 2.0f))) - prev_rot.y());
	//		rot.setZ(atan2f(r21, r11) - prev_rot.z());

	//		aiMatrix4x4 rotation, Xrotation, Yrotation, Zrotation;
	//		aiMatrix4x4 translation;

	//		translation = aiMatrix4x4::Translation(aiVector3D(move.x(), move.y(), move.z()), translation);
	//		Xrotation = Xrotation.FromEulerAnglesXYZ(rot.x(), 0.0f, 0.0f);
	//		Yrotation = Yrotation.FromEulerAnglesXYZ(0.0f, rot.y(), 0.0f);
	//		Zrotation = Zrotation.FromEulerAnglesXYZ(0.0f, 0.0f, rot.z());
	//		rotation = Zrotation * Xrotation * Yrotation;

	////Check!
	//		m_transformations[bone] = /*rotation * */translation;
	//		m_prevTransforms[bone] = actual;
	//	//}
	//	//else
	//	//{
	//	//	m_transformations[bone] = aiMatrix4x4();
	//	//	btTransform actual;
	//	//	m_rigidBodys[bone]->getMotionState()->getWorldTransform(actual);
	//	//	m_prevTransforms[bone] = actual;
	//	//}
	//}

	//for(int ver = 0; ver < m_model->m_model->mMeshes[0]->mNumVertices; ++ver)
	//{
	//	aiMatrix4x4 transform, finalTransform;
	//	aiVector3D pos = m_model->m_model->mMeshes[0]->mVertices[ver];
	//	float w = 0.0f;
	//	float we = 0.0f;
	//	finalTransform = aiMatrix4x4();
	//	for(int bone = 0; bone < m_vertexInfos[ver].m_boneWeights.size(); ++bone)
	//	{
	//		btTransform actual;
	//		m_rigidBodys[bone]->getMotionState()->getWorldTransform(actual);

	//		aiVector3D n_pos(actual.getOrigin.x(), actual.getOrigin.y(), actual.getOrigin.z());
	//		btMatrix3x3  actual.getBasis()
	//		aiQuaternion n_rot(actual.getRotation().w(), actual.getRotation().x(), actual.getRotation().y(), actual.getRotation().z());

	//		we = m_vertexInfos[ver].m_boneWeights[bone]->weight;
	//		w += we;
	//		if(w > 1.0f)
	//		{
	//			we -= w - 1.0f;
	//			w = 1.0f;
	//		}
	//		//transform = m_transformations[m_vertexInfos[ver].m_boneWeights[bone]->boneID];
	//		//transform.a1 *= we;
	//		//transform.a2 *= we;
	//		//transform.a3 *= we;
	//		//transform.a4 *= we;
	//		//transform.b1 *= we;
	//		//transform.b2 *= we;
	//		//transform.b3 *= we;
	//		//transform.b4 *= we;
	//		//transform.c1 *= we;
	//		//transform.c2 *= we;
	//		//transform.c3 *= we;
	//		//transform.c4 *= we;
	//		//transform.d1 *= we;
	//		//transform.d2 *= we;
	//		//transform.d3 *= we;
	//		//transform.d4 *= we;

	//		//finalTransform = transform * finalTransform;
	//		aiMatrix4x4 n_posMat;
	//		aiMatrix4x4::Translation(n_pos, n_posMat);
	//		aiMatrix4x4 n_rotMat;
	//		pos = aiMatrix4x4::Translation(n_pos, 
	//		//pos = transform * pos;
	//		//m_model->m_model->mMeshes[0]->mVertices[ver] = transform * m_model->m_model->mMeshes[0]->mVertices[ver];
	//		//m_model->m_model->mMeshes[0]->mVertices[ver] += aiVector3D(0.0f, 0.1f, 0.0f);
	//	}

	//	//m_model->m_model->mMeshes[0]->mVertices[ver] = finalTransform * m_model->m_model->mMeshes[0]->mVertices[ver];
	//	m_model->m_model->mMeshes[0]->mVertices[ver] = pos;
	//}

	////btTransform trans;
	////m_rigidBodys[bones::Spine0]->getMotionState()->getWorldTransform(trans);
	////btVector3 pos = trans.getOrigin();
	////btQuaternion rot = trans.getRotation();
	////m_model->SetPosition(D3DXVECTOR3(pos.x(), pos.y(), pos.z()));
	////m_model->SetRotation(D3DXQUATERNION(rot.x(), rot.y(), rot.z(), rot.w()));
}

bool RagdollClass::Initialize(int bone, btScalar size_x, btScalar size_y, btScalar size_z, aiVector3D position, btScalar offset_x, btScalar offset_y, btScalar offset_z, aiVector3D rotation, btScalar mass, btScalar inertia_x, btScalar inertia_y, btScalar inertia_z, ID3D11Device* device)
{
	aiMatrix4x4 rotationMatrix, XrotationMatrix, YrotationMatrix, ZrotationMatrix;
	aiMatrix4x4 translationMatrix, offsetMatrix;

	translationMatrix = aiMatrix4x4::Translation(position, translationMatrix);
	offsetMatrix = aiMatrix4x4::Translation(aiVector3D(offset_x, offset_y, offset_z), offsetMatrix);

	XrotationMatrix = XrotationMatrix.FromEulerAnglesXYZ(rotation.x, 0.0f, 0.0f);
	YrotationMatrix = YrotationMatrix.FromEulerAnglesXYZ(0.0f, rotation.y, 0.0f);
	ZrotationMatrix = ZrotationMatrix.FromEulerAnglesXYZ(0.0f, 0.0f, rotation.z);
	aiMatrix4x4 boneMatrix = m_bones[bone]->mOffsetMatrix;

	rotationMatrix = ZrotationMatrix * XrotationMatrix * YrotationMatrix;

	aiMatrix4x4 boneWorldMatrix =  translationMatrix * rotationMatrix.Inverse() * boneMatrix.Inverse() * offsetMatrix;

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

	m_models[bone] = new ModelClass;
	m_models[bone]->Initialize(device,  "../PwAG/data/cube.DAE", L"../PwAG/data/stone02.dds", 
										L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
										bonePosition, boneRotation);
	m_models[bone]->SetScale(size_x, size_y, size_z);

	return true;
}
