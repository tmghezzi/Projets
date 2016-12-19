import javax.swing.*;
import java.awt.*;

public class Remplacer extends JFrame {
	
	public Remplacer (){
		setTitle("Remplacer");
        setSize(500, 500);   
       JPanel panelRecherche,panelBouton,panelChamptext,panelRemplacer,panelHaut,panelBas;
       panelBas=new JPanel();
       panelHaut=new JPanel();
       panelChamptext= new JPanel();
       panelBouton=new JPanel();
       panelRecherche=new JPanel();
       panelRemplacer=new JPanel();
       setLayout(new GridLayout(2,1));
       this.add(panelHaut);
       this.add(panelBas);
       panelHaut.setLayout(new GridLayout(1,2));
panelChamptext.setLayout(new BoxLayout(panelChamptext,BoxLayout.Y_AXIS));
panelBouton.setLayout(new BoxLayout(panelBouton,BoxLayout.Y_AXIS));
panelRecherche.setLayout(new BoxLayout(panelRecherche,BoxLayout.X_AXIS));
panelRemplacer.setLayout(new BoxLayout(panelRemplacer,BoxLayout.X_AXIS));
panelBas.setLayout(new BoxLayout(panelBas,BoxLayout.Y_AXIS));
panelHaut.add(panelChamptext);
panelHaut.add(panelBouton);
panelChamptext.add(panelRecherche);
panelChamptext.add(panelRemplacer);
JLabel label1 = new JLabel("Recherche: ");
JTextField recherche=new JTextField(30);
panelRecherche.add(label1);
panelRecherche.add(recherche);
JLabel label = new JLabel("Remplacer par: ");
JTextField remplacerpar=new JTextField(30);
panelRemplacer.add(label);
panelRemplacer.add(remplacerpar);
JButton btn1,btn2,btn3,btn4;
btn1=new JButton("Suivant");
btn2=new JButton("Remplacer");
btn3=new JButton("Remplacer Tout");
btn4=new JButton("annuler");
Dimension d= new Dimension(20,20);
Dimension d1= new Dimension(60,60);
btn1.setMinimumSize(d);

panelBouton.add(btn1);
panelBouton.add(Box.createRigidArea(d));
panelBouton.add(btn2);
panelBouton.add(Box.createRigidArea(d));
panelBouton.add(btn3);
panelBouton.add(Box.createRigidArea(d));
panelBouton.add(btn4);
JCheckBox c1=new JCheckBox("Respecter les cases");
panelBas.add(c1);

         setVisible(true);
	
	}

	
	}