   import java.awt.event.*;
    public  class   JButtonListener implements   ActionListener
    {
		
        public  void    actionPerformed(ActionEvent evt)
        {
    		String Button = evt.getActionCommand();
    		if(Button.equals("REVENIR")){
    			System.out.println("Retour au bloc note");
    		}
    	if(Button.equals("Quitter")){
    		System.out.println("Fermeture du bloc note");
    		System.exit(0);
    	}
    		}
         
        }
    