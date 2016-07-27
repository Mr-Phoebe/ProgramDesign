import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import java.awt.*;
import java.awt.event.*;
import java.net.*;
import java.io.*;
import java.util.*;

/**
 * Title: QICQ聊天系统登录程序
 * Description: 系统用户登录后进行聊天 
 * Copyright: Copyright (c) 2015
 * 
 * @author 吴浩男
 * @version 1.0
 */

public class ChatRoom extends Thread implements ActionListener {
	private JComboBox sizeComboBox; // 大小
	private JComboBox styleComboBox; // 样式
	private JComboBox fontComboBox; // 字体
	private JComboBox emote; // 表情

	static JFrame frmChat;

	JPanel pnlChat;

	JButton btnCls, btnExit, btnSend, btnClear, btnSave, btnTimer;

	JLabel lblUserList, lblUserMessage, lblSendMessage, lblChatUser;
	JLabel lblUserTotal, lblCount, lblBack;

	JTextField txtMessage;

	java.awt.List lstUserList;

	TextArea taUserMessage;

	JComboBox cmbUser;

	JCheckBox chPrivateChat;

	String strServerIp, strLoginName;

	Thread thread;

	final JLabel headLabel = new JLabel();

	// 用于将窗口用于定位
	Dimension scrnsize;

	Toolkit toolkit = Toolkit.getDefaultToolkit();

	Message messobj = null;

	String serverMessage = "";

	// 颜色滑条
	final JSlider blueSlider = new JSlider();
	final JSlider redSlider = new JSlider();
	final JSlider greenSlider = new JSlider();

	final JLabel characterLabel = new JLabel();

	// 构造方法
	public ChatRoom(String name, String ip) {
		// Dialog d = new FontDialog();
		strServerIp = ip;
		strLoginName = name;
		frmChat = new JFrame("聊天室" + "[用户:" + name + "]");
		pnlChat = new JPanel();
		frmChat.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frmChat.getContentPane().add(pnlChat);

		Font fntDisp1 = new Font("宋体", Font.PLAIN, 12);

		btnCls = new JButton("清屏(C)");
		btnExit = new JButton("退出(X)");
		btnSend = new JButton("发送(N)");
		btnSave = new JButton("保存(S)");
		btnTimer = new JButton("时钟(T)");
		lblUserList = new JLabel("【在线用户列表】");
		lblUserMessage = new JLabel("【聊天信息】");
		lblSendMessage = new JLabel("聊天内容:");
		lblChatUser = new JLabel("你对:");
		lblUserTotal = new JLabel("在线人数:");
		lblCount = new JLabel("0");
		lstUserList = new java.awt.List();
		txtMessage = new JTextField(170);
		
		String list[] = { "所有人" };
		cmbUser = new JComboBox(list);			// 聊天对象初始化为所有人
		cmbUser.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent arg0) {
				freshHead();
			}
		});
		chPrivateChat = new JCheckBox("私聊");
		taUserMessage = new TextArea("", 300, 200,
				TextArea.SCROLLBARS_VERTICAL_ONLY);// 只能向下滚动
		// taUserMessage.setText("HAHA");
		taUserMessage.setForeground(new Color(0, 0, 0));
		taUserMessage.setEditable(false); // 不可写入

		/**
		 * 该布局采用手动布局 setBounds设置组件位置 setFont设置字体、字型、字号 setForeground设置文字的颜色
		 * setBackground设置背景色 setOpaque将背景设置为透明
		 */
		// -----------位置按钮--------------//
		pnlChat.setLayout(null);
		pnlChat.setBackground(new Color(52, 130, 203));
		btnTimer.setBounds(400, 360, 80, 25);
		btnSave.setBounds(500, 330, 80, 25);
		btnCls.setBounds(400, 330, 80, 25);
		btnExit.setBounds(500, 360, 80, 25);
		btnSend.setBounds(500, 300, 80, 25);

		lblUserList.setBounds(5, 0, 120, 40);
		lblUserTotal.setBounds(130, 0, 60, 40);
		lblCount.setBounds(190, 0, 60, 40);
		lblUserMessage.setBounds(225, 0, 180, 40);
		lblChatUser.setBounds(10, 290, 40, 40);
		lblSendMessage.setBounds(210, 290, 60, 40);

		// lblUserTotal.setBounds(10,340,100,40);
		// lblCount.setBounds(73,340,100,40);
		lstUserList.setBounds(5, 40, 210, 255);
		taUserMessage.setBounds(225, 40, 360, 255);
		txtMessage.setBounds(270, 300, 210, 25);
		cmbUser.setBounds(50, 300, 80, 25);
		chPrivateChat.setBounds(333, 336, 60, 20);
		btnTimer.setFont(fntDisp1);
		btnCls.setFont(fntDisp1);
		btnExit.setFont(fntDisp1);
		btnSend.setFont(fntDisp1);
		btnSave.setFont(fntDisp1);
		lblUserList.setFont(fntDisp1);
		lblUserMessage.setFont(fntDisp1);
		lblChatUser.setFont(fntDisp1);
		lblSendMessage.setFont(fntDisp1);
		lblUserTotal.setFont(fntDisp1);
		lblCount.setFont(fntDisp1);
		cmbUser.setFont(fntDisp1);
		chPrivateChat.setFont(fntDisp1);

		lblUserList.setForeground(Color.YELLOW);
		lblUserMessage.setForeground(Color.YELLOW);
		lblSendMessage.setForeground(Color.black);
		lblChatUser.setForeground(Color.black);
		lblSendMessage.setForeground(Color.black);
		lblUserTotal.setForeground(Color.YELLOW);
		lblCount.setForeground(Color.YELLOW);
		cmbUser.setForeground(Color.black);
		chPrivateChat.setForeground(Color.black);
		lstUserList.setBackground(Color.white);
		taUserMessage.setBackground(Color.white);
		btnTimer.setBackground(Color.ORANGE);
		btnCls.setBackground(Color.ORANGE);
		btnExit.setBackground(Color.ORANGE);
		btnSend.setBackground(Color.PINK);
		btnSave.setBackground(Color.ORANGE);
		pnlChat.add(btnTimer);
		pnlChat.add(btnCls);
		pnlChat.add(btnExit);
		pnlChat.add(btnSend);
		pnlChat.add(btnSave);
		pnlChat.add(lblUserList);
		pnlChat.add(lblUserMessage);
		pnlChat.add(lblSendMessage);
		pnlChat.add(lblChatUser);
		pnlChat.add(lblUserTotal);
		pnlChat.add(lblCount);
		pnlChat.add(lstUserList);
		pnlChat.add(taUserMessage);
		pnlChat.add(txtMessage);
		pnlChat.add(cmbUser);
		pnlChat.add(chPrivateChat);

		frmChat.addWindowListener(new Windowclose());
		btnTimer.addActionListener(this);
		btnCls.addActionListener(this);
		btnExit.addActionListener(this);
		btnSend.addActionListener(this);
		btnSave.addActionListener(this);
		lstUserList.addActionListener(this);
		txtMessage.addActionListener(this);

		headLabel.setHorizontalAlignment(SwingConstants.CENTER);
		headLabel.setIcon(new ImageIcon("resource/face/1.JPG"));
		headLabel.setBounds(15, 335, 70, 60);
		pnlChat.add(headLabel);

		// -----------位置按钮--------------//

		// -----------聊天字体样式--------------//

		emote = new JComboBox();
		emote.setModel(new DefaultComboBoxModel(new String[] { "表情", "微笑",
				"甜笑", "惊喜", "嘻嘻", "扮酷", "傻笑", "好奇", "媚眼", "鬼脸", "陶醉", "害羞",
				"生气", "发怒", "伤心", "高明", "菜鸟", "问号", "狂笑", "大哭", "示爱", "呻吟",
				"想想" }));
		emote.setBounds(141, 301, 60, 23);
		pnlChat.add(emote);

		fontComboBox = new JComboBox();
		fontComboBox.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent arg0) {
				freshFont();
			}

		});
		fontComboBox.setModel(new DefaultComboBoxModel(new String[] { "宋体",
				"黑体" }));
		fontComboBox.setBounds(76, 337, 64, 23);
		pnlChat.add(fontComboBox);

		styleComboBox = new JComboBox();
		styleComboBox.setModel(new DefaultComboBoxModel(new String[] { "正规",
				"粗体", "斜体", "粗斜" }));
		styleComboBox.setBounds(153, 337, 52, 23);
		styleComboBox.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent arg0) {
				freshFont();
			}

		});
		pnlChat.add(styleComboBox);

		sizeComboBox = new JComboBox();
		sizeComboBox.setModel(new DefaultComboBoxModel(new String[] { "12",
				"14", "16", "18", "20" }));
		sizeComboBox.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent arg0) {
				freshFont();
			}

		});
		sizeComboBox.setBounds(220, 335, 40, 23);
		pnlChat.add(sizeComboBox);

		blueSlider.setMaximum(255);
		blueSlider.setValue(128);
		blueSlider.setMinimum(0);
		blueSlider.addChangeListener(new ChangeListener() {
			public void stateChanged(ChangeEvent arg0) {
				// TODO 自动生成方法存根
				freshColor();
			}
		});
		// slider.setModel(null);
		blueSlider.setBounds(80, 365, 180, 10);
		pnlChat.add(blueSlider);

		redSlider.setMaximum(255);
		redSlider.setValue(128);
		redSlider.setMinimum(0);
		redSlider.addChangeListener(new ChangeListener() {
			public void stateChanged(ChangeEvent arg0) {
				// TODO 自动生成方法存根
				freshColor();
			}
		});
		redSlider.setBounds(80, 380, 180, 10);
		pnlChat.add(redSlider);

		greenSlider.setMaximum(255);
		greenSlider.setValue(128);
		greenSlider.setMinimum(0);
		greenSlider.addChangeListener(new ChangeListener() {
			public void stateChanged(ChangeEvent arg0) {
				// TODO 自动生成方法存根
				freshColor();
			}
		});
		greenSlider.setBounds(80, 395, 180, 10);
		pnlChat.add(greenSlider);

		// -----------聊天字体样式--------------//

		characterLabel.setForeground(new Color(128, 128, 128));
		characterLabel.setHorizontalAlignment(SwingConstants.CENTER);
		characterLabel.setFont(new Font("宋体", Font.BOLD, 18));
		characterLabel.setBackground(Color.ORANGE);
		characterLabel.setText("字体样式");
		characterLabel.setBounds(273, 360, 100, 50);
		pnlChat.add(characterLabel);

		// 启动聊天页面信息刷新线程
		Thread thread = new Thread(this);
		thread.start();

		frmChat.setSize(600, 461);
		frmChat.setVisible(true);
		frmChat.setResizable(false);

		// 将窗口定位在屏幕中央
		scrnsize = toolkit.getScreenSize();
		frmChat.setLocation(scrnsize.width / 2 - frmChat.getWidth() / 2,
				scrnsize.height / 2 - frmChat.getHeight() / 2);
		Image img = toolkit.getImage("resource/images/appico.jpg");
		frmChat.setIconImage(img);

	}

	// 构造方法结束

	protected void freshFont() {
		// TODO 自动生成方法存根
		String fontString = fontComboBox.getSelectedItem().toString();
		String sizeString = sizeComboBox.getSelectedItem().toString();
		String styleString = styleComboBox.getSelectedItem().toString();

		int style = 0;
		int size = Integer.parseInt(sizeString.toString());
		if (styleString.compareTo("常规") == 0) {
			style = Font.PLAIN;
		} else if (styleString.compareTo("粗体") == 0) {
			style = Font.BOLD;
		} else if (styleString.compareTo("斜体") == 0) {
			style = Font.ITALIC;
		} else if (styleString.compareTo("粗斜") == 0) {
			style = Font.BOLD | Font.ITALIC;
		}

		taUserMessage.setFont(new Font(fontString, style, size));
		taUserMessage.setForeground(characterLabel.getForeground());
	}

	protected void freshColor() {
		characterLabel.setForeground(new Color(blueSlider.getValue(), redSlider
				.getValue(), greenSlider.getValue()));
		freshFont();
	}

	@SuppressWarnings("deprecation")
	public void run() {
		int intMessageCounter = 0;
		int intUserTotal = 0;
		boolean isFirstLogin = true; // 判断是否刚登陆
		boolean isFound; // 判断是否找到用户
		Vector user_exit = new Vector();

		try {
			// Socket toServer;
			// toServer = new Socket(strServerIp, 1080);
			for (;;) {
				Socket toServer;
				toServer = new Socket(strServerIp, 1080);
				// 将信息发往服务器
				messobj = new Message();
				ObjectOutputStream streamtoserver = new ObjectOutputStream(
						toServer.getOutputStream());
				streamtoserver.writeObject((Message) messobj);
				// 收来自服务器的信息
				ObjectInputStream streamfromserver = new ObjectInputStream(
						toServer.getInputStream());
				messobj = (Message) streamfromserver.readObject();
				// 刷新聊天信息列表
				if (isFirstLogin) // 如果刚登陆
				{
					intMessageCounter = messobj.chat.size(); // 屏蔽该用户登陆前的聊天内容
					isFirstLogin = false;
				}
				if (strLoginName.equals(messobj.ti)) {
					// taUserMessage.append("踢踢踢");
					exitChatRoom();
					JOptionPane.showMessageDialog(null, strLoginName
							+ "你被管理员剔除!");

				}

				if (!serverMessage.equals(messobj.serverMessage)) {
					serverMessage = messobj.serverMessage;
					taUserMessage.append("[系统消息]：" + serverMessage + "\n");
				}
				// taUserMessage.setText("");
				for (int i = intMessageCounter; i < messobj.chat.size(); i++) {
					Chat temp = (Chat) messobj.chat.elementAt(i);

					String emote = temp.emote;
					if (emote.equals("表情")) {
						emote = "";
					} else {
						emote += "地";
					}
					String temp_message;
					if (temp.chatUser.equals(strLoginName)) {
						if (temp.chatToUser.equals(strLoginName)) {
							temp_message = "系统提示您：请不要自言自语！" + "\n";
						} else {
							if (!temp.whisper) // 不是悄悄话
							{
								temp_message = "【你】对【" + temp.chatToUser + "】"
										+ emote + "说：" + temp.chatMessage
										+ "\n";
							} else if (temp.chatToUser.equals("所有人") ) { // ////////////////////////////////
								temp_message = "系统提示您：请不要对所有人私信！" + "\n";
							} else {
								temp_message = "【你】悄悄对【" + temp.chatToUser
										+ "】" + emote + "说：" + temp.chatMessage
										+ "\n";
							}
						}
					} else {
						if (temp.chatToUser.equals(strLoginName)) {
							if (!temp.whisper) // 不是悄悄话
							{
								temp_message = "【" + temp.chatUser + "】对【你】"
										+ emote + "说：" + temp.chatMessage
										+ "\n";
							} else {
								temp_message = "【" + temp.chatUser + "】悄悄对【你】"
										+ emote + "说：" + temp.chatMessage
										+ "\n";
							}
						} else {
							if (!temp.chatUser.equals(temp.chatToUser)) { // 对方没有自言自语
								if (!temp.whisper) { // 不是悄悄话
									temp_message = "【" + temp.chatUser + "】对【"
											+ temp.chatToUser + "】" + emote
											+ "说：" + temp.chatMessage + "\n";
								} else {
									temp_message = "";
								}
							} else {
								temp_message = "";
							}
						}
					}
					taUserMessage.append(temp_message);
					intMessageCounter++;
				}

				// 刷新在线用户
				lstUserList.clear();
				for (int i = 0; i < messobj.userOnLine.size(); i++) {
					String User = ((Customer) messobj.userOnLine.elementAt(i)).custName;
					lstUserList.addItem(User);
				}
				Integer a = new Integer(messobj.userOnLine.size());
				lblCount.setText(a.toString());
				// 显示用户进入聊天室的信息
				if (messobj.userOnLine.size() > intUserTotal) {
					String tempstr = ((Customer) messobj.userOnLine
							.elementAt(messobj.userOnLine.size() - 1)).custName;
					// String tempstr = messobj.userOnLine.elementAt(
					// messobj.userOnLine.size() - 1).toString();
					if (!tempstr.equals(strLoginName)) {
						taUserMessage.append("【" + tempstr + "】来了" + "\n");
					}
				}
				// 显示用户离开聊天室的信息
				if (messobj.userOnLine.size() < intUserTotal) {
					for (int b = 0; b < user_exit.size(); b++) {
						isFound = false;
						for (int c = 0; c < messobj.userOnLine.size(); c++) {
							String tempstr = ((Customer) user_exit.elementAt(b)).custName;

							if (tempstr.equals(((Customer) messobj.userOnLine
									.elementAt(c)).custName)) {
								isFound = true;
								break;
							}
						}
						if (!isFound) // 没有发现该用户
						{
							String tempstr = ((Customer) user_exit.elementAt(b)).custName;

							if (!tempstr.equals(strLoginName)) {
								taUserMessage.append("【" + tempstr + "】走了"
										+ "\n");
							}
						}
					}
				}
				user_exit = messobj.userOnLine;
				intUserTotal = messobj.userOnLine.size();
				streamtoserver.close();
				streamfromserver.close();
				toServer.close();
				Thread.sleep(3000);
			}

		} catch (Exception e) {
			@SuppressWarnings("unused")
			JOptionPane jop = new JOptionPane();
			JOptionPane.showMessageDialog(null, "不能连接服务器！");
			e.printStackTrace();
			frmChat.dispose();
			// System.out.println();
			// System.out.println(e.getMessage());
		}

	} // run()结束

	private void exitChatRoom() {
		// TODO 自动生成方法存根
		exit();
	}

	// 监听按钮响应
	public void actionPerformed(ActionEvent ae) {
		Object source = (Object) ae.getSource();
		if (source.equals(btnTimer)) {
			new Clock();
		} else if (source.equals(btnCls)) {
			clearMessage();
		} else if (source.equals(btnExit)) {
			exit();
		} else if (source.equals(btnSend)) {
			sendMessage();
		} else if (source.equals(btnSave)) {
			saveMessage();
		} else if (source.equals(lstUserList)) { // 双击列表框更换聊天对象
			changeUser();
		}
	} // actionPerformed()结束

	// 监听窗口关闭响应
	class Windowclose extends WindowAdapter {
		public void windowClosing(WindowEvent e) {
			exit();
		}
	}

	// "清屏"按钮
	public void clearMessage() {
		taUserMessage.setText("");
	}

	// "退出"按钮
	public void exit() {
		Exit exit = new Exit();
		exit.exitName = strLoginName;
		// 发送退出信息
		try {
			Socket toServer = new Socket(strServerIp, 1080);
			// 向服务器发送信息
			ObjectOutputStream outObj = new ObjectOutputStream(
					toServer.getOutputStream());
			outObj.writeObject(exit);
			outObj.close();
			toServer.close();

			frmChat.dispose();
			// this.destroy();
		} catch (Exception e) {
		}

	} // exit()结束

	// "发送"按钮
	public void sendMessage() {
		Chat chatobj = new Chat(strLoginName,
				txtMessage.getText(),
				String.valueOf(cmbUser.getSelectedItem()),
				chPrivateChat.isSelected() ? true : false,
				emote.getSelectedItem().toString());
		// 向服务器发送信息
		try {
			Socket toServer = new Socket(strServerIp, 1080);
			ObjectOutputStream outObj = new ObjectOutputStream(
					toServer.getOutputStream());
			outObj.writeObject(chatobj);
			txtMessage.setText(""); // 清空文本框
			outObj.close();
			toServer.close();
		} catch (Exception e) {
		}
	} // sendMessage()结束

	// "保存"按钮
	public void saveMessage() {
		try {
			FileOutputStream fileoutput = new FileOutputStream(
					this.strLoginName + "_message.txt", true);
			String temp = taUserMessage.getText();
			// System.out.println(temp);
			fileoutput.write(temp.getBytes());
			fileoutput.close();
			JOptionPane.showMessageDialog(null, "聊天记录保存在" + this.strLoginName
					+ "_message.txt");
		} catch (Exception e) {
			System.out.println(e);
		}

	}

	// 将所选用户添加到cmbUser中
	public void changeUser() {
		boolean key = true;
		String selected = lstUserList.getSelectedItem();
		// JOptionPane.showMessageDialog(null, selected);
		for (int i = 0; i < cmbUser.getItemCount(); i++) {
			if (selected.equals(cmbUser.getItemAt(i))) {
				key = false;
				break;
			}
		}
		if (key == true) {
			cmbUser.insertItemAt(selected, 0);
		}
		String head = getUserHead(lstUserList.getSelectedItem());
		// JOptionPane.showMessageDialog(null, head);
		cmbUser.setSelectedItem(selected);

		headLabel.setIcon(new ImageIcon("resource/face//" + head + ".JPG"));
	} // changeUser()结束

	// 刷新头像
	protected void freshHead() {
		// TODO 自动生成方法存根
		String head = getUserHead(cmbUser.getSelectedItem().toString());
		// JOptionPane.showMessageDialog(null, head);
		// cmbUser.setSelectedItem(selected);

		headLabel.setIcon(new ImageIcon("resource/face//" + head + ".JPG"));
	}

	// chenmin
	private String getUserHead(String selectedItem) {
		// TODO 自动生成方法存根
		String head = "oo";
		for (int i = 0; i < messobj.userOnLine.size(); i++) {
			String User = ((Customer) messobj.userOnLine.elementAt(i)).custName;
			if (User.equals(selectedItem)) {
				head = ((Customer) messobj.userOnLine.elementAt(i)).custHead;
				break;
			}
			// System.out.println(User+":"+head);
		}
		return head;
	}

	public static void main(String args[]) {
		new ChatRoom("测试用户", "127.0.0.1"); // test
	}

}