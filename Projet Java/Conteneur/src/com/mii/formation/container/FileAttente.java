package com.mii.formation.container;

import java.util.Vector;
//Déclaration d'une classe générique c'est à dire qu'on pourra insérer dans la FileAttente différent type d'objet
//(Exemple de classe générique: Vector<T> ...)

public class FileAttente<T> extends MonContainer implements IContainerStatistique{

	private Vector<TimedObject<T>> aVector;
	private int nbEntre;
	private int nbSortie;
	private long debutTime;
	private float tempsDattente;
	
	public FileAttente() {
		this.aVector = new Vector<TimedObject<T>>();
		this.nbEntre = 0;
		this.nbSortie = 0;
		//On enregistre la date de création de la file d'attente
		//pour les methodes getNbMoyenEntreesParSeconde et getNbMoyenSortiesParSeconde
		this.debutTime = System.currentTimeMillis();
	}

	public void ajouter(T aObj)
	{
		aVector.add(new TimedObject<T>(aObj));
		nbEntre++;
	}
	
	public T retirer() throws Exception
	{
		//On léve une exception si la taille du vector est égale à 0 (car il n'y a plus d'objet à retirer)
		if( aVector.size() == 0)
			throw new Exception("Impossible de retirer car il y a zéro objet dans la File d'attente !");
		nbSortie++;
		
		//On stock le temps d'attente pour faire des stats sur l'attente moyenne 
		tempsDattente += aVector.get(0).dureObjet();
		
		
		return (T)aVector.remove(0).getObj();
	}
	
	public T peek(int idx) throws Exception 
	{
		//On vérifie si l'indexe demandé (idx) ne dépasse pas les bornes inf et sup du Vector
		//(index inférieur à 0 ou supérieur à la taille du vector) si c'est le cas on léve une exception 
		if( idx >= aVector.size() || idx < 0)
			throw new IllegalArgumentException(
					"Impossible de récuperer l'objet situé à l'indexe : "+idx+" (OutOfBound)");
					
		//sinon on retourne l'objet enregistré à cette indexe
		return (T)aVector.get(idx).getObj();
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
		return super.getNombreObjets()+" taille: "+aVector.size();
	}
	
	public float getAttenteMoyenne()
	{
	
		float enCoursDattente = 0;
		//On calcul le temps d'attente pour les objets qui sont encore dans la file
		for(TimedObject<T> itemCourant : aVector)
				enCoursDattente += itemCourant.dureObjet();
		
		//On calcul l'attente moyenne des objets déja sortie et ceux encore dans la file
		//On vérifie qu'on ne divise par zéro sinon on risque de levé une exception ^^
		if(nbSortie+aVector.size() > 0)
			return (enCoursDattente+tempsDattente)/(aVector.size()+nbSortie);
		
		return 0.0f;
	}
	
	public float getObjetAttente(int idx)
	{
		if(idx >= aVector.size() || idx < 0)
			throw new IllegalArgumentException("Impossible de récuperer la durée de l'objet (OutOfBound)"
					+ " situé à l'indexe : "+idx);
		
		return aVector.get(idx).dureObjet();
	}
	
	
	public void afficherListeAttente()
	{
		for(TimedObject<T> itemCourant : aVector)
			System.out.println(itemCourant);
	}
	
	
	//Classe qui va permettre d'avoir une date d'ajout de l'objet, pour pouvoir le stocker
	//directement dans le Vector (Nécessaire au calcul de la durée d'attente)
	@SuppressWarnings("hiding")
	class TimedObject<T>
	{
		private long dateAjout;
		private T obj;
		
		public TimedObject(T obj) {
			this.dateAjout = System.currentTimeMillis();
			this.obj = obj;
		}
		
		public TimedObject(T obj, long dateAjout) {
			this.dateAjout = dateAjout;
			this.obj = obj;
		}
		
		public T getObj() {
			return obj;
		}

		public void setObj(T obj) {
			this.obj = obj;
		}
		
		public float dureObjet()
		{
			return (System.currentTimeMillis()-dateAjout)/1000f;
		}
		
		@Override
		public String toString()
		{
			return "Informations objet dans la file:\nObjet de type"+obj.getClass().getSimpleName()
					+"\nDurée dans la file: "+dureObjet()+"\nContenu Objet:\n"+obj;
		}
		
	}

}
