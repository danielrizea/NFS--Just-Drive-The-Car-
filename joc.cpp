//-------------------------------------------------
// EGC
// -The Need for Speed-
//-------------------------------------------------
// W S    - miscare camera fata/spate
// A D    - miscare camera stanga/dreapta (strafe)
// R T    - rotatie camera stanga/dreapta pe Y
// F G    - rotatie camera sus/ jos pe X
// [ ]    - trecere intre diversele tipuri de camera
// < >    - modificare nivel de detaliu teren
// Sageti - miscare masinaselectat
//
// ESC    - iesire din program
//-------------------------------------------------


#include <stdlib.h>
#include <glut.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "Vector3D.h"
#include "Vector4D.h"
#include "Camera.h"
#include "Object3D.h"
#include "Plane.h"
#include "Paralelipiped.h"
#include "Light.h"
#include "Car.h"
#include <windows.h>

#define PI 3.14159265
// tasta escape
#define ESC	27

float *Vector3D::arr;
float *Vector4D::arr;


bool left;
bool right;
bool up;
bool down;

int upMoveObject;
float maxMoveObject;
float minMoveObject;


// VARIABILE
//-------------------------------------------------
// numarul de obiecte
int objectCount;
// obiectul selectat
int selectedIndex = -1;


int rotateCamera;

float lastx;
float lasty;

float unghiRotireMasina = 5;
float pasMiscareMasina = 0.2;
// camera
Camera *camera;
// vector de obiecte 3D
Object3D *objects;


Light *lights;
int nrFelinare ;

// planul de baza
Plane *ground;
// o lumina
Light *light;

Paralelipiped	*parapet;

int nrParalelipipedeParapet ;

Car *masina;

// FUNCTII
//-------------------------------------------------

// functie de initializare
void init(void)
{
	int i;

	// initialize vector arrays
	Vector3D::arr = new float[3];
	Vector4D::arr = new float[4];

	// initializam camera
	camera = new Camera();

	nrFelinare = 3;

	lights = new Light[nrFelinare];


	
	
	rotateCamera = 0;

	// vrem 5 obiecte
	objectCount = 8;
	
	objects = new Object3D[objectCount];

	
	right = false;
	left = false;
	up = false;
	down = false;

	masina = new Car();

	masina->SetBoundingBoxDimensions(1,0.6,0.5);
	

	nrParalelipipedeParapet = 12;
	parapet = new Paralelipiped[nrParalelipipedeParapet];


	


	float yParapet = 0.2;
	float latimeParapet = 0.25;
	for( i=0; i<nrParalelipipedeParapet; i++)
	{
		parapet[i].SetPosition(new Vector3D(0,yParapet,0));
	}


	parapet[0].SetPosition(new Vector3D(-19,-1.75,0.5));

	parapet[0].SetDimensiuni(latimeParapet,37,yParapet);

	parapet[1].SetPosition(new Vector3D(-16,-1.75,1.1));

	parapet[1].SetDimensiuni(latimeParapet,30,yParapet);

	parapet[2].SetPosition(new Vector3D(-9.1,-1.75,19));
	
	parapet[2].SetDimensiuni(20,latimeParapet,yParapet);

	parapet[3].SetPosition(new Vector3D(-9.1,-1.75,16));
	
	parapet[3].SetDimensiuni(14,latimeParapet,yParapet);

	parapet[4].SetPosition(new Vector3D(1,-1.75,16.6));
	
	parapet[4].SetDimensiuni(latimeParapet,5,yParapet);

	parapet[5].SetPosition(new Vector3D(-2.2,-1.75,12.5));

	parapet[5].SetDimensiuni(latimeParapet,7,yParapet);

	parapet[6].SetPosition(new Vector3D(5.8,-1.75,9));

	parapet[6].SetDimensiuni(16,latimeParapet,yParapet);
	
	parapet[7].SetPosition(new Vector3D(9.5,-1.75,14.2));

	parapet[7].SetDimensiuni(17,latimeParapet,yParapet);

	parapet[8].SetPosition(new Vector3D(14,-1.75,-2.5));

	parapet[8].SetDimensiuni(latimeParapet,23,yParapet);
	
	parapet[9].SetPosition(new Vector3D(18,-1.75,-1.9));
	
	parapet[9].SetDimensiuni(latimeParapet,32,yParapet);

	parapet[10].SetPosition(new Vector3D(-0.5,-1.75,-18));
	
	parapet[10].SetDimensiuni(37,latimeParapet,yParapet);

	parapet[11].SetPosition(new Vector3D(-1,-1.75,-14));
	
	parapet[11].SetDimensiuni(30,latimeParapet,yParapet);
	

	// felinare pentru circuit 

	lights[0].SetPosition(new Vector3D(-14,10,16));
	lights[0].LightType = Spot;
	lights[0].diffuse = Vector4D(4,4,4,1);
	lights[0].spotDirection = Vector3D(0,-1,0);

	lights[1].SetPosition(new Vector3D(10,10,-16));
	lights[1].LightType = Spot;
	lights[1].diffuse = Vector4D(4,4,4,1);
	lights[1].spotDirection = Vector3D(0,-1,0);

	lights[2].SetPosition(new Vector3D(12,10,12));
	lights[2].LightType = Spot;
	lights[2].diffuse = Vector4D(4,4,4,1);
	lights[2].spotDirection = Vector3D(0,-1,0);



	//cele 2 obiecte cu efecte id 0, 1 acestea sunt si transparente si nu au collision detection;

	maxMoveObject=15;
	minMoveObject=-15;

	upMoveObject = 1;

	objects[0].size = 0.5;
	objects[0].Type = Teapot;
	objects[0].SetPosition(new Vector3D(-18,-1.5,-10));
	objects[0].SetColor(new Vector3D(0.2,0.2,0.2));
	objects[0].diffuse = Vector4D(0.2,0.2,0.2,0.5);
	

	objects[1].size = 0.5;
	objects[1].Type = Teapot;
	objects[1].SetPosition(new Vector3D(16,-1.5,-10));
	objects[1].SetColor(new Vector3D(0.6,0.7,0.2));
	objects[1].diffuse = Vector4D(0.6,0.7,0.2,0.5);


	objects[2].size = 0.5;
	objects[2].Type = Cube;
	objects[2].setBoundingBox(0.5,0.5,0.5);
	objects[2].SetPosition(new Vector3D(-16.5,-1.75,10));
	objects[2].SetColor(new Vector3D(0.1,0.4,0.3));
	


	objects[3].size = 0.5;
	objects[3].Type = Cube;
	objects[3].setBoundingBox(0.5,0.5,0.5);
	objects[3].SetPosition(new Vector3D(16,-1.75,0));
	objects[3].SetColor(new Vector3D(0.7,0.3,0.2));
	

	printf(" cele doua cuburi au %f %f %f %f\n",objects[2].lungime,objects[2].latime,objects[3].lungime,objects[3].latime);
	objects[4].size = 0.5;
	objects[4].Type = Sphere;
	objects[4].SetPosition(new Vector3D(-18.5,-1.5,10));
	objects[4].SetColor(new Vector3D(0.3,0.4,0.5));
	
	objects[5].size = 0.5;
	objects[5].Type = Sphere;
	objects[5].SetPosition(new Vector3D(10,-1.5,10));
	objects[5].SetColor(new Vector3D(0.4,0.1,0.6));
	


	objects[6].size = 0.5;
	objects[6].Type = Sphere;
	objects[6].SetPosition(new Vector3D(17,-1.5,5));
	objects[6].SetColor(new Vector3D(0.8,0.5,0.2));
	

	objects[7].size = 0.5;
	objects[7].Type = Sphere;
	objects[7].SetPosition(new Vector3D(6,-1.5,12));
	objects[7].SetColor(new Vector3D(0.5,0.2,0.9));

	
	
	// initializam un plan de latura 20.0f
	ground = new Plane(20.0f);
	// culoare
	ground->SetColor(new Vector3D(0.04,0.0,0.0));
	// setam o grila de 4
	ground->SetLevelOfDetail(4);
	// sub nivelul obiectelor
	ground->SetPosition(new Vector3D(0,-1,0));

	masina->SetPosition(new Vector3D(-18,-1.9,0));
	masina->UpdateLightsPosition();
	// si wireframe
	ground->Wireframe = false;

	



	// initializam o noua lumina
	light = new Light();
	// setam pozitia
	light->SetPosition(new Vector3D(0, 10, 0));

	// pregatim o scena noua in opengl
	glClearColor(0.0, 0.0, 0.0, 0.0);	// stergem tot
	glEnable(GL_DEPTH_TEST);			// activam verificarea distantei fata de camera (a adancimii)
	glShadeModel(GL_SMOOTH);			// mod de desenare SMOOTH
	glEnable(GL_LIGHTING);				// activam iluminarea
	glEnable(GL_NORMALIZE);				// activam normalizarea normalelor
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
}


// functie de desenare (se apeleaza cat de repede poate placa video)
void drawScene(void)
{
	int i;

	

	// plasare observator
	camera->Render();
	// activare lumina

	
	//light->Render();
	masina->RenderLights();
	//desenare obiecte
	
	for( i=0; i<nrFelinare; i++)
		lights[i].Render();


	masina->Draw();

	for( i=0 ;i<nrFelinare; i++)
		lights[i].Draw();
	/*
	masina->farStanga->Draw();
	masina->farDreapta->Draw();
	masina->stopDreapta->Draw();
	masina->stopStanga->Draw();
	*/

	for( i=0; i<objectCount; i++)
		objects[i].Draw();

	for( i=0; i<nrParalelipipedeParapet; i++)
	{
		parapet[i].Draw();
	}

	
	// desenare plan
	ground->Draw();
	// desenare lumina (deseneaza o sfera acolo unde se afla lumina, nu face nimic altceva)
	//light->Draw();

	
	for( i=0; i<nrFelinare; i++)
		lights[0].Disable();

	// dezactivare lumina
	//light->Disable();
	masina->DisableLights();

}

void display(void)
{
	// stergere ecran
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	

	


	glAlphaFunc(GL_GEQUAL, 1.0f);
	// Render Pass - deseneaza scena
	drawScene();


	// pentru transparentA 
	glAlphaFunc(GL_LESS, 1.0f);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	// Render Pass - deseneaza scena
	drawScene();
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	//glDisable(GL_CULL_FACE);


	// double buffering
	glutSwapBuffers();

	// redeseneaza scena
	glutPostRedisplay();
		
}





int verificaColiziune(){

int i;

	for( i=0; i<nrParalelipipedeParapet; i++)
		if(masina->collisionDetection(parapet[i]) == 1)
			return 1;
	

	// primele doua obiecte sunt transparente, nu au collision detection
	for( i=2; i<objectCount; i++)
		if(masina->collisionDetection(objects[i]) == 1)
			return 1;

	
return 0;
}

// functie de update (se apeleaza constant, independent de Draw() )
void update(void)
{
	
//Sleep(20);

	//efect translatie
	Vector3D pos = objects[0].GetPosition();
	if(pos.z > maxMoveObject)
		upMoveObject = 0;

	if(pos.z < minMoveObject)
		upMoveObject = 1;

	if(upMoveObject == 1)
		objects[0].SetPosition( &(pos + Vector3D(0,0,0.4)) );
	else
		objects[0].SetPosition( &(pos + Vector3D(0,0,-0.4)) );

	// efect rotire
	Vector3D rot = objects[1].GetRotation();
	if(rot.y == 360)
		rot.y = 0;



	objects[1].SetRotation( &(rot + Vector3D(0,5,0) ));



	if(right && down || right && up) 
		{
			Vector3D rot = masina->GetRotation();

			if(rot.y == 0)
				rot.y = 360;

			masina->SetRotation(new Vector3D(rot.x,rot.y - unghiRotireMasina,rot.z));

			masina->UpdateLightsPosition();

			//doar cand se roteste se updateaza razele bounding box
			masina->updateBoundingBox();
			camera->UpdateCamera(masina->GetPosition(),rot);
			
		}
	if( left && down || left && up)  
		{
		
			Vector3D rot = masina->GetRotation();

			if(rot.y == 360)
				rot.y = 0;
			masina->SetRotation(new Vector3D(rot.x,rot.y + unghiRotireMasina,rot.z));

			masina->updateBoundingBox();
			masina->UpdateLightsPosition();

			//doar cand se roteste se updateaza razele bounding box
			masina->updateBoundingBox();
			camera->UpdateCamera(masina->GetPosition(),rot);
	}

	
	if( down) 
		{
			Vector3D rot = masina->GetRotation();
			

			

			masina->SetPosition(&( masina->GetPosition() + Vector3D(pasMiscareMasina * cos((rot.y * PI)/180 ),0,pasMiscareMasina * -sin((rot.y*PI)/180)) ));
		
			if(verificaColiziune() == 1)

			masina->SetPosition(&( masina->GetPosition() + Vector3D(pasMiscareMasina * -cos((rot.y * PI)/180 ),0,pasMiscareMasina * sin((rot.y*PI)/180)) ));

			masina->updateBoundingBox();
			masina->UpdateLightsPosition();


			camera->UpdateCamera(masina->GetPosition(),rot);

			
	} 
	 if (up)  
		{
Vector3D rot = masina->GetRotation();
			
			masina->SetPosition(&( masina->GetPosition() + Vector3D(pasMiscareMasina * -cos((rot.y * PI)/180 ),0,pasMiscareMasina * sin((rot.y*PI)/180)) ));

			if(verificaColiziune() == 1)

			masina->SetPosition(&( masina->GetPosition() + Vector3D(pasMiscareMasina * cos((rot.y * PI)/180 ),0,pasMiscareMasina * -sin((rot.y*PI)/180)) ));

			masina->UpdateLightsPosition();

			camera->UpdateCamera(masina->GetPosition(),rot);
		}

	
}

// functie de proiectie
void reshape(int w, int h)
{
	// viewport de dimensiuni date
	glViewport(0,0, (GLsizei) w, (GLsizei) h);
	// calculare aspect ratio ( Width/ Height )
	GLfloat aspect = (GLfloat) w / (GLfloat) h;

	// intram in modul proiectie
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// incarcam matrice de perspectiva 
	gluPerspective(45, aspect, 1.0, 60);
}

// handler pentru tastatura
void keyboard(unsigned char key , int x, int y)
{
	switch (key)
	{
		// la escape se iese din program
	case ESC : exit(0);
		// cu [ si ] se selecteaza urmatorul obiect sau predecesorul
	case ']' : 
		camera->cameraType = camera->cameraType++;
		
		if(camera->cameraType > 3)
			camera->cameraType = 0;


		printf("Tipul camerei %d\n",camera->cameraType);
		camera->UpdateCamera(masina->GetPosition(),masina->GetRotation());
		break;
	case '[' : 
	
		camera->cameraType = camera->cameraType--;
		if(camera->cameraType < 0)
		camera->cameraType = 3;

		printf("Tipul camerei %d\n",camera->cameraType);

		camera->UpdateCamera(masina->GetPosition(),masina->GetRotation());

		break;
		// cu < si > se modifica nivelul de detaliu al terenului
	case ',' : ground->SetLevelOfDetail(ground->GetLevelOfDetail()*2); break;
	case '.' : ground->SetLevelOfDetail(ground->GetLevelOfDetail()/2); break;
		// cu W A S D  R T F G freecam  observatorul se misca prin scena

		// W A S D deplasare camera fata stanga spate dreapta

		//R T rotatie pe Y

		//F G rotatie pe X

	case 'w' : case 'W' : 
		if(camera->cameraType == 3)
		camera->MoveForward(0.5); break;
	case 's' : case 'S' : 
		if(camera->cameraType == 3)
		camera->MoveBackward(0.5); break;
	case 'a' : case 'A' : 
		if(camera->cameraType == 3)
		camera->MoveLeft(0.5); break;
		break;
	case 'd' : case 'D' : 
		if(camera->cameraType == 3)
		camera->MoveRight(0.5); break;
		break;

	case 'u' : case 'U' :
		if(camera->cameraType == 3)
		camera->MoveUpward(0.5); break;
		break;

	case 'y' : case 'Y' : 
		if(camera->cameraType == 3)
		camera->MoveDownward(0.1); break;
		break;
	case 'r' : case 'R' : 
		if(camera->cameraType == 3)
		camera->RotateY(-0.05); 
		break;break;
	case 't' : case 'T' : 
		if(camera->cameraType == 3)
		camera->RotateY(0.05); 
		break;break;
		
		if(camera->cameraType == 3)
		case 'g' : case 'G' : 
			if(camera->cameraType == 3)
		camera->RotateX(-0.05); 
		break;break;
	case 'f' : case 'F' :
		if(camera->cameraType == 3)
		camera->RotateX(0.05); 
		break;break;

	



	default: break;
	}
}

// handler taste speciale
void keyboard(int key , int x, int y)
{
	
		
	// cu stanga/dreapta/sus/jos se misca masina

	if(GLUT_KEY_RIGHT == key) 
		{
		right = true;

		}
	if( GLUT_KEY_LEFT == key)  
		{
		
			left = true;
		}
	
	if( GLUT_KEY_DOWN == key) 
		{
			down = true;
		} 
	 if (GLUT_KEY_UP == key)  
		{
			up = true;
		}
	
}

void keybordUp(int key,int x, int y){

	if(GLUT_KEY_RIGHT == key) 
		{
		right = false;

		}
	if( GLUT_KEY_LEFT == key)  
		{
		
			left = false;
		}
	
	if( GLUT_KEY_DOWN == key) 
		{
			down = false;
		} 
	 if (GLUT_KEY_UP == key)  
		{
			up = false;
		}

}

void mouse(int buton, int stare, int x, int y)
{
	
	if (buton == GLUT_LEFT_BUTTON)
    {
      rotateCamera = (stare == GLUT_DOWN) ? 1 : 0;
      printf("Buton rotate camera %d \n",rotateCamera);
    }

	




}

void mouseMovement(int x, int y) {

		if(camera->cameraType == 3 && rotateCamera == 1){

float diffx=x-lastx; //check the difference between the current x and the last x position
float diffy=y-lasty; //check the difference between the current y and the last y position

printf("printf %d %d\n",diffx,diffy);
lastx=x; //set lastx to the current x position
lasty=y; //set lasty to the current y position
camera->RotateX( -diffy /1000); //set the xrot to xrot with the addition of the difference in the y position
camera->RotateY( -diffx /1000);// set the xrot to yrot with the addition of the difference in the x position
 glutPostRedisplay();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Animatie");
	init();
	glutIdleFunc(update);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutSpecialFunc(keyboard);
	glutSpecialUpFunc(keybordUp);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMovement);
	glutMainLoop();
	return 0;
}