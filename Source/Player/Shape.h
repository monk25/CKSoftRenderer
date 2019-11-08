#pragma once

#include "RenderingSoftwareInterface.h"
#include "RSIDataTypes.h"

class Shape
{
public:
	Shape() : vertices(nullptr), vertexCount(0),
		indices(nullptr), indexCount(0) {};
	virtual ~Shape() {
		delete[] vertices;
		delete[] indices;
	}

public:
	void Render(RenderingSoftwareInterface* RSI) {
		RSI->IASetVertexBuffer(vertices);
		RSI->IASetIndexBuffer(indices);
	}

	const unsigned int& GetIndexCount() { return indexCount; }

protected:
	Vertex* vertices;
	unsigned int vertexCount;
	unsigned int* indices;
	unsigned int indexCount;
};

class Triangle :
	public Shape
{
public:
	Triangle() {
		Initialize();
		SetTriangle(
			Vertex{ Vector2{ -50.0f, -50.0f }},
			Vertex{ Vector2{   0.0f,  50.0f }},
			Vertex{ Vector2{  50.0f, -50.0f }});
	}
	Triangle(const Vector2& p1, const Vector2& p2, const Vector2& p3) {
		Initialize();
		SetTriangle(p1, p2, p3);
	}
	Triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) {
		Initialize();
		SetTriangle(v1, v2, v3);
	}
	~Triangle() {}

public:
	void SetTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3) {
		vertices[0].pos = p1;
		vertices[1].pos = p2;
		vertices[2].pos = p3;
	}
	void SetTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) {
		vertices[0] = v1;
		vertices[1] = v2;
		vertices[2] = v3;
	}

private:
	void Initialize() {
		vertexCount = 3;
		indexCount = 3;
		vertices = new Vertex[vertexCount];
		indices = new unsigned int[indexCount] { 0, 1, 2 };
	}

};

class Quad :
	public Shape
{
public:
	Quad() {
		Initialize();
		SetQuad(
			Vertex{ Vector2{-50,  50} },
			Vertex{ Vector2{ 50,  50} },
			Vertex{ Vector2{-50, -50} },
			Vertex{ Vector2{ 50, -50} });
	}
	Quad(const int& left, const int& top, const int& right, const int& bottom) {
		Initialize();
		SetQuad(left, top, right, bottom);
	}
	Quad(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4) {
		Initialize();
		SetQuad(p1, p2, p3, p4);
	}
	Quad(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4) {
		Initialize();
		SetQuad(v1, v2, v3, v4);
	}
	~Quad() {}

public:
	void SetQuad(const int& left, const int& top, const int& right, const int& bottom) {
		vertices[0].pos = Vector2{ left, top };
		vertices[1].pos = Vector2{ right, top };
		vertices[2].pos = Vector2{ left, bottom };
		vertices[3].pos = Vector2{ right, bottom };
	}
	void SetQuad(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4) {
		vertices[0].pos = p1;
		vertices[1].pos = p2;
		vertices[2].pos = p3;
		vertices[3].pos = p4;
	}
	void SetQuad(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4) {
		vertices[0] = v1;
		vertices[1] = v2;
		vertices[2] = v3;
		vertices[3] = v4;
	}

private:
	void Initialize() {
		vertexCount = 4;
		indexCount = 6;
		vertices = new Vertex[vertexCount];
		indices = new unsigned int[indexCount] { 0, 1, 2, 1, 3, 2 };
	}

};