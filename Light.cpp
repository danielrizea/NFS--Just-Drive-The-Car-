// EGC
// Laborator 7
//-------------------------------------------------
#include <stdio.h>


#include "Light.h"
#include "math.h"


// id-ul de baza
int Light::baseId = 0;

// constructor fara parametri, mosteneste constructorul de Sfera din Object3D
// deoarece dorim ca lumina sa fie ilustrata printr-o sfera
Light::Light() : Object3D(Sphere)
{
	// valori default
	diffuse = Vector4D(4,4,4,1);
	ambient = Vector4D(0,0,0,0);
	specular = Vector4D(1,1,1,1);
	color = Vector3D(1,1,1);
	scale = Vector3D(0.2,0.2,0.2);

	// id-ul este unic, id-ul de baza incrementat
	id = baseId++;
	
	// sfera plasata in locul luminii nu este wireframe
	Wireframe = false;
	LightType = Ideal;

	linearAtenuation = 0.1f;
	constantAtenuation = 0.1f;
	quadricAtenuation = 0.0f;

	spotCutOff = 30;
	spotExponent = 30;
	spotDirection=	Vector3D(-10,-1,0);
	

}

Light::Light(IlluminationType t) : Object3D(Sphere)
{
// valori default
	diffuse = Vector4D(4,4,4,1);
	ambient = Vector4D(0,0,0,0);
	specular = Vector4D(1,1,1,1);
	color = Vector3D(1,1,1);
	scale = Vector3D(0.2,0.2,0.2);

	
	// id-ul este unic, id-ul de baza incrementat
	id = baseId++;
	
	// sfera plasata in locul luminii nu este wireframe
	Wireframe = false;

	LightType = t;
	linearAtenuation = 0.0f;
	constantAtenuation = 0.1f;
	quadricAtenuation = 0.0f;


	spotCutOff = 30;
	spotExponent = 30;
	spotDirection=	Vector3D(-10,-1,0);
	

}
// functie care plaseaza efectivl umina in scena
void Light::Render()
{
	if(LightType == Ideal)
	{
	// atenuari standard
	glLightf(GL_LIGHT0 + id,GL_CONSTANT_ATTENUATION,constantAtenuation);
	glLightf(GL_LIGHT0 + id,GL_LINEAR_ATTENUATION,linearAtenuation);
	glLightf(GL_LIGHT0 + id,GL_QUADRATIC_ATTENUATION,quadricAtenuation );

	// culoarea luminii 
	glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, Vector4D(diffuse.x, diffuse.y, diffuse.z, diffuse.a).Array());
	// culoarea ambientala 
	glLightfv(GL_LIGHT0 + id, GL_AMBIENT, ambient.Array());
	// culoarea speculara
	glLightfv(GL_LIGHT0 + id, GL_SPECULAR, specular.Array());
	// pozitia luminii
	glLightfv(GL_LIGHT0 + id, GL_POSITION, Vector4D(translation.x,translation.y,translation.z,1).Array());
	}
	else
	{

		//printf("activare light %d \n",id);

	glLightf(GL_LIGHT0 + id,GL_CONSTANT_ATTENUATION,1);
	glLightf(GL_LIGHT0 + id,GL_LINEAR_ATTENUATION,0.2f);

	// culoarea luminii 
	glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, Vector4D(diffuse.x, diffuse.y, diffuse.z, diffuse.a).Array());
	// culoarea ambientala 
	glLightfv(GL_LIGHT0 + id, GL_AMBIENT, ambient.Array());
	// culoarea speculara
	glLightfv(GL_LIGHT0 + id, GL_SPECULAR, specular.Array());
	// pozitia luminii
	glLightfv(GL_LIGHT0 + id, GL_POSITION, Vector4D(translation.x,translation.y,translation.z,1).Array());
		
	

		glLightfv(GL_LIGHT0 + id, GL_SPOT_DIRECTION, spotDirection.Array());
		glLightf(GL_LIGHT0 + id, GL_SPOT_CUTOFF, spotCutOff);
		glLightf(GL_LIGHT0 + id, GL_SPOT_EXPONENT, spotExponent);

	}

	// activam lumina
	glEnable(GL_LIGHT0 + id);
}

// functie care dezactiveaza lumina
void Light::Disable()
{
	glDisable(GL_LIGHT0 + id);
}
