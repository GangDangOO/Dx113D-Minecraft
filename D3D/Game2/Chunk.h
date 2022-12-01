#pragma once
#define SIZE_XZ 16
#define SIZE_Y 64

class Chunk
{
private:
	Block*		block[SIZE_XZ][SIZE_Y][SIZE_XZ];
	vector<Block> arr;
public:
	Vector3		pos;

	Chunk();
	~Chunk();
	void SetWorldPos(Vector3 pos);
	void RenderHierarchy();
	void SetRender();
	void SetMesh();
	int	 SetChunk();
	void Update();
	void Render();
};

