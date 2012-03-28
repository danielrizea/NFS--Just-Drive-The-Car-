// EGC
// Laborator 7
//-------------------------------------------------

#include "camera.h"
#include "math.h"
#include "Vector3D.h"
#define PI 3.14159265

// constructor
Camera::Camera()
{
	//initializare cu valorile standard OpenGL

/*
	Position = Vector3D (0.0, 0.0, 12.0);
	ForwardVector = Vector3D( 0.0, 0.0, -1.0);
	RightVector = Vector3D (1.0, 0.0, 0.0);
	UpVector = Vector3D (0.0, 1.0, 0.0);
*/



	Position = Vector3D (0.0, 50, 0.0);
	ForwardVector = Vector3D( 0.0, -1.0, 0.0);
	RightVector = Vector3D (1.0, 0.0, 0.0);
	UpVector = Vector3D (0.0, 0.0, -1.0);

	// urmareste masina din spate
	cameraType = 0;


	}
void Camera::UpdateCamera(Vector3D posMasina, Vector3D rotMasina){


	Vector3D pos;

	Vector3D fwVector;
	Vector3D rVector;
	Vector3D uVector;

	float distFataMasina = -10;

	switch(cameraType) {

		case 0 :{

			//camera in spatele masinii
				distFataMasina = -10;

				pos = posMasina - Vector3D (distFataMasina * cos(rotMasina.y * PI / 180),posMasina.y,distFataMasina* -sin(rotMasina.y * PI/180));

	
				Position = pos;
				ForwardVector = Vector3D(-cos(rotMasina.y * PI / 180),0,sin(rotMasina.y * PI/180));
				
				RightVector = Vector3D( -cos((rotMasina.y* PI -90)/180),0,sin((rotMasina.y*PI-90)/180));
				UpVector=RightVector.CrossProduct(ForwardVector);
				

				}break;


		case 1 :{

			//camera pe capota masinii
			distFataMasina = -0.42;

				pos = posMasina - Vector3D (distFataMasina * cos(rotMasina.y * PI / 180),posMasina.y+1.5,distFataMasina* -sin(rotMasina.y * PI/180));

	
				Position = pos;
				ForwardVector = Vector3D(-cos(rotMasina.y * PI / 180),0,sin(rotMasina.y * PI/180));
				
				RightVector = Vector3D( -cos((rotMasina.y* PI -90)/180),0,sin((rotMasina.y*PI-90)/180));
				UpVector=RightVector.CrossProduct(ForwardVector);


				}break;

		case 2:{

				//camera satelit 


				distFataMasina = 0;

				pos = posMasina - Vector3D (distFataMasina * cos(rotMasina.y * PI / 180),-20,distFataMasina* -sin(rotMasina.y * PI/180));


				Position = pos;
				ForwardVector = Vector3D(0,-1,0);
				
				RightVector = Vector3D(-1,0,0);
				UpVector= Vector3D(0,0,1);


			   }break;

		case 3 : {
				
				// free cam

				 }break;

		case 4 : {
//developer cam, dezactivata , sare peste 4 
	
	Position = Vector3D (0.0, 50, 0.0);
	ForwardVector = Vector3D( 0.0, -1.0, 0.0);
	RightVector = Vector3D (1.0, 0.0, 0.0);
	UpVector = Vector3D (0.0, 0.0, -1.0);
				 }

	}

}

void Camera::RotateX (GLfloat Angle)
{

	Vector3D fwd;
	Vector3D up;

	fwd = ForwardVector * cos(Angle) +  UpVector* sin(Angle);

	up = -ForwardVector * sin(Angle) +  UpVector* cos(Angle);
	up = fwd.CrossProduct(RightVector);

	ForwardVector = fwd;
	UpVector = -up;




}

void Camera::RotateY (GLfloat Angle)
{
	Vector3D fwd;
	Vector3D right;

	fwd = ForwardVector * cos(Angle) +  RightVector* sin(Angle);

	right = -ForwardVector * sin(Angle) +  RightVector* cos(Angle);
	right = UpVector.CrossProduct(fwd);

	ForwardVector = fwd;
	RightVector = -right;


}

void Camera::RotateZ (GLfloat Angle)
{
	Vector3D up;
	Vector3D right;

	up = UpVector * cos(Angle) +  RightVector* sin(Angle);

	right = -UpVector * sin(Angle) +  RightVector* cos(Angle);
	ForwardVector = -right.CrossProduct(up);

	UpVector = up;
	RightVector = right;


}

// rotire fata de centru, la o distanta generica 5
void Camera::RotateXCenter (GLfloat Angle)
{
	float distance = 10;
	MoveForward(distance);
	RotateX(Angle);
	MoveBackward(distance);
}

// rotire fata de centru, la o distanta generica 5
void Camera::RotateYCenter (GLfloat Angle)
{
	float distance = 10;
	MoveForward(distance);
	RotateY(Angle);
	MoveBackward(distance);
}

// rotire fata de centru, la o distanta generica 5
void Camera::RotateZCenter (GLfloat Angle)
{
		float distance = 10;
	MoveForward(distance);
	RotateZ(Angle);
	MoveBackward(distance);

}

// plasare observator in scena
void Camera::Render( void )
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// punctul catre care se uita camera
	Vector3D ViewPoint = Position + ForwardVector;

	// stim vectorul UpVector, folosim LookAt
	gluLookAt(	Position.x,Position.y,Position.z,
				ViewPoint.x,ViewPoint.y,ViewPoint.z,
				UpVector.x,UpVector.y,UpVector.z);
}

// miscari simple, pe toate axele

void Camera::MoveForward( GLfloat Distance )
{


	Position = Position +ForwardVector * Distance;
	
}

void Camera::MoveBackward( GLfloat Distance )
{
	

	Position = Position -ForwardVector * Distance;
}

void Camera::MoveRight ( GLfloat Distance )
{


	Position = Position +RightVector * -Distance;
	
	
}

void Camera::MoveLeft ( GLfloat Distance )
{
	Vector3D addition(Distance,0,0);

	Position = Position -RightVector * -Distance;

}

void Camera::MoveUpward( GLfloat Distance )
{
	Vector3D addition(0,Distance,0);

	Position = Position + addition;

}

void Camera::MoveDownward( GLfloat Distance )
{

	Vector3D addition(0,-Distance,0);

	Position = Position + addition;
}

