#include "Quad.h"

Quad::Quad()
	: Quad(1, 1)
{
}

Quad::Quad(float width, float height)
{
	m_Vertices = {
		{ { -width,  height, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
		{ { -width, -height, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
		{ {  width,  height, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
		{ {  width, -height, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } },
	};

	m_Indices = {
		0, 1, 2,
		2, 1, 3,
	};
	
	Finalize();
}
