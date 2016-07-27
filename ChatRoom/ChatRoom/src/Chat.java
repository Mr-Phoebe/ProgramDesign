/**
 * Title: QICQ聊天系统登录程序
 * Description: 聊天内容对象 
 * Copyright: Copyright (c) 2015
 * 
 * @author 吴浩男
 * @version 1.0
 */

import java.io.Serializable;
import java.security.PublicKey;

public class Chat implements Serializable {

	private static final long serialVersionUID = 4058485121419391969L;
	public String chatUser; // 发言人用户名
	
	public String chatMessage; // 聊天内容
	
	public String chatToUser; // 接受对象用户名
	
	public String emote; // 聊天表情
	
	public boolean whisper; // 是否私聊
	
	public Chat() {
		// TODO Auto-generated constructor stub
	}
	
	public Chat(String User, String message,
			String toUser, boolean flag, String emotion) {
		chatUser = User;
		chatMessage = message;
		chatToUser = toUser;
		emote = emotion;
		whisper = flag;
	}
}