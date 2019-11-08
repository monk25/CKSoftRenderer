
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

void WindowsRSI::DrawLine(const Vector2 & InStartPos, const Vector2 & InEndPos, const LinearColor & InColor)
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

	//ScreenPoint lV = ScreenPoint::ToScreenCoordinate(ScreenSize, InStartPos);
	//ScreenPoint rV = ScreenPoint::ToScreenCoordinate(ScreenSize, InEndPos);

	//if (lV.X > rV.X) {
	//	ScreenPoint t = lV;
	//	lV = rV;
	//	rV = t;
	//}

	//ScreenPoint v = rV - lV;
	//int w = v.X;
	//int h = v.Y;
	//int length = w;

	//ScreenPoint underV = ScreenPoint{ 1, 0 };
	//ScreenPoint overV = ScreenPoint{ 1, 1 };

	//if (Math::Abs(w) < Math::Abs(h)) {
	//	int t = w;
	//	w = h;
	//	h = t;
	//	length = w;

	//	underV = ScreenPoint{ 0, 1 };
	//}
	//if (w * h < 0) {
	//	underV.Y *= -1;
	//	overV.Y *= -1;
	//	length = abs(length);
	//}

	//int underF = Math::Abs(h) * 2;
	//int overF = 2 * (Math::Abs(h) - Math::Abs(w));
	//int f = 2 * Math::Abs(h) - Math::Abs(w);


	//ScreenPoint dir{ 0,0 };
	//for (int i{ 0 }; i <= length; ++i) {
	//	SetPixel(ScreenPoint(lV + dir), InColor);
	//	if (f < 0) {
	//		dir.X += underV.X;
	//		dir.Y += underV.Y;
	//		f += underF;
	//	}
	//	else {
	//		dir.X += overV.X;
	//		dir.Y += overV.Y;
	//		f += overF;
	//	}
	//}
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
