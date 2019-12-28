/* -------- Final Assignment Computer Graphic -------- //

	Nama	: Auliya Raka Pratama
	Kelas	: 3A
	NIM		: 151511008
	
	3D Pendopo Using GLUT
	
// --------------------------------------------------- */

#include "imageloader.h"
#include "size.h"
#include "texture.h"

//using namespace std;

void loadSize() {
	FILE *myFile;
    myFile = fopen("sizePendopo.txt", "r");

    float numberArray[2];
    int i;

    if (myFile == NULL){
        printf("Error Reading File\n");
        exit (0);
    }
    
    for (i = 0; i < 2; i++){
        fscanf(myFile, "%f,", &numberArray[i] );
    }
	
	initialHeight = -1.0*numberArray[0],
	baseHeight = numberArray[1],
	baseWidth = baseHeight*(2.0/0.3),
	baseMiddleWidth = baseWidth - baseHeight*(1.6/0.3),
	baseDepth = baseWidth,
	baseMiddleDepth = baseDepth - baseHeight*(0.3/0.3),
	stairHeight = baseHeight/3,
	stairDepth = (baseDepth - baseMiddleDepth)/3,
	
	bodyInitialHeight = initialHeight + baseHeight,
	bodyHeight = baseHeight*(0.8/0.3),
	bodyWidth = baseWidth*(1.5/2.0),
	bodyDepth = bodyWidth,
	
	bodyUpperHeight = bodyHeight - baseHeight*(0.7/0.3),
	
	r1InitialHeight = bodyInitialHeight + bodyHeight + bodyUpperHeight,
	r1Height = baseHeight*(0.5/0.3),
	r1Width = baseHeight*(0.9/0.3),
	r1Depth = r1Width,
	
	r2InitialHeight = r1InitialHeight + r1Height,
	r2Height = r1Height - baseHeight*(0.15/0.3),
	r2Width = r1Width - baseHeight*(0.475/0.3),
	r2Depth = r2Width,
	
	r3InitialHeight = r2InitialHeight + r2Height,
	r3Height = baseHeight*(0.2/0.3),
	r3Width = r2Width + baseHeight*(0.175/0.3),
	
	sideStairHeight = baseHeight,
	sideStairInitialWidth = baseWidth,
	sideStairWidth = baseHeight*(0.3/0.3),
	sideStairDepth = baseHeight*(0.8/0.3),
	sStairDepth = sideStairDepth + (2*stairDepth);
}

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
		
		image = loadBMP("bodySide.bmp");
		_bodySide = loadTexture(image);
		delete image;
		
		image = loadBMP("bodyUpper.bmp");
		_bodyUpper = loadTexture(image);
		delete image;
		
		image = loadBMP("roof.bmp");
		_roof = loadTexture(image);
		delete image;
		
		image = loadBMP("bodyUpperSide.bmp");
		_bodyUpperSide = loadTexture(image);
		delete image;
		
		image = loadBMP("wallBuffer.bmp");
		_wall = loadTexture(image);
		delete image;
		
		image = loadBMP("backBodySide.bmp");
		_backSide = loadTexture(image);
		delete image;
		
		image = loadBMP("backBackSide.bmp");
		_back = loadTexture(image);
		delete image;
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); 
	glEnable(GL_LIGHT1); 
	glEnable(GL_NORMALIZE); 
	glShadeModel(GL_SMOOTH);
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 13: //Enter
			printf("DONE"); exit(0); break;
			
		case 105: //I
			angleX -= 2.0f;
			if (angleX > 360) {
				angleX -= 360;
			}
			
			glutPostRedisplay(); 
			break;
			
		case 106: //J
			angleY -= 2.0f;
			if (angleY < -360) {
				angleY += 360;
			}
			
			glutPostRedisplay(); 
			break;	
			
		case 107: //K
			angleX += 2.0f;
			if (angleX < -360) {
				angleX += 360;
			}
			
			glutPostRedisplay(); 
			break;
			
		case 108: //L
			angleY += 2.0f;
			if (angleY > 360) {
				angleY -= 360;
			}
			
			glutPostRedisplay(); 
			break;
			
		case 97: //A
			xAxis -= 0.2;
			xCenter -= 0.2;
			
			glutPostRedisplay(); 
			break;	
	
		case 100: //D
			xAxis += 0.2;
			xCenter += 0.2;
			
			glutPostRedisplay(); 
			break;
			
		case 120: //X
			if(yAxis > -0.3) {
				yAxis -= 0.2;
				yCenter -= 0.2;
			}
			
			glutPostRedisplay(); 
			break;	
	
		case 122: //Z
			if(yAxis > -2.0) {
				yAxis += 0.2;
				yCenter += 0.2;
			}
			
			
			glutPostRedisplay(); 
			break;	
			
		case 119: //W
		
			if(zAxis > 0.0) {
				zAxis -= 0.2f;
			}
			else 
			{
				zCenter -= 0.3;
				zAxis -= 0.2;
			}
			
			glutPostRedisplay(); 
			break;
			
		case 115: //S
			
			if(zAxis <= 30.0) {
				zAxis += 0.2f;
			}
			
			glutPostRedisplay(); 
			break;
			
		case 102: //F
			
			xCenter -= 0.2;
			
			glutPostRedisplay(); 
			break;
			
		case 104: //H
			
			xCenter += 0.2;
			
			glutPostRedisplay(); 
			break;
			
		case 116: //T
			
			yCenter += 0.2;
			
			glutPostRedisplay(); 
			break;
			
		case 103: //G
			
			yCenter -= 0.2;
			
			glutPostRedisplay(); 
			break;		
			
				
	}
	
	//printf("Ini x Axis: %f\nIni z Axis: %f\n\n", xAxis, zAxis);
}

void drawBase() {

	glColor3f(1.0f, 1.0f, 1.0f);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _sideBase);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	
	glBegin(GL_QUADS);
	
	
	/* -------------------- This is Left-Front Face of Base -------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseWidth,initialHeight, baseDepth);						//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-baseMiddleWidth, initialHeight, baseDepth); 				//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-baseMiddleWidth, initialHeight+baseHeight, baseDepth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseWidth, initialHeight+baseHeight, baseDepth); 			//left- top-corner
	
	/* -------------------- This is Right-Front Face of Base -------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(baseMiddleWidth,initialHeight, baseDepth);					//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(baseWidth, initialHeight, baseDepth); 						//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(baseWidth, initialHeight+baseHeight, baseDepth); 			//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(baseMiddleWidth, initialHeight+baseHeight, baseDepth); 		//left- top-corner
	
	/* ------------------------ This is Left Face of Base ----------------------- */
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseWidth,initialHeight, baseDepth);				//left-bottom-corner
	glTexCoord2f(2.5f, 0.0f);
	glVertex3f(-baseWidth, initialHeight, -baseDepth); 				//right-bottom-corner
	glTexCoord2f(2.5f, 1.0f);
	glVertex3f(-baseWidth, initialHeight+baseHeight, -baseDepth); 	//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseWidth, initialHeight+baseHeight, baseDepth); 	//left- top-corner
	
	/* ------------------------ This is Right Face of Base ----------------------- */
	
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(baseWidth,initialHeight, baseDepth);					//left-bottom-corner
	glTexCoord2f(2.5f, 0.0f);
	glVertex3f(baseWidth, initialHeight, -baseDepth); 				//right-bottom-corner
	glTexCoord2f(2.5f, 1.0f);
	glVertex3f(baseWidth, initialHeight+baseHeight, -baseDepth); 	//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(baseWidth, initialHeight+baseHeight, baseDepth); 	//left- top-corner
	
	/* ------------------------ This is Back Face of Base ----------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseWidth,initialHeight, -baseDepth);					//left-bottom-corner
	glTexCoord2f(2.5f, 0.0f);
	glVertex3f(baseWidth, initialHeight, -baseDepth); 					//right-bottom-corner
	glTexCoord2f(2.5f, 1.0f);
	glVertex3f(baseWidth, initialHeight+baseHeight, -baseDepth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseWidth, initialHeight+baseHeight, -baseDepth); 		//left- top-corner
	
	glEnd();
	
	
	glBindTexture(GL_TEXTURE_2D, _upperBase);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	/* ------------------------ This is Left-Upper Face of Base ----------------------- */	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 3.0f);
	glVertex3f(-baseWidth,initialHeight+baseHeight, baseDepth);					//left-bottom-corner
	glTexCoord2f(8.0f, 3.0f);
	glVertex3f(-baseWidth,initialHeight+baseHeight, -baseDepth);				//left-upper-corner
	glTexCoord2f(8.0f, 0.0f);
	glVertex3f(-baseMiddleWidth, initialHeight+baseHeight, -baseDepth); 		//right-top-corner
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseMiddleWidth, initialHeight+baseHeight, baseDepth); 			//right-bottom-corner
	
	/* ------------------------ This is Right-Upper Face of Base ----------------------- */	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 3.0f);
	glVertex3f(baseMiddleWidth,initialHeight+baseHeight, baseDepth);			//left-bottom-corner
	glTexCoord2f(8.0f, 3.0f);
	glVertex3f(baseMiddleWidth,initialHeight+baseHeight, -baseDepth);			//left-upper-corner
	glTexCoord2f(8.0f, 0.0f);
	glVertex3f(baseWidth, initialHeight+baseHeight, -baseDepth); 				//right-top-corner
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(baseWidth, initialHeight+baseHeight, baseDepth); 				//right-bottom-corner
	
	/* ------------------------ This is Middle-Upper Face of Base ----------------------- */
		
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(-baseMiddleWidth,initialHeight+baseHeight, baseMiddleDepth+stairDepth);			//left-bottom-corner
	glTexCoord2f(8.0f, 0.5f);
	glVertex3f(-baseMiddleWidth,initialHeight+baseHeight, -baseDepth);				//left-upper-corner
	glTexCoord2f(8.0f, 0.0f);
	glVertex3f(baseMiddleWidth, initialHeight+baseHeight, -baseDepth); 				//right-top-corner
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(baseMiddleWidth, initialHeight+baseHeight, baseMiddleDepth+stairDepth); 		//right-bottom-corner
	
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, _bottomBase);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	
	/* ------------------------ This is Bottom Face of Base ----------------------- */
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 8.0f);
	glVertex3f(-baseWidth,initialHeight, baseDepth);				//left-bottom-corner
	glTexCoord2f(8.0f, 8.0f);
	glVertex3f(-baseWidth,initialHeight, -baseDepth);			//left-upper-corner
	glTexCoord2f(8.0f, 0.0f);
	glVertex3f(baseWidth, initialHeight, -baseDepth); 			//right-top-corner
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(baseWidth, initialHeight, baseDepth); 			//right-bottom-corner

	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, _mSideBase);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	
	glBegin(GL_QUADS);
	/* ------------------------ This is Left-Middle Face of Base ----------------------- */
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseMiddleWidth,initialHeight, baseMiddleDepth);				//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-baseMiddleWidth, initialHeight, baseDepth); 					//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-baseMiddleWidth, initialHeight+baseHeight, baseDepth); 			//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseMiddleWidth, initialHeight+baseHeight, baseMiddleDepth); 	//left- top-corner
	
	/* ------------------------ This is Right-Middle Face of Base ----------------------- */
	
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(baseMiddleWidth,initialHeight, baseMiddleDepth);					//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(baseMiddleWidth, initialHeight, baseDepth); 						//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(baseMiddleWidth, initialHeight+baseHeight, baseDepth); 			//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(baseMiddleWidth, initialHeight+baseHeight, baseMiddleDepth); 	//left- top-corner
	
	glEnd();
	
	/* -------------------- This is Middle-Front Face of Base -------------------- */
	
	glBindTexture(GL_TEXTURE_2D, _stairSide);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	
	//glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseMiddleWidth,initialHeight, baseMiddleDepth);						//left-bottom-corner
	//glTexCoord2f(1.0f, 0.0f);
	glVertex3f(baseMiddleWidth, initialHeight, baseMiddleDepth); 						//right-bottom-corner
	//glTexCoord2f(1.0f, 1.0f);
	glVertex3f(baseMiddleWidth, initialHeight+baseHeight, baseMiddleDepth); 			//right-top-corner
	//glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseMiddleWidth, initialHeight+baseHeight, baseMiddleDepth); 			//left- top-corner
	
	/* -------------------- This is First Stair Middle-Front Face of Base -------------------- */
	
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseMiddleWidth,initialHeight, baseDepth);						//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(baseMiddleWidth, initialHeight, baseDepth); 						//right-bottom-corner
	glTexCoord2f(3.0f, 1.0f);
	glVertex3f(baseMiddleWidth, initialHeight+stairHeight, baseDepth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseMiddleWidth, initialHeight+stairHeight, baseDepth); 		//left- top-corner
	
	/* -------------------- This is Second Stair Middle-Front Face of Base -------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseMiddleWidth,initialHeight+stairHeight, baseDepth-stairDepth);		//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(baseMiddleWidth, initialHeight+stairHeight, baseDepth-stairDepth); 		//right-bottom-corner
	glTexCoord2f(3.0f, 1.0f);
	glVertex3f(baseMiddleWidth, initialHeight+(stairHeight*2), baseDepth-stairDepth); 	//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseMiddleWidth, initialHeight+(stairHeight*2), baseDepth-stairDepth); 	//left- top-corner
	
	/* -------------------- This is Third Stair Middle-Front Face of Base -------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseMiddleWidth,initialHeight+(stairHeight*2), baseMiddleDepth+stairDepth);		//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(baseMiddleWidth, initialHeight+(stairHeight*2), baseMiddleDepth+stairDepth); 		//right-bottom-corner
	glTexCoord2f(3.0f, 1.0f);
	glVertex3f(baseMiddleWidth, initialHeight+baseHeight, baseMiddleDepth+stairDepth); 			//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseMiddleWidth, initialHeight+baseHeight, baseMiddleDepth+stairDepth); 		//left- top-corner
	
	/* -------------------- This is First Stair Middle-Upper Face of Base -------------------- */
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseMiddleWidth,initialHeight+stairHeight, baseDepth);				//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-baseMiddleWidth,initialHeight+stairHeight, baseDepth-stairDepth);	//left-upper-corner
	glTexCoord2f(1.0f, 3.0f);
	glVertex3f(baseMiddleWidth, initialHeight+stairHeight, baseDepth-stairDepth); 	//right-top-corner
	glTexCoord2f(0.0f, 3.0f);
	glVertex3f(baseMiddleWidth, initialHeight+stairHeight,baseDepth) ;				//right-bottom-corner
	
	/* -------------------- This is Second Stair Middle-Upper Face of Base -------------------- */
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseMiddleWidth,initialHeight+(stairHeight*2), baseDepth-stairDepth);		//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-baseMiddleWidth,initialHeight+(stairHeight*2), baseMiddleDepth+stairDepth);										//left-upper-corner
	glTexCoord2f(1.0f, 3.0f);
	glVertex3f(baseMiddleWidth, initialHeight+(stairHeight*2), baseMiddleDepth + stairDepth); 									//right-top-corner
	glTexCoord2f(0.0f, 3.0f);
	glVertex3f(baseMiddleWidth, initialHeight+(stairHeight*2), baseDepth-stairDepth);		//right-bottom-corner
	
	glEnd();

}

void drawBody() {
//	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _bodySide);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
		
	glBegin(GL_QUADS);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	
	/* ------------------------ This is Front Face of Body ----------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-bodyWidth,bodyInitialHeight, bodyDepth);					//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(bodyWidth, bodyInitialHeight, bodyDepth); 					//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(bodyWidth, bodyInitialHeight+bodyHeight, bodyDepth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-bodyWidth, bodyInitialHeight+bodyHeight, bodyDepth); 		//left- top-corner
	
	/* ------------------------ This is Back Face of Body ----------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-bodyWidth,bodyInitialHeight, -bodyDepth);					//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(bodyWidth, bodyInitialHeight, -bodyDepth); 					//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(bodyWidth, bodyInitialHeight+bodyHeight, -bodyDepth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-bodyWidth, bodyInitialHeight+bodyHeight, -bodyDepth); 		//left- top-corner
	
	/* ------------------------ This is Left Face of Body ----------------------- */
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-bodyWidth,bodyInitialHeight, -bodyDepth);					//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-bodyWidth, bodyInitialHeight, bodyDepth); 					//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-bodyWidth, bodyInitialHeight+bodyHeight, bodyDepth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-bodyWidth, bodyInitialHeight+bodyHeight, -bodyDepth); 		//left- top-corner
	
	/* ------------------------ This is Right Face of Body ----------------------- */
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(bodyWidth,bodyInitialHeight, -bodyDepth);					//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(bodyWidth, bodyInitialHeight, bodyDepth); 					//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(bodyWidth, bodyInitialHeight+bodyHeight, bodyDepth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(bodyWidth, bodyInitialHeight+bodyHeight, -bodyDepth); 		//left- top-corner
	
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, _bodyUpper);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	
	/* ------------------------ This is Upper Face of Body ----------------------- */
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.3f,0.3f,0.3f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseWidth, bodyInitialHeight+bodyHeight, baseDepth); 					//left-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-baseWidth, bodyInitialHeight+bodyHeight, -baseDepth); 					//left-top-corner
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(baseWidth, bodyInitialHeight+bodyHeight, -baseDepth);					//right- top-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(baseWidth, bodyInitialHeight+bodyHeight, baseDepth); 					//right-bottoms-corner
			
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, _bodyUpperSide);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	
	/* ------------------------ This is Left Face of UpperBody ----------------------- */
	
	glColor3f(0.5f,0.5f,0.5f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseWidth,bodyInitialHeight+bodyHeight, baseDepth);				//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-baseWidth, bodyInitialHeight+bodyHeight, -baseDepth); 				//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-baseWidth, bodyInitialHeight+bodyHeight+bodyUpperHeight, -baseDepth); 	//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseWidth, bodyInitialHeight+bodyHeight+bodyUpperHeight, baseDepth); 	//left- top-corner
	
	/* ------------------------ This is Right Face of UpperBody ----------------------- */
	
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(baseWidth,bodyInitialHeight+bodyHeight, baseDepth);					//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(baseWidth, bodyInitialHeight+bodyHeight, -baseDepth); 				//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(baseWidth, bodyInitialHeight+bodyHeight+bodyUpperHeight, -baseDepth); 	//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(baseWidth, bodyInitialHeight+bodyHeight+bodyUpperHeight, baseDepth); 	//left- top-corner
	
	/* ------------------------ This is Back Face of UpperBody ----------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseWidth,bodyInitialHeight+bodyHeight, -baseDepth);					//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(baseWidth, bodyInitialHeight+bodyHeight, -baseDepth); 					//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(baseWidth, bodyInitialHeight+bodyHeight+bodyUpperHeight, -baseDepth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseWidth, bodyInitialHeight+bodyHeight+bodyUpperHeight, -baseDepth); 		//left- top-corner
	
	/* ------------------------ This is Front Face of UpperBody ----------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseWidth,bodyInitialHeight+bodyHeight, baseDepth);					//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(baseWidth, bodyInitialHeight+bodyHeight, baseDepth); 					//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(baseWidth, bodyInitialHeight+bodyHeight+bodyUpperHeight, baseDepth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseWidth, bodyInitialHeight+bodyHeight+bodyUpperHeight, baseDepth); 		//left- top-corner
	
	glEnd();
}

void drawRoof(float initial, float height, float width, float depth, float base){
	
	glBindTexture(GL_TEXTURE_2D, _roof);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	
	glColor3f(1.0f, 0.6f, 0.6f);
	
	/* ------------------------ This is Front Face of Roof ----------------------- */
	
	glNormal3f(0.0f, 0.0f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-base,initial, base);		//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(base, initial, base); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, height, depth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, height, depth); 		//left- top-corner
	
	/* ------------------------ This is Back Face of Roof ----------------------- */
	
	glNormal3f(0.0f, 0.0f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-base,initial, -base);		//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(base, initial, -base); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, height, -depth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, height, -depth); 	//left- top-corner
	
	/* ------------------------ This is Right Face of Roof ----------------------- */
	
	glNormal3f(0.5f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(base,initial, -base);		//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(base, initial, base); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, height, depth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(width, height, -depth); 		//left- top-corner
	
	
	/* ------------------------ This is Left Face of Roof ----------------------- */
	
	glNormal3f(0.5f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-base,initial, -base);		//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(-base, initial, base); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-width, height, depth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, height, -depth); 	//left- top-corner
	
	glEnd();
}

void drawRoof2(){	
	
	glBindTexture(GL_TEXTURE_2D, _roof);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	
	glColor3f(1.0f, 0.6f, 0.6f);
		
	//Front
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-r2Width, r3InitialHeight, r2Depth);			//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(r2Width, r3InitialHeight, r2Depth); 			//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(r3Width, r3InitialHeight + r3Height, 0.0f); 	//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-r3Width, r3InitialHeight + r3Height, 0.0f); //left-kkk top-corner
	
	//Back
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-r2Width, r3InitialHeight, -r2Depth);		//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(r2Width, r3InitialHeight, -r2Depth); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(r3Width, r3InitialHeight + r3Height, 0.0f); 	//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-r3Width, r3InitialHeight + r3Height, 0.0f); //left-kkk top-corner
	
	glEnd();
	
	glBegin(GL_TRIANGLES);
	
	glColor3f(0.8f, 0.8f, 0.8f);
	glVertex3f(r2Width, r3InitialHeight, r2Depth);			//left-bottom-corner
	glVertex3f(r2Width, r3InitialHeight, -r2Depth); 		//right-bottom-corner
	glVertex3f(r3Width, r3InitialHeight + r3Height, 0.0f); 	//right-top-corner
	
	glColor3f(0.8f, 0.8f, 0.8f);
	glVertex3f(-r2Width, r3InitialHeight, r2Depth);			//left-bottom-corner
	glVertex3f(-r2Width, r3InitialHeight, -r2Depth); 		//right-bottom-corner
	glVertex3f(-r3Width, r3InitialHeight + r3Height, 0.0f); //right-top-corner
	
	glEnd();
}

void drawSideStair(float xdir, float zdir) {
	glBindTexture(GL_TEXTURE_2D, _stairSide);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	
	/* -------------------- This is First Stair Middle-Front Face of Base -------------------- */
	
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xdir*sideStairInitialWidth,initialHeight, zdir*sStairDepth);										//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight, zdir*sStairDepth); 					//right-bottom-corner
	glTexCoord2f(3.0f, 1.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight+stairHeight, zdir*sStairDepth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xdir*sideStairInitialWidth, initialHeight+stairHeight, zdir*sStairDepth); 						//left- top-corner
	
	/* -------------------- This is Second Stair Middle-Front Face of Base -------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xdir*sideStairInitialWidth,initialHeight+stairHeight, zdir*(sideStairDepth+stairDepth));						//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight+stairHeight, zdir*(sideStairDepth+stairDepth)); 		//right-bottom-corner
	glTexCoord2f(3.0f, 1.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight+(stairHeight*2), zdir*(sideStairDepth+stairDepth)); 	//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xdir*sideStairInitialWidth, initialHeight+(stairHeight*2), zdir*(sideStairDepth+stairDepth)); 				//left- top-corner
	
	/* -------------------- This is Third Stair Middle-Front Face of Base -------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xdir*sideStairInitialWidth,initialHeight+(stairHeight*2), zdir*sideStairDepth);					//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight+(stairHeight*2), zdir*sideStairDepth); 	//right-bottom-corner
	glTexCoord2f(3.0f, 1.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight+baseHeight, zdir*sideStairDepth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xdir*sideStairInitialWidth, initialHeight+baseHeight, zdir*sideStairDepth); 						//left- top-corner
	
	/* -------------------- This is First Stair Middle-Upper Face of Base -------------------- */
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xdir*(sideStairInitialWidth),initialHeight+stairHeight, zdir*sStairDepth);				//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xdir*(sideStairInitialWidth),initialHeight+stairHeight, zdir*(sStairDepth-stairDepth));	//left-upper-corner
	glTexCoord2f(1.0f, 3.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight+stairHeight, zdir*(sStairDepth-stairDepth)); 	//right-top-corner
	glTexCoord2f(0.0f, 3.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight+stairHeight, zdir*sStairDepth) ;				//right-bottom-corner
	
	/* -------------------- This is Second Stair Middle-Upper Face of Base -------------------- */
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xdir*(sideStairInitialWidth),initialHeight+(stairHeight*2), zdir*(sStairDepth-stairDepth));					//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xdir*(sideStairInitialWidth),initialHeight+(stairHeight*2), zdir*(sStairDepth-(2*stairDepth)));				//left-upper-corner
	glTexCoord2f(1.0f, 3.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight+(stairHeight*2), zdir*(sStairDepth-(2*stairDepth))); //right-top-corner
	glTexCoord2f(0.0f, 3.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight+(stairHeight*2), zdir*(sStairDepth-stairDepth));	//right-bottom-corner
	
	glEnd();
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _sideBase);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	
	glBegin(GL_QUADS);
	
	/* ------------------------ This is Second Right Face of Base ----------------------- */
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth),initialHeight, zdir*(sideStairDepth+stairDepth));						//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight, zdir*sideStairDepth); 								//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight+(2*stairHeight), zdir*sideStairDepth); 				//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight+(2*stairHeight), zdir*(sideStairDepth+stairDepth)); 	//left- top-corner
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth),initialHeight, zdir*sStairDepth);							//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight, zdir*(sStairDepth-stairDepth)); 				//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight+stairHeight, zdir*(sStairDepth-stairDepth)); 	//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight+stairHeight, zdir*sStairDepth); 				//left- top-corner
	
	glEnd();
}

void drawStair(float xdir) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _sideBase);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	
	glBegin(GL_QUADS);
	
	/* ------------------------ This is Right Face of Base ----------------------- */
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth),initialHeight, sideStairDepth);						//left-bottom-corner
	glTexCoord2f(2.5f, 0.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight, -sideStairDepth); 					//right-bottom-corner
	glTexCoord2f(2.5f, 1.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight+sideStairHeight, -sideStairDepth); 	//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight+sideStairHeight, sideStairDepth); 	//left- top-corner
	
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, _upperBase);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);


	
	/* ------------------------ This is Right-Upper Face of Base ----------------------- */	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xdir*(sideStairInitialWidth),initialHeight+sideStairHeight, sideStairDepth);					//left-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(xdir*(sideStairInitialWidth),initialHeight+sideStairHeight, -sideStairDepth);					//left-upper-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight+sideStairHeight, -sideStairDepth); 	//right-top-corner
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight+sideStairHeight, sideStairDepth); 	//right-bottom-corner
	
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, _bottomBase);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	
	/* ------------------------ This is Right-Bottom Face of Base ----------------------- */	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xdir*(sideStairInitialWidth),initialHeight, sStairDepth);						//left-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(xdir*(sideStairInitialWidth),initialHeight, -sStairDepth);					//left-upper-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight, -sStairDepth); 	//right-top-corner
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xdir*(sideStairInitialWidth+sideStairWidth), initialHeight, sStairDepth); 	//right-bottom-corner
	
	glEnd();
	
	drawSideStair(xdir,1.0);
	
	drawSideStair(xdir,-1.0);
	
	
}

void drawBuffer (float initial,float height, float width, float depth) {
	glBindTexture(GL_TEXTURE_2D, _wall);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
	glBegin(GL_QUADS);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	
	/* ------------------------ This is Front Face of Roof ----------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-width,initial, depth);		//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(width, initial, depth); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, height, depth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, height, depth); 		//left- top-corner
	
	/* ------------------------ This is Back Face of Roof ----------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-width,initial, -depth);		//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(width, initial, -depth); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, height, -depth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, height, -depth); 	//left- top-corner
	
	/* ------------------------ This is Right Face of Roof ----------------------- */
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(width,initial, -depth);		//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(width, initial, depth); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, height, depth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(width, height, -depth); 		//left- top-corner
	
	
	/* ------------------------ This is Left Face of Roof ----------------------- */
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-width,initial, -depth);		//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(-width, initial, depth); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-width, height, depth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, height, -depth); 	//left- top-corner
	
	/* ------------------------ This is Bottom Face of Roof ----------------------- */
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-width,initial, -depth);			//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(width, initial, -depth); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, initial, depth); 			//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, initial, depth); 		//left- top-corner
	
	/* ------------------------ This is Upper Face of Roof ----------------------- */
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-width,height, -depth);			//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(width, height, -depth); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, height, depth); 			//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, height, depth); 		//left- top-corner
	
	glEnd();
}

void drawBuffers () {
	/* ------- Front Left ------*/
	
	glPushMatrix();
	glTranslatef(baseHeight*-(0.8/0.3),0.0,baseHeight*(2.7/0.3));
	drawBuffer(initialHeight, initialHeight+baseHeight+bodyHeight-(baseHeight*(0.1/0.3)), baseHeight*(0.025/0.3), baseHeight*(0.025/0.3));
	glPopMatrix();
	
	/* ------- Back Left 1------*/
	
	glPushMatrix();
	glTranslatef(baseHeight*-(0.8/0.3),0.0,baseHeight*(1.9/0.3));
	drawBuffer(bodyInitialHeight, bodyInitialHeight+bodyHeight-(baseHeight*(0.1/0.3)), baseHeight*(0.025/0.3), baseHeight*(0.025/0.3));
	glPopMatrix();
	
	/* ------- Front Right ------*/
	
	glPushMatrix();
	glTranslatef(baseHeight*(0.8/0.3),0.0,baseHeight*(2.7/0.3));
	drawBuffer(initialHeight, initialHeight+baseHeight+bodyHeight-(baseHeight*(0.1/0.3)), baseHeight*(0.025/0.3), baseHeight*(0.025/0.3));
	glPopMatrix();
	
	/* ------- Back Right 1 ------*/
	
	
	glPushMatrix();
	glTranslatef(baseHeight*(0.8/0.3),0.0,baseHeight*(1.9/0.3));
	drawBuffer(bodyInitialHeight, bodyInitialHeight+bodyHeight-(baseHeight*(0.1/0.3)), baseHeight*(0.025/0.3), baseHeight*(0.025/0.3));
	glPopMatrix();
	
	/* ------- Back Right 2 ------*/
	
	glPushMatrix();
	glTranslatef(baseHeight*(0.5/0.3),0.0,baseHeight*(1.9/0.3));
	drawBuffer(bodyInitialHeight, bodyInitialHeight+bodyHeight-(baseHeight*(0.20/0.3)), baseHeight*(0.025/0.3), baseHeight*(0.025/0.3));
	glPopMatrix();
	
	/* ------- Back Left 2 ------*/
	
	glPushMatrix();
	glTranslatef(baseHeight*-(0.5/0.3),0.0,baseHeight*(1.9/0.3));
	drawBuffer(bodyInitialHeight, bodyInitialHeight+bodyHeight-(baseHeight*(0.20/0.3)), baseHeight*(0.025/0.3), baseHeight*(0.025/0.3));
	glPopMatrix();
	
	/* ------- Middle Left  ------*/
	
	glPushMatrix();
	glTranslatef(baseHeight*-(0.5/0.3),0.0,baseHeight*(2.25/0.3));
	drawBuffer(initialHeight, initialHeight+baseHeight+bodyHeight-(baseHeight*(0.20/0.3)),baseHeight*(0.025/0.3), baseHeight*(0.025/0.3));
	glPopMatrix();
	
	/* ------- Middle Right  ------*/
	
	glPushMatrix();
	glTranslatef(baseHeight*(0.5/0.3),0.0,baseHeight*(2.25/0.3));
	drawBuffer(initialHeight, initialHeight+baseHeight+bodyHeight-(baseHeight*(0.20/0.3)), baseHeight*(0.025/0.3), baseHeight*(0.025/0.3));
	glPopMatrix();
	
	/* ------- Upper  ------*/
	
	glPushMatrix();
	glTranslatef(0.0,0.0,baseHeight*(2.31/0.3));
	drawBuffer(initialHeight+baseHeight+bodyHeight-(baseHeight*(0.20/0.3)), initialHeight+baseHeight+bodyHeight-(baseHeight*(0.1/0.3)), baseHeight*(0.7/0.3), baseHeight*(0.45/0.3));
	glPopMatrix();
	
	/* ------- Upper Left ------*/
	
	glPushMatrix();
	glTranslatef(baseHeight*-(0.74/0.3),0.0,baseHeight*(2.68/0.3));
	drawBuffer(initialHeight+baseHeight+bodyHeight-(baseHeight*(0.20/0.3)), initialHeight+baseHeight+bodyHeight-(baseHeight*(0.1/0.3)), baseHeight*(0.04/0.3), baseHeight*(0.09/0.3));
	glPopMatrix();
	
	/* ------- Upper Back Left ------*/
	
	glPushMatrix();
	glTranslatef(baseHeight*-(0.74/0.3),0.0,baseHeight*(1.95/0.3));
	drawBuffer(initialHeight+baseHeight+bodyHeight-(baseHeight*(0.20/0.3)), initialHeight+baseHeight+bodyHeight-(baseHeight*(0.1/0.3)), baseHeight*(0.04/0.3), baseHeight*(0.09/0.3));
	glPopMatrix();
	
	/* ------- Upper Left ------*/
	
	glPushMatrix();
	glTranslatef(baseHeight*(0.74/0.3),0.0,baseHeight*(2.68/0.3));
	drawBuffer(initialHeight+baseHeight+bodyHeight-(baseHeight*(0.20/0.3)), initialHeight+baseHeight+bodyHeight-(baseHeight*(0.1/0.3)), baseHeight*(0.04/0.3), baseHeight*(0.09/0.3));
	glPopMatrix();
	
	/* ------- Upper Back Left ------*/
	
	glPushMatrix();
	glTranslatef(baseHeight*(0.74/0.3),0.0,baseHeight*(1.95/0.3));
	drawBuffer(initialHeight+baseHeight+bodyHeight-(baseHeight*(0.20/0.3)), initialHeight+baseHeight+bodyHeight-(baseHeight*(0.1/0.3)), baseHeight*(0.04/0.3), baseHeight*(0.09/0.3));
	glPopMatrix();
}

void drawUpperBack() {
	glBindTexture(GL_TEXTURE_2D, _bodyUpper);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	
	/* ------------------------ This is Upper Face of Body ----------------------- */
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.3f,0.3f,0.3f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseHeight*(1.1/0.3), bodyInitialHeight+bodyHeight, baseHeight*(0.8/0.3)); 					//left-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-baseHeight*(1.1/0.3), bodyInitialHeight+bodyHeight, -baseHeight*(0.8/0.3)); 					//left-top-corner
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(baseHeight*(1.1/0.3), bodyInitialHeight+bodyHeight, -baseHeight*(0.8/0.3));					//right- top-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(baseHeight*(1.1/0.3), bodyInitialHeight+bodyHeight, baseHeight*(0.8/0.3)); 					//right-bottoms-corner
			
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, _bodyUpperSide);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	glColor3f(1.0f,1.0f,1.0f);
	/* ------------------------ This is Left Face of UpperBody ----------------------- */
	
	glColor3f(0.5f,0.5f,0.5f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseHeight*(1.1/0.3),bodyInitialHeight+bodyHeight, baseHeight*(0.8/0.3));				//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-baseHeight*(1.1/0.3), bodyInitialHeight+bodyHeight, -baseHeight*(0.8/0.3)); 				//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-baseHeight*(1.1/0.3), bodyInitialHeight+bodyHeight+bodyUpperHeight, -baseHeight*(0.8/0.3)); 	//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseHeight*(1.1/0.3), bodyInitialHeight+bodyHeight+bodyUpperHeight, baseHeight*(0.8/0.3)); 	//left- top-corner
	
	/* ------------------------ This is Right Face of UpperBody ----------------------- */
	
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(baseHeight*(1.1/0.3),bodyInitialHeight+bodyHeight, baseHeight*(0.8/0.3));					//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(baseHeight*(1.1/0.3), bodyInitialHeight+bodyHeight, -baseHeight*(0.8/0.3)); 				//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(baseHeight*(1.1/0.3), bodyInitialHeight+bodyHeight+bodyUpperHeight, -baseHeight*(0.8/0.3)); 	//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(baseHeight*(1.1/0.3), bodyInitialHeight+bodyHeight+bodyUpperHeight, baseHeight*(0.8/0.3)); 	//left- top-corner
	
	/* ------------------------ This is Back Face of UpperBody ----------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseHeight*(1.1/0.3),bodyInitialHeight+bodyHeight, -baseHeight*(0.8/0.3));					//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(baseHeight*(1.1/0.3), bodyInitialHeight+bodyHeight, -baseHeight*(0.8/0.3)); 					//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(baseHeight*(1.1/0.3), bodyInitialHeight+bodyHeight+bodyUpperHeight, -baseHeight*(0.8/0.3)); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseHeight*(1.1/0.3), bodyInitialHeight+bodyHeight+bodyUpperHeight, -baseHeight*(0.8/0.3)); 		//left- top-corner
	
	glEnd();
}

void drawBaseBack() {
	glColor3f(1.0f, 1.0f, 1.0f);
	
	
	glBindTexture(GL_TEXTURE_2D, _upperBase);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);	
	/* ------------------------ This is Middle-Upper Face of Base ----------------------- */
		
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 3.0f);
	glVertex3f(-baseHeight*(1.2/0.3),initialHeight+baseHeight,baseHeight*(0.35/0.3));			//left-bottom-corner
	glTexCoord2f(8.0f, 3.0f);
	glVertex3f(-baseHeight*(1.2/0.3),initialHeight+baseHeight, -baseHeight*(0.35/0.3));				//left-upper-corner
	glTexCoord2f(8.0f, 0.0f);
	glVertex3f(baseHeight*(1.2/0.3), initialHeight+baseHeight, -baseHeight*(0.35/0.3)); 				//right-top-corner
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(baseHeight*(1.2/0.3), initialHeight+baseHeight, baseHeight*(0.35/0.3)); 		//right-bottom-corner
	
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, _sideBase);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	
	glBegin(GL_QUADS);
	
	
	/* -------------------- This is Front Face of Base -------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseHeight*(1.2/0.3),initialHeight, baseHeight*(0.35/0.3));						//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-baseHeight*(1.2/0.3), initialHeight, baseHeight*(0.35/0.3)); 				//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-baseHeight*(1.2/0.3), initialHeight+baseHeight, baseHeight*(0.35/0.3)); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseHeight*(1.2/0.3), initialHeight+baseHeight, baseHeight*(0.35/0.3)); 			//left- top-corner
	
	/* ------------------------ This is Left Face of Base ----------------------- */
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseHeight*(1.2/0.3),initialHeight, baseHeight*(0.35/0.3));				//left-bottom-corner
	glTexCoord2f(2.5f, 0.0f);
	glVertex3f(-baseHeight*(1.2/0.3), initialHeight, -baseHeight*(0.35/0.3)); 				//right-bottom-corner
	glTexCoord2f(2.5f, 1.0f);
	glVertex3f(-baseHeight*(1.2/0.3), initialHeight+baseHeight, -baseHeight*(0.35/0.3)); 	//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseHeight*(1.2/0.3), initialHeight+baseHeight, baseHeight*(0.35/0.3)); 	//left- top-corner
	
	/* ------------------------ This is Right Face of Base ----------------------- */
	
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(baseHeight*(1.2/0.3),initialHeight, baseHeight*(0.35/0.3));					//left-bottom-corner
	glTexCoord2f(2.5f, 0.0f);
	glVertex3f(baseHeight*(1.2/0.3), initialHeight, -baseHeight*(0.35/0.3)); 				//right-bottom-corner
	glTexCoord2f(2.5f, 1.0f);
	glVertex3f(baseHeight*(1.2/0.3), initialHeight+baseHeight, -baseHeight*(0.35/0.3)); 	//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(baseHeight*(1.2/0.3), initialHeight+baseHeight, baseHeight*(0.35/0.3)); 	//left- top-corner
	
	/* ------------------------ This is Back Face of Base ----------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-baseHeight*(1.2/0.3),initialHeight, -baseHeight*(0.35/0.3));					//left-bottom-corner
	glTexCoord2f(2.5f, 0.0f);
	glVertex3f(baseHeight*(1.2/0.3), initialHeight, -baseHeight*(0.35/0.3)); 					//right-bottom-corner
	glTexCoord2f(2.5f, 1.0f);
	glVertex3f(baseHeight*(1.2/0.3), initialHeight+baseHeight, -baseHeight*(0.35/0.3)); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-baseHeight*(1.2/0.3), initialHeight+baseHeight, -baseHeight*(0.35/0.3)); 		//left- top-corner
	
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, _bottomBase);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	
	/* ------------------------ This is Bottom Face of Base ----------------------- */
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 8.0f);
	glVertex3f(-baseHeight*(1.2/0.3),initialHeight, baseHeight*(0.35/0.3));				//left-bottom-corner
	glTexCoord2f(8.0f, 8.0f);
	glVertex3f(-baseHeight*(1.2/0.3),initialHeight, -baseHeight*(0.35/0.3));			//left-upper-corner
	glTexCoord2f(8.0f, 0.0f);
	glVertex3f(baseHeight*(1.2/0.3), initialHeight, -baseHeight*(0.35/0.3)); 			//right-top-corner
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(baseHeight*(1.2/0.3), initialHeight, baseHeight*(0.35/0.3)); 			//right-bottom-corner

	glEnd();

}

void drawBodyBack(float initial,float height, float width, float depth) {
	glBindTexture(GL_TEXTURE_2D, _backSide);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
	glBegin(GL_QUADS);	
	
	/* ------------------------ This is Right Face of Roof ----------------------- */
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(width,initial, -depth);		//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(width, initial, depth); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, height, depth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(width, height, -depth); 		//left- top-corner
	
	
	/* ------------------------ This is Left Face of Roof ----------------------- */
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-width,initial, -depth);		//left-bottom-corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-width, initial, depth); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-width, height, depth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, height, -depth); 	//left- top-corner
	
	glEnd();glBindTexture(GL_TEXTURE_2D, _back);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
	glBegin(GL_QUADS);
	
	/* ------------------------ This is Bottom Face of Roof ----------------------- */
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-width,initial, -depth);			//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(width, initial, -depth); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, initial, depth); 			//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, initial, depth); 		//left- top-corner
	
	/* ------------------------ This is Upper Face of Roof ----------------------- */
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-width,height, -depth);			//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(width, height, -depth); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, height, depth); 			//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, height, depth); 		//left- top-corner
	
	/* ------------------------ This is Front Face of Roof ----------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-width,initial, depth);		//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(width, initial, depth); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, height, depth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, height, depth); 		//left- top-corner
	
	/* ------------------------ This is Back Face of Roof ----------------------- */
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-width,initial, -depth);		//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(width, initial, -depth); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, height, -depth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, height, -depth); 	//left- top-corner
	
	glEnd();
}

void drawRoofBack(float initial, float height, float width, float depth, float base){
	
	glBindTexture(GL_TEXTURE_2D, _roof);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	
	glColor3f(1.0f, 0.6f, 0.6f);
	
	/* ------------------------ This is Front Face of Roof ----------------------- */
	
	glNormal3f(0.0f, 0.0f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-base,initial, depth);		//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(base, initial, depth); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, height, depth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, height, depth); 		//left- top-corner
	
	/* ------------------------ This is Back Face of Roof ----------------------- */
	
	glNormal3f(0.0f, 0.0f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-base,initial, -depth);		//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(base, initial, -depth); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, height, -depth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, height, -depth); 	//left- top-corner
	
	/* ------------------------ This is Right Face of Roof ----------------------- */
	
	glNormal3f(0.5f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(base,initial, -depth);		//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(base, initial, depth); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, height, depth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(width, height, -depth); 		//left- top-corner
	
	
	/* ------------------------ This is Left Face of Roof ----------------------- */
	
	glNormal3f(0.5f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-base,initial, -depth);		//left-bottom-corner
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(-base, initial, depth); 		//right-bottom-corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-width, height, depth); 		//right-top-corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-width, height, -depth); 	//left- top-corner
	
	glEnd();
}

void drawBack() {
	/* ------- Back ------*/
	
	glPushMatrix();
	glTranslatef(0.0,0.0,baseHeight*-(2.0/0.3));
	drawBodyBack(bodyInitialHeight, bodyInitialHeight+bodyHeight, baseHeight*(0.9/0.3), baseHeight*(0.5/0.3));
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0,0.0,baseHeight*-(2.0/0.3));
	drawUpperBack();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0,0.0,baseHeight*-(2.3/0.3));
	drawBaseBack();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0,0.0,baseHeight*-(2.0/0.3));
	drawRoofBack(r1InitialHeight,r1InitialHeight + r1Height,baseHeight*(0.0/0.3),baseHeight*(0.85/0.3),baseHeight*(1.2/0.3));
	glPopMatrix();
	
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(xAxis,yAxis,zAxis,xCenter,yCenter,zCenter,0,1,0);
	
	glRotatef(angleX, 1.0f, 0.0f, 0.0f);
	glRotatef(angleY, 0.0f, 1.0f, 0.0f);
	
	GLfloat ambientColor[] = {0.6f, 0.6f, 0.6f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	GLfloat lightColor0[] = {0.8f, 0.8f, 0.8f, 1.0f}; 
	GLfloat lightPos0[] = {4.0f, 20.0f, 8.0f, 1.0f}; 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; 
	
	GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	
	drawBase();
	drawBody();
	drawRoof(r1InitialHeight,r1InitialHeight + r1Height,r1Width,r1Depth,baseDepth+0.1f);
	drawRoof(r2InitialHeight,r2InitialHeight + r2Height,r2Width,r2Depth,r1Width+0.1f);	
	drawRoof2();
	drawStair(1.0);
	drawStair(-1.0);
	drawBuffers();
	drawBack();
	

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1080, 480);
	
	//Create the window
	glutCreateWindow("Pendopo Polban - Auliya Raka Pratama 151511008");
	initRendering();
	loadSize();
	getTexture();
	
	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutMainLoop();
	return 0;
}
