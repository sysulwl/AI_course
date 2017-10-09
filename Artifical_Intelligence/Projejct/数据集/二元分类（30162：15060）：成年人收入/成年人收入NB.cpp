#include<iostream>
#include<bits/stdc++.h> 
#define PI 3.1415926535898
#define DIMEN  14 //ά��,����dimen������
#define NUM_TRAIN  30162 //ѵ���ı�����
#define NUM_TEST  15060 //�����ı����� 
using namespace std;
string line;
vector<vector<string> > table; //���Ա��NUM_TRAIN*DIMEN-1, �� education-num��Ӧ education��������������education-num  
vector<string> tmpVec; 
int label[NUM_TRAIN];//label ��ǩ
int num_of_label[2];//��ǩΪ0��ѵ���ı��� ����ǩΪ1��ѵ���ı���
int table_cols ;
double sum[2][5]; //ÿ�ֱ�ǩ��0,1����ԭ�����ݼ���0��2��9��10��11�еĺͣ�respectively��
double numbers[NUM_TRAIN][5];
double u[2][5];//ÿ�ֱ�ǩ��0,1���ľ�ֵ����Ӧtable�� 0,2,9,10,11�� 
double theta[2][5];//���� 
double P[2]; 
double num_of_line[5];
int numOfValidation=0;
void readTrainFile()
{
	cout<<"��ȡѵ��������"<<endl; 
	ifstream trainFile("train.txt",ios::in);
	getline(trainFile,line);//������һ��˵�������� 
	for(int i=0;i<2;i++){
		for(int j=0;j<5;j++){
			sum[i][j]=0;
		}
	} 
	for(int i=0;i<2;i++) num_of_label[i]=0;
	int row=0;
	while(getline(trainFile,line)){
		if(line=="\n") continue; //������ֿ���
		for(int i=0;i<line.length();i++){
			if(line[i]==',') line[i]=' ';
		}
		stringstream ss(line);
		string tmp;
		double number;
		for(int i=0;i<DIMEN;i++){
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
				tmpVec.push_back(tmp);
			}
		}
		ss >> label[row];
		num_of_label[label[row]]++;
		for(int i=0;i<5;i++) sum[label[row]][i]+=numbers[row][i];
		table.push_back(tmpVec);
		tmpVec.clear();
		row++;
	}
	table_cols = table[0].size();
	cout << "��ȡ��ѵ���ı�" << endl;
		for(int i=0;i<2;i++)
		{
			for(int j=0;j<5;j++){
				u[i][j] = sum[i][j]*1.0/num_of_label[i];
				theta[i][j]=0;
				for(int k=0;k<NUM_TRAIN;k++)
				{
					theta[i][j]+=(numbers[k][j]-u[i][j])*(numbers[k][j]-u[i][j]);	
				}
				theta[i][j]/=(num_of_label[i]-1);
				theta[i][j] = sqrt(theta[i][j]);	
			} 
		}
}
void readTest()
{
	cout<<"��ʼ��ȡ��������"<<endl;
	ofstream result("result.txt",ios::out);
	ifstream Validation("test.txt",ios::in);
	ofstream tt2("tt4.txt",ios::out);
	getline(Validation,line);//������һ��˵�������� 
	while(getline(Validation,line))
	{
		if(line=="\n") continue; //������ֿ���		
		for(int i=0;i<line.length();i++){
			if(line[i]==',') line[i]=' ';
		}
		stringstream ss(line);
		string tmp;
		tmpVec.clear();
		for(int i=0;i<DIMEN;i++){
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
				tmpVec.push_back(tmp);
			}
		}
		//��ǩΪ0ʱ����֤�ı��ĸ��ʣ���ǩΪ1ʱ����֤�ı��ĸ��ʡ���ʼ��Ϊ1 
		for(int i=0;i<2;i++) P[i]=1;
		//5���������Եĸ������ 
		for(int i=0;i<2;i++){
			for(int j=0;j<5;j++){
				P[i] *= (1/(sqrt(2*PI)*theta[i][j]))*exp(-(num_of_line[j]-u[i][j])*(num_of_line[j]-u[i][j])/(2*theta[i][j]*theta[i][j]));
			}			
		}
		tt2 << P[0] << "  "<<P[1] << " "; 
		//���ʵĸ���		
		for(int j=0;j<table[0].size();j++)
		{
			string s = tmpVec[j];
			int s_cnt[2];
			for(int k=0;k<2;k++) s_cnt[k]=0;
			for(int p=0;p<NUM_TRAIN;p++){
				if(table[p][j]==s) s_cnt[label[p]]++;
			}
			for(int q=0;q<2;q++){
				P[q] *= ((s_cnt[q]+0.1)*1.0/(num_of_label[q]+0.1));
			}
		}		
		tt2 << P[0] << "  "<<P[1] << " "; 
		for(int i=0;i<2;i++){
			P[i]*=(num_of_label[i]*1.0/NUM_TRAIN);
		}
		tt2 << P[0] << "  "<<P[1] << endl; 
		if(P[0]>P[1]){
			result << "0" << endl;
		}
		else{
			result << "1" << endl;
		}
		numOfValidation++;
	}
	cout<<"��ȡ���������"<<endl; 
}
int main(){

	readTrainFile();
	readTest(); 
	return 0;	
}
