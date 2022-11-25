#pragma once
#define SIZE_XZ 16
#define SIZE_Y 1

class Chunk
{
private:

public:
	Vector3		pos;
	Block*		block[SIZE_XZ][SIZE_Y][SIZE_XZ];
	Chunk();
	~Chunk();
	void SetWorldPos(Vector3 pos);
	void RenderHierarchy();
	void Update();
	void Render();
};

