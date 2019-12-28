#include "texture.h"
#include "imageloader.h"

using namespace std;

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); 				//Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); 	//Tell OpenGL which texture to edit
	
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, 					   //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, 			   //GL_UNSIGNED_BYTE, because pixels are stored
				                   			   //as unsigned numbers
				 image->pixels);               //The actual pixel data
				 
	return textureId; 						   //Returns the id of the texture
}

void getTexture() {
	Image* image = loadBMP("baseSide.bmp");
		_sideBase = loadTexture(image);
		delete image;
		
		image = loadBMP("baseUpper.bmp");
		_upperBase = loadTexture(image);
		delete image;
		
		image = loadBMP("baseBottom.bmp");
		_bottomBase = loadTexture(image);
		delete image;
		
		image = loadBMP("baseMSide.bmp");
		_mSideBase = loadTexture(image);
		delete image;
		
		image = loadBMP("baseStair.bmp");
		_stairSide = loadTexture(image);
		delete image;
}
