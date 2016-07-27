import java.io.Serializable;
import java.util.Vector;

public class Message implements Serializable {

	private static final long serialVersionUID = -3831507106408529855L;

	public Vector userOnLine; // 用户在线对象集

	public Vector chat; // 聊天信息集

	public String ti; // 被踢者姓名

	public String serverMessage;// 公告
	
	public Message() {
		
	}
	
	public Message(Vector userlist, Vector chatVector,
			String dele, String announcement) {
		userOnLine = userlist;
		chat = chatVector;
		ti = dele;
		serverMessage = announcement;
	}

}