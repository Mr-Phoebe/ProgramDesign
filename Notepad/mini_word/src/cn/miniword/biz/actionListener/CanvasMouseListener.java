package cn.miniword.biz.actionListener;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import cn.miniword.biz.MiniwordController;
import cn.miniword.biz.MiniwordController.EventType;
import cn.miniword.model.Coordinate;

public class CanvasMouseListener implements MouseListener, MouseMotionListener {
	public void mousePressed(MouseEvent e){
		MiniwordController.getInstance().setClickPos(new Coordinate(e.getX(), e.getY()));
		MiniwordController.getInstance().handleEvent(EventType.MOUSE_PRESSED);
	}
	public void mouseReleased(MouseEvent e){
		MiniwordController.getInstance().setClickPos(new Coordinate(e.getX(), e.getY()));
		MiniwordController.getInstance().handleEvent(EventType.MOUSE_RELEASED);
	}
	@Override
	public void mouseDragged(MouseEvent e) {
		// TODO Auto-generated method stub
		MiniwordController.getInstance().setClickPos(new Coordinate(e.getX(), e.getY()));
		MiniwordController.getInstance().handleEvent(EventType.MOUSE_DRAGGED);
	}
	@Override
	public void mouseMoved(MouseEvent e) {
		// TODO Auto-generated method stub		
	}
	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		MiniwordController.getInstance().setClickPos(new Coordinate(e.getX(), e.getY()));
		MiniwordController.getInstance().handleEvent(EventType.MOUSE_CLICK);
	}
	@Override
	public void mouseEntered(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
}
