package com.mii.formation.container;

import java.util.Vector;
//D�claration d'une classe g�n�rique c'est � dire qu'on pourra ins�rer dans la FileAttente diff�rent type d'objet
//(Exemple de classe g�n�rique: Vector<T> ...)

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
		//On enregistre la date de cr�ation de la file d'attente
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
		//On l�ve une exception si la taille du vector est �gale � 0 (car il n'y a plus d'objet � retirer)
		if( aVector.size() == 0)
			throw new Exception("Impossible de retirer car il y a z�ro objet dans la File d'attente !");
		nbSortie++;
		
		//On stock le temps d'attente pour faire des stats sur l'attente moyenne 
		tempsDattente += aVector.get(0).dureObjet();
		
		
		return (T)aVector.remove(0).getObj();
	}
	
	public T peek(int idx) throws Exception 
	{
		//On v�rifie si l'indexe demand� (idx) ne d�passe pas les bornes inf et sup du Vector
		//(index inf�rieur � 0 ou sup�rieur � la taille du vector) si c'est le cas on l�ve une exception 
		if( idx >= aVector.size() || idx < 0)
			throw new IllegalArgumentException(
					"Impossible de r�cuperer l'objet situ� � l'indexe : "+idx+" (OutOfBound)");
					
		//sinon on retourne l'objet enregistr� � cette indexe
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
		
		//On calcul l'attente moyenne des objets d�ja sortie et ceux encore dans la file
		//On v�rifie qu'on ne divise par z�ro sinon on risque de lev� une exception ^^
		if(nbSortie+aVector.size() > 0)
			return (enCoursDattente+tempsDattente)/(aVector.size()+nbSortie);
		
		return 0.0f;
	}
	
	public float getObjetAttente(int idx)
	{
		if(idx >= aVector.size() || idx < 0)
			throw new IllegalArgumentException("Impossible de r�cuperer la dur�e de l'objet (OutOfBound)"
					+ " situ� � l'indexe : "+idx);
		
		return aVector.get(idx).dureObjet();
	}
	
	
	public void afficherListeAttente()
	{
		for(TimedObject<T> itemCourant : aVector)
			System.out.println(itemCourant);
	}
	
	
	//Classe qui va permettre d'avoir une date d'ajout de l'objet, pour pouvoir le stocker
	//directement dans le Vector (N�cessaire au calcul de la dur�e d'attente)
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
					+"\nDur�e dans la file: "+dureObjet()+"\nContenu Objet:\n"+obj;
		}
		
	}

}
