#pragma once

class Chunk
{
private:
	Block*	block[Size_X][Size_Y][Size_Z];
	Actor*	voxel[6][Size_X][Size_Y][Size_Z];
	vector<Actor*> arr;
public:
	Vector3	position;

	Chunk(int posX, int posZ, int height[Size_X * Size_Z]);
	~Chunk();
	
	void	RenderHierarchy();
	void	SetRendering();
	void	SetGreedyMeshing();
	int		SetArray();
	int		GetChunkSize();
	void	Update();
	void	Render();
};

