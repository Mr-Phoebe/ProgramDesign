package homework7;

/**
 * @author: SuPhoebe
 * Date: 2016/1/10
 * Time: 17:35
 * Name: homework7
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * 策略添加UI
 */
class _13211228_wuhaonan_7_strategyAddUI {
	private JFrame jframe;
	private Container contentPane;

	private JButton Done;
	private JButton Reset;

	_13211228_wuhaonan_7_strategyAddUI(final _13211228_wuhaonan_7_Controller cur) {
		jframe = new JFrame("添加策略");
		contentPane = jframe.getContentPane();
		GridBagLayout layout = new GridBagLayout();
		contentPane.setLayout(layout);

		JLabel label_kind = new JLabel("类型:");
		contentPane.add(label_kind);
		String names[] = new String[5];
		names[0] = "非教材计算机";
		names[1] = "教材类";
		names[2] = "连环画";
		names[3] = "养生类";
		names[4] = "其他";
		final JComboBox<String> comboBox = new JComboBox<String>(names);
		comboBox.setEditable(false);
		contentPane.add(comboBox);

		JLabel label_dec = new JLabel("	基本策略－立减(double)");
		contentPane.add(label_dec);
		final JTextField decrease = new JTextField();
		contentPane.add(decrease);

		JLabel label_per = new JLabel("	基本策略－折扣(int[0~100])");
		contentPane.add(label_per);
		final JTextField percent = new JTextField();
		contentPane.add(percent);

		final JRadioButton radio1 = new JRadioButton("基本策略－立减");
		final JRadioButton radio2 = new JRadioButton("基本策略－折扣");

		final JRadioButton radio3 = new JRadioButton("组合策略");
		radio1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				percent.setEditable(false);
				percent.setVisible(false);
				decrease.setEditable(true);
				decrease.setVisible(true);
			}
		});
		radio2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				decrease.setEditable(false);
				decrease.setVisible(false);
				percent.setEditable(true);
				percent.setVisible(true);
			}
		});
		radio3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				percent.setEditable(true);
				percent.setVisible(true);
				decrease.setEditable(true);
				decrease.setVisible(true);
			}
		});
		contentPane.add(radio1);
		contentPane.add(radio2);
		contentPane.add(radio3);
		ButtonGroup group = new ButtonGroup();
		group.add(radio1);
		group.add(radio2);
		group.add(radio3);
		radio3.setSelected(true);

		Done = new JButton("Done");
		Done.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int kk = comboBox.getSelectedIndex() + 1;
				if (radio1.isSelected()) {
					try {
						Double.parseDouble(decrease.getText());
					} catch (NumberFormatException ee) {
						JOptionPane.showMessageDialog(null, "立减价格输入有误！");
						decrease.setText("");
						return;
					}
					double tmp = Double.parseDouble(decrease.getText());
					_13211228_wuhaonan_7_FlatRateStrategy dec = new _13211228_wuhaonan_7_FlatRateStrategy(tmp);
					cur.addSimpleStrategy(kk, dec);
					JOptionPane.showMessageDialog(null, "策略添加成功 ^_^");
				}
				if (radio2.isSelected()) {
					try {
						Double.parseDouble(percent.getText());
					} catch (NumberFormatException ee) {
						JOptionPane.showMessageDialog(null, "折扣输入有误！");
						percent.setText("");
						return;
					}
					int tmp = Integer.parseInt(percent.getText());
					if (tmp < 0 || tmp > 100) {
						JOptionPane.showMessageDialog(null, "折扣输入有误！");
						percent.setText("");
						return;
					}
					_13211228_wuhaonan_7_PercentageStrategy per = new _13211228_wuhaonan_7_PercentageStrategy(tmp);
					cur.addSimpleStrategy(kk, per);
					JOptionPane.showMessageDialog(null, "策略添加成功 ^_^");
				}
				if (radio3.isSelected()) {
					try {
						Double.parseDouble(decrease.getText());
					} catch (NumberFormatException ee) {
						JOptionPane.showMessageDialog(null, "立减价格输入有误！");
						decrease.setText("");
						return;
					}
					try {
						Double.parseDouble(percent.getText());
					} catch (NumberFormatException ee) {
						JOptionPane.showMessageDialog(null, "折扣输入有误！");
						percent.setText("");
						return;
					}
					int tmp = Integer.parseInt(percent.getText());
					if (tmp < 0 || tmp > 100) {
						JOptionPane.showMessageDialog(null, "折扣输入有误！");
						percent.setText("");
						return;
					}
					_13211228_wuhaonan_7_PercentageStrategy per = new _13211228_wuhaonan_7_PercentageStrategy(tmp);
					double tp = Double.parseDouble(decrease.getText());
					_13211228_wuhaonan_7_FlatRateStrategy dec = new _13211228_wuhaonan_7_FlatRateStrategy(tp);

					_13211228_wuhaonan_7_CopositeStrategy haha = new _13211228_wuhaonan_7_CompositeBestForCustomer();
					haha.add(per);
					haha.add(dec);

					cur.addCompositeStrategy(kk, haha);
					JOptionPane.showMessageDialog(null, "策略添加成功 ^_^");
				}
				jframe.dispose();
				decrease.setText("");
				percent.setText("");
			}
		});
		Reset = new JButton("Reset");
		Reset.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				decrease.setText("");
				percent.setText("");
			}
		});
		//addbook.setBackground(Color.red);
		contentPane.add(Done);
		contentPane.add(Reset);

		GridBagConstraints s = new GridBagConstraints();//定义一个GridBagConstraints，
		//是用来控制添加进的组件的显示位置
		s.fill = GridBagConstraints.BOTH;

		s.gridwidth = 1;//该方法是设置组件水平所占用的格子数，如果为0，就说明该组件是该行的最后一个
		s.weightx = 1;//该方法设置组件水平的拉伸幅度，如果为0就说明不拉伸，不为0就随着窗口增大进行拉伸，0到1之间
		s.weighty = 1;//该方法设置组件垂直的拉伸幅度，如果为0就说明不拉伸，不为0就随着窗口增大进行拉伸，0到1之间
		layout.setConstraints(label_kind, s);
		s.gridwidth = 0;//该方法是设置组件水平所占用的格子数，如果为0，就说明该组件是该行的最后一个
		s.weightx = 0;//该方法设置组件水平的拉伸幅度，如果为0就说明不拉伸，不为0就随着窗口增大进行拉伸，0到1之间
		s.weighty = 0;//该方法设置组件垂直的拉伸幅度，如果为0就说明不拉伸，不为0就随着窗口增大进行拉伸，0到1之间
		layout.setConstraints(comboBox, s);

		s.gridwidth = 1;
		s.weightx = 1;
		s.weighty = 1;
		layout.setConstraints(label_dec, s);
		s.gridwidth = 0;
		s.weightx = 0;
		s.weighty = 0;
		layout.setConstraints(decrease, s);

		s.gridwidth = 1;
		s.weightx = 1;
		s.weighty = 1;
		layout.setConstraints(label_per, s);
		s.gridwidth = 0;
		s.weightx = 0;
		s.weighty = 0;
		layout.setConstraints(percent, s);

		s.gridwidth = 1;
		s.weightx = 1;
		s.weighty = 1;
		layout.setConstraints(radio1, s);
		s.gridwidth = 1;
		s.weightx = 1;
		s.weighty = 1;
		layout.setConstraints(radio2, s);
		s.gridwidth = 1;
		s.weightx = 1;
		s.weighty = 1;
		layout.setConstraints(radio3, s);

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
