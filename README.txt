Rizea Daniel-Octavian
331CA


			Tema 4 -The Need for Speed-






	Taste JOC :

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

	Platforma development : Windows XP, Visula Studio Express.

	Clase noi (fata de laborator 7):

	Paralelipiped => (primeste dimensiunile latime, lungime, inaltime) si deseneaza un paralelipiped prin glVertex3f() si glNormal3f() ;
 
	Car => clasa sintetizeaza elementele componente ale masinii (capota, acoperis.. faruri) si contine
functii ajutatoare de manipulare a farurilor de tip spot si recalculari de pozitie pentru faruri (spoturi) la rotire.
 
	


	Implementare :

		Masina a fost realizata ca in descrierea din tema.A fost construita din mai multe paralelipipede
de diverse dimensiuni toruri pentru roti , geamuri transparente si 4 lumini de tip spot;

		Obstacolele : contruite prin Glut cub, sfera, teapot

	Gameplay :
		Jucatorul se afla in controlul masinii si trebuie sa se plimbe pe pista. Acesta nu poate trece
prin parapet si nici prin obiectele solide.Jucatorul poate trece prin obiectele transparente. (Cele doua ceainice).

		Cele doua ceainice transparente au doua efecte. Unul se translateaza pe o latura a circuitlui, iar
celalalt se invarte fata de propriul centru.

		In total sunt 8 obstacole pe circuit.


	Collision detection :

		->functia de scoate noile coordonate ale bounding box Object3D->updateBoundingBox();

		->functia ce testeaza coliziunea intre doua obiecte Object3D1->collisionDetection(object3D2);

		Ambele functii sunt membre ale clasei Object3D.

		Am utilizat collision detection alligned bounding boxes.
		
		updateBoundingBox();

		Fiecare obiect are un bounding box corespunzator.In
momentul cand obiectul de misca, se modifica si "coordonatele" acestui bounding box.La translatare este simplu, se translateaza si
aceste coordonate.La rotire este mai dificil, se calculeaza prin intermediul vectorului rotatie al obiectului care este
vectorul de forward din care se afla vectorul right pe obiect dupa care lucrurile sunt simple, se pot afla punctele
ce delimiteaza bounding boxul . 

		collisionDetection();

		Verifica daca dreptunghiurile proiectiilor boundingBoxurilor pe axele de coordonate se suprapun.



	
		  
	