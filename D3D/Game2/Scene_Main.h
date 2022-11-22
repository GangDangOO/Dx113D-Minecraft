#pragma once

class Scene_Main : public Scene
{
private:
	Camera* cam;

	Block* test;
public:
	Scene_Main();
	~Scene_Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

