#include <iostream> 
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <cstdlib> 
#include <cstdio>
#include <vector>
#include <cassert>
#include <iomanip>
#include "math.h"
using namespace std;

int divid_number;
int frame_size;
int a_register;
int the_size;
int shift_time;

vector<string> vec;
void print_fifo();
void print_lru();
void print_arb();
long long int decimal(string& hex);
int find_longest_time();
class page{
public:
	string type;
	string id;
	string number;
	string command;
	string refer;
	string address;
	int time;
	int pageNumber;
	int level;
	string status;
	string dir;
	page(){
		type = "";
		id = "";
		number = "";
		command = "";
		address = "";
		dir="";
		pageNumber = 0;
	}
	page(int pageNumber){
		this->pageNumber = pageNumber;
	}
	page(string id, char type, int time, string address){
		this->id = id;
		this->type += type;
		this->time = time;
		this->address = address;
	}
};
class process_lru{
public:
	vector<page> store;
	int time;
	page newPage;

	int faults;
	string status;
	page replace_page;
	vector<page> write;
	vector<page> read;

	int w;
	int events;

	vector<page> total_write;
	vector<page> total_read;
	vector<page> frame;
	process_lru(){
		time = -1;

		faults = 0;

		status="";
		time = 0;

		for (int i = 0; i < frame_size; ++i)
		{
			page m = page(-1);
			frame.push_back(m);
		}
	}
	void sort(){
		for (int i = 0; i < frame.size(); ++i)
		{
			for (int j = i+1; j < frame.size(); ++j)
			{
				if (frame[i].pageNumber>frame[j].pageNumber)
				{
					page n = frame[i];
					frame[i] = frame[j];
					frame[j] = n;
				}
			}
		}
	}
	int judge_repeat(page s){
		for (int i = 0; i < frame.size(); ++i)
		{
			if (s.pageNumber==frame[i].pageNumber)
			{
				return i;
			}
		}
		return -99;
	}
	void add_final_read(page s){
		for (int i = 0; i < total_read.size(); ++i)
		{
			if (s.pageNumber== total_read[i].pageNumber)
			{
				return;
			}
		}
		total_read.push_back(s);
	}
	void add_final_write(page s){
		for (int i = 0; i < total_write.size(); ++i)
		{
			if (s.pageNumber== total_write[i].pageNumber)
			{
				return;
			}
		}
		total_write.push_back(s);
	}
	void check_repeat_r(page s){
		add_final_read(s);
		for (int i = 0; i < read.size(); ++i)
		{
			if (s.pageNumber== read[i].pageNumber)
			{
				return;
			}
		}
		read.push_back(s);
	}
	void check_repeat_w(page s){
		add_final_write(s);
		for (int i = 0; i < write.size(); ++i)
		{
			if (s.pageNumber== write[i].pageNumber)
			{
				return;
			}
		}
		write.push_back(s);
	}
	void remove_read(page s){

		if (read[0].pageNumber==s.pageNumber)
		{
			read.erase(read.begin());
			return;
		}
		for (int i = 1; i <	read.size(); ++i)
		{
			if (read[i].pageNumber==s.pageNumber)
			{
				read.erase(read.begin()+i);
			}
		}
	}
	void remove_write(page s){
		if (write[0].pageNumber==s.pageNumber)
		{
			write.erase(write.begin());
			return;
		}
		for (int i = 1; i <	write.size(); ++i)
		{
			if (write[i].pageNumber==s.pageNumber)
			{
				write.erase(write.begin()+i);
			}
		}
	}
	int find_longest_time_lru(){
		int p = frame[0].time;
		int place = 0;;
		for (int i = 0; i < frame.size(); ++i)
		{
			if (frame[i].time<p)
			{
				p = frame[i].time;
				place = i;
			}
		}
		return place;
	}
	void changePlace(){
		for (int i = 0; i < frame.size()-1; ++i)
		{
			frame[i] = frame[i+1];
		}
	}
	void lru(page s){
		time++;
		replace_page= -99;
		newPage = s;
		
		int e = judge_repeat(s);
		if (e==-99)
		{
			if (frame[0].pageNumber==-1)
			{
				if (s.type=="R")
				{
					check_repeat_r(s);
				}else if(s.type=="W"){
					check_repeat_w(s);
				}
				changePlace();
				s.time = time;
				frame[frame.size()-1] = s;
				faults++;
				status = "MISS";
			}else{
				if (s.type=="R")
				{
					check_repeat_r(s);
				}else if(s.type=="W"){
					check_repeat_w(s);
				}
				int f = find_longest_time_lru();
				replace_page = frame[f];
				frame[f] = s;
				frame[f].time = time;
				faults++;
				status = "MISS";
			}
		}else{
			if (s.type=="R")
			{
				check_repeat_r(s);
			}else if(s.type=="W"){
				check_repeat_w(s);
			}
			status = "HIT";

			frame[e].time = time;
			frame[e].status = "HIT";
		}
		
		sort();
		print_lru();

	}
	bool ch(){
		for (int i = 0; i < write.size(); ++i)
		{
			if (replace_page.pageNumber==write[i].pageNumber)
			{
				return false;
			}
		}
		return true;
	}
	void print_lru(){
		cout<<"Time  ";
		if (time>=10)
		{
			cout<<time;
		}else{
			cout<<" "<<time;
		}
		if (status=="MISS")
		{
			cout<<"  "<<status<<":";
		}else{
			cout<<"  "<<status<<": ";
		}
		if (newPage.pageNumber>9)
		{
			cout<<"    page "<<newPage.pageNumber;
		}else{
			cout<<"    page  "<<newPage.pageNumber;
		}
		if (replace_page.pageNumber!=-99)
		{
			cout<<"  REPLACE: page   "<<replace_page.pageNumber;
			if (!ch())
			{
				cout<<"  (DIRTY)   ";
				w++;
				remove_read(replace_page);	
				remove_write(replace_page);
			}else{
				cout<<"         ";
			}
		}else{
			cout<<"                              ";
		}
		cout<<"frame:  ";
		for (int i = 0; i < frame.size(); ++i)
		{
			cout<<frame[i].pageNumber<<" ";
		}
		cout<<endl;
		replace_page.pageNumber= -99;
	}


	int find_longest_time(){
		if (frame[0].time<frame[1].time&&frame[0].time<frame[2].time)
		{
			return 0;
		}else if (frame[1].time<frame[0].time&&frame[1].time<frame[2].time)
		{
			return 1;
		}else if (frame[2].time<frame[0].time&&frame[2].time<frame[1].time)
		{
			return 2;
		}
		return -99;
	}

	void simply(){
		string p = vec[0].erase(0,2);
		for (int i = 1; i < vec.size(); ++i)
		{
			char a = vec[i].at(0);
			page l = page(p, a,  0, vec[i].erase(0,2));
			store.push_back(l);
		}
		for (int i = 0; i < store.size(); ++i)
		{	
			string q = store[i].address;

			int result ;
		    unsigned int x;   
		    std::stringstream ss;
		    ss << std::hex << q;
		    ss >> x;
		    result = static_cast<int>(x);
		    store[i].pageNumber = result/divid_number;
		}
		int ii = 0;
		while(ii<store.size()){
			lru(store[ii]);
			ii++;
		}
		events = ii;
	}
	void print_output(){
		cout<<"events in trace:    "<<events<<endl;
		cout<<"total disk reads:   "<<faults<<endl;
		cout<<"total disk writes:  "<<w<<endl;
		cout<<"page faults:        "<<faults<<endl;
	}
	
};
class process_fifo{
public:
	vector<page> store;
	int time;
	page newPage;

	int faults;
	string status;
	page replace_page;
	vector<page> write;
	vector<page> read;
	int w;
	int events;

	vector<page> total_write;
	vector<page> total_read;
	vector<page> frame;
	process_fifo(){
		time = -1;

		faults = 0;

		status="";
		time = 0;

		for (int i = 0; i < frame_size; ++i)
		{
			page m = page(-1);
			frame.push_back(m);
		}
	}
	void sort(){
		for (int i = 0; i < frame.size(); ++i)
		{
			for (int j = i+1; j < frame.size(); ++j)
			{
				if (frame[i].pageNumber>frame[j].pageNumber)
				{
					page n = frame[i];
					frame[i] = frame[j];
					frame[j] = n;
				}
			}
		}
	}
	int judge_repeat(page s){
		for (int i = 0; i < frame.size(); ++i)
		{
			if (s.pageNumber==frame[i].pageNumber)
			{
				return i;
			}
		}
		return -99;
	}
	void add_final_read(page s){
		for (int i = 0; i < total_read.size(); ++i)
		{
			if (s.pageNumber== total_read[i].pageNumber)
			{
				return;
			}
		}
		total_read.push_back(s);
	}
	void add_final_write(page s){
		for (int i = 0; i < total_write.size(); ++i)
		{
			if (s.pageNumber== total_write[i].pageNumber)
			{
				return;
			}
		}
		total_write.push_back(s);
	}
	void check_repeat_r(page s){
		add_final_read(s);
		for (int i = 0; i < read.size(); ++i)
		{
			if (s.pageNumber== read[i].pageNumber)
			{
				return;
			}
		}
		read.push_back(s);
	}
	void check_repeat_w(page s){
		add_final_write(s);
		for (int i = 0; i < write.size(); ++i)
		{
			if (s.pageNumber== write[i].pageNumber)
			{
				return;
			}
		}
		write.push_back(s);
	}
	void remove_read(page s){

		if (read[0].pageNumber==s.pageNumber)
		{
			read.erase(read.begin());
			return;
		}
		for (int i = 1; i <	read.size(); ++i)
		{
			if (read[i].pageNumber==s.pageNumber)
			{
				read.erase(read.begin()+i);
			}
		}
	}
	void remove_write(page s){
		if (write[0].pageNumber==s.pageNumber)
		{
			write.erase(write.begin());
			return;
		}
		for (int i = 1; i <	write.size(); ++i)
		{
			if (write[i].pageNumber==s.pageNumber)
			{
				write.erase(write.begin()+i);
			}
		}
	}
	void changePlace(){
		for (int i = 0; i < frame.size()-1; ++i)
		{
			frame[i] = frame[i+1];
		}
	}
	void fifo(page s){
		time++;
		replace_page= -99;
		newPage = s;
		int e = judge_repeat(s);
		if (e==-99)
		{
			if (frame[0].pageNumber==-1)
			{
				if (s.type=="R")
				{
					check_repeat_r(s);
				}else if(s.type=="W"){
					check_repeat_w(s);
				}
				changePlace();
				frame[frame.size()-1] = s;
				faults++;
				status = "MISS";
			}else{
				if (s.type=="R")
				{
					check_repeat_r(s);
				}else if(s.type=="W"){
					check_repeat_w(s);
				}

				int f = find_longest_time();
				replace_page = frame[f];
				frame[f] = s;
				frame[f].time = time;
				faults++;
				status = "MISS";
			}
			
		}else{
			if (s.type=="R")
			{
				check_repeat_r(s);
			}else if(s.type=="W"){
				check_repeat_w(s);
			}
			status = "HIT";
			// frame[e].time = time;
			frame[e].status = "HIT";
		}
			// }
		sort();
		print_fifo();

	}
	bool ch(){
		for (int i = 0; i < write.size(); ++i)
		{
			if (replace_page.pageNumber==write[i].pageNumber)
			{
				return false;
			}
		}
		return true;
	}
	void print_fifo(){
		cout<<"Time  ";
		if (time>=10)
		{
			cout<<time;
		}else{
			cout<<" "<<time;
		}
		if (status=="MISS")
		{
			cout<<"  "<<status<<":";
		}else{
			cout<<"  "<<status<<": ";
		}
		if (newPage.pageNumber>9)
		{
			cout<<"    page "<<newPage.pageNumber;
		}else{
			cout<<"    page  "<<newPage.pageNumber;
		}
		if (replace_page.pageNumber!=-99)
		{
			cout<<"  REPLACE: page   "<<replace_page.pageNumber;
			if (!ch())
			{
				cout<<"  (DIRTY)   ";
				w++;
				remove_read(replace_page);	
				remove_write(replace_page);
			}else{
				cout<<"         ";
			}
		}else{
			cout<<"                              ";
		}
		cout<<"frame:  ";
		for (int i = 0; i < frame.size(); ++i)
		{
			cout<<frame[i].pageNumber<<" ";
		}
		cout<<endl;

		replace_page.pageNumber= -99;
	}


	int find_longest_time(){
		int p = frame[0].time;
		int place = 0;;
		for (int i = 0; i < frame.size(); ++i)
		{
			if (frame[i].time<p)
			{
				p = frame[i].time;
				place = i;
			}
		}
		return place;
	}
	void simply(){
		string p = vec[0].erase(0,2);
		for (int i = 1; i < vec.size(); ++i)
		{
			char a = vec[i].at(0);
			page l = page(p, a,  0, vec[i].erase(0,2));
			store.push_back(l);
		}
		for (int i = 0; i < store.size(); ++i)
		{	
			string q = store[i].address;

			int result ;
		    unsigned int x;   
		    std::stringstream ss;
		    ss << std::hex << q;
		    ss >> x;
		    result = static_cast<int>(x);
		    store[i].pageNumber = result/divid_number;
		}
		int ii = 0;
		while(ii<store.size()){
			fifo(store[ii]);
			ii++;
		}
		events = ii;
	}
	void print_output(){
		cout<<"events in trace:    "<<events<<endl;
		cout<<"total disk reads:   "<<faults<<endl;
		cout<<"total disk writes:  "<<w<<endl;
		cout<<"page faults:        "<<faults<<endl;

	}
};
int de(string &q){
	int result = 0;
	char p ;
	for (int i = 0; i < q.size(); ++i)
	{
		if (q.at(i)!=48)
		{
			p =q.at(i);
			break;
		}
		if (i==q.length()-1)
		{
			p='0';
		}
	}
	switch(p){
		case '0'...'9':
			result = p-48;
			break;
		case 'a'...'f':
			result = p- 87;
			break;
	}
	return result;
}

long long int decimal(string& hex){
	long long int result = 0;
    for (int i=0; i<hex.length(); i++) {
        if (hex[i]>=48 && hex[i]<=57)
        {
            result += (hex[i]-48)*pow(16,hex.length()-i-1);
        } else if (hex[i]>=65 && hex[i]<=70) {
            result += (hex[i]-55)*pow(16,hex.length( )-i-1);
        } else if (hex[i]>=97 && hex[i]<=102) {
            result += (hex[i]-87)*pow(16,hex.length()-i-1);
        }
    }
    return result;
}




class process_arb{
public:
	vector<page> store;
	int time;
	page newPage;

	int faults;
	string status;
	page replace_page;
	vector<page> write;
	vector<page> read;
	int w;
	int events;
	page prev;
	vector<page> total_write;
	vector<page> total_read;
	vector<page> frame;
	process_arb(){
		time = -1;

		faults = 0;

		status="";
		time = 0;

		for (int i = 0; i < frame_size; ++i)
		{
			page m = page(-1);
			for (int j = 0; j < a_register; ++j)
			{
				m.refer+='0';
			}
			frame.push_back(m);
		}
	}
	void sort(){
		for (int i = 0; i < frame.size(); ++i)
		{
			for (int j = i+1; j < frame.size(); ++j)
			{
				if (frame[i].pageNumber>frame[j].pageNumber)
				{
					page n = frame[i];
					frame[i] = frame[j];
					frame[j] = n;
				}
			}
		}
	}
	int judge_repeat(page s){
		for (int i = 0; i < frame.size(); ++i)
		{
			if (s.pageNumber==frame[i].pageNumber)
			{
				return i;
			}
		}
		return -99;
	}
	void add_final_read(page s){
		for (int i = 0; i < total_read.size(); ++i)
		{
			if (s.pageNumber== total_read[i].pageNumber)
			{
				return;
			}
		}
		total_read.push_back(s);
	}
	void add_final_write(page s){
		for (int i = 0; i < total_write.size(); ++i)
		{
			if (s.pageNumber== total_write[i].pageNumber)
			{
				return;
			}
		}
		total_write.push_back(s);
	}
	void check_repeat_r(page s){
		add_final_read(s);
		for (int i = 0; i < read.size(); ++i)
		{
			if (s.pageNumber== read[i].pageNumber)
			{
				return;
			}
		}
		read.push_back(s);
	}
	void check_repeat_w(page s){
		add_final_write(s);
		for (int i = 0; i < write.size(); ++i)
		{
			if (s.pageNumber== write[i].pageNumber)
			{
				return;
			}
		}
		write.push_back(s);
	}
	void remove_read(page s){

		if (read[0].pageNumber==s.pageNumber)
		{
			read.erase(read.begin());
			return;
		}
		for (int i = 1; i <	read.size(); ++i)
		{
			if (read[i].pageNumber==s.pageNumber)
			{
				read.erase(read.begin()+i);
			}
		}
	}
	void remove_write(page s){
		if (write[0].pageNumber==s.pageNumber)
		{
			write.erase(write.begin());
			return;
		}
		for (int i = 1; i <	write.size(); ++i)
		{
			if (write[i].pageNumber==s.pageNumber)
			{
				write.erase(write.begin()+i);
			}
		}
	}
	void change_refer(){
		for (int j = 0; j < frame.size(); ++j)
		{
			for (int i = 0; i < frame[j].refer.length(); ++i)
			{
				if (i!=frame[j].refer.length()-1)
				{
					frame[j].refer[frame[j].refer.length()-(i+1)] = frame[j].refer[frame[j].refer.length()-(i+2)];
				}else{
					frame[j].refer[0] = '0';
				}
				
			}
		}
	}
	void change_exist_refer(page s){

		for (int j = 0; j < frame.size(); ++j)
		{
			for (int i = 0; i < frame[j].refer.length(); ++i)
			{
				if (s.pageNumber == frame[j].pageNumber)
				{
					if (frame[j].refer[0] == '0')
					{
						frame[j].refer[0] = '1';
						break;
					}else{
						if (i!=frame[j].refer.length()-1)
						{
							frame[j].refer[frame[j].refer.length()-(i+1)] = frame[j].refer[frame[j].refer.length()-(i+2)];
						}else{
							frame[j].refer[0] = '1';
							break;
						}
					}
					
				}else{
					if (i!=frame[j].refer.length()-1)
					{
						frame[j].refer[frame[j].refer.length()-(i+1)] = frame[j].refer[frame[j].refer.length()-(i+2)];
					}else{
						frame[j].refer[0] = '0';
					}
				}
			}
		}
	}
	void change_exist_refer_read(page s){
		for (int j = 0; j < frame.size(); ++j)
		{
			for (int i = 0; i < frame[j].refer.length(); ++i)
			{
				if (s.pageNumber == frame[j].pageNumber)
				{
					if (frame[j].refer[0] == '0')
					{
						frame[j].refer[0] = '1';
						break;
					}else{
						if (i!=frame[j].refer.length()-1)
						{
							frame[j].refer[frame[j].refer.length()-(i+1)] = frame[j].refer[frame[j].refer.length()-(i+2)];
						}else{
							frame[j].refer[0] = '1';
							break;
						}
					}
				}
			}
		}
	}
	int find_longest_time_arb(){
		int p = frame[0].time;
		int place = 0;;
		for (int i = 0; i < frame.size(); ++i)
		{
			if (frame[i].time>p)
			{
				p = frame[i].time;
				place = i;
			}
		}
		return place;
	}
	void changePlace(){
		for (int i = 0; i < frame.size()-1; ++i)
		{
			frame[i] = frame[i+1];
		}
	}
	void shift(page s){
		if ((time-1)%shift_time==0&&(time-1)!=0)
		{
			for (int j = 0; j < frame.size(); ++j)
			{
				for (int i = 0; i < frame[j].refer.length(); ++i)
				{
					if (i!=frame[j].refer.length()-1)
					{
						frame[j].refer[frame[j].refer.length()-(i+1)] = frame[j].refer[frame[j].refer.length()-(i+2)];
					}else{
						frame[j].refer[0] = '0';
					}
				}
			}
			for (int i = 0; i < frame.size(); ++i)
			{
				if (s.pageNumber == frame[i].pageNumber)
				{
					frame[i].refer[0] = '1';
				}
			}
		}
	}
	int judge_change(page s){
		vector<int> place;
		string p = frame[0].refer;
		
		for (int i = 0; i < frame.size(); ++i)
		{
			if (frame[i].refer.compare(p)<0)
			{
				p = frame[i].refer;
			}
		}
		for (int i = 0; i < frame.size(); ++i)
		{
			if (frame[i].refer.compare(p)==0)
			{
				place.push_back(i);
			}
		}
		if (place.size()==1)
		{

			return place[0];
		}else{
			int t = frame[place[0]].time;
			int pl = place[0];
			for (int i = 0; i < place.size(); ++i)
			{
				if (frame[place[i]].time<t)
				{
					p = frame[place[i]].time;
					pl = place[i];

				}
			}
			return pl;
		}
	}
	void arb(page s){
		time++;
		replace_page= -99;
		prev = newPage;
		newPage = s;
		int e = judge_repeat(s);
		shift(s);
		if (e==-99)
		{
			if (frame[0].pageNumber==-1)
			{
				if (s.type=="R")
				{
					check_repeat_r(s);
				}else if(s.type=="W"){
					check_repeat_w(s);
				}
				changePlace();
				frame[frame.size()-1] = s;
				faults++;
				status = "MISS";
			}else{
				if (s.type=="R")
				{
					check_repeat_r(s);

				}else if(s.type=="W"){
					check_repeat_w(s);

				}
				int cc = judge_change(s);

				replace_page = frame[cc];
		
				frame[cc] = s;
				frame[cc].time = time;

				faults++;
				status = "MISS";
			}
			
		}else{
			if (s.type=="R")
			{
				check_repeat_r(s);

			}else if(s.type=="W"){
				check_repeat_w(s);

			}
			for (int i = 0; i < frame.size(); ++i)
			{
				if (s.pageNumber == frame[i].pageNumber)
				{
					frame[i].refer[0] = '1';
				}
			}
			status = "HIT";
			// frame[e].time = time;
			frame[e].status = "HIT";
		}
		
		sort();
		
		print_arb();

	}
	bool ch(){
		for (int i = 0; i < write.size(); ++i)
		{
			if (replace_page.pageNumber==write[i].pageNumber)
			{
				return false;
			}
		}
		return true;
	}
	void print_arb(){
		cout<<"Time  ";
		if (time>=10)
		{
			cout<<time;
		}else{
			cout<<" "<<time;
		}
		if (status=="MISS")
		{
			cout<<"  "<<status<<":";
		}else{
			cout<<"  "<<status<<": ";
		}
		if (newPage.pageNumber>9)
		{
			cout<<"    page "<<newPage.pageNumber;
		}else{
			cout<<"    page  "<<newPage.pageNumber;
		}
		if (replace_page.pageNumber!=-99)
		{
			cout<<"  REPLACE: page   "<<replace_page.pageNumber;
			if (!ch())
			{
				cout<<"  (DIRTY)   ";
				w++;
				remove_read(replace_page);	
				remove_write(replace_page);
			}else{
				cout<<"         ";
			}
		}else{
			cout<<"                              ";
		}
		cout<<"frame:  ";
		for (int i = 0; i < frame.size(); ++i)
		{
			cout<<frame[i].pageNumber<<"("<<frame[i].refer<<")"<<" ";
		}
		cout<<endl;
	
		replace_page.pageNumber= -99;
	}


	int find_longest_time(){
		if (frame[0].time<frame[1].time&&frame[0].time<frame[2].time)
		{
			return 0;
		}else if (frame[1].time<frame[0].time&&frame[1].time<frame[2].time)
		{
			return 1;
		}else if (frame[2].time<frame[0].time&&frame[2].time<frame[1].time)
		{
			return 2;
		}
		return -99;
	}

	void simply(){
		string p = vec[0].erase(0,2);
		for (int i = 1; i < vec.size(); ++i)
		{
			char a = vec[i].at(0);
			page l = page(p, a,  0, vec[i].erase(0,2));
			l.refer="1000";
			store.push_back(l);
		}
		for (int i = 0; i < store.size(); ++i)
		{	
			string q = store[i].address;
			int result ;
		    unsigned int x;   
		    std::stringstream ss;
		    ss << std::hex << q;
		    ss >> x;
		    result = static_cast<int>(x);
		    store[i].pageNumber = result/divid_number;
		}
		int ii = 0;
		while(ii<store.size()){

			arb(store[ii]);
			ii++;
		}
		events = ii;
	}
	void print_output(){
		cout<<"events in trace:    "<<events<<endl;
		cout<<"total disk reads:   "<<faults<<endl;
		cout<<"total disk writes:  "<<w<<endl;
		cout<<"page faults:        "<<faults<<endl;

	}
};

// vector<page> store;

int main(int argc, char const *argv[])
{

	string s="";
	int l = 0;
	std::ifstream file("input.txt");
	if (file.is_open()) {
	    string line;
	    while (getline(file, line)) {
	        s+=line;
	        s+='\n';
	        if (line[0]=='#')
	        {
	        	vec.push_back(line);
	        }else{
	        	vec.push_back(line);
	        }
	    }
	    file.close();
	}
	divid_number = atoi(argv[2]);
		frame_size = atoi(argv[3]);
	string file_type = argv[4];
	if (file_type=="FIFO")
	{
	
		process_fifo m = process_fifo();
		m.simply();
		m.print_output();
	}else if(file_type=="LRU"){
	
		process_lru m = process_lru();
		m.simply();
		m.print_output();
	}else if(file_type=="ARB"){
		a_register = atoi(argv[5]);
		shift_time = atoi(argv[6]);
		process_arb m = process_arb();
				cout<<123<<endl;
		m.simply();
		m.print_output();
	}
	return 0;
}
