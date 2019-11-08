
#include "Precompiled.h"
#include "SoftRendererImpl2D.h"
#include "SoftRenderer.h"
#include "Shape.h"

SoftRendererImpl2D::SoftRendererImpl2D(SoftRenderer* InOwner)
{
	RSI = InOwner->RSI.get();
	ScreenSize = InOwner->CurrentScreenSize;
	InputManager = InOwner->GetInputManager();
}

SoftRendererImpl2D::~SoftRendererImpl2D()
{
}

void SoftRendererImpl2D::DrawGrid2D()
{
	// Colors to use
	LinearColor gridColor(LinearColor(0.8f, 0.8f, 0.8f, 0.3f));

	// Render Start
	RSI->Clear(LinearColor::White);

	// Draw Grid Line
	ScreenPoint screenHalfSize = ScreenSize.GetHalf();

	for (int x = screenHalfSize.X; x <= ScreenSize.X; x += Grid2DUnit)
	{
		RSI->DrawFullVerticalLine(x, gridColor);
		if (x > screenHalfSize.X)
		{
			RSI->DrawFullVerticalLine(2 * screenHalfSize.X - x, gridColor);
		}
	}

	for (int y = screenHalfSize.Y; y <= ScreenSize.Y; y += Grid2DUnit)
	{
		RSI->DrawFullHorizontalLine(y, gridColor);
		if (y > screenHalfSize.Y)
		{
			RSI->DrawFullHorizontalLine(2 * screenHalfSize.Y - y, gridColor);
		}
	}

	// Draw World Axis
	RSI->DrawFullHorizontalLine(screenHalfSize.Y, LinearColor::Red);
	RSI->DrawFullVerticalLine(screenHalfSize.X, LinearColor::Green);
}

void SoftRendererImpl2D::RenderFrameImpl()
{
	assert(RSI != nullptr && RSI->IsInitialized() && !ScreenSize.HasZero());

	DrawGrid2D();

	RSI->DrawPoint(Vector2::Zero, LinearColor::Blue);
	RSI->DrawPoint(Vector2::Zero + Vector2::UnitX, LinearColor::Blue);
	RSI->DrawPoint(Vector2::Zero - Vector2::UnitX, LinearColor::Blue);
	RSI->DrawPoint(Vector2::Zero + Vector2::UnitY, LinearColor::Blue);
	RSI->DrawPoint(Vector2::Zero - Vector2::UnitY, LinearColor::Blue);

	Quad q{ -100, 100, 100, -100 };
	q.Render(RSI);
	Matrix3x3 qMatrix;
	qMatrix.SetIdentity();
	//TRS
	Matrix3x3 TRS;
	Matrix3x3 T;
	Matrix3x3 R;
	Matrix3x3 S;
	T.SetIdentity();
	R.SetIdentity();
	S.SetIdentity();

	float dir = Math::Deg2Rad(90);
	T[2].X = 100;
	R[0].X = cosf(dir);
	R[0].Y = sinf(dir);
	R[1].X = -sinf(dir);
	R[1].Y = cosf(dir);
	S[0].X = 0.5f;
	TRS = T * R * S;
	qMatrix = qMatrix * TRS;
	RSI->Render(qMatrix, q.GetIndexCount());
}

void SoftRendererImpl2D::UpdateImpl(float DeltaSeconds)
{
}
