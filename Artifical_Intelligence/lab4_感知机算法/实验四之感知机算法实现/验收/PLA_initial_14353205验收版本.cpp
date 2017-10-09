#include<bits/stdc++.h>
using namespace std;
#define ROWS 6 
#define COLUMNS 3 
#define TEST_ROWS 4
#define TEST_COLUMNS 3
int matrix[ROWS][COLUMNS];
int trainY[ROWS],testY[TEST_ROWS],myY[ROWS];
int W[COLUMNS] = {0};//��Ϊ����һ��x0;
ofstream output;
ifstream Input;
int iterTimes = 0;//�������� 
int sign(int x) {return x > 0 ? +1 : -1; }
void makeUpMatrix_train(string fileName)
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
		int this_time = 0; 
		while(ss>>dict) //����ÿ�е����ݼ����ݵĴʻ� 
		{
			this_time++;
			if(this_time < COLUMNS)matrix[lines][columns++] = dict;
			else trainY[lines] = dict;
		}
		//��ȡ�����дʻ��� 
		lines++;  //�ڼ��м��� 
	}
	Input.close();
	
}
void makeUpMatrix_test(string fileName)
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
		int this_time = 0; 
		while(ss>>dict) //����ÿ�е����ݼ����ݵĴʻ� 
		{
			matrix[lines][columns++] = dict;
		}
		//��ȡ�����дʻ��� 
		lines++;  //�ڼ��м��� 
	}
	Input.close();
	
}

void checkMatrix()
{
	output.open("temp.txt");
	for(int i = 0; i < ROWS ; i++)
	{ 
		for(int j = 0 ; j < COLUMNS; j++)
		{
			output<< matrix[i][j] <<" ";
		}
		output<<endl;
	}
	output.close();
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
void checkDotProduct()
{
	int a[4][4];
	for(int i = 0 ; i < 4 ;i++) {
		a[2][i] = i;
	}
	int b[4] = {0,1,2,3};
	cout<< dotProduct(a[2],b,4)<<endl;
}
void updateW(int label, int* a)
{
	for(int i = 0 ; i < COLUMNS; i++)
	{
		W[i] = W[i] + label * (*a);
		a++;
	}
}
void findW()
{
	bool ok = false;// �Ƿ��ҵ�w������
	while(!ok) //��û���� 
	{
		for(int i = 0 ; i < ROWS; i++)
		{
			if(sign( dotProduct(matrix[i],W,COLUMNS) ) != trainY[i])
			{
				updateW(trainY[i],matrix[i]);
				iterTimes++;  //����һ�� 
				cout<<iterTimes<<endl; 
				break;
			}
			if(i == ROWS - 1) ok = true;//�ҵ��ˣ� 
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
	for(int i = 0 ; i < TEST_ROWS; i++)
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
	//cal4(TP,FN,FP,TN);
}
int main()
{
	//checkMatrix�������Լ�����õ��������Ƿ���ȷ 
	output.open("myAnswer.txt");
	makeUpMatrix_train("train.txt");  //��train.data���ݴ洢��matrix�����ά���� 
	findW();//����W������ 
	seeW();// �����ҵ���W����͵������� 
	makeUpMatrix_test("test.txt");//��test.data���ݴ洢��matrix�����ά���� 
	//checkMatrix();
	test();         //��test���з��� 
	output.close();
	for(int i = 0 ; i < TEST_ROWS ; i++)
	{
		printf("��%d����%d\n",i,myY[i]);
	}
} 
