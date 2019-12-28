#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLuint _sideBase, _upperBase, _bottomBase, _mSideBase, _stairSide, _bodySide, _bodyUpper, _bodyUpperSide, _roof, _wall, _back, _backSide;

float angleX = 0.0f;
float angleY = 0.0f;
float xAxis = 0.0f, xCenter = xAxis, yAxis = 0;
float zAxis = 5.0, yCenter = yAxis, zCenter = 0;

float initialHeight,
	  baseHeight,
	  baseWidth,
	  baseMiddleWidth,
      baseDepth,
      baseMiddleDepth,
      stairHeight,
      stairDepth,
      
      bodyInitialHeight,
	  bodyHeight,
	  bodyWidth,
	  bodyDepth,
	  
	  bodyUpperHeight,
	  
	  r1InitialHeight,
	  r1Height,
	  r1Width,
	  r1Depth,
	  
	  r2InitialHeight,
	  r2Height,
	  r2Width,
	  r2Depth,
	  
	  r3InitialHeight,
	  r3Height,
	  r3Width,
	  
	  sideStairHeight,
	  sideStairInitialWidth,
	  sideStairWidth,
	  sideStairDepth,
	  sStairDepth;
