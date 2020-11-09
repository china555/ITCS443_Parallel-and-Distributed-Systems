public class example 
{
	public static void main(String[] args) 
	{     
		int[] x = { 1, 3, 5, 7, 10, 12, 14, 16 };
		int[] y = { 2, 4, 6, 8, 9, 11, 13, 15 };
		int[] xx = new int[x.length];
		int[] xy = new int[x.length];
		int x_sum = 0, y_sum = 0, xx_sum = 0, xy_sum = 0; 
		float  m = 0, b = 0;
		int N = x.length;
		
		for(int i = 0; i < x.length ; i++) //assign value to xx[] , xy[]
		{
			xx[i] = x[i] * x[i];
			xy[i] = x[i] * y[i];
		}
		
		for(int j = 0; j < x.length ; j++) //find sum x, y, xx, xy
		{
			x_sum = x_sum + x[j];
			y_sum = y_sum + y[j];
			xx_sum = xx_sum + xx[j];
			xy_sum = xy_sum + xy[j];
		}
		
		for (int i = 0; i < x.length; i++) //print xx[], xy[] 
	    {
			System.out.println("xx[" + i + "] = " + xx[i]+"      xy[" + i + "] = " + xy[i]);
	    }
		
		System.out.println("number of data point (n) = "+ N);
		System.out.println("x_sum = "+ x_sum +" "+"y_sum = "+ y_sum +" "+"xx_sum = "+ xx_sum +" "+"xy_sum = "+ xy_sum);
		
		float m1 = (x.length * xy_sum) - (x_sum * y_sum); //find m
		float m2 = (x.length * xx_sum) - (x_sum * x_sum);
		System.out.println("m1 = " + m1 +"   "+ "m2 = " + m2);
		
		m = m1 / m2;
		System.out.println("m = " + m);
		System.out.printf("m = " + "%.2f", m);
		
		float b1 = y_sum - (m * x_sum);     //find b
		float b2 = x.length;
		System.out.println("\nb1 = " + b1 +"   "+ "b2 = " + b2);
		
		b = b1 / b2;
		System.out.println("b = " + b);
		System.out.printf("b = " + "%.2f", b);
		
    }
}
