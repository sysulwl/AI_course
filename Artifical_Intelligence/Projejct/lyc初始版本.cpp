#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector> 
#include<iterator>
#include<algorithm>
#include<cmath>
#define PI 3.1415926535898
using namespace std;

const int dimen = 14; //维度,dimen种属性
const int numOftrain = 30162; //训练文本行数    ！！！要注意看读进来的训练文本行数 
const int numOftest = 15060; //测试文本行数     ！！！要注意看读进来的测试文本行数
double Accuracy(int TP,int FN,int FP,int TN){
	return (double)(TP+TN)*1.0/(TP+FP+TN+FN);
}
double Recall(int TP,int FN,int FP,int TN){
	return (double)TP*1.0/(TP+FN);
}
double Precision(int TP,int FN,int FP,int TN){
	return (double)TP*1.0/(TP+FP);
}
double F1(int TP,int FN,int FP,int TN){
	return 2.0*Precision(TP,FN,FP,TN)*Recall(TP,FN,FP,TN)/(Precision(TP,FN,FP,TN)+Recall(TP,FN,FP,TN));
}
int main(){
	string line;
	
	vector<vector<string> > table; //属性表格，numOftrain*dimen-1, 因 education-num对应 education，不独立，忽略education-num  
	vector<string> tmp_vec; 
	int y[numOftrain];//label 标签，0代表工资小于五千，1代表公资大于五千 
	
	ifstream trainFile("train.txt",ios::in);
	getline(trainFile,line);//除掉第一行说明性文字 
	double sum[2][5]; //每种标签（0,1）在原本数据集第0，2，9，10，11列的和（respectively） 
	for(int i=0;i<2;i++){
		for(int j=0;j<5;j++){
			sum[i][j]=0;
		}
	} 
	int num_of_y[2];//标签为0的训练文本数 、标签为1的训练文本数 
	for(int i=0;i<2;i++) num_of_y[i]=0;
	double numbers[numOftrain][5];
	int row=0;
	while(getline(trainFile,line)){
		if(line=="\n") continue; //避免出现空行
		for(int i=0;i<line.length();i++){
			if(line[i]==',') line[i]=' ';
		}
		stringstream ss(line);
		string tmp;
		double number;
		for(int i=0;i<dimen;i++){
			if(i==0){
				ss >> number;
				numbers[row][0]=number;
			}
			else if(i==2){
				ss >> number;
				numbers[row][1]=number;
			}
			else if(i==4){
				ss >> tmp;
			}
			else if(i==10){
				ss >> number;
				numbers[row][2]=number;
			}
			else if(i==11){
				ss >> number;
				numbers[row][3]=number;
			}
			else if(i==12){
				ss >> number;
				numbers[row][4]=number;
			}
			else{
				ss >> tmp;
				tmp_vec.push_back(tmp);
			}
		}
		ss >> y[row];
		num_of_y[y[row]]++;
		for(int i=0;i<5;i++) sum[y[row]][i]+=numbers[row][i];
		table.push_back(tmp_vec);
		tmp_vec.clear();
		row++;
	}
	
	int table_cols = table[0].size();
	cout << "训练文本行数：" << row << endl;
	
	double u[2][5];//每种标签（0,1）的均值，对应table的 0,2,9,10,11列 
	double theta[2][5];//方差 
	
	for(int i=0;i<2;i++){
		for(int j=0;j<5;j++){
			u[i][j] = sum[i][j]*1.0/num_of_y[i];
			theta[i][j]=0;
			for(int k=0;k<numOftrain;k++){
				theta[i][j]+=(numbers[k][j]-u[i][j])*(numbers[k][j]-u[i][j]);	
			}
			theta[i][j]/=(num_of_y[i]-1);
			theta[i][j] = sqrt(theta[i][j]);	
		} 
	}

	int TP=0,FN=0,FP=0,TN=0;
	ofstream result("2.txt",ios::out);
	double P[2]; 
	double num_of_line[5];
	int numOfvalidation=0;
	ifstream validation("test.txt",ios::in);
	ofstream tt2("tt4.txt",ios::out);
	getline(validation,line);//除掉第一行说明性文字 
	while(getline(validation,line)){
		if(line=="\n") continue; //避免出现空行		
		for(int i=0;i<line.length();i++){
			if(line[i]==',') line[i]=' ';
		}
		stringstream ss(line);
		string tmp;
		tmp_vec.clear();
		for(int i=0;i<dimen;i++){
			if(i==0){
				ss >> num_of_line[0];
			}
			else if(i==2){
				ss >> num_of_line[1];
			}
			else if(i==4){
				ss >> tmp;
				continue;
			}
			else if(i==10){
				ss >> num_of_line[2];
			}
			else if(i==11){
				ss >> num_of_line[3];
			}
			else if(i==12){
				ss >> num_of_line[4];
			}
			else{
				ss >> tmp;
				tmp_vec.push_back(tmp);
			}
		}
		//标签为0时该验证文本的概率，标签为1时该验证文本的概率。初始化为1 
		for(int i=0;i<2;i++) P[i]=1;
		//5种数字属性的概率相乘 
		for(int i=0;i<2;i++){
			for(int j=0;j<5;j++){
				P[i] *= (1/(sqrt(2*PI)*theta[i][j]))*exp(-(num_of_line[j]-u[i][j])*(num_of_line[j]-u[i][j])/(2*theta[i][j]*theta[i][j]));
			}			
		}
		tt2 << P[0] << "  "<<P[1] << " "; 
		//单词的概率		
		for(int j=0;j<table[0].size();j++){
			string s = tmp_vec[j];
			int s_cnt[2];
			for(int k=0;k<2;k++) s_cnt[k]=0;
			for(int p=0;p<numOftrain;p++){
				if(table[p][j]==s) s_cnt[y[p]]++;
			}
			for(int q=0;q<2;q++){
				P[q] *= ((s_cnt[q]+0.1)*1.0/(num_of_y[q]+0.1));
			}
		}		
		tt2 << P[0] << "  "<<P[1] << " "; 
		for(int i=0;i<2;i++){
			P[i]*=(num_of_y[i]*1.0/numOftrain);
		}
		tt2 << P[0] << "  "<<P[1] << endl; 
		if(P[0]>P[1]){
			result << "0" << endl;
//			if(yy==0) TN++;
//			else FN++;
		}
		else{
			result << "1" << endl;
//			if(yy==1) TP++;
//			else FP++;
		}
		numOfvalidation++;
	}
	cout<<"验证集行数："<< numOfvalidation << endl << endl;
	//输出四种评测指标 
//	cout<<"Accuracy:"<<Accuracy(TP,FN,FP,TN)<<endl;
//	cout<<"Recall:"<<Recall(TP,FN,FP,TN)<<endl;
//	cout<<"Precision:"<<Precision(TP,FN,FP,TN)<<endl;
//	cout<<"F1:"<<F1(TP,FN,FP,TN)<<endl;
	return 0;	
}
