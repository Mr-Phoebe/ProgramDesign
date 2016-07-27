
import java.io.Serializable;

public class Exit implements Serializable {

	private static final long serialVersionUID = -5267537916643834426L;

	public String exitName; // 退出者用户名
	
	public Exit() {
		// TODO Auto-generated constructor stub
	}
	
	public Exit(String name) {
		exitName = name;
	}
}