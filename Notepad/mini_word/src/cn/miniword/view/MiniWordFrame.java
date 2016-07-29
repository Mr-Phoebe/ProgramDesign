package cn.miniword.view;

import java.awt.Canvas;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Scrollbar;
import java.awt.event.KeyEvent;

import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JScrollPane;
import javax.swing.KeyStroke;

import cn.miniword.biz.actionListener.CanvasKeyListener;
import cn.miniword.biz.actionListener.CanvasMouseListener;
import cn.miniword.biz.actionListener.CopyListener;
import cn.miniword.biz.actionListener.CutListener;
import cn.miniword.biz.actionListener.FindListener;
import cn.miniword.biz.actionListener.NewFileListener;
import cn.miniword.biz.actionListener.OpenFileListener;
import cn.miniword.biz.actionListener.PasteListener;
import cn.miniword.biz.actionListener.QuitListener;
import cn.miniword.biz.actionListener.ReplaceListener;
import cn.miniword.biz.actionListener.SaveAsListener;
import cn.miniword.biz.actionListener.SaveFileListener;
import cn.miniword.biz.actionListener.SelectListener;
import cn.miniword.biz.actionListener.WindowClosingListener;


 public class MiniWordFrame extends JFrame{
	private static final long serialVersionUID = 1L;
	private JMenu menu1;//菜单
    private JMenuItem mt1, mt2, mt3, mt4, mt31; //子菜单
    private Canvas textArea = null;
	private Scrollbar scroll;
	private JMenu menu2;
	public JMenu getMenu1() {
		return menu1;
	}
	public void setMenu1(JMenu menu1) {
		this.menu1 = menu1;
	}

	public JMenu getMenu2() {
		return menu2;
	}

	public void setMenu2(JMenu menu2) {
		this.menu2 = menu2;
	}

	private JMenuItem mt5,mt6,mt7,mt8,mt9,mt10;
	public static final int PREFER_X = 500;
	public static final int PREFER_Y = 500;
	public int size_x = 600;
	public int size_y = 600;
    public MiniWordFrame() {
 //       super("Miniword");
        /**
         * 菜单栏
         */
    	init();
//    	freshen();
    }

    public void freshen() {
		// TODO Auto-generated method stub
  //      menu1.add(mt4);

 //       menu2.setVisible(true);
 //       textArea.setLocation(this.getLocation());
 //   	scroll = new JScrollPane(textArea);
 //       add(scroll);
 //       System.out.println("this.getLocation():"+this.getLocation());
 //       System.out.println("textArea:"+textArea.getLocation());
	}

	private void init() {
    	JMenuBar menuBar = new JMenuBar();
        menu1 = new JMenu("文件",true);
        mt1 = new JMenuItem("新建");
        mt1.addActionListener(new NewFileListener());
        mt2 = new JMenuItem("打开");
        mt2.addActionListener(new OpenFileListener());
        mt3 = new JMenuItem("保存");
        mt3.addActionListener(new SaveFileListener());
        mt31 = new JMenuItem("另存为...");
        mt31.addActionListener(new SaveAsListener());
        mt4 = new JMenuItem("退出");
        mt4.addActionListener(new QuitListener());
        
        this.setJMenuBar(menuBar);
        menuBar.add(menu1);
        menu1.add(mt1);
        menu1.add(mt2);
        menu1.add(mt3);
        menu1.add(mt31);
        menu1.addSeparator();
        menu1.add(mt4);
        mt1.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N, KeyEvent.CTRL_MASK));
        mt2.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, KeyEvent.CTRL_MASK));
        mt3.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, KeyEvent.CTRL_MASK));
        mt4.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_W, KeyEvent.CTRL_MASK));
        menu2 = new JMenu("编辑",true);
        mt5 = new JMenuItem("查找");
        mt5.addActionListener(new FindListener());
        mt6 = new JMenuItem("剪切");
        mt6.addActionListener(new CutListener());
        mt7 = new JMenuItem("复制");
        mt7.addActionListener(new CopyListener());
        mt8 = new JMenuItem("粘贴");
        mt8.addActionListener(new PasteListener());
        mt9 = new JMenuItem("全选");
        mt9.addActionListener(new SelectListener());
/*      mt10 = new JMenuItem("替换");
        mt10.addActionListener(new ReplaceListener());
  */      
        menu2.add(mt6);
        menu2.add(mt7);
        menu2.add(mt8);
        menu2.addSeparator();
        menu2.add(mt5);
//       menu2.add(mt10);
        menu2.addSeparator();
        menu2.add(mt9);
        menuBar.add(menu2);
        mt5.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F, KeyEvent.CTRL_MASK));
        mt6.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_X, KeyEvent.CTRL_MASK));
        mt7.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_C, KeyEvent.CTRL_MASK));
        mt8.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_V, KeyEvent.CTRL_MASK));
        mt9.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_A, KeyEvent.CTRL_MASK));
        //we us canvas to act as textArea.
        Font f = new Font("TimesRoman", Font.PLAIN, 18);
        textArea = new Canvas();
        textArea.setFont(f);
        textArea.addMouseListener(new CanvasMouseListener());
        textArea.addMouseMotionListener(new CanvasMouseListener());
        textArea.addKeyListener(new CanvasKeyListener());
        this.add(textArea);

        textArea.setPreferredSize(new Dimension(0, 0));

//        textArea.setSize(size_x, size_y);
        Dimension screenSize = java.awt.Toolkit.getDefaultToolkit().getScreenSize();
        this.setSize(size_x, size_y);
        
        this.setLocation(screenSize.width/2-this.getWidth()/2,screenSize.height/2-this.getHeight()/2);
        textArea.setLocation(this.getLocation());
        scroll = new Scrollbar();
/*        scroll.setBounds(this.getWidth()-30, 0, 15, this.getHeight());
        add(scroll);
        scroll.setValue(50);
        this.add(textArea);
*/      this.setVisible(true);
        this.addWindowListener(new WindowClosingListener());
        
    }

    public Canvas getTextArea() {
    	return textArea;
    }

}