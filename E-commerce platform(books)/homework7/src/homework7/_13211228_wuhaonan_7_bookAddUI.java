package homework7;
/**
 * @author: SuPhoebe
 * Date: 2016/1/8
 * Time: 17:20
 * Name: homework7
 */
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


/**
 * 添加图书子窗口
 */
public class _13211228_wuhaonan_7_bookAddUI {
	private JFrame jframe;
	private Container contentPane;
	private JButton Done;
	private JButton Reset;

	_13211228_wuhaonan_7_bookAddUI(_13211228_wuhaonan_7_Controller cur, ActionListener actionListener) {
	}

	/**
	 *	添加图书子窗口构造函数
	 * @param cur 界面控制器
	 */
	_13211228_wuhaonan_7_bookAddUI(final _13211228_wuhaonan_7_Controller cur) {
		jframe = new JFrame("添加新图书");
		contentPane = jframe.getContentPane();
		contentPane.setLayout(new GridLayout(5, 2));
		jframe.add(new JLabel("	ISBN号(8位数字):"));
		final JTextField isbn = new JTextField();
		jframe.add(isbn);
		jframe.add(new JLabel("	名称(string):"));
		final JTextField name = new JTextField();
		jframe.add(name);
		jframe.add(new JLabel("	单价(double)"));
		final JTextField price = new JTextField();
		jframe.add(price);


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
				int kind = comboBox.getSelectedIndex() + 1;
				try {
					Integer.parseInt(isbn.getText());
				} catch (NumberFormatException ee) {
					JOptionPane.showMessageDialog(null, "ISBN码格式有误！");
					isbn.setText("");
					return;
				} finally {
					if (isbn.getText().length() != 8) {
						JOptionPane.showMessageDialog(null, "ISBN码长度有误!");
						isbn.setText("");
						return;
					}
				}
				if (name.getText().length() == 0) {
					JOptionPane.showMessageDialog(null, "名称不能为空！");
					return;
				}
				try {
					Double.parseDouble(price.getText());
				} catch (NumberFormatException ee) {
					JOptionPane.showMessageDialog(null, "价格不为小数，输入有误！");
					price.setText("");
					return;
				}
				boolean flag = cur.getBookCatalog().add(
						new _13211228_wuhaonan_7_BookSpecification(isbn.getText(), name.getText(), Double.parseDouble(price.getText()), kind)
				);
				if (flag) {
					JOptionPane.showMessageDialog(null, "添加成功 ^_^");
					isbn.setText("");
					name.setText("");
					price.setText("");
					jframe.dispose();
				} else {
					JOptionPane.showMessageDialog(null, "失败:该图书已经存在！");
					isbn.setText("");
					name.setText("");
					price.setText("");
				}
			}
		});
		Reset = new JButton("Reset");
		Reset.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				isbn.setText("");
				name.setText("");
				price.setText("");
			}
		});
		//addbook.setBackground(Color.red);
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