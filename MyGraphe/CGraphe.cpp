#include "stdafx.h"
#include "CGraphe.h"

/****************************************
*  @brief: constructeur par default
*  @param:  rien
*  @return : rien
****************************************/
CGraphe::CGraphe()
{
	uiGRANBSommets = 0;
	uiGRANBArcs = 0;
	ppGRASommets = nullptr;
}

/****************************************
*  @brief: constructeur de recopie
*  @param:  & GRAGraphe
*  @return : rien
****************************************/
CGraphe::CGraphe(CGraphe & GRAGraphe)
{
	// Allocation de la liste sommet
	ppGRASommets = (CSommet **)malloc(sizeof(CSommet*) * GRAGraphe.uiGRANBSommets);
	
	if(ppGRASommets == nullptr)
		throw CException(ERREUR_ALLOCATION, "Erreur de l'allocation"); 

	for(unsigned int uiBoucle = 0 ; uiBoucle < GRAGraphe.uiGRANBSommets ; uiBoucle++) {
		ppGRASommets[uiBoucle] = new CSommet(*GRAGraphe.ppGRASommets[uiBoucle]);   //constructeur de recopie de CSommet
	}
	//Copier le nombre des sommets et des arcs
	uiGRANBSommets = GRAGraphe.uiGRANBSommets;
	uiGRANBArcs = GRAGraphe.uiGRANBArcs;
}

/****************************************
*  @brief: destructeur
*  @param:  rien
*  @return : rien
****************************************/
CGraphe::~CGraphe()
{
}

/****************************************
*  @brief: detruire la memoire
*  @param:  rien
*  @return : rien
****************************************/
void CGraphe::GRADetruireMemoire()
{
	if(ppGRASommets != nullptr) {
		for (unsigned int uiBoucleI = 0 ; uiBoucleI < uiGRANBSommets ; uiBoucleI++) {
			if(ppGRASommets[uiBoucleI] != nullptr)
				ppGRASommets[uiBoucleI]->SOMDetruireMemoire();
				delete ppGRASommets[uiBoucleI];
		}
		free(ppGRASommets);
	}
}

/****************************************
*  @brief: Obtenir le nombre de sommet
*  @param:  rien
*  @return : le nombre du sommet
****************************************/
unsigned int CGraphe::GRALireNBSommets()
{
	return uiGRANBSommets;
}

/****************************************
*  @brief: Obtenir le nombre de arc
*  @param:  rien
*  @return : le nombre du arc
****************************************/
unsigned int CGraphe::GRALireNBArcs()
{
	return uiGRANBArcs;
}

/****************************************
*  @brief: Modifier le nombre de sommet
*  @param:  uiValeur
*  @return : rien
****************************************/
void CGraphe::GRAModifierNBSommets(unsigned int uiValeur)
{
	uiGRANBSommets = uiValeur;
}

/****************************************
*  @brief: Modifier le nombre de arc
*  @param:  uiValeur
*  @return : rien
****************************************/
void CGraphe::GRAModifierNBArcs(unsigned int uiValeur)
{
	uiGRANBArcs = uiValeur;
}

/****************************************
*  @brief: Obtenir le tableau de sommet
*  @param:  rien
*  @return : le tableau de la classe CSommet
****************************************/
CSommet ** CGraphe::GRALireSommets()
{
	return ppGRASommets;
}

/****************************************
*  @brief: Ajouter un sommet
*  @param:  uiNumSommet
*  @return : rien
****************************************/
void CGraphe::GRAAjouterSommet(unsigned int uiNumSommet)
{
	CSommet * SOMRecherche = GRATrouverSommetParNum(uiNumSommet);
	if(SOMRecherche != nullptr){
		char pcMsg[1024];
		sprintf_s(pcMsg, "Impossible d'ajouter le sommet au graphe :le sommet num�ro %d d�j� existe  .", uiNumSommet);
		throw CException(ERREUR_SOMMET_DOUBLE, pcMsg); 
	}
	if(ppGRASommets == nullptr) {
		ppGRASommets = (CSommet **) malloc(sizeof(CSommet *));
	}
	else{
		ppGRASommets = (CSommet **) realloc(ppGRASommets, (uiGRANBSommets + 1) * sizeof(CSommet *) );
	}
	CSommet * SOMNewSommet = new CSommet(uiNumSommet);
	ppGRASommets[uiGRANBSommets] = SOMNewSommet;
	uiGRANBSommets++;
}

/****************************************
*  @brief: Modifier un sommet du tableau ppGRASommets
*  @param:  uiNumSommet, SOMSommet
*  @return : rien
****************************************/
void CGraphe::GRAModifierSommet(unsigned int uiNumSommet, CSommet * SOMSommet)
{
	if (ppGRASommets == nullptr)
		throw CException(ERREUR_VIDE_GRAPHE, "La liste des sommets est vide"); 
	CSommet * SOMRecherche = GRATrouverSommetParNum(uiNumSommet);
	if(SOMRecherche != nullptr){
		char pcMsg[1024];
		//Pr�paration du message d'erreur
		sprintf_s(pcMsg, "On ne peux pas faire la modification car on a d�j� le sommet num�ro %d dans ce graphe, c'est pas bien. ", uiNumSommet);
		throw CException(ERREUR_SOMMET_DOUBLE,pcMsg); 
	}

	unsigned int uiBoucle, uiNbArcArrivant = SOMSommet->SOMLireNBArcArrivant();

	// Permet d'actualiser le nouveau numero du sommet aux arcs precedant
	for (uiBoucle = 0 ; uiBoucle < uiNbArcArrivant ; uiBoucle++)
		SOMSommet->SOMLireArcsArrivant()[uiBoucle]->ARCModifierDestination(uiNumSommet);

	for (uiBoucle = 0 ; uiBoucle < uiGRANBSommets ; uiBoucle++) {
		CArc * ARCArcPartant = GRATrouverArcPartant(ppGRASommets[uiBoucle], SOMSommet->SOMLireNumSommet());
		CArc * ARCArcArrivant = GRATrouverArcArrivant(ppGRASommets[uiBoucle], SOMSommet->SOMLireNumSommet());
		if (ARCArcPartant != nullptr)
			ARCArcPartant->ARCModifierDestination(uiNumSommet);
		if (ARCArcArrivant != nullptr)
			ARCArcArrivant->ARCModifierDestination(uiNumSommet);
	}
	// Permet de changer le numero du sommet
	SOMSommet->SOMModifierNumSommet(uiNumSommet);
}

/****************************************
*  @brief: Supprimer un sommet du tableau ppGRASommets
*  @param: SOMSommet
*  @return : rien
****************************************/
void CGraphe::GRASupprimerSommet(CSommet * SOMSommet)
{
	unsigned int uiNumSommet = SOMSommet->SOMLireNumSommet();
	if(uiGRANBSommets < 1)
		throw CException(ERREUR_VIDE_GRAPHE, "Le nombre de sommet est z�ro"); 
	if(ppGRASommets == nullptr)
		throw CException(ERREUR_VIDE_GRAPHE, "La liste des sommets est nul");

	CSommet * SOMRecherche = GRATrouverSommetParNum(uiNumSommet);
	if(SOMRecherche == nullptr){
		char pcMsg[1024];
		sprintf_s(pcMsg, "Erreur lors de la suppresion du sommet : La num�ro du sommet %d n'a pas �t� trouv�e",  uiNumSommet);
		throw CException(ERREUR_SOMMET_INEXISTANT, pcMsg); 
	}

	uiGRANBArcs = uiGRANBArcs - SOMSommet->SOMLireNBArcArrivant() - SOMSommet->SOMLireNBArcPartant();

	// Vider les arcs partant du sommets et arrivant dans les autres
	for (unsigned int uiBoucleSommets = 0 ; uiBoucleSommets < uiGRANBSommets ; uiBoucleSommets++ ) {
		ppGRASommets[uiBoucleSommets]->SOMSupprimerArcArrivant(SOMSommet->SOMLireNumSommet());
		ppGRASommets[uiBoucleSommets]->SOMSupprimerArcPartant(SOMSommet->SOMLireNumSommet());
	}

	// Permet de supprimer les arcs li�s � ce sommet et liberer le memoire
	SOMSommet->SOMViderSommet();
	
	// Suppression du sommet
	for (unsigned int uiBoucleI = 0 ; uiBoucleI < uiGRANBSommets ; uiBoucleI++)
		if (SOMSommet->SOMLireNumSommet() == ppGRASommets[uiBoucleI]->SOMLireNumSommet()) {
			delete(ppGRASommets[uiBoucleI]);
			uiGRANBSommets--;
			while (uiBoucleI < uiGRANBSommets) {
				ppGRASommets[uiBoucleI] = ppGRASommets[uiBoucleI + 1];
				uiBoucleI++;
			}
		}
}

/****************************************
*  @brief: Ajouter un arc
*  @param:  uiNumDepart, uiNumArrivee
*  @return : rien
****************************************/
void CGraphe::GRAAjouterArc(unsigned int uiNumDepart, unsigned int uiNumArrivee)
{
	// Verifier si la liste des sommets est vide
	if (ppGRASommets == nullptr)
		throw CException(ERREUR_VIDE_GRAPHE, "La liste des sommets est vide");
	
	//Rechercher du sommet associ�
	CSommet * SOMDepart = GRATrouverSommetParNum(uiNumDepart);
	CSommet * SOMArrivant = GRATrouverSommetParNum(uiNumArrivee);

	//Verifier si le sommet est trouv�
	if(SOMDepart == nullptr) {
		char pcMsg[1024];
		sprintf_s(pcMsg, "Erreur lors de la cr�ation de l'arc entre les sommets %d et %d : La num�ro du sommet %d n'a pas �t� trouv�e", uiNumDepart, uiNumArrivee, uiNumDepart);
		throw CException(ERREUR_SOMMET_INEXISTANT, pcMsg); 
	}
	if(SOMArrivant == nullptr) {
		char pcMsg[1024];
		sprintf_s(pcMsg, "Erreur lors de la cr�ation de l'arc entre les sommets %d et %d : La num�ro du sommet %d n'a pas �t� trouv�e", uiNumDepart, uiNumArrivee, uiNumArrivee);
		throw CException(ERREUR_SOMMET_INEXISTANT, pcMsg); 
	}
	//Verifier la r�p�tition 
	CArc * ARCReherche = GRATrouverArcPartant(SOMDepart, uiNumArrivee);
	if(ARCReherche != nullptr)
		throw CException(ERREUR_ARC_DOUBLE, "L'arc est doubl�. Ne peux pas ajouter l'arc.");  

	CArc * ARCPartant = new CArc(uiNumArrivee);
	SOMDepart->SOMAjouterArcPartant(ARCPartant);

	CArc *  ARCArrivant = new CArc(uiNumDepart);
	SOMArrivant->SOMAjouterArcArrivant(ARCArrivant);

	uiGRANBArcs++;
}

/****************************************
*  @brief: Modifier un arc
*  @param:  uiNumDepartPre, uiNumArriveePre, uiNumDepartSuiv, uiNumArriveeSuiv
*  @return : rien
****************************************/
void CGraphe::GRAModifierArc(unsigned int uiNumDepartPre, unsigned int uiNumArriveePre, unsigned int uiNumDepartSuiv, unsigned int uiNumArriveeSuiv)
{
	GRASupprimerArc(uiNumDepartPre, uiNumArriveePre);
	GRAAjouterArc(uiNumDepartSuiv, uiNumArriveeSuiv);
}

/****************************************
*  @brief: Supprimer un arc
*  @param:  uiNumDepart, uiNumArrivee
*  @return : rien
****************************************/
void CGraphe::GRASupprimerArc(unsigned int uiNumDepart, unsigned int uiNumArrivee)
{
	//Rechercher du sommet associ�
	CSommet * SOMDepart = GRATrouverSommetParNum(uiNumDepart);
	CSommet * SOMArrivant = GRATrouverSommetParNum(uiNumArrivee);
	if (SOMDepart == nullptr)
	{
		char pcMsg[1024];
		sprintf_s(pcMsg, "Erreur lors de la suppression de l'arc entre les sommets %d et %d : La num�ro du sommet %d n'a pas �t� trouv�e.", uiNumDepart, uiNumArrivee, uiNumDepart);
		throw CException(ERREUR_SOMMET_INEXISTANT, pcMsg); 
	}

	if (SOMArrivant == nullptr)
	{
		char pcMsg[1024];
		sprintf_s(pcMsg, "Erreur lors de la suppression de l'arc entre les sommets %d et %d : La num�ro du sommet %d n'a pas �t� trouv�e", uiNumDepart, uiNumArrivee, uiNumArrivee);
		throw CException(ERREUR_SOMMET_INEXISTANT, pcMsg);
	}

	CArc * ARCPartant = GRATrouverArcPartant(SOMDepart, uiNumArrivee);
	
	for (unsigned int uiBoucle = 0 ; uiBoucle < SOMDepart->SOMLireNBArcPartant() ; uiBoucle++) {
		
		if(ARCPartant == nullptr)
			throw CException(ERREUR_ARC_INEXISTANT, "L'arc n'a pas �t� trouv�e");
		if (ARCPartant->ARCLireDestination() == SOMDepart->SOMLireArcsPartant()[uiBoucle]->ARCLireDestination()) {
			SOMDepart->SOMModifierNBArcPartant(SOMDepart->SOMLireNBArcPartant() - 1);
			delete(ARCPartant);
			while (uiBoucle < SOMDepart->SOMLireNBArcPartant()) {
				SOMDepart->SOMLireArcsPartant()[uiBoucle] = SOMDepart->SOMLireArcsPartant()[uiBoucle + 1];
				uiBoucle++;
			}	
			break;
		}
	}

	CArc * ARCArrivant = GRATrouverArcArrivant(SOMArrivant, uiNumDepart);

	for (unsigned int uiBoucle = 0 ; uiBoucle < SOMArrivant->SOMLireNBArcPartant() ; uiBoucle++) {
		
		if(ARCArrivant == nullptr)
			throw CException(ERREUR_ARC_INEXISTANT, "L'arc n'a pas �t� trouv�e");
		if(ARCArrivant->ARCLireDestination() == SOMArrivant->SOMLireArcsArrivant()[uiBoucle]->ARCLireDestination()) {
			SOMArrivant->SOMModifierNBArcArrivant(SOMArrivant->SOMLireNBArcArrivant() - 1);
			delete(ARCArrivant);
			while (uiBoucle < SOMArrivant->SOMLireNBArcArrivant()) {
				SOMArrivant->SOMLireArcsArrivant()[uiBoucle] = SOMArrivant->SOMLireArcsArrivant()[uiBoucle + 1];
				uiBoucle++;
			}
			break;
		}
	}

	uiGRANBArcs--;

}

/****************************************
*  @brief: Trouver un sommet par le numero du sommet
*  @param:  uiNumSommet
*  @return : un objet de la classe CSommet
****************************************/
CSommet * CGraphe::GRATrouverSommetParNum(unsigned int uiNumSommet)
{
	for(unsigned int uiBoucleI = 0 ; uiBoucleI < uiGRANBSommets ; uiBoucleI++) {
		if(uiNumSommet == ppGRASommets[uiBoucleI]->SOMLireNumSommet() )
			return ppGRASommets[uiBoucleI];
	}
	return nullptr;
}

/****************************************
*  @brief: Trouver un ArcPartant 
*  @param:  SOMDepart, uiDestination
*  @return : un objet de la classe CArc
****************************************/
CArc * CGraphe::GRATrouverArcPartant(CSommet * SOMDepart, unsigned int uiDestination)
{
	unsigned int uiNBArcPartant = SOMDepart->SOMLireNBArcPartant();
	CArc ** ARCPartant = SOMDepart->SOMLireArcsPartant();
	for(unsigned int uiBoucleArcs = 0 ; uiBoucleArcs < uiNBArcPartant ; uiBoucleArcs++)
			if(uiDestination  ==  ARCPartant[uiBoucleArcs]->ARCLireDestination())
				return ARCPartant[uiBoucleArcs];
	return nullptr;
}

/****************************************
*  @brief: Trouver un ArcArrivan
*  @param:  SOMArrivant, uiDestination
*  @return : un objet de la classe CArc
****************************************/
CArc * CGraphe::GRATrouverArcArrivant(CSommet * SOMArrivant, unsigned int uiDestination)
{
	unsigned int uiNBArcArrivant = SOMArrivant->SOMLireNBArcArrivant();
	CArc ** ARCArrivant = SOMArrivant->SOMLireArcsArrivant();
	for(unsigned int uiBoucleArcs = 0 ; uiBoucleArcs < uiNBArcArrivant ; uiBoucleArcs++)
			if(uiDestination ==  ARCArrivant[uiBoucleArcs]->ARCLireDestination())
				return ARCArrivant[uiBoucleArcs];
	return nullptr;
}

/****************************************
*  @brief: Afficher tous les informations du tableau de sommet
*  @param:  rien
*  @return : rien
****************************************/
void CGraphe::GRAAfficherSommets()
{
	cout << "-----------GrapheSommet:----------" << endl;
	for(unsigned int uiBoucleI = 0 ; uiBoucleI < uiGRANBSommets ; uiBoucleI++) {

		cout << "NumSommet = " << ppGRASommets[uiBoucleI]->SOMLireNumSommet() << endl;
		cout << "NBArcArrivant = " << ppGRASommets[uiBoucleI]->SOMLireNBArcArrivant() << endl;
		cout << "NBArcPartant = " << ppGRASommets[uiBoucleI]->SOMLireNBArcPartant() << endl;

		for(unsigned int uiBoucleArc = 0 ; uiBoucleArc < ppGRASommets[uiBoucleI]->SOMLireNBArcPartant() ; uiBoucleArc++) {
			cout << "ArcPartant:" << ppGRASommets[uiBoucleI]->SOMLireArcsPartant()[uiBoucleArc]->ARCLireDestination() << endl;
		}

		for(unsigned int uiBoucleArc = 0 ; uiBoucleArc < ppGRASommets[uiBoucleI]->SOMLireNBArcArrivant() ; uiBoucleArc++) {
			cout << "ArcArrivant:" << ppGRASommets[uiBoucleI]->SOMLireArcsArrivant()[uiBoucleArc]->ARCLireDestination() << endl;
		}
		cout << endl;
	}
	cout << "----------------------------------" << endl;
	cout << endl;
}

/****************************************
*  @brief: Afficher le graphe 
*  @param:  rien
*  @return : rien
****************************************/
void CGraphe::GRAAfficherGraphe()
{
	cout << "-------Afficher le graphe:--------\n" << endl;

	cout << "GrapheNBSommets = " << GRALireNBSommets() << endl;
	cout << "GrapheNBArcs = " << GRALireNBArcs() << endl;
	cout << endl;
	for(unsigned int uiBoucleSommets = 0 ; uiBoucleSommets < uiGRANBSommets ; uiBoucleSommets++) {
		unsigned int uiNBArcPartant = ppGRASommets[uiBoucleSommets]->SOMLireNBArcPartant();
		CArc ** ARCPartant = ppGRASommets[uiBoucleSommets]->SOMLireArcsPartant();
		for(unsigned int uiBoucleArc = 0 ; uiBoucleArc < uiNBArcPartant ; uiBoucleArc++)
			cout << ppGRASommets[uiBoucleSommets]->SOMLireNumSommet() << " --> " << ARCPartant[uiBoucleArc]->ARCLireDestination() << " ; " << endl;
	}
	cout << endl;
	GRAAfficherSommets();
}

/****************************************
*  @brief:  La surcharge d'operateur = de deux objets de la classe CGraphe
*  @param: & GRAGraphe
*  @return: un objet de la classe CGraphe
****************************************/
CGraphe & CGraphe::operator=(CGraphe & GRAGraphe)
{
	if (GRAGraphe.GRALireSommets() == nullptr)
		throw CException(ERREUR_VIDE_GRAPHE, "La liste des sommets est vide");//ECHECLISTEVIDE

	// Allocation de la liste sommet
	if (ppGRASommets == nullptr) {
		ppGRASommets = (CSommet **) malloc(sizeof(CSommet * ) * GRAGraphe.uiGRANBSommets);
	}
	else{
		ppGRASommets = (CSommet **) realloc(ppGRASommets, GRAGraphe.uiGRANBSommets * sizeof(CSommet * ) );
	}
	if(ppGRASommets == nullptr)
		throw CException(ERREUR_ALLOCATION, "Erreur de l'allocation");

	//Cre�r des nouveau sommets et les copier
	for(unsigned int uiBoucle = 0 ; uiBoucle < GRAGraphe.uiGRANBSommets ; uiBoucle++)
		ppGRASommets[uiBoucle] = new CSommet(*GRAGraphe.ppGRASommets[uiBoucle]);   //constructeur de recopie de CSommet
			
	uiGRANBSommets = GRAGraphe.uiGRANBSommets;
	uiGRANBArcs = GRAGraphe.uiGRANBArcs;
	
	return *this;
}