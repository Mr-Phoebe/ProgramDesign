package homework7;

/**
 * 组合策略类
 * 对接口IPricingStrategy的实现
 */

public class _13211228_wuhaonan_7_CopositeStrategy implements _13211228_wuhaonan_7_IPricingStrategy {
	protected _13211228_wuhaonan_7_IPricingStrategy[] strategies = null;
	protected int num;

	/**
	 * 构造函数，初始化策略数目，申请内存池
	 */
	_13211228_wuhaonan_7_CopositeStrategy() {
		strategies = new _13211228_wuhaonan_7_IPricingStrategy[100];
		num = 0;
	}

	/**
	 * 添加一个策略
	 * @param A 策略类
	 */
	public void add(_13211228_wuhaonan_7_IPricingStrategy A) {
		strategies[num++] = A;
	}

	/**
	 * 根据购买策略获得价格
	 * @param cur 销售项目
	 * @return 价格
	 */
	public double getSubTotal(_13211228_wuhaonan_7_SaleLineItem cur) {
		double tot;
		tot = cur.getItem().get_price() * cur.getNum();
		return tot;
	}

	/**
	 * 返回优惠信息
	 * @return 优惠信息
	 */
	public String getString() {
		String res = "";
		for (int i = 0; i < num; i++) {
			res = res + strategies[i].getString();
			if (i != num - 1) res = res + " | ";
		}
		return res;
	}

}
