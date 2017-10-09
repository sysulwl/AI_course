#include<iostream>
#include<fstream>
#include<map>
#include<vector> 
#include<sstream>
#include<cmath>
#include<algorithm>
using namespace std;
double P[250][6]; 
double DIS[500][246];
//1.������������һ�����ļ������⣬������ô��ȡ��һ���ַ���������һ�����̶����ַ���֮�� ����6������ 
struct Three_Var
{
	int i,j;
	bool operator<(Three_Var& t) {return i<t.i||(i==t.i&&j<t.j);}
	bool operator==(Three_Var& t) {return i==t.i&&j==t.j;}
};
bool Sort( Three_Var d1,Three_Var d2)    {return d1 < d2;}   //��������
vector< vector<int> > NumsPerLines; 
int main()
{
	int index=0;//���γ��ֵģ�ȥ�أ��ʻ�Ķ�Ӧ�±� 
	int Lines=0;//���ֵ����� 
	int ThreeVarNums=0;//��Ԫ��ĸ��� 
	ifstream Input;
	Input.open("Dataset_train.txt");//��ȡ�ļ� 
	string line;	//һ����ʱ�������� 
	map<string, int> FirstIndex;//string�Ƕ�Ӧ�Ĵʻ㣬int�����������ظ��£���һ�γ��ֵ��ڸ�map�е��±�
	map<int,int> repeatTimes; 
	vector<Three_Var> smat;
	vector<int> Emo;
	bool first = true;//��Ϊѵ���ı���һ��û�ã�
	ofstream Info,Pro;
	Info.open("EveryLine.txt");
	Pro.open("Pro.txt");
	while(getline(Input,line))
	{		
		if(first) {first = false;continue;} 
		stringstream ss;
		int temp = 0;
		//��������ע�⵽һ����ʵ����д�ְ����dev_cpp��ʱ��������ؿ�����һ��һ�仰�ģ�������stringstream
		//���ж�������Ի᷽��ܶ� 
		ss.clear(); 
		ss.str(line);
		string dict; 
		ss >> dict ; //����train_���û�õĵ��� 
		map<string,int>::iterator it1;
		map<int,int>::iterator it2;
		repeatTimes.clear();
		int P_OF_EMO = 0;
		while(ss>>dict)  //����ÿ�е����ݼ����ݵĴʻ� 
		{
			stringstream See(dict); 
			double doub;
			See >> doub;
			if(!See.fail())//�Ǹ�����
			{
 				P[Lines][P_OF_EMO] = doub;
 				P_OF_EMO++;
 				Info<<doub<<" ";
			} 
			else{               //�������־�����ͨ�ַ��� 
				if(dict == "��") break; //Dataset_test �е����ֱ��ʺŴ����� 
				Info<<dict<<" ";
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
		}
		Info<<temp<<endl;
		//��ȡ�����дʻ��� 
		
		vector <int> Temp_Vec;
		for(it2=repeatTimes.begin();it2!=repeatTimes.end();it2++)  //Ϊ����vector�����򣬽������map 
		{
			Three_Var item{Lines,it2->first};//���û������¼������ʳ��ֵ��������±�
			smat.push_back(item);
			ThreeVarNums++;//�ṹ��vector�з���ĸ��� 
			Temp_Vec.push_back(it2->first);//����ṹ�洢ÿһ��ӵ�е��ַ������±ꣻ
		}
		NumsPerLines.push_back(Temp_Vec);
		Lines++;  //�ڼ��м��� 
		if(Lines == 246){
			first = true;
			Input.close();
			Input.open("Dataset_test.txt");
		}
	}
	cout<<"����������"<<Lines<<"; ��ͬ���ַ�������"<<index<<endl;
	cout<<"�ж�Ԫ�����"<<ThreeVarNums<<endl;

	Input.close();
	cout<<"Input operation has done!"<<endl;
	//��ȡ�������ĵ� 
	
	//���������д������� 
	sort(smat.begin(),smat.end(),Sort);
	ofstream OneHot,SMATRIX1;
	OneHot.open("OneHot.txt");
	SMATRIX1.open("smatrix1.txt"); //��Ԫ����� 
	SMATRIX1<<Lines<<endl<<index<<endl<<ThreeVarNums<<endl;
	int pos=0;
	int RightNums = 0;
	Info <<"������� : " <<endl; 
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
		if(i >= 246){//test.txt�����࿩�� 
			int MinLine = 0; 
			Info << i <<" ";
				for(int r = 0; r < 246; r++){ //��ѵ���ı���ÿһ����ŷʽ����
						int dis = 0;
						int c = 0 , k = 0 , equals = 0; 
						for(; c < NumsPerLines[i].size() ; c++){ //��ǰ�е��ַ��� 
							for(; k < NumsPerLines[r].size(); k++){
								if(NumsPerLines[i][c] <  NumsPerLines[r][k])
									break;
								else if(NumsPerLines[i][c] ==  NumsPerLines[r][k])
									equals++;
							}
						}
					    dis = NumsPerLines[i].size() + NumsPerLines[r].size() - equals * 2;//�õ����������
						DIS[i-246][r] = dis;   //�õ�������� 
						Info<<dis <<" ";
				} 	
				Info <<endl;
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
	map<string,int>::iterator it;
	for(it = FirstIndex.begin();it != FirstIndex.end(); it++)
	{
		Info << it->first <<" " << it->second<<endl;
	}
	cout<<"File operation has done!"<<endl;
	for(int i = 0 ; i < 500; i++) //ʵ���ϴ���� i + 246 �� 
	{
		Pro <<"test"<< i+1 <<" ";
		double SUM[6], all = 0;
		for(int j = 0 ; j < 6 ; j++)
		{
			double sum = 0;
			for(int k = 0; k < 246 ; k++)
			{
				sum += P[k][j]/ DIS[i][k];
			}
			SUM[j] = sum;
			all += sum;
		}
		for(int j = 0 ; j < 6 ; j++) //��һ�� 
		{
			Pro << SUM[j]/all<<" ";
		}
		Pro << endl;
	} 
	//cout<<"The right rate is "<<(double)(RightNums)/1000<<endl;
	/*---------------��ɲ������ر��ļ������ ---------------*/ 
	OneHot.close();
	SMATRIX1.close();
	Info.close();
	return 0;
}
