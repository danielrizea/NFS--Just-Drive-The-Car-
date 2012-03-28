// EGC
// Laborator 7
//-------------------------------------------------

#ifndef CAMERA_H
#define CAMERA_H

#include <glut.h>		
#include "Vector3D.h"

/*
	Camera
	Clasa pentru initializarea si miscarea unui observator prin scena
*/

class Camera
{
	
// VARIABILE
//-------------------------------------------------
private:
	Vector3D ForwardVector;
	Vector3D RightVector;	
	Vector3D UpVector;
	Vector3D Position;


	// 0 - urmareste masina din spate
	// 1 - botul masinii
	// 2 - satelit urmareste masina de sus
	// 3 - free cam

	

// FUNCTII
//-------------------------------------------------
public:
	// constructor fara parametri
	Camera();				

	// plaseaza observatorul in scena
	void Render ( void );	

	// rotatie fata de axele de coordonate
	void RotateX ( GLfloat Angle );
	void RotateY ( GLfloat Angle );
	void RotateZ ( GLfloat Angle );

	// rotatie fata de un centru de rotatie
	void RotateXCenter ( GLfloat Angle );
	void RotateYCenter ( GLfloat Angle );
	void RotateZCenter ( GLfloat Angle );

	// miscare fata/spate
	void MoveForward ( GLfloat Distance );
	void MoveBackward ( GLfloat Distance );

	// miscare sus/jos
	void MoveUpward ( GLfloat Distance );
	void MoveDownward ( GLfloat Distance );

	// miscare stanga/dreapta
	void MoveRight ( GLfloat Distance );
	void MoveLeft ( GLfloat Distance );

	// pt diversele tipuri de camere posibile
	void UpdateCamera(Vector3D posMasina, Vector3D rotMasina);

public :
	int cameraType;
};

#endif
