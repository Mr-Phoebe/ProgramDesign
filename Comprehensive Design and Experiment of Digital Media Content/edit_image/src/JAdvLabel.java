/**
 * Created by SuPhoebe on 2016/10/20.
 */
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
public class JAdvLabel extends JLabel implements MouseMotionListener{
	final int ZOOM_MAX_W_H=60;
	BufferedImage buffered_image;
	BufferedImage abuffered_image;
	ImageIcon image_icon;
	String filename;
	 /**
     * 当前图像的宽度和高度
     */
	int width,height;
	/**
     * 当前放大镜的起始坐标
     */
	int magX,magY;
	 /**
     * 是否显示放大镜的标志。
     */
	boolean showf=false;
	public JAdvLabel(String filename){
		this.filename=filename;
		setImageIcon(new ImageIcon(filename));
		addMouseMotionListener(this);
	}
	public JAdvLabel(){
		super();
		addMouseMotionListener(this);
	}
	public void setImageIcon(ImageIcon icon){
		image_icon=icon;
		width=icon.getIconWidth();
		height=icon.getIconHeight();
		buffered_image=new BufferedImage(
				width,height,BufferedImage.TYPE_INT_BGR);
		buffered_image.getGraphics()
		.drawImage(image_icon.getImage(),0,0,null);
		abuffered_image=new BufferedImage(
				width,height,BufferedImage.TYPE_INT_ARGB);
		abuffered_image.getGraphics()
		.drawImage(image_icon.getImage(),0,0,null);
		setIcon((Icon)icon);
	}
	public void paint(Graphics g){
		super.paint(g);
		if(showf){
			g.setColor(Color.red.darker());
			g.drawRect(magX, magY, ZOOM_MAX_W_H+2, ZOOM_MAX_W_H+2);
			int sx1=magX-ZOOM_MAX_W_H/4;
			int sy1=magY-ZOOM_MAX_W_H/4;
			int sx2=sx1+ZOOM_MAX_W_H/2;
			int sy2=sy1+ZOOM_MAX_W_H/2;
			if(sx1<0){
				sx1=0;
				sx2=ZOOM_MAX_W_H/2;
			}
			if(sy1<0){
				sy1=0;
				sy2=ZOOM_MAX_W_H/2;
			}
			g.drawImage(
					buffered_image,magX+1,magY+1
					,magX+ZOOM_MAX_W_H+2,magY+ZOOM_MAX_W_H+2,
					sx1,sy1,sx2,sy2,null);
		}
	}
	public void showf(boolean show){
		showf=show;
		repaint();
	}
	public boolean isshowf(){
		return showf;
	}
	public void mouseDragged(MouseEvent e){

	}
	public void mouseMoved(MouseEvent e){
		if((showf)&&e.getX()<=width&&e.getY()<=height){
			magX=e.getX();
			magY=e.getY();
			repaint();
		}
	}
}

