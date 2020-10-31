#include <iostream> 
#include <vector> 
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <cstdio>

#include <cassert>
void time();
using namespace std;

class Customer{
	public:
	string Id;//set id 
	int arrival_time;//set arrival time
	int priority;//set priority of each customer
	int age;//set the aging 
	int total_tickets;//set the needed tickets,each time it may change
	int endingTime;//set ending time
	int readyTime;//set ready time
	int waitingTime;//set waiting time
	int runningTime;//set running time
	bool executed;//set whether it has been excuted 
	bool age_status;

	public:
	Customer(string Id,int arrival_time,int priority,int age,int total_tickets){
		this-> Id = Id;
		this->arrival_time = arrival_time;
		this->priority = priority;
		this->age = age;	
		this->total_tickets = total_tickets;
		endingTime= 0;
		readyTime= 0;
		waitingTime = 0;
		runningTime = 0;
		executed = false;;

		age_status = false;
	}
	string get_Id()
	{
		return Id;
	}
	int get_arrival_time()
	{
		return arrival_time;
	}

	int get_priority()
	{
		return priority;
	}
	int get_age()
	{
		return age;
	}
	void set_age(int age)
	{
		this->age = age;
	}
	void set_total_tickets(int total_tickets)
	{
		this->total_tickets = total_tickets;
	}
	int get_total_tickets()
	{
		return total_tickets;
	}
	int get_endingTime()
	{
		return endingTime;
	}
	int get_readyTime()
	{
		return readyTime;
	}
	int get_waitingTime()
	{
		return waitingTime;
	}
	int get_runningTime()
	{
		return runningTime;
	}
	bool get_executed()
	{
		return executed;
	}
	void set_priority(int priority)
	{
		this->priority = priority;
	}
	void set_endingTime(int endingTime)
	{
		this->endingTime = endingTime;
	}
	void set_readyTime(int readyTime)
	{
		this->readyTime = readyTime;
	}
	void set_waitingTime(int waitingTime)
	{
		this->waitingTime = waitingTime;
	}
	void set_runningTime(int runningTime)
	{
		this->runningTime = runningTime;
	}
	void set_executed(bool executed)
	{
		this->executed = executed;
	}
	void set_age_status(bool age_status)
	{
		this->age_status = age_status;
	}
	bool get_age_status()
	{
		return age_status;
	}
};
//shifting the string to int
int shift(string s) 
{ 
  
    // object from the class stringstream 
    stringstream geek(s); 
    int x = 0; 
    geek >> x; 
 
    return x; 
}
//shifting int to string 
std::string to_string( int x ) {
  int length = snprintf( NULL, 0, "%d", x );
  assert( length >= 0 );
  char* buf = new char[length + 1];
  snprintf( buf, length + 1, "%d", x );
  std::string str( buf );
  delete[] buf;
  return str;
}
vector<string> tmp;
vector<string> tmp1;
std::vector<Customer> c;
vector<Customer> Customer_tmp;
int Time;//the most importent variable to control the whole process
bool is_queue1;//whether the queue is empty
bool is_queue2;//whether the queue is empty
bool is_queue1_last;
vector<Customer> queue1;
vector<Customer> queue2;
vector<Customer> queue3;//the output queue
vector<string> result;
void display(){
	if (!is_queue1&&!is_queue2)
	{
		
	}else{
		cout<<"Time:"<<Time<<endl;
		cout<<"name"<<" "<<"arrival_time"<<" "<<"tickets_required"<<" "<<"running"<<" "<<"priority_number"<<" "<<"age/runs"<<endl;
		cout<<"queue1";
		cout<<endl;
		if (is_queue1)
		{
			
			for (int i = 0; i < queue1.size(); ++i)
			{
				cout<<queue1[i].get_Id()<<"           "<<queue1[i].get_arrival_time()<<"           "<<queue1[i].get_total_tickets()<<"           "<<queue1[i].get_runningTime()<<"           "<<queue1[i].get_priority()<<"           "<<queue1[i].get_age()<<endl;
			}
		}
		cout<<"queue2";
		cout<<endl;
		if (is_queue2)
		{
		
			for (int i = 0; i < queue2.size(); ++i)
			{
				cout<<queue2[i].get_Id()<<"           "<<queue2[i].get_arrival_time()<<"           "<<queue2[i].get_total_tickets()<<"           "<<queue2[i].get_runningTime()<<"           "<<queue2[i].get_priority()<<"           "<<queue2[i].get_age()<<endl;
			}
		}
	}
}
void final_display(){
	cout<<"name"<<"   "<<"arrival"<<"   "<<"end"<<"   "<<"ready"<<"   "<<"running"<<"   "<<"waiting"<<endl;
	for (int i = 0; i < queue3.size(); ++i)
	{

		string s ="";
			
		string a = queue3[i].get_Id();
	
		string b = to_string(queue3[i].get_arrival_time());
		
	// 	// result[1] = static_cast<ostringstream*>( &(ostringstream() << queue3[i].get_arrival_time()) )->str();
		
	
		string c = to_string(queue3[i].get_endingTime());
		string d= to_string(queue3[i].get_readyTime());
		string e = to_string(queue3[i].get_runningTime());
		string f = to_string(queue3[i].get_waitingTime());
		        
			s=s+a;
			for (int i = 0; i < 12-a.size()-b.size(); ++i)
			{
				s+=" ";
			}
			s+=b;
			for (int i = 0; i < 10-c.size(); ++i)
			{
				s+=" ";
			}
			s+=c;
			for (int i = 0; i < 10-d.size(); ++i)
			{
				s+=" ";
			}
			s+=d;
			for (int i = 0; i < 10-e.size(); ++i)
			{
				s+=" ";
			}
			s+=e;
			for (int i = 0; i < 10-f.size(); ++i)
			{
				s+=" ";
			}
			s+=f;
			cout<<s<<endl;
		
		// for (int i = 0; i < cou4nt; ++i)
		// {
		// 	/* code */
		// }
		
		
			
			// <<"       "<<queue3[i].get_arrival_time()<<"       "<<queue3[i].get_endingTime()<<"       "<<queue3[i].get_readyTime()<<"       "<<queue3[i].get_runningTime()<<"       "<<queue3[i].get_waitingTime()<<endl;
	}
	
}
//sort the waiting list 
void  sort(std::vector<string> v,int l){
	
	int q = 1;
	int m = 0;
	//cout<<q<<endl;
	while(m<v.size()){
		c.push_back(Customer(v[m], shift(v[m+1]), shift(v[m+2]), shift(v[m+3]), shift(v[m+4])));
		// cout<<c[0].get_age()<<endl;;
		m+=5;
	}
	//cout<<c.size()<<endl;
	while(q<v.size()){
		tmp.push_back(v[q]);
		q+=5;

		// cout<<tmp.size()<<endl;
	}
	// for (int i = 0; i < tmp.size(); i++)
	// {
	// 	cout<<tmp[i]<<" ";
	// }

	for (int i = 0; i < tmp.size(); ++i)
	{
		for (int j = i+1; j < tmp.size(); ++j)
		{
			if (c[i].get_arrival_time()>c[j].get_arrival_time())
			{
				swap(c[i],c[j]);
			}
		}
	}
}
//get the initial time
void first_time(){

	Time = c[0].get_arrival_time();

}
//sort the priority for queue1
void sort_priority(vector<Customer> &q){
	
	if (is_queue1)
	{
		int i, key, j;  
		 
	    for (i = 1; i < q.size(); i++) 
	    {  
	        key = q[i].get_priority();  
	        j = i - 1;  
	  		Customer tmp  = q[i];
	        while (j >= 0 && q[j].get_priority() > key) 
	        {  
	            q[j + 1] = q[j];  
	            j = j - 1;  
	        }  
	        q[j + 1] = tmp;  
	    }  
	}
}
//select the queue for the customer followint the priority
void select(Customer c){
	if (c.get_priority()<=3)
	{
		queue1.push_back(c);
		
		is_queue1 = true;
		is_queue1_last = true;
		// cout<<queue1.size()<<endl;
	}else{
		queue2.push_back(c);
	
		is_queue2 =true;
		// cout<<queue2.size()<<endl;
	}
}
//get the ready time for queue
void changeTimeQueue1(vector<Customer> &queue1, vector<Customer> &queue2){
	if (queue1.size()>0)
	{
		for (int i = 0; i <queue1.size() ; ++i)
		{
			if (queue1[i].get_runningTime()==0)
			{
				queue1[i].set_readyTime(Time);
		
			}
		}
	}
	// if (queue2.size()>0)
	// {
	// 	for (int i = 0; i <queue2.size() ; ++i)
	// 	{
	// 		if (queue2[i].get_executed()&&queue2[i].get_runningTime()>0)
	// 		{
	// 			queue2[i].set_waitingTime(queue2[i].get_waitingTime()+p);
	// 		}else{
	// 			queue2[i].set_readyTime(Time);
	// 		}
	// 	}
	// }
	if (queue2.size()>0)
	{
		for (int i = 0; i <queue2.size() ; ++i)
		{
			if (queue2[i].get_runningTime()==0)
			{
				queue2[i].set_readyTime(Time);
		
			}
		}
	}
}
//useless function
void changeTimeQueue2(vector<Customer> &queue2,int p){
	if (queue2.size()>0)
	{
		for (int i = 0; i <queue2.size() ; ++i)
		{
			if (queue2[i].get_runningTime()==0)
			{
				queue2[i].set_readyTime(Time);
		
			}
		}
	}
}
// plus age for two queues after running one time
void plus_age(vector<Customer> &queue2){
	for (int i = 0; i < queue2.size(); ++i)
	{
		if (!queue2[i].get_age_status())
		{
			queue2[i].set_age(queue2[i].get_age()+1);
		}
		else{
			queue2[i].set_age(0);
		}
	}
	for (int i = 0; i < queue2.size(); ++i)
	{
		queue2[i].set_age_status(false);
	}
}

//check the age and priority to move the customer to queue1 and queue2
void check_age(vector<Customer> &queue2){
	for (int i = 0; i < queue2.size(); ++i)
	{
		if (queue2[i].get_age()==8)
		{
			queue2[i].set_age(0);
			queue2[i].set_priority(queue2[i].get_priority()-1);
		}
		if (queue2[i].get_priority()<=3)
		{
			queue1.push_back(queue2[i]);
			is_queue1 = true;
			queue2.erase(queue2.begin()+i);
			i--;
		}
	}
}
bool tr = true;
//calculate the wait time for each customer
void wait_time(vector<Customer> &q){

	if (q.size()>0)
	{
		for (int i = 0; i<q.size(); i++)
		{
			q[i].set_waitingTime(q[i].get_endingTime()-q[i].get_readyTime()-q[i].get_runningTime());
		}
	}

}
//all the processes in this function to calculate time
void queue(){
	int bol = 0;
	//if queue1 is not empty
	if (is_queue1)
	{

		sort_priority(queue1);
		int n = (8-queue1[0].get_priority())*2;
		if (n<queue1[0].get_total_tickets())
		{

			changeTimeQueue1(queue1, queue2);
			queue1[0].set_total_tickets(queue1[0].get_total_tickets()-n); 
			Time +=n*5;
			//changeTimeQueue1(queue1, queue2);
			queue1[0].set_runningTime(queue1[0].get_runningTime()+(n*5));
			queue1[0].set_age(queue1[0].get_age()+1);
			
			queue1[0].set_executed(true);
			queue1[0].set_endingTime(Time);
			
			if (queue1[0].get_age()>=3)
			{	

				queue1[0].set_priority(queue1[0].get_priority()+1);
				queue1[0].set_age(0);
			}
			bol = 1;
			
		}else{

			changeTimeQueue1(queue1, queue2);
			Time += queue1[0].get_total_tickets()*5;
			queue1[0].set_runningTime(queue1[0].get_runningTime()+queue1[0].get_total_tickets()*5);
			queue1[0].set_total_tickets(0) ;
			
			queue1[0].set_endingTime(Time);
			if (queue1.size()==1)
			{

				queue3.push_back(queue1[0]);
				queue1.erase(queue1.begin(),queue1.begin()+1);
				is_queue1 = false;
				bol = 0;

				//changeTimeQueue1(queue1, queue2);
				//queue2[0].set_executed(true);
				plus_age(queue2);
				// cout<<11111111111<<endl;
				check_age(queue2);
			}else{

				queue3.push_back(queue1[0]);
				queue1.erase(queue1.begin(),queue1.begin()+1);
				// queue1[0].set_executed(true);
			 	//changeTimeQueue1(queue1, queue2);
			 	// queue2[0].set_executed(true);
			 	plus_age(queue2);
				check_age(queue2);
			 	time();
			 	
			 	bol = 0;
			}
			
			
		}
		if (is_queue1&&bol == 1)
		{
			plus_age(queue2);
			check_age(queue2);
			time();
			queue1.push_back(queue1[0]);
			queue1.erase(queue1.begin(),queue1.begin()+1);
			
		}
		//decrease_age(queue1);

		// if (queue1.size()>0)
		// 
		for (int i = 0; i < queue1.size(); ++i)
		{
			if (queue1[i].get_priority()>3)
			{
				queue2.insert(queue2.begin()+queue2.size(), queue1[i]);
				queue1.erase(queue1.begin()+i);
				i--;
				is_queue2=true;
				if (queue1.size()==0)
				{
					is_queue1=false;
					
				}
			}
			
		}
			
		sort_priority(queue1);
		//if queue1 is empty and queue2 is not empty
	}else if (is_queue2&&!is_queue1){

		int qq = 0;
		int q = 0;
		if (queue2[0].get_total_tickets()>20)
		{
			qq = 20;
		}else{
			qq = queue2[0].get_total_tickets();
		}
		for (int i = 0; i < c.size(); ++i)
		{
			if (c[i].get_priority()<=3)
			{
				q = i;
				break;
			}
		}
		//when running queue2 and queue1 is not empty
		if (c.size()>0&&c[q].get_priority()<=3&&((c[q].get_arrival_time()- Time)/5<=qq)){
			//judge sequence reversed
			
			queue2[0].set_total_tickets(queue2[0].get_total_tickets()-(c[q].get_arrival_time()- Time)/5); 
			
			changeTimeQueue1(queue1,queue2);
			queue2[0].set_runningTime(queue2[0].get_runningTime()+c[q].get_arrival_time()- Time);
			Time += c[q].get_arrival_time()- Time;

			queue2[0].set_endingTime(Time);
			
			queue2[0].set_executed(true);
			//=*queue2[0];
			queue2[0].set_age_status(true);
			
			plus_age(queue2);
			check_age(queue2);
			
			time();
			queue2.push_back(queue2[0]);
		
			queue2.erase(queue2.begin(),queue2.begin()+1);
		}else if(c.size()>0&&c[0].get_priority()>3&&((c[0].get_arrival_time()- Time)/5<qq)){	

			if (queue2[0].get_total_tickets()>20)
			{
				changeTimeQueue1(queue1,queue2);
				queue2[0].set_total_tickets(queue2[0].get_total_tickets()-20); 
				Time +=100;
				queue2[0].set_runningTime(queue2[0].get_runningTime()+100);
				//queue2[0].set_age(queue2[0].get_age()+1);
				queue2[0].set_endingTime(Time);
				
				// if (queue2[0].get_age()>=8)
				// {
				// 	queue2[0].set_age(0);
				// 	queue2[0].set_priority(queue2[0].get_priority()-1);
				// }
				queue2[0].set_executed(true);
			
				queue2[0].set_age_status(true);
				plus_age(queue2);
				check_age(queue2);
				time();
			
				queue2.push_back(queue2[0]);
				queue2.erase(queue2.begin(),queue2.begin()+1);
			

			}else{

				changeTimeQueue1(queue1,queue2);
				Time += queue2[0].get_total_tickets()*5;
				queue2[0].set_runningTime(queue2[0].get_runningTime()+queue2[0].get_total_tickets()*5);
				queue2[0].set_total_tickets(0) ;
				queue2[0].set_endingTime(Time);
				queue2[0].set_executed(true);
				if (queue2.size()==1)
				{

					queue3.push_back(queue2[0]);
					queue2.erase(queue2.begin(),queue2.begin()+1);
					is_queue2 = false;
					
				}else{
					
					queue2[0].set_age_status(true);
					// queue1[0].set_executed(true);
				 	// changeTimeQueue1(queue1,queue2);
				 	plus_age(queue2);
					check_age(queue2);
				 	time();
				 	queue3.push_back(queue2[0]);
				 	queue2.erase(queue2.begin(),queue2.begin()+1);
				}
				
			}
			//}
		}else{
			
			if (queue2[0].get_total_tickets()>20)
			{
				changeTimeQueue1(queue1,queue2);
				queue2[0].set_total_tickets(queue2[0].get_total_tickets()-20); 
				Time +=100;
				queue2[0].set_runningTime(queue2[0].get_runningTime()+100);
				//queue2[0].set_age(queue2[0].get_age()+1);
				queue2[0].set_endingTime(Time);
				

				queue2[0].set_executed(true);
		
				queue2[0].set_age_status(true);

				queue2.push_back(queue2[0]);
				queue2.erase(queue2.begin(),queue2.begin()+1);

			}else{
				changeTimeQueue1(queue1, queue2);
				Time += queue2[0].get_total_tickets()*5;
				
				queue2[0].set_runningTime(queue2[0].get_runningTime()+queue2[0].get_total_tickets()*5);
				queue2[0].set_executed(true);
				queue2[0].set_endingTime(Time);
				queue2[0].set_total_tickets(0) ;
				queue2[0].set_age_status(true);
				if (queue2.size()==1)
				{
					
					
					queue3.push_back(queue2[0]);
					queue2.erase(queue2.begin(),queue2.begin()+1);
					is_queue2 = false;
					
				}else{

					queue3.push_back(queue2[0]);
					queue2.erase(queue2.begin(),queue2.begin()+1);
					// queue1[0].set_executed(true);
				 	// changeTimeQueue1(queue1, queue2);
				 	
				}
			}
			plus_age(queue2);
			check_age(queue2);
		}
		
		// plus_age(queue2);
		// check_age(queue2);
		sort_priority(queue1);
	}
}
//display the status for the first time  
void first_display(){
	if (tr)
	{
		cout<<"Time:"<<Time<<endl;
		cout<<"name"<<" "<<"arrival_time"<<" "<<"tickets_required"<<" "<<"running"<<" "<<"priority_number"<<" "<<"age/runs"<<endl;
		cout<<"queue1";
		cout<<endl;
		if (is_queue1)
		{
			
			for (int i = 0; i < queue1.size(); ++i)
			{
				cout<<queue1[i].get_Id()<<"           "<<queue1[i].get_arrival_time()<<"           "<<queue1[i].get_total_tickets()<<"           "<<queue1[i].get_runningTime()<<"           "<<queue1[i].get_priority()<<"           "<<queue1[i].get_age()<<endl;
			}
		}
		cout<<"queue2";
		cout<<endl;
		if (is_queue2)
		{
		
			for (int i = 0; i < queue2.size(); ++i)
			{
				cout<<queue2[i].get_Id()<<"           "<<queue2[i].get_arrival_time()<<"           "<<queue2[i].get_total_tickets()<<"           "<<queue2[i].get_runningTime()<<"           "<<queue2[i].get_priority()<<"           "<<queue2[i].get_age()<<endl;
			}
		}
	}
	tr = false;
}
//pick customer in waiting list to queue
void time(){

	if (c.size()>0)
	{
		if (queue1.size()<=0&&queue2.size()<=0&&c[0].get_arrival_time()>Time)
		{
			
			Time = c[0].get_arrival_time();
			
		}	
					// cout<<Time<<endl;
		for (int i = 0; i<c.size(); )
		{

			if (c[i].get_arrival_time()<=Time)
			{
				select(c[i]);
				c.erase(c.begin(),c.begin()+1);
				//display();
			}else{
				break;
			}
		}
	}
	//first_display();	
}

int main(int argc, char const *argv[])
{
	vector<string> vec;
	string s="";
	int l = 0;
	vector <string> processes;
	std::ifstream file("input.txt");
	if (file.is_open()) {
	    string line;
	    while (getline(file, line)) {
	    	// if (/* condition */)
	    	// {
	    	// 	 code 
	    	// }
	    	// line.erase(line.size()-1);
	        // vec.push_back(line);
	        //vec.push_back('\n');
	        s+=line;
	        s+='\n';
	        
	    }
	    file.close();
	}
	s.erase(s.size()-1);
	string tmp = "";
	// for (int i = 0; i < s.size(); i++)
	// {
	int i = 0;
	while(i<s.size()){	
		if (s.at(i)!=' ')
		{
			tmp+=s.at(i);
		}else{
			vec.push_back(tmp);
			tmp.clear();
		}
		// cout<<s.at(i)<<endl;
		i++;
		// cout<<i<<endl;
		if (i>=s.size())
		{

			vec.push_back(tmp);	
			break;
		}
		if (s.at(i)=='\n')
		{
			vec.push_back(tmp);	
			tmp.clear();
			i++;
			l+=1;
		}
	}
	// 	    s.at(i)!='\n'&&
	// 
	// }

	// for (int i = vec.size()-1; i >=0 ; i--)
	// {
	// 	if (vec[i].empty())
	// 	{
	// 		vec.pop_back();
	// 	}
	// }

	// for (int i = 0; i < vec.size(); i++)
	// {
	// 	cout<<vec[i]<<" ";
	// }
	// cout<<vec.size()<<endl;
	// int q = 1;
	// while(q<vec.size()){
	// 	tmp1.push_back(vec[q]);
	// 	q+=5;

	// 	// cout<<tmp.size()<<endl;
	// }
	
	sort(vec,l);
	first_time();

	do{
		time();
		
		queue();
		//display();
	//}while(Time<445);
	}while(!queue1.empty()||!c.empty()||!queue2.empty());
	// ||

	wait_time(queue3);

	final_display();
	cout<<endl;
	return 0;
}
