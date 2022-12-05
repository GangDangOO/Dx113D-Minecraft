#pragma once
#define Size_X 16
#define Size_Y 16
#define Size_Z 16
class Chunk
{
private:
	Block*	block[Size_X][Size_Y][Size_Z];
	Actor*	voxel[6][Size_X][Size_Y][Size_Z];
	vector<Actor*> arr;
public:
	Vector3	position;
	Chunk(int posX, int posZ);
	~Chunk();
	void	RenderHierarchy();
	void	SetRendering();
	void	SetGreedyMeshing();
	int		SetArray();
	void	Update();
	void	Render();
};

