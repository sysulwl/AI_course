#include<iostream>
#include<fstream>
#include<map>
#include<vector> 
#include<sstream>
#include<cmath>
const int ExpreTimes = 7;
using namespace std;
struct info{
	int x,y,v;
	bool operator<(const info& t) const{return x<t.x||(x==t.x&&y<t.y);}
	bool operator==(const info& t) const{return x==t.x&&y==t.y;}
};
int main(){
	ifstream Input;
	Input.open("semeval.txt");//读取文件 
	string line;	//一个临时变量而已 
	map<string, int> findIndex;//string是对应的词汇，int是它（无视重复下）第一次出现的在该map中的下标 
	map<int, int> repeatTimes,appearTimes;	//default key ascending in map
	vector<int> numsPerLine;//每行的词汇个数 （重复不算1个）
	vector<info> smat;
	int index=0;//依次出现的（去重）词汇的对应下标 
	int nums=0;//出现的行数 
	int total=0;// 
	while(getline(Input,line))
	{		
		stringstream ss;
		int tmp;
		//几经周折注意到一个事实：用写字板或者dev_cpp打开时可以清楚地看见是一行一句话的，所以用stringstream
		//整行读入的特性会方便很多 
		ss.clear(); 
		ss.str(line);//From:http://blog.csdn.net/lanbing510/article/details/42423333
					//str()成员函数的使用可以让istringstream对象返回一个string字符串 
		ss>>tmp;    //读入一个整数，也就是每行的序号 
		string words; 
		for(int i=0;i<ExpreTimes;i++)//因为有all，anger，disgust，fear，joy，sad，surprise七项，所以循环7次 
			ss>>words;	
		tmp=0;
		map<string,int>::iterator it;
		map<int,int>::iterator it2;
		map<int,int>::iterator it3;
		repeatTimes.clear();
		while(ss>>words)  //读入每行的数据集内容的词汇 
		{
			it=findIndex.find(words); //first元素的map查找函数 
			if(it==findIndex.end())//迭代器到了end()，说明这个词还没出现过 
			{
				findIndex.insert(pair<string,int>(words,index));
				index++;  //维护map中的下标 
			}
			it2=repeatTimes.find(findIndex[words]);//计算该词汇在数据集中重复出现的次数 
			if(it2==repeatTimes.end())//这个下标第一次出现的话，放进这个repaeatTimes<int,int>中 
				repeatTimes.insert(pair<int,int>(findIndex[words],1));
				//第一个整数记录它在map中的下标，第二个整数记录它重复的次数 
			else
				it2->second++;//否则，维护好这个RepeatTimes即可。 
			tmp++;//这行的词汇个数（重复不算1个） 
		}
		//读取完这行词汇了 
		
		for(it2=repeatTimes.begin();it2!=repeatTimes.end();it2++)
		{
			it3=appearTimes.find(it2->first);//每个词汇对应的下标重复的次数 
			//计算在所有数据集中出现的次数 
			if(it3==appearTimes.end()) //如果是空的，说明第一次出现 
				appearTimes.insert(pair<int,int>(it2->first,1));
			else
				it3->second++;
			//add a new item in ordering list 
			info item{nums,it2->first,it2->second};//利用机构体记录这个单词出现的行数，下标，重复次数 
			smat.push_back(item);
			total++;//结构体vector中放入的个数 
		}
		nums++;  //第几行计数 
		numsPerLine.push_back(tmp);//记录好每行的词汇个数 
	}
	Input.close();
	//读取完整个文档 
	
	//接下来进行处理数据 
	ofstream ans[10];//原来输出流可以用数组的 
	ans[0].open("OneHot.txt");
	ans[1].open("TF.txt");
	ans[2].open("TFIDF.txt");
	ans[3].open("smatrix1.txt"); //三元组矩阵 
	ans[4].open("AplusB1.txt");	//AplusB for one-hot
	ans[3]<<nums<<endl<<index<<endl<<total<<endl;
	int pos=0,fpos=0;
	for(int i=0;i<smat.size();i++ )
	{
		if(smat[i].x>=nums/2)
		{
			fpos=i;
			break;
		}
	}
	for(int i=0;i<nums;i++) //行数 
	{
		for(int j=0;j<index;j++) //下标 
		{
			if(smat[pos].x==i&&smat[pos].y==j)  //匹配到一个字符串出现 
			{
				ans[0]<<1<<" ";      //OneHot矩阵为1 
				double rate=(double)smat[pos].v/numsPerLine[i];  //归一化频率 
				ans[1]<<rate<<" "; 
				ans[2]<<rate*log((double)nums/(1+appearTimes[j]))<<" "; //TF-IDF矩阵 
				ans[3]<<i<<" "<<j<<" "<<1<<endl;	//输出到三元组 
				if(smat[pos].x>=nums/2)
					smat[pos].x-=nums/2;
				pos++;//找下一个字符串了 
			}
			else
			{
				for(int k=0;k<3;k++)  //3个文档都是0 
					ans[k]<<0<<" ";
			}
		}
		for(int k=0;k<3;k++)  //每一行都换行咯 
			ans[k]<<endl;
	}	
	vector<info> plusmat;
	int i=0,j=fpos,tx,ty,tv;
	while(i<fpos&&j<total)
	{
		if(smat[i]==smat[j])
		{
			//combine the same x-y position
			tx=smat[i].x;ty=smat[i].y;tv=2;	//if not one-hot, 2 replaced by smat[i].v+smat[j].v
			i++;j++;
		}
		else if(smat[i]<smat[j])
		{
			//smaller one comes first
			tx=smat[i].x;ty=smat[i].y;tv=1;	//if not one-hot, 1 replaced by smat[i].v
			i++;
		}
		else
		{
			tx=smat[j].x;ty=smat[j].y;tv=1;	//if not one-hot, 1 replaced by smat[j].v
			j++;
		}
		info item{tx,ty,tv};
		plusmat.push_back(item);
	}
	while(i<fpos)
	{
		tx=smat[i].x;ty=smat[i].y;tv=1;	//if not one-hot, 1 replaced by smat[i].v
		i++;
		info item{tx,ty,tv};
		plusmat.push_back(item);
	}
	while(j<total)
	{
		tx=smat[j].x;ty=smat[j].y;tv=1;	//if not one-hot, 1 replaced by smat[j].v
		j++;
		info item{tx,ty,tv};
		plusmat.push_back(item);
	}
	ans[4]<<nums/2<<endl<<index<<endl<<plusmat.size()<<endl;
	for(int i=0;i<plusmat.size();i++)
		ans[4]<<plusmat[i].x<<" "<<plusmat[i].y<<" "<<plusmat[i].v<<endl;
	
	//完成操作，关闭文件输出流 
	for(int i=0;i<5;i++) //因为有OneHot,TF,TFIDF,smatrix,A+B共5个文件 
		ans[i].close();
	return 0;
}
