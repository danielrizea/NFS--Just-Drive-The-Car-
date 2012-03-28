// EGC
// Laborator 7
//-------------------------------------------------

#ifndef LIGHT_H
#define LIGHT_H

#include <glut.h>
#include "Object3D.h"

// tipul de iluminare
enum IlluminationType
{
	Ideal, // lumina omnidirectionala
	Spot   // lumina directionala
};

/*
	Light
	Clasa pentru desenarea si activarea unei lumini
*/

// derivata din object3D
class Light : public Object3D
{

// VARIABILE STATICE
//-------------------------------------------------
private:
	static int baseId;

// VARIABILE
//-------------------------------------------------
public:
	// tipul luminii - nu este folosit, inca
	IlluminationType LightType;
	float linearAtenuation;
	float constantAtenuation;
	float quadricAtenuation;

	Vector3D spotDirection;
	float spotCutOff;
	float spotExponent;
	// lumina difuza
	Vector4D diffuse;

private:
	// id-ul asignat. pleaca din 0 si este folosit pentru GL_LIGHT0 + id
	int id;
	
	// lumina ambientala
	Vector4D ambient;
	// lumina speculara
	Vector4D specular;
	

	// pentru spot :

// FUNCTII
//-------------------------------------------------
public:
	// constructor fara parametri
	Light();
	
	Light(IlluminationType);
	// plaseaza lumina in scena si o activeaza
	void Render();
	// dezactiveaza lumina
	void Disable();

};

#endif