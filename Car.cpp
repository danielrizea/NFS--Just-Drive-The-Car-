#include "Car.h"
#include "stdio.h"
#define PI 3.14159265
Car::Car() : Object3D(Custom)
{
	// valori default
	diffuse = Vector4D(1,1,1,1);
	ambient = Vector4D(0,0,0,0);
	specular = Vector4D(1,1,1,1);
	color = Vector3D(1,1,1);
	scale = Vector3D(1.0,1.0,1.0);
	
	rotation.y = 90;

	direction = Vector3D(0,0,0);

	//instantiere poligoane

	// valori utilizate pentru bounding box 
	

	acoperis = new Paralelipiped(0.3,0.5,0.05);
	acoperis->SetPosition(&(acoperis->GetPosition()+ Vector3D(0.04,0.4,0.0)));

	acoperis->diffuse = Vector4D(0.2,0.4,0,1);
	podea = new Paralelipiped(1,0.5,0.05);
	

	capota = new Paralelipiped(0.2,0.4,0.05);

	capota->SetPosition( &(capota->GetPosition() + Vector3D(-0.4,0.2,0.0)));
	capota->diffuse = Vector4D(0.2,0.4,0,1);

	portbagaj = new Paralelipiped(0.2,0.5,0.2);

	portbagaj->SetPosition( &(portbagaj->GetPosition() + Vector3D(0.4,0.1,0.0)));

	spateStopuri = new Paralelipiped(0.05,0.5,0.2);

	spateStopuri->SetPosition( &(spateStopuri->GetPosition() + Vector3D(0.5,0.1,0.0)));

	fataFaruri = new Paralelipiped(0.05,0.5,0.2);
	
	fataFaruri->SetPosition( &(fataFaruri->GetPosition() + Vector3D(-0.5,0.1,0.0)));

	lateralDreapta = new Paralelipiped(1,0.05,0.2);

	lateralDreapta->SetPosition( &(lateralDreapta->GetPosition() + Vector3D(0.0,0.1,-0.25)));

	lateralStanga = new Paralelipiped(1,0.05,0.2);

	lateralStanga->SetPosition( & (lateralStanga->GetPosition() + Vector3D(0.0,0.1,0.25)));

	parbrizFata = new Paralelipiped(0.05,0.5,0.3);

	parbrizFata->SetPosition( &(parbrizFata->GetPosition() + Vector3D(-0.2,0.3,0) ));
	parbrizFata->SetRotation( &(parbrizFata->GetRotation() + Vector3D(0,0,-45)));
	
	parbrizFata->diffuse = Vector4D(0.3,1,1,0.9);

	parbrizSpate = new Paralelipiped(0.05,0.5,0.3);

	parbrizSpate->SetPosition ( &(parbrizSpate->GetPosition() + Vector3D(0.3,0.3,0)));
	parbrizSpate->SetRotation( &(parbrizSpate->GetRotation() + Vector3D(0,0,50)));
	
	parbrizSpate->diffuse = Vector4D(0.3,1,1,0.9);

	geamStanga = new Paralelipiped(0.3,0.05,0.2);

	geamStanga->SetPosition( &(geamStanga->GetPosition() + Vector3D(0.05,0.3,0.25)));

	geamStanga->diffuse = Vector4D(0.3,1,1,0.9);
	
	geamDreapta = new Paralelipiped(0.3,0.05,0.2);

	geamDreapta->SetPosition( &(geamDreapta->GetPosition() + Vector3D(0.05,0.3,-0.25)));
	
	geamDreapta->diffuse = Vector4D(0.3,1,1,0.9);

	roataSpateDreapta = new Object3D(Torus);

	

	roataSpateDreapta->SetPosition( &(roataSpateDreapta->GetPosition() + Vector3D(0.4,0,-0.3)));

	roataSpateDreapta->SetColor(new Vector3D(0.01,0.01,0.01));

	roataSpateStanga = new Object3D(Torus);

	roataSpateStanga->SetPosition( &(roataSpateStanga->GetPosition()+ Vector3D(0.4,0,0.3)));

	roataSpateStanga->SetColor(new Vector3D(0.01,0.01,0.01));

	roataFataDreapta = new Object3D(Torus);

	roataFataDreapta->SetPosition( &(roataFataDreapta->GetPosition() + Vector3D(-0.4,0,-0.3)));
	roataFataDreapta->SetColor(new Vector3D(0.01,0.01,0.01));
	

	roataFataStanga = new Object3D(Torus);
	roataFataStanga->SetPosition( &(roataFataStanga->GetPosition() + Vector3D(-0.4,0,0.3)));
	roataFataStanga->SetColor(new Vector3D(0.01,0.01,0.01));
	

	
	farStangaDummy = new Object3D(Sphere);
	farStangaDummy->size = 0.06;
	farStangaDummy->SetPosition(&(farStangaDummy->GetPosition() + Vector3D(-0.5,0.15,-0.15)));
	farStangaDummy->SetColor(new Vector3D(1,1,0));


	farStanga = new Light(Spot);
	farStanga->SetColor(new Vector3D(0.2,0.2,0.2));
	farStanga->size = 0.6;
	
	farStanga->SetPosition(&(farStanga->GetPosition() + Vector3D(-0.8,-0.5,-0.15)));

	farStanga->spotCutOff = 40;
	farStanga->spotExponent = 10;
	farStanga->diffuse = Vector4D(4,4,4,1);
	farStanga->spotDirection =  Vector3D(0,-1,0);


	farDreaptaDummy = new Object3D(Sphere);
	farDreaptaDummy->size = 0.06;
	farDreaptaDummy->SetPosition(&(farDreaptaDummy->GetPosition() + Vector3D(-0.5,0.15,0.15)));
	farDreaptaDummy->SetColor(new Vector3D(1,1,0));


	farDreapta = new Light(Spot);
	farDreapta->SetColor(new Vector3D(0.2,0.2,0.2));
	farDreapta->size = 0.6;
	
	farDreapta->SetPosition(&(farDreapta->GetPosition() + Vector3D(-0.8,-0.5,0.15)));

	farDreapta->spotCutOff = 40;
	farDreapta->spotExponent = 10;
	farDreapta->diffuse = Vector4D(1,1,1,1);
	farDreapta->spotDirection =  Vector3D(0,-1,0);



	stopStanga = new Light(Spot);
	stopStanga->SetColor(new Vector3D(0.2,0.2,0.2));
	stopStanga->size = 0.6;
	

	stopStanga->SetPosition(&(stopStanga->GetPosition() + Vector3D(-0.8,-0.5,0.15)));

	stopStanga->spotCutOff = 40;
	stopStanga->spotExponent = 20;
	stopStanga->diffuse = Vector4D(1,0,0,1);
	stopStanga->spotDirection =  Vector3D(0,-1,0);


	stopStangaDummy = new Object3D(Cube);
	stopStangaDummy->size = 0.1;
	stopStangaDummy->SetPosition(&(stopStangaDummy->GetPosition() + Vector3D(0.5,0.1,0.15)));
	stopStangaDummy->SetColor(new Vector3D(1,0,0));


	stopDreapta = new Light(Spot);
	stopDreapta->SetColor(new Vector3D(0.2,0.2,0.2));
	stopDreapta->size = 0.6;
	
	stopDreapta->SetPosition(&(stopDreapta->GetPosition() + Vector3D(-0.8,-0.5,0.15)));

	stopDreapta->spotCutOff = 40;
	stopDreapta->spotExponent = 20;
	stopDreapta->diffuse = Vector4D(1,0,0,1);
	stopDreapta->spotDirection =  Vector3D(0,-1,0);

	stopDreaptaDummy = new Object3D(Cube);
	stopDreaptaDummy->size = 0.1;
	stopDreaptaDummy->SetPosition(&(stopDreaptaDummy->GetPosition() + Vector3D(0.5,0.1,-0.15)));
	stopDreaptaDummy->SetColor(new Vector3D(1,0,0));
}
void Car::Draw(){

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
	
	
	// culoare speculara, default
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(Vector4D(0.1,0.1,0.1,1)).Array());

	acoperis->Draw();
	podea->Draw();
	capota->Draw();
	portbagaj->Draw();
	spateStopuri->Draw();
	fataFaruri->Draw();
	lateralDreapta->Draw();
	lateralStanga->Draw();
	parbrizFata->Draw();
	parbrizSpate->Draw();
	geamStanga->Draw();
	geamDreapta->Draw();

	roataSpateDreapta->Draw();
	roataSpateStanga->Draw();
	roataFataDreapta->Draw();
	roataFataStanga->Draw();
	
	DrawLights();

	
	//printf("Desenare masina\n");

	glPopMatrix();
}

void Car::RenderLights(){

	farStanga->Render();
	farDreapta->Render();
	stopStanga->Render();
	stopDreapta->Render();


}

void Car::DisableLights(){

	farStanga->Disable();
	farDreapta->Disable();
	stopStanga->Disable();
	stopDreapta->Disable();

}

void Car::DrawLights(){

	farStangaDummy->Draw();
	farDreaptaDummy->Draw();
	stopDreaptaDummy->Draw();
	stopStangaDummy->Draw();


	


}

void Car::UpdateLightsPosition(){


	Vector3D pos = GetPosition();
	Vector3D rot = GetRotation();


	farStanga->SetPosition( &(pos + Vector3D(cos(((rot.y+12) * PI)/180) * -0.5,0.15, -sin(((rot.y + 12)*PI)/180)* -0.5)) ); 

	farStanga->spotDirection = Vector3D( -cos(((rot.y) * PI)/180),-0.02,sin(((rot.y )*PI)/180));
	
	
	farDreapta->SetPosition( &(pos + Vector3D(cos(((rot.y-12) * PI)/180) * -0.5,0.15, -sin(((rot.y - 12)*PI)/180)* -0.5)) ); 

	farDreapta->spotDirection = Vector3D( -cos(((rot.y) * PI)/180),-0.02,sin(((rot.y )*PI)/180));
	

	stopStanga->SetPosition( &(pos + Vector3D(cos(((rot.y-12) * PI)/180) * 0.5,0.15, sin(((rot.y - 12)*PI)/180)* -0.5)) ); 

	stopStanga->spotDirection = Vector3D( cos(((rot.y) * PI)/180),-0.02,-sin(((rot.y )*PI)/180));


	stopDreapta->SetPosition( &(pos + Vector3D(cos(((rot.y+12) * PI)/180) * 0.5,0.15, sin(((rot.y + 12)*PI)/180)* -0.5)) ); 

	stopDreapta->spotDirection = Vector3D( cos(((rot.y) * PI)/180),-0.02,-sin(((rot.y )*PI)/180));


}

void Car::SetBoundingBoxDimensions(GLfloat _lungime, GLfloat _latime, GLfloat _inaltime){



lungime = _lungime ;
latime = _latime;
inaltime = _inaltime;

rLungime = lungime/2;
rLatime = latime/2;

	xMin=translation.x -lungime/2;
	xMax=translation.x +lungime/2;

	zMin=translation.z -latime/2;
	zMax=translation.z +latime/2;

	yMin=translation.y-inaltime/2;
	yMax=translation.y +inaltime/2;


}