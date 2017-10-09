#include<bits/stdc++.h> 
#define MAX_ITER_TIMES 50 
#define VECTOR_NUMS 10 
#define TEST_LINES  100 
#define TRAIN_LINES 583
using namespace std;
int trainData[600][VECTOR_NUMS];
int testData[TEST_LINES][VECTOR_NUMS];
double w1[VECTOR_NUMS];//������¼���µ�ϵ�� 
double w2[VECTOR_NUMS];//������¼��ǰʹ�õ�ϵ�� 
double w[VECTOR_NUMS];//���õ���ϵ�� 
int trainLabels[600];
int testLabels[TEST_LINES];
double pre1[600];   //���� 
double findLabels[TEST_LINES];
float err[VECTOR_NUMS]; //�ݶ� 
int TP=0,FN=0,FP=0,TN=0;
int j,times=0;//��¼�������� 
const double n = 0.2; //ѧϰ����Ϊ0.2 
int i,temp,row1,row2;
void readFile()
{
  	ifstream in;
	in.open("train_data.txt");
  	i= 0; 
    while (!in.eof())
    {
    	for(j=1;j<VECTOR_NUMS;j++) //ÿһ������������9ά���� 
    	{
    		in>>trainData[i][j];
    	}
    	i++;
    }
    row1 = i - 1; //ѵ���������� 
	for(int j = 0;j < i - 1; j++)
	{
		trainData[j][0] = 1;
	}
	in.close();
    in.open("train_labels.txt");
    i = -1;
    while ( !in.eof() )
    {	
		i++;
    	in>>trainLabels[i];
    }
    in.close();
    in.open("test_data.txt");
	i=0;  
    while (!in.eof() )
    {
    	for(int j=1;j<VECTOR_NUMS;j++)
    	{
    		in>>testData[i][j];
    	}
    	i++;
    }
    row2=i-1; //������������ 
    for(int j=0;j<i;j++)
	{
		testData[j][0]=1;
	}
	in.close();
    in.open("test_labels.txt");
    i = -1;
    while (!in.eof())
    {	
		i++;
    	in>>testLabels[i];
    }
    in.close();
}
void FindW()
{
	for(int i = 0 ;i < VECTOR_NUMS; i++)
	{
		w1[i] = 1;   //��ʼ��Ϊ1 
	} 
	for(times = 0; times < MAX_ITER_TIMES; times++)
	{
		memset(err, 0, sizeof(err));
		bool flag = false;
		memset(pre1, 0, sizeof(pre1));	
		for(int k = 0;k < VECTOR_NUMS; k++)
			w2[k] = w1[k];//����ϵ�� 
		for(j = 0;j < row1; j++)//��������ѵ�������������ÿһ������Ȩ�ط��� 
   		{
    		for(int k = 0;k < VECTOR_NUMS;k++)
    		{
    			pre1[j] = pre1[j] + w2[k] * trainData[j][k];
    		}			
   		}
   		for(int j = 0;j < VECTOR_NUMS;j++)
		{
			for(int k = 0; k < row1; k++) //�����ݶ� 
			{
				err[j] += ( 1/(1+exp(-pre1[k])) - trainLabels[k] ) * (trainData[k][j]);
			}
			w1[j] = w2[j] - n * err[j]; //����Ȩ�� 
			if(err[j] != 0)
			{
				flag = true;  //����һ���ݶȲ�Ϊ0 �������Լ������� 
			}
		} 
		if(flag)
		{
			for(int i = 0;i < VECTOR_NUMS;i++)
   		 	w[i] = w1[i];
		}
   		else
   		{
   		 	for(int i = 0;i < VECTOR_NUMS;i++)
   		 	w[i] = w2[i];
   		 	break; //����ݶ�ȫ��Ϊ0��ֹͣ��������ΪȨ�ز���������µ��ˡ� 
   		}
	}   
    cout<<"���������� "<<times<<endl;
}
void exam()
{
	ofstream out("result.txt");
	for(i = 0;i < row2;i++) //��test��ÿ����������Ԥ�� 
    {
    	for(int m = 0;m < VECTOR_NUMS;m++)
    		findLabels[i] = findLabels[i] + w[m] * testData[i][m];
    	float pre = 1 / ( 1 + exp(-findLabels[i]) );
    	out<<pre<<endl;
    	if (pre >= 0.5)	findLabels[i] = 1;
    	else if(pre<0.5)	findLabels[i] = 0;
    }
    for(i = 0;i < row2; i++)
    {
    	if(testLabels[i]==findLabels[i])
    	{
    		if(testLabels[i]==1)	TP++;
    		else	TN++;
    	}
    	else
    	{
    		if(testLabels[i] == 1 && findLabels[i] == 0)	FN++;
    		else if(testLabels[i] == 0 && findLabels[i] == 1)	FP++;
    	}
    } 
	cout<<"TP:"<<TP<<" TN:"<<TN<<" FP:"<<FP<<" FN:"<<FN<<endl; 
}
void show()
{
	cout<<"accurancy = "<<double(TP+TN)/(TP+TN+FP+FN)<<endl;
	double recall=double(TP)/(TP+FN);
	cout<<"recall = "<<recall<<endl;
	double precision = double(TP)/(TP+FP);	
	cout<<"precision = "<<precision<<endl;
	double F1 = 2*precision*recall/(precision+recall);
	cout<<"F1 = "<<F1<<endl;
}
int main()
{	
	readFile();
	FindW();  //��Ȩ��ϵ�� 
	exam();   //���� 
    show();
    return 0;
}
