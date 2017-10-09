#include<bits/stdc++.h>
using namespace std;
#define ROWS 23786 
#define COLUMNS 59 
#define MAXITERTIMES 500
double matrix[ROWS][COLUMNS];
int trainY[ROWS],testY[ROWS],myY[ROWS];
double W[COLUMNS] = {1};//因为多了一个x0;
double bestW[COLUMNS] = {0};
ofstream output;
ifstream Input;
int iterTimes = 0;//迭代次数 
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
					//str()成员函数的使用可以让istringstream对象返回一个string字符串 
		double dict; 
		matrix[lines][0] = 1;
		while(ss>>dict) //读入每行的数据集内容的词汇 
		{
			matrix[lines][columns++] = dict;
			output<<dict<<" ";
		}
		output<<endl;
		//读取完这行词汇了 
		lines++;  //第几行计数 
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

int dotProduct(double *a, double *b,int length) //（二维数组，w数组）
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
void updateW(int label, double* a) //w可能是W数组，也可能是bestW数组 
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
		//计算原来的W得到的正确次数 
		if(sign(dotProduct(matrix[i],bestW,COLUMNS)) == trainY[i]) newRightTimes++;
		//计算bestW 
	}
	printf("原正确次数= %d， 后正确次数= %d\n",originRightTimes,newRightTimes);
	if(newRightTimes < originRightTimes) return true;
}
void findW()
{
	bool ok = false;// 是否找到w数组了
	while( (!ok) && (iterTimes < MAXITERTIMES) ) //还没完善 
	{
		ok = true;
		for(int i = 0 ; i < ROWS; i++)
		{
			if(sign( dotProduct(matrix[i],W,COLUMNS) ) != trainY[i]) //第一个预测错误的样本 
			{
				ok = false;
				updateW(trainY[i],matrix[i]);
				iterTimes++;  //迭代一次 
				cout<<"iterTimes is "<<iterTimes<<endl; 
				if(isBetter(trainY[i],matrix[i])) 
				{
					for(int i = 0 ; i < COLUMNS;i++)
					{bestW[i] = W[i];}//更新bestW 数组 
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
	makeUpMatrix("train_data.txt");  //将train.data数据存储在matrix这个二维矩阵 
	readLabels();   //读取train,test的标签 
	findW();//完善W数组了 
	seeW();// 看看找到的W数组和迭代次数 
	makeUpMatrix("test_data.txt");//将test.data数据存储在matrix这个二维矩阵 
	test();         //对test进行分类 
	output.close();
	return 0;
} 
