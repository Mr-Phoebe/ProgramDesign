/**
 * Title: QICQ聊天系统登录程序 
 * Description: 聊天服务器 
 * Copyright: Copyright (c) 2015
 * 
 * 封装注册信息 用于发送聊天和在线用户的信息 聊天信息序列化 退出信息序列化
 * 
 * @author 吴浩男
 * @version 1.0
 */

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintStream;
import java.net.Socket;
import java.util.Date;
import java.util.Vector;


public class Connection extends Thread {
	private Socket netClient; // 与客户端通讯Socket

	private Vector<Customer> userOnline; // 在线用户列表

	private Vector<Chat> userChat; // 聊天信息

	private ObjectInputStream fromClient; // 从客户到服务器 输入流

	private PrintStream toClient; // 传到客户端 打印流

	private static Vector vList = new Vector();// 注册用户列表

	private Object obj; // 临时对象

	private ServerFrame sFrame; // 服务器日志窗体

	@SuppressWarnings("unchecked")
	// 创建与客户端通讯
	public Connection(ServerFrame frame, Socket client,
					Vector u, Vector c) {
		netClient = client;
		userOnline = u;
		userChat = c;
		sFrame = frame;
		// 发生双向通信
		try {
			// 检索客户输入
			fromClient = new ObjectInputStream(netClient.getInputStream());
			// 服务器写到客户
			toClient = new PrintStream(netClient.getOutputStream());
		} catch (IOException e) {
			try {
				netClient.close();
			} catch (IOException e1) {
				System.out.println("不能建立流" + e1);
				return;
			}
		}
		this.start();
	}

	// 处理与客户端的通讯线程
	public void run() {
		try {// obj是Object类的对象
			obj = (Object) fromClient.readObject();
			if (obj.getClass().getName().equals("Customer")) {
				serverLogin();
			} else if (obj.getClass().getName().equals("Register_Customer")) {
				serverRegiste();
			} else if (obj.getClass().getName().equals("Message")) {
				serverMessage();
			} else if (obj.getClass().getName().equals("Chat")) {
				serverChat();
			} else if (obj.getClass().getName().equals("Exit")) {
				serverExit();
			} else if (obj.getClass().getName().equals("Change_Customer")) {
				serverChange();
			}
		} catch (IOException e) {
			System.out.println(e);
		} catch (ClassNotFoundException e1) {
			System.out.println("读对象发生错误！" + e1);
		} finally {
			try {
				netClient.close();
			} catch (IOException e) {
				System.out.println(e);
			}
		}
	}

	@SuppressWarnings("deprecation")
	// 登录处理
	public void serverLogin() {

		try {
			Customer clientMessage = (Customer) obj;
			// 读文件
			FileInputStream file = new FileInputStream("user.txt");
			ObjectInputStream objInput1 = new ObjectInputStream(file);
			vList = (Vector) objInput1.readObject();
//			System.out.println("传输：" + clientMessage.custName.toString() + 
//					" " + clientMessage.custPassword.toString());
			int find = 0; // 查找判断标志
			// System.out.println(find);
			for (int i = 0; i < vList.size(); i++) {
				Register_Customer reg = (Register_Customer) vList.elementAt(i);
				//System.out.println(reg.custName + 
				//		" " + reg.custPassword);
				if (reg.custName.equals(clientMessage.custName)) {
					find = 1;
					if (!reg.custPassword.equals(clientMessage.custPassword)) {
						toClient.println("密码不正确");
						break;
					} else {
						// 判断是否已经登录
						int login_flag = 0;
						for (int a = 0; a < userOnline.size(); a++) {
							String _custName = ((Customer) userOnline
									.elementAt(a)).custName;
							if (clientMessage.custName.equals(_custName)) {
								login_flag = 1;
								break;
							}
						}

						if (userOnline.size() >= 50) {
							toClient.println("登录人数过多，请稍候再试");
							break;
						}

						if (login_flag == 0) {
							clientMessage.custHead = reg.head;// getUserHeadByName(clientMessage.custName);
							userOnline.addElement(clientMessage);
							// System.out.println("Login:"
							// + clientMessage.custName + ":"
							// + clientMessage.custHead);
							// userOnline.addElement(clientMessage.custName);
							// 该用户名何在
							toClient.println("登录成功");
							Date t = new Date();
							// System.out.println("用户" + clientMessage.custName
							// + "登录成功，" + "登录时间:" + t.toLocaleString()
							// + "\n");
							log("用户" + clientMessage.custName + "登录成功，"
									+ "登录时间:" + t.toLocaleString() + "\n");
							freshServerUserList();
							break;
						} else {
							toClient.println("该用户已登录");
						}
					}
				} else {
					continue;
				}
			}
			if (find == 0) {
				toClient.println("没有这个用户，请先注册");
			}

			file.close();
			objInput1.close();
			fromClient.close();
		} catch (ClassNotFoundException e) {
			System.out.println(e);
		} catch (IOException e) {
			System.out.println(e);
		}
	}

	// 刷新服务器日志窗体在线列表
	private void freshServerUserList() {
		String[] userList = new String[50];
		Customer cus = null;
		for (int j = 0; j < userOnline.size(); j++) {
			cus = (Customer) userOnline.get(j);
			userList[j] = cus.custName;
		}
		sFrame.list.setListData(userList);
		sFrame.txtNumber.setText("" + userOnline.size());
		sFrame.lblUserCount.setText("当前在线人数:" + userOnline.size());
		// System.out.println("fresh ok");
	}

	@SuppressWarnings({ "unchecked", "deprecation" })
	// 注册处理
	public void serverRegiste() {
		try {
			int flag = 0; // 是否重名判断标志
			Register_Customer clientMessage = (Register_Customer) obj;
			File fList = new File("user.txt");
			if (fList.length() != 0)// 判断是否是第一个注册用户
			{
				ObjectInputStream objInput = new ObjectInputStream(
						new FileInputStream(fList));
				vList = (Vector) objInput.readObject();
				// 判断是否有重名
				for (int i = 0; i < vList.size(); i++) {
					Register_Customer reg = (Register_Customer) vList
							.elementAt(i);
					if (reg.custName.equals(clientMessage.custName)) {
						toClient.println("注册名重复,请另外选择");
						flag = 1;
						break;
					} else if (reg.custName.equals("所有人")) {
						toClient.println("禁止使用此注册名,请另外选择");
						flag = 1;
						break;
					}
				}
			}
			if (flag == 0) {
				// 添加新注册用户
				vList.addElement(clientMessage);
				// 将向量中的类写回文件
				FileOutputStream file = new FileOutputStream(fList);
				ObjectOutputStream objout = new ObjectOutputStream(file);
				objout.writeObject(vList);

				// 发送注册成功信息
				toClient.println(clientMessage.custName + "注册成功");
				Date t = new Date();
				// append("用户"+clientMessage.custName+"注册成功!;注册时间:"+t.toLocaleString()+"\n");
				// System.out.println("用户" + clientMessage.custName + "注册成功, "
				// + "注册时间:" + t.toLocaleString() + "\n");

				log("用户" + clientMessage.custName + "注册成功, " + "注册时间:"
						+ t.toLocaleString() + "\n");
				file.close();
				objout.close();
				fromClient.close();
			}
		} catch (ClassNotFoundException e) {
			System.out.println(e);
		} catch (IOException e) {
			System.out.println(e);
		}
	}
	
	@SuppressWarnings({ "unchecked", "deprecation" })
	// 修改密码处理
	public void serverChange() {

		try {
			Change_Customer clientMessage = (Change_Customer) obj;
			// 读文件
			File fList = new File("user.txt");
			FileInputStream file = new FileInputStream(fList);
			ObjectInputStream objInput1 = new ObjectInputStream(file);
			vList = (Vector) objInput1.readObject();

			int find = 0; // 查找判断标志
			int login_flag = 0;// 判断是否已经登录
			Register_Customer reg = null;
			for (int i = 0; i < vList.size(); i++) {
				reg = (Register_Customer) vList.elementAt(i);

				if (reg.custName.equals(clientMessage.custName)) {
					find = 1;	// 找到该用户，该用户已经注册
					if (!reg.custPassword.equals(clientMessage.custPassword)) {
						toClient.println("原密码不正确");	// 原来的密码不正确
					} else {
						vList.remove(i);
						reg.custPassword = clientMessage.newPassword;
						// 判断是否已经登录
						for (int a = 0; a < userOnline.size(); a++) {
							String _custName = ((Customer) userOnline
									.elementAt(a)).custName;
							if (clientMessage.custName.equals(_custName)) {
								login_flag = 1;
								break;
							}
						}
					}
					break;
				}else {
					continue;
				}
			}
			file.close();
			if (find == 0) {
				toClient.println("没有这个用户，请先注册");
			} else if(login_flag == 1) {
				toClient.println("该用户已登录，不能修改密码");
			} else {
				// 添加修改密码用户
				vList.addElement(reg);
				// 将向量中的类写回文件
				FileOutputStream file2 = new FileOutputStream(fList);
				ObjectOutputStream objout = new ObjectOutputStream(file2);
				objout.writeObject(vList);

				// 发送注册成功信息
				toClient.println(clientMessage.custName + "修改密码成功");
				Date t = new Date();
				// append("用户"+clientMessage.custName+"注册成功!;注册时间:"+t.toLocaleString()+"\n");
				// System.out.println("用户" + clientMessage.custName + "注册成功, "
				// + "注册时间:" + t.toLocaleString() + "\n");

				log("用户" + clientMessage.custName + "修改密码成功, " + "修改时间:"
						+ t.toLocaleString() + "\n");
			}
			objInput1.close();
			fromClient.close();
		} catch (ClassNotFoundException e) {
			System.out.println(e);
		} catch (IOException e) {
			System.out.println(e);
		}
	}

	// 发送信息处理
	public void serverMessage() {
		try {
			Message mess = new Message(userOnline,
							userChat,
							sFrame.ti,
							"" + sFrame.serverMessage);
			// log("s:" + mess.serverMessage);
			// mess.chat = WordFilter.filter(mess.chat.get(index));

			ObjectOutputStream outputstream = new ObjectOutputStream(
					netClient.getOutputStream());
			outputstream.writeObject((Message) mess);

			// server list
			// sFrame.list.setListData(new String[] { "3", "4", "5" });
			netClient.close();
			outputstream.close();
		} catch (IOException e) {
			System.out.println(e);
		}

	}

	// 增加信息处理
	public void serverChat() {
		// 将接收到的对象值赋给聊天信息的序列化对象
		Chat cObj = new Chat();
		cObj = (Chat) obj;
		cObj.chatMessage = WordFilter.filter(cObj.chatMessage);
		chatLog(cObj);
		// 将聊天信息的序列化对象填加到保存聊天信息的矢量中
		userChat.addElement((Chat) cObj);
		return;
	}

	// 用户退出处理
	@SuppressWarnings("deprecation")
	public void serverExit() {
		Exit exit = new Exit();
		exit = (Exit) obj;

		removeUser(exit);

		if (sFrame.ti.equals(exit.exitName)) {
			sFrame.ti = "";
		}

		Date t = new Date();

		log("用户" + exit.exitName + "已经退出, " + 
				"退出时间:" + t.toLocaleString() + "\n");

		freshServerUserList();
	}

	/**
	 * 在线用户中删除退出用户
	 * 
	 * @param exit
	 *            退出用户名对象
	 */
	private void removeUser(Exit exit) {
		// TODO 自动生成方法存根
		Vector<Customer> vec = new Vector<Customer>();
		Customer _cus = null;
		for (int j = 0; j < userOnline.size(); j++) {
			_cus = (Customer) userOnline.get(j);
			if (!exit.exitName.equals(_cus.custName)) {
				vec.add(_cus);
			}
			// System.out.println("list:"+_cus.custName);
		}
		userOnline.removeAllElements();
		for (int j = 0; j < vec.size(); j++) {
			_cus = (Customer) vec.get(j);
			userOnline.add(_cus);
		}
		// userOnline = vec;

	}

	/**
	 * 日志服务器窗体写 信息
	 * 
	 * @param log
	 *            日志信息
	 */
	public void log(String log) {
		String newlog = sFrame.taLog.getText() + "\n" + log;
		sFrame.taLog.setText(newlog);
	}

	/**
	 * 日志服务器窗体写聊天 信息
	 * 
	 * @param obj
	 *            聊天 信息对象
	 */
	@SuppressWarnings("deprecation")
	public void chatLog(Chat obj) {
		String newlog = sFrame.taMessage.getText();
		Date date = new Date();
		if (!obj.whisper) {
			newlog += "\n";
			newlog += ("[" + date.getHours() + ":" + date.getMinutes() + ":"
					+ date.getSeconds() + "]");
			newlog += obj.chatUser;
			newlog += "->";
			newlog += obj.chatToUser;
			newlog += ":";
			newlog += obj.chatMessage;
		}

		sFrame.taMessage.setText(newlog);
	}
}