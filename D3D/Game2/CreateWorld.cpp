#include "stdafx.h"

using namespace OpenSimplexNoise;

CreateWorld::CreateWorld()
{
	unsigned int seed = 2100;
	Noise n = Noise(seed);
	float frequency = 2.0f;
	long sizeX = Size_X * Chunk_X;
	long sizeZ = Size_Z * Chunk_Z;
	for (int x = 0; x < sizeX; x++)
	{
		double nx = (x * sizeX * 0.1) / sizeX * 0.1;
		for (int y = 0; y < sizeZ; y++)
		{
			double ny = (y * sizeZ * 0.1) / sizeZ * 0.1 + 1.0;
			double e = 1 * n.eval(1 * frequency * nx, 1 * frequency * ny)
				+ 0.5 * n.eval(2 * frequency * nx, 2 * frequency * ny)
				+ 0.25 * n.eval(4 * frequency * nx, 4 * frequency * ny);
			double h = e / (1 + 0.5 + 0.25);
			h = round(h * 7) / 7 + 1;
			h /= 0.2;
			// cout << h << endl;
			height[x][y] = (int)h;
		}
	}
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
