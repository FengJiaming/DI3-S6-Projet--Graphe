// MyGraphe.cpp�: d�finit le point d'entr�e pour l'application console.
//


#include "stdafx.h"
#include "CFichier.h"
#include "COperationGraphe.h"
#include "CTestsUnitaires.h"

int main(int argc, char* argv[])
{

	if(argc == 2){
		
		//Cre�r un objet CFichier pour passer le nom de fichier
		CFichier * FICFichier = new CFichier(argv[1]); 

		// Declaration des graphes
		//Stocker le graphe lit par le fichier
		CGraphe * GRAGraphe = new CGraphe();
		//Pour stocker le nouveau graphe invers�
		CGraphe * GRAGrapheInverse = new CGraphe();

		//G�n�rer l'operation pour inverser le graphe
		COperationGraphe * OPGOperation = new COperationGraphe();;

		try{
			//Lire le fichier et cre�r le graphe associ�
			*GRAGraphe = FICFichier->FICLire_Fichier();

			//Afficher le graphe associ� � �cran
			cout <<  "\n-----------GRAPHE INITIAL----------- \n" << endl;
			GRAGraphe->GRAAfficherGraphe();

			//Inverser le graphe
			*GRAGrapheInverse = OPGOperation->OPGInverserGraphe(*GRAGraphe);
			
			//Afficher le graphe invers� � �cran
			cout <<  "\n-----------GRAPHE INVERSE----------- \n" << endl;
			GRAGrapheInverse->GRAAfficherGraphe();
		
		}
		catch(CException EXCLevee){
			cout << "Exception numero " <<EXCLevee.EXCLireValeur() << ": "<< EXCLevee.EXCLireMessage() << endl;

		}
		//Lib�rer m�moire
		GRAGraphe->GRADetruireMemoire();
		GRAGrapheInverse->GRADetruireMemoire();
		delete GRAGraphe;
		delete GRAGrapheInverse;

		//Lib�rer le m�moire du graphe temporaire pendant qu'on lire le fichier
		FICFichier->FICDetruireGraphe();  
		delete FICFichier;

		//Lib�rer le m�moire du graphe temporaire pendant qu'on inverse le graphe
		OPGOperation->OPGDetruireGraphe();
		delete OPGOperation;
		
	}
	else{
		cout << "Veuillez entrer UN nom de fichier" << endl;
	}

	//Tests Unitaires
	CTestsUnitaires TUNITests;	
	TUNITests.TUNIStart();

	system("pause");
	
	//D�tecter les fuites de m�moire
	_CrtDumpMemoryLeaks();

    return 0;
	
}




//Tests sur des op�ration sur un graphe(test1.txt)
/*
	GRAGraphe->GRAModifierSommet(4,GRAGraphe->GRATrouverSommetParNum(2));
	GRAGraphe->GRASupprimerSommet(GRAGraphe->GRATrouverSommetParNum(1)); 
	GRAGraphe->GRASupprimerSommet(GRAGraphe->GRATrouverSommetParNum(6)); //Exception
	GRAGraphe->GRASupprimerArc(1, 2);
	GRAGraphe->GRASupprimerArc(1, 3);
	GRAGraphe->GRASupprimerArc(1, 4); //Exception
	GRAGraphe->GRAModifierArc(1,2,1,7);//OK
	GRAGraphe->GRAAfficherGraphe();
*/

//Tests sur des op�ration sur un graphe(test3.txt)
/*
	GRAGraphe->GRASupprimerSommet(GRAGraphe->GRATrouverSommetParNum(1));
	GRAGraphe->GRAAjouterSommet(100);
	GRAGraphe->GRAAjouterSommet(10);
	GRAGraphe->GRAAjouterSommet(101);
	GRAGraphe->GRAAjouterArc(1,101);
	GRAGraphe->GRAAjouterArc(101,1);
	GRAGraphe->GRAAfficherGraphe();
*/