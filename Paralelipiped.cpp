// EGC
// Laborator 7
//-------------------------------------------------

#include "Paralelipiped.h"

// constructor care primeste ca parametru latura cubului

Paralelipiped::Paralelipiped(){

	// valori default
	diffuse = Vector4D(1,1,1,1);
	ambient = Vector4D(0,0,0,0);
	specular = Vector4D(1,1,1,1);
	color = Vector3D(1,1,1);
	scale = Vector3D(1.0,1.0,1.0);

	// default , nu este wireframe
	Wireframe = false;

	lungime = 3.0;
	latime = 0.5;
	inaltime = 0.5;

	rLatime = latime / 2;
	rLungime = lungime / 2;

	

}
Paralelipiped::Paralelipiped(GLfloat _lungime, GLfloat _latime , GLfloat _inaltime) : Object3D()
{
	// valori default
	diffuse = Vector4D(1,1,1,1);
	ambient = Vector4D(0,0,0,0);
	specular = Vector4D(1,1,1,1);
	color = Vector3D(1,1,1);
	scale = Vector3D(1.0,1.0,1.0);
	
	// default , nu este wireframe
	Wireframe = false;

	lungime = _lungime;
	latime = _latime;
	inaltime = _inaltime;

	rLungime = lungime / 2;
	rLatime = latime / 2;

	

}

// functie care seteaza latura cubului
void Paralelipiped::SetDimensiuni(GLfloat _lungime, GLfloat _latime, GLfloat _inaltime)
{
	Vector3D pos;
	pos = GetPosition();

	lungime = _lungime;
	latime = _latime;
	inaltime = _inaltime;

	rLungime = lungime / 2;
	rLatime = latime /2;


	xMin=translation.x -lungime/2;
	xMax=translation.x +lungime/2;

	zMin=translation.z -latime/2;
	zMax=translation.z +latime/2;

	yMin=translation.y-inaltime/2;
	yMax=translation.y +inaltime/2;
}

// Seteaza culoare difuza ( atentie , la testul alfa se foloseste componenta A din culoarea difuza !!!_
void Paralelipiped::SetDiffuse(Vector4D *color)
{
	diffuse = *color;
}

// DRAW
// Suprascriem prin polimorfism functia de desenare a clasei parinte 
// pentru a avea propria functie de desenare
//-------------------------------------------------
void Paralelipiped::Draw ()
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
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(Vector4D(diffuse.x,diffuse.y,diffuse.z,diffuse.a)).Array());
	
	
	// culoare speculara, default
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(Vector4D(0.1,0.1,0.1,1)).Array());

	// daca este wireframe
	if( Wireframe )
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}
	// daca nu este wireframe
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}

	// desenare quaduri care alcatuiesc cubul

	glBegin(GL_QUADS);

	// Back face
	glNormal3f(0.0,0.0,-1.0);
	glVertex3f( lungime/2,  inaltime/2, -latime/2);

	glNormal3f(0.0,0.0,-1.0);
	glVertex3f( -lungime/2, inaltime/2, -latime/2);

	glNormal3f(0.0,0.0,-1.0);
	glVertex3f(-lungime/2, -inaltime/2, -latime/2);

	glNormal3f(0.0,0.0,-1.0);
	glVertex3f(lungime/2,  -inaltime/2, -latime/2);

	// Front face
	glNormal3f(0.0,0.0,1.0);
	glVertex3f( lungime/2,  inaltime/2, latime/2);

	glNormal3f(0.0,0.0,1.0);
	glVertex3f( -lungime/2, inaltime/2, latime/2);

	glNormal3f(0.0,0.0,1.0);
	glVertex3f(-lungime/2, -inaltime/2, latime/2);

	glNormal3f(0.0,0.0,1.0);
	glVertex3f(lungime/2,  -inaltime/2, latime/2);

	// left face
	glNormal3f(-1.0,0.0,0.0);
	glVertex3f( -lungime/2,  inaltime/2, -latime/2);

	glNormal3f(-1.0,0.0,0.0);
	glVertex3f( -lungime/2, inaltime/2, latime/2);

	glNormal3f(-1.0,0.0,0.0);
	glVertex3f(-lungime/2, -inaltime/2, latime/2);

	glNormal3f(-1.0,0.0,0.0);
	glVertex3f(-lungime/2,  -inaltime/2, -latime/2);

	// right face
	glNormal3f(1.0,0.0,0.0);
	glVertex3f( lungime/2,  inaltime/2, -latime/2);

	glNormal3f(1.0,0.0,0.0);
	glVertex3f( lungime/2, inaltime/2, latime/2);

	glNormal3f(1.0,0.0,0.0);
	glVertex3f(lungime/2, -inaltime/2, latime/2);

	glNormal3f(1.0,0.0,0.0);
	glVertex3f(lungime/2,  -inaltime/2, -latime/2);

	// top face
	glNormal3f(0.0,1.0,0.0);
	glVertex3f( lungime/2,  inaltime/2, -latime/2);

	glNormal3f(0.0,1.0,0.0);
	glVertex3f( -lungime/2, inaltime/2, -latime/2);

	glNormal3f(0.0,1.0,0.0);
	glVertex3f(-lungime/2, inaltime/2, latime/2);

	glNormal3f(0.0,1.0,0.0);
	glVertex3f(lungime/2,  inaltime/2, latime/2);

	// bottom face
	glNormal3f(0.0,-1.0,0.0);
	glVertex3f( lungime/2,  -inaltime/2, -latime/2);

	glNormal3f(0.0,-1.0,0.0);
	glVertex3f( -lungime/2, -inaltime/2, -latime/2);

	glNormal3f(0.0,-1.0,0.0);
	glVertex3f(-lungime/2, -inaltime/2, latime/2);

	glNormal3f(0.0,-1.0,0.0);
	glVertex3f(lungime/2,  -inaltime/2, latime/2);


	glEnd();

	glPopMatrix();
}