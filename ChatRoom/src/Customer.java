
public class Customer extends Object implements java.io.Serializable {

	private static final long serialVersionUID = -9215977405584592618L; // 版本控制

	public String custName; // 用户名

	public String custPassword; // 密码

	public String custHead; // 用户头像
	
	public Customer() {
		// TODO Auto-generated constructor stub
	}
	
	public Customer(String name, String pass, String head) {
		custName = name;
		custPassword = pass;
		custHead = head;
	}
}