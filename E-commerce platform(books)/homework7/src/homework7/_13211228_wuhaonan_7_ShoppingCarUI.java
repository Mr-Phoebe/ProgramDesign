package homework7;

import java.awt.BorderLayout;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.JTable;

/**
 * 购物车UI界面
 */
public class _13211228_wuhaonan_7_ShoppingCarUI extends JDialog implements _13211228_wuhaonan_7_Observer {
	private static final long serialVersionUID = 1L;
	private JTable table;
	private JLabel label;
	private String[] headers = {"ISBN", "名称", "单价", "数量"};
	private JScrollPane pane;

	/**
	 * 构造函数
	 * 初始化界面
	 */
	_13211228_wuhaonan_7_ShoppingCarUI() {
		table = new JTable(new Object[0][4], headers);
		//table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
		pane = new JScrollPane(table);
		label = new JLabel("总价：");
		add(pane, BorderLayout.NORTH);
		add(label, BorderLayout.SOUTH);
		setSize(500, 550);
		setLocation(850, 200);
	}

	/**
	 * 根据销售类的情况更新购物车表格
	 * @param cur 销售类
	 */
	public void update(_13211228_wuhaonan_7_Sale cur) {
		int num = cur.getNum();
		Object data[][] = new Object[num][4];
		for (int i = 0; i < num; i++) {
			_13211228_wuhaonan_7_SaleLineItem tt = cur.getItem(i);
			_13211228_wuhaonan_7_BookSpecification pp = tt.getItem();
			data[i][0] = pp.get_isbn();
			data[i][1] = pp.get_name();
			data[i][2] = pp.get_price();
			data[i][3] = tt.getNum();
		}
		String tmp = new java.text.DecimalFormat("0.00").format(cur.getSubTotal());
		double total = Double.parseDouble(tmp);
		label.setText("总价：" + total + "元");

		if(total <= 0.0)
			label.setText("总价：0 元");

		table = new JTable(data, headers);
		remove(pane);
		pane = new JScrollPane(table);
		add(pane);
	}


}