package cn.miniword.biz;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.util.List;

import javax.swing.JFrame;

import cn.miniword.model.Coordinate;
import cn.miniword.view.MiniWordFrame;

public class FrameController{
	MiniWordFrame miniWordFrame = new MiniWordFrame();
	public static final int X_BASE = 10;
	public static final int Y_BASE = 20;
	private static final int PADDING = 0;
	public boolean selectFlag = false;
	public static final Coordinate COO_BASE = new Coordinate(X_BASE,Y_BASE);
	private static final Dimension defaultDimention = new Dimension(MiniWordFrame.PREFER_X,MiniWordFrame.PREFER_Y);
	public FrameController getInstance(){
		return new FrameController();
	}
	
	public void clear() {
		Dimension frameSize = miniWordFrame.getSize();
		miniWordFrame.getTextArea().getGraphics().clearRect(0,0, frameSize.width, frameSize.height);
	}
	public void showText(Coordinate a, Coordinate b, List<String> content) {
		Graphics g = miniWordFrame.getTextArea().getGraphics();
		int height = g.getFontMetrics().getHeight();
		FontMetrics fm = g.getFontMetrics();
		/*若有拖拽事件则画选择框*/
		if (selectFlag){
			Coordinate ta = new Coordinate(a.getX(),a.getY());
			Coordinate tb = new Coordinate(b.getX(),b.getY());
			if (a.getX() > b.getX() || (a.getX() == b.getX() && a.getY() > b.getY())){
				ta.setX(b.getX());
				ta.setY(b.getY());
				tb.setX(a.getX());
				tb.setY(a.getY());
			}
			int ax = ta.getX(), bx = tb.getX(), by = tb.getY();
			while (bx > ax){
				/*画当前行的矩形框*/
				Coordinate drawa = new Coordinate(0,0);
				drawa.setX(bx);
				drawa.setY(0);
				drawa = transferString2Pixel(drawa, content);
				tb = transferString2Pixel(tb, content);	
				g.setColor(new Color(190,170,190));
				g.fillRect(drawa.getX()+ PADDING, drawa.getY() - fm.getAscent(), tb.getX() - drawa.getX(), 25);
				by = content.get(--bx).length();
				tb.setX(bx);
				tb.setY(by);
			}/*while*/
			ta = transferString2Pixel(ta, content);
			tb = transferString2Pixel(tb, content);
			g.setColor(new Color(190,170,190));
			g.fillRect(ta.getX()+ PADDING, ta.getY() - fm.getAscent(), tb.getX() - ta.getX(), 25);
		}/*if (flag)*/
		for(int lineNum = 0; lineNum < content.size(); lineNum++){
			String lineContent = content.get(lineNum);
			miniWordFrame.getTextArea().getGraphics().drawString(lineContent,
					FrameController.X_BASE, FrameController.Y_BASE + height * lineNum);
		}
//		miniWordFrame.getTextArea().setPreferredSize(new Dimension(width, height));
	}	
	public void showCursor(Coordinate cursorPixel)
	{
		Graphics g = miniWordFrame.getTextArea().getGraphics();
		FontMetrics fm = g.getFontMetrics();
		g.drawLine(cursorPixel.getX() + PADDING, cursorPixel.getY() - fm.getAscent(),
				cursorPixel.getX() + PADDING, cursorPixel.getY() + fm.getDescent());
	}
	
	public  Coordinate transferPixel2String(Coordinate coo, List<String> buffer)
	{
		if(buffer == null || buffer.isEmpty() || coo == null)
			return COO_BASE;
		int x = coo.getX();
		int y = coo.getY();
		int relativeX = (x - FrameController.X_BASE < 0) ? 0 : x - FrameController.X_BASE;
		int relativeY = (y - FrameController.Y_BASE < 0) ? 0 : y - FrameController.Y_BASE;
		FontMetrics fm = miniWordFrame.getTextArea().getGraphics().getFontMetrics();
		int height = fm.getHeight();
		int lineNum = relativeY / height;
		int lastLine = (buffer.size() - 1 < 0) ? 0 : (buffer.size() - 1);
		int opLine = (lineNum <= lastLine) ? lineNum : lastLine;
		String str = buffer.get(opLine);
		int index;
		for(index = str.length(); index > 0; index--){
			int len = fm.stringWidth(str.substring(0, index));
			if(len < relativeX){
				if(index < str.length()){
					len = len + fm.charWidth(str.charAt(index)) / 2;
					if(len < relativeX)
						index ++;
				}/*if*/
				return new Coordinate(opLine, index);
			}/*if*/
		}/*for*/
		return new Coordinate(opLine,0);
	}
	
	public Coordinate transferString2Pixel(Coordinate coo, List<String> buffer)
	{
		if(buffer == null || buffer.isEmpty())
			return COO_BASE;
		FontMetrics fm = miniWordFrame.getTextArea().getGraphics().getFontMetrics();
		int height = fm.getHeight();
		int y = FrameController.Y_BASE + coo.getX() * height;
		int x = FrameController.X_BASE + fm.stringWidth(buffer.get(coo.getX()).substring(0,coo.getY()));
		return new Coordinate(x, y);
	}
	
	public void setTitle(String title)
	{
		miniWordFrame.setTitle(title);
	}
	
	public String getTitle()
	{
		return miniWordFrame.getTitle();
	}

	public void doNotCloseWindow() {
		miniWordFrame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
	}
	
	public void setDimensionByContent(List<String> content)
	{
		if(content == null || content.isEmpty())
			miniWordFrame.setPreferredSize(defaultDimention);
		int height;
		FontMetrics fm = miniWordFrame.getTextArea().getGraphics().getFontMetrics();
		int lineHight = fm.getHeight();
		height = FrameController.Y_BASE + lineHight * (content.size() - 1);
		int maxLength = 0;
		for(String str : content){
			int len = fm.stringWidth(str);
			if(len > maxLength)
				maxLength = len;
		}
		int xDimension = maxLength > defaultDimention.width ? maxLength : defaultDimention.width;
		int yDimension = height > defaultDimention.height ? height : defaultDimention.height;
//		System.out.println("xDimension::"+xDimension + " yDimention::" + yDimension );
		miniWordFrame.getTextArea().setPreferredSize(new Dimension(xDimension, yDimension));
	}
	
	public void setDefaultDimension()
	{
		miniWordFrame.getTextArea().setPreferredSize(defaultDimention);
	}
}
