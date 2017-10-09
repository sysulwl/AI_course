#include<iostream>
#include<fstream>
#include<map>
#include<vector> 
#include<sstream>
#include<cmath>
#include<algorithm>
using namespace std;
double P[250][6]; 
double DIS[500][246];
//1.我现在遇到的一个最大的技术问题，就是怎么读取完一行字符床，其中一串不固定的字符串之后 ，有6个数字 
struct Three_Var
{
	int i,j;
	bool operator<(Three_Var& t) {return i<t.i||(i==t.i&&j<t.j);}
	bool operator==(Three_Var& t) {return i==t.i&&j==t.j;}
};
bool Sort( Three_Var d1,Three_Var d2)    {return d1 < d2;}   //降序排列
vector< vector<int> > NumsPerLines; 
int main()
{
	int index=0;//依次出现的（去重）词汇的对应下标 
	int Lines=0;//出现的行数 
	int ThreeVarNums=0;//三元组的个数 
	ifstream Input;
	Input.open("Dataset_train.txt");//读取文件 
	string line;	//一个临时变量而已 
	map<string, int> FirstIndex;//string是对应的词汇，int是它（无视重复下）第一次出现的在该map中的下标
	map<int,int> repeatTimes; 
	vector<Three_Var> smat;
	vector<int> Emo;
	bool first = true;//因为训练文本第一行没用；
	ofstream Info,Pro;
	Info.open("EveryLine.txt");
	Pro.open("Pro.txt");
	while(getline(Input,line))
	{		
		if(first) {first = false;continue;} 
		stringstream ss;
		int temp = 0;
		//几经周折注意到一个事实：用写字板或者dev_cpp打开时可以清楚地看见是一行一句话的，所以用stringstream
		//整行读入的特性会方便很多 
		ss.clear(); 
		ss.str(line);
		string dict; 
		ss >> dict ; //读入train_这个没用的单词 
		map<string,int>::iterator it1;
		map<int,int>::iterator it2;
		repeatTimes.clear();
		int P_OF_EMO = 0;
		while(ss>>dict)  //读入每行的数据集内容的词汇 
		{
			stringstream See(dict); 
			double doub;
			See >> doub;
			if(!See.fail())//是个数字
			{
 				P[Lines][P_OF_EMO] = doub;
 				P_OF_EMO++;
 				Info<<doub<<" ";
			} 
			else{               //不是数字就是普通字符了 
				if(dict == "？") break; //Dataset_test 中的数字被问号代替了 
				Info<<dict<<" ";
				it1=FirstIndex.find(dict); //first元素的map查找函数 
				if(it1==FirstIndex.end())//迭代器到了end()，说明这个词还没出现过 
				{
					FirstIndex.insert(pair<string,int>(dict,index));
					index++;  //维护map中的下标 
				}
				it2=repeatTimes.find(FirstIndex[dict]);
				if(it2==repeatTimes.end())//这个下标第一次出现的话，放进这个repaeatTimes<int,int>中 
				{ repeatTimes.insert(pair<int,int>(FirstIndex[dict],1));	}
				else
					it2->second++; 
				temp++;
			}	
		}
		Info<<temp<<endl;
		//读取完这行词汇了 
		
		vector <int> Temp_Vec;
		for(it2=repeatTimes.begin();it2!=repeatTimes.end();it2++)  //为了在vector中有序，借用这个map 
		{
			Three_Var item{Lines,it2->first};//利用机构体记录这个单词出现的行数，下标
			smat.push_back(item);
			ThreeVarNums++;//结构体vector中放入的个数 
			Temp_Vec.push_back(it2->first);//这个结构存储每一行拥有的字符串的下标；
		}
		NumsPerLines.push_back(Temp_Vec);
		Lines++;  //第几行计数 
		if(Lines == 246){
			first = true;
			Input.close();
			Input.open("Dataset_test.txt");
		}
	}
	cout<<"共有行数："<<Lines<<"; 不同的字符串个数"<<index<<endl;
	cout<<"有二元组个数"<<ThreeVarNums<<endl;

	Input.close();
	cout<<"Input operation has done!"<<endl;
	//读取完整个文档 
	
	//接下来进行处理数据 
	sort(smat.begin(),smat.end(),Sort);
	ofstream OneHot,SMATRIX1;
	OneHot.open("OneHot.txt");
	SMATRIX1.open("smatrix1.txt"); //三元组矩阵 
	SMATRIX1<<Lines<<endl<<index<<endl<<ThreeVarNums<<endl;
	int pos=0;
	int RightNums = 0;
	Info <<"距离矩阵 : " <<endl; 
	for(int i = 0;i<Lines;i++) //行数 
	{
		/*————————每一行的处理————————*/ 
		for(int j = 0;j < index; j++) //字符串下标 
		{
			if(smat[pos].i==i && smat[pos].j==j)  //匹配到一个字符串出现 
			{
				OneHot<<1<<" ";      //OneHot矩阵为1  
				SMATRIX1<<i<<" "<<j<<" "<<1<<endl;	//输出到三元组 
				pos++;//找下一个字符串了 
			}
			else
			{
				OneHot<<0<<" ";       //不出现，这3个矩阵都是0，三元组则例外 
			}
			/*----————————--处理完一行了----——---*/ 
		}
		if(i >= 246){//test.txt来分类咯； 
			int MinLine = 0; 
			Info << i <<" ";
				for(int r = 0; r < 246; r++){ //与训练文本的每一行求欧式距离
						int dis = 0;
						int c = 0 , k = 0 , equals = 0; 
						for(; c < NumsPerLines[i].size() ; c++){ //当前行的字符串 
							for(; k < NumsPerLines[r].size(); k++){
								if(NumsPerLines[i][c] <  NumsPerLines[r][k])
									break;
								else if(NumsPerLines[i][c] ==  NumsPerLines[r][k])
									equals++;
							}
						}
					    dis = NumsPerLines[i].size() + NumsPerLines[r].size() - equals * 2;//得到这个距离了
						DIS[i-246][r] = dis;   //得到距离矩阵 
						Info<<dis <<" ";
				} 	
				Info <<endl;
		} 
		OneHot<<endl;       //每一句新闻后都换行咯
	}	
	for(int i = 0 ; i < Lines; i++)
	{
		Info<<i<<": ";
		for(int j = 0 ; j < NumsPerLines[i].size(); j++)
		{
			Info<<NumsPerLines[i][j]<<" ";
		}
		Info<<endl;
	}
	map<string,int>::iterator it;
	for(it = FirstIndex.begin();it != FirstIndex.end(); it++)
	{
		Info << it->first <<" " << it->second<<endl;
	}
	cout<<"File operation has done!"<<endl;
	for(int i = 0 ; i < 500; i++) //实际上代表第 i + 246 行 
	{
		Pro <<"test"<< i+1 <<" ";
		double SUM[6], all = 0;
		for(int j = 0 ; j < 6 ; j++)
		{
			double sum = 0;
			for(int k = 0; k < 246 ; k++)
			{
				sum += P[k][j]/ DIS[i][k];
			}
			SUM[j] = sum;
			all += sum;
		}
		for(int j = 0 ; j < 6 ; j++) //归一化 
		{
			Pro << SUM[j]/all<<" ";
		}
		Pro << endl;
	} 
	//cout<<"The right rate is "<<(double)(RightNums)/1000<<endl;
	/*---------------完成操作，关闭文件输出流 ---------------*/ 
	OneHot.close();
	SMATRIX1.close();
	Info.close();
	return 0;
}
