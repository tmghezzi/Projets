package com.mii.formation.container;
/*
 Mini projet Formation MII
*/

public class Main {

	public static void main(String[] args) {
		
		TestPile();
		TestCarnet();
		TestFileDAttente();
		
	}

	
	public static void TestPile() 
	{
		System.out.println("\n--------------Begin Test Pile -------------------");
		 //Création Pile
		 Pile<Integer> aPile = new Pile<Integer>();
		 
		 //Phase 1: On peuple la pile
		for (int i = 1; i <= 10; i++) 
		{
			try
			{
				System.out.println(aPile.getNombreObjets());
				aPile.push(new Integer(i));
				Thread.sleep(1000);
			}
			catch(Exception e)
			{
				System.out.println("Exception : "+e.getMessage());
			}
		}
		
		//Calcul du nombre d'entrée par seconde
		System.out.println("Entrée/s ~="+aPile.getNbMoyenEntreesParSeconde()+ " objet/s");
		
		System.out.println(aPile.getNombreObjets());
		
		//Phase 2: On depeuple la pile avec pop
		for (int i = 0; i < 10; i++) {
			
				try {
					aPile.pop();
					System.out.println(aPile.getNombreObjets());
					Thread.sleep(1000);
				} catch (Exception e) {
					System.out.println("Exception : "+e.getMessage());
				}
				
		}
		
		//Calcul du nombre de sorties par seconde
		System.out.println(" Sortie/s ~="+aPile.getNbMoyenSortiesParSeconde()+ " objet/s");
		
		//Phase 3: On repeuple la pile pour s'assurer que la methode getNbMoyenEntreesParSeconde() fonctionne bien
		for (int i = 1; i <= 10; i++) {
			try
			{
			System.out.println(aPile.getNombreObjets());
			aPile.push(new Integer(i));
			Thread.sleep(1000);
			}
			catch(Exception e)
			{
				System.out.println("Exception : "+e.getMessage());
			}
		}
		
		System.out.println(" Entrée/s ~= "+aPile.getNbMoyenEntreesParSeconde()+ " objet/s");
		
		
		System.out.println("\n--------------End Test Pile -------------------");
	}
	
	
	public static void TestCarnet()
	{

		System.out.println("\n--------------Begin Test Carnet Adresse -------------------");

		CarnetAdresse aCarnet = null;
		Personne aPers1 = null;
		Personne aPers2  = null;
		try {
			
		//Création de personnes pour peupler notre carnet
		aPers1 = new Personne("Johanson", "Scarlett", "16 rue victor hugo", "Paris", "75016");
		aPers2 = new Personne("Bach", "Johann Sebastian", "19 rue des compositeurs", "Paris", "75012");
		
		System.out.println("Personne crée:\n"+aPers1);
		System.out.println("Personne crée:\n"+aPers2);
		
		aCarnet = new CarnetAdresse();
	
		//On peuple notre carnet 
		aCarnet.inserer(aPers1);
		aCarnet.inserer(aPers2);
		
		System.out.println(aCarnet.getNombreObjets());
		System.out.println(" Get CarnetAdresse.Information.VILLE: "+aCarnet.get("Johanson", "Scarlette", CarnetAdresse.Information.VILLE));
		} catch (Exception e) {
			System.out.println("Exception : "+e.getMessage());
		}
		
		try {
			aCarnet.supprimer(aPers2);
		} catch (Exception e) {
			System.out.println("Exception : "+e.getMessage());
		}
		System.out.println("Aprés suppression de aPers2: "+aCarnet.getNombreObjets());
		System.out.println("\n--------------End Test Carnet Adresse -------------------");
		
	}
	
	public static void TestFileDAttente()
	{
		System.out.println("\n--------------Begin Test file Attente -------------------");
		Personne aPers3 = new Personne("Miyamoto", "Musashi", "19 rue la victoire", "Paris", "75016");
		Personne aPers4 = new Personne("Zinedine", "Zidane", "156 cité de La Castellane", "Marseille", "13000");
		
		//Création file Attente
		FileAttente<Personne> aFileAtt = new FileAttente<Personne>();
		//peupler la file d'attente
		aFileAtt.ajouter(aPers3);
		
		System.out.println(aFileAtt.getNombreObjets());
		
		try {
			//Cela devrait lever une exception car la taille de la file d'attente est inférieur à 33
			System.out.println("Peek: "+aFileAtt.peek(33));
		} catch (Exception e) {
			System.out.println("Message Exception: "+e.getMessage()+aFileAtt.getNombreObjets());
		}
		
		
		try {
			Thread.sleep(1000);
			System.out.println(aFileAtt.retirer());
		} catch (Exception e) {
			System.out.println("Exception : "+e.getMessage());
		}
		
		aFileAtt.ajouter(aPers4);
		
		try {
			Thread.sleep(3000);
		} catch (InterruptedException e) {
			
		}
		
		System.out.println("getObjetAttente(0): "+aFileAtt.getObjetAttente(0)+" seconde(s)");
		
		System.out.println("Moyenne attente dans la file: ~= "+aFileAtt.getAttenteMoyenne()+" seconde(s),"
				+ " getNbMoyenSortiesParSeconde "+aFileAtt.getNbMoyenSortiesParSeconde()+ " objet/s");
		System.out.println("\n--------------End Test file Attente -------------------");
	}
}
