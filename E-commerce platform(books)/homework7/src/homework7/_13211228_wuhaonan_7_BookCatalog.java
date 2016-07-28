package homework7;
/**
 * @author: SuPhoebe
 * Date: 2016/1/7
 * Time: 14:54
 * Name: homework7
 */

/**
 * 书本信息目录，包括多个书本信息
 */
public class _13211228_wuhaonan_7_BookCatalog {
	private _13211228_wuhaonan_7_BookSpecification[] books = null;
	private int num;

	/**
	 * 书本信息目录构造函数，开辟内存池
	 */
	_13211228_wuhaonan_7_BookCatalog() {
		books = new _13211228_wuhaonan_7_BookSpecification[100];
		num = 0;
	}

	/**
	 * 添加书本，并返回是否已经成功添加
	 * @param A 书本信息类
	 * @return 成功返回true，失败返回false
	 */
	public boolean add(_13211228_wuhaonan_7_BookSpecification A) {
		if (getBookSpecification(A.get_isbn()) == null) {
			books[num] = A;
			num++;
			return true;
		}
		return false;
	}

	/**
	 * 获得书目录的大小
	 * @return 返回现在书本的个数
	 */
	public int getNumber() {
		return num;
	}

	/**
	 * 根据书本目录下标得到书的信息类
	 * @param id 下标
	 * @return	返回书的信息类
	 */
	public _13211228_wuhaonan_7_BookSpecification getItem(int id) {
		return books[id];
	}

	/**
	 * 根据书本的ISBN号得到书的信息类
	 * @param isbn 书的ISBN号
	 * @return	若查找到，则返回相应对象；若没有找到，则返回null
	 */
	public _13211228_wuhaonan_7_BookSpecification getBookSpecification(String isbn) {
		for (int i = 0; i < num; i++) {
			if (books[i].get_isbn().equals(isbn)) {
				return books[i];
			}
		}
		return null;
	}
}
