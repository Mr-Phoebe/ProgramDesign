package homework7;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

import javax.swing.JFrame;

/**
 * 购买书的窗口
 */
public class _13211228_wuhaonan_7_BuyUI {
	/**
	 * 购买书的窗口构造函数
	 * @param cur 界面控制器
	 */
	_13211228_wuhaonan_7_BuyUI(final _13211228_wuhaonan_7_Controller cur) {
		final JFrame jframe = new JFrame("图书管理界面");
		int num = cur.getBookCatalog().getNumber();
		Object data[][] = new Object[num][4];
		for (int i = 0; i < num; i++) {
			_13211228_wuhaonan_7_BookSpecification book = cur.getBookCatalog().getItem(i);
			data[i][0] = book.get_isbn();
			data[i][1] = book.get_name();
			data[i][2] = book.get_price();
			data[i][3] = book.get_type();
		}
		String columnNames[] = {"ISBN", "名称", "单价", "类型"};
		JTable table = new JTable(data, columnNames);
		//table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
		JScrollPane pane = new JScrollPane(table);
		Container contentPane = jframe.getContentPane();
		contentPane.setLayout(new FlowLayout());
		JButton add = new JButton("购买");
		jframe.add(pane, BorderLayout.NORTH);


		jframe.add(new JLabel("ISBN : "));
		final JTextField isbn = new JTextField(10);
		jframe.add(isbn);
		jframe.add(new JLabel("数量 : "));
		final JTextField book_num = new JTextField(8);
		jframe.add(book_num);

		add.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
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
				try {
					Integer.parseInt(book_num.getText());
				} catch (NumberFormatException ee) {
					JOptionPane.showMessageDialog(null, "数量不为整数，输入有误！");
					book_num.setText("");
					return;
				}
				if (Integer.parseInt(book_num.getText()) <= 0) {
					JOptionPane.showMessageDialog(null, "数量不能小于等于0，输入有误！");
					book_num.setText("");
					return;
				}
				if (cur.buyBook(isbn.getText(), Integer.parseInt(book_num.getText())) == true)
					JOptionPane.showMessageDialog(null, "添加成功 ^_^");
				else
					JOptionPane.showMessageDialog(null, "书本不存在，添加失败 ->_<-");
			}
		});
		jframe.add(add);
		jframe.setSize(500, 550);
		jframe.setLocation(300, 200);
		jframe.setVisible(true);

		_13211228_wuhaonan_7_ShoppingCarUI Car = new _13211228_wuhaonan_7_ShoppingCarUI();
		Car.update(cur.getSale());
		Car.setVisible(true);
		cur.addObserver(Car);
	}
}

