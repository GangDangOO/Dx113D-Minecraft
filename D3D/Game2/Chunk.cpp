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
				block[x][y][z]->voxel->SetWorldPos(Vector3(x, -y, z));
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
	Vector3 move = Vector3(pos.x * SIZE_XZ, 0, pos.z * SIZE_XZ);
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
				if (x - 1 >= 0 && block[x - 1][y][z]->voxel->visible)
					block[x][y][z]->voxel->Find("Back")->visible = false;
				if (x + 1 < SIZE_XZ && block[x + 1][y][z]->voxel->visible)
					block[x][y][z]->voxel->Find("Front")->visible = false;

				if (z - 1 >= 0 && block[x][y][z - 1]->voxel->visible)
					block[x][y][z]->voxel->Find("Left")->visible = false;
				if (z + 1 < SIZE_XZ && block[x][y][z + 1]->voxel->visible)
					block[x][y][z]->voxel->Find("Right")->visible = false;

				if (y - 1 >= 0 && block[x][y - 1][z]->voxel->visible)
					block[x][y][z]->voxel->Find("Top")->visible = false;
				if (y + 1 < SIZE_Y && block[x][y + 1][z]->voxel->visible)
					block[x][y][z]->voxel->Find("Under")->visible = false;
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
						name = "Right";
						break;
					case 2:
						name = "Front";
						break;
					case 3:
						name = "Back";
						break;
					case 4:
						name = "Top";
						break;
					case 5:
						name = "Under";
						break;
					default:
						return;
						break;
					}
					// 위 아래 그리딩 메쉬a
					if (block[x][y][z]->voxel->Find(name)->visible)
					{
						if (i >= 4)
						{
							for (int w = z + 1; w < SIZE_XZ; w++)
							{
								if (block[x][y][z]->type == block[x][y][w]->type)
								{
									if (block[x][y][w]->voxel->Find(name)->visible)
										block[x][y][w]->voxel->Find(name)->visible = false;
									if (w == SIZE_XZ - 1)
									{
										if (w - z != 1)
										{
											VertexPT* pt = (VertexPT*)block[x][y][z]->voxel->Find(name)->mesh->vertices;
											pt[1].position.z = (w - z) + 0.5f;
											pt[1].uv.y = (w - z);
											pt[2].position.z = (w - z) + 0.5f;
											pt[2].uv.y = (w - z);
											block[x][y][z]->voxel->Find(name)->mesh->UpdateMesh();
										}
									}
								}
								else
								{
									if (w - z != 1)
									{
										VertexPT* pt = (VertexPT*)block[x][y][z]->voxel->Find(name)->mesh->vertices;
										pt[1].position.z = (w - z) + 0.5f;
										pt[1].uv.y = (w - z);
										pt[2].position.z = (w - z) + 0.5f;
										pt[2].uv.y = (w - z);
										block[x][y][z]->voxel->Find(name)->mesh->UpdateMesh();
									}
									break;
								}
							}
						}
						// 옆쪽 그리딩 메쉬
						else
						{
							for (int w = y + 1; w < SIZE_Y; w++)
							{
								if (block[x][y][z]->type == block[x][w][z]->type)
								{
									if (block[x][w][z]->voxel->Find(name)->visible)
										block[x][w][z]->voxel->Find(name)->visible = false;
									if (w == SIZE_Y - 1)
									{
										if (w - y != 1)
										{
											VertexPT* pt = (VertexPT*)block[x][y][z]->voxel->Find(name)->mesh->vertices;
											pt[1].position.z = (w - y) + 0.5f;
											pt[1].uv.y = (w - y);
											pt[2].position.z = (w - y) + 0.5f;
											pt[2].uv.y = (w - y);
											block[x][y][z]->voxel->Find(name)->mesh->UpdateMesh();
										}
									}
								}
								else
								{
									if (w - y != 1)
									{
										w--;
										VertexPT* pt = (VertexPT*)block[x][y][z]->voxel->Find(name)->mesh->vertices;
										pt[1].position.z = (w - y) + 0.5f;
										pt[1].uv.y = (w - y);
										pt[2].position.z = (w - y) + 0.5f;
										pt[2].uv.y = (w - y);
										block[x][y][z]->voxel->Find(name)->mesh->UpdateMesh();
									}
									break;
								}
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
					!block[x][y][z]->voxel->Find("Right")->visible &&
					!block[x][y][z]->voxel->Find("Back")->visible &&
					!block[x][y][z]->voxel->Find("Front")->visible &&
					!block[x][y][z]->voxel->Find("Top")->visible &&
					!block[x][y][z]->voxel->Find("Under")->visible)
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
