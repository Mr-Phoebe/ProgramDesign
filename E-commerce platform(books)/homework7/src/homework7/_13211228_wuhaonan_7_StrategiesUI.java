package homework7;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;



/**
 * 策略维护窗口
 */

public class _13211228_wuhaonan_7_StrategiesUI {
	_13211228_wuhaonan_7_StrategiesUI() {
	}

	_13211228_wuhaonan_7_StrategiesUI(final _13211228_wuhaonan_7_Controller cur) {
		final JFrame jframe = new JFrame("策略管理");
		Object data[][] = new Object[5][2];
		for (int i = 0; i < 5; i++) {
			_13211228_wuhaonan_7_IPricingStrategy pp = cur.getStrategyCatalog().getVal(i + 1);
			data[i][0] = i + 1;
			if (pp != null) data[i][1] = pp.getString();
		}
		String columnNames[] = {"书本类型", "策略描述"};
		JTable table = new JTable(data, columnNames);

		JScrollPane pane = new JScrollPane(table);
		jframe.add(pane, BorderLayout.NORTH);

		Container contentPane = jframe.getContentPane();
		contentPane.setLayout(new FlowLayout());
		JButton add = new JButton("增加");
		add.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				@SuppressWarnings("unused")
				_13211228_wuhaonan_7_strategyAddUI add = new _13211228_wuhaonan_7_strategyAddUI(cur);
				jframe.dispose();
			}
		});
		JButton delete = new JButton("删除");
		delete.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				@SuppressWarnings("unused")
				_13211228_wuhaonan_7_strategyDelUI add = new _13211228_wuhaonan_7_strategyDelUI(cur);
				jframe.dispose();
			}
		});
		JButton update = new JButton("修改");
		update.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				@SuppressWarnings("unused")
				_13211228_wuhaonan_7_strategyUpdateUI add = new _13211228_wuhaonan_7_strategyUpdateUI(cur);
				jframe.dispose();
			}
		});
		contentPane.add(add);
		contentPane.add(delete);
		contentPane.add(update);
		jframe.setSize(500, 550);
		jframe.setResizable(false);
		jframe.setLocation(300, 200);
		jframe.setVisible(true);
	}
}
