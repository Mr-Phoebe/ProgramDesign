package cn.miniword.model;

public class Coordinate extends Pair<Integer, Integer>{
	
	public static final Coordinate ZERO = new Coordinate(0, 0);
	
	public Coordinate(Integer x, Integer y) {
		super(x, y);
	}

	public int getX() {
		return fst;
	}

	public void setX(int x) {
		fst = x;
	}

	public int getY() {
		return snd;
	}

	public void setY(int y) {
		this.snd = y;
	}
	
	
}
