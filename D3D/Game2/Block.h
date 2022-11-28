#pragma once

enum class _BlockType
{
	GRASS,
	DIRT,
	STONE
};

class Block
{
private:

public:
	Actor*	voxel;
	bool	isExists;
	Block(_BlockType type);
	~Block();
	void	RenderHierarchy();
	void	Release();
	void	Update();
	void	Render();
};

