#pragma once
class Player
{
private:
	Camera* cam;

	bool	isCamRot;
	vector<Actor*> arr;
	float	gravity;
	bool	isJump;
	Vector3 move;
public:
	Player();
	~Player();
	void SetLiveChunk(vector<Actor*> arr);
	void SetWorldPos(Vector3 pos);
	void RenderHierarchy();
	void Move();
	void Update();
	void LateUpdate();
	void Render();
};