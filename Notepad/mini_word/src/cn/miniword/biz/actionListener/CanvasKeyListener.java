package cn.miniword.biz.actionListener;

import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import cn.miniword.biz.MiniwordController;
import cn.miniword.biz.MiniwordController.EventType;

public class CanvasKeyListener extends KeyAdapter {
	boolean delete = false;
	boolean ctrl = false;
	@Override	
	
	public void keyPressed(KeyEvent e) {
		if (ctrl == true){
			switch (e.getKeyCode()){
				case KeyEvent.VK_HOME:
					MiniwordController.getInstance().handleEvent(EventType.TO_HEAD);
					break;
				case KeyEvent.VK_END:
					MiniwordController.getInstance().handleEvent(EventType.TO_END);
					break;
			}
		}
			
		if (isSpecialKey(e)){
			int code = e.getKeyCode();
			if (code == KeyEvent.VK_DELETE)	delete = true;
			if (code == KeyEvent.VK_CONTROL)ctrl = true;
			else{
			MiniwordController.getInstance().setInputCode(code);
			MiniwordController.getInstance().handleEvent(EventType.KEY_PRESSED);
			}
		}
	}
	public void keyReleased (KeyEvent e){
		if (e.getKeyCode() == KeyEvent.VK_CONTROL)	ctrl = false;
	}
	public void keyTyped(KeyEvent e) {
		if (!delete && !e.isControlDown()){
			MiniwordController.getInstance().setInputChar(e.getKeyChar());
			MiniwordController.getInstance().handleEvent(EventType.KEY_TYPED);
		}
		delete = false;
	}
	public boolean isSpecialKey (KeyEvent e){
		int code = e.getKeyCode();
		if (code != KeyEvent.VK_DELETE && code != KeyEvent.VK_INSERT && code != KeyEvent.VK_HOME && code != KeyEvent.VK_END &&
				code != KeyEvent.VK_UP && code != KeyEvent.VK_DOWN && code != KeyEvent.VK_LEFT && code != KeyEvent.VK_RIGHT && code != KeyEvent.VK_CONTROL)
			return false;
		else
			return true;
	}
}
