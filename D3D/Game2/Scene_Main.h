#pragma once
#define SIZE_X 1
#define SIZE_Z 1

class Scene_Main : public Scene
{
private:
	Camera* cam;

	Chunk* chunk[SIZE_X][SIZE_Z];
public:
	Scene_Main();
	~Scene_Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

