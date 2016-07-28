package homework7;

/**
 * 按百分比进行优惠的策略
 */
public class _13211228_wuhaonan_7_PercentageStrategy implements _13211228_wuhaonan_7_IPricingStrategy {
	/**
	 * 折扣
	 */
	private int discountPercentage;

	/**
	 * 构造函数，将折扣初始化为10
	 */
	public _13211228_wuhaonan_7_PercentageStrategy() {
		discountPercentage = 10;
	}

	/**
	 * 构造函数，将将折扣初始化为参数值
	 * @param discount 折扣
	 */
	public _13211228_wuhaonan_7_PercentageStrategy(int discount) {
		discountPercentage = discount;
	}

	/**
	 * 将折扣修改为参数值
	 * @param discount 折扣
	 */
	public void setDiscount(int discount) {
		discountPercentage = discount;
	}

	/**
	 * 根据销售项目与销售策略返回价格
	 * @param cur 销售项目
	 * @return 价格
	 */
	public double getSubTotal(_13211228_wuhaonan_7_SaleLineItem cur) {
		double tot;
		tot = (cur.getItem().get_price() * discountPercentage / 100.0) * cur.getNum();
		return tot;
	}

	/**
	 * 返回优惠信息
	 * @return 优惠信息
	 */
	public String getString() {
		return "折扣" + (double) discountPercentage / 100.0;
	}
}

