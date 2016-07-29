package cn.miniword.model;

import java.util.List;

import javax.swing.JOptionPane;

import cn.miniword.biz.MiniwordController;

public class StringFinder {
	private List<String> buffer;
	private String target;
	private Coordinate cursor ;
	private MiniwordController Controller;

	public StringFinder(List<String> buffer, Coordinate cursor)
	{
		this.buffer = buffer;
		this.cursor = cursor;
	}
	
	private void find()
	{
		/*若无查找数据则直接返回*/
		if(buffer == null || buffer.isEmpty())
			return;
		int start = cursor.getX();
		int end = buffer.size() ;
		int col = cursor.getY();
		int index = buffer.get(start).substring(col).indexOf(target);
		/*若在第一行找到数据则更新鼠标信息*/
		if(index > -1){
			this.Controller.setCursorStringCoo(new Coordinate(start, col + index + target.length()));
			this.Controller.setTemp(new Coordinate(start, col + index));
			this.Controller.getFrameController().selectFlag = true;
			return ;
		}
		/*从第二行开始查找*/
		for(int i = start + 1; i < end; i++)
		{
			int pos = buffer.get(i).indexOf(target);
			/*若找到则更新鼠标信息*/
			if(pos > -1){
				this.Controller.setCursorStringCoo(new Coordinate(i, pos + target.length()));
				this.Controller.setTemp(new Coordinate(i, pos));
				this.Controller.getFrameController().selectFlag = true;
				return ; 
			}
		}
		return;
	}
	
	public void findString()
	{
		String inputString = JOptionPane.showInputDialog("查找内容：");
		if(inputString != null){
			target = inputString;
			find();
		}
		return ;
	}

	public MiniwordController getController() {
		return Controller;
	}

	public void setController(MiniwordController controller) {
		Controller = controller;
	}

}
