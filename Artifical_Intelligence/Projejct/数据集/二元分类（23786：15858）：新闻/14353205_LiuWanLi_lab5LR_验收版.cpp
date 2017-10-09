#include<bits/stdc++.h> 
#define MAX_ITER_TIMES 500 
#define VECTOR_NUMS 59 
#define TEST_LINES  15858 
#define TRAIN_LINES 23786 
using namespace std;
double trainData[24000][VECTOR_NUMS];
double testData[TEST_LINES][VECTOR_NUMS];
double w1[VECTOR_NUMS];//用来记录更新的系数 
double w2[VECTOR_NUMS];//用来记录当前使用的系数 
double w[VECTOR_NUMS];//最后得到的系数 
int trainLabels[24000];
double pre1[24000];   //概率 
double findLabels[TEST_LINES];
float err[VECTOR_NUMS]; //梯度 
int j,times=0;//记录迭代次数 
const double n = 100; //学习速率为0.2 ,20竟然跑不出来 ？？ 
int i,temp,row1,row2;
void readFile()
{
  	ifstream in;
	in.open("train_data.txt");
	
  	i= 0; 
	cout<<"Reading File!\n";
    while (!in.eof())
    {
    	for(j = 1 ;j < VECTOR_NUMS;j++) //每一个测试样本向量 
    	{
    		in>>trainData[i][j];
    		//cout<<trainData[i][j]<<endl; 
    	}
    	
    	i++;
    }
	//cout<<"nani!\n";
    row1 = i - 1; //训练样本行数 
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
    row2=i-1; //测试样本行数 
    for(int j=0;j<i;j++)
	{
		testData[j][0]=1;
	}
	in.close();
    //cout<<" File end!\n";
}
void FindW()
{
	for(int i = 0 ;i < VECTOR_NUMS; i++)
	{
		w1[i] = 1;   //初始化为1 
	} 
	for(times = 0; times < MAX_ITER_TIMES; times++)
	{
		printf("第%d几次迭代\n",times);
		memset(err, 0, sizeof(err));
		bool flag = false;
		memset(pre1, 0, sizeof(pre1));	
		for(int k = 0;k < VECTOR_NUMS; k++)
			w2[k] = w1[k];//更新系数 
		for(j = 0;j < row1; j++)//遍历所有训练样本，计算出每一个样例权重分数 
   		{
    		for(int k = 0;k < VECTOR_NUMS;k++)
    		{
    			pre1[j] = pre1[j] + w2[k] * trainData[j][k];
    		}			
   		}
   		for(int j = 0;j < VECTOR_NUMS;j++)
		{
			for(int k = 0; k < row1; k++) //计算梯度 
			{
				err[j] += ( 1/(1+exp(-pre1[k])) - trainLabels[k] ) * (trainData[k][j]);
			}
			w1[j] = w2[j] - n * err[j]; //更新权重 
			if(err[j] != 0)
			{
				flag = true;  //还有一个梯度不为0 ，还可以继续更新 
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
   		 	break; //如果梯度全部为0，停止迭代，因为权重不会继续更新的了。 
   		}
	}   
    //cout<<"迭代次数是 "<<times<<endl;
}
void exam()
{
	ofstream out("myAnswer.txt");
	for(i = 0;i < row2;i++) //对test的每个样例进行预测 
    {
    	for(int m = 0;m < VECTOR_NUMS;m++)
    		findLabels[i] = findLabels[i] + w[m] * testData[i][m];
    	float pre = 1 / ( 1 + exp(-findLabels[i]) );
    	out<<pre<<endl;
    	if (pre >= 0.5)	findLabels[i] = 1;
    	else if(pre < 0.5)	findLabels[i] = 0;
    }
}

int main()
{	
	readFile();
	FindW();  //找权重系数 
	exam();   //测试 
    return 0;
}
