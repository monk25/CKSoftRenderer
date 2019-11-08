
#include "Precompiled.h"
#include "WindowsRSI.h"
#include "WindowsGDI.h"

WindowsRSI::~WindowsRSI()
{
}

bool WindowsRSI::Init(const ScreenPoint& InScreenSize)
{
	SetBlendingMode(BlendingMode);
	return InitializeGDI(InScreenSize);
}

void WindowsRSI::Shutdown()
{
	ReleaseGDI();
}

void WindowsRSI::SetBlendingMode(BlendingModes InNewBlendingMode)
{
	BlendingMode = InNewBlendingMode;
	//using namespace std::placeholders;
	//if (BlendingMode == BlendingModes::Opaque)
	//{
	//	SetPixel = std::bind(&WindowsGDI::SetPixelOpaque, this, _1, _2);
	//}
	//else if (BlendingMode == BlendingModes::AlphaBlending)
	//{
	//	SetPixel = std::bind(&WindowsGDI::SetPixelAlphaBlending, this, _1, _2);
	//}
}

void WindowsRSI::Clear(const LinearColor & InClearColor)
{
	FillBuffer(InClearColor.ToColor32());
	ClearDepthBuffer();
}

void WindowsRSI::BeginFrame()
{
}

void WindowsRSI::EndFrame()
{
	SwapBuffer();
}

void WindowsRSI::DrawPoint(const Vector2& InVectorPos, const LinearColor& InColor)
{
	SetPixel(ScreenPoint::ToScreenCoordinate(ScreenSize, InVectorPos), InColor);
}

void WindowsRSI::DrawLine(const Vector2& InStartPos, const Vector2& InEndPos, const LinearColor& InColor)
{
	int w = InEndPos.X - InStartPos.X;
	int h = InEndPos.Y - InStartPos.Y;
	int dirX = w < 0 ? -1 : 1;
	int dirY = h < 0 ? -1 : 1;
	h *= dirY;
	w *= dirX;
	bool slope = w > h;

	int f = slope ? 2 * h - w : h - 2 * w;
	int underF = slope ? 2 * h : 2 * (h - w);
	int overF = slope ? 2 * (h - w) : -2 * w;

	ScreenPoint p{ ScreenPoint::ToScreenCoordinate(ScreenSize, InStartPos) };
	ScreenPoint underV = slope ? ScreenPoint{ dirX, 0 } : ScreenPoint{ dirX, -dirY };
	ScreenPoint overV = slope ? ScreenPoint{ dirX, -dirY } : ScreenPoint{ 0, -dirY };

	int length = slope ? w : h;
	for (int i = 0; i <= length; ++i)
	{
		SetPixel(p, InColor);
		if (f < 0) {
			f += underF;
			p = p + underV;
		}
		else {
			f += overF;
			p = p + overV;
		}
	}
}

void WindowsRSI::DrawTriangle(const Vector2& InVector1, const Vector2& InVector2, const Vector2& InVector3, const LinearColor& InColor)
{
	DrawLine(InVector1, InVector2, InColor);
	DrawLine(InVector1, InVector3, InColor);
	DrawLine(InVector2, InVector3, InColor);
}

void WindowsRSI::DrawTriangle(const Vertex& InVertex1, const Vertex& InVertex2, const Vertex& InVertex3)
{
	DrawLine(InVertex1.pos, InVertex2.pos, LinearColor::Blue);
	DrawLine(InVertex1.pos, InVertex3.pos, LinearColor::Blue);
	DrawLine(InVertex2.pos, InVertex3.pos, LinearColor::Blue);
}

void WindowsRSI::DrawFullVerticalLine(int InX, const LinearColor & InColor)
{
	if (InX < 0 || InX >= ScreenSize.X)
	{
		return;
	}

	for (int y = 0; y < ScreenSize.Y; ++y)
	{
		SetPixel(ScreenPoint(InX, y), InColor);
	}

	return;
}

void WindowsRSI::DrawFullHorizontalLine(int InY, const LinearColor & InColor)
{
	if (InY < 0 || InY >= ScreenSize.Y)
	{
		return;
	}

	for (int x = 0; x < ScreenSize.X; ++x)
	{
		SetPixel(ScreenPoint(x, InY), InColor);
	}
}

void WindowsRSI::Render(const Matrix3x3& worldMatrix, const unsigned int& indexCount)
{
	for (int i = 0; i < indexCount; i += 3) {
		Vertex v1 = vertexBuffer[indexBuffer[i]];
		Vertex v2 = vertexBuffer[indexBuffer[i + 1]];
		Vertex v3 = vertexBuffer[indexBuffer[i + 2]];
		v1.pos *= worldMatrix;
		v2.pos *= worldMatrix;
		v3.pos *= worldMatrix;
		DrawTriangle(v1, v2, v3);
	}
}

void WindowsRSI::IASetVertexBuffer(Vertex* vertexBuffer)
{
	this->vertexBuffer = vertexBuffer;
}

void WindowsRSI::IASetIndexBuffer(unsigned int* indexBuffer)
{
	this->indexBuffer = indexBuffer;
}

void WindowsRSI::SetPixel(const ScreenPoint& InPos, const LinearColor& InColor)
{
	if (BlendingMode == BlendingModes::Opaque)
	{
		SetPixelOpaque(InPos, InColor);
	}
	else if (BlendingMode == BlendingModes::AlphaBlending)
	{
		SetPixelAlphaBlending(InPos, InColor);
	}
}
