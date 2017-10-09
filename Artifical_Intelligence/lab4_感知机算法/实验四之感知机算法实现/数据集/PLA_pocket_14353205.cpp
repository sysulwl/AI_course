#include<bits/stdc++.h>
using namespace std;
#define ROWS 100 
#define COLUMNS 10001 
#define MAXITERTIMES 1000
int matrix[ROWS][COLUMNS];
int trainY[ROWS],testY[ROWS],myY[ROWS];
int W[COLUMNS] = {0};//��Ϊ����һ��x0;
int bestW[COLUMNS] = {0};
ofstream output;
ifstream Input;
int iterTimes = 0;//�������� 
int sign(int x) {return x >= 0 ? +1 : -1; }
void makeUpMatrix(string fileName)
{
	int lines = 0;
	Input.open(fileName.c_str());
	string line;
	while(getline(Input,line))
	{		
		stringstream ss;
		int columns = 1;
		//һ��һ�仰�ģ�������stringstream,���ж�������Ի᷽��ܶ� 
		ss.clear(); 
		ss.str(line);//From:http://blog.csdn.net/lanbing510/article/details/42423333
					//str()��Ա������ʹ�ÿ�����istringstream���󷵻�һ��string�ַ��� 
		int dict; 
		matrix[lines][0] = 1;
		while(ss>>dict) //����ÿ�е����ݼ����ݵĴʻ� 
		{
			matrix[lines][columns++] = dict;
		}
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
	
	Input.open("test_labels.txt");
	lines = 0;
	while(getline(Input,line))
	{		
		stringstream ss;
		ss.clear(); 
		ss.str(line);
		int dict; 
		while(ss>>dict)
		{
			testY[lines++] = dict;
		}
	}
	Input.close();
}

int dotProduct(int *a, int *b,int length) //����ά���飬w���飩
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
void updateW(int label, int* a) //w������W���飬Ҳ������bestW���� 
{
	for(int i = 0 ; i < COLUMNS; i++)
	{
		W[i] = W[i] + label * (*a);
		a++;
	}
}
bool isBetter(int label,int *a)
{
	int originRightTimes = 0, newRightTimes = 0;
	for(int i = 0 ;i < ROWS;i++) 
	{
		if(sign(dotProduct(matrix[i],W,COLUMNS)) == trainY[i]) originRightTimes++;
		//����ԭ����W�õ�����ȷ���� 
		if(sign(dotProduct(matrix[i],bestW,COLUMNS)) == trainY[i]) newRightTimes++;
	}
	printf("ԭ��ȷ����= %d�� ����ȷ����= %d\n",originRightTimes,newRightTimes);
	if(newRightTimes < originRightTimes) return true;
	else return false;
}
void findW()
{
	bool ok = false;// �Ƿ��ҵ�w������
	while((!ok) && (iterTimes < MAXITERTIMES)) //��û���� 
	{
		ok = true;
		for(int i = 0 ; i < ROWS; i++)
		{
			if(sign( dotProduct(matrix[i],W,COLUMNS) ) != trainY[i])
			{
				ok = false;
				updateW(trainY[i],matrix[i]);
				iterTimes++;  //����һ�� 
				cout<<iterTimes<<endl; 
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
	for(int i = 0 ; i < COLUMNS; i++) output<<W[i]<<" ";
	output<<endl;
	output<<"iterator times is "<< iterTimes <<endl; 
}
void cal4(int TP,int FN,int FP, int TN)
{
	double Accuracy = 1.0 * (TP+TN) / (TP+FP+TN+FN);
	double Recall = 1.0 * TP / (TP+FN);
	double Precision= 1.0 * TP / (TP+FP);
	double  F1 = 2 * Precision * Recall / (Precision + Recall);
	output<< "Accuracy = "<< Accuracy<<endl;
	output<< "Recall = "<<Recall<<endl;
	output<< "Precision= "<<Precision<<endl;
	output<< "F1 = "<<F1<<endl;
}
void test()
{
	int TP = 0, FN = 0, FP = 0, TN = 0;
	for(int i = 0 ; i < ROWS; i++)
	{
		myY[i] = sign(dotProduct(matrix[i],W,COLUMNS));
		if(testY[i] == 1) //��ȷ��Ϊ1 
		{
			if(myY[i] == 1) TP++;
			else  FN++;
		}
		else //��ȷ��Ϊ-1
		{
			if(myY[i] == 1) FP++;
			else  TN++;
		}
	}
	cal4(TP,FN,FP,TN);
}
int main()
{
	output.open("myansWer.txt");
	makeUpMatrix("train_data.txt");  //��train.data���ݴ洢��matrix�����ά���� 
	readLabels();   //��ȡtrain,test�ı�ǩ 
	findW();//����W������ 
	seeW();// �����ҵ���W����͵������� 
	makeUpMatrix("test_data.txt");//��test.data���ݴ洢��matrix�����ά���� 
	test();         //��test���з��� 
	output.close();
} 
