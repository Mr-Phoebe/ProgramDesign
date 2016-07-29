package cn.miniword.model.edit;

import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.List;

import cn.miniword.model.Coordinate;


public class EditList {
	int num = 0;										//链表编号
	Array data = null;									//字符数组
	EditList next = null;								//下一节点
	boolean insertFlag = false;							//覆盖标志
	boolean copyFlag = false;							//缓存标志
	List<String> buffer = new ArrayList<String>();		//链表存储的字符信息
	Coordinate mouse = null;							//光标信息
	//默认方法，创建链表节点
	public EditList (){		
		data = new Array();
		if (data == null){
			;//空间申请失败
		}
	}//List()
	/*块删除*/
	public void delModule(int x1, int y1, int x2, int y2){
		EditList current = this;
		while (current.num < x1)
			current = current.next;
		int j = current.data.sit;
		for (int i = x1; i < x2; i++){
			/*删除当前行*/
			for ( ; j >= y1; j--){
				this.editChar(x1, y1, KeyEvent.VK_DELETE);
			}/*for*/
			/*定位下一行*/
			current = current.next;
			j = current.data.sit + y1 + 1;
			this.editChar(x1, y1, KeyEvent.VK_DELETE);
		}/*for*/
		/*若是在同一行则删除y2-y1个，否则删除y2个*/
		if (x1 == x2)	j = y1;
		else			j = 0;
		for ( ; j < y2; j++){
			this.editChar(x1, y1, KeyEvent.VK_DELETE);
		}
		this.mouse = new Coordinate(x1,y1);
	}//delModule
	/*块复制*/
	public void copyModule(int ax, int ay, int bx, int by) {
		// TODO Auto-generated method stub
//		System.out.println("ax:"+ax+"  ay:"+ay+"  bx:"+bx+"  by:"+by);
		EditList current = this;
		String tmp = null;
		this.setCopyFlag(true);
		/*清空缓存区*/
		buffer.clear();
		while (current.num < ax)		current = current.next;
		/*若在同一行*/
		if (ax == bx){
			tmp = new String(current.data.str).substring(ay, by);
			buffer.add(tmp);
//			System.out.println("copytmp:"+buffer);
		}
		else{
			/*拷贝第一行*/
			tmp = new String(current.data.str).substring(ay,current.data.sit+1);
			current= current.next;
			buffer.add(tmp);
			/*拷贝中间行*/
			while (++ax < bx){
				tmp = new String(current.data.str).substring(0,current.data.sit);
				current = current.next;
				buffer.add(tmp);
			}
			/*拷贝最后一行*/
			tmp = new String(current.data.str).substring(0,by);
			buffer.add(tmp);
		}
	}
	/*块粘贴*/
	public void pasteModule(int x, int y) {
		// TODO Auto-generated method stub
		String tmp = null;
		if (buffer.isEmpty())		return;
		
		tmp = buffer.get(0);
		for (int j = 0; j < tmp.length(); j++){
			this.addChar(x, y++, tmp.charAt(j));
		}/*for*/
		for (int i = 1; i < buffer.size(); i++){
			tmp = buffer.get(i);
			this.addChar(x++, y, '\n');
			y = 0;
			for (int j = 0; j < tmp.length(); j++){
				this.addChar(x, y++, tmp.charAt(j));
			}/*for*/
		}/*for*/
	}
	/*根据x找到插入的行，将插入位置y和字符ch传给Array进行插入操作*/
	public void addChar (int x, int y, char ch){
		
		EditList current = this;
				
		while (x > current.num && current.next != null){			
			current = current.next;						
		}//while
		if (x > current.num){					
			current.next = new EditList();
			current.next.num = x;
			current = current.next;					
		}//if(x > num)	
		/*将Tab符当做空格处理*/
		if (ch == '\t'){
			ch = ' ';
		}
		//检查是否是回车符，若是则增加链表ta
		if (ch == '\n'){
			EditList temp = new EditList();
			/*若在插入的字符不在数组尾部则新建链表将回车符后面的字符数组拷贝给新链表*/
			if (y <= current.data.sit){
				int i = y;
				for ( ; i <= current.data.sit; i++){
					temp.data.str[i-y] = current.data.str[i];
					current.data.str[i] = '\0';
				}//for
				temp.data.sit = i-y-1;				//重置数组长度
				current.data.sit = y-1;
			}//if(current)
			/*否则新建空链表*/
			temp.next = current.next;
			temp.num = current.num;
			current.next = temp;
			/*更新链表编号*/
			while (temp != null){
				temp.num++;
				temp = temp.next;				
			}//while(temp != null)
			this.mouse = new Coordinate(x+1,0);
//			System.out.println("("+(x+1)+","+ 0 + ")");
		}//if(ch == '\n')
		else if (ch == '\b'){
			/*若删除的字符在数组头部则删除链表将字符接到上一链表尾*/
			if (y == 0){
				if (x == 0){
					this.mouse = new Coordinate(0,0);
//					System.out.println("("+0 +","+ 0 + ")");
				}
				else{
					EditList temp = this;
					while (temp.num < current.num - 1){
						temp = temp.next;
					}//while
					/*若空间不够则重新申请，将数字接到上一链表尾*/
					if (temp.data.leng <= temp.data.sit + current.data.sit){
						char t[] = temp.data.str;
						temp.data.leng = 80 * ((temp.data.sit + current.data.sit)/80 + 1);
						temp.data.str = new char[temp.data.leng];
					
						/*若申请空间不足则输出提示语句并退出*/
						if (temp.data.str == null){					
							;//申请空间失败
						}
					
						/*数组拷贝*/
						for (int i = 0; i < t.length; i++){					
							temp.data.str[i] = t[i];					
						}//for 				
					}//if(leng < sit + sit)
					for (int i = 0; i <= current.data.sit; i++){
						temp.data.str[++temp.data.sit] = current.data.str[i];
					}//for
					/*更新光标位置*/
					this.mouse = new Coordinate(x-1,temp.data.sit-current.data.sit);
//					System.out.println("("+(x-1)+","+ (temp.data.sit-current.data.sit) + ")");
					/*删除链表节点*/
					temp.next = current.next;
					/*更新链表编号*/
					while (temp.next != null){
						temp = temp.next;	
						temp.num--;
					}//while(temp != null)
				}//else
			}//if(y == 0)
			/*否则删除一个字符*/
			else{
				
				for (int i = y-1; i < current.data.sit; i++){
					current.data.str[i] = current.data.str[i+1];
				}//for
				current.data.str[current.data.sit--] = '\0';
				this.mouse = new Coordinate(x,y-1);
//				System.out.println("("+(x)+","+ (y-1) + ")");
			}//else
		}//else if (ch == '\b')
		else{
			/*更新光标位子*/
			this.mouse = new Coordinate(x,y+1);
		}//else
		current.data.add(x,y,ch,insertFlag);
	}//addChar(int,int,char)
	

	public void editChar(int x, int y, int inputCode) {
		// TODO Auto-generated method stub
		EditList current = this;
		switch (inputCode){
			case KeyEvent.VK_DELETE:
				/*读取到操作行*/
				while (current.num < x && current.next != null){
					current = current.next;
				}/*while*/
				/*若是在数据最尾部不操作*/
				if (current.next == null && current.data.sit == y-1){
					break;
				}
				/*若在当前行最尾部则删除换行*/
				if (current.data.sit == y-1){
					this.addChar(x+1, 0, '\b');
					//this.mouse = current.mouse;
				}
				/*删除后面一位数据*/
				else{
					this.addChar(x, y+1, '\b');
					}
				break;
			case KeyEvent.VK_HOME:
				this.mouse = new Coordinate(x,0) ;
				break;
			case KeyEvent.VK_END:
				while (current.num < x)		current = current.next;
				this.mouse = new Coordinate(x,current.data.sit+1);
				break;
			case KeyEvent.VK_UP:
				/*若在第一行则不操作*/
				if (x-- == 0)				break;
				while (current.num < x)	current = current.next;
				if (y > current.data.sit)	this.mouse = new Coordinate(x,current.data.sit+1);
				else						this.mouse = new Coordinate(x,y);
				break;
			case KeyEvent.VK_DOWN:
				while (current.num < x)		current = current.next;
				/*若在最后一行则不操作*/
				if (current.next == null)	break;
				current = current.next;
				if (y > current.data.sit)	this.mouse = new Coordinate(x+1,current.data.sit+1);
				else						this.mouse = new Coordinate(x+1,y);
				break;
			case KeyEvent.VK_LEFT:
				/*若在最左端则不操作*/
				if (y-- == 0)				break;
				else						this.mouse = new Coordinate(x,y);
				break;
			case KeyEvent.VK_RIGHT:
				/*若在最右段则不操作*/
				while (current.num < x)		current = current.next;
				if (y++ == current.data.sit+1)	break;
				else							this.mouse = new Coordinate(x,y);
				break;
		}/*switch*/
	}/*editChar*/

	public int getNum() {
		return num;
	}

	public void setNum(int num) {
		this.num = num;
	}

	public Array getData() {
		return data;
	}

	public void setData(Array data) {
		this.data = data;
	}

	public EditList getNext() {
		return next;
	}

	public void setNext(EditList next) {
		this.next = next;
	}

	public Coordinate getMouse() {
		return mouse;
	}

	public void setMouse(Coordinate mouse) {
		this.mouse = mouse;
	}

	public List<String> getBuffer() {

		List<String> buffer = new ArrayList<String>();		//链表存储的字符信息
		/*返回字符串链*/
		EditList current = this;
		String tmp = "";
		while(current != null){
			tmp = new String(current.data.str).substring(0, current.data.sit + 1);
//			System.out.println("tmp:"+tmp);
			buffer.add(tmp);
			current = current.next;
		}//while(current != null)
		
		return buffer;
	}

	public EditList getthis(){
		return this;
	}
	public boolean isInsertFlag() {
		return insertFlag;
	}
	public void setInsertFlag(boolean insertFlag) {
		this.insertFlag = insertFlag;
	}
	public boolean isCopyFlag() {
		return copyFlag;
	}
	public void setCopyFlag(boolean copyFlag) {
		this.copyFlag = copyFlag;
	}
	public void setBuffer(List<String> buffer) {
		this.buffer = buffer;
	}
	
}
