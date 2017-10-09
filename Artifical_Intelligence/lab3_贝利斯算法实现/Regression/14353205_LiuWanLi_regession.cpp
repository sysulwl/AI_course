#include<iostream>
#include<fstream>
#include<map>
#include<vector> 
#include<sstream>
#include<cmath>
#include<algorithm>
#define TRAINLINES 246
using namespace std;
double P[250][6]; 
double tf[250][2000];
//1.我现在遇到的一个最大的技术问题，就是怎么读取完一行字符床，其中一串不固定的字符串之后 ，有6个数字 
struct Three_Var
{
	int i,j,v;
	bool operator<(Three_Var& t) {return i<t.i||(i==t.i&&j<t.j);}
	bool operator==(Three_Var& t) {return i==t.i&&j==t.j;}
};
vector< vector<int> > NumsPerLines; 
int index=0;//依次出现的（去重）词汇的对应下标 
int Lines=0;//出现的行数 
int ThreeVarNums=0;//三元组的个数 
string line;	//一个临时变量而已 
map<string, int> FirstIndex;//string是对应的词汇，int是它（无视重复下）第一次出现的在该map中的下标
map<int,int> repeatTimes,AppearLines; 
vector<Three_Var> smat;
vector<int> Emo;
bool first = true;//因为训练文本第一行没用；
int temp = 0;
map<string,int>::iterator it1;
map<int,int>::iterator it2;
map<int,int>::iterator it3;
vector<int> NumsOfLines;//每行的词汇个数 （重复不算1个）
void Do(string dict)
{
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
int main()
{
	ifstream Input;
	ofstream Info;
	Info.open("EveryLine.txt");
	Input.open("Dataset_train.txt");//读取文件 
	while(getline(Input,line))
	{		
		if(first) {first = false;continue;} 
		stringstream ss;
		temp = 0;
		ss.clear(); 
		ss.str(line);
		string dict; 
		ss >> dict ; //读入train_这个没用的单词 
		repeatTimes.clear();
		dict = dict.substr(dict.find(",")+1,dict.size());
		Info <<dict<<" ";
		Do(dict);
		int P_OF_EMO = 0;
		while(ss>>dict)  //读入每行的数据集内容的词汇 
		{
			if(dict.find(",") <= dict.size()) //是最后一个字符串 
			{
				string T = dict.substr(0,dict.find(","));
				Info<<T<<" ";
				Do(T);
				T = dict;
				int prepos = T.find(",");
				T[prepos] = '*';
				int lastpos = T.find(",");
				for(int i = 0 ; i < 6; i++)
				{
					string a = T.substr(prepos+1,lastpos);
					stringstream xxx(a);
					double doub;
					xxx>>doub;
					P[Lines][i+1] = doub;  //得到每个文档每种感情的概率矩阵 
					Info<<doub<<" ";
					prepos = lastpos;
					T[prepos] = '*';
					lastpos = T.find(",");
				}
			}
			else   
			{
				Info<<dict<<" ";
				Do(dict);	
			}
			
		}
		Info<<temp<<endl;
		//读取完这行词汇了 
		for(it2=repeatTimes.begin();it2!=repeatTimes.end();it2++)
		{
			it3=AppearLines.find(it2->first);//每个词汇对应的下标重复的次数 
			//计算在所有数据集中出现的次数 
			if(it3==AppearLines.end()) //如果是空的，说明第一次出现 
				AppearLines.insert(pair<int,int>(it2->first,1));
			else
				it3->second++; //it3的second存储的是对应下标的字符串出现的行数 
			Three_Var item{Lines,it2->first,it2->second};
			//利用机构体记录这个单词出现的行数，下标，重复次数 
			smat.push_back(item);
			ThreeVarNums++;//结构体vector中放入的个数 
		}
		Lines++;  //第几行计数 
		NumsOfLines.push_back(temp);//记录好每行的词汇个数 
	}
	Input.close();
	//读取完整个文档 
	ofstream OneHot,TF,TF_IDF,SMATRIX1;
	OneHot.open("OneHot");
	TF.open("TF");
	SMATRIX1.open("smatrix1"); //三元组矩阵 
	SMATRIX1<<Lines<<endl<<index<<endl<<ThreeVarNums<<endl;
	int pos=0;
	for(int i=0;i<Lines;i++) //行数 
	{
		/*————————每一行的处理————————*/ 
		for(int j=0;j<index;j++) //字符串下标 
		{
			if(smat[pos].i==i&&smat[pos].j==j)  //匹配到一个字符串出现 
			{
				OneHot<<1<<" ";      //OneHot矩阵为1 
				double rate=(double)smat[pos].v/NumsOfLines[i];  //归一化频率 
				TF<<rate<<" ";
				tf[i][j] = rate;  
				SMATRIX1<<i<<" "<<j<<" "<<1<<endl;	//输出到三元组 
				if(smat[pos].i>=Lines/2)
					smat[pos].i-=Lines/2;
				pos++;//找下一个字符串了 
			}
			else
			{
				OneHot<<0<<" ";       //不出现，这3个矩阵都是0，三元组则例外 
				TF<<0<<" ";
				tf[i][j] = 0;
			}
			/*----————————--处理完一行了----——---*/ 
		}
		OneHot<<endl;       //每一句新闻后都换行咯
		TF<<endl;
	}	
	/*---------------完成操作，关闭文件输出流 ---------------*/ 
	OneHot.close();
	TF.close();
	SMATRIX1.close();
	Info.close();
	printf("有%d个字符串\n",index); 
	
	/*----------读取测试文档-------------------*/ 
	ofstream output;
	output.open("myResult.txt");
	Input.open("Dataset_validation.txt");//读取文件 
	first = true;	
	string line;
	while(getline(Input,line))
	{		
		vector<string> thisLine;
		if(first) {first = false;continue;} 
		stringstream ss;
		ss.clear(); 
		ss.str(line);
		string dict; 
		ss >> dict ; //读入train_这个没用的单词 
		dict = dict.substr(dict.find(",")+1,dict.size());
		thisLine.push_back(dict);	
	
		while(ss>>dict)  //读入每行的数据集内容的词汇 
		{
			if(dict.find(",") <= dict.size()) //是最后一个字符串 
			{
				string T = dict.substr(0,dict.find(",")); //提取词汇 
				thisLine.push_back(T);
			}
			else   
			{
				thisLine.push_back(dict);	
			}
		}
		
		double pro[7];
		double sum = 0;
		for(int i = 1 ; i <= 6; i++) pro[i] = 0;
		for(int j = 1; j <= 6; j++)  //感情 
		{
			for(int i = 0 ; i < TRAINLINES; i++) //训练行数 
			{
				double k = 1.0;
				double sum_xk = 0;
				for(int x = 0 ; x < thisLine.size() ;x++)
				{
					sum_xk += tf[i][ FirstIndex.find(thisLine[x]) -> second];
				}
				for(int x = 0 ; x < thisLine.size() ;x++)//这行的词汇个数
				{
					//这里用了拉普拉斯平滑 
					if(tf[i][ FirstIndex.find(thisLine[x]) -> second] == 0)
					k *= (( tf[i][ FirstIndex.find(thisLine[x]) -> second] + 1 ) /(sum_xk + thisLine.size()) );
					else
					k *= tf[i][ FirstIndex.find(thisLine[x]) -> second];
				}
				k *= P[i][j];
				pro[j] += k;
			}
			sum += pro[j];
		}
		//归一化并输出到文档中
		for(int j = 1; j <= 6; j++)
		{
			pro[j] = pro[j] / sum;
			output<< pro[j] <<" ";
		} 
		output<<endl;
	}
	cout<<"Finish!!!"<<endl;
	Input.close();
	return 0;
}
