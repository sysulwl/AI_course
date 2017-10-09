#include<iostream>
#include<bits/stdc++.h> 
using namespace std;
//���� TRAIN_LINES ��ѵ������ 
#define TRAIN_LINES 30162 
int tarinLabels[35000] = {0};
struct Three_Var
{
	int i,j;
	bool operator<(Three_Var& t) {return i<t.i||(i==t.i&&j<t.j);}
	bool operator>(Three_Var& t) {return i>t.i||(i==t.i&&j>t.j);}
	bool operator==(Three_Var& t) {return i==t.i&&j==t.j;}
};
bool Sort( Three_Var d1,Three_Var d2)//�����ıȽϺ���  
{    
    return d1 < d2;//��������     
}   
vector< vector<int> > NumsPerLines; 
int index=0;//���γ��ֵģ�ȥ�أ��ʻ�Ķ�Ӧ�±� 
int Lines = 1;//���ֵ����� 
int ThreeVarNums=0;//��Ԫ��ĸ��� 
ifstream Input;
string line;	//һ����ʱ�������� 
map<string, int> FirstIndex;//string�Ƕ�Ӧ�Ĵʻ㣬int�����������ظ��£���һ�γ��ֵ��ڸ�map�е��±�
map<int,int> repeatTimes; 
vector<int> NumsOfLines;//ÿ�еĴʻ���� ���ظ�����1����
vector<Three_Var> smat;
vector<int> Emo;
bool first = true;//��Ϊѵ���ı���һ��û�ã�
ofstream Info;

void readData()
{
	Input.open("knn_train_data.txt");//��ȡ�ļ�
	Info.open("EveryLine.txt");
	while(getline(Input,line))
	{		
		if(first) {
			first = false;
			continue;
		} 
		stringstream ss;
		//��������ע�⵽һ����ʵ����д�ְ����dev_cpp��ʱ��������ؿ�����һ��һ�仰�ģ�������stringstream
		//���ж�������Ի᷽��ܶ� 
		ss.clear(); 
		ss.str(line);
		string EXM;
		string dict;  
		map<string,int>::iterator it1;
		map<int,int>::iterator it2;
		repeatTimes.clear();
		for(int fuck = 1; fuck <= 8 ; fuck++) //����ÿ�е����ݼ����ݵĴʻ� 
		{
			ss>>dict
			it1=FirstIndex.find(dict); //firstԪ�ص�map���Һ��� 
			if(it1==FirstIndex.end())//����������end()��˵������ʻ�û���ֹ� 
			{
				FirstIndex.insert(pair<string,int>(dict,index));
				index++;  //ά��map�е��±� 
			}
			it2=repeatTimes.find(FirstIndex[dict]);//����ôʻ������ݼ����ظ����ֵĴ��� 
			if(it2==repeatTimes.end())//����±��һ�γ��ֵĻ����Ž����repaeatTimes<int,int>�� 
			{
				Info << dict<<" ";
				repeatTimes.insert(pair<int,int>(FirstIndex[dict],1));
				//��һ��������¼����map�е��±꣬�ڶ���������¼���ظ��Ĵ��� 
			}
				
			else
				it2->second++;//����ά�������RepeatTimes���ɡ� 
			temp++;//���еĴʻ�������ظ�����1���� 
		}
		ss >> trainLabels[Lines];
		//��ȡ�����дʻ��� 
		vector <int> Temp_Vec;
		for(it2 = repeatTimes.begin();it2!=repeatTimes.end();it2++)  //Ϊ����vector�����򣬽������map 
		{
			Three_Var item{Lines,it2->first};//���û������¼������ʳ��ֵ��������±꣬�ظ����� 
			smat.push_back(item);
			ThreeVarNums++;//�ṹ��vector�з���ĸ��� 
			Temp_Vec.push_back(it2->first);//����ṹ�洢ÿһ��ӵ�е��ַ������±ꣻ
		}
		NumsPerLines.push_back(Temp_Vec);
		Lines++;  //�ڼ��м��� 
		NumsOfLines.push_back(temp);//��¼��ÿ�еĴʻ���� 
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
		//���������д������� 
	sort(smat.begin(),smat.end(),Sort);
	
	OneHot.open("OneHot.txt");
	SMATRIX1.open("smatrix1.txt"); //��Ԫ����� 
	SMATRIX1<<Lines<<endl<<index<<endl<<ThreeVarNums<<endl;
	int pos=0;
	int RightNums = 0;
	for(int i = 0;i<Lines;i++) //���� 
	{
		/*����������������ÿһ�еĴ�����������������*/ 
		for(int j = 0;j < index; j++) //�ַ����±� 
		{
			if(smat[pos].i==i && smat[pos].j==j)  //ƥ�䵽һ���ַ������� 
			{
				OneHot<<1<<" ";      //OneHot����Ϊ1  
				SMATRIX1<<i<<" "<<j<<" "<<1<<endl;	//�������Ԫ�� 
				pos++;//����һ���ַ����� 
			}
			else
			{
				OneHot<<0<<" ";       //�����֣���3��������0����Ԫ�������� 
			}
			/*----����������������--������һ����----����---*/ 
		}
		if(i >= TRAIN_LINES){//test.txt�����࿩�� 
			int MinLine = 0, MinDis = 999999; 
			for(int r = 0; r < TRAIN_LINES; r++){ //��ѵ���ı���ÿһ����ŷʽ����
			if(NumsPerLines[r].size() > 3)
			{
				int dis = 0, c = 0 , k = 0 , equals = 0; 
				for(; c < NumsPerLines[i].size() ; c++){ //��ǰ�е��ַ��� 
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
		OneHot<<endl;       //ÿһ�����ź󶼻��п�
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
	cout<<"�ж�Ԫ�����"<<ThreeVarNums<<endl;

	cout<<"Input operation has done!"<<endl;
	//��ȡ�������ĵ� 
	process();
	/*---------------��ɲ������ر��ļ������ ---------------*/ 
	OneHot.close();
	SMATRIX1.close();
	Info.close();
	return 0;
}
