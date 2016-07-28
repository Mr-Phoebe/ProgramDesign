package homework7;

/**
 * 控制器，所有来自UI的请求会发给该控制器对象，由控制器对象再转发给其他领域对象
 * 控制器中包含三个属性：
 * (1) BookCatalog
 * (2) StrategyCatalog
 * (3) Sale
 */
public class _13211228_wuhaonan_7_Controller {
	private _13211228_wuhaonan_7_BookCatalog bookset;
	private _13211228_wuhaonan_7_StrategyCatalog catalog = null;
	private _13211228_wuhaonan_7_Sale cur_Sale = null;

	/**
	 * 控制器的构造函数，为三个属性申请内存空间
	 */
	_13211228_wuhaonan_7_Controller() {
		bookset = new _13211228_wuhaonan_7_BookCatalog();
		catalog = new _13211228_wuhaonan_7_StrategyCatalog();
		cur_Sale = new _13211228_wuhaonan_7_Sale();
	}

	/**
	 * 添加组合策略
	 * 以kk为键,tmp为值 加入到hashMap中
	 * @param kk 表示此策略对应的书的种类
	 * @param tmp　对应的策略
	 */
	public void addCompositeStrategy(int kk, _13211228_wuhaonan_7_IPricingStrategy tmp) {
		catalog.insert(kk, tmp);
		new _13211228_wuhaonan_7_PricingStrategyFactory();
		_13211228_wuhaonan_7_PricingStrategyFactory.getInstance().setCatalog(catalog);
	}

	/**
	 * 添加简单策略
	 * 以kk为键,tmp为值 加入到hashMap中
	 * @param kk 表示此策略对应的书的种类
	 * @param tmp 对应的策略
	 */
	public void addSimpleStrategy(int kk, _13211228_wuhaonan_7_IPricingStrategy tmp) {
		catalog.insert(kk, tmp);
		new _13211228_wuhaonan_7_PricingStrategyFactory();
		_13211228_wuhaonan_7_PricingStrategyFactory.getInstance().setCatalog(catalog);
	}

	/**
	 * 删除策略
	 * 将key种类的书所对应的策略设为无优惠策略
	 * @param key 表示此策略对应的书的种类
	 */
	public void deleteStrategy(int key) {
		catalog.del(key);
		new _13211228_wuhaonan_7_PricingStrategyFactory();
		_13211228_wuhaonan_7_PricingStrategyFactory.getInstance().setCatalog(catalog);
	}

	/**
	 * 更新策略
	 * 将键kk所对应的值更新成tmp
	 * @param kk 表示此策略对应的书的种类
	 * @param tmp 对应的策略
	 */
	public void updateStrategy(int kk, _13211228_wuhaonan_7_IPricingStrategy tmp) {
		catalog.insert(kk, tmp);
		new _13211228_wuhaonan_7_PricingStrategyFactory();
		_13211228_wuhaonan_7_PricingStrategyFactory.getInstance().setCatalog(catalog);
	}

	/**
	 * 购书函数，向Sale中添加新的SaleLineItem项
	 * @param isbn　表示要购买书的isbn码
	 * @param num 表示要购买的数量
	 * @return true表示此isbn码所对应的书存在,购买成功. false表示此isbn码对应的书不存在，购买失败.
	 */
	public boolean buyBook(String isbn, int num) {
		_13211228_wuhaonan_7_BookSpecification spec = bookset.getBookSpecification(isbn);
		if (spec == null) return false;
		cur_Sale.addItem(new _13211228_wuhaonan_7_SaleLineItem(spec, num));
		cur_Sale.notifyObservers();
		return true;
	}

	/**
	 * 通过此函数调用私有属性Sale
	 * @return Sale
	 */
	public _13211228_wuhaonan_7_Sale getSale() {
		return cur_Sale;
	}

	/**
	 *　通过此函数调用私有属性BookCatalog
	 * @return 返回书本目录
	 */
	public _13211228_wuhaonan_7_BookCatalog getBookCatalog() {
		return bookset;
	}

	/**
	 * 通过此函数调用私有属性getStrategyCatalog
	 * @return 返回销售策略目录
	 */
	public _13211228_wuhaonan_7_StrategyCatalog getStrategyCatalog() {
		return catalog;
	}

	/**
	 * 向Sale中添加新的观察者
	 * @param cur　表示待添加的观察值
	 */
	public void addObserver(_13211228_wuhaonan_7_Observer cur) {
		cur_Sale.registerObserver(cur);
	}

}
