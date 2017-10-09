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
	Input.open("semeval.txt");//��ȡ�ļ� 
	string line;	//һ����ʱ�������� 
	map<string, int> findIndex;//string�Ƕ�Ӧ�Ĵʻ㣬int�����������ظ��£���һ�γ��ֵ��ڸ�map�е��±� 
	map<int, int> repeatTimes,appearTimes;	//default key ascending in map
	vector<int> numsPerLine;//ÿ�еĴʻ���� ���ظ�����1����
	vector<info> smat;
	int index=0;//���γ��ֵģ�ȥ�أ��ʻ�Ķ�Ӧ�±� 
	int nums=0;//���ֵ����� 
	int total=0;// 
	while(getline(Input,line))
	{		
		stringstream ss;
		int tmp;
		//��������ע�⵽һ����ʵ����д�ְ����dev_cpp��ʱ��������ؿ�����һ��һ�仰�ģ�������stringstream
		//���ж�������Ի᷽��ܶ� 
		ss.clear(); 
		ss.str(line);//From:http://blog.csdn.net/lanbing510/article/details/42423333
					//str()��Ա������ʹ�ÿ�����istringstream���󷵻�һ��string�ַ��� 
		ss>>tmp;    //����һ��������Ҳ����ÿ�е���� 
		string words; 
		for(int i=0;i<ExpreTimes;i++)//��Ϊ��all��anger��disgust��fear��joy��sad��surprise�������ѭ��7�� 
			ss>>words;	
		tmp=0;
		map<string,int>::iterator it;
		map<int,int>::iterator it2;
		map<int,int>::iterator it3;
		repeatTimes.clear();
		while(ss>>words)  //����ÿ�е����ݼ����ݵĴʻ� 
		{
			it=findIndex.find(words); //firstԪ�ص�map���Һ��� 
			if(it==findIndex.end())//����������end()��˵������ʻ�û���ֹ� 
			{
				findIndex.insert(pair<string,int>(words,index));
				index++;  //ά��map�е��±� 
			}
			it2=repeatTimes.find(findIndex[words]);//����ôʻ������ݼ����ظ����ֵĴ��� 
			if(it2==repeatTimes.end())//����±��һ�γ��ֵĻ����Ž����repaeatTimes<int,int>�� 
				repeatTimes.insert(pair<int,int>(findIndex[words],1));
				//��һ��������¼����map�е��±꣬�ڶ���������¼���ظ��Ĵ��� 
			else
				it2->second++;//����ά�������RepeatTimes���ɡ� 
			tmp++;//���еĴʻ�������ظ�����1���� 
		}
		//��ȡ�����дʻ��� 
		
		for(it2=repeatTimes.begin();it2!=repeatTimes.end();it2++)
		{
			it3=appearTimes.find(it2->first);//ÿ���ʻ��Ӧ���±��ظ��Ĵ��� 
			//�������������ݼ��г��ֵĴ��� 
			if(it3==appearTimes.end()) //����ǿյģ�˵����һ�γ��� 
				appearTimes.insert(pair<int,int>(it2->first,1));
			else
				it3->second++;
			//add a new item in ordering list 
			info item{nums,it2->first,it2->second};//���û������¼������ʳ��ֵ��������±꣬�ظ����� 
			smat.push_back(item);
			total++;//�ṹ��vector�з���ĸ��� 
		}
		nums++;  //�ڼ��м��� 
		numsPerLine.push_back(tmp);//��¼��ÿ�еĴʻ���� 
	}
	Input.close();
	//��ȡ�������ĵ� 
	
	//���������д������� 
	ofstream ans[10];//ԭ������������������ 
	ans[0].open("OneHot.txt");
	ans[1].open("TF.txt");
	ans[2].open("TFIDF.txt");
	ans[3].open("smatrix1.txt"); //��Ԫ����� 
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
	for(int i=0;i<nums;i++) //���� 
	{
		for(int j=0;j<index;j++) //�±� 
		{
			if(smat[pos].x==i&&smat[pos].y==j)  //ƥ�䵽һ���ַ������� 
			{
				ans[0]<<1<<" ";      //OneHot����Ϊ1 
				double rate=(double)smat[pos].v/numsPerLine[i];  //��һ��Ƶ�� 
				ans[1]<<rate<<" "; 
				ans[2]<<rate*log((double)nums/(1+appearTimes[j]))<<" "; //TF-IDF���� 
				ans[3]<<i<<" "<<j<<" "<<1<<endl;	//�������Ԫ�� 
				if(smat[pos].x>=nums/2)
					smat[pos].x-=nums/2;
				pos++;//����һ���ַ����� 
			}
			else
			{
				for(int k=0;k<3;k++)  //3���ĵ�����0 
					ans[k]<<0<<" ";
			}
		}
		for(int k=0;k<3;k++)  //ÿһ�ж����п� 
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
	
	//��ɲ������ر��ļ������ 
	for(int i=0;i<5;i++) //��Ϊ��OneHot,TF,TFIDF,smatrix,A+B��5���ļ� 
		ans[i].close();
	return 0;
}
