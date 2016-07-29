package cn.miniword.util;

import java.util.List;

import cn.miniword.model.edit.EditList;

public class EditUtility {
	
	/*List<String>向EditList转换*/
	public static EditList listToEditList (List<String> buffer){
		EditList head = new EditList();
		int x = 0, y = 0;
		for(int i = 0; i < buffer.size(); i++){
			for (int j = 0; j < buffer.get(i).length(); j++){
				head.addChar(x, y++, buffer.get(i).charAt(j));
			}
			head.addChar(x++, y, '\n');
			y = 0;
		}
		return head;
	}//listToEditList
	
	/*List<String>向char数组转换*/
	public static char[] listToChar (List<String> buffer){
		return null;
	}//listToChar
	
}
