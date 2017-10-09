#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define PROPERTY_NUM 58
#define MAX_ITER_TIMES 5000
float trainData[24000][60];
float testData[24000][60];
float w1[60];//������¼���µ�ϵ�� 
float w2[60];//������¼��ǰʹ�õ�ϵ�� 
float w[60];//������¼ÿ�θ��º���������������������������������ϵ�� 
float labelsOfTrain[24000];
int labelsOfTest[24000];
float pre1[24000];//ѵ��������Ԥ��ֵ 
float pre2[24000];//��������Ԥ��ֵ 
float err[60];//PPT��Err(w)���ݶ�
char buffer[6000];
int col;
int g = 0;
int i = -1,TRAIN_DATA_LINES,TEST_DATA_LINES;
float StringToNumber(string s)//���ַ���ת��Ϊ���� 
{
	float x=0;
	int flag=0;
	if(s[0]=='-')
	{
		for(int r=1;r<s.size();r++)
		{
			if(s[r]!='-'&&s[r]!='0'&&s[r]!='1'&&s[r]!='2'&&s[r]!='3'&&s[r]!='4'&&s[r]!='5'&&s[r]!='6'&&s[r]!='7'&&s[r]!='8'&&s[r]!='9')
			{
				flag=r;
				break;
			}
		}
		if(flag!=0)
		{
			for(int r=1;r<flag;r++)
			{
				x=x+(s[r]-'0')*float(pow(10,flag-r-1));
			}
			for(int r=flag+1;r<s.size();r++)
			{
				x=x+(s[r]-'0')*float(pow(10,-(r-flag)));
			}
		}
		else
		{
			for(int r=1;r<s.size();r++)
			{
				x=x+(s[r]-'0')*float(pow(10,s.size()-r-1));
			}
		}
		x=-x;
	}
	else{
		for(int r=1;r<s.size();r++)
		{
			if(s[r]!='-'&&s[r]!='0'&&s[r]!='1'&&s[r]!='2'&&s[r]!='3'&&s[r]!='4'&&s[r]!='5'&&s[r]!='6'&&s[r]!='7'&&s[r]!='8'&&s[r]!='9')
			{
				flag=r;
				break;
			}
		}
		if(flag!=0)
		{
			for(int r=0;r<flag;r++)
			{
				x=x+(s[r]-'0')*float(pow(10,flag-r-1));
			}
			for(int r=flag+1;r<s.size();r++)
			{
				x=x+(s[r]-'0')*float(pow(10,-(r-flag)));
			}
		}
		else
		{
			for(int r=0;r<s.size();r++)
			{
				x=x+(s[r]-'0')*float(pow(10,s.size()-r-1));
			}
		}
	}
	return x;
} 
//��������ָ�� 
int eliminate(int a,int b,int c,int d)
{
	cout<<"accurancy:"<<double(a+b) / (a+b+c+d) <<endl;
	double recall = double(a)/(a+d);
	cout<<"recall:"<<recall<<endl;
	double precision = double(a)/(a+c);	
	cout<<"precision:"<<precision<<endl;
	double F1 = 2*precision*recall/(precision+recall);
	cout<<"F1:"<<F1<<endl;
	return 0;
}
void init()
{
	memset(trainData, 0, sizeof(trainData));
	memset(testData, 0, sizeof(testData));
	memset(labelsOfTrain, 0, sizeof(labelsOfTrain));
	memset(labelsOfTest, 0, sizeof(labelsOfTest));
	memset(w1, 0, sizeof(w1));
	memset(w2, 0, sizeof(w2));
	memset(w, 0, sizeof(w));
	memset(pre1, 0, sizeof(pre1));	
	memset(pre2, 0, sizeof(pre2));	
	for(int j = 0;j < TEST_DATA_LINES;j++)//ÿһ����������һ��1 
	{
		testData[j][0] = 1;
	}   
}
void readTrain()
{
	ifstream in("train.txt");   
    if (! in.is_open())
    { cout << "Error opening file"; exit (1); }
	//��train 
    while (!in.eof() )
    {
        in.getline (buffer,sizeof(buffer));
        const char *d = ",";
        char *p;
        p = strtok(buffer,d);
        col = 0;
		if(p)
		i++;
        while(p != NULL)
        {
        		col ++;    	
                if(i == 0)
                {
                	break;
                }
                else
                {
                	if (col < PROPERTY_NUM + 1 && p != NULL)
                	{
                		string str(p);
                		trainData[i-1][col] = StringToNumber(str);
                	}
                	else if (col == PROPERTY_NUM + 1&&p != NULL) 
    				{   
    					string str(p);
                		labelsOfTrain[i-1] = StringToNumber(str);
    				}
                }
				p = strtok(NULL,d);  			
        }
    }
}
char buffer1[6000];
void readTest()
{
	ifstream in1("test.txt");   
    if (!in1.is_open())
    { cout << "Error opening file"; exit(1); }
	g = 0;
	i = -1;
	//��test 
    while (!in1.eof() )
    {
        in1.getline (buffer,sizeof(buffer));
        const char *d = ",";
        char *p;
        p = strtok(buffer,d);
        col = 0;
		if(p)
		i++;
	//	cout<<i<<" ";
        while(p!=NULL)
        {
        		col++;    	
                if(i==0)
                {
                	break;
                }
                else
                {
                	if (col <PROPERTY_NUM + 1 && p != NULL)
                	{
                		string str(p);
                		testData[i-1][col]=StringToNumber(str);
                	}
                	else if (col == PROPERTY_NUM + 1 && p != NULL) 
    				{   
    					string str(p);
                		//labelsOfTest[i-1]=StringToNumber(str);
    				}
                }
				p = strtok(NULL,d);  			
        }
    }
}
void work()
{
    i = 0;
	int j;
	//int times = 0;//��¼�������� 
	double n = 1000;//����һ���ʼ�ĳɳ����� 
	int maxRightTimes = 0;
	int rightTimes;
	for(int times = 0;times < MAX_ITER_TIMES ;times++)//�����ֻ� 
	{
		rightTimes = 0;
		cout<<times<<" ";
		memset(err, 0, sizeof(err));
		memset(pre1, 0, sizeof(pre1));//ÿһ�ε�����ʼ����������һ�ε���������������Ӱ�� 
		int flag = 0;//����Err(w)�ݶȲ�Ϊ0���� 	
		n = 1000 - pow(float(times)/200,2);//���³ɳ�����n�ķ������ɳ�����Խ��ԽС 
		for(int k = 0; k < PROPERTY_NUM + 1; k++)
			w2[k] = w1[k];//����ϵ�� 
		for(j = 0;j < TRAIN_DATA_LINES; j++)
   		{//��������ѵ���������ó�ÿһ������Ȩ�ط��� 
    		for(int k = 0;k < PROPERTY_NUM + 1; k++)
    		{
    			pre1[j] = pre1[j] + w2[k] * trainData[j][k];
    		}		
			float pre = float(  1 / float(1+float(  exp(-pre1[j]) )  )  );
    		if (pre >= 0.5)	pre2[j] = 1;
    		else if(pre < 0.5)	pre2[j] = 0;
    		if(pre2[j] == labelsOfTrain[j]) rightTimes++;
   		}
   		for( int j = 0;j < PROPERTY_NUM + 1;j++ )
		{
			for(int k = 0;k < TRAIN_DATA_LINES;k++)
			{//���ݹ�ʽ����Err(wi)���ݶ� 
				err[j] += (1/(1+float(exp(-pre1[k]))) - labelsOfTrain[k]) * (trainData[k][j]); 
			}
			w1[j] = w2[j] - n * err[j];//����Ȩ�� 
			if(err[j] != 0)
			{
				flag++;
			}
		} 
	/*	if(flag!=0)
		{
			for(int k=0;k<PROPERTY_NUM + 1;k++)
   		 		w[k]=w1[k];
		}*/
   		if(flag != 0 && rightTimes > maxRightTimes)
   		 {  
   		 	for(int k = 0; k < PROPERTY_NUM + 1; k++)
   		 		w[k] = w2[k];
   		 	maxRightTimes = rightTimes;
   		 //	break;
   		 }
   		 else if(flag == 0)
   		 {//err������0�����ҵ����Ž�����
			cout<<"�ҵ����Ž⣡����\n";  
   		 	for(int k = 0;k < PROPERTY_NUM + 1;k++)
   		 		w[k] = w2[k];
   		 	maxRightTimes = rightTimes;
   		 	break;
   		 }
	}   
	cout<<"MAX_ITER_TIMES = "<<MAX_ITER_TIMES<<endl; 
	ofstream out("testAnswer.txt");
    //Ԥ��������� 
	for(int l = 0;l < TEST_DATA_LINES;l++ )
    {
    	for(int m = 0;m < PROPERTY_NUM + 1;m++)
    		pre2[l] = pre2[l] + w[m] * testData[l][m];
    	float pre = float( 1/   float(1 + float( exp(-pre2[l])) )  );
    	if (pre > 0.5)	pre2[l] = 1;
    	else if(pre < 0.5)	pre2[l] = 0;
    	else if(pre == 0.5)	pre2[l] = 1;
    	out<< pre2[l] <<endl;
    }
}
int main()
{		
	init();
	readTrain();
    TRAIN_DATA_LINES = i;
	readTest();
	TEST_DATA_LINES = i;
	work();
   /* int TP=0;
    int FN=0;
    int FP=0;
    int TN=0;
    for(int k=0;k<TEST_DATA_LINES;k++)
    {
    	if(labelsOfTest[k]==pre2[k])
    	{
    		count++;
    		if(labelsOfTest[k]==1)	TP++;
    		else	TN++;
    	}
    	else
    	{
    		if(labelsOfTest[k]==1&&pre2[k]==0)	FN++;
    		else if(labelsOfTest[k]==0&&pre2[k]==1)	FP++;
    	}
    } 
	cout<<"TP:"<<TP<<" TN:"<<TN<<" FP:"<<FP<<" FN:"<<FN<<endl; 
    eliminate(TP,TN,FP,FN);*/
    return 0;
}
