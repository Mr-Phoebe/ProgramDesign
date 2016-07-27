import java.io.*;
import java.net.*;
import java.util.*;

/**
 * Title: QICQ聊天系统服务器程序
 * Description: 聊天服务器 
 * Copyright: Copyright (c) 2015
 * 友情链接：http://blog.csdn.net/u013007900
 * 
 * 创建服务器
 * 
 * @author 吴浩男
 * @version 1.0
 * 
 */
public class AppServer extends Thread {
	private ServerSocket serverSocket;

	private ServerFrame sFrame;

	private static Vector userOnline = new Vector(1, 1);

	private static Vector v = new Vector(1, 1);

	/**
	 * 创建服务器 启动服务监听1080端口
	 * 这里借用了sock5的代理地址
	 */
	public AppServer() {
		sFrame = new ServerFrame();
		try {
			serverSocket = new ServerSocket(1080);
			// 获取服务器的主机名和IP地址
			InetAddress address = InetAddress.getLocalHost();
			sFrame.txtServerName.setText(address.getHostName());
			sFrame.txtIP.setText(address.getHostAddress());
			
			sFrame.txtPort.setText("1080");
		} catch (IOException e) {
			fail(e, "不能启动服务！");
		}
		sFrame.txtStatus.setText("已启动...");
		this.start(); // 启动线程
	}

	/**
	 * 退出服务器
	 * 
	 * @param e
	 *            异常
	 * @param str
	 *            退出信息
	 */
	public static void fail(Exception e, String str) {
		System.out.println(str + " 。" + e);
	}

	/**
	 * 监听客户的请求，当有用户请求时创建 Connection线程
	 */
	public void run() {
		try {
			while (true) {
				// 监听并接受客户的请求
				Socket client = serverSocket.accept();
				// 支持多线程
				new Connection(sFrame, client, userOnline, v);
				// System.out.println("userLength:"+userLength);
			}
		} catch (IOException e) {
			fail(e, "不能监听！");
		}
	}

	/**
	 * 启动服务器
	 */
	public static void main(String args[]) {
		new AppServer();
	}
}
