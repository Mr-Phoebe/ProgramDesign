
public class Table {
	private static int[] table[] = new int[15][15];
	public Table()
	{
		for(int i = 0; i < 15; i++)
			for(int j = 0; j < 15; j++)
				table[i][j] = 0;
	}
	
	public void updateTable(int x, int y, int w)
	{
		if(x >= 0 && x < 15 && y >= 0 && y < 15 && w>=1 && w<=2)
			table[x][y] = w;
	}

	public String changeCmd(String str)
	{
		String cmd = new String(str);
		for(int i = 0; i < 15; i++) {
			for(int j = 0; j < 15; j++){
				cmd += table[i][j];
			}
			cmd += " ";
		}
		return cmd;
	}
	
	public boolean find(int x, int y, int dirx, int diry, int w)
	{
		int tot = 5;
		int num = 0;
		for(int i = x, j = y; tot > 0 && i > 0 && i < 15 && j > 0 && j < 15; i += dirx, j += diry, tot--)
			if(table[i][j] == w)
				num++;
		if(num == 5)	return true;
		return false;
	}
	
	public int getTable(int x, int y)
	{
		return table[x][y];
	}
	
	public void showAll()
	{
		for(int i= 0 ; i < 15; i++){
			for(int j = 0; j < 15; j++)
				System.out.print(table[i][j]);
			System.out.println();
		}
	}
}
