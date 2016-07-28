package homework7;
/**
 * @author: SuPhoebe
 * Date: 2016/1/8
 * Time: 14:33
 * Name: homework7
 */
import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

/**
 * 增加书本窗口
 */

public class _13211228_wuhaonan_7_AddBookUI {
	/**
	 * 增加书本窗口构造函数
	 *
	 * @param cur 界面控制器
	 */
	_13211228_wuhaonan_7_AddBookUI(final _13211228_wuhaonan_7_Controller cur) {
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
		contentPane.setLayout(new GridLayout());
		JButton add = new JButton("增加");
		add.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				@SuppressWarnings("unused")
				_13211228_wuhaonan_7_bookAddUI addbookui = new _13211228_wuhaonan_7_bookAddUI(cur);
				jframe.dispose();
			}
		});
		contentPane.add(add);
		jframe.add(pane, BorderLayout.NORTH);
		jframe.setSize(500, 550);
		jframe.setLocation(300, 200);
		jframe.setVisible(true);
	}

}
