package homework7;

/**
 * 立减策略(每本优惠x元)
 */


public class _13211228_wuhaonan_7_FlatRateStrategy implements _13211228_wuhaonan_7_IPricingStrategy {
	private double discountPerBook;

	/**
	 * 构造函数，将优化价格设置为1
	 */
	public _13211228_wuhaonan_7_FlatRateStrategy() {
		discountPerBook = 1;
	}

	/**
	 * 构造函数，将优化价格设置为discount
	 * @param discount 优惠价格
	 */
	public _13211228_wuhaonan_7_FlatRateStrategy(double discount) {
		discountPerBook = discount;
	}

	/**
	 * 设置优惠价格
	 * @param discount	优惠价格
	 */
	public void setDiscount(double discount) {
		discountPerBook = discount;
	}

	/**
	 * 根据购买情况返回价格
	 * @param cur 销售项目
	 * @return double 价格
	 */
	public double getSubTotal(_13211228_wuhaonan_7_SaleLineItem cur) {
		double tot;
		tot = (cur.getItem().get_price() - discountPerBook) * cur.getNum();
		return tot;
	}

	/**
	 * 返回优惠信息
	 *
	 * @return String 优惠信息
	 */
	public String getString() {
		String res = "立减" + discountPerBook;
		return res;
	}

}
