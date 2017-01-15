


package com.mii.formatuib;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;
import java.util.Scanner;

import javax.swing.JFileChooser;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.ArmEvent;
import org.eclipse.swt.events.ArmListener;
import org.eclipse.swt.events.DisposeEvent;
import org.eclipse.swt.events.DisposeListener;
import org.eclipse.swt.events.HelpEvent;
import org.eclipse.swt.events.HelpListener;
import org.eclipse.swt.events.MenuEvent;
import org.eclipse.swt.events.MenuListener;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.RGB;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.widgets.*;

public class Main {
	private static Text txt1;
	private static String saisie = "";
	private static FileDialog fd ;
	public static void main(String[] args) 
	{
	
		Display display = new Display();
		Shell shell = new Shell(display);
		shell.setSize(900,700);
		
	
		Menu barreMenu = new Menu(shell,SWT.BAR);
		shell.setMenuBar(barreMenu);
		txt1 = new Text(shell,SWT.MULTI | SWT.WRAP);
		txt1.setText("");
		txt1.setLocation(2,2);
		txt1.setSize(shell.getSize());
		
		Listener listener = new Listener() {
			
			@Override
			public void handleEvent(Event e) 
			{
				MenuItem mi = (MenuItem)e.widget ;
				switch(mi.getID())
				{
					case 2:
						//Console
						//System.out.println("Quel fichier voulez vous ouvrir?");
						//Scanner scanLine = new Scanner(System.in);
						//String saisie = "";
						//saisie = scanLine.nextLine();
						//System.out.println("Fichier "+saisie);
						
						/*
						 //Swing
						JFileChooser jfc = new JFileChooser("C:\\Users\\formation\\Desktop\\FormationM2I\\05_SWT_JFace\\10_Menus");
						jfc.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
						jfc.showDialog(null, "MonChoix est fait");
						File objFileSelected = jfc.getSelectedFile();
					
						//tester si l'utilisateur n'a pas clické le bouton
						if(objFileSelected != null && objFileSelected.exists())//Un choix a été fait
						{
							//Récupérer le nom absolu du fichier
							System.out.println(" Nom absolu du fichier choisi: "+objFileSelected.getAbsolutePath());
							//Récupérer le nom court du fichier
							System.out.println(" Nom relatiff du fichier choisi: "+objFileSelected.getName());
							saisie = objFileSelected.getAbsolutePath();
					
						}
						else
						{
							System.out.println("Probléme");
							break;
						}
						*/
						 /*
						if(saisie.equals("") || saisie == null)
						{
							System.out.println("Le nom ne peut pas etre vide");
							break;
						}
						*/
						
						
						 //SWT
						fd = new FileDialog(shell);
						fd.setText("Vueillez choisir un fichier");
						fd.setFilterPath("C:/dev");
						String[] tbExtensions = {"*.txt","*.java","*.*"};
						fd.setFilterExtensions(tbExtensions);
						saisie = fd.open();
						
						if( saisie == null || saisie.equals("") )
						{
							System.out.println("Aucune selection !");
							break;
						}
						
						
						try {
							File objNouveauNom = new File(saisie);
							FileReader fr = new FileReader(objNouveauNom);
							BufferedReader lecteurTampon = new BufferedReader(fr);
							
							String txt;
							String contenu = "";
							while( (txt = lecteurTampon.readLine()) != null)
							{
								contenu += txt+"\n";
							}
							
							System.out.println("Contenu: "+contenu);
							txt1.setText(contenu);
						} catch (FileNotFoundException ex) {
								System.out.println("Le fichier n'existe pas");
								MessageBox messageBox = new MessageBox(shell,SWT.ICON_ERROR);
								messageBox.setMessage("Le fichier n'existe pas");
								messageBox.open();
						}
						catch(IOException ex)
						{
							System.out.println("Erreur de lecture. Messsge d'erreyr: "+ex.getMessage());
						}
					break;
					
					case 3: //Sauvegarder
						if( saisie == null || saisie.equals(""))
						{
							fd = new FileDialog(shell);
							fd.setText("Vueillez choisir un fichier");
							fd.setFilterPath("C:/dev");
							String[] tbExt = {"*.txt","*.java","*.*"};
							fd.setFilterExtensions(tbExt);
							
							saisie = fd.open();
							if( saisie == null || saisie.equals("") )
							{
								System.out.println("Aucune selection !");
								break;
							}
						}
								
						
						PrintStream ps = null;
						try {
							ps = new PrintStream(saisie);
					
							ps.print(txt1.getText());
							//Fermer le flux (le stream)
							ps.close();
							System.out.println("J'ai écrit dans le fichier");
						} catch (FileNotFoundException ex) {
								System.out.println("Le fichier n'existe pas");
						}
						
						
						break;
						
					case 4: //Quitter
						MessageBox messageBox = new MessageBox(shell,SWT.ICON_QUESTION | SWT.YES | SWT.NO | SWT.CANCEL);
						messageBox.setMessage("Voulez-vous vraiment quitter?");
						int reponse = messageBox.open(); 
														
						switch(reponse)
						{
							case SWT.YES:
								System.out.println("A bientot");
								shell.dispose();
								break;
							case SWT.NO:
								System.out.println("C'est bien");
								break;
								
							case SWT.CANCEL:
								System.out.println("Pffff");
								break;
								default:
									throw new RuntimeException("Reponse non traitée");
						}
						
						break;
					case 101:
						
					
					case 102:
						
						
					case 103:
						System.out.println("L'item "+mi.getText() +" est "+ (mi.getSelection() ? "":" non ")+"sélectionné ");
						break;
					case 107:
						ColorDialog cd = new ColorDialog(shell);
						cd.setText("Veuillez choisir une couleur");
						//proposer une couleur par défaut
						cd.setRGB(new RGB(0, 255, 0));
						RGB retour = cd.open();
						if( retour == null)
						{
							System.out.println("Aucune couleur");
						}
						else
						{
							System.out.println("Couleur: "+retour);
							txt1.setForeground(new Color(null,retour.red,retour.green,retour.blue));
							
						}
						break;
					default:
						System.out.println(mi.getText());
						break;
				}
			}
		};
		
		ArmListener armListener = new ArmListener() {
			
			@Override
			public void widgetArmed(ArmEvent e)
			{
				System.out.println("WidgetArmed sur "+e.widget);
				
			}
		};
		
		
		//Créer le 1er MenuItem de la barre de menu 
		MenuItem mi = new MenuItem(barreMenu,SWT.CASCADE);
		mi.setText("Fichier");
		mi.setID(1);
		mi.addArmListener(armListener);
		mi.addListener(SWT.Selection, listener);
		
		
		//Créer la partie déroulante qui sera attribuée à l'item de menu 'Fichier'
		Menu dropdown = new Menu(shell,SWT.DROP_DOWN);
		mi.setMenu(dropdown);
		
		// créer les différents menu items de ce drop down
		MenuItem item = new MenuItem(dropdown,SWT.PUSH);
		item.setText("Ouvrir");
		item.setID(2);
		item.addArmListener(armListener);
		item.addListener(SWT.Selection, listener);
		 
		
		item = new MenuItem(dropdown,SWT.PUSH);
		item.setText("Sauvegarder");
		item.setID(3);
		item.addArmListener(armListener);
		item.addListener(SWT.Selection, listener);
		
		new MenuItem(dropdown,SWT.SEPARATOR);
		
		item = new MenuItem(dropdown,SWT.PUSH);
		item.setText("Quitter");
		item.setID(4);
		item.addArmListener(armListener);
		item.addListener(SWT.Selection, listener);
		
		//ajouter un 2e menu item sur la barre
		mi = new MenuItem(barreMenu,SWT.CASCADE);
		mi.setText("&Autres");
		mi.setID(100);
		mi.addArmListener(armListener);
		mi.addListener(SWT.Selection, listener);
		
		dropdown = new Menu(shell,SWT.DROP_DOWN);
		mi.setMenu(dropdown);
		
		//menuitem avec bouton radio
		item = new MenuItem(dropdown, SWT.RADIO);
		item.setText("Radio 1");
		item.setID(101);
		item.addArmListener(armListener);
		item.addListener(SWT.Selection, listener);
		
		item = new MenuItem(dropdown, SWT.RADIO);
		item.setText("Radio 2");
		item.setID(102);
		item.addArmListener(armListener);
		item.addListener(SWT.Selection, listener);
		
		item = new MenuItem(dropdown, SWT.CHECK);
		item.setText("Check");
		item.setID(103);
		item.addArmListener(armListener);
		item.addListener(SWT.Selection, listener);
		
		item = new MenuItem(dropdown, SWT.PUSH);
		item.setText("Couleur");
		item.setID(107);
		item.addArmListener(armListener);
		item.addListener(SWT.Selection, listener);
		
		
		// créer un menu item avec des sous menus 
		MenuItem cascade = new  MenuItem(dropdown, SWT.CASCADE);
		cascade.setText("&Cascade");
		cascade.setID(104);
		cascade.addArmListener(armListener);
		cascade.addListener(SWT.Selection, listener);
		
		//Créer une nouvelle boite dropdown (qui contiendra les sous menus de l'item 'cascade')
		Menu dropdown2 = new Menu(shell,SWT.DROP_DOWN);
		//affecter ce dropdown au menu cascade
		cascade.setMenu(dropdown2);
		//je voudrais intercepte l'apparition et la disparition du dropdown
		dropdown2.addMenuListener(new MenuListener() {
			
			@Override
			public void menuShown(MenuEvent e) {
				System.out.println("Dropdown2 affiché ");
				
			}
			
			@Override
			public void menuHidden(MenuEvent e) {
				
				System.out.println("Dropdown2 caché ");
			}
		});
		
		
		
		item = new MenuItem(dropdown2, SWT.PUSH);
		
	
		item.setText("&Action\tCtrl+A");
		//Définir l'accélérateur pour cet item (la combinaison de touches qui lance l'action du menu sans cliquer dessus)
		item.setAccelerator(SWT.CTRL + 'A');
		item.setID(105);
		item.addArmListener(armListener);
		item.addListener(SWT.Selection, listener);
		
		item = new MenuItem(dropdown2, SWT.PUSH);
		item.setText("Réaction");
		item.setID(106);
		//ajouter sur ce menu un SelectionListener
		item.addSelectionListener(new SelectionListener() {
			
			@Override
			public void widgetSelected(SelectionEvent e) 
			{
					System.out.println("WidgeSelected sur: "+((MenuItem)e.getSource()).getText());
			}
			
			@Override
			public void widgetDefaultSelected(SelectionEvent e) {
				System.out.println("WidgetDefaultSelected sur: "+((MenuItem)e.getSource()).getText());
			}
		});
		
		item.addArmListener(armListener);
		//ajouter aussi un HelpListener sur cet item de menu 
		item.addHelpListener(new HelpListener() {
			
			@Override
			public void helpRequested(HelpEvent e) {
				System.out.println("Vous devez vous munir de votre carte d'identité avant de continuer");
			}
		});
		
		
		
		shell.addListener(SWT.Close, new Listener() {
			
			@Override
			public void handleEvent(Event e) {
				MessageBox messageBox = new MessageBox(shell,SWT.ICON_QUESTION | SWT.YES | SWT.NO | SWT.CANCEL);
				messageBox.setMessage("Voulez-vous vraiment quitter?");
				int reponse = messageBox.open(); 
											
				switch(reponse)
				{
					case SWT.YES:
						System.out.println("A bientot");
						e.doit = true;
						break;
					case SWT.NO:
						System.out.println("C'est bien ");
						e.doit = false;
						break;	
					case SWT.CANCEL:
						System.out.println("Pffff");
						e.doit = false;
						break;
						default:
							throw new RuntimeException("Reponse non traitée");
				}	
			}
				
		});
		
		shell.open();	
		//exécuter une boucle d'attente d'événement tant que la fenetre n'a pas été fermée
		while(!shell.isDisposed())
		{
			if(!display.readAndDispatch())
				display.sleep();
		}
		
		//fermer le display
		display.close();
	}

}
