package homework7;

import java.util.ArrayList;
import java.util.List;

/**
 * 购物清单类
 * 是对接口Subject（被观察者）的一种实现
 */

public class _13211228_wuhaonan_7_Sale implements _13211228_wuhaonan_7_Subject {
	private _13211228_wuhaonan_7_SaleLineItem[] items = null;
	private List<_13211228_wuhaonan_7_Observer> list = new ArrayList<_13211228_wuhaonan_7_Observer>();
	private int num;

	/**
	 * 构造函数，初始化销售数目，申请内存池
	 */
	public _13211228_wuhaonan_7_Sale() {
		items = new _13211228_wuhaonan_7_SaleLineItem[100];
		num = 0;
	}

	/**
	 * 添加销售项目
	 * @param cur 销售项目
	 */
	public void addItem(_13211228_wuhaonan_7_SaleLineItem cur) {
		items[num++] = cur;
	}

	/**
	 * 返回本次销售的优惠后总价
	 * @return 价格
	 */
	public double getSubTotal() {
		double total = 0;
		for (int i = 0; i < num; i++)
			total += items[i].getTotal();
		return total;
	}

	/**
	 * 根据下标获得销售项目
	 * @param id 下标
	 * @return 销售项目
	 */
	public _13211228_wuhaonan_7_SaleLineItem getItem(int id) {
		return items[id];
	}

	/**
	 * 获得销售项目的个数
	 * @return 销售项目的个数
	 */
	public int getNum() {
		return num;
	}


	/**
	 * 添加观察者接口
	 * @param cur 观察者接口
	 */
	public void registerObserver(_13211228_wuhaonan_7_Observer cur) {
		list.add(cur);
	}

	/**
	 * 删除观察者接口
	 * @param cur 观察者接口
	 */
	public void removeObserve(_13211228_wuhaonan_7_Observer cur) {
		list.remove(cur);
	}

	/**
	 * 更新观察者接口
	 */
	public void notifyObservers() {
		for (_13211228_wuhaonan_7_Observer cur : list) {
			cur.update(this);
		}
	}
}
