/**
 * Created by SuPhoebe on 2016/10/20.
 */
import javax.swing.*;
import java.awt.*;
import javax.imageio.*;
import javax.swing.event.*;
import java.awt.image.*;
import java.io.*;
import java.awt.geom.*;
public class ImageFrame extends JInternalFrame implements ChangeListener{
	/**
	 * 缩放图像的比例因子，控制图像放大的的最大倍数
	 * */
	static final int ZOOM_MAX=200;
	mainForm mf;
	 /**
	    * 用于放大或者缩小图像
	    */
	JSlider sliderZoom;
	 /**
	    * 用于放大或者缩小图像的对话框，sliderZoom
	    */
	JDialog jdZoom;
	/**
	    * 保存原始的图像
	    */
	BufferedImage bfi;
	JAdvLabel jal;
	JScrollPane jsp;
	int current_tool=mainForm.TOOL_MOUSE;
	public ImageFrame(mainForm mf,String imagename){
		this.mf=mf;
		initComponents();
		setTitle(imagename);
		jal.filename=imagename;
		jal.setImageIcon(new ImageIcon(imagename));
		setSize(400,300);
		bfi=jal.abuffered_image;
	}
	/**
     * 初始化窗口中的组件
     */
	public void initComponents(){
		jsp=new JScrollPane();
		jal=new JAdvLabel();
		setClosable(true);//设置是否可以通过某个用户操作关闭此 JInternalFrame。
		setIconifiable(true);//设置 iconable 属性，对于能够使 JInternalFrame 变成一个图标的用户而言，该属性必须为 true。某些外观可能不实现图标化；它们将忽略此属性。
		setResizable(true);//设置此窗体是否可由用户调整大小。
		 jsp.setViewportView(jal);
		jal.setOpaque(true);
		jal.setVerticalAlignment(SwingConstants.TOP);

		getContentPane().add(jsp,BorderLayout.CENTER);
	}
	 /**
	   * 执行相应的图像操作
	   */
	public void operate(int op){
		current_tool=op;
		jal.showf(current_tool==mainForm.TOOL_JMI9);
		if(current_tool==mainForm.TOOL_JMI7){//旋转
			rotate(270);
		}
		else if(current_tool==mainForm.TOOL_JMI5){//锐化
			opJmi(true);
		}
		else if(current_tool==mainForm.TOOL_JMI6){//钝化
			opJmi(false);
		}
		else if(current_tool==mainForm.TOOL_ZOOM){
			if(jdZoom==null){
				jdZoom=new JDialog(mf);
				jdZoom.setBounds(getWidth()/2,getHeight()/2,200,100);
				/**JSlider(int orientation, int min, int max, int value)
          用指定的方向和指定的最小值、最大值以及初始值创建一个滑块。
          */
				sliderZoom=new JSlider(JSlider.HORIZONTAL,0,1000,ZOOM_MAX);
				sliderZoom.addChangeListener(this);
				jdZoom.getContentPane().add(sliderZoom);
			}
			jdZoom.show();
			bfi=jal.buffered_image;
		}
	}
	  /**
	   * 当JInternalFrame改变时，该函数将被调用，
	   * 下面的事件可能被执行:
	   *    InternalFrameEvent.INTERNAL_FRAME_OPENED
	   *    InternalFrameEvent.INTERNAL_FRAME_CLOSING
	   *    InternalFrameEvent.INTERNAL_FRAME_CLOSED
	   *    InternalFrameEvent.INTERNAL_FRAME_ICONIFIED
	   *    InternalFrameEvent.INTERNAL_FRAME_DEICONIFIED
	   *    InternalFrameEvent.INTERNAL_FRAME_ACTIVATED
	   *    InternalFrameEvent.INTERNAL_FRAME_DEACTIVATED
	   */
	protected void fireInternalFrameEvent(int id){
		if(id==InternalFrameEvent.INTERNAL_FRAME_ACTIVATED){
			mf.debug(
					"ImageFrame.fireInternalFrameEvent"
					,getTitle()+"Frame is actived");
			mf.updateToolButtons(current_tool);
		}if(id==InternalFrameEvent.INTERNAL_FRAME_CLOSED){
			sliderZoom=null;
			jdZoom=null;
		}
	}
	 public void stateChanged(ChangeEvent e) {
	        if (e.getSource().equals(sliderZoom)) {
	        	 zoom(sliderZoom.getValue());
	        }
	    }
	 void zoom(double factor) {
         //获取原图像大小
         int w = bfi.getWidth();
         int h = bfi.getHeight();

         //计算缩放后的大小
         int newX = (int)(factor==0?1:(w*factor/ZOOM_MAX));
         int newY = (int)(factor==0?1:(h*factor/ZOOM_MAX));

         BufferedImage biDst =  new BufferedImage(
                        newX,newY, BufferedImage.TYPE_4BYTE_ABGR);

         //创建Graphics2D对象，缩放图像将绘制在其上
         Graphics2D g2d = biDst.createGraphics();

         g2d.setRenderingHint(
                RenderingHints.KEY_INTERPOLATION,
                RenderingHints.VALUE_INTERPOLATION_BILINEAR);
         g2d.drawImage(bfi, 0, 0, newX, newY, null);

         jal.setImageIcon(new ImageIcon(biDst));
         mf.debug("ImageFrame.zoom", "图像缩放完毕");
     }
	/**
     * 对图像进行旋转操作
     * 这里只选择0, 90. 180, 270度
     */
	public void rotate(int d){
		int a=d%360;
		int w=jal.image_icon.getIconWidth();
		int h=jal.image_icon.getIconHeight();
		AffineTransform at=AffineTransform.getRotateInstance(Math.toRadians(a),w/2,h/2);
		AffineTransformOp ato=new AffineTransformOp(
				at,AffineTransformOp.TYPE_BILINEAR);
		if(a!=180){
			int temp=w;
			w=h;
			h=temp;
		}
		BufferedImage bfi=new BufferedImage(
				w,h,BufferedImage.TYPE_INT_ARGB);
		ato.filter(jal.abuffered_image, bfi);
		jal.setImageIcon(new ImageIcon(bfi));
		mf.debug("ImageFrame.rotae","图像旋转完毕");
	}
	/**
     * 对图像进行锐化或者钝化处理
     */
	void opJmi(boolean sp){
		int w=jal.image_icon.getIconWidth();
		int h=jal.image_icon.getIconHeight();
		BufferedImage bf=new BufferedImage(
				w,h,BufferedImage.TYPE_INT_RGB);
		BufferedImage bfo=jal.buffered_image;
		float sharpData[] = {-1.0f, -1.0f, -1.0f,
                -1.0f, 9.0f, -1.0f,
                -1.0f, -1.0f, -1.0f};
		float blurData[] = { 0.1f, 0.1f, 0.1f,
                0.1f, 0.2f, 0.1f,
                0.1f, 0.1f, 0.1f};
		ConvolveOp op;
		if(sp){
			op=new ConvolveOp(new Kernel(3,3,sharpData));//构造给定了 Kernel 的 ConvolveOp。
		}else{
			op=new ConvolveOp(new Kernel(3,3,blurData));
		}
		//进行图像变化
		op.filter(bf, bfo);
		jal.setImageIcon(new ImageIcon(bf));
		mf.debug("ImageFrame.opJmi", "锐化/钝化化处理完成");
	}
	public void save(String filename){
		if (filename=="") {
            //保存到当前的文件中
            saveAs(jal.filename);
        } else {
            saveAs(filename);
        }
	}
	public void saveAs(String filename){
		String format;
		BufferedImage bi=null;
		if(filename.endsWith(".gif")){
			format="gif";
		}
		else if(filename.endsWith(".jpg")){
			format="jpg";
		}
		else if(filename.endsWith(".png")){
			format="png";
		}
		else {
            mf.debug("ImageFrame.saveAs","不支持的图像格式");
            return;
        }
		try{
			ImageIO.write(bi=jal.buffered_image, "jpg", new File(filename));
			ImageIO.write(bi=jal.buffered_image, "gif", new File(filename));
			ImageIO.write(bi=jal.buffered_image, "png", new File(filename));
		}
		catch(Exception e){
			mf.debug("ImageFrame.saveAs", "保存文件时出现异常：" + filename);
            return;
		}
		jal.filename=filename;
		mf.debug("ImageFrame.saveAs", "图像保存到：" + filename);
	}
}
