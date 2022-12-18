#pragma once

class CreateWorld
{
private:
	int		height[Size_X * Chunk_X][Size_Z * Chunk_Z];
	int		chunk[Size_X * Size_Z];
	vector<Int2> bufChunk;
public:
	CreateWorld();
	int*	GetType(int ChunkX, int ChunkZ);
};