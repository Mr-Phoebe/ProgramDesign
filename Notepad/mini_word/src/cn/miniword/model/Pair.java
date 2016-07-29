package cn.miniword.model;

public class Pair<A,B> {
	protected A fst;
	protected B snd;
	
	public Pair(A a, B b) {
		fst = a;
		snd = b;
	}
	
	public boolean equals(Object other) {
		if (!(other instanceof Pair))
			return false;
		
		Pair<?,?> o = (Pair<?,?>) other;
		return (fst.equals(o.fst) && snd.equals(o.snd));
	}
	
	public int hashCode() {
		return fst.hashCode() ^ snd.hashCode();
	}

	public String toString() {
		return "(" + fst + ", " + snd + ")";
	}
}
