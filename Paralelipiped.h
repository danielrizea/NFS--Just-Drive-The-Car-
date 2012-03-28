#ifndef PARALELIPIPED_H
#define PARALELIPIPED_H

#include <glut.h>
#include "Object3D.h"
#include "Camera.h"

class Paralelipiped: public Object3D
{
public:

	Paralelipiped();

	// Constructor
	Paralelipiped(GLfloat , GLfloat, GLfloat);

	// Draw
	void Draw();

public:
	// Functie pentru a seta latura cubului
	void SetDimensiuni(GLfloat , GLfloat, GLfloat);
	// Seteaza culoare difuza ( atentie , la testul alfa se foloseste componenta A din culoarea difuza !!!_
	void SetDiffuse(Vector4D *color);
	// culoare difuza
	Vector4D diffuse;
	// culoare ambientala
	Vector4D ambient;
	// culoare speculara
	Vector4D specular;

	
private:
	
	

	
};


#endif
