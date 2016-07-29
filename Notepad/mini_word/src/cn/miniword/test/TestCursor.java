package cn.miniword.test;

import java.applet.Applet;
import java.awt.Cursor;
import java.util.*;

public class TestCursor extends Applet{
	/**
	 * 
	 */
	private static final long serialVersionUID = 971256154524566886L;

	public void init()
	{
		setCursor(Cursor.getPredefinedCursor(Cursor.TEXT_CURSOR));
	}
	
	public static void main(String[] args)
	{
		new TestCursor();
	}
}
