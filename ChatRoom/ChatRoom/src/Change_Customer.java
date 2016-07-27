
public class Change_Customer extends Object implements java.io.Serializable {

	private static final long serialVersionUID = 7114684729771538742L;

	public String custName; // ĞÕÃû

	public String custPassword; // ÃÜÂë

	public String newPassword;
	
	public Change_Customer() {
		// TODO Auto-generated constructor stub
	}
	
	public Change_Customer(String name, String pass, String newPass) {
		custName = name;
		custPassword = pass;
		newPassword = newPass;
	}

}