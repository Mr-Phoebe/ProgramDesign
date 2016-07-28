package homework7;
/**
 * @author: SuPhoebe
 * Date: 2015/12/31
 * Time: 22:17
 * Name: homework7
 */

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

/**
 * 主窗口
 */

public class _13211228_wuhaonan_7_MainUi {
	private JFrame jframe;
	private JMenuBar jmb;
	private JMenu book;
	private JMenuItem addbook;
	private JMenu strategiesManage;
	private JMenuItem strategies;
	private JMenu shopping;
	private JMenuItem buy;
	private JMenu menu_aboutme;
	private JMenuItem authors ;
	private JMenuItem software;
	private JLabel label;
	private _13211228_wuhaonan_7_Controller mycore;

	/**
	 * MainUi的构造函数
	 */
	_13211228_wuhaonan_7_MainUi() {

		jframe = new JFrame("图书大卖场");
		jframe.setSize(400, 300);
		jframe.setResizable(false);

		label = new JLabel("欢迎来到图书大卖场", JLabel.CENTER);

		jframe.add(label, BorderLayout.CENTER);

		jmb = new JMenuBar();

		mycore = new _13211228_wuhaonan_7_Controller();

		book = new JMenu("图书管理");
		addbook = new JMenuItem("添加图书");
		addbook.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				_13211228_wuhaonan_7_AddBookUI addbookui = new _13211228_wuhaonan_7_AddBookUI(mycore);
			}
		});
		book.add(addbook);

		strategiesManage = new JMenu("策略管理");
		strategies = new JMenuItem("策略管理");
		strategies.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				_13211228_wuhaonan_7_StrategiesUI stge = new _13211228_wuhaonan_7_StrategiesUI(mycore);
			}
		});
		strategiesManage.add(strategies);

		shopping = new JMenu("购买图书");
		buy = new JMenuItem("购买图书");
		buy.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				_13211228_wuhaonan_7_BuyUI buyui = new _13211228_wuhaonan_7_BuyUI(mycore);
			}
		});
		shopping.add(buy);


		menu_aboutme = new JMenu("关于");
		authors  = new JMenuItem("关于作者");

		authors.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				JFrame authorFrame = new JFrame("作者情况");
				JTextArea authorTextArea = new JTextArea("作者: 吴浩男\n博客：http://blog.csdn.net/u013007900");

				authorTextArea.setPreferredSize(new Dimension(300, 100));
				authorFrame.add(authorTextArea);

				int Width = authorFrame.getWidth(); //获得窗口宽
				int Height = authorFrame.getHeight(); //获得窗口高
				Toolkit kit = Toolkit.getDefaultToolkit(); //定义工具包
				Dimension screenSize = kit.getScreenSize(); //获取屏幕的尺寸
				int sW = screenSize.width; //获取屏幕的宽
				int sH = screenSize.height; //获取屏幕的高
				authorFrame.setLocation(sW / 2 - Width / 2, sH / 2 - Height / 2);//设置窗口居中显示
				authorFrame.setSize(300, 100);
				authorFrame.setVisible(true);
			}
		});

		software = new JMenuItem("关于软件");

		software.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				JFrame authorFrame = new JFrame("软件情况");
				JTextArea authorTextArea = new JTextArea("软件环境：Intellij IDEA 15.0.2\n开发环境：JDK 1.8.0");

				authorTextArea.setPreferredSize(new Dimension(300, 100));
				authorFrame.add(authorTextArea);

				int Width = authorFrame.getWidth(); //获得窗口宽
				int Height = authorFrame.getHeight(); //获得窗口高
				Toolkit kit = Toolkit.getDefaultToolkit(); //定义工具包
				Dimension screenSize = kit.getScreenSize(); //获取屏幕的尺寸
				int sW = screenSize.width; //获取屏幕的宽
				int sH = screenSize.height; //获取屏幕的高
				authorFrame.setLocation(sW / 2 - Width / 2, sH / 2 - Height / 2);//设置窗口居中显示
				authorFrame.setSize(300, 100);
				authorFrame.setVisible(true);
			}
		});

		menu_aboutme.add(authors);
		menu_aboutme.add(software);

		jmb.add(book);
		jmb.add(strategiesManage);
		jmb.add(shopping);
		jmb.add(menu_aboutme);
		jframe.setJMenuBar(jmb);
		// 窗口居中
		int windowWidth = jframe.getWidth(); //获得窗口宽
		int windowHeight = jframe.getHeight(); //获得窗口高
		Toolkit kit = Toolkit.getDefaultToolkit(); //定义工具包
		Dimension screenSize = kit.getScreenSize(); //获取屏幕的尺寸
		int screenWidth = screenSize.width; //获取屏幕的宽
		int screenHeight = screenSize.height; //获取屏幕的高
		jframe.setLocation(screenWidth / 2 - windowWidth / 2, screenHeight / 2 - windowHeight / 2);//设置窗口居中显示

		jframe.setVisible(true);
	}

	/**
	 * 程序入口
	 *
	 * @param args 命令行变元，在程序中没有使用
	 */
	public static void main(String[] args) {
		_13211228_wuhaonan_7_MainUi mainui = new _13211228_wuhaonan_7_MainUi();
	}

}
