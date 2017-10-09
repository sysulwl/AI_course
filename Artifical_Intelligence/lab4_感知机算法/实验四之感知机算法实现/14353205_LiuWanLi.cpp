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
	int index=0;//���γ��ֵģ�ȥ�أ��ʻ�Ķ�Ӧ�±� 
	int Lines=0;//���ֵ����� 
	int ThreeVarNums=0;//��Ԫ��ĸ��� 
	ifstream Input;
	Input.open("semeval");//��ȡ�ļ� 
	string line;	//һ����ʱ�������� 
	map<string, int> FirstIndex;//string�Ƕ�Ӧ�Ĵʻ㣬int�����������ظ��£���һ�γ��ֵ��ڸ�map�е��±� 
	map<int, int> RepeatTimes,AppearLines;	//default key ascending in map
	vector<int> NumsOfLines;//ÿ�еĴʻ���� ���ظ�����1����
	vector<Three_Var> smat;
	while(getline(Input,line))
	{		
		stringstream ss;
		int temp;
		//��������ע�⵽һ����ʵ����д�ְ����dev_cpp��ʱ��������ؿ�����һ��һ�仰�ģ�������stringstream
		//���ж�������Ի᷽��ܶ� 
		ss.clear(); 
		ss.str(line);//From:http://blog.csdn.net/lanbing510/article/details/42423333
					//str()��Ա������ʹ�ÿ�����istringstream���󷵻�һ��string�ַ��� 
		ss>>temp;    //����һ��������Ҳ����ÿ�е���� 
		string dict; 
		for(int i=0;i<7;i++)//��Ϊ��all��anger��disgust��fear��joy��sad��surprise�������ѭ��7�� 
			ss>>dict;	
		temp=0;
		map<string,int>::iterator it1;
		map<int,int>::iterator it2;
		map<int,int>::iterator it3;
		RepeatTimes.clear();
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
				it2->second++;//����ά�������RepeatTimes���ɡ� 
			temp++;//���еĴʻ�������ظ�����1���� 
		}
		//��ȡ�����дʻ��� 
		
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
		Lines++;  //�ڼ��м��� 
		NumsOfLines.push_back(temp);//��¼��ÿ�еĴʻ���� 
	}
	Input.close();
	//��ȡ�������ĵ� 
	
	//���������д������� 
	ofstream OneHot,TF,TF_IDF,SMATRIX1;
	OneHot.open("OneHot");
	TF.open("TF");
	TF_IDF.open("TFIDF");
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
				OneHot<<1<<" ";      //OneHot����Ϊ1 
				double rate=(double)smat[pos].v/NumsOfLines[i];  //��һ��Ƶ�� 
				TF<<rate<<" "; 
				TF_IDF<<rate*log((double)Lines/(1+AppearLines[j]))<<" "; //TF-IDF���� 
				SMATRIX1<<i<<" "<<j<<" "<<1<<endl;	//�������Ԫ�� 
				if(smat[pos].i>=Lines/2)
					smat[pos].i-=Lines/2;
				pos++;//����һ���ַ����� 
			}
			else
			{
				OneHot<<0<<" ";       //�����֣���3��������0����Ԫ�������� 
				TF<<0<<" ";
				TF_IDF<<0<<" ";
			}
			/*----����������������--������һ����----����---*/ 
		}
		OneHot<<endl;       //ÿһ�����ź󶼻��п�
		TF<<endl;
		TF_IDF<<endl;
	}	
	
	//��ɲ������ر��ļ������ 
	OneHot.close();
	TF.close();
	TF_IDF.close();
	SMATRIX1.close();
	return 0;
}
