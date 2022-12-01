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
				case 1:
				case 2:
				case 3:
				case 4:
					block[x][y][z] = new Block(_BlockType::DIRT);
					break;
				default:
					block[x][y][z] = new Block(_BlockType::STONE);
					break;
				}
				block[x][y][z]->voxel->SetWorldPos(Vector3(x * 2, y * -2, z * 2));
				arr.push_back(*block[x][y][z]);
			}
		}
	}
	Update();
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
	Update();
}

void Chunk::RenderHierarchy()
{
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i].RenderHierarchy();
	}
}

void Chunk::SetRender()
{
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
	Update();
}

void Chunk::SetMesh()
{
	for (int x = 0; x < SIZE_XZ; x++)
	{
		for (int z = 0; z < SIZE_XZ; z++)
		{
			for (int y = 0; y < SIZE_Y; y++)
			{
				for (int i = 0; i < 6; i++)
				{
					string name;
					switch (i)
					{
					case 0:
						name = "Left";
						break;
					case 1:
						name = "Light";
						break;
					case 2:
						name = "Front";
						break;
					case 3:
						name = "Back";
						break;
					case 4:
						name = "Up";
						break;
					case 5:
						name = "Down";
						break;
					default:
						return;
						break;
					}
					// 위 아래 그리딩 메쉬
					if (i >= 4)
					{
						for (int w = z + 1; w < SIZE_XZ; w++)
						{
							if (block[x][y][z]->voxel->Find(name)->visible && block[x][y][z]->type == block[x][y][w]->type)
							{
								block[x][y][w]->voxel->Find(name)->visible = false;
								if (w == 15)
								{
									block[x][y][z]->voxel->Find(name)->scale.z = (w - z) + 1;
									block[x][y][z]->voxel->Find(name)->MoveWorldPos(Vector3(0, 0, (w - z)));
								}
							}
							else
							{
								block[x][y][z]->voxel->Find(name)->scale.z = (w - z) + 1;
								block[x][y][z]->voxel->Find(name)->MoveWorldPos(Vector3(0, 0, (w - z)));
								break;
							}
						}
					}
					// 옆쪽 그리딩 메쉬
					else if (block[x][y][z]->voxel->Find(name)->visible)
					{
						for (int w = y + 1; w < SIZE_Y; w++)
						{
							if (block[x][y][z]->voxel->Find(name)->visible && block[x][y][z]->type == block[x][w][z]->type)
							{
								block[x][w][z]->voxel->Find(name)->visible = false;
								if (w == 15)
								{
									block[x][y][z]->voxel->Find(name)->scale.z = (w - y);
									block[x][y][z]->voxel->Find(name)->MoveWorldPos(Vector3(0, -(w - y) + 1, 0));
								}
							}
							else
							{
								block[x][y][z]->voxel->Find(name)->scale.z = (w - y);
								block[x][y][z]->voxel->Find(name)->MoveWorldPos(Vector3(0, -(w - y) + 1, 0));
								break;
							}
						}
					}
				}
			}
		}
	}
	Update();
}

int Chunk::SetChunk()
{
	arr.clear();
	for (int x = 0; x < SIZE_XZ; x++)
	{
		for (int y = 0; y < SIZE_Y; y++)
		{
			for (int z = 0; z < SIZE_XZ; z++)
			{
				if (!block[x][y][z]->voxel->Find("Left")->visible &&
					!block[x][y][z]->voxel->Find("Light")->visible &&
					!block[x][y][z]->voxel->Find("Back")->visible &&
					!block[x][y][z]->voxel->Find("Front")->visible &&
					!block[x][y][z]->voxel->Find("Up")->visible &&
					!block[x][y][z]->voxel->Find("Down")->visible)
				{
					block[x][y][z]->voxel->visible = false;
				}
				else
				{
					arr.push_back(*block[x][y][z]);
				}
			}
		}
	}
	Update();
	return arr.size();
}

void Chunk::Update()
{
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i].Update();
	}
	pos = block[SIZE_XZ / 2][0][SIZE_XZ / 2]->voxel->GetWorldPos();
}

void Chunk::Render()
{
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i].Render();
	}
}
