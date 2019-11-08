
#pragma once

#include <memory>
#include "WindowsGDI.h"
#include "RenderingSoftwareInterface.h"

class WindowsGDI;
class WindowsRSI : public WindowsGDI, public RenderingSoftwareInterface
{
public:
	WindowsRSI() = default;
	~WindowsRSI();

public:
	virtual bool Init(const ScreenPoint& InScreenSize) override;
	virtual void Shutdown() override;
	virtual bool IsInitialized() const { return IsGDIInitialized; }
	virtual void SetBlendingMode(BlendingModes InNewBlendingMode) override;

	virtual void Clear(const LinearColor& InClearColor) override;
	virtual void BeginFrame() override;
	virtual void EndFrame() override;

	virtual void DrawPoint(const Vector2& InVectorPos, const LinearColor& InColor) override;
	virtual void DrawLine(const Vector2& InStartPos, const Vector2& InEndPos, const LinearColor& InColor) override;
	virtual void DrawTriangle(const Vector2& InVector1, const Vector2& InVector2, const Vector2& InVector3, const LinearColor& InColor) override;
	virtual void DrawTriangle(const Vertex& InVertex1, const Vertex& InVertex2, const Vertex& InVertex3) override;

	virtual void DrawFullVerticalLine(int InX, const LinearColor& InColor) override;
	virtual void DrawFullHorizontalLine(int InY, const LinearColor& InColor) override;

	virtual void Render(const Matrix3x3& worldMatrix, const unsigned int& indexCount) override;
	virtual void IASetVertexBuffer(Vertex* vertexBuffer) override;
	virtual void IASetIndexBuffer(unsigned int* indexBuffer) override;

private:
	void SetPixel(const ScreenPoint& InPos, const LinearColor& InColor);

	BlendingModes BlendingMode = BlendingModes::Opaque;
};
