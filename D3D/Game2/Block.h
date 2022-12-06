#pragma once

enum class _BlockType
{
	AIR,
	GRASS,
	DIRT,
	STONE
};
enum class _Dir {
	Top = 0,
	Under,
	Left,
	Right,
	Front,
	Back
};
class Block
{
private:

public:
	_BlockType	type;
	bool		isCheck[6];
	Vector3		pos;

	Block(_BlockType _type);
	~Block();
};

