
import java.awt.event.*;
import javax.swing.*;

public class JMenuItemBlocNotes extends JMenuItem {
	
public JMenuItemBlocNotes(String nom,int evt){
	super(nom);
	this.addActionListener(new BlocnoteActionlistener());
	
	}

}