package com.mii.formation.container;

public abstract class MonContainer {
	//Alternative
	//protected int nbObjets;
	String getNombreObjets() {
		String typeName = getClass().getSimpleName();
		return "Type de container: "+typeName;
	}
}
