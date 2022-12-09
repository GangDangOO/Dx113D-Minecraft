#include "stdafx.h"

using namespace OpenSimplexNoise;

CreateWorld::CreateWorld()
{
	unsigned int seed = 2100;
	Noise n = Noise(seed);
	for (int x = 0; x < Size_X * Chunk_X; x++)
	{
		for (int y = 0; y < Size_Z * Chunk_Z; y++)
		{
			double h = n.eval(x, y);
			// cout<< h << endl;
			if (h > 0.5f)
				height[x][y] = 3;
			else if(h > 0.0f)
				height[x][y] = 2;
			else if (h > -0.5f)
				height[x][y] = 1;
			else
				height[x][y] = 0;
		}
	}
	// CallAutomata(3);
}

int* CreateWorld::GetType(int ChunkX, int ChunkZ)
{
	for (int x = 0; x < Size_X; x++)
	{
		for (int z = 0; z < Size_Z; z++)
		{
			chunk[x * Size_X + z] = height[ChunkX * Size_X + x][ChunkZ * Size_Z + z];
		}
	}
	return chunk;
}

void CreateWorld::CallAutomata(int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int x = 1; x < Size_X * Chunk_X - 1; x++)
		{
			for (int y = 1; y < Size_Z * Chunk_Z - 1; y++)
			{
				if (RANDOM->Int(0, 3) == 0) height[x - 1][y]++;
				if (RANDOM->Int(0, 3) == 0) height[x + 1][y]++;
				if (RANDOM->Int(0, 3) == 0) height[x][y - 1]++;
				if (RANDOM->Int(0, 3) == 0) height[x][y + 1]++;
				if (RANDOM->Int(0, 5) == 0) height[x][y]++;
			}
		}
	}
}
