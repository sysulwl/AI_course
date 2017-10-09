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
int dictsOfEmotion_Repeat[7] = {0}; //��1��6 
int dictsOfEmotion_NoRepeat[7] = {0};
int index=0;//���γ��ֵģ�ȥ�أ��ʻ�Ķ�Ӧ�±� 
int Lines=0;//���ֵ����� 
int ThreeVarNums=0;//��Ԫ��ĸ��� 	
string line;	//һ����ʱ�������� 
map<string, int> FirstIndex;//string�Ƕ�Ӧ�Ĵʻ㣬int�����������ظ��£���һ�γ��ֵ��ڸ�map�е��±� 
map<int, int> RepeatTimes,AppearLines;	//default key ascending in map
vector<int> NumsOfLines;//ÿ�еĴʻ���� ���ظ�����1����
vector<Three_Var> smat;
bool first = true;
map<string,int>  EMO1; 
map<string,int>  EMO2; 
map<string,int>  EMO3; 
map<string,int>  EMO4; 
map<string,int>  EMO5; 
map<string,int>  EMO6; //ÿ�ָ�����ÿ���ʻ��Ӧ�ĳ��ִ���
map<string,int>::iterator it1;
map<int,int>::iterator it2;
map<int,int>::iterator it3;
vector<map<string,int> > DictsEmos;
int emo_times[7]={0};//��1��6 
void Cal_Dicts_Emos(int emo,string dict)
{
	switch (emo)
	{
			case 1:
			it1 = EMO1.find(dict);
			if(it1==FirstIndex.end())//����������end()��˵������������ָ��黹û���ֹ� 
			{
			     FirstIndex.insert(pair<string,int>(dict,1));
			     dictsOfEmotion_NoRepeat[1]++; //����dictsOfEmotion_NoRepeat[7]������������˹ƽ��-
			}
			else 
				it1->second++; 
			break;
			
			case 2:
			it1 = EMO2.find(dict);
			if(it1==FirstIndex.end())//����������end()��˵������������ָ��黹û���ֹ�
			{
				FirstIndex.insert(pair<string,int>(dict,1));
				dictsOfEmotion_NoRepeat[2]++;
			} 	
			else 
				it1->second++; 
			break;
				
			case 3:
			it1 = EMO3.find(dict);
			if(it1==FirstIndex.end())//����������end()��˵������������ָ��黹û���ֹ� 
			{
			    FirstIndex.insert(pair<string,int>(dict,1));
			    dictsOfEmotion_NoRepeat[3]++;
			}	
			else 
				it1->second++; 
			break;	
			
			case 4:
			it1 = EMO4.find(dict);
			if(it1==FirstIndex.end())//����������end()��˵������������ָ��黹û���ֹ� 
			{
				FirstIndex.insert(pair<string,int>(dict,1));
				dictsOfEmotion_NoRepeat[4]++;
			}	
			else 
				it1->second++; 
			break;
			
			case 5:
			it1 = EMO5.find(dict);
			if(it1==FirstIndex.end())//����������end()��˵������������ָ��黹û���ֹ� 
			{
				FirstIndex.insert(pair<string,int>(dict,1));
				dictsOfEmotion_NoRepeat[5]++;
			}	
			else 
				it1->second++; 
			break;
			
			case 6:
			it1 = EMO6.find(dict);
			if(it1==FirstIndex.end())//����������end()��˵������������ָ��黹û���ֹ� 
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
		//��������ע�⵽һ����ʵ����д�ְ����dev_cpp��ʱ��������ؿ�����һ��һ�仰�ģ�������stringstream
		//���ж�������Ի᷽��ܶ� 
		ss.clear(); 
		ss.str(line);//From:http://blog.csdn.net/lanbing510/article/details/42423333
					//str()��Ա������ʹ�ÿ�����istringstream���󷵻�һ��string�ַ��� 
		ss>>numbersOfLines;    //����һ��������Ҳ����ÿ�е���� 
		int emo;//emotion 
		ss>>emo;
		emo_times[emo]++; 
		numbersOfLines=0;
		RepeatTimes.clear();   //ÿ�ζ���� 
		string dict;
		while(ss>>dict)  //����ÿ�е����ݼ����ݵĴʻ� 
		{
			it1=FirstIndex.find(dict); //firstԪ�ص�map���Һ��� 
			if(it1==FirstIndex.end())//����������end()��˵������ʻ�û���ֹ� 
			{
				FirstIndex.insert(pair<string,int>(dict,index));
				index++;  //ά��map�е��±� 
			}
			it2=RepeatTimes.find(FirstIndex[dict]);//����ôʻ������ݼ����ظ����ֵĴ��� 
			if(it2==RepeatTimes.end())//����±��һ�γ��ֵĻ����Ž����repaeatTimes<int,int>�� 
				RepeatTimes.insert(pair<int,int>(FirstIndex[dict],1));
				//��һ��������¼����map�е��±꣬�ڶ���������¼���ظ��Ĵ��� 
			else
				it2->second++;//����ά�������RepeatTimes���ɣ�������������仰���ظ����� 
			numbersOfLines++;//���еĴʻ�������ظ�����1���� 
			Cal_Dicts_Emos(emo,dict);
			
			/*-------------ά����dictsOfEmotion_NoRepeat[7]������������˹ƽ��------*/
			
			/*-------------------------------*/ 
		}
		//��ȡ�����дʻ��� 
		Lines++;  //�ڼ��м��� 
		NumsOfLines.push_back(numbersOfLines);//��¼��ÿ�еĴʻ���� 
		dictsOfEmotion_Repeat[emo] +=  numbersOfLines;//ά����ÿ�ָ���Ĵʻ���� 
		
		for(it2=RepeatTimes.begin();it2!=RepeatTimes.end();it2++)
		{
			it3=AppearLines.find(it2->first);//ÿ���ʻ��Ӧ���±��ظ��Ĵ��� 
			//�������������ݼ��г��ֵĴ��� 
			if(it3==AppearLines.end()) //����ǿյģ�˵����һ�γ��� 
				AppearLines.insert(pair<int,int>(it2->first,1));
			else
				it3->second++; //it3��second�洢���Ƕ�Ӧ�±���ַ������ֵ����� 
			Three_Var item{Lines,it2->first,it2->second};
			//���û������¼������ʳ��ֵ��������±꣬�ظ����� 
			smat.push_back(item);
			ThreeVarNums++;//�ṹ��vector�з���ĸ��� 
		}
		
	}
	Input.close();
	Input_Finish();
	//��ȡ�������ĵ� 
	
	
	//���������д������� 
	ofstream OneHot,SMATRIX1;
	OneHot.open("OneHot");
	SMATRIX1.open("smatrix1"); //��Ԫ����� 
	SMATRIX1<<Lines<<endl<<index<<endl<<ThreeVarNums<<endl;
	int pos=0;
	for(int i=0;i<Lines;i++) //���� 
	{
		/*����������������ÿһ�еĴ�����������������*/ 
		for(int j=0;j<index;j++) //�ַ����±� 
		{
			if(smat[pos].i==i&&smat[pos].j==j)  //ƥ�䵽һ���ַ������� 
			{
				OneHot<<smat[pos].v<<" ";      //OneHot����Ϊ1 
				SMATRIX1<<i<<" "<<j<<" "<<1<<endl;	//�������Ԫ�� 
				if(smat[pos].i>=Lines/2)
					smat[pos].i-=Lines/2;
				pos++;//����һ���ַ����� 
			}
			else
			{
				OneHot<<0<<" ";       //�����֣���3��������0����Ԫ�������� 
			}
			/*----����������������--������һ����----����---*/ 
		}
		OneHot<<endl;       //ÿһ�����ź󶼻��п�
	}	
	
	//��ɲ������ر��ļ������ 
	OneHot.close();
	SMATRIX1.close();

	//���ڶ�ȡ���Լ������з���
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
		ss>>numbersOfLines;    //����һ��������Ҳ����ÿ�е���� 
		int emo;//emotion 
		ss>>emo;
		numbersOfLines=0;
		double pro[7] ; //6�������ĸ��� 
		for(int i = 1; i <= 6; i++) pro[i] = 1;
		string dict;
		while(ss>>dict)  //����ÿ�е����ݼ����ݵĴʻ� 
		{
			for(int i = 1 ; i <= 6; i++)
			{
				//����ÿ��������������ʵĸ��ʳ˻����ӣ��������������������˹ƽ�� 
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
	printf("������ȷ��Ϊ%f\n",rate);
	return 0;
}
