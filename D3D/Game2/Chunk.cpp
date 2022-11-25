#include "stdafx.h"

Chunk::Chunk()
{
	for (int x = 0; x < SIZE_XZ; x++)
	{
		for (int y = 0; y < SIZE_Y; y++)
		{
			for (int z = 0; z < SIZE_XZ; z++)
			{
				switch (y)
				{
				case 0:
					block[x][y][z] = new Block(_BlockType::GRASS);
					break;
				default:
					block[x][y][z] = new Block(_BlockType::DIRT);
					break;
				}
				block[x][y][z]->voxel->SetWorldPos(Vector3(x * 2, y * -2, z * 2));
			}
		}
	}
	for (int x = 0; x < SIZE_XZ; x++)
	{
		for (int y = 0; y < SIZE_Y; y++)
		{
			for (int z = 0; z < SIZE_XZ; z++)
			{
				// 왼쪽 오른쪽 블럭있으면 렌더비활성
				if (x - 1 >= 0 && block[x - 1][y][z]->isExists)
					block[x][y][z]->voxel->Find("Left")->visible = false;
				if (x + 1 < SIZE_XZ && block[x + 1][y][z]->isExists)
					block[x][y][z]->voxel->Find("Light")->visible = false;

				// 앞 뒤 블럭있으면 렌더비활성
				if (z - 1 >= 0 && block[x][y][z - 1]->isExists)
					block[x][y][z]->voxel->Find("Back")->visible = false;
				if (z + 1 < SIZE_XZ && block[x][y][z + 1]->isExists)
					block[x][y][z]->voxel->Find("Front")->visible = false;

				// 위 아래 블럭있으면 렌더비활성
				if (y - 1 >= 0 && block[x][y - 1][z]->isExists)
					block[x][y][z]->voxel->Find("Up")->visible = false;
				if (y + 1 < SIZE_Y && block[x][y + 1][z]->isExists)
					block[x][y][z]->voxel->Find("Down")->visible = false;
			}
		}
	}
	pos = block[SIZE_XZ / 2][0][SIZE_XZ / 2]->voxel->GetWorldPos();
}

Chunk::~Chunk()
{

}

void Chunk::SetWorldPos(Vector3 pos)
{
	Vector3 move = Vector3(pos.x * 2 * SIZE_XZ, 0, pos.z * 2 * SIZE_XZ);
	for (int x = 0; x < SIZE_XZ; x++)
	{
		for (int y = 0; y < SIZE_Y; y++)
		{
			for (int z = 0; z < SIZE_XZ; z++)
			{
				block[x][y][z]->voxel->MoveWorldPos(move);
			}
		}
	}
}

void Chunk::RenderHierarchy()
{
	for (int x = 0; x < SIZE_XZ; x++)
	{
		for (int y = 0; y < SIZE_Y; y++)
		{
			for (int z = 0; z < SIZE_XZ; z++)
			{
				block[x][y][z]->RenderHierarchy();
			}
		}
	}
}

void Chunk::Update()
{
	for (int x = 0; x < SIZE_XZ; x++)
	{
		for (int y = 0; y < SIZE_Y; y++)
		{
			for (int z = 0; z < SIZE_XZ; z++)
			{
				block[x][y][z]->Update();
			}
		}
	}
}

void Chunk::Render()
{
	for (int x = 0; x < SIZE_XZ; x++)
	{
		for (int y = 0; y < SIZE_Y; y++)
		{
			for (int z = 0; z < SIZE_XZ; z++)
			{
				block[x][y][z]->Render();
			}
		}
	}
}
