#include<bits/stdc++.h>
using namespace std;
#define ROWS 100 
#define COLUMNS 10001 
int matrix[ROWS][COLUMNS];
int trainY[ROWS],testY[ROWS],myY[ROWS];
int W[COLUMNS] = {0};//因为多了一个x0;
ofstream output;
ifstream Input;
int iterTimes = 0;//迭代次数 
int sign(int x) {return x > 0 ? +1 : -1; }
void makeUpMatrix(string fileName)
{
	int lines = 0;
	Input.open(fileName.c_str());
	string line;
	while(getline(Input,line))
	{		
		stringstream ss;
		int columns = 1;
		//一行一句话的，所以用stringstream,整行读入的特性会方便很多 
		ss.clear(); 
		ss.str(line);//From:http://blog.csdn.net/lanbing510/article/details/42423333
					//str()成员函数的使用可以让istringstream对象返回一个string字符串 
		int dict; 
		matrix[lines][0] = 1;
		while(ss>>dict) //读入每行的数据集内容的词汇 
		{
			matrix[lines][columns++] = dict;
		}
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
int dotProduct(int *a, int *b,int length) //（二维数组，w数组）
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
	bool ok = false;// 是否找到w数组了
	while(!ok) //还没完善 
	{
		for(int i = 0 ; i < ROWS; i++)
		{
			if(sign( dotProduct(matrix[i],W,COLUMNS) ) != trainY[i])
			{
				updateW(trainY[i],matrix[i]);
				iterTimes++;  //迭代一次 
				cout<<iterTimes<<endl; 
				break;
			}
			if(i == ROWS - 1) ok = true;//找到了！ 
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
		if(testY[i] == 1) //正确答案为1 
		{
			if(myY[i] == 1) TP++;
			else  FN++;
		}
		else //正确答案为-1
		{
			if(myY[i] == 1) FP++;
			else  TN++;
		}
	}
	cal4(TP,FN,FP,TN);
}
int main()
{
	//checkMatrix函数可以检查矩阵得到的内容是否正确 
	output.open("myAnswer.txt");
	makeUpMatrix("train_data.txt");  //将train.data数据存储在matrix这个二维矩阵 
	readLabels();   //读取train,test的标签 
	findW();//完善W数组了 
	seeW();// 看看找到的W数组和迭代次数 
	makeUpMatrix("test_data.txt");//将test.data数据存储在matrix这个二维矩阵 
	test();         //对test进行分类 
	output.close();
} 
