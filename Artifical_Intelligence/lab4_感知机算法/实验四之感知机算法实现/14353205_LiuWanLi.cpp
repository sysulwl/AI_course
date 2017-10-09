#include<iostream>
#include<fstream>
#include<map>
#include<vector> 
#include<sstream>
#include<cmath>
using namespace std;
struct Three_Var
{
	int i,j,v;
	bool operator<(Three_Var& t) {return i<t.i||(i==t.i&&j<t.i);}
	bool operator==(Three_Var& t) {return i==t.i&&j==t.j;}
};
int main()
{
	int index=0;//依次出现的（去重）词汇的对应下标 
	int Lines=0;//出现的行数 
	int ThreeVarNums=0;//三元组的个数 
	ifstream Input;
	Input.open("semeval");//读取文件 
	string line;	//一个临时变量而已 
	map<string, int> FirstIndex;//string是对应的词汇，int是它（无视重复下）第一次出现的在该map中的下标 
	map<int, int> RepeatTimes,AppearLines;	//default key ascending in map
	vector<int> NumsOfLines;//每行的词汇个数 （重复不算1个）
	vector<Three_Var> smat;
	while(getline(Input,line))
	{		
		stringstream ss;
		int temp;
		//几经周折注意到一个事实：用写字板或者dev_cpp打开时可以清楚地看见是一行一句话的，所以用stringstream
		//整行读入的特性会方便很多 
		ss.clear(); 
		ss.str(line);//From:http://blog.csdn.net/lanbing510/article/details/42423333
					//str()成员函数的使用可以让istringstream对象返回一个string字符串 
		ss>>temp;    //读入一个整数，也就是每行的序号 
		string dict; 
		for(int i=0;i<7;i++)//因为有all，anger，disgust，fear，joy，sad，surprise七项，所以循环7次 
			ss>>dict;	
		temp=0;
		map<string,int>::iterator it1;
		map<int,int>::iterator it2;
		map<int,int>::iterator it3;
		RepeatTimes.clear();
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
				it2->second++;//否则，维护好这个RepeatTimes即可。 
			temp++;//这行的词汇个数（重复不算1个） 
		}
		//读取完这行词汇了 
		
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
		Lines++;  //第几行计数 
		NumsOfLines.push_back(temp);//记录好每行的词汇个数 
	}
	Input.close();
	//读取完整个文档 
	
	//接下来进行处理数据 
	ofstream OneHot,TF,TF_IDF,SMATRIX1;
	OneHot.open("OneHot");
	TF.open("TF");
	TF_IDF.open("TFIDF");
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
				TF_IDF<<rate*log((double)Lines/(1+AppearLines[j]))<<" "; //TF-IDF矩阵 
				SMATRIX1<<i<<" "<<j<<" "<<1<<endl;	//输出到三元组 
				if(smat[pos].i>=Lines/2)
					smat[pos].i-=Lines/2;
				pos++;//找下一个字符串了 
			}
			else
			{
				OneHot<<0<<" ";       //不出现，这3个矩阵都是0，三元组则例外 
				TF<<0<<" ";
				TF_IDF<<0<<" ";
			}
			/*----————————--处理完一行了----——---*/ 
		}
		OneHot<<endl;       //每一句新闻后都换行咯
		TF<<endl;
		TF_IDF<<endl;
	}	
	
	//完成操作，关闭文件输出流 
	OneHot.close();
	TF.close();
	TF_IDF.close();
	SMATRIX1.close();
	return 0;
}
