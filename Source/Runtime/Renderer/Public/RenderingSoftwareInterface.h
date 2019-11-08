
#pragma once

#include "ScreenPoint.h"
#include "LinearColor.h"
#include "RSIDataTypes.h"

class RenderingSoftwareInterface
{
public:
	virtual bool Init(const ScreenPoint& InSize) = 0;
	virtual void Shutdown() = 0;
	virtual bool IsInitialized() const = 0;
	virtual void SetBlendingMode(BlendingModes InNewBlendingMode) = 0;

	virtual void Clear(const LinearColor& InClearColor) = 0;
	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;

	virtual void DrawPoint(const Vector2& InVectorPos, const LinearColor& InColor) = 0;
	virtual void DrawLine(const Vector2& InStartPos, const Vector2& InEndPos, const LinearColor& InColor) = 0;
	virtual void DrawTriangle(const Vector2& InVector1, const Vector2& InVector2, const Vector2& InVector3, const LinearColor& InColor) = 0;
	virtual void DrawTriangle(const Vertex& InVertex1, const Vertex& InVertex2, const Vertex& InVertex3) = 0;

	virtual void DrawFullVerticalLine(int InX, const LinearColor& InColor) = 0;
	virtual void DrawFullHorizontalLine(int InY, const LinearColor& InColor) = 0;

	virtual void Render(const Matrix3x3& worldMatrix, const unsigned int& indexCount) = 0;
	virtual void IASetVertexBuffer(Vertex* vertexBuffer) = 0;
	virtual void IASetIndexBuffer(unsigned int* indexBuffer) = 0;

protected:
	Vertex* vertexBuffer;
	unsigned int* indexBuffer;
};
