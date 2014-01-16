#include "EngineObjectClass.h"


EngineObjectClass::EngineObjectClass(void)
{
	m_model = 0;
	m_rigidBody = 0;
	m_collisionShape = 0;
}


EngineObjectClass::~EngineObjectClass(void)
{
}

// for Ragdoll
bool EngineObjectClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename1, WCHAR* textureFilename2, 
								   WCHAR* textureFilename3, aiVector3D modelPosition, aiVector3D modelRotation, std::string name, 
								   int shaderType)
{
	m_model = new ModelClass;
	m_model->Initialize(device, modelFilename, textureFilename1, textureFilename2, textureFilename3, modelPosition, modelRotation);

	m_shaderType = shaderType;

	return true;
}

// for StaticPlane
bool EngineObjectClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename1, WCHAR* textureFilename2, 
								   WCHAR* textureFilename3, aiVector3D modelPosition, aiVector3D modelRotation, std::string name, 
								   btScalar normalx, btScalar normaly, btScalar normalz, btScalar planeConstant, int shaderType)
{
	m_model = new ModelClass;
	m_model->Initialize(device, modelFilename, textureFilename1, textureFilename2, textureFilename3, modelPosition, modelRotation);

	if(name == "StaticPlane")
		m_collisionShape = new btStaticPlaneShape(btVector3(normalx, normaly, normalz), planeConstant);
	else
		return false;

	if(!m_collisionShape)
		return false;

	return Initialize(modelPosition, modelRotation, 0, 0, 0, 0, shaderType);
}

// for Sphere
bool EngineObjectClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename1, WCHAR* textureFilename2, 
								   WCHAR* textureFilename3, aiVector3D modelPosition, aiVector3D modelRotation, std::string name, btScalar radius, 
								   btScalar mass, btScalar inertiax, btScalar inertiay, btScalar inertiaz, int shaderType)
{
	m_model = new ModelClass;
	m_model->Initialize(device, modelFilename, textureFilename1, textureFilename2, textureFilename3, modelPosition, modelRotation);

	if(name == "Sphere")
		m_collisionShape = new btSphereShape(radius);
	else
		return false;

	if(!m_collisionShape)
		return false;

	return Initialize(modelPosition, modelRotation, mass, inertiax, inertiay, inertiaz, shaderType);
}

// for Capsule (Capsule/CapsuleX/CapsuleZ) and Cone (Cone/ConeX/ConeZ)
bool EngineObjectClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename1, WCHAR* textureFilename2, 
								   WCHAR* textureFilename3, aiVector3D modelPosition, aiVector3D modelRotation, std::string name, btScalar radius, btScalar height, 
								   btScalar mass, btScalar inertiax, btScalar inertiay, btScalar inertiaz, int shaderType)
{
	m_model = new ModelClass;
	m_model->Initialize(device, modelFilename, textureFilename1, textureFilename2, textureFilename3, modelPosition, modelRotation);

	if(name == "Capsule")
		m_collisionShape = new btCapsuleShape(radius, height);
	else if(name == "CapsuleX")
		m_collisionShape = new btCapsuleShapeX(radius, height);
	else if(name == "CapsuleZ")
		m_collisionShape = new btCapsuleShapeZ(radius, height);
	else if(name == "Cone")
		m_collisionShape = new btConeShape(radius, height);
	else if(name == "ConeX")
		m_collisionShape = new btConeShapeX(radius, height);
	else if(name == "ConeZ")
		m_collisionShape = new btConeShapeZ(radius, height);
	else
		return false;

	if(!m_collisionShape)
		return false;

	return Initialize(modelPosition, modelRotation, mass, inertiax, inertiay, inertiaz, shaderType);
}

// for Box and Cylinder (Cylinder/CylinderX/CylinderZ)
bool EngineObjectClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename1, WCHAR* textureFilename2, 
								   WCHAR* textureFilename3, aiVector3D modelPosition, aiVector3D modelRotation, std::string name, btScalar x, btScalar y, btScalar z, 
								   btScalar mass, btScalar inertiax, btScalar inertiay, btScalar inertiaz, int shaderType)
{
	m_model = new ModelClass;
	m_model->Initialize(device, modelFilename, textureFilename1, textureFilename2, textureFilename3, modelPosition, modelRotation);

	if(name == "Box")
		m_collisionShape = new btBoxShape(btVector3(x, y, z));
	else if(name == "Cylinder")
		m_collisionShape = new btCylinderShape(btVector3(x, y, z));
	else if(name == "CylinderX")
		m_collisionShape = new btCylinderShapeX(btVector3(x, y, z));
	else if(name == "CylinderZ")
		m_collisionShape = new btCylinderShapeZ(btVector3(x, y, z));
	else
		return false;

	if(!m_collisionShape)
		return false;

	return Initialize(modelPosition, modelRotation, mass, inertiax, inertiay, inertiaz, shaderType);
}

bool EngineObjectClass::Initialize(aiVector3D modelPosition, aiVector3D modelRotation, btScalar mass, btScalar inertiax, btScalar inertiay, btScalar inertiaz, int shaderType)
{
	btDefaultMotionState* m_motionState = new btDefaultMotionState(btTransform(btQuaternion(modelRotation.y, modelRotation.x, modelRotation.z), btVector3(modelPosition.x, modelPosition.y, modelPosition.z)));
	if(!m_motionState)
		return false;
	btScalar m_mass = mass;
	btVector3 m_inertia(inertiax, inertiay, inertiaz);
	if(m_mass)		
		m_collisionShape->calculateLocalInertia(m_mass, m_inertia);

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(m_mass, m_motionState, m_collisionShape, m_inertia);
	m_rigidBody = new btRigidBody(rigidBodyCI);
	if(!m_rigidBody)
		return false;

	m_shaderType = shaderType;

	return true;
}

void EngineObjectClass::Shutdown(void)
{
	if(m_model)
	{
		m_model->Shutdown();
		delete m_model;
	}
	m_model = 0;

	if(m_rigidBody)
		delete m_rigidBody;
	m_rigidBody = 0;

	if(m_collisionShape)
		delete m_collisionShape;
	m_collisionShape = 0;
}

void EngineObjectClass::Update(void)
{
	btTransform transform;
	m_rigidBody->getMotionState()->getWorldTransform(transform);

	D3DXVECTOR3 pos( transform.getOrigin().getX(), transform.getOrigin().getY(), transform.getOrigin().getZ() );
	D3DXQUATERNION quat( transform.getRotation().x(), transform.getRotation().y(), transform.getRotation().z(), transform.getRotation().w() );
	m_model->SetPosition(pos);
	m_model->SetRotation(quat);
	//m_model->Move(aiVector3D(pos.x, pos.y, pos.z));
}
