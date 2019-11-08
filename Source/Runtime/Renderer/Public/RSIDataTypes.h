#pragma once

enum class BlendingModes
{
	Opaque,
	AlphaBlending
};

struct Vertex
{
	Vector2 pos;
	LinearColor color;
};