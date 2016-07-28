package homework7;

/**
 * 最佳组合策略
 */
public class _13211228_wuhaonan_7_CompositeBestForCustomer extends _13211228_wuhaonan_7_CopositeStrategy {
	/**
	 * 根据销售项目与策略获得价格
	 * @param cur 销售项目
	 * @return 价格
	 */
	public double getSubTotal(_13211228_wuhaonan_7_SaleLineItem cur)
	{
		double tot = -1;
		for (int i = 0; i < num; i++)
		{
			if (tot == -1)
				tot = strategies[i].getSubTotal(cur);
			else
				tot = Math.min(tot, strategies[i].getSubTotal(cur));
		}
		return tot;
	}

}
