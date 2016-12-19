
import java.awt.event.*;
import javax.swing.*;


public class MenuFichier extends JMenu {
private JMenuItemBlocNotes menuNouveau,menuOuvrir,menuEnregistrer,menuEnregistrerSous,menuImprimer,menuQuit,menuMiseEnpage;
public MenuFichier(){
 setText("Fichier");
 menuNouveau=new JMenuItemBlocNotes("Nouveau",KeyEvent.VK_N);
 menuNouveau.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N, ActionEvent.CTRL_MASK));
  add(menuNouveau);
  menuOuvrir=new JMenuItemBlocNotes("Ouvrir",KeyEvent.VK_O);
  menuOuvrir.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, ActionEvent.CTRL_MASK));
  add(menuOuvrir);
  addSeparator();
  menuEnregistrer=new JMenuItemBlocNotes("Enregistrer",KeyEvent.VK_S);
  menuEnregistrer.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, ActionEvent.CTRL_MASK));
  add(menuEnregistrer);
  menuEnregistrerSous=new JMenuItemBlocNotes("Enregistrer-Sous",0);
  add(menuEnregistrerSous);
  addSeparator();
  menuMiseEnpage=new JMenuItemBlocNotes("Mise en page",0);
  add(menuMiseEnpage);
  menuImprimer=new JMenuItemBlocNotes("Imprimer",KeyEvent.VK_P);
  menuImprimer.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_P, ActionEvent.CTRL_MASK));
  add(menuImprimer);
  addSeparator();
  menuQuit=new JMenuItemBlocNotes("Quit",KeyEvent.VK_Q);
  menuQuit.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_Q, ActionEvent.CTRL_MASK));
  add(menuQuit);



 
  }
}