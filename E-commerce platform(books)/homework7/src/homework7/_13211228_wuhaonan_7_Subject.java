package homework7;

/**
 * 被观察者接口
 * 用于观察者模式
 */
public interface _13211228_wuhaonan_7_Subject {
	/**
	 * 删除观察者接口
	 * @param cur 观察者接口
	 */
	public void removeObserve(_13211228_wuhaonan_7_Observer cur);

	/**
	 * 添加观察者接口
	 * @param cur 观察者接口
	 */
	public void registerObserver(_13211228_wuhaonan_7_Observer cur);

	/**
	 * 更新观察者接口
	 */
	public void notifyObservers();
}
