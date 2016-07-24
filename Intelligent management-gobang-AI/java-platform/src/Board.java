import java.io.*;
import java.util.*;
import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.Insets;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import java.awt.Button;

import javax.swing.JLabel;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

import java.awt.GridLayout;

public class Board extends JFrame {
	
	private AI player1 = new AI();
	private AI player2 = new AI();
	private Table chequer = new Table();
	private JPanel contentPane;
	private JPanel panel;
	JLabel labels[] = new JLabel[(15*15)];
	
	private static String wincmd = new String("cmd /C ");

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Board frame = new Board();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public Board() {
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 671, 648);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JLabel player2Label = new JLabel("Executable Path");
		player2Label.setBounds(108, 499, 224, 39);
		contentPane.add(player2Label);
		
		JLabel player1Label = new JLabel("Executable Path");
		player1Label.setBounds(404, 495, 224, 39);
		contentPane.add(player1Label);
		
		panel = new JPanel();
		panel.setBounds(20, 11, 577, 458);
		
		for (int i = 0; i < 15*15; i++)
		{
		    labels[i] = new JLabel(new ImageIcon("resources\\white.png"));
		    panel.add(labels[i]);
		}
		contentPane.add(panel);
		panel.setLayout(new GridLayout(15, 15, 0, 0));
		
		Button button = new Button("Start");
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				play();
			}
		});
		button.setBounds(212, 556, 120, 33);
		contentPane.add(button);
		
		JButton player1Btn = new JButton("");
		player1Btn.setIcon(new ImageIcon("resources\\black-dot-hi.png"));
		player1Btn.setBounds(327, 491, 54, 47);
		player1Btn.setBorderPainted(false);
		player1Btn.setBorder(null);
		//button.setFocusable(false);
		player1Btn.setMargin(new Insets(0, 0, 0, 0));
		player1Btn.setContentAreaFilled(false);
		player1Btn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
		        JFileChooser fileChooser = new JFileChooser();
		        int returnValue = fileChooser.showOpenDialog(null);
		        if (returnValue == JFileChooser.APPROVE_OPTION) {
		          File selectedFile = fileChooser.getSelectedFile();
		          player1.setPath(selectedFile.getPath());
		          player1Label.setText(player1.getPath());
		        }
			}
		});
		contentPane.add(player1Btn);
		
		JButton player2Btn = new JButton("");
		player2Btn.setIcon(new ImageIcon("resources\\white-circle.png"));
		player2Btn.setMargin(new Insets(0, 0, 0, 0));
		player2Btn.setContentAreaFilled(false);
		player2Btn.setBorderPainted(false);
		player2Btn.setBorder(null);
		player2Btn.setBounds(10, 499, 54, 47);
		player2Btn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
		        JFileChooser fileChooser = new JFileChooser();
		        int returnValue = fileChooser.showOpenDialog(null);
		        if (returnValue == JFileChooser.APPROVE_OPTION) {
		          File selectedFile = fileChooser.getSelectedFile();
		          player2.setPath(selectedFile.getPath());
		          player2Label.setText(player2.getPath());
		        }
			}
		});
		contentPane.add(player2Btn);
	}
	
	//Implement what happens after click start - wait for player1 to make a move  then player 2 etc. until one of them wins or board is full
	private void play(){
		//So put a while loop here, if the game is not terminated then call runExe and pass in the cmd, which
		// will contain player1.getPath() and argument, which will be the array representing board state, get the output from AI
		// update the board with the output, then call checkWin() to check wether the game should end. If not then pass control to the next player.
		// and keep looping until board is full or one player won.
		int x, y;
		String str, output;
		while(true){
			
	 
			str = wincmd + player1.getPath() + " ";
			
			output = runExe(str);
			
			String[] pos = output.split(" ");
			if(pos.length != 2) {
				// show error
			}
			x = Integer.parseInt(pos[0]);
			y = Integer.parseInt(pos[1]);
			System.out.println(x + " " + y + " " + 1);
			if(!in(x, y)) {
				// show error
			}
			
			if(checkWin(1)) {
				System.out.println("The winner is black");
				/*
				 * show the page the black is the winner.
				 */
				JOptionPane op1 = new JOptionPane();
				JOptionPane.showMessageDialog(null, "黑棋赢了！");
				return;
			}
			else{
				chequer.updateTable(x, y, 1);
				updateBoard(x, y, 1);           
			}
			str = wincmd + player2.getPath() + " ";
		
			output = runExe(str);
			
			pos = output.split(" ");
			if(pos.length != 2) {
				// show error
			}
			x = Integer.parseInt(pos[0]);
			y = Integer.parseInt(pos[1]);
			System.out.println(x + " " + y + " " + 2);
			if(!in(x, y)) {
				// show error
			}
			if(checkWin(2)) {
				System.out.println("The winner is white");
				/*
				 * show the page the white is the winner.
				 */
				JOptionPane op1 = new JOptionPane();
				JOptionPane.showMessageDialog(null, "白棋赢了！");
				return;
			}
			else{
				chequer.updateTable(x, y, 2);
				updateBoard(x, y, 2);
			}
		}
		
	}
	
	
	//TODO: Need to re-organize this abit. you probably only need one line output. replace "ping localhost" with cmd
	private String runExe(String str)
	{
		try {
			String line;
			String output = "";
			String cmd = chequer.changeCmd(str);
			Process p = Runtime.getRuntime().exec(cmd);
			System.out.println(cmd);
			p.waitFor();
	        BufferedReader input = new BufferedReader
	            (new InputStreamReader(p.getInputStream()));
	        while ((line = input.readLine()) != null) {
	        	//System.out.println(line);
	            output += line + " ";
	        }
	        input.close();
		    return output;
		  } catch (Exception e) {
		    e.printStackTrace();
		  }
		return null;
	}
	
	//TODO: Use whatever the algorithm your AI program uses to make the next move to determine whether there is a winner.
	// input will be the last player move (x, y) and will check all the directions whether there is 5 of the same number
	private boolean checkWin(int w) //technically the coordinate should be a class representing (x, y). but im toooo lazy
	{
		boolean flag = false;
        for(int i = 0; i < 15; i++) { 
            for(int j = 0; j < 15; j++){
            	for(int dirx = -1; dirx <= 1; dirx++)
            		for(int diry = -1; diry <=1; diry++)
            			if(dirx != 0 || diry != 0)
            				flag |= chequer.find(i, j, dirx, diry, w);
            	if(flag)	return true;
            }
        } 
	    return false;       //整个棋盘扫过没有赢 
	}
	
	private boolean in(int x, int y)
	{
		if( x >= 0 && x < 15 && y >= 0 && y < 15)	return true;
		return false;
	}
	
	//TODO: Update board. Set array[x][y] to be symbol. I didnt even create the array -  -   teeheeee
	private void updateBoard(int x, int y, int w)
	{
		if(w==1) {
			labels[x*15+y].setIcon(new ImageIcon("resources\\black-dot-hi.png"));
		}
		else {
			labels[x*15+y].setIcon(new ImageIcon("resources\\white-circle.png"));
		}
		contentPane.paintImmediately(0, 0, contentPane.getWidth(), contentPane.getHeight());
		try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace(); 
        }
	}
}
