import java.util.*;
import java.lang.Math;
import java.io.*; 

public class pathfinder {
	private static HashSet <node> v = new HashSet();
	private static String [][]m;
	private static int r,c,x_iniP,y_iniP,x_finP,y_finP;
	
	public static class node{
		int x=0,y=0,g=0;double diff=0;String h;
		node Next;
		node Previous;
		public node(double diff_e,node t,node u,int x_a,int y_b,String h_c,int g_d)
		{
			diff=diff_e;
			Next= t;
			Previous =u;
			x = x_a;
			y = y_b;
			h = h_c;
			g = g_d;
			
		}
	}

	public static String[][] readMap(String file){
		try {
		BufferedReader bfr = new BufferedReader(new FileReader(file));
		String L;
		
			L = bfr.readLine();
			String[] part = L.split(" ");
			r= Integer.parseInt(part[0]);
			c= Integer.parseInt(part[1]);
			
			
			L = bfr.readLine();
			part = L.split(" ");
			x_iniP = (Integer.parseInt(part[0])-1);
			y_iniP = (Integer.parseInt(part[1])-1);
			
			L = bfr.readLine();
			part = L.split(" ");
			x_finP = (Integer.parseInt(part[0])-1);
			y_finP = (Integer.parseInt(part[1])-1);
			
			String[][] MAP = new String[r][c];
			int r_c=0;
			while(r_c<r)
				{
					L = bfr.readLine();
					part = L.split(" ");
					int c_c=0;
					while(c_c<c)
					{
						MAP[r_c][c_c] = part[c_c];
						c_c++;	
					}
					r_c++;
				}
			bfr.close();
			return MAP;
		} catch (IOException e) {System.out.println(e+"no file found");	}
		return null;
	}
			//checking up
	public static boolean Up(node f)
		{
			boolean ava1;
			int s1= v.size();
			int check_f_up=f.x-1;//check if it can goes up
			ava1 = check_f_up>=0;
			if (ava1==false){return false;
		}
		ava1 = !m[check_f_up][f.y].equals("X");//find obstacle
		if (ava1==false){return false;}
		
		if (s1!=0)
		{
			node next = null;
			Iterator <node> iterate = v.iterator();
			for (;;)
			{
				next = iterate.next();
				if ( next.y == f.y && next.x==check_f_up){return false;}
				s1=s1-1;
				if (s1 == 0){break;}
			}
		}
		return true;
	}
		//checking down
	public static boolean Down(node f)
	{
		boolean ava2;
		int s2= v.size();
		int check_f_down=f.x+1;//check if i can goes down
		ava2 = check_f_down<r;
		if (ava2 == false){return false;}
		ava2 = !m[check_f_down][f.y].equals("X");//find obstacle
		if (ava2 == false){return false;}		
		
		if (s2!=0)
		{
			node next = null;
			Iterator <node> iterate = v.iterator();
			for(;;)
			{
				next = iterate.next();
				if ( next.y == f.y && next.x==check_f_down){return false;}
				s2=s2-1;
				if (s2== 0){break;
				}
			}
		}
		return true;
	}
				   
		//checking left
	public static boolean Left(node f)
	{
		boolean ava3;
		int s3 = v.size();
		int check_f_left=f.y-1;
		ava3= check_f_left>=0;//check if it can go left
		if (ava3 == false){return false;}
		ava3= !m[f.x][check_f_left].equals("X");		
		if (ava3 == false){return false;}
		if (s3!=0)
		{
			node next = null;
			Iterator <node> iterate = v.iterator();
			for (;;)
			{
				next = iterate.next();
				if ( next.y == check_f_left && next.x==f.x)
				{
						return false;
				}
				s3=s3-1;
				if (s3== 0)
				{
					break;
				}
			}
		}
		return true;
	}
	//checking right
	public static boolean Right(node f)
	{
		boolean ava4;
		int s4= v.size();
		int check_f_right=f.y+1;
		ava4 = check_f_right<c;
		if (ava4 == false){return false;}
		ava4 = !m[f.x][check_f_right].equals("X");
		if (ava4 == false){return false;}		
		if (s4!=0)
		{
			node next = null;
			Iterator <node> iterate = v.iterator();
			for (;;)
			{
				next = iterate.next();
				if ( next.y == check_f_right && next.x==f.x )
				{
						return false;
				}
				s4=s4-1;
				if (s4== 0){break;}
			}
		}
		return true;
	}
	
	public static int Cost(node now,int x, int y)
	{
		int h_cost,before,after,cost;
		before=Integer.parseInt(m[x][y]);
		after=Integer.parseInt(m[now.x][now.y]);
		h_cost=before-after;
		if (h_cost <= 0){h_cost = 0;}
		 cost=1+now.g+h_cost;
		 return cost;
		
	}
	
	public static double CostAstar(node now, node goal,String s,int x, int y ){
		double cost_A=0, h = 0;
		int x_diff=goal.x-x;
		int y_diff=goal.y-y;
		if (s.equals("E"))
		{       
			h = Math.sqrt(Math.abs(x_diff)*Math.abs(x_diff) +  Math.abs(y_diff)*Math.abs(y_diff));
		}

		if (s.equals("M"))
		{
			h= Math.abs(x_diff)+Math.abs(y_diff);
		}
		
			cost_A=1+now.g+h;
			return cost_A;
		
	}

	public static void printPath(node pr)
	{
		node next = pr;
		while (next!=null)
		{
			m[next.x][next.y] = "*";
			next = next.Next;
		}
		
		int r_c=0;
		while(r_c<r)
		{
			int c_c=0;
			while(c_c<c)
			{
				System.out.print(m[r_c][c_c]+" ");
				c_c++;

			}
			System.out.println();
			r_c++;
		}
	}

	

	public static void printnode(node f){System.out.println("( "+f.x+","+f.y+" ) -- "+f.h + " -p " +f.diff);}

	public static void BFS(){
		Queue <node> look = new LinkedList<node>();
		int ct = 0;
		node start = new node(0,null,null,x_iniP,y_iniP,m[x_iniP][y_iniP],0);
		node goal  = new node(0,null,null,x_finP,y_finP,m[x_finP][y_finP],0);
		v.add(start);
		node new_node;
		node now = start;
		if (goal.h.equals("X")){System.out.println("empty");
			return;
		}
		
		if ( now!=null ){
			while ( now.x != goal.x || now.y != goal.y)
			{
				
				if (Up(now)){
					new_node = new node(0,now,null,now.x-1,now.y,m[now.x-1][now.y],0);
					look.offer(new_node);
					v.add(new_node);
				}
				if (Down(now)){
					new_node = new node(0,now,null,now.x+1,now.y,m[now.x+1][now.y],0);
					look.offer(new_node);
					v.add(new_node);
				}
				if (Left(now)){
					new_node = new node(0,now,null,now.x,now.y-1,m[now.x][now.y-1],0);
					look.offer(new_node);
					v.add(new_node);
				}
				if (Right(now)){
					new_node = new node(0,now,null,now.x,now.y+1,m[now.x][now.y+1],0);
					look.offer(new_node);
					v.add(new_node);
				}
				now = look.poll();
				ct ++;
			}printPath(now);
			return;
		}
		System.out.println("empty");	
		return;			
	}
	
	public static void  UniS(){
		LinkedList <node> look = new LinkedList<node>();
		int s;
		node start = new node(0,null,null,x_iniP,y_iniP,m[x_iniP][y_iniP],0);
		node goal  = new node(0,null,null,x_finP,y_finP,m[x_finP][y_finP],0);
		v.add(start);
		node new_node;
		node now = start;
		int ct = 0;
		if (goal.h.equals("X")){System.out.println("empty");
			return;
		}
		
		if ( now!=null ){
			while ( now.x != goal.x || now.y != goal.y)
			{
				if (Up(now))
				{
					new_node = new node(0,now,null,now.x-1,now.y,m[now.x-1][now.y],Cost(now,now.x-1,now.y));
					look.add(new_node);
					v.add(new_node);
				}
				if (Down(now))
				{
					new_node = new node(0, now,null,now.x+1,now.y,m[now.x+1][now.y], Cost(now,now.x+1,now.y));
					look.add(new_node);
					v.add(new_node);
				}
				if (Left(now))
				{
					new_node = new node(0, now,null,now.x,now.y-1,m[now.x][now.y-1], Cost(now,now.x,now.y-1));
					look.add(new_node);
					v.add(new_node);
				}
				if (Right(now)){
					new_node = new node(0,now,null,now.x,now.y+1,m[now.x][now.y+1],Cost(now,now.x,now.y+1));
					look.add(new_node);
					v.add(new_node);
				}
				
				s = look.size();
				if (s!=0)
				{
					Iterator <node> iterate = look.iterator();
					node least = iterate.next();
					s--;
					while (s !=0 ){
						node next = iterate.next();
						if ( next.g<least.g ){
							 least = next;
						}
						s --;
					}
					now  = least;
					look.remove(least);
				} else {
				now = null;
				}
				ct ++;
			}
			printPath(now);
			return;
		}
		System.out.println("null");	
		return;
	}
	

	
	public static void Astarsearch(String way){
		int ct = 0;
		int s;
		LinkedList <node> look = new LinkedList<node>();
		node start = null;
		if (way.equals("M")){
			start = new node(Math.abs(x_iniP-x_finP)+Math.abs(y_iniP-y_finP),null,null,x_iniP,y_iniP,m[x_iniP][y_iniP],0);
		}
		if (way.equals("E")){
			start = new node(Math.sqrt(Math.abs(x_iniP-x_finP)*Math.abs(x_iniP-x_finP) +  Math.abs(y_iniP-y_finP)*Math.abs(y_iniP-y_finP)),null,null,x_iniP,y_iniP,m[x_iniP][y_iniP],0);
			
		}
		node goal  = new node(0,null,null,x_finP,y_finP,m[x_finP][y_finP],0);
		v.add(start);
		node new_node;
		node now = start;
		
		if (goal.h.equals("X")){
			System.out.println("null");
			return;
		}
		
		if ( now!=null ){
			while ( now.x != goal.x || now.y != goal.y){
				ct ++;
				if (Up(now)){
					new_node = new node(0,now,null,now.x-1,now.y,m[now.x-1][now.y],Cost(now,now.x-1,now.y));
					new_node.diff = CostAstar(new_node,goal,way,new_node.x,new_node.y);
					look.add(new_node);
					v.add(new_node);
				}
				
				if (Down(now)){
					new_node = new node(CostAstar(now,goal,way,now.x+1,now.y), now,null,now.x+1,now.y,m[now.x+1][now.y], Cost(now,now.x+1,now.y));
					new_node.diff = CostAstar(new_node,goal,way,new_node.x,new_node.y);
					look.add(new_node);
					v.add(new_node);
				}
				if (Left(now)){
					new_node = new node(CostAstar(now,goal,way,now.x,now.y-1), now,null,now.x,now.y-1,m[now.x][now.y-1],Cost(now,now.x,now.y-1));
					new_node.diff = CostAstar(new_node,goal,way,new_node.x,new_node.y);
					look.add(new_node);
					v.add(new_node);
				}
				if (Right(now)){
					new_node = new node(CostAstar(now,goal,way,now.x,now.y+1), now,null,now.x,now.y+1,m[now.x][now.y+1],Cost(now,now.x,now.y+1));
					new_node.diff = CostAstar(new_node,goal,way,new_node.x,new_node.y);
					look.add(new_node);
					v.add(new_node);
				}
				
				s = look.size();
				if (s!=0){
					Iterator <node> iterate = look.iterator();
					node least = iterate.next();
					s--;
					while (s !=0 ){
						node next = iterate.next();
						if ( next.diff<least.diff ){
							 least = next;
						}
						s --;
					}
				now  = least;
				look.remove(least);
				} else {
				now = null;
				System.out.println("null");
				return;
				}
			}
			printPath(now);
			return;
		}
		System.out.println("null");	
		return;
	}
	
	

	public static void main (String [] cal){ 

		m= readMap(cal[0]);
		if (cal[1].equals( "bfs" ))
		{
			BFS();
		}else if ( cal[1].equals("ucs")){
			UniS();
		}
		
		if (cal[1].equals("astar") && cal[2].equals("manhattan")){
			Astarsearch("M");
		}
		else if (cal[1].equals("astar") && cal[2].equals("euclidean")){
			Astarsearch("E");
		}
		return;
	}		
}