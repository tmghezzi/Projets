package com.mii.formation.container;

import java.util.TreeMap;

public class CarnetAdresse extends MonContainer {
	private TreeMap<String,Personne> aTreeMap;
	
	
	public enum Information{ADRESSE,VILLE};
	public CarnetAdresse() {
		this.aTreeMap = new TreeMap<String,Personne>();
	}
	
	public void inserer(Personne aPersonne) throws Exception
	{
		String pNom = aPersonne.getNom();
		String pPrenom = aPersonne.getPrenom(); 
		if(estPresent(pNom, pPrenom))
			throw new Exception("Cette personne existe déja dans le carnet d'adresse!");
				
		aTreeMap.put(pNom+pPrenom, 
				aPersonne);	
	}
	
	
	public Personne supprimer(String nom,String prenom) throws Exception
	{
		if(!estPresent(nom, prenom))
			throw new Exception("Impossible de supprimer cette personne car elle n'existe pas dans le carnet d'adresse!");		
		return aTreeMap.remove(nom+prenom);
	}
	
	public Personne supprimer(Personne aPersonne) throws Exception
	{	
		return this.supprimer(aPersonne.getNom(),aPersonne.getPrenom());
	}
	
	public String get(String nom, String prenom, Information aInfo) throws Exception
	{
		if(!estPresent(nom, prenom))
			throw new Exception("Cette personne n'existe pas dans le carnet d'adresse!");
		Personne aPers = ((Personne)aTreeMap.get(nom+prenom));
		
		String info ;
		switch (aInfo) {
		case ADRESSE:
			info = aPers.getAdresse();
			break;
			
		case VILLE:
			info = aPers.getVille();
			break;
		default:
			info = " Demande invalide !";
			break;
		}
		
		if(info == null || info.equals("") )
		{
			throw new Exception("Champ non renseigné!");
		}
		
		return info;
	}
	
	public String get(Personne aPers, Information aInfo) throws Exception
	{
		return this.get(aPers.getNom(), aPers.getPrenom(), aInfo);
	}
	
	public boolean estPresent(String nom, String prenom)
	{
		return aTreeMap.containsKey(nom+prenom);
	}
	
	@Override
	String getNombreObjets() {
		return super.getNombreObjets()+" taille: "+aTreeMap.size();
	}
}
