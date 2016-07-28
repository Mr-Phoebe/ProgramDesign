package homework7;

/**
 * 不进行优惠的策略
 */

public class _13211228_wuhaonan_7_NoDiscountStrategy implements _13211228_wuhaonan_7_IPricingStrategy {
	/**
	 * 根据销售信息返回价格
	 * @param cur 销售项目
	 * @return 价格
	 */
	public double getSubTotal(_13211228_wuhaonan_7_SaleLineItem cur) {
		double tot;
		tot = cur.getItem().get_price() * cur.getNum();
		return tot;
	}

	/**
	 * 返回优惠信息，但是没有优惠
	 *
	 * @return 空字符串
	 */
	public String getString() {
		return "";
	}

}
