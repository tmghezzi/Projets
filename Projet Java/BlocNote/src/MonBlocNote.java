import javax.swing.*;
import java.io.*; 
import java.awt.*;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

public class MonBlocNote extends JFrame {

 private JMenuBar BarreMenu;
 private  File fichier;
	public MonBlocNote (String titre){
	
		 JTextArea zonetext= new JTextArea();
		 JScrollPane scroll=new JScrollPane(zonetext);
		 add(scroll);
		 fichier=new File("/home/admin/Bureau/nouveau dossier/sde.txt");
			if(fichier.exists()){
				if(fichier.canRead()){
					String leTexte="";
					String chaine;
					try{
						BufferedReader buffer=new BufferedReader(new FileReader(fichier));
						while((chaine = buffer.readLine())!=null){
								leTexte+=chaine+"\n";
							 
						}
						zonetext.insert(leTexte,0);
				}
	catch(IOException except){
						System.err.println("Erreur lors de l'ouverture du fichier");
					}
			}
		
		}
			
		 setTitle(titre);
         setSize(800, 800);
         MenuFichier MonFichier= new MenuFichier();
		 BarreMenu = new JMenuBar();
		 BarreMenu.add(MonFichier);
		 setJMenuBar(BarreMenu);
         setVisible(true);
         addWindowListener(new BlocNoteslistener());
     }

		
}



