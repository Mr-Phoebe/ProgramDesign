package cn.miniword.test;

import java.awt.Canvas;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.font.FontRenderContext;
import java.awt.font.LineBreakMeasurer;
import java.text.AttributedCharacterIterator;

import javax.swing.JFrame;

public class TestMetrics implements KeyListener{

	/**
	 * 
	 */
	private static final long serialVersionUID = 8645602437882532831L;
	Canvas draw = null;
	private Font font;
	String text = "";
	private JFrame frame;
	
	public TestMetrics()
	{
		frame = new JFrame("Miniword");
		draw = new Canvas();
		draw.addKeyListener(this);
		frame.add("Center",draw);
		frame.setSize(600, 600);
		frame.setVisible(true);
	}
	
	void metricText()
	{
		Graphics graphics = draw.getGraphics();
//		font = graphics.getFont();
		 // get metrics from the graphics
	    FontMetrics metrics = graphics.getFontMetrics();
	    // get the height of a line of text in this font and render context
	    int hgt = metrics.getHeight();
	    // get the advance of my text in this font and render context
	    int adv = metrics.stringWidth(text);
	    // calculate the size of a box to hold the text with some padding.
	    Dimension size = new Dimension(adv+2, hgt+2);
//	    System.out.println("hgt::" + hgt);
//	    System.out.println("adv::" + adv);
//	    System.out.println("size::" + size);
	}
	
//	void metricText2()
//	{
//		AttributedCharacterIterator paragraph = vanGogh.getIterator();
//	    paragraphStart = paragraph.getBeginIndex();
//	    paragraphEnd = paragraph.getEndIndex();
//	    FontRenderContext frc = g2d.getFontRenderContext();
//	    lineMeasurer = new LineBreakMeasurer(paragraph, frc);
//	}

	@Override
	public void keyTyped(KeyEvent e) {
		char ch = e.getKeyChar(); 
		text += ch;
		switch(ch)
		{
		case '\n':
			System.out.println("\\n");
			break;
		case '\r':
			System.out.println("\\n");
			break;
		case '\b':
			System.out.println("\\b");
			break;
		default:
			System.out.println(e.getKeyChar());
			break;
		}
//		System.out.println(text);
		draw.getGraphics().drawString(text, 10, 20);
//		FontMetrics fm = draw.getGraphics().getFontMetrics();
//		System.out.println(fm.getHeight());
//		metricText();
	}

	@Override
	public void keyPressed(KeyEvent e) {
		
	}

	@Override
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub
	}
	
	public static void main(String[] args)
	{
		new TestMetrics();
	}
}
