
/**************************************************************
 *                                                            *
 *                                                            *
 *                                                            *
 *                                                            *
 *                                                            *
 *                                                            *
 *                                                            *
 *                                                            *
 *                                                            *
 **************************************************************/

package cn.miniword.model.edit;


public class Array {
	
	private static final int LEN = 80;				//定义数组基本单位长度
	int sit = -1;									//数组下标
	int leng = LEN;									//数组长度
	char str[] = null;								//字符数组
	
	/*默认方法，创建新数组*/
	public Array (){		
		str = new char[LEN];
		if (str == null){
			;//申请空间失败
		}//if(str == null)	
	}//Array()
	
	/*插入字符操作*/
	public void add(int x, int y, char ch, boolean insert) {		
		switch (ch){
			case '\n' :
				//返回新的光标的位置
				break;
			case '\b' :
				//返回新的光标的位置
				break;
			default :
				/*若超过字符数组长度且不是覆盖数据则重新申请空间存储*/
				if (sit < y || !insert)
					sit++;
				if (sit >= leng && !insert){
					char temp[] = str;
					leng += LEN;
					str = new char[leng];
				
					/*若申请空间不足则输出提示语句并退出*/
					if (str == null){					
						;//申请空间失败
					}
				
					/*数组拷贝*/
					for (int i = 0; i < temp.length; i++){					
						str[i] = temp[i];					
					}//for 				
				}//if(sit >= 80)
			
				/*追加数据或者插入数据判断,若不是覆盖模式则直接替换字符*/
				if (sit > y && !insert){
					for (int i = sit; i > y; i--){					
						str[i] = str[i-1];					
					}//for
				}//if(sit > y)			
				str[y] = ch;
		}//switch(ch)
	}//add(int,int)

	public int getSit() {
		return sit;
	}

	public void setSit(int sit) {
		this.sit = sit;
	}

	public int getLeng() {
		return leng;
	}

	public void setLeng(int leng) {
		this.leng = leng;
	}

	public char[] getStr() {
		return str;
	}

	public void setStr(char[] str) {
		this.str = str;
	}

}
