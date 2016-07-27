import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

/**
 * Title: QICQ聊天系统登录程序 
 * Description: 过滤用户聊天内容 
 * Copyright: Copyright (c) 2015
 * 
 * @author 吴浩男
 * @version 1.0
 */
public class WordFilter {

	private String word = ""; // 准备过滤的内容

	/**
	 * 得到过滤的内容
	 * 
	 * @return 过滤的内容
	 */
	public String getWord() {
		return word;
	}

	/**
	 * 设置过滤内容
	 * 
	 * @param word
	 *            过滤内容
	 */
	public void setWord(String word) {
		this.word = word;
	}

	/**
	 * 设置过滤内容
	 * 
	 * @param word
	 *            过滤内容
	 */
	public WordFilter(String word) {
		super();
		this.word = word;
	}

	// 创建过滤类
	public WordFilter() {
		// TODO 自动生成构造函数存根
	}

	// 处理过滤内容
	public void process() {
		String badWord = this.getFile("badword.txt");
		// System.out.println(badWord);
		String badWordList[] = badWord.split(",");
		for (int i = 0; i < badWordList.length; i++) {
			// System.out.println(badWordList[i]);
			// System.out.println(badWordList[i]+":"+word.indexOf(badWordList[i]));
			if (word.indexOf(badWordList[i]) != -1) {
				word = "非法内容,系统屏蔽";
			}
		}
	}

	/**
	 * 得到过滤文件内容
	 * 
	 * @param file
	 *            过滤文件名
	 * @return 过滤文件内容
	 */
	public String getFile(String file) {
		String fileString = "";
		try {
			File files = new File(file);
			// System.out.println(files.getAbsolutePath());
			FileReader fileReader = new FileReader(files);
			BufferedReader read = new BufferedReader(fileReader);
			while (true) {
				String line = read.readLine();
				if (line == null) {
					break;
				}
				fileString += (line);				
			}
			read.close();
			// System.out.println(fileString);
		} catch (FileNotFoundException e) {
			// TODO 自动生成 catch 块
			e.printStackTrace();
		} catch (IOException e) {
			// TODO 自动生成 catch 块
			e.printStackTrace();
		}
		return fileString;
	}

	/**
	 * 过滤内容，返回合法内容
	 * 
	 * @param word
	 *            过滤内容
	 * @return 合法内容
	 */
	public static String filter(String word) {
		WordFilter wf = new WordFilter(word);
		wf.process();

		return wf.getWord();

	}

}
