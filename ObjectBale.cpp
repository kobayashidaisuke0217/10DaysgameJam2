#include "ObjectBale.h"

void ObjectBale::Initialize()
{
	
	textureManager_=Texturemanager::GetInstance();
	texturehandle_ = textureManager_->Load("Resource/Black.png");
	sphere_ = new Sphere();
	sphere_->Initialize();
	SetGround(ground_);
	SetParent(&ground_->GetWorldTransform());
	worldtransform_.scale_ = { 0.1f,0.1f,0.1f };
	worldtransform_.translation_ = { 0.5f,0.5f,0.50f };
	worldtransform_.Initialize();
}

void ObjectBale::Update()
{
	worldtransform_.UpdateMatrix();
}

void ObjectBale::Draw(const ViewProjection& viewprojection, const DirectionalLight& light)
{
	sphere_->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldtransform_, texturehandle_, viewprojection, light);
}

void ObjectBale::Finalize()
{
	delete sphere_;
	worldtransform_.constBuff_.ReleaseAndGetAddressOf();
}

void ObjectBale::SetParent(const WorldTransform* parent)
{
	worldtransform_.parent_ = parent;
	
}