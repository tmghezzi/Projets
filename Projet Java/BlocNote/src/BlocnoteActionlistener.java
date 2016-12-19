import java.awt.event.*;
import javax.swing.*;
import java.io.*; 
import java.awt.*;
public class BlocnoteActionlistener implements ActionListener{
	public void Fenetrequite(){
		JButton Revenir,Quitter;
		  Revenir= new JButton("REVENIR");
		  Quitter= new JButton("Quitter");
		  Revenir.addActionListener(new JButtonListener()); 
	Quitter.addActionListener(new JButtonListener()); 

		JFrame msg =new JFrame();
		msg.setTitle("Fermeture");
	    msg.setSize(200,100); 
	    msg.setLayout(new GridLayout(1,2));
	  msg.add(Revenir);
	  msg.add(Quitter);
	  msg.setVisible(true);
	}

	public void actionPerformed(ActionEvent evt){
		String Button = evt.getActionCommand();
if(Button.equals("Ouvrir")){

	 JFileChooser jfilec = new JFileChooser();
     int result = jfilec.showOpenDialog(null);
     if(result == JFileChooser.CANCEL_OPTION) return;
     File file = jfilec.getSelectedFile();
	System.out.println("clic ouvrir");
	System.out.println("Vous avez choisis: " + jfilec.getSelectedFile().getName());

}
if(Button.equals("Quit")){
	Fenetrequite();
	System.out.println("clic quit");
	
}
	}
}