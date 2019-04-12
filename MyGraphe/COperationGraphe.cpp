#include "stdafx.h"
#include "COperationGraphe.h"

/****************************************
*  @brief: constructeur par default
*  @param:  rien
*  @return : rien
****************************************/
COperationGraphe::COperationGraphe(void)
{
}

/****************************************
*  @brief: destructeur
*  @param:  rien
*  @return : rien
****************************************/
COperationGraphe::~COperationGraphe(void)
{
}

/****************************************
*  @brief: Operation pour Inverser un graphe
*  @param:  GRAGraphe
*  @return : CGraphe    le graphe inverse
****************************************/
CGraphe & COperationGraphe::OPGInverserGraphe(CGraphe & GRAGraphe)
{
	//Extraire les sommets du graphe initial
	CSommet ** ppOPGSommets = GRAGraphe.GRALireSommets();
	unsigned int uiOPGNBSommet = GRAGraphe.GRALireNBSommets();

	// Creation des sommets
	for (unsigned int uiBoucleSommets = 0 ; uiBoucleSommets < uiOPGNBSommet ; uiBoucleSommets++)
		OperationGraphe.GRAAjouterSommet(ppOPGSommets[uiBoucleSommets]->SOMLireNumSommet());

	// Creation des arcs
	for (unsigned int uiBoucleSommets = 0 ; uiBoucleSommets < uiOPGNBSommet ; uiBoucleSommets++) {
		
		//Extraire les arcs partant des sommets
		CArc ** ppOPGArcPartant = ppOPGSommets[uiBoucleSommets]->SOMLireArcsPartant();
		unsigned int uiNBArcPartant = ppOPGSommets[uiBoucleSommets]->SOMLireNBArcPartant();

		//Inverser les arcs de chaque sommets
		for (unsigned int uiBoucleArcs = 0 ; uiBoucleArcs < uiNBArcPartant ; uiBoucleArcs++) {
			unsigned int uiArcInverse = ppOPGArcPartant[uiBoucleArcs]->ARCLireDestination();
			OperationGraphe.GRAAjouterArc(uiArcInverse, ppOPGSommets[uiBoucleSommets]->SOMLireNumSommet());
		}
	}
	cout << "Tous les arcs du graphe est inversé!" << endl;
	return OperationGraphe;
}

/****************************************
*  @brief: detruire la memoire du graphe pendant qu'on inverse le graphe
*  @param:  rien
*  @return : rien
****************************************/
void COperationGraphe::OPGDetruireGraphe()
{
	OperationGraphe.GRADetruireMemoire();
}