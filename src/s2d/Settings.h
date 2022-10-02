#pragma once

namespace s2d
{

// depth
#define SKY_DEPTH				0.0f;
#define FAR_BACKGROUND_DEPTH	-.5f;
#define NEAR_BACKGROUND_DEPTH	-.1f;
#define SPRITE_DEPTH			0.0f;
#define FOREGROUND_DEPTH		0.5f;
#define HUD_DEPTH		        0.0f;

	// layer
	enum RenderLayer
	{
		SKY_LAYER,
		FAR_BACKGROUND_LAYER,
		NEAR_BACKGROUND_LAYER,
		SPRITE_BACKGROUND_LAYER,
		SPRITE_LAYER,
		SPRITE_FOREGROUND_LAYER,
		FOREGROUND_LAYER,
		HUD_LAYER
	};

}
