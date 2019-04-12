#pragma once
#include"CGraphe.h"

class COperationGraphe
{
private:
	CGraphe OperationGraphe;
public:
	/****************************************
	*  @brief: constructeur par default
	*  @param:  rien
	*  @return : rien
	****************************************/
	COperationGraphe(void);
	/****************************************
	*  @brief: destructeur
	*  @param:  rien
	*  @return : rien
	****************************************/
	~COperationGraphe(void);
	/****************************************
	*  @brief: Operation pour Inverser un graphe
	*  @param:  GRAGraphe
	*  @return : CGraphe    le graphe inverse
	****************************************/
	CGraphe & OPGInverserGraphe(CGraphe & GRAgraphe);
	/****************************************
	*  @brief: detruire la memoire du graphe pendant qu'on inverse le graphe
	*  @param:  rien
	*  @return : rien
	****************************************/
	void OPGDetruireGraphe();
};

