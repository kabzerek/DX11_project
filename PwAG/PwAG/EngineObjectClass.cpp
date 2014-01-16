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

// for StaticPlane
bool EngineObjectClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename1, WCHAR* textureFilename2, 
								   WCHAR* textureFilename3, aiVector3D modelPosition, aiVector3D modelRotation, std::string name, 
								   btScalar normalx, btScalar normaly, btScalar normalz, btScalar planeConstant)
{
	m_model = new ModelClass;
	m_model->Initialize(device, modelFilename, textureFilename1, textureFilename2, textureFilename3, modelPosition, modelRotation);

	if(name == "StaticPlane")
		m_collisionShape = new btStaticPlaneShape(btVector3(normalx, normaly, normalz), planeConstant);
	else
		return false;

	if(!m_collisionShape)
		return false;

	return Initialize(modelPosition, modelRotation, 0, 0, 0, 0);
}

// for Sphere
bool EngineObjectClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename1, WCHAR* textureFilename2, 
								   WCHAR* textureFilename3, aiVector3D modelPosition, aiVector3D modelRotation, std::string name, btScalar radius, 
								   btScalar mass, btScalar inertiax, btScalar inertiay, btScalar inertiaz)
{
	m_model = new ModelClass;
	m_model->Initialize(device, modelFilename, textureFilename1, textureFilename2, textureFilename3, modelPosition, modelRotation);

	if(name == "Sphere")
		m_collisionShape = new btSphereShape(radius);
	else
		return false;

	if(!m_collisionShape)
		return false;

	return Initialize(modelPosition, modelRotation, mass, inertiax, inertiay, inertiaz);
}

// for Capsule (Capsule/CapsuleX/CapsuleZ) and Cone (Cone/ConeX/ConeZ)
bool EngineObjectClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename1, WCHAR* textureFilename2, 
								   WCHAR* textureFilename3, aiVector3D modelPosition, aiVector3D modelRotation, std::string name, btScalar radius, btScalar height, 
								   btScalar mass, btScalar inertiax, btScalar inertiay, btScalar inertiaz)
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

	return Initialize(modelPosition, modelRotation, mass, inertiax, inertiay, inertiaz);
}

// for Box and Cylinder (Cylinder/CylinderX/CylinderZ)
bool EngineObjectClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename1, WCHAR* textureFilename2, 
								   WCHAR* textureFilename3, aiVector3D modelPosition, aiVector3D modelRotation, std::string name, btScalar x, btScalar y, btScalar z, 
								   btScalar mass, btScalar inertiax, btScalar inertiay, btScalar inertiaz)
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

	return Initialize(modelPosition, modelRotation, mass, inertiax, inertiay, inertiaz);
}

bool EngineObjectClass::Initialize(aiVector3D modelPosition, aiVector3D modelRotation, btScalar mass, btScalar inertiax, btScalar inertiay, btScalar inertiaz)
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


	float x = transform.getOrigin().getX();
	float y = transform.getOrigin().getY();
	float z = transform.getOrigin().getZ();
	D3DXVECTOR3 pos(x,y,z);
	//float rx = NULL;
	//float ry = NULL;
	//float rz = NULL;

	//D3DXMATRIX matRotate, matTranslate;
	//D3DXVECTOR4 posEnd(pos, 1.0f);
	//
	//D3DXQUATERNION q;
	//q.x = transform.getRotation().getX();
	//q.y = transform.getRotation().getY();
	//q.z = transform.getRotation().getZ();
	//q.w = transform.getRotation().getW();

	//D3DXQuaternionToAxisAngle(&q, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &rx);
	//D3DXQuaternionToAxisAngle(&q, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &ry);
	//D3DXQuaternionToAxisAngle(&q, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &rz);

	//D3DXMatrixRotationYawPitchRoll(&matRotate, ry, rx, rz);
	//D3DXMatrixTranslation(&matTranslate, x, y, z);
	//D3DXMatrixMultiply(&matTranslate, &matTranslate, &matRotate);
	////D3DXMatrixTransl
	//D3DXVec3Transform(&posEnd, &pos, &matTranslate);


	m_model->SetRotation( D3DXQUATERNION(transform.getRotation().getX(), transform.getRotation().getY(), transform.getRotation().getZ(), transform.getRotation().getW()) );

	m_model->Move(aiVector3D(pos.x, pos.y, pos.z));
}
