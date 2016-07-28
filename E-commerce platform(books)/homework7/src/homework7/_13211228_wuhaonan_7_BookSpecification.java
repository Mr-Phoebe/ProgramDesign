package homework7;

/**
 * @author: SuPhoebe
 * Date: 2016/1/4
 * Time: 14:33
 * Name: homework7
 */

/**
 * 书的规格说明，描述一本书的信息。
 * 包括书的isbn号、书名、单价和书的类型。
 */

public class _13211228_wuhaonan_7_BookSpecification {
	/**
	 * 书的isbn号
	 */
	private String isbn;
	/**
	 * 书的书名
	 */
	private String name;
	/**
	 * 书的单价
	 */
	private double price;
	/**
	 * 书的类型
	 */
	private int type;

	/**
	 * 书的规格说明构造函数
	 * @param _isbn		书的isbn号
	 * @param _name		书的书名
	 * @param _price 	书的单价
	 * @param _type		书的类型
	 */
	public _13211228_wuhaonan_7_BookSpecification(String _isbn, String _name, double _price, int _type) {
		isbn = _isbn;
		name = _name;
		price = _price;
		type = _type;
	}

	/**
	 * @return 书的isbn号
	 */
	public String get_isbn() {
		return isbn;
	}

	/**
	 * @return 书的书名
	 */
	public String get_name() {
		return name;
	}

	/**
	 * @return 书的单价
	 */
	public double get_price() {
		return price;
	}

	/**
	 * @return 书的类型
	 */
	public int get_type() {
		return type;
	}

}
