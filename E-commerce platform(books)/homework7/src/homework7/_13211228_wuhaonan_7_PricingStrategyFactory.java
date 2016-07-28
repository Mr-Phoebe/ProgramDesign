package homework7;

/**
 * 策略工厂，负责根据书的类型提供对应的策略类
 * 策略类将根据具体的优惠策略计算折扣后1个销售项目（SaleLineItem）的总价
 * 设计成单子
 */

public class _13211228_wuhaonan_7_PricingStrategyFactory {
	/**
	 * 设计成单子模式
	 */
	private static _13211228_wuhaonan_7_PricingStrategyFactory single = null;

	/**
	 * 初始化定价策略目录
	 */
	_13211228_wuhaonan_7_PricingStrategyFactory() {
		catalog = new _13211228_wuhaonan_7_StrategyCatalog();
	}

	/**
	 * 单子模型下，获得策略工厂对象
	 * @return 单子模式下的策略工厂
	 */
	public static _13211228_wuhaonan_7_PricingStrategyFactory getInstance() {
		if (single == null) {
			single = new _13211228_wuhaonan_7_PricingStrategyFactory();
		}
		return single;
	}

	/**
	 * 定价策略目录
	 */
	private _13211228_wuhaonan_7_StrategyCatalog catalog = null;

	/**
	 * 添加定价策略
	 * @param key 键值
	 * @param val 策略类的接口
	 */
	public void addStrategy(int key, _13211228_wuhaonan_7_IPricingStrategy val) {
		catalog.insert(key, val);
	}

	/**
	 * 删除定价策略
	 * @param key 键值
	 */
	public void delStrategy(int key) {
		catalog.del(key);
	}

	/**
	 * 根据书的类型获得定价策略
	 * @param booktype 书的类型
	 * @return 定价策略
	 */
	public _13211228_wuhaonan_7_IPricingStrategy getPricingStreategy(int booktype) {
		return catalog.getVal(booktype);
	}

	/**
	 * 设置定价策略目录
	 * @param lala 定价策略目录
	 */
	public void setCatalog(_13211228_wuhaonan_7_StrategyCatalog lala) {
		catalog = lala;
	}
}
