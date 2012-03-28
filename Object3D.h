// EGC
// Laborator 7
//-------------------------------------------------

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <glut.h>
#include "Vector3D.h"
#include "Vector4D.h"

// nivelul maxim de detaliu
#define MAXIMUM_LOD 50 

enum ObjectType
{
	Cube,	// glut cube
	Sphere, // glut sphere
	Torus,  // glut torus
	Teapot,
	Custom  // obiect propriu
};

/*
	OBJECT3D
	Clasa pentru desenare si modificare a unui obiect 3d.
*/
class Object3D
{
// VARIABILE STATICE ::
//-------------------------------------------------
public:
	static Vector3D SelectedColor;
	static Vector3D ColorIncrement;

// VARIABILE
//-------------------------------------------------
// publice
public :
	// incep cu litera mare
	ObjectType Type;	// tipul obiectuliu
	bool Wireframe;		// daca va fi desenat wireframe
	bool Visible;		// daca va fi sau nu desenat
	bool Lighted;		// daca este sau nu luminat

	float size;

	Vector3D translation;	// pozitie
	Vector3D rotation;		// rotatie
	Vector3D scale;			// scalare
	Vector3D color;			// culoare

	// culoare difuza
	Vector4D diffuse;
	// culoare ambientala
	Vector4D ambient;
	// culoare speculara
	Vector4D specular;

// private
protected:
	// incep cu litera mica
	

	float levelOfDetail;	// nivelul de detaliu (pentru glutSphere)
	bool selected;			// daca este sau nu selectat


// FUNCTII ::
//-------------------------------------------------
public:
// constructor
	// fara parametri
	Object3D();		
	// doar cu tip
	Object3D(ObjectType);
	// doar cu pozitie
	Object3D(Vector3D *);			
	// cu pozitie, rotatie, scalare
	Object3D(Vector3D *,Vector3D *,Vector3D *);


// functie de desenare
	void virtual Draw();

	void updateBoundingBox();
	
	void setBoundingBox(float _lungime, float _latime, float _inaltime);

	// 1 -> true 0 -> false
	int collisionDetection(Object3D obiect);



	//bounding box pentru coliziuni

	float xMin;
	float xMax;
	float yMin;
	float yMax;
	float zMin;
	float zMax;

	float rLungime;
	float rLatime;

	// vector 4 elemente puncte st fata, dr fata ,dr spate, st spate
	Vector3D *puncteBoundingBox[4];

	Vector3D fataSt;
	Vector3D fataDr;
	Vector3D spateSt;
	Vector3D spateDr;



	//pe x
	GLfloat latime;
	//pe z
	GLfloat lungime;
	//pe y
	GLfloat inaltime;

// setters 
	// pentru toate variabilele care nu sunt publice
	void Select();
	void Deselect();
	void SetPosition(Vector3D *);
	void SetRotation(Vector3D *);
	void SetScale(Vector3D *);
	void SetColor(Vector3D *);
	void SetLevelOfDetail(float);
// getters
	// pentru toate variabilele care nu sunt publice, si pot fi modificate din exterior
	Vector3D GetRotation();
	Vector3D GetScale();
	Vector3D GetPosition();
	float GetLevelOfDetail();

protected:
	// functie proprie de desenare. se apeleaza doar daca tipul este Custom
	void virtual customDraw();
	// seteaza valorile default 
	void defaultSettings();
	
};

#endif
