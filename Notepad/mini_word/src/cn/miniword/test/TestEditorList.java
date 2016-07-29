package cn.miniword.test;

import java.util.List;

import junit.framework.Assert;

import org.junit.Test;

import cn.miniword.biz.FrameController;
import cn.miniword.model.Coordinate;
import cn.miniword.model.edit.EditList;

public class TestEditorList {
	
	private Coordinate curSorStringCoo = Coordinate.ZERO;
	private EditList editor = new EditList();
	private List<String> content;
	
	@Test
	public void test()
	{
		editor = new EditList();
		String testString = "aa\na";
		simulateInput(testString);
		System.out.println(content);
		System.out.println("StringPos::" + curSorStringCoo);
		Coordinate expectedCoo = new Coordinate(1, 0);
		Coordinate actualCoo = curSorStringCoo;
		Assert.assertEquals(expectedCoo, actualCoo);
	}
	
	/**
	 * 调用模型层得到输入后的文本内容以及光标位置
	 */
	private void getTextAfterKeyTyped(char inputChar)
	{
		//调用接口得到更新后的文本内容
		editor.addChar(curSorStringCoo.getX(), curSorStringCoo.getY(), inputChar);
		//更新数据内容
		content = editor.getBuffer();
//		System.out.println(content);
		//得到光标字符位置。
		curSorStringCoo = editor.getMouse();
//		System.out.println("StringPos::" + curSorStringCoo);
	}
	
	private void simulateInput(String str)
	{
		for(int i = 0; i < str.length(); i++)
			getTextAfterKeyTyped(str.charAt(i));
	}
}
