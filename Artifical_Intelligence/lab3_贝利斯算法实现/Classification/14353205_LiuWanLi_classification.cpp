#include<iostream>
#include<fstream>
#include<map>
#include<vector> 
#include<sstream>
#include<cmath>
#include<assert.h>
using namespace std;
#define TRAINLINES 246
#define TESTLINES 1000
struct Three_Var
{
	int i,j,v;
	bool operator<(Three_Var& t) {return i<t.i||(i==t.i&&j<t.i);}
	bool operator==(Three_Var& t) {return i==t.i&&j==t.j;}
};
int dictsOfEmotion_Repeat[7] = {0}; //从1到6 
int dictsOfEmotion_NoRepeat[7] = {0};
int index=0;//依次出现的（去重）词汇的对应下标 
int Lines=0;//出现的行数 
int ThreeVarNums=0;//三元组的个数 	
string line;	//一个临时变量而已 
map<string, int> FirstIndex;//string是对应的词汇，int是它（无视重复下）第一次出现的在该map中的下标 
map<int, int> RepeatTimes,AppearLines;	//default key ascending in map
vector<int> NumsOfLines;//每行的词汇个数 （重复不算1个）
vector<Three_Var> smat;
bool first = true;
map<string,int>  EMO1; 
map<string,int>  EMO2; 
map<string,int>  EMO3; 
map<string,int>  EMO4; 
map<string,int>  EMO5; 
map<string,int>  EMO6; //每种感情下每个词汇对应的出现次数
map<string,int>::iterator it1;
map<int,int>::iterator it2;
map<int,int>::iterator it3;
vector<map<string,int> > DictsEmos;
int emo_times[7]={0};//从1到6 
void Cal_Dicts_Emos(int emo,string dict)
{
	switch (emo)
	{
			case 1:
			it1 = EMO1.find(dict);
			if(it1==FirstIndex.end())//迭代器到了end()，说明这个词在这种感情还没出现过 
			{
			     FirstIndex.insert(pair<string,int>(dict,1));
			     dictsOfEmotion_NoRepeat[1]++; //护好dictsOfEmotion_NoRepeat[7]，来做拉普拉斯平滑-
			}
			else 
				it1->second++; 
			break;
			
			case 2:
			it1 = EMO2.find(dict);
			if(it1==FirstIndex.end())//迭代器到了end()，说明这个词在这种感情还没出现过
			{
				FirstIndex.insert(pair<string,int>(dict,1));
				dictsOfEmotion_NoRepeat[2]++;
			} 	
			else 
				it1->second++; 
			break;
				
			case 3:
			it1 = EMO3.find(dict);
			if(it1==FirstIndex.end())//迭代器到了end()，说明这个词在这种感情还没出现过 
			{
			    FirstIndex.insert(pair<string,int>(dict,1));
			    dictsOfEmotion_NoRepeat[3]++;
			}	
			else 
				it1->second++; 
			break;	
			
			case 4:
			it1 = EMO4.find(dict);
			if(it1==FirstIndex.end())//迭代器到了end()，说明这个词在这种感情还没出现过 
			{
				FirstIndex.insert(pair<string,int>(dict,1));
				dictsOfEmotion_NoRepeat[4]++;
			}	
			else 
				it1->second++; 
			break;
			
			case 5:
			it1 = EMO5.find(dict);
			if(it1==FirstIndex.end())//迭代器到了end()，说明这个词在这种感情还没出现过 
			{
				FirstIndex.insert(pair<string,int>(dict,1));
				dictsOfEmotion_NoRepeat[5]++;
			}	
			else 
				it1->second++; 
			break;
			
			case 6:
			it1 = EMO6.find(dict);
			if(it1==FirstIndex.end())//迭代器到了end()，说明这个词在这种感情还没出现过 
			{
				FirstIndex.insert(pair<string,int>(dict,1));
				dictsOfEmotion_NoRepeat[6]++;
			}
			else 
				it1->second++; 
			break;
	}
}
void Input_Finish()
{
	DictsEmos.push_back(EMO1);
	DictsEmos.push_back(EMO2);
	DictsEmos.push_back(EMO3);
	DictsEmos.push_back(EMO4);
	DictsEmos.push_back(EMO5);
	DictsEmos.push_back(EMO6);
}
int main()
{
	ifstream Input;
	Input.open("train.txt");
	
	while(getline(Input,line))
	{		
		if(first) {
			first = false;
			continue;
		}
		stringstream ss;
		int numbersOfLines;
		//几经周折注意到一个事实：用写字板或者dev_cpp打开时可以清楚地看见是一行一句话的，所以用stringstream
		//整行读入的特性会方便很多 
		ss.clear(); 
		ss.str(line);//From:http://blog.csdn.net/lanbing510/article/details/42423333
					//str()成员函数的使用可以让istringstream对象返回一个string字符串 
		ss>>numbersOfLines;    //读入一个整数，也就是每行的序号 
		int emo;//emotion 
		ss>>emo;
		emo_times[emo]++; 
		numbersOfLines=0;
		RepeatTimes.clear();   //每次都清空 
		string dict;
		while(ss>>dict)  //读入每行的数据集内容的词汇 
		{
			it1=FirstIndex.find(dict); //first元素的map查找函数 
			if(it1==FirstIndex.end())//迭代器到了end()，说明这个词还没出现过 
			{
				FirstIndex.insert(pair<string,int>(dict,index));
				index++;  //维护map中的下标 
			}
			it2=RepeatTimes.find(FirstIndex[dict]);//计算该词汇在数据集中重复出现的次数 
			if(it2==RepeatTimes.end())//这个下标第一次出现的话，放进这个repaeatTimes<int,int>中 
				RepeatTimes.insert(pair<int,int>(FirstIndex[dict],1));
				//第一个整数记录它在map中的下标，第二个整数记录它重复的次数 
			else
				it2->second++;//否则，维护好这个RepeatTimes即可，这里是它在这句话的重复次数 
			numbersOfLines++;//这行的词汇个数（重复不算1个） 
			Cal_Dicts_Emos(emo,dict);
			
			/*-------------维护好dictsOfEmotion_NoRepeat[7]，来做拉普拉斯平滑------*/
			
			/*-------------------------------*/ 
		}
		//读取完这行词汇了 
		Lines++;  //第几行计数 
		NumsOfLines.push_back(numbersOfLines);//记录好每行的词汇个数 
		dictsOfEmotion_Repeat[emo] +=  numbersOfLines;//维护好每种感情的词汇个数 
		
		for(it2=RepeatTimes.begin();it2!=RepeatTimes.end();it2++)
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
		
	}
	Input.close();
	Input_Finish();
	//读取完整个文档 
	
	
	//接下来进行处理数据 
	ofstream OneHot,SMATRIX1;
	OneHot.open("OneHot");
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
				OneHot<<smat[pos].v<<" ";      //OneHot矩阵为1 
				SMATRIX1<<i<<" "<<j<<" "<<1<<endl;	//输出到三元组 
				if(smat[pos].i>=Lines/2)
					smat[pos].i-=Lines/2;
				pos++;//找下一个字符串了 
			}
			else
			{
				OneHot<<0<<" ";       //不出现，这3个矩阵都是0，三元组则例外 
			}
			/*----————————--处理完一行了----——---*/ 
		}
		OneHot<<endl;       //每一句新闻后都换行咯
	}	
	
	//完成操作，关闭文件输出流 
	OneHot.close();
	SMATRIX1.close();

	//现在读取测试集并进行分类
	Input.open("test.txt");
	first = true;
	int rightTimes = 0;
	line = ""; 
	while(getline(Input,line))
	{		
		if(first) {
			first = false;
			continue;
		}
			
		stringstream ss;
		int numbersOfLines;
		ss.clear(); 
		ss.str(line);
		ss>>numbersOfLines;    //读入一个整数，也就是每行的序号 
		int emo;//emotion 
		ss>>emo;
		numbersOfLines=0;
		double pro[7] ; //6种情绪的概率 
		for(int i = 1; i <= 6; i++) pro[i] = 1;
		string dict;
		while(ss>>dict)  //读入每行的数据集内容的词汇 
		{
			for(int i = 1 ; i <= 6; i++)
			{
				//计算每种情绪下这个单词的概率乘积因子，并且在这里进行拉普拉斯平滑 
				it1 = DictsEmos[i - 1].find(dict);
				if(it1 == DictsEmos[i - 1].end())
					pro[i] *= (1.0/(dictsOfEmotion_Repeat[i] + dictsOfEmotion_NoRepeat[i]));
				else
					pro[i] *= ( 1.0 * it2->second / dictsOfEmotion_Repeat[i]) ;
			}
		}
		double max = 0;
		int ans;
		for(int i = 1 ; i <= 6; i++)
		{	
			pro[i] *= (1.0 * emo_times[i] / TRAINLINES);
			//cout<<pro[i]<<endl; 
			if(pro[i] > max)
			{
				max = pro[i];
				ans = i;
			}
		}
		cout<<ans<<endl;
		if(ans == emo) rightTimes++;
	}
	double rate = 1.0 * rightTimes / TESTLINES;
	printf("分类正确率为%f\n",rate);
	return 0;
}
