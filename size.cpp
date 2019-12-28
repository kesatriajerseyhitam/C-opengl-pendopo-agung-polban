#include "size.h"

void loadSize() {
	  initialHeight = -1.0f,
	  baseHeight = 0.3,
	  baseWidth = (baseHeight/2.0)*baseHeight,
	  baseMiddleWidth = baseWidth - (baseWidth/(2.0/1.6)),
      baseDepth = baseWidth,
      baseMiddleDepth = baseDepth - (baseWidth/(2.0/0.3)),
      stairHeight = baseHeight/3,
      stairDepth = (baseDepth - baseMiddleDepth)/3,
      
      bodyInitialHeight = initialHeight + baseHeight,
	  bodyHeight = baseHeight*2.67,
	  bodyWidth = baseWidth*0.75,
	  bodyDepth = bodyWidth,
	  
	  bodyUpperHeight = bodyHeight - 0.7f,
	  
	  r1InitialHeight = bodyInitialHeight + bodyHeight + bodyUpperHeight - 0.04f,
	  r1Height = 0.5f,
	  r1Width = 0.9f,
	  r1Depth = r1Width,
	  
	  r2InitialHeight = r1InitialHeight + r1Height,
	  r2Height = r1Height - 0.15f,
	  r2Width = r1Width - 0.475f,
	  r2Depth = r2Width,
	  
	  r3InitialHeight = r2InitialHeight + r2Height,
	  r3Height = 0.20f,
	  r3Width = r2Width + 0.175f,
	  
	  sideStairHeight = baseHeight,
	  sideStairInitialWidth = baseWidth,
	  sideStairWidth = 0.3f,
	  sideStairDepth = 0.8f,
	  sStairDepth = sideStairDepth + (2*stairDepth);
}
