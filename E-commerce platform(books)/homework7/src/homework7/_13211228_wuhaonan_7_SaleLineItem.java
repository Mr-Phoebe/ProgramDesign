package homework7;

/**
 * 销售项目
 */
public class _13211228_wuhaonan_7_SaleLineItem {
	private _13211228_wuhaonan_7_BookSpecification item;
	private int num;
	private _13211228_wuhaonan_7_IPricingStrategy strategy = null;

	/**
	 * 构造函数
	 * @param _isbn 	书的ISBN号
	 * @param _name 	书的名称
	 * @param _price	书的价格
	 * @param _type		书的类型
	 * @param _num		购买的数量
	 */
	public _13211228_wuhaonan_7_SaleLineItem(String _isbn, String _name, double _price, int _type, int _num) {
		item = new _13211228_wuhaonan_7_BookSpecification(_isbn, _name, _price, _type);
		num = _num;
		new _13211228_wuhaonan_7_PricingStrategyFactory();
		strategy = _13211228_wuhaonan_7_PricingStrategyFactory.getInstance().getPricingStreategy(_type);
	}

	/**
	 * 构造函数
	 * @param lala BookSpecification 待购书本的描述
	 * @param _num 书本的个数
	 */
	public _13211228_wuhaonan_7_SaleLineItem(_13211228_wuhaonan_7_BookSpecification lala, int _num) {
		item = lala;
		num = _num;
		new _13211228_wuhaonan_7_PricingStrategyFactory();
		strategy = _13211228_wuhaonan_7_PricingStrategyFactory.getInstance().getPricingStreategy(lala.get_type());
	}

	/**
	 * 获得本销售项目中书的规格说明
	 * @return 书的信息
	 */
	public _13211228_wuhaonan_7_BookSpecification getItem() {
		return item;
	}

	/**
	 * 获得购买书籍的数量
	 * @return 书籍数量
	 */
	public int getNum() {
		return num;
	}

	/**
	 * 获得购买书籍的价格
	 * @return 价格
	 */
	public double getTotal() {
		return strategy.getSubTotal(this);
	}
}
