import java.awt.event.*;

public class BlocNoteslistener implements WindowListener{

	public void windowClosed(WindowEvent evt) {
        System.out.println("Fenetre fermer");
    }
    public void windowActivated(WindowEvent evt) {
        System.out.println("Fenetre Active");
    }
    public void windowClosing(WindowEvent evt) {
        System.out.println("Fenetre en cours de fermeture");
    }
    public void windowDeactivated(WindowEvent evt) {
        System.out.println("Fenetre désactivé");
    }
    public void windowDeiconified(WindowEvent evt) {
        System.out.println("Fenetre agrandit");
    }
    public void windowIconified(WindowEvent evt) {
        System.out.println("Fenetre réduite");
    }
    public void windowOpened(WindowEvent evt) {
        System.out.println("Fenetre ouverte");
    }
    public void mouseposition(WindowEvent evt) {
        System.out.println("Fenetre fermer");
    }
}