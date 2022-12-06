#include "stdafx.h"

Chunk::Chunk(int posX, int posZ, PerlinNoise* pn)
{
	for (int x = 0; x < Size_X; x++)
	{
		for (int z = 0; z < Size_Z; z++)
		{
			double q = (double)x / (double)posX * Size_X * Chunk_X;
			double w = (double)z / (double)posZ * Size_Z * Chunk_Z;

			double noise = 20 * pn->noise(q, w, 0.9f);
			noise = noise - floor(noise);
			int depth;
			if (floor(255 * noise) > 200)
				depth = 4;
			else if (floor(255 * noise) > 150)
				depth = 3;
			else if (floor(255 * noise) > 100)
				depth = 2;
			else if (floor(255 * noise) > 50)
				depth = 1;
			else
				depth = 0;
			for (int y = 0; y < Size_Y; y++)
			{
				if (y < depth)
				{
					block[x][y][z] = new Block(_BlockType::AIR);
				}
				else
				{
					block[x][y][z] = new Block(_BlockType::STONE);
				}
				block[x][y][z]->pos = Vector3(posX * Size_X + x, -y, posZ * Size_Z + z);
			}
		}
		cout << endl;
	}
	position = Vector3(posX * Size_X + Size_X * 0.5f, 0.0f, posZ * Size_Z + Size_Z * 0.5f);
	SetRendering();
	SetGreedyMeshing();
	SetArray();
}

Chunk::~Chunk()
{
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

int Chunk::GetChunkSize()
{
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
				if (block[x][y][z]->type != _BlockType::AIR)
				{
					// 위쪽면 그리딩 메쉬
					if (block[x][y][z]->isCheck[(int)_Dir::Top])
					{
						for (int t = x + 1; t < Size_X; t++)
						{
							if (y == 0 || block[t][y - 1][z]->type == _BlockType::AIR)
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
										VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Top][x][y][z]->mesh->vertices;
										vertex[2].position.x = t - x + 0.5f;
										vertex[2].uv.x = t - x;
										vertex[3].position.x = t - x + 0.5f;
										vertex[3].uv.x = t - x;
										voxel[(int)_Dir::Top][x][y][z]->mesh->UpdateMesh();
										break;
									}
								}
								else
								{
									t--;
									if (t - x > 0)
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
							else
							{
								t--;
								if (t - x > 0)
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
					}
					// 아래쪽면 그리딩 메쉬
					if (block[x][y][z]->isCheck[(int)_Dir::Under])
					{
						for (int t = x + 1; t < Size_X; t++)
						{
							if (y == Size_Y - 1 || block[t][y + 1][z]->type == _BlockType::AIR)
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
										VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Under][x][y][z]->mesh->vertices;
										vertex[2].position.x = t - x + 0.5f;
										vertex[2].uv.x = t - x;
										vertex[3].position.x = t - x + 0.5f;
										vertex[3].uv.x = t - x;
										voxel[(int)_Dir::Under][x][y][z]->mesh->UpdateMesh();
									}
								}
								else{
									t--;
									if (t - x > 0)
									{
										VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Under][x][y][z]->mesh->vertices;
										vertex[2].position.x = t - x + 0.5f;
										vertex[2].uv.x = t - x;
										vertex[3].position.x = t - x + 0.5f;
										vertex[3].uv.x = t - x;
										voxel[(int)_Dir::Under][x][y][z]->mesh->UpdateMesh();
									}
									break;
								}
							}
							else
							{
								t--;
								if (t - x > 0)
								{
									VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Under][x][y][z]->mesh->vertices;
									vertex[2].position.x = t - x + 0.5f;
									vertex[2].uv.x = t - x;
									vertex[3].position.x = t - x + 0.5f;
									vertex[3].uv.x = t - x;
									voxel[(int)_Dir::Under][x][y][z]->mesh->UpdateMesh();
								}
								break;
							}
						}
					}
					// 앞쪽면 그리딩 메쉬
					if (block[x][y][z]->isCheck[(int)_Dir::Front])
					{
						for (int t = y + 1; t < Size_Y; t++)
						{
							if (z == 0 || block[x][t][z - 1]->type == _BlockType::AIR)
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
										VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Front][x][y][z]->mesh->vertices;
										vertex[0].position.z = -(t - y + 0.5f);
										vertex[0].uv.y = t - y;
										vertex[3].position.z = -(t - y + 0.5f);
										vertex[3].uv.y = t - y;
										voxel[(int)_Dir::Front][x][y][z]->mesh->UpdateMesh();
										break;
									}
								}
								else
								{
									t--;
									if (t - y > 0)
									{
										VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Front][x][y][z]->mesh->vertices;
										vertex[0].position.z = -(t - y + 0.5f);
										vertex[0].uv.y = t - y + 1;
										vertex[3].position.z = -(t - y + 0.5f);
										vertex[3].uv.y = t - y + 1;
										voxel[(int)_Dir::Front][x][y][z]->mesh->UpdateMesh();
									}
									break;
								}
							}
							else
							{
								t--;
								if (t - y > 0)
								{
									VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Front][x][y][z]->mesh->vertices;
									vertex[0].position.z = -(t - y + 0.5f);
									vertex[0].uv.y = t - y + 1;
									vertex[3].position.z = -(t - y + 0.5f);
									vertex[3].uv.y = t - y + 1;
									voxel[(int)_Dir::Front][x][y][z]->mesh->UpdateMesh();
								}
								break;
							}
						}
					}
					// 뒤쪽면 그리딩 메쉬
					if (block[x][y][z]->isCheck[(int)_Dir::Back])
					{
						for (int t = y + 1; t < Size_Y; t++)
						{
							if (z == Size_Z - 1 || block[x][t][z + 1]->type == _BlockType::AIR)
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
										VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Back][x][y][z]->mesh->vertices;
										vertex[1].position.z = (t - y + 0.5f);
										vertex[1].uv.y = t - y;
										vertex[2].position.z = (t - y + 0.5f);
										vertex[2].uv.y = t - y;
										voxel[(int)_Dir::Back][x][y][z]->mesh->UpdateMesh();
										break;
									}
								}
								else
								{
									t--;
									if (t - y > 0)
									{
										VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Back][x][y][z]->mesh->vertices;
										vertex[1].position.z = (t - y + 0.5f);
										vertex[1].uv.y = t - y + 1;
										vertex[2].position.z = (t - y + 0.5f);
										vertex[2].uv.y = t - y + 1;
										voxel[(int)_Dir::Back][x][y][z]->mesh->UpdateMesh();
									}
									break;
								}
							}
							else
							{
								t--;
								if (t - y > 0)
								{
									VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Back][x][y][z]->mesh->vertices;
									vertex[1].position.z = (t - y + 0.5f);
									vertex[1].uv.y = t - y + 1;
									vertex[2].position.z = (t - y + 0.5f);
									vertex[2].uv.y = t - y + 1;
									voxel[(int)_Dir::Back][x][y][z]->mesh->UpdateMesh();
								}
								break;
							}
						}
					}
					// 왼쪽면 그리딩 메쉬
					if (block[x][y][z]->isCheck[(int)_Dir::Left])
					{
						for (int t = y + 1; t < Size_Y; t++)
						{
							if (x == 0 || block[x - 1][t][z]->type == _BlockType::AIR)
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
								else
								{
									t--;
									if (t - y > 0)
									{
										VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Left][x][y][z]->mesh->vertices;
										vertex[0].position.z = -(t - y + 0.5f);
										vertex[0].uv.y = t - y + 1;
										vertex[3].position.z = -(t - y + 0.5f);
										vertex[3].uv.y = t - y + 1;
										voxel[(int)_Dir::Left][x][y][z]->mesh->UpdateMesh();
									}
									break;
								}
							}
							else
							{
								t--;
								if (t - y > 0)
								{
									VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Left][x][y][z]->mesh->vertices;
									vertex[0].position.z = -(t - y + 0.5f);
									vertex[0].uv.y = t - y + 1;
									vertex[3].position.z = -(t - y + 0.5f);
									vertex[3].uv.y = t - y + 1;
									voxel[(int)_Dir::Left][x][y][z]->mesh->UpdateMesh();
								}
								break;
							}
						}
					}
					// 오른쪽면 그리딩 메쉬
					if (block[x][y][z]->isCheck[(int)_Dir::Right])
					{
						for (int t = y + 1; t < Size_Y; t++)
						{
							if (x == Size_X - 1 || block[x + 1][t][z]->type == _BlockType::AIR)
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
								else
								{
									t--;
									if (t - y > 0)
									{
										VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Right][x][y][z]->mesh->vertices;
										vertex[1].position.z = (t - y + 0.5f);
										vertex[1].uv.y = t - y + 1;
										vertex[2].position.z = (t - y + 0.5f);
										vertex[2].uv.y = t - y + 1;
										voxel[(int)_Dir::Right][x][y][z]->mesh->UpdateMesh();
									}
									break;
								}
							}
							else 
							{
								t--;
								if (t - y > 0)
								{
									VertexPT* vertex = (VertexPT*)voxel[(int)_Dir::Right][x][y][z]->mesh->vertices;
									vertex[1].position.z = (t - y + 0.5f);
									vertex[1].uv.y = t - y + 1;
									vertex[2].position.z = (t - y + 0.5f);
									vertex[2].uv.y = t - y + 1;
									voxel[(int)_Dir::Right][x][y][z]->mesh->UpdateMesh();
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

void Chunk::SetRendering()
{
	for (int x = 0; x < Size_X; x++)
	{
		for (int z = 0; z < Size_Z; z++)
		{
			for (int y = 0; y < Size_Y; y++)
			{
				if (block[x][y][z]->type != _BlockType::AIR)
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
}

void Chunk::Render()
{
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i]->Render();
	}
}