#include "stdafx.h"

Chunk::Chunk(int posX, int posZ)
{
	for (int x = 0; x < Size_X; x++)
	{
		for (int z = 0; z < Size_Z; z++)
		{
			for (int y = 0; y < Size_Y; y++)
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
				case 5:
					block[x][y][z] = new Block(_BlockType::DIRT);
					break;
				default:
					block[x][y][z] = new Block(_BlockType::STONE);
					break;
				}
				block[x][y][z]->pos = Vector3(posX * Size_X + x, -y, posZ * Size_Z + z);
			}
		}
	}
	position = Vector3(posX * Size_X + Size_X * 0.5f, 0.0f, posZ * Size_Z + Size_Z * 0.5f);
	SetRendering();
	SetGreedyMeshing();
	SetArray();
}

void Chunk::RenderHierarchy()
{
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i]->RenderHierarchy();
	}
}

void Chunk::Update()
{
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i]->Update();
	}
}

int Chunk::SetArray()
{
	arr.clear();
	for (int x = 0; x < Size_X; x++)
	{
		for (int z = 0; z < Size_Z; z++)
		{
			for (int y = 0; y < Size_Y; y++)
			{
				for (int n = 0; n < 6; n++)
				{
					if (block[x][y][z]->isCheck[n] == true) 
						arr.push_back(voxel[n][x][y][z]);
				}
			}
		}
	}
	return arr.size();
}

void Chunk::SetGreedyMeshing()
{
	for (int x = 0; x < Size_X; x++)
	{
		for (int y = 0; y < Size_Y; y++)
		{
			for (int z = 0; z < Size_Z; z++)
			{
				// 위쪽면 그리딩 메쉬
				for (int t = x + 1; t < Size_X; t++)
				{
					if (block[x][y][z]->type == block[t][y][z]->type)
					{
						if (block[t][y][z]->isCheck[(int)_Dir::Top])
						{
							block[t][y][z]->isCheck[(int)_Dir::Top] = false;
							voxel[(int)_Dir::Top][t][y][z]->visible = false;
						}
						if (t == Size_X - 1)
						{
							if (voxel[(int)_Dir::Top][x][y][z] != nullptr)
							{
								VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Top][x][y][z]->mesh->vertices;
								vertex[2].position.x = t - x + 0.5f;
								vertex[2].uv.x = t - x;
								vertex[3].position.x = t - x + 0.5f;
								vertex[3].uv.x = t - x;
								voxel[(int)_Dir::Top][x][y][z]->mesh->UpdateMesh();
							}
							break;
						}
					}
					else if (t - x != 1) {
						if (voxel[(int)_Dir::Top][x][y][z] != nullptr)
						{
							t--;
							VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Top][x][y][z]->mesh->vertices;
							vertex[2].position.x = t - x + 0.5f;
							vertex[2].uv.x = t - x;
							vertex[3].position.x = t - x + 0.5f;
							vertex[3].uv.x = t - x;
							voxel[(int)_Dir::Top][x][y][z]->mesh->UpdateMesh();
						}
						break;
					}
					else
						break;
				}
				// 아래쪽면 그리딩 메쉬
				for (int t = x + 1; t < Size_X; t++)
				{
					if (block[x][y][z]->type == block[t][y][z]->type)
					{
						if (block[t][y][z]->isCheck[(int)_Dir::Under])
						{
							block[t][y][z]->isCheck[(int)_Dir::Under] = false;
							voxel[(int)_Dir::Under][t][y][z]->visible = false;
						}
						if (t == Size_X - 1)
						{
							if (voxel[(int)_Dir::Under][x][y][z] != nullptr)
							{
								VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Under][x][y][z]->mesh->vertices;
								vertex[2].position.x = t - x + 0.5f;
								vertex[2].uv.x = t - x;
								vertex[3].position.x = t - x + 0.5f;
								vertex[3].uv.x = t - x;
								voxel[(int)_Dir::Under][x][y][z]->mesh->UpdateMesh();
							}
						}
					}
					else if (t - x != 1) {
						if (voxel[(int)_Dir::Under][x][y][z] != nullptr)
						{
							t--;
							VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Under][x][y][z]->mesh->vertices;
							vertex[2].position.x = t - x + 0.5f;
							vertex[2].uv.x = t - x;
							vertex[3].position.x = t - x + 0.5f;
							vertex[3].uv.x = t - x;
							voxel[(int)_Dir::Under][x][y][z]->mesh->UpdateMesh();
						}
						break;
					}
					else
						break;
				}
				// 앞쪽면 그리딩 메쉬
				for (int t = y + 1; t < Size_Y; t++)
				{
					if (block[x][y][z]->type == block[x][t][z]->type)
					{
						if (block[x][t][z]->isCheck[(int)_Dir::Front])
						{
							block[x][t][z]->isCheck[(int)_Dir::Front] = false;
							voxel[(int)_Dir::Front][x][t][z]->visible = false;
						}
						if (t == Size_Y - 1)
						{
							if (voxel[(int)_Dir::Front][x][y][z] != nullptr)
							{
								VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Front][x][y][z]->mesh->vertices;
								vertex[0].position.z = -(t - y + 0.5f);
								vertex[0].uv.y = t - y;
								vertex[3].position.z = -(t - y + 0.5f);
								vertex[3].uv.y = t - y;
								voxel[(int)_Dir::Front][x][y][z]->mesh->UpdateMesh();
							}
							break;
						}
					}
					else if (t - y != 1) {
						if (voxel[(int)_Dir::Front][x][y][z] != nullptr)
						{
							t--;
							VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Front][x][y][z]->mesh->vertices;
							vertex[0].position.z = -(t - y + 0.5f);
							vertex[0].uv.y = t - y + 1;
							vertex[3].position.z = -(t - y + 0.5f);
							vertex[3].uv.y = t - y + 1;
							voxel[(int)_Dir::Front][x][y][z]->mesh->UpdateMesh();
						}
						break;
					}
					else
						break;
				}
				// 뒤쪽면 그리딩 메쉬
				for (int t = y + 1; t < Size_Y; t++)
				{
					if (block[x][y][z]->type == block[x][t][z]->type)
					{
						if (block[x][t][z]->isCheck[(int)_Dir::Back])
						{
							block[x][t][z]->isCheck[(int)_Dir::Back] = false;
							voxel[(int)_Dir::Back][x][t][z]->visible = false;
						}
						if (t == Size_Y - 1)
						{
							if (voxel[(int)_Dir::Back][x][y][z] != nullptr)
							{
								VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Back][x][y][z]->mesh->vertices;
								vertex[1].position.z = (t - y + 0.5f);
								vertex[1].uv.y = t - y;
								vertex[2].position.z = (t - y + 0.5f);
								vertex[2].uv.y = t - y;
								voxel[(int)_Dir::Back][x][y][z]->mesh->UpdateMesh();
							}
							break;
						}
					}
					else if (t - y != 1) {
						if (voxel[(int)_Dir::Back][x][y][z] != nullptr)
						{
							t--;
							VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Back][x][y][z]->mesh->vertices;
							vertex[1].position.z = (t - y + 0.5f);
							vertex[1].uv.y = t - y + 1;
							vertex[2].position.z = (t - y + 0.5f);
							vertex[2].uv.y = t - y + 1;
							voxel[(int)_Dir::Back][x][y][z]->mesh->UpdateMesh();
						}
						break;
					}
					else
						break;
				}
				// 왼쪽면 그리딩 메쉬
				for (int t = y + 1; t < Size_Y; t++)
				{
					if (block[x][y][z]->type == block[x][t][z]->type)
					{
						if (block[x][t][z]->isCheck[(int)_Dir::Left])
						{
							block[x][t][z]->isCheck[(int)_Dir::Left] = false;
							voxel[(int)_Dir::Left][x][t][z]->visible = false;
						}
						if (t == Size_Y - 1)
						{
							if (voxel[(int)_Dir::Left][x][y][z] != nullptr)
							{
								VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Left][x][y][z]->mesh->vertices;
								vertex[0].position.z = -(t - y + 0.5f);
								vertex[0].uv.y = t - y;
								vertex[3].position.z = -(t - y + 0.5f);
								vertex[3].uv.y = t - y;
								voxel[(int)_Dir::Left][x][y][z]->mesh->UpdateMesh();
							}
							break;
						}
					}
					else if (t - y != 1) {
						if (voxel[(int)_Dir::Left][x][y][z] != nullptr)
						{
							t--;
							VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Left][x][y][z]->mesh->vertices;
							vertex[0].position.z = -(t - y + 0.5f);
							vertex[0].uv.y = t - y + 1;
							vertex[3].position.z = -(t - y + 0.5f);
							vertex[3].uv.y = t - y + 1;
							voxel[(int)_Dir::Left][x][y][z]->mesh->UpdateMesh();
						}
						break;
					}
					else
						break;
				}
				// 오른쪽면 그리딩 메쉬
				for (int t = y + 1; t < Size_Y; t++)
				{
					if (block[x][y][z]->type == block[x][t][z]->type)
					{
						if (block[x][t][z]->isCheck[(int)_Dir::Right])
						{
							block[x][t][z]->isCheck[(int)_Dir::Right] = false;
							voxel[(int)_Dir::Right][x][t][z]->visible = false;
						}
						if (t == Size_Y - 1)
						{
							if (voxel[(int)_Dir::Right][x][y][z] != nullptr)
							{
								VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Right][x][y][z]->mesh->vertices;
								vertex[1].position.z = (t - y + 0.5f);
								vertex[1].uv.y = t - y;
								vertex[2].position.z = (t - y + 0.5f);
								vertex[2].uv.y = t - y;
								voxel[(int)_Dir::Right][x][y][z]->mesh->UpdateMesh();
							}
							break;
						}
					}
					else if (t - y != 1) {
						if (voxel[(int)_Dir::Right][x][y][z] != nullptr)
						{
							t--;
							VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Right][x][y][z]->mesh->vertices;
							vertex[1].position.z = (t - y + 0.5f);
							vertex[1].uv.y = t - y + 1;
							vertex[2].position.z = (t - y + 0.5f);
							vertex[2].uv.y = t - y + 1;
							voxel[(int)_Dir::Right][x][y][z]->mesh->UpdateMesh();
						}
						break;
					}
					else
						break;
				}
			}
		}
	}
}

void Chunk::SetRendering()
{
	for (int x = 0; x < Size_X; x++)
	{
		for (int z = 0; z < Size_Z; z++)
		{
			for (int y = 0; y < Size_Y; y++)
			{
				string file;
				switch (block[x][y][z]->type)
				{
				case _BlockType::GRASS:
					file = "Grass.xml";
					break;
				case _BlockType::DIRT:
					file = "Dirt.xml";
					break;
				case _BlockType::STONE:
					file = "Stone.xml";
					break;
				default:
					break;
				}
				// 윗면 렌더링
				if (y == 0 || block[x][y - 1][z]->type == _BlockType::AIR)
				{
					block[x][y][z]->isCheck[(int)_Dir::Top] = true;
					voxel[(int)_Dir::Top][x][y][z] = Actor::Create();
					voxel[(int)_Dir::Top][x][y][z]->LoadFile(file);
					voxel[(int)_Dir::Top][x][y][z]->SetWorldPos(block[x][y][z]->pos);
					voxel[(int)_Dir::Top][x][y][z]->MoveWorldPos(Vector3(0, 1, 0));
					voxel[(int)_Dir::Top][x][y][z]->Update();
					arr.push_back(voxel[(int)_Dir::Top][x][y][z]);
				}
				// 아랫면 렌더링
				if (y == Size_Y - 1 || block[x][y + 1][z]->type == _BlockType::AIR)
				{
					block[x][y][z]->isCheck[(int)_Dir::Under] = true;
					voxel[(int)_Dir::Under][x][y][z] = Actor::Create();
					voxel[(int)_Dir::Under][x][y][z]->LoadFile(file);
					voxel[(int)_Dir::Under][x][y][z]->SetWorldPos(block[x][y][z]->pos);
					voxel[(int)_Dir::Under][x][y][z]->rotation = Vector3(180, 0, 0) * TORADIAN;
					voxel[(int)_Dir::Under][x][y][z]->Update();
					arr.push_back(voxel[(int)_Dir::Under][x][y][z]);
				}
				// 앞쪽면 렌더링
				if (z == 0 || block[x][y][z - 1]->type == _BlockType::AIR)
				{
					block[x][y][z]->isCheck[(int)_Dir::Front] = true;
					voxel[(int)_Dir::Front][x][y][z] = Actor::Create();
					voxel[(int)_Dir::Front][x][y][z]->LoadFile(file);
					voxel[(int)_Dir::Front][x][y][z]->SetWorldPos(block[x][y][z]->pos);
					voxel[(int)_Dir::Front][x][y][z]->MoveWorldPos(Vector3(0, 0.5f, -0.5f));
					voxel[(int)_Dir::Front][x][y][z]->rotation = Vector3(-90, 0, 0) * TORADIAN;
					voxel[(int)_Dir::Front][x][y][z]->Update();
					arr.push_back(voxel[(int)_Dir::Front][x][y][z]);
				}
				// 뒤쪽면 렌더링
				if (z == Size_Z - 1 || block[x][y][z + 1]->type == _BlockType::AIR)
				{
					block[x][y][z]->isCheck[(int)_Dir::Back] = true;
					voxel[(int)_Dir::Back][x][y][z] = Actor::Create();
					voxel[(int)_Dir::Back][x][y][z]->LoadFile(file);
					voxel[(int)_Dir::Back][x][y][z]->SetWorldPos(block[x][y][z]->pos);
					voxel[(int)_Dir::Back][x][y][z]->MoveWorldPos(Vector3(0, 0.5f, +0.5f));
					voxel[(int)_Dir::Back][x][y][z]->rotation = Vector3(90, 0, 0) * TORADIAN;
					voxel[(int)_Dir::Back][x][y][z]->Update();
					arr.push_back(voxel[(int)_Dir::Back][x][y][z]);
				}
				// 왼쪽면 렌더링
				if (x == 0 || block[x - 1][y][z]->type == _BlockType::AIR)
				{
					block[x][y][z]->isCheck[(int)_Dir::Left] = true;
					voxel[(int)_Dir::Left][x][y][z] = Actor::Create();
					voxel[(int)_Dir::Left][x][y][z]->LoadFile(file);
					voxel[(int)_Dir::Left][x][y][z]->SetWorldPos(block[x][y][z]->pos);
					voxel[(int)_Dir::Left][x][y][z]->MoveWorldPos(Vector3(-0.5f, 0.5f, 0));
					voxel[(int)_Dir::Left][x][y][z]->rotation = Vector3(-90, 90, 0) * TORADIAN;
					voxel[(int)_Dir::Left][x][y][z]->Update();
					arr.push_back(voxel[(int)_Dir::Left][x][y][z]);
				}
				// 오른쪽면 렌더링
				if (x == Size_X - 1 || block[x + 1][y][z]->type == _BlockType::AIR)
				{
					block[x][y][z]->isCheck[(int)_Dir::Right] = true;
					voxel[(int)_Dir::Right][x][y][z] = Actor::Create();
					voxel[(int)_Dir::Right][x][y][z]->LoadFile(file);
					voxel[(int)_Dir::Right][x][y][z]->SetWorldPos(block[x][y][z]->pos);
					voxel[(int)_Dir::Right][x][y][z]->MoveWorldPos(Vector3(+0.5f, 0.5f, 0));
					voxel[(int)_Dir::Right][x][y][z]->rotation = Vector3(90, 90, 0) * TORADIAN;
					voxel[(int)_Dir::Right][x][y][z]->Update();
					arr.push_back(voxel[(int)_Dir::Right][x][y][z]);
				}
			}
		}
	}
}

void Chunk::Render()
{
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i]->Render();
	}
}