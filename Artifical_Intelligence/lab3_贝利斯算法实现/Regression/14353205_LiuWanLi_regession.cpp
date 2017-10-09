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
//1.������������һ�����ļ������⣬������ô��ȡ��һ���ַ���������һ�����̶����ַ���֮�� ����6������ 
struct Three_Var
{
	int i,j,v;
	bool operator<(Three_Var& t) {return i<t.i||(i==t.i&&j<t.j);}
	bool operator==(Three_Var& t) {return i==t.i&&j==t.j;}
};
vector< vector<int> > NumsPerLines; 
int index=0;//���γ��ֵģ�ȥ�أ��ʻ�Ķ�Ӧ�±� 
int Lines=0;//���ֵ����� 
int ThreeVarNums=0;//��Ԫ��ĸ��� 
string line;	//һ����ʱ�������� 
map<string, int> FirstIndex;//string�Ƕ�Ӧ�Ĵʻ㣬int�����������ظ��£���һ�γ��ֵ��ڸ�map�е��±�
map<int,int> repeatTimes,AppearLines; 
vector<Three_Var> smat;
vector<int> Emo;
bool first = true;//��Ϊѵ���ı���һ��û�ã�
int temp = 0;
map<string,int>::iterator it1;
map<int,int>::iterator it2;
map<int,int>::iterator it3;
vector<int> NumsOfLines;//ÿ�еĴʻ���� ���ظ�����1����
void Do(string dict)
{
	it1=FirstIndex.find(dict); //firstԪ�ص�map���Һ��� 
	if(it1==FirstIndex.end())//����������end()��˵������ʻ�û���ֹ� 
	{
		FirstIndex.insert(pair<string,int>(dict,index));
		index++;  //ά��map�е��±� 
	}
	
	it2=repeatTimes.find(FirstIndex[dict]);
	if(it2==repeatTimes.end())//����±��һ�γ��ֵĻ����Ž����repaeatTimes<int,int>�� 
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
	Input.open("Dataset_train.txt");//��ȡ�ļ� 
	while(getline(Input,line))
	{		
		if(first) {first = false;continue;} 
		stringstream ss;
		temp = 0;
		ss.clear(); 
		ss.str(line);
		string dict; 
		ss >> dict ; //����train_���û�õĵ��� 
		repeatTimes.clear();
		dict = dict.substr(dict.find(",")+1,dict.size());
		Info <<dict<<" ";
		Do(dict);
		int P_OF_EMO = 0;
		while(ss>>dict)  //����ÿ�е����ݼ����ݵĴʻ� 
		{
			if(dict.find(",") <= dict.size()) //�����һ���ַ��� 
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
					P[Lines][i+1] = doub;  //�õ�ÿ���ĵ�ÿ�ָ���ĸ��ʾ��� 
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
		//��ȡ�����дʻ��� 
		for(it2=repeatTimes.begin();it2!=repeatTimes.end();it2++)
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
	ofstream OneHot,TF,TF_IDF,SMATRIX1;
	OneHot.open("OneHot");
	TF.open("TF");
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
				tf[i][j] = rate;  
				SMATRIX1<<i<<" "<<j<<" "<<1<<endl;	//�������Ԫ�� 
				if(smat[pos].i>=Lines/2)
					smat[pos].i-=Lines/2;
				pos++;//����һ���ַ����� 
			}
			else
			{
				OneHot<<0<<" ";       //�����֣���3��������0����Ԫ�������� 
				TF<<0<<" ";
				tf[i][j] = 0;
			}
			/*----����������������--������һ����----����---*/ 
		}
		OneHot<<endl;       //ÿһ�����ź󶼻��п�
		TF<<endl;
	}	
	/*---------------��ɲ������ر��ļ������ ---------------*/ 
	OneHot.close();
	TF.close();
	SMATRIX1.close();
	Info.close();
	printf("��%d���ַ���\n",index); 
	
	/*----------��ȡ�����ĵ�-------------------*/ 
	ofstream output;
	output.open("myResult.txt");
	Input.open("Dataset_validation.txt");//��ȡ�ļ� 
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
		ss >> dict ; //����train_���û�õĵ��� 
		dict = dict.substr(dict.find(",")+1,dict.size());
		thisLine.push_back(dict);	
	
		while(ss>>dict)  //����ÿ�е����ݼ����ݵĴʻ� 
		{
			if(dict.find(",") <= dict.size()) //�����һ���ַ��� 
			{
				string T = dict.substr(0,dict.find(",")); //��ȡ�ʻ� 
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
		for(int j = 1; j <= 6; j++)  //���� 
		{
			for(int i = 0 ; i < TRAINLINES; i++) //ѵ������ 
			{
				double k = 1.0;
				double sum_xk = 0;
				for(int x = 0 ; x < thisLine.size() ;x++)
				{
					sum_xk += tf[i][ FirstIndex.find(thisLine[x]) -> second];
				}
				for(int x = 0 ; x < thisLine.size() ;x++)//���еĴʻ����
				{
					//��������������˹ƽ�� 
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
		//��һ����������ĵ���
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
