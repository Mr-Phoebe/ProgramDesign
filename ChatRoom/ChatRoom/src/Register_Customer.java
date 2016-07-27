
public class Register_Customer extends Object implements java.io.Serializable {

	private static final long serialVersionUID = 7116984729771538742L;

	public String custName; // 姓名

	public String custPassword; // 密码

	public String age; // 年龄

	public String sex; // 性别

	public String email; // 电子邮件

	public String head; // 头像文件名
	
	public Register_Customer() {
		// TODO Auto-generated constructor stub
	}
	
	public Register_Customer(String name, String pass, String _age,
			String _sex, String _email, String _head) {
		custName = name;
		custPassword = pass;
		age = _age;
		sex = _sex;
		email = _email;
		head = _head;
	}
}

