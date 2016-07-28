package homework7;

/**
 * @author: SuPhoebe
 * Date: 2016/1/10
 * Time: 17:36
 * Name: homework7
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * 策略删除UI
 */
class _13211228_wuhaonan_7_strategyDelUI {
	private JFrame jframe;
	private Container contentPane;

	private JButton Done;
	private JButton Reset;

	_13211228_wuhaonan_7_strategyDelUI(final _13211228_wuhaonan_7_Controller cur) {
		jframe = new JFrame("删除");
		contentPane = jframe.getContentPane();
		contentPane.setLayout(new GridLayout(2, 2));

		jframe.add(new JLabel("类型："));
		String names[] = new String[5];
		names[0] = "非教材计算机";
		names[1] = "教材类";
		names[2] = "连环画";
		names[3] = "养生类";
		names[4] = "其他";
		final JComboBox<String> comboBox = new JComboBox<String>(names);
		comboBox.setEditable(false);
		jframe.add(comboBox);

		Done = new JButton("Done");
		Done.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int key = comboBox.getSelectedIndex() + 1;
				jframe.dispose();
				cur.deleteStrategy(key);
				JOptionPane.showMessageDialog(null, "策略删除成功 ^_^");
			}
		});
		Reset = new JButton("Reset");
		Reset.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// 卖萌
			}
		});
		contentPane.add(Done);
		contentPane.add(Reset);
		jframe.setSize(600, 400);
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
}

