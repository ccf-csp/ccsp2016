import java.util.Scanner;

public class Main{
	static int M = 1000000;
	static Integer n, m, p_rest, empty_x;
	private class Node{
		public Integer x, y;
		
		Node(Integer x, Integer y){
			this.x = x;
			this.y = y;
		}
		
		public Result get(Integer cnt){
			if(y < 0)
				return y - cnt + 1 < -m ? null : new Result(x, y - cnt + 1, y);
			return y + cnt - 1 > m ? null : new Result(x, y, y + cnt - 1);
		}
		
		public void use(Integer cnt){
			if(y < 0)
				y -= cnt;
			else
				y += cnt;
		}
		
		public Boolean empty(){
			return y < -m || y > m;
		}
	};
	private class Result{
		public Integer x, yl, yr;
		Result(Integer x, Integer yl, Integer yr){
			this.x = x;
			this.yl = yl;
			this.yr = yr;
		}
		
		public Long getCost(){
			Long ans = new Long(yr - yl + 1) * abs(x);
			if(yr < 0)
				ans += sum[-yl] - sum[-yr - 1];
			else if(yl > 0)
				ans += sum[yr] - sum[yl - 1];
			else 
				ans += sum[yr] + sum[-yl];
			return ans;			
		}
		
		public Boolean greater(Result a){
			Long cost = getCost();
			Long a_cost = a.getCost();
			/*if(x == -2)
				System.out.println("greater " + a.x + ' ' + cost + ' ' + a_cost);*/
			if(!cost.equals(a_cost))
				return cost > a_cost;
			/*if(x == -2)
				System.out.println("!!");*/
			if(x != a.x)
				return x > a.x;
			return yl > a.yl;
		}
	};
	static private Node rest[];
	static private Long sum[];
	
	static private int abs(Integer x) {
		return x >= 0 ? x : -x;
	}

	Result get(Integer cnt){
		if(cnt > m * 2 + 1)
			return null;
		Result min_res = new Result(empty_x, -cnt / 2, (cnt - 1) / 2);
		if(empty_x < -m)
			min_res = new Result(empty_x - 1, m - cnt + 1, m);
		Integer min_idx = null;
		for(Integer i = 1; i <= p_rest; i++){
			Result res = rest[i].get(cnt);
			if(res != null && min_res.greater(res)){
				min_res = res;
				min_idx = i;
			}
		}
		if(min_idx == null){
			if(empty_x < -m)
				return null;
			if(cnt < 2 * m){
				p_rest += 1;
				rest[p_rest] = new Node(empty_x, (cnt - 1) / 2 + 1);
			}
			if(cnt < 2 * m + 1){
				p_rest += 1;
				rest[p_rest] = new Node(empty_x, -cnt / 2 - 1);
			}
			if(empty_x >= 0)
				empty_x = -empty_x - 1;
			else
				empty_x = -empty_x;
		}else{
			rest[min_idx].use(cnt);
			if(rest[min_idx].empty()){
				rest[min_idx] = rest[p_rest];
				p_rest -= 1;
			}
		}
		/*System.out.print(empty_x);
		for(Integer i = 1; i <= p_rest; i++)
			System.out.print("(" + rest[i].x + ',' + rest[i].y + ')');
		System.out.println();*/
		return min_res;
	}
	
	void solve(Scanner sc){
		n = sc.nextInt();
		m = sc.nextInt();
		empty_x = 0;
		m = m / 2;
		p_rest = 0;
		
		for(Integer i = 0; i < n; i++){
			Integer k = sc.nextInt();
			Result res = get(k);
			if(res != null)
				System.out.println(
						new Integer(res.x + m + 1).toString() + ' ' + 
						new Integer(res.yl + m + 1).toString() + ' ' + 
						new Integer(res.yr + m + 1).toString());
			else
				System.out.println("-1");
		}
	}
	
	static void init(){
		sum[0] = 0L;
		for(Integer i = 1; i <= M; i++)
			sum[i] = sum[i - 1] + i;
	}
	
	public static void main(String args[]){
		rest = new Node[M * 2 + 11];
		sum = new Long[M + 11];
		init();
		Scanner sc = new Scanner(System.in);
		Main main = new Main();
		while(sc.hasNext())
			main.solve(sc);
	}
}