import java.util.*;

public class test{
	
	public static void main(String[] args) {
		String a="0.11e-10";
		System.out.println(Double.parseDouble(a));
	}
 
	
	public int snoredetect(double[] sample){
		LinkedList<Double> window = new LinkedList<>();
		int count = 0, i = 0, len=sample.length;
		boolean startCount = false;
		double sum = 0;
		while(i<4000){
			sum+=Math.abs(sample[i]);
			window.add(Math.abs(sample[i]));
			i++;
		}
		while(i<len){
			sum-= window.removeFirst();
			sum += sample[i];
			window.addLast(sample[i]);
			if(!startCount && sum>1.2){
				count++;
				startCount = true;
			}
			if(startCount && sum<0.4){
				startCount = false;
			}
		}
		return count;
	}

}