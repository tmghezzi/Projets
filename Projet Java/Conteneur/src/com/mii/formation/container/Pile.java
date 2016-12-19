package com.mii.formation.container;

import java.util.ArrayList;

//D�claration d'une classe g�n�rique c'est � dire qu'on pourra ins�rer dans la pile diff�rent type d'objet
//(Exemple de classe g�n�rique: Vector<T> ...) 
public class Pile<T> extends MonContainer implements IContainerStatistique 
{
	private ArrayList<T> arList;
	private int nbEntre;
	private int nbSortie;
	private long debutTime;
	
	public Pile() {
		this.arList = new ArrayList<T>();
		this.nbEntre = 0;
		this.nbSortie = 0;
		this.debutTime = System.currentTimeMillis();
		
	}

	public void push(T aObject)
	{
		arList.add(aObject);
		nbEntre++;
	}
	
	public T pop() throws Exception
	{
		//On l�ve une exception si la taille de l'arrayList est �gale � 0
		if( arList.size() == 0)
			throw new Exception("Impossible de popper car il y a z�ro objet dans la Pile !");
		nbSortie++;
		return arList.remove(arList.size()-1);
	}
	
	@Override
	public float getNbMoyenEntreesParSeconde() {
		
		return nbEntre/((System.currentTimeMillis()-debutTime)/1000f);
	}

	@Override
	public float getNbMoyenSortiesParSeconde() {
		return nbSortie/((System.currentTimeMillis()-debutTime)/1000f);
	}

	@Override
	String getNombreObjets() {
		return super.getNombreObjets()+" taille: "+arList.size();
	}
	
}
