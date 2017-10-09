#include<iostream>
#include<bits/stdc++.h> 
using namespace std;
//共有 TRAIN_LINES 个训练样本 
#define TRAIN_LINES 30162 
int tarinLabels[35000] = {0};
struct Three_Var
{
	int i,j;
	bool operator<(Three_Var& t) {return i<t.i||(i==t.i&&j<t.j);}
	bool operator>(Three_Var& t) {return i>t.i||(i==t.i&&j>t.j);}
	bool operator==(Three_Var& t) {return i==t.i&&j==t.j;}
};
bool Sort( Three_Var d1,Three_Var d2)//容器的比较函数  
{    
    return d1 < d2;//降序排列     
}   
vector< vector<int> > NumsPerLines; 
int index=0;//依次出现的（去重）词汇的对应下标 
int Lines = 1;//出现的行数 
int ThreeVarNums=0;//三元组的个数 
ifstream Input;
string line;	//一个临时变量而已 
map<string, int> FirstIndex;//string是对应的词汇，int是它（无视重复下）第一次出现的在该map中的下标
map<int,int> repeatTimes; 
vector<int> NumsOfLines;//每行的词汇个数 （重复不算1个）
vector<Three_Var> smat;
vector<int> Emo;
bool first = true;//因为训练文本第一行没用；
ofstream Info;

void readData()
{
	Input.open("knn_train_data.txt");//读取文件
	Info.open("EveryLine.txt");
	while(getline(Input,line))
	{		
		if(first) {
			first = false;
			continue;
		} 
		stringstream ss;
		//几经周折注意到一个事实：用写字板或者dev_cpp打开时可以清楚地看见是一行一句话的，所以用stringstream
		//整行读入的特性会方便很多 
		ss.clear(); 
		ss.str(line);
		string EXM;
		string dict;  
		map<string,int>::iterator it1;
		map<int,int>::iterator it2;
		repeatTimes.clear();
		for(int fuck = 1; fuck <= 8 ; fuck++) //读入每行的数据集内容的词汇 
		{
			ss>>dict
			it1=FirstIndex.find(dict); //first元素的map查找函数 
			if(it1==FirstIndex.end())//迭代器到了end()，说明这个词还没出现过 
			{
				FirstIndex.insert(pair<string,int>(dict,index));
				index++;  //维护map中的下标 
			}
			it2=repeatTimes.find(FirstIndex[dict]);//计算该词汇在数据集中重复出现的次数 
			if(it2==repeatTimes.end())//这个下标第一次出现的话，放进这个repaeatTimes<int,int>中 
			{
				Info << dict<<" ";
				repeatTimes.insert(pair<int,int>(FirstIndex[dict],1));
				//第一个整数记录它在map中的下标，第二个整数记录它重复的次数 
			}
				
			else
				it2->second++;//否则，维护好这个RepeatTimes即可。 
			temp++;//这行的词汇个数（重复不算1个） 
		}
		ss >> trainLabels[Lines];
		//读取完这行词汇了 
		vector <int> Temp_Vec;
		for(it2 = repeatTimes.begin();it2!=repeatTimes.end();it2++)  //为了在vector中有序，借用这个map 
		{
			Three_Var item{Lines,it2->first};//利用机构体记录这个单词出现的行数，下标，重复次数 
			smat.push_back(item);
			ThreeVarNums++;//结构体vector中放入的个数 
			Temp_Vec.push_back(it2->first);//这个结构存储每一行拥有的字符串的下标；
		}
		NumsPerLines.push_back(Temp_Vec);
		Lines++;  //第几行计数 
		NumsOfLines.push_back(temp);//记录好每行的词汇个数 
		if(Lines == TRAIN_LINES){
			first = true;
			Input.close();
			Input.open("test.txt");
		}
	}
	Input.close();
}
ofstream OneHot,SMATRIX1;

void process()
{
		//接下来进行处理数据 
	sort(smat.begin(),smat.end(),Sort);
	
	OneHot.open("OneHot.txt");
	SMATRIX1.open("smatrix1.txt"); //三元组矩阵 
	SMATRIX1<<Lines<<endl<<index<<endl<<ThreeVarNums<<endl;
	int pos=0;
	int RightNums = 0;
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
		if(i >= TRAIN_LINES){//test.txt来分类咯； 
			int MinLine = 0, MinDis = 999999; 
			for(int r = 0; r < TRAIN_LINES; r++){ //与训练文本的每一行求欧式距离
			if(NumsPerLines[r].size() > 3)
			{
				int dis = 0, c = 0 , k = 0 , equals = 0; 
				for(; c < NumsPerLines[i].size() ; c++){ //当前行的字符串 
					for(; k < NumsPerLines[r].size(); k++){
						if(NumsPerLines[i][c] <  NumsPerLines[r][k]){
							break;
						}
						else if(NumsPerLines[i][c] ==  NumsPerLines[r][k]){
							equals++;
						}
					}
				}
				dis = NumsPerLines[i].size() + NumsPerLines[r].size() - equals * 2;
				if(dis < MinDis){
					MinDis = dis;
					MinLine = r;
				}
			}
			}
			OneHot<<"min line = "<<MinLine<<"; MinDis = "<<MinDis<<"; emotion = "<<Emo[MinLine]<<"; ";
			if(Emo[MinLine] == Emo[i]) RightNums++;
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
	cout<<"File operation has done!"<<endl;
	cout<<"The right rate is "<<(double)(RightNums)/1000<<endl;
} 
int main()
{
	readData();
	cout<<Lines<<" "<<index<<endl;
	cout<<"有二元组个数"<<ThreeVarNums<<endl;

	cout<<"Input operation has done!"<<endl;
	//读取完整个文档 
	process();
	/*---------------完成操作，关闭文件输出流 ---------------*/ 
	OneHot.close();
	SMATRIX1.close();
	Info.close();
	return 0;
}
