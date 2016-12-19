package com.mii.formation.container;

import java.util.ArrayList;

//Déclaration d'une classe générique c'est à dire qu'on pourra insérer dans la pile différent type d'objet
//(Exemple de classe générique: Vector<T> ...) 
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
		//On léve une exception si la taille de l'arrayList est égale à 0
		if( arList.size() == 0)
			throw new Exception("Impossible de popper car il y a zéro objet dans la Pile !");
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
