package cn.miniword.biz.actionListener;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import cn.miniword.biz.MiniwordController;
import cn.miniword.biz.MiniwordController.EventType;

public class OpenFileListener implements ActionListener {

	@Override
	public void actionPerformed(ActionEvent e) {
		MiniwordController.getInstance().handleEvent(EventType.OPEN_FILE);;
	}
}
