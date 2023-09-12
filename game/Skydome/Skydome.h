#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

#include <memory>

class Skydome {
public:
	void Initialize();

	void Update();

	void Draw(const ViewProjection& viewProjection, const DirectionalLight& directionalLight);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};