package homework7;

/**
 * 策略类的接口，用于向SaleLineItem屏蔽具体的策略类
 */


public interface _13211228_wuhaonan_7_IPricingStrategy {

	/**
	 * 用于子类继承
	 * @param cur 销售项目
	 * @return 价格
	 */
	public double getSubTotal(_13211228_wuhaonan_7_SaleLineItem cur);

	/**
	 * 用于子类继承
	 * @return 优惠信息
	 */
	public String getString();

}
