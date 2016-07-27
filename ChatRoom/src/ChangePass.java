import javax.swing.*;

import java.awt.*;
import java.awt.event.*;
import java.net.*;
import java.io.*;

/**
 * Title: QICQ聊天系统登录程序 
 * Description: 根据指定的服务器地址、用户名和密码修改原密码
 * Copyright: Copyright (c) 2015
 * 
 * @author 吴浩男
 * @version 1.0
 */

public class ChangePass extends JFrame implements ActionListener {
	private static final long serialVersionUID = -8965773902046088264L;
	
	private JPanel pnlChange;
	
	private JLabel lblUserName, lblPassword, lblNewPassword, lblConfirmNewPass;
	
	private JLabel lblLogo;
	
	private JButton btnSubmit, btnClear, btnCancel;
	
	private JTextField txtUserName;
	
	private JPasswordField pwdPassword, pwdNewPassword, pwdConfirmNewPass;
	
	private String strServerIp;
	
	// 用于将窗口用于定位
	private Dimension scrnsize;
	private Toolkit toolkit = Toolkit.getDefaultToolkit();

	// 构造方法
	@SuppressWarnings(value={"unchecked", "rawtypes"})
	public ChangePass(String ip) {
		super("[QICQ]聊天室修改密码");
		strServerIp = ip;
		pnlChange = new JPanel();
		this.getContentPane().add(pnlChange);
		
		btnSubmit = new JButton("提交(S)");
		btnSubmit.setToolTipText("提交密码修改，返回登录界面");
		btnSubmit.setMnemonic('S');
		btnClear = new JButton("清空(L)");
		btnClear.setToolTipText("清空修改信息");
		btnClear.setMnemonic('L');
		btnCancel = new JButton("取消(C)");
		btnCancel.setToolTipText("取消修改，返回登录界面");
		btnCancel.setMnemonic('C');
		
		lblUserName = new JLabel("用户名:");
		lblPassword = new JLabel("原密码:");
		lblNewPassword = new JLabel("新密码:");
		lblConfirmNewPass = new JLabel("确认密码:");
		
		txtUserName = new JTextField(30);
		pwdPassword = new JPasswordField(30);
		pwdNewPassword = new JPasswordField(30);
		pwdConfirmNewPass = new JPasswordField(30);
		
		/**
		 * 该布局采用手动布局 
		 * setBounds设置组件位置 
		 * setFont设置字体、字型、字号 
		 * setForeground设置文字的颜色
		 * setBackground设置背景色 
		 * setOpaque将背景设置为透明
		 */
		pnlChange.setLayout(null); // 组件用手动布局
		pnlChange.setBackground(new Color(52, 130, 203));

		lblUserName.setBounds(50, 80, 100, 30);
		txtUserName.setBounds(150, 80, 120, 25);
		lblPassword.setBounds(50, 115, 100, 30);
		pwdPassword.setBounds(150, 115, 120, 25);
		lblNewPassword.setBounds(50, 150, 80, 30);
		pwdNewPassword.setBounds(150, 150, 120, 25);
		lblConfirmNewPass.setBounds(50, 185, 80, 30);
		pwdConfirmNewPass.setBounds(150, 185, 120, 25);
		
		btnSubmit.setBounds(50, 220, 80, 25);
		btnClear.setBounds(130, 220, 80, 25);
		btnCancel.setBounds(210, 220, 80, 25);
		
		Font fontstr = new Font("宋体", Font.PLAIN, 12);
		lblUserName.setFont(fontstr);
		lblPassword.setFont(fontstr);
		lblNewPassword.setFont(fontstr);
		lblConfirmNewPass.setFont(fontstr);
		txtUserName.setFont(fontstr);
		pwdPassword.setFont(fontstr);
		pwdNewPassword.setFont(fontstr);
		pwdConfirmNewPass.setFont(fontstr);
		
		lblUserName.setForeground(Color.BLACK);
		lblPassword.setForeground(Color.BLACK);
		lblNewPassword.setForeground(Color.BLACK);
		lblConfirmNewPass.setForeground(Color.BLACK);
		btnSubmit.setBackground(Color.ORANGE);
		btnClear.setBackground(Color.ORANGE);
		btnCancel.setBackground(Color.ORANGE);
		
		pnlChange.add(btnCancel);
		pnlChange.add(btnClear);
		pnlChange.add(btnSubmit);
		pnlChange.add(lblUserName);
		pnlChange.add(lblPassword);
		pnlChange.add(lblNewPassword);
		pnlChange.add(lblConfirmNewPass);
		pnlChange.add(txtUserName);
		pnlChange.add(pwdPassword);
		pnlChange.add(pwdNewPassword);
		pnlChange.add(pwdConfirmNewPass);
		
		// 设置背景图片
		Icon logo1 = new ImageIcon("resource/images/loginlogo.jpg");
		lblLogo = new JLabel(logo1);
		lblLogo.setBounds(0, 0, 340, 66);
		pnlChange.add(lblLogo);
		// 设置登录窗口
		setResizable(false);
		setSize(340, 300);
		setVisible(true);
		scrnsize = toolkit.getScreenSize();
		setLocation(scrnsize.width / 2 - this.getWidth() / 2, scrnsize.height
				/ 2 - this.getHeight() / 2);
		Image img = toolkit.getImage("resource/images/appico.jpg");
		setIconImage(img);
		
		// 三个按钮注册监听
		btnSubmit.addActionListener(this);
		btnClear.addActionListener(this);
		btnCancel.addActionListener(this);
	}
	
	/**
	 * 按钮监听响应
	 */
	@SuppressWarnings({ "deprecation", "static-access" })
	public void actionPerformed(ActionEvent ae) {
		Object source = ae.getSource();
		if (source.equals(btnSubmit)) {
			// 判断用户名和密码是否为空
			if (txtUserName.getText().equals("") || 
				pwdPassword.getText().equals("") ||
				pwdNewPassword.getText().equals("") ||
				pwdConfirmNewPass.getText().equals("") ) {
				JOptionPane op1 = new JOptionPane();
				op1.showMessageDialog(null, "用户名和密码不能为空");
			} else {
				change();
			}
		} else if (source.equals(btnClear)) {
			txtUserName.setText("");
			pwdPassword.setText("");
			pwdNewPassword.setText("");
			pwdConfirmNewPass.setText("");
		} else if (source.equals(btnCancel)) {
			new Login();
			this.dispose();
		}
	} // actionPerformed()结束

	
	/**
	 * 改密码事件响应方法
	 */
	@SuppressWarnings("deprecation")
	public void change() {
		String newPass = pwdNewPassword.getText();
		String confirmPass = pwdConfirmNewPass.getText();
		if(!newPass.equals(confirmPass)) {
			JOptionPane.showMessageDialog(null, "密码两次输入不一致，请重新输入");
			pwdNewPassword.setText("");
			pwdConfirmNewPass.setText("");
			return;
		}
		// 接受客户的详细资料
		Change_Customer data = new Change_Customer(
				txtUserName.getText(),
				pwdPassword.getText(),
				pwdNewPassword.getText());
		try {
			// 连接到服务器
			Socket toServer;
			toServer = new Socket(strServerIp, 1080);
			ObjectOutputStream streamToServer = new ObjectOutputStream(
					toServer.getOutputStream());
			// 写客户详细资料到服务器socket
			streamToServer.writeObject((Change_Customer) data);
			// 读来自服务器socket的登录状态
			BufferedReader fromServer = new BufferedReader(
					new InputStreamReader(toServer.getInputStream()));
			String status = fromServer.readLine();
			if (status.equals(data.custName+"修改密码成功")) {
				new ChatRoom((String) data.custName, strServerIp);
				this.dispose();
				// 关闭流对象
				streamToServer.close();
				fromServer.close();
				toServer.close();
			} else {
				JOptionPane.showMessageDialog(null, status);
				// 关闭流对象
				streamToServer.close();
				fromServer.close();
				toServer.close();
			}
		} catch (ConnectException e1) {
			JOptionPane.showMessageDialog(null, "未能建立到指定服务器的连接!");
		} catch (InvalidClassException e2) {
			JOptionPane.showMessageDialog(null, "类错误!");
		} catch (NotSerializableException e3) {
			JOptionPane.showMessageDialog(null, "对象未序列化!");
		} catch (IOException e4) {
			JOptionPane.showMessageDialog(null, "不能写入到指定服务器!");
		}
	}
	
	/**
	 * 启动登陆窗体
	 * 
	 * @param args
	 */
	public static void main(String args[]) {
		new ChangePass("127.0.0.1");
	}
}
