#include "stdafx.h"

Block::Block(_BlockType _type)
{
	type = _type;
	for(int i = 0; i < 6; i++)
	{ 
		isCheck[i] = false;
	}
	pos = Vector3(0, 0, 0);
}

Block::~Block()
{

}