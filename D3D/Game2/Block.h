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
	_BlockType type;
	Block(_BlockType _type);
	~Block();
	void	RenderHierarchy();
	void	Release();
	void	Update();
	void	Render();
};

