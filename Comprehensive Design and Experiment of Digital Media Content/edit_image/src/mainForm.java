/**
 * Created by SuPhoebe on 2016/10/20.
 */
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
import java.io.*;
public class mainForm extends JFrame implements ActionListener{
	JMenuBar jmb;
	JMenu jm1,jm2,jm3,jm4;
	JMenuItem jmi1,jmi2,jmi4,jmi5,jmi6,jmi7,jmi8,jmi9;
	JDesktopPane jdp;
	JRadioButton jrb1,jrb2,jrb4,jrb5,jrb6,jrb7,jrb8,jrb9;
	public static int TOOL_MOUSE=0;
	public static int TOOL_JMI9=1;
	public static int TOOL_JMI7=2;
	public static int TOOL_JMI5=3;
	public static int TOOL_JMI6=4;
	public static int TOOL_JMI0=5;
	public static int TOOL_ZOOM=6;
	Vector vct;
	JToolBar jtb;
	int current_tool = TOOL_MOUSE;
	public mainForm(){
		pack();
		setExtendedState(MAXIMIZED_BOTH);
		vct=new Vector();
		jdp=new JDesktopPane();
		jmb=new JMenuBar();
		jm1=new JMenu("文件");
		jm2=new JMenu("图形");
		jm3=new JMenu("图像");
		jm4=new JMenu("缩放");
		jmi1=new JMenuItem("打开");
		jmi1.setAccelerator(KeyStroke.getKeyStroke
				(KeyEvent.VK_O,InputEvent.CTRL_MASK));
		jmi1.setMnemonic('o');
		jmi1.addActionListener(this);
		jmi2=new JMenuItem("保存");
		jmi2.setAccelerator(
				KeyStroke.getKeyStroke(
						KeyEvent.VK_S,InputEvent.CTRL_MASK));
		jmi2.setMnemonic('s');
		jmi2.addActionListener(this);

		jmi4=new JMenuItem("退出");
		jmi4.setAccelerator(
				KeyStroke.getKeyStroke(
						KeyEvent.VK_F4,InputEvent.ALT_MASK));
		jmi4.addActionListener(this);
		jmi5=new JMenuItem("锐化");
		jmi5.setAccelerator(
				KeyStroke.getKeyStroke(
						KeyEvent.VK_M,InputEvent.CTRL_MASK));
		jmi5.setMnemonic('m');
		jmi5.addActionListener(this);
		jmi6=new JMenuItem("钝化");
		jmi6.setAccelerator(
				KeyStroke.getKeyStroke(
						KeyEvent.VK_N,InputEvent.CTRL_MASK));
		jmi6.setMnemonic('n');
		jmi6.addActionListener(this);
		jmi7=new JMenuItem("旋转");
		jmi7.setAccelerator(
				KeyStroke.getKeyStroke(
						KeyEvent.VK_X,InputEvent.CTRL_MASK));
		jmi7.setMnemonic('x');
		jmi7.addActionListener(this);
		jmi8=new JMenuItem("缩放");
		jmi8.setAccelerator(
				KeyStroke.getKeyStroke(
						KeyEvent.VK_Q,InputEvent.CTRL_MASK));
		jmi8.setMnemonic('q');
		jmi8.addActionListener(this);
		jmi9=new JMenuItem("放大镜");
		jmi9.setAccelerator(
				KeyStroke.getKeyStroke(
						KeyEvent.VK_W,InputEvent.CTRL_MASK));
		jmi9.setMnemonic('w');
		jmi9.addActionListener(this);
		/*jmi0=new JMenuItem("缩小");
		jmi0.setAccelerator(
				KeyStroke.getKeyStroke(
						KeyEvent.VK_S,InputEvent.CTRL_MASK));
		jmi0.setMnemonic('s');
		jmi0.addActionListener(this);*/

		setJMenuBar(jmb);
		jmb.add(jm1);
		jmb.add(jm2);
		jmb.add(jm3);
		jmb.add(jm4);
		jm1.add(jmi1);
		jm1.add(jmi2);

		jm1.add(jmi4);
		jm2.add(jmi5);
		jm2.add(jmi6);
		jm3.add(jmi7);
		jm3.add(jmi8);
		jm4.add(jmi9);
		//jm4.add(jmi0);
		//getContentPane().add(jdp);

		jrb1=new JRadioButton();
		jrb1.addActionListener(this);
		jrb2=new JRadioButton();
		jrb2.addActionListener(this);

		jrb4=new JRadioButton();
		jrb4.addActionListener(this);
		jrb5=new JRadioButton();
		jrb5.addActionListener(this);
		jrb6=new JRadioButton();
		jrb6.addActionListener(this);
		jrb7=new JRadioButton();
		jrb7.addActionListener(this);
		jrb8=new JRadioButton();
		jrb8.addActionListener(this);
		jrb9=new JRadioButton();
		jrb9.addActionListener(this);
		//jrb0=new JRadioButton();
		//jrb0.addActionListener(this);
		ButtonGroup bg=new ButtonGroup();
		bg.add(jrb1);
		bg.add(jrb2);

		bg.add(jrb4);
		bg.add(jrb5);
		bg.add(jrb6);
		bg.add(jrb7);
		bg.add(jrb8);
		bg.add(jrb9);
		//bg.add(jrb0);
		vct.add(jrb1);
		vct.add(jrb2);

		vct.add(jrb4);
		vct.add(jrb5);
		vct.add(jrb6);
		vct.add(jrb7);
		vct.add(jrb8);
		vct.add(jrb9);
		//vct.add(jrb0);
		jtb=new JToolBar();
		jtb.add(jrb1);
		jtb.add(jrb2);

		jtb.add(jrb4);
		jtb.add(jrb5);
		jtb.add(jrb6);
		jtb.add(jrb7);
		jtb.add(jrb8);
		jtb.add(jrb9);
		//jtb.add(jrb0);
		getContentPane().add(jdp);
		setTitle("图片编辑器");
		setSize(800,600);
		setLocation((int)(Toolkit.getDefaultToolkit()
				.getScreenSize().getSize().getWidth()-800)/2,
				(int)(Toolkit.getDefaultToolkit().getScreenSize()
						.getHeight()-600)/2);
		setVisible(true);
	}

	private static class ImageFileFilter extends javax.swing.filechooser.FileFilter
	{
		public boolean accept(java.io.File file)
		{
			if(file==null)
				return false;
			return file.isDirectory()||
			file.getName().toLowerCase().endsWith(".gif")||
			file.getName().toLowerCase().endsWith(".png")||
			file.getName().toLowerCase().endsWith(".jpg");
		}
		public String getDescription()
		{
			return "Image files(*.gif,*.png,*.jpg)";
		}
	}
	public void actionPerformed(ActionEvent e)
	{

		if(e.getSource()==jmi4){
			System.exit(0);
		}
		else if(e.getSource()==jmi1){
			JFileChooser chooser=new JFileChooser();
			chooser.addChoosableFileFilter(new ImageFileFilter());
			int option=chooser.showOpenDialog(this);
			if(option==JFileChooser.APPROVE_OPTION){
				File file=chooser.getSelectedFile();
				if(file==null)return;
				ImageFrame ifr = new ImageFrame(this, file.getAbsolutePath());
				jdp.add(ifr,JLayeredPane.DEFAULT_LAYER);
				ifr.setVisible(true);
				ifr.setLocation(0,0);
			}
			return;
		}
		else {
			JInternalFrame jif=jdp.getSelectedFrame();
			if((jif==null)||(!(jif instanceof ImageFrame))){
				debug("actionPerformed"
						,"No JInternalFrame is selected, return");
				return;
			}
			ImageFrame ifr=(ImageFrame)jif;
			if(e.getSource()==jmi2){
				ifr.save("");
				return;
			}
			if(e.getSource()==jmi9||e.getSource()==jrb9){
				current_tool=TOOL_JMI9;
			}
			if(e.getSource()==jmi7||e.getSource()==jrb7){
				current_tool=TOOL_JMI7;
			}
			if(e.getSource()==jmi5||e.getSource()==jrb5){
				current_tool=TOOL_JMI5;
			}
			if(e.getSource()==jmi6||e.getSource()==jrb6){
				current_tool=TOOL_JMI6;
			}
			if(e.getSource()==jmi8||e.getSource()==jrb8){
				current_tool=TOOL_ZOOM;
			}
			ifr.operate(current_tool);
		}

	}
	void debug(String m_name,String msg){
		System.out.println("["+m_name+"]  :"+msg);
	}
	/**
     * 当ImageFrame的状态改变时（活动的ImageFram改变时），
     * 修改工具栏上的按钮状态
     */
	void updateToolButtons(int buttonsID){
		if(buttonsID<=vct.size()){
			JRadioButton jrb=(JRadioButton)vct.elementAt(buttonsID);//
			jrb.setSelected(true);
			jrb.updateUI();
		}
	}
	public static void main(String args[])
	{
		new mainForm();
	}

}

