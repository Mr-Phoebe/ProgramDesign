package cn.miniword.biz;

import java.awt.event.KeyEvent;
import java.io.File;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JOptionPane;

import cn.miniword.model.Coordinate;
import cn.miniword.model.StringFinder;
import cn.miniword.model.edit.EditList;
import cn.miniword.util.EditUtility;
import cn.miniword.util.FileUtility;

public class MiniwordController extends Thread{
	private String filePath = null;
	private boolean notSaved = false;
	private static final MiniwordController instance = new MiniwordController();
	private Coordinate cursorPixelCoo = null;
	private Coordinate cursorStringCoo = null;
	private Coordinate temp = null;
	private char inputChar ;
	private int  inputCode;
	private FrameController frameController = null;
	
	private List<String> content = null;
	private boolean starFlag = false;
	private static final String defaultTile = "无标题 - Miniword";
	private EditList editor = new EditList();
	private int ax,bx,ay,by;
	
	private boolean ch = false;
	//定义可以接受的用户输入
	public static enum EventType{
		/*新建文件*/
		NEW_FILE,
		/*打开文件*/
		OPEN_FILE,
		/*保存文件*/
		SAVE_FILE,
		/*文件另存为*/
		SAVE_AS,
		/*退出*/
		QUIT,
		/*用户键盘输入单个字符*/
		KEY_TYPED,
		/*用户按下键盘*/
		KEY_PRESSED,
		/*用户松开键盘*/
		KEY_RELEASED,
		/*用户单击鼠标*/
		MOUSE_CLICK,
		/*用户按下鼠标*/
		MOUSE_PRESSED,
		/*用户松开鼠标*/
		MOUSE_RELEASED,
		/*用户拖拽鼠标*/
		MOUSE_DRAGGED,	
		/*查找字符串*/
		FIND_STR,
		/*复制*/
		COPY_MODULE,
		/*粘贴*/
		PASTE_MODULE,
		/*剪切*/
		CUT_MODULE,
		/*全选*/
		SELECT_ALL,
		/*替换*/
		REPLACE,
		/*定位文件头*/
		TO_HEAD,
		/*定义文件尾*/
		TO_END
	}

	public void init(){
		frameController = new FrameController();
		notSaved = false;
		clear();
		start();
		handleEvent(EventType.NEW_FILE);
	}
	
	public void clear(){
		content = new ArrayList<String>();
		content.add("");
		/*光标位置设为控制模块的信息*/
		cursorPixelCoo = FrameController.COO_BASE;
		/*数据位设为起始原点*/
		cursorStringCoo = Coordinate.ZERO;
	}
	
	public static MiniwordController getInstance(){
		return instance;
	}
	
	public void handleEvent(EventType event){
		
		switch(event){
		case NEW_FILE:
			newFile();
			break;
			
		case OPEN_FILE:
			openFile();
			break;
			
		case SAVE_FILE:
			saveFile();
			break;
			
		case SAVE_AS:
			saveAs();
			break;
			
		case QUIT:
			quit();
			break;
			
		case MOUSE_CLICK:
			calCursorCharPos();
			/*设置绘画标志为假*/
			frameController.selectFlag = false;
//			System.out.println("MOUSE_CLICK：："+"("+ cursorStringCoo.getX()+","+cursorStringCoo.getY()+")");
			break;
		
		case MOUSE_PRESSED:
			frameController.selectFlag = false;
			calCursorCharPos();
			/*记录下按下时的起始坐标位置*/
			temp = cursorStringCoo;
			/*设置绘画标志为真*/
			frameController.selectFlag = true;
			break;
			
		case MOUSE_RELEASED:
			calCursorCharPos();
			/*若松开位置和按下位置在同一个位置时则取消选中状态*/
			if (temp.getX() == cursorStringCoo.getX() && temp.getY() == cursorStringCoo.getY()){
				frameController.selectFlag = false;
			}
			break;
			
		case MOUSE_DRAGGED:
			calCursorCharPos();
			break;
			
		case KEY_TYPED:
			getTextAfterKeyTyped();
			break;
			
		case KEY_PRESSED:
			getTextAfterKeyPressed();
			break;
			
		case COPY_MODULE:
			/*若不是选中状态则不进行复制*/
			if (!frameController.selectFlag)	break;
			sort();
			editor.copyModule(ax, ay, bx, by);
			break;
			
		case PASTE_MODULE:
			/*若缓存区无内容则不操作*/
			if (!editor.isCopyFlag())		break;
			/*若是选中状态且缓存区有内容则删除选中的内容*/
			if (frameController.selectFlag && editor.isCopyFlag()){
				sort();
				editor.delModule(ax, ay, bx, by);
				cursorStringCoo = editor.getMouse();
			}
			editor.pasteModule(cursorStringCoo.getX(), cursorStringCoo.getY());
			update();
			break;
		case CUT_MODULE:
			/*复制*/
			if (!frameController.selectFlag)	break;
			sort();
			editor.copyModule(ax, ay, bx, by);
			/*删除*/
			editor.delModule(ax, ay, bx, by);
			update();
			break;
		case FIND_STR:
			findString();
			break;
			
/*		case REPLACE:
			new Replace();
			break;
*/			
		case SELECT_ALL:
			frameController.selectFlag = true;
			cursorStringCoo = new Coordinate(content.size()-1,content.get(content.size()-1).length());
			temp = new Coordinate(0, 0);
			frameController.clear();
			frameController.showText(temp, cursorStringCoo, content);
			cursorPixelCoo = frameController.transferString2Pixel(cursorStringCoo, content);
			frameController.showCursor(cursorPixelCoo);
			break;
			
		case TO_HEAD:
			cursorStringCoo = new Coordinate(0,0);
			frameController.clear();
			frameController.showText(temp, cursorStringCoo, content);
			cursorPixelCoo = frameController.transferString2Pixel(cursorStringCoo, content);
			frameController.showCursor(cursorPixelCoo);
			break;
			
		case TO_END:
			cursorStringCoo = new Coordinate(content.size()-1,content.get(content.size()-1).length());
			frameController.clear();
			frameController.showText(temp, cursorStringCoo, content);
			cursorPixelCoo = frameController.transferString2Pixel(cursorStringCoo, content);
			frameController.showCursor(cursorPixelCoo);
			break;
		default:
//			System.err.println("unknown handle event");
			break;
		}
	}

	private void sort() {
		// TODO Auto-generated method stub
		ax = temp.getX();
		ay = temp.getY();
		bx = cursorStringCoo.getX();
		by = cursorStringCoo.getY();
		if (ax > bx || (ax == bx && ay > by)){
			ax = cursorStringCoo.getX();
			ay = cursorStringCoo.getY();
			bx = temp.getX();
			by = temp.getY();
		}
	}

	private void findString() {
//		Coordinate tmp = new StringFinder(content,cursorStringCoo).findString();
		StringFinder find = new StringFinder(content,cursorStringCoo);
		find.setController(this);
		find.findString();
//		if (tmp != null){
//			cursorStringCoo = tmp;
			cursorPixelCoo = frameController.transferString2Pixel(cursorStringCoo, content);
//		}
		frameController.showCursor(cursorPixelCoo);
	}

	private void newFile(){
		if(querySave() != JOptionPane.CANCEL_OPTION){
			frameController.clear();
			clear();
			setNotSaveAndTitle(true, defaultTile);
			refreshFrame();
			frameController.setDefaultDimension();
			editor = new EditList();
		}
	}
	/**
	 * 打开文件
	 */
	private void openFile() {
		if(querySave() != JOptionPane.CANCEL_OPTION){
			File file = FileUtility.openFile();
			if(file != null){
				setFilePath(file.getAbsolutePath());
				//读取文件内容并在界面上显示。
				frameController.clear();
				setContent(FileUtility.readFileContent(file));
				frameController.showText(temp, cursorStringCoo, getContent());
				setNotSaveAndTitle(false, file.getName());
				refreshFrame();
				editor = EditUtility.listToEditList(content);
				frameController.setDimensionByContent(content);
			}
		}
	}

	/**
     * 保存文件
     */
	private void saveFile() {
		String fileName = FileUtility.saveFile(filePath, getContent());
		/*若文件名不为空则讲文件修改标志改为假*/
		if (fileName != null)
			setNotSaveAndTitle(false, fileName);
		else
			notSaved = true;
		refreshFrame();
	}

	/**
	 * 文件另存为
	 */
	private void saveAs() {
		String fileName = FileUtility.saveAs(getContent());
		/*若文件名不为空则讲文件修改标志改为假*/
		if (fileName != null)
			setNotSaveAndTitle(false, fileName);
		refreshFrame();
	}

	/**
	 * 退出系统，若退出前有未保存的编辑内容，需要先执行save操作再退出。
	 */
	private void quit() {
		int choice = querySave();
		/*若是取消按键则不操作操作*/
		if (choice == JOptionPane.CANCEL_OPTION){
			frameController.doNotCloseWindow();
			return;
		}
		if (choice == JOptionPane.YES_OPTION){
			/*若保存成功则退出，否则不操作*/
			if (!notSaved)		System.exit(0);
			else				frameController.doNotCloseWindow();
		}
		else
			System.exit(0);
	}
	
	private int querySave()
	{
		if(!hasNotSaved())
			return JOptionPane.NO_OPTION;
		int usrChoice = confirmSave();
		if(usrChoice == JOptionPane.YES_OPTION){
			saveFile();
			return JOptionPane.YES_OPTION;
		}
		return usrChoice;
	}
	
	private int confirmSave()
	{
		 int rst =  JOptionPane.showConfirmDialog(null, "是否保存当前文件？"); 
		 return rst;
	}
	
	/**
	 * @param c 鼠标点击的像素坐标
	 * 计算鼠标的字符坐标
	 * 刷新页面
	 */
	private void calCursorCharPos() {
		//通过像素坐标计算字符坐标。
		 cursorStringCoo = frameController.transferPixel2String(cursorStringCoo, content);
		 //界面清屏。
		 frameController.clear();
		//界面显示。
		 frameController.showText(temp, cursorStringCoo, content);
		 cursorPixelCoo = frameController.transferString2Pixel(cursorStringCoo, content);
		 frameController.showCursor(cursorPixelCoo);
	}
	
	/**
	 * 调用模型层得到输入后的文本内容以及光标位置
	 */
	private void getTextAfterKeyTyped()
	{
		if (frameController.selectFlag){
			int ax = temp.getX(), ay = temp.getY(), bx = cursorStringCoo.getX(), by = cursorStringCoo.getY();
			if (ax > bx || (ax == bx && ay > by)){
				ax = cursorStringCoo.getX();
				ay = cursorStringCoo.getY();
				bx = temp.getX();
				by = temp.getY();
			}
//			System.out.println("HERE"+"ax:"+ax+"  ay:"+ay+"  bx:"+bx+"  by:"+by);
			editor.delModule(ax, ay, bx, by);
			cursorStringCoo = editor.getMouse();
		}
		//调用接口得到更新后的文本内容
		if (!frameController.selectFlag || inputChar != '\b'){
			if (frameController.selectFlag && editor.isInsertFlag()){
				editor.setInsertFlag(false);
				editor.addChar(cursorStringCoo.getX(), cursorStringCoo.getY(), inputChar);
				editor.setInsertFlag(true);
			}
			else
				editor.addChar(cursorStringCoo.getX(), cursorStringCoo.getY(), inputChar);
		}
		//更新数据内容
		update();
	}
	
	private void getTextAfterKeyPressed()
	{
		switch (inputCode){
			case KeyEvent.VK_DELETE:
				if (frameController.selectFlag){
					inputChar = '\b';
					getTextAfterKeyTyped();
					return;
				}/*if*/
				else{
					editor.editChar(cursorStringCoo.getX(), cursorStringCoo.getY(), inputCode);
					content = editor.getBuffer();
				}
				break;
			case KeyEvent.VK_INSERT:
				editor.setInsertFlag(!editor.isInsertFlag());
				return;
			default:
				editor.editChar(cursorStringCoo.getX(), cursorStringCoo.getY(), inputCode);
				break;
		}/*switch*/
		update();
	}
	
	private void setNotSaveAndTitle(boolean notSaved, String titleName)
	{
		if(titleName == null)
			titleName = frameController.getTitle();
		setNotSaved(notSaved);
		if(hasNotSaved()){
			if(starFlag == false)
			{
				starFlag = true;
				frameController.setTitle(
						addStar(titleName, starFlag));
			}
		}
		else if(starFlag == true)
		{
			starFlag = false;
			frameController.setTitle(
					addStar(titleName, starFlag));
		}
	}
	
	public void refreshFrame()
	{
		frameController.clear();
		frameController.showText(temp, cursorStringCoo, content);
		frameController.showCursor(cursorPixelCoo);
	}
	
	
	private String addStar(String str,boolean starFlag)
	{
		String rst = str;
		if(starFlag)
			rst = "*" + str;
		else
			if(str.startsWith("*"))
				rst = str.substring(1);
		return rst;
	}

	public void update(){
		content = editor.getBuffer();
//		System.out.println(content);
		frameController.selectFlag = false;
		//得到光标字符位置。
		cursorStringCoo = editor.getMouse();
		if (cursorStringCoo == null)	cursorStringCoo = new Coordinate (0,0);
		//计算光标像素位置。
		cursorPixelCoo = frameController.transferString2Pixel(cursorStringCoo, content);
		//在界面刷新鼠标位置
		refreshFrame(); 
		//设置标题和存储标志
		setNotSaveAndTitle(true, null);
		frameController.setDimensionByContent(content);
	}
	private boolean hasNotSaved() {
		return notSaved;
	}

	private void setNotSaved(boolean notSaved) {
		this.notSaved = notSaved;
	}

	private void setFilePath(String filePath) {
		this.filePath = filePath;
	}

	public void setClickPos(Coordinate clickPos) {
		this.cursorStringCoo = clickPos;
	}

	public void setInputChar(char inputChar) {
		this.inputChar = inputChar;
	}
	
	private List<String> getContent() {
		return content;
	}
	
	private void setContent(List<String> content) {
		this.content = content;
	}

	public void run() {
		boolean showCursor = true;
		try {
			while(true){
				if (!ch) {
					frameController.clear();
					frameController.showText(temp, cursorStringCoo, content);
					if(showCursor)
						frameController.showCursor(cursorPixelCoo);
					showCursor = !showCursor;
					Thread.sleep(300);
					ch = true;
				}
				else{
					int x = frameController.miniWordFrame.getWidth(), y = frameController.miniWordFrame.getHeight();
					/*若窗口大小发生改变则重新布置组件*/
					if ( x != frameController.miniWordFrame.size_x && y != frameController.miniWordFrame.size_y){
						frameController.miniWordFrame.freshen();
						update();
					}
					Thread.sleep(300);
					ch = false;
				}
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	public int getInputCode() {
		return inputCode;
	}

	public void setInputCode(int inputCode) {
		this.inputCode = inputCode;
	}
	
	public Coordinate getCursorStringCoo() {
		return cursorStringCoo;
	}

	public void setCursorStringCoo(Coordinate cursorStringCoo) {
		this.cursorStringCoo = cursorStringCoo;
	}

	public Coordinate getTemp() {
		return temp;
	}

	public void setTemp(Coordinate temp) {
		this.temp = temp;
	}
	
	public FrameController getFrameController() {
		return frameController;
	}

	public void setFrameController(FrameController frameController) {
		this.frameController = frameController;
	}
}
