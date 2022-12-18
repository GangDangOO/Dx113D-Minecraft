#pragma once
class Scene_Main : public Scene
{
private:
	Player*			player;
	CreateWorld*	world;

	Chunk*	chunk[Chunk_X][Chunk_Z];
	Vector3 pos[Chunk_X][Chunk_Z];
	Int2	curLocation;
	vector<Chunk*> arr;
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

