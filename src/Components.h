#pragma once

/*
	p1
	   .  p0
	p2
*/
constexpr float scale = 1.0f;
struct BoidModel
{
	float p0x, p0y, p1x, p1y, p2x, p2y;
	BoidModel()
	{
		p0x = 5.f * scale;
		p0y = 0.f * scale;
		p1x = -5.f * scale;
		p1y = -3.f * scale;
		p2x = -5.f * scale;
		p2y = 3.f * scale;
	}
};