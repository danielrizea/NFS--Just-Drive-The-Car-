
#ifndef CAR_H
#define CAR_H

#include <glut.h>
#include "Object3D.h"
#include "Camera.h"
#include "Light.h"
#include "Paralelipiped.h"
class Car: public Object3D
{
public:
	Car();

	void Draw();

	void RenderLights();
	void DisableLights();
	void DrawLights();
	

	//updateaza luminile masinii si vectorul directie in fuctie de pozitia si directia masinii
	void UpdateLightsPosition();

	void SetBoundingBoxDimensions(GLfloat lungime, GLfloat latime, GLfloat inaltime);

	Vector3D direction;

	Light *farStanga;
	Light *farDreapta;
	Light *stopStanga;
	Light *stopDreapta;

	//bounding box dimensiuni masina

	

private:
	// poligoane pentru partile ,asinii

	Paralelipiped *acoperis;
	Paralelipiped *podea;
	Paralelipiped *capota;
	Paralelipiped *portbagaj;
	Paralelipiped *spateStopuri;
	Paralelipiped *fataFaruri;
	Paralelipiped *lateralDreapta;
	Paralelipiped *lateralStanga;
	Paralelipiped *parbrizFata;
	Paralelipiped *parbrizSpate;
	Paralelipiped *geamStanga;
	Paralelipiped *geamDreapta;


	Object3D *roataSpateDreapta;
	Object3D *roataSpateStanga;
	Object3D *roataFataDreapta;
	Object3D *roataFataStanga;

	
	// doar conturile farurilor
	Object3D *farStangaDummy;
	Object3D *farDreaptaDummy;
	Object3D *stopStangaDummy;
	Object3D *stopDreaptaDummy;

	// culoare difuza
	Vector4D diffuse;
	// culoare ambientala
	Vector4D ambient;
	// culoare speculara
	Vector4D specular;

};
#endif