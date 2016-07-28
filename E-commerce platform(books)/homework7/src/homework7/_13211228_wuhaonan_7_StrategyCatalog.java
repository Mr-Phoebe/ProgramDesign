package homework7;

import java.util.HashMap;

/**
 * 定价策略目录
 */
public class _13211228_wuhaonan_7_StrategyCatalog {
	private HashMap<Integer, _13211228_wuhaonan_7_IPricingStrategy> mp;

	/**
	 * 构造函数，并用hash表存储
	 */
	_13211228_wuhaonan_7_StrategyCatalog() {
		mp = new HashMap<Integer, _13211228_wuhaonan_7_IPricingStrategy>();
		for (int i = 0; i < 5; i++)
			mp.put(i, new _13211228_wuhaonan_7_NoDiscountStrategy());
	}

	/**
	 * 删除定价策略
	 * @param key 图书的类型
	 */
	public void del(int key) {
		mp.put(key, new _13211228_wuhaonan_7_NoDiscountStrategy());
	}

	/**
	 * 添加定价策略
	 * @param key 图书类型
	 * @param val 定价策略
	 */
	public void insert(int key, _13211228_wuhaonan_7_IPricingStrategy val) {
		mp.put(key, val);
	}

	/**
	 * 查找定价策略
	 * @param key 图书类型
	 * @return 返回定价策略
	 */
	public _13211228_wuhaonan_7_IPricingStrategy getVal(int key) {
		return mp.get(key);
	}

	/**
	 * 返回定价策略目录大小
	 * @return 定价策略目录大小
	 */
	public int getSize() {
		return mp.size();
	}
}
