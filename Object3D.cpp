// EGC
// Laborator 7
//-------------------------------------------------

#include "Object3D.h"
#include <math.h>
#include <stdio.h>

#define PI 3.14159265
/*
Declaratiile clasei Object3D
Clasa pentru desenare si modificare a unui obiect 3d.
*/

// VARIABILE STATICE
//-------------------------------------------------
//float *Vector3D::arr = new float[3];
Vector3D Object3D::SelectedColor = Vector3D(1,0,1);		// culoarea obiectului selectat
Vector3D Object3D::ColorIncrement = Vector3D(0.04,0.04,0.04);	// valoarea cu care creste/scade in timp culoarea de mai sus


// CONSTRUCTORI
//-------------------------------------------------

// constructor de baza
Object3D::Object3D()
{
	defaultSettings();
}

// seteaza si tipul obiectului
Object3D::Object3D(ObjectType _Type)
{
	defaultSettings();
	Type = _Type;

}

// seteaza si pozitia
Object3D::Object3D(Vector3D *_translation)
{
	defaultSettings();
	this->SetPosition(_translation);

	

}

// seteaza pozitie, rotatie, translatie
Object3D::Object3D(Vector3D *_translation, Vector3D *_rotation, Vector3D *_scale)
{
	defaultSettings();
	this->SetPosition(_translation);
	this->SetRotation(_rotation);
	this->SetScale(_scale);	
	

}

// seteaza toti parametrii la valorile lor default
void Object3D::defaultSettings()
{
	translation = Vector3D(0.0,0.0,0.0);
	rotation = Vector3D(0.0,0.0,0.0);
	scale = Vector3D(1.0,1.0,1.0);

	Lighted = true;
	Wireframe = false;
	Visible = true;
	Type = Cube;


	diffuse.a = 1;

	size = 1;

	levelOfDetail = 12;
	selected = false;

	//bounding box default
	lungime = 1;
	latime = 1;
	inaltime = 1;

	fataDr = Vector3D();
	fataSt = Vector3D();
	spateSt = Vector3D();
	spateDr = Vector3D();

	puncteBoundingBox[0] = &spateSt;
	puncteBoundingBox[1] = &spateDr;
	puncteBoundingBox[2] = &fataDr;
	puncteBoundingBox[3] = &fataSt;
	

	xMin=-lungime/2;
	xMax=lungime/2;

	zMin=-latime/2;
	zMax=latime/2;

	yMin=-inaltime/2;
	yMax=inaltime/2;


	rLungime = lungime/2;
	rLatime = latime/2;

}

// DRAW
//-------------------------------------------------
void Object3D::Draw ()
{
	// daca nu este vizibil, nu-l desenam
	if(!Visible)
	return;

	glPushMatrix();

	// translatie
	glTranslatef( translation.x , translation.y , translation.z );

	// rotatie
	glRotatef( rotation.x , 1.0 , 0.0 , 0.0 );
	glRotatef( rotation.y , 0.0 , 1.0 , 0.0 );
	glRotatef( rotation.z , 0.0 , 0.0 , 1.0 );

	// scalare
	glScalef( scale.x , scale.y , scale.z);

	// setari de material :
	// daca nu este selectat
	
	
		// culoare normala
		glColor3f(color.x,color.y,color.z);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(Vector4D(color.x,color.y,color.z,diffuse.a)).Array());
	
	
	
	// culoare speculara, default
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(Vector4D(0.1,0.1,0.1,1)).Array());

	// daca este wireframe
	if( Wireframe )
		switch( Type )
	{
		// cub wireframe
		case Cube :	glutWireCube(1.0); break;
		// sfera wireframe
		case Sphere : glutWireSphere(1.0, levelOfDetail, levelOfDetail); break;
		// orice alt obiect, specificat de programator
		case Custom : customDraw();
	}
	// daca nu este wireframe
	else
		switch( Type )
	{
		// cub solid
		case Cube :	glutSolidCube(size); break;
		// sfera solida
		case Sphere : glutSolidSphere(size, levelOfDetail, levelOfDetail); break;
		// orice alt obiect, specificat de programator

		case Teapot : glutSolidTeapot(size);break;
		case Torus : glutSolidTorus(0.05,0.07,100,30); break;
		case Custom : customDraw();
	}

	glPopMatrix();
}


void Object3D::updateBoundingBox(){

int i;
float min = 1000;
float max = -1000;
	Vector3D rot = GetRotation();
	Vector3D pos = GetPosition();


	printf("Update bounding box %f %f\n",lungime,latime);

	
	float s = sin((rot.y * PI)/180 ); 
	float c = cos((rot.y * PI)/180 );
	
	float sr = -c; 
	float cr = -s; 
	// ne intereseaza doar rotatia pe y momentan, rotatie in planul xoz
	Vector3D dreapta = Vector3D(cr,0,-sr);

	Vector3D pctFata = pos + Vector3D(lungime/2 * c,0,lungime/2*-s);

	Vector3D pctSpate = pos + Vector3D(lungime/2*-c,0,lungime/2*s);

	fataDr = pctFata + Vector3D(latime/2,0,latime/2 ) * dreapta;
	fataSt = pctFata - Vector3D(latime/2,0,latime/2) * dreapta;

	
	spateDr = pctSpate + Vector3D(latime/2,0,latime/2 ) * dreapta;
	spateSt = pctSpate - Vector3D(latime/2,0,latime/2) * dreapta;



	min = 1000;
	max = -1000;
	
	for(i=0; i<4 ;i++)
	{

		if(puncteBoundingBox[i]->x < min)
			min = puncteBoundingBox[i]->x;

		if(puncteBoundingBox[i]->x > max)
			max = puncteBoundingBox[i]->x;
	}

	xMin = min;
	xMax = max;


	min = 1000;
	max = -1000;
	
	for(i=0; i<4 ;i++)
	{

		if(puncteBoundingBox[i]->z < min)
			min = puncteBoundingBox[i]->z;

		if(puncteBoundingBox[i]->z > max)
			max = puncteBoundingBox[i]->z;
	}

	zMin = min;
	zMax = max;
	
	


}

int Object3D::collisionDetection(Object3D object){


	Vector3D pos = GetPosition();


	printf("masina %f %f %f %f\n",xMin,xMax,zMin,zMax);
	printf("obiect %f %f %f %f \n",object.xMin,object.xMax,object.zMin,object.zMax);
	printf("\n");

	// aligned bounding box collision detection

	// nu au cum sa se intersecteze daca satisfac conditiile 

	if(zMax < object.zMin)
		return 0;

	if(zMin > object.zMax)
		return 0;

	if(xMax < object.xMin)
		return 0;

	if(xMin > object.xMax)
		return 0;

	// se intersecteaza 
	return 1;

		/* old collision detection 
	if(abs(pos.x - object.GetPosition().x) < rLungime + object.rLungime &&  abs(pos.z - object.GetPosition().z) <rLatime + object.rLatime )
		return 1;

	return 0;
	*/
}

// functie proprie
// se presupune ca Wireframe este tratat inauntru
void Object3D::customDraw()
{
	// TODO : aici va puteti desena un obiect personalizat/incarcat din fisier/pre-generat/etc
}

// SETTERS
//-------------------------------------------------

// selecteaza
void Object3D::Select()
{
	selected = true;
}

// deselecteaza
void Object3D::Deselect()
{
	selected = false;
}

// seteaza culoare
void Object3D::SetColor(Vector3D *_color)
{
	color = *_color;
}

// seteaza pozitie
void Object3D::SetPosition(Vector3D *_translation)
{


	xMin= xMin + _translation->x - translation.x;
	xMax= xMax + _translation->x - translation.x;

	zMin= zMin + _translation->z - translation.z;
	zMax= zMax + _translation->z - translation.z;

	yMin= yMin + _translation->y - translation.y;
	yMax= yMax + _translation->y - translation.y;

	translation = *_translation;

	

}


// seteaza rotatie
void Object3D::SetRotation(Vector3D *_rotation)
{
	rotation = *_rotation;


}

// seteaza scalare
void Object3D::SetScale(Vector3D *_scale)
{
	scale = *_scale;
}

// seteaza nivelul de detaliu
void Object3D::SetLevelOfDetail(float _levelOfDetail)
{
	if( _levelOfDetail > 0 && _levelOfDetail < MAXIMUM_LOD)
		levelOfDetail = _levelOfDetail;
}


// GETTERS
//-------------------------------------------------

// intoarce pozitia
Vector3D Object3D::GetPosition()
{
	return translation;
}

// intoarce rotatia
Vector3D Object3D::GetRotation()
{
	return rotation;
}

// intoarce scala
Vector3D Object3D::GetScale()
{
	return scale;
}

// intoarce nivelul de detaliu
float Object3D::GetLevelOfDetail()
{
	return levelOfDetail;
}

void Object3D::setBoundingBox(float _lungime, float _latime, float _inaltime){


	lungime = _lungime;
	latime = _latime;
	inaltime = _inaltime;


	xMin=translation.x-lungime/2;
	xMax=translation.x+lungime/2;

	zMin=translation.z-latime/2;
	zMax=translation.z+latime/2;

	yMin=translation.y-inaltime/2;
	yMax=translation.y+inaltime/2;

}