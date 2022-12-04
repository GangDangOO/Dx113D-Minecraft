#include "stdafx.h"

Block::Block(_BlockType _type)
{
	type = _type;
	voxel = Actor::Create();
	switch (type)
	{
	case _BlockType::GRASS:
		voxel->LoadFile("Grass.xml");
		break;
	case _BlockType::DIRT:
		voxel->LoadFile("Dirt.xml");
		break;
	case _BlockType::STONE:
		voxel->LoadFile("Stone.xml");
		break;
	default:
		voxel->visible = false;
		break;
	}
}

Block::~Block()
{

}

void Block::RenderHierarchy()
{
	voxel->RenderHierarchy();
}

void Block::Release()
{

}

void Block::Update()
{
	voxel->Update();
}

void Block::Render()
{
	voxel->Render();
}