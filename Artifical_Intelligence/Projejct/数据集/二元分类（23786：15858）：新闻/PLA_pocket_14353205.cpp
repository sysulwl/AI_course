#include<bits/stdc++.h>
using namespace std;
#define ROWS 23786 
#define COLUMNS 59 
#define MAXITERTIMES 500
double matrix[ROWS][COLUMNS];
int trainY[ROWS],testY[ROWS],myY[ROWS];
double W[COLUMNS] = {1};//��Ϊ����һ��x0;
double bestW[COLUMNS] = {0};
ofstream output;
ifstream Input;
int iterTimes = 0;//�������� 
int sign(double x) {return x >= 0 ? 1 : 0; }
void makeUpMatrix(string fileName)
{
	int lines = 0;
	Input.open(fileName.c_str());
	string line;
	while(getline(Input,line))
	{		
		stringstream ss;
		int columns = 1;
		ss.clear(); 
		ss.str(line);//From:http://blog.csdn.net/lanbing510/article/details/42423333
					//str()��Ա������ʹ�ÿ�����istringstream���󷵻�һ��string�ַ��� 
		double dict; 
		matrix[lines][0] = 1;
		while(ss>>dict) //����ÿ�е����ݼ����ݵĴʻ� 
		{
			matrix[lines][columns++] = dict;
			output<<dict<<" ";
		}
		output<<endl;
		//��ȡ�����дʻ��� 
		lines++;  //�ڼ��м��� 
	}
	Input.close();
	
}
void readLabels()
{
	Input.open("train_labels.txt");
	int lines = 0;
	string line;
	while(getline(Input,line))
	{		
		stringstream ss;
		ss.clear(); 
		ss.str(line);
		int dict; 
		while(ss>>dict)
		{
			trainY[lines++] = dict;
		}
	}
	Input.close();

}

int dotProduct(double *a, double *b,int length) //����ά���飬w���飩
{
	int ans = 0;
	for(int i = 0 ; i < length ;i++)
	{
		ans += (*a) * (*b);
		a++;
		b++;
	}
	return ans;
} 
void updateW(int label, double* a) //w������W���飬Ҳ������bestW���� 
{
	for(int i = 0 ; i < COLUMNS; i++)
	{
		W[i] = W[i] + label * (*a);
		a++;
	}
}
bool isBetter(int label,double *a)
{
	int originRightTimes = 0, newRightTimes = 0;
	for(int i = 0 ;i < ROWS;i++) 
	{
		if(sign(dotProduct(matrix[i],W,COLUMNS)) == trainY[i]) originRightTimes++;
		//����ԭ����W�õ�����ȷ���� 
		if(sign(dotProduct(matrix[i],bestW,COLUMNS)) == trainY[i]) newRightTimes++;
		//����bestW 
	}
	printf("ԭ��ȷ����= %d�� ����ȷ����= %d\n",originRightTimes,newRightTimes);
	if(newRightTimes < originRightTimes) return true;
}
void findW()
{
	bool ok = false;// �Ƿ��ҵ�w������
	while( (!ok) && (iterTimes < MAXITERTIMES) ) //��û���� 
	{
		ok = true;
		for(int i = 0 ; i < ROWS; i++)
		{
			if(sign( dotProduct(matrix[i],W,COLUMNS) ) != trainY[i]) //��һ��Ԥ���������� 
			{
				ok = false;
				updateW(trainY[i],matrix[i]);
				iterTimes++;  //����һ�� 
				cout<<"iterTimes is "<<iterTimes<<endl; 
				if(isBetter(trainY[i],matrix[i])) 
				{
					for(int i = 0 ; i < COLUMNS;i++)
					{bestW[i] = W[i];}//����bestW ���� 
				} 
				break;
			}
		} 
	} 
}
void seeW()
{
	output<<"Let's see W!\n";
	for(int i = 0 ; i < COLUMNS; i++) output<<W[i]<<" ";
	output<<endl;
	output<<"iterator times is "<< iterTimes <<endl; 
}
void test()
{
	for(int i = 0 ; i < ROWS; i++)
	{
		myY[i] = sign(dotProduct(matrix[i],W,COLUMNS));
		output<<myY[i]<<endl; 
	}
}
int main()
{
	//memset(W,1,sizeof(W));
	for(int i = 0; i < COLUMNS ; i++) W[i] = 100;
	output.open("myAnswer.txt");
	makeUpMatrix("train_data.txt");  //��train.data���ݴ洢��matrix�����ά���� 
	readLabels();   //��ȡtrain,test�ı�ǩ 
	findW();//����W������ 
	seeW();// �����ҵ���W����͵������� 
	makeUpMatrix("test_data.txt");//��test.data���ݴ洢��matrix�����ά���� 
	test();         //��test���з��� 
	output.close();
	return 0;
} 
