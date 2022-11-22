#pragma once
class Block : public Scene
{
private:
	GameObject* voxel;
	bool check[6];

public:
	struct _BlockType
	{

	};
	Block(int type);
	~Block();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

