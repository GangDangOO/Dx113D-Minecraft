#include "stdafx.h"

Block::Block(int type)
{
	string name = "voxel";
	voxel = Actor::Create(name);

	voxel->LoadFile("Voxel.xml");
}

Block::~Block()
{

}

void Block::Init()
{


}

void Block::Release()
{

}

void Block::Update()
{
	ImGui::Begin("Hierarchy");
	voxel->RenderHierarchy();
	ImGui::End();

	voxel->Update();
}

void Block::LateUpdate()
{

}

void Block::PreRender()
{

}

void Block::Render()
{
	voxel->Render();
}

void Block::ResizeScreen()
{

}
