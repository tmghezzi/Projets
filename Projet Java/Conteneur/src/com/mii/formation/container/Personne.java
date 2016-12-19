package com.mii.formation.container;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Personne {
	private String nom = ""; 
	private String prenom= "";
	private String adresse = "";
	private String ville = "" ;
	private String codePostal = "";

	public Personne(String nom, String prenom)
	{ 
		if( !estArgumentValide(nom,2) )
			throw new IllegalArgumentException("Le nom ne convient pas !!!");
		
		this.nom = nom.trim();
		
		if( !estArgumentValide(prenom,2) )
			throw new IllegalArgumentException("Le prénom ne convient pas !!!");
		
		this.prenom = prenom.trim();
	}

	public Personne(String nom, String prenom, String adresse) {
		this(nom,prenom);
		if( !estArgumentValide(adresse,6) )
			throw new IllegalArgumentException("L'adresse ne convient pas !!!");
		this.adresse = adresse.trim();
	}
	
	
	public Personne(String nom, String prenom, String adresse,String ville) {
		this(nom,prenom,adresse);
		if( !estArgumentValide(ville,2) )
			throw new IllegalArgumentException("La ville ne convient pas !!!");
		this.ville = ville.trim();
	}
	
	public Personne(String nom, String prenom, String adresse,String ville, String codePostale) {
		this(nom,prenom,adresse,ville);
		if( !estCodePostalFrValide(codePostale) )
			throw new IllegalArgumentException("Le code postal ne convient pas !!!");
		this.codePostal = codePostale.trim();
	}
	
	private boolean estArgumentValide(String arg,int cond)
	{
		return arg != null && arg.length() >= cond;
	}
	
	
	private boolean estCodePostalFrValide(String arg)
	{
		//On vérifie si le code postal tiens sur 5 chiffres
		Pattern pattern = Pattern.compile("^[0-9]{5}$"); 
		Matcher match = pattern.matcher(arg);
		return match.find();
	}

	public String getNom() {
		return nom;
	}

	public void setNom(String nom) {
		this.nom = nom;
	}

	public String getPrenom() {
		return prenom;
	}

	public void setPrenom(String prenom) {
		this.prenom = prenom;
	}

	public String getAdresse() {
		return adresse;
	}

	public void setAdresse(String adresse) {
		this.adresse = adresse;
	}

	public String getVille() {
		return ville;
	}

	public void setVille(String ville) {
		this.ville = ville;
	}

	public String getCodePostal() {
		return codePostal;
	}

	public void setCodePostal(String codePostal) {
		this.codePostal = codePostal;
	}
	
	@Override
	public String toString()
	{
		return "Nom: "+nom+", prenom: "+prenom+"\nAdresse: "+adresse+", ville: "+ville+", code postale: "+codePostal;
	}
}
