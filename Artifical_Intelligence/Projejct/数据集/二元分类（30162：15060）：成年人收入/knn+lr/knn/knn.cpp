#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
//共有TRAIN_LINES个训练样本，TEST_LINES个测试样本, PRO_NUMS个属性（不算最后的income） 
//KNN中的参数K 
#define TRAIN_LINES 30162
#define TEST_LINES 15060
#define PRO_NUMS 8 
#define K 20
int trainData[35000][150];
int trainLabels[35000];
int testData[20000][150];
map<string,int> allData;
void initTable()
{
allData["State-gov"] = 1;  
allData["Self-emp-not-inc"] = 2;  
allData["Private"] = 3;  
allData["Federal-gov"] = 4;  
allData["Local-gov"] = 5;  
allData["Self-emp-inc"] = 6;  
allData["Without-pay"] = 7;  

allData["Bachelors"] = 8; 
allData["HS-grad"] = 9;   
allData["11th"] = 10;      
allData["Masters"] = 11;   
allData["9th"] = 12;       
allData["Some-college"] = 13;
allData["Assoc-acdm"] = 14;
allData["7th-8th"] = 15;   
allData["Doctorate"] = 16; 
allData["Assoc-voc"] = 17; 
allData["Prof-school"] = 18; 
allData["5th-6th"] = 19;   
allData["10th"] = 20;      
allData["Preschool"] = 21; 
allData["12th"] = 22;      
allData["1st-4th"] = 23; 

allData["Never-married"] = 24;      
allData["Married-civ-spouse"] = 25; 
allData["Divorced"] = 26;           
allData["Married-spouse-absent"] = 27;
allData["Separated"] = 28;          
allData["Married-AF-spouse"] = 29;  
allData["Widowed"] = 30; 

allData["Adm-clerical"] = 31;   
allData["Exec-managerial"] = 32;
allData["Handlers-cleaners"] = 33;
allData["Prof-specialty"] = 34; 
allData["Other-service"] = 35;  
allData["Sales"] = 36;          
allData["Transport-moving"] = 37; 
allData["Farming-fishing"] = 38;
allData["Machine-op-inspct"] = 39;
allData["Tech-support"] = 40;   
allData["Craft-repair"] = 41;   
allData["Protective-serv"] = 42;
allData["Armed-Forces"] = 43;   
allData["Priv-house-serv"] = 44;


allData["Not-in-family"] = 45; 
allData["Husband"] = 46;     
allData["Wife"] = 47;        
allData["Own-child"] = 48;   
allData["Unmarried"] = 49;   
allData["Other-relative"] = 50;

allData["White"] = 51;           
allData["Black"] = 52;           
allData["Asian-Pac-Islander"] = 53;
allData["Amer-Indian-Eskimo"] = 54;
allData["Other"] = 55; 


allData["Male"] = 56;
allData["Female"] = 57;

allData["United-States"] = 58;           
allData["Cuba"] = 59;                    
allData["Jamaica"] = 60;                 
allData["India"] = 61;                   
allData["Mexico"] = 62;                  
allData["Puerto-Rico"] = 63;             
allData["Honduras"] = 64;                
allData["England"] = 65;                 
allData["Canada"] = 66;                  
allData["Germany"] = 67;                 
allData["Iran"] = 68;                    
allData["Philippines"] = 69;             
allData["Poland"] = 70;                  
allData["Columbia"] = 71;                
allData["Cambodia"] = 72;                
allData["Thailand"] = 73;                
allData["Ecuador"] = 74;                 
allData["Laos"] = 75;                    
allData["Taiwan"] = 76;                  
allData["Haiti"] = 77;                   
allData["Portugal"] = 78;                
allData["Dominican-Republic"] = 79;      
allData["El-Salvador"] = 80;             
allData["France"] = 81;                  
allData["Guatemala"] = 82;               
allData["Italy"] = 83;                   
allData["China"] = 84;                   
allData["South"] = 85;                   
allData["Japan"] = 86;                   
allData["Yugoslavia"] = 87;              
allData["Peru"] = 88;                    
allData["Outlying-US(Guam-USVI-etc)"] = 89;
allData["Scotland"] = 90;                
allData["Trinadad&Tobago"] = 91;         
allData["Greece"] = 92;                  
allData["Nicaragua"] = 93;               
allData["Vietnam"] = 94;                 
allData["Hong"] = 95;                    
allData["Ireland"] = 96;                 
allData["Hungary"] = 97;                 
allData["Holand-Netherlands"] = 98;
}

void initArray()
{
	memset(trainData,0,sizeof(trainData));
	memset(testData,0,sizeof(testData));
	memset(trainLabels,0,sizeof(trainLabels));
}
struct DIS{
	double dis;
	int label;
};
bool cmp(DIS a,DIS b)
{
	return a.dis < b.dis;
}
ifstream Input;
ofstream Info;
string lineString;
bool first = true;
void readTrain()
{
	int lines = 1;
	Input.open("knn_train_data.txt");//读取文件
	Info.open("EveryLine.txt");
	while(getline(Input,lineString))
	{		
		if(first) {
			first = false;
			continue;
		} 
		stringstream ss;
		ss.clear(); 
		ss.str(lineString);
		for(int i = 1; i <= PRO_NUMS; i++)  
		{
			string temp;
			ss >> temp ;//读入每行的数据集内容的词汇
			int index = allData[temp];
			trainData[lines][index] = 1; //这行样本的对应下表的矩阵中值为1 
			Info<< index <<" ";
		}
		ss >> trainLabels[lines];
		Info <<  trainLabels[lines] <<endl;	
		lines ++;
		//读取完这行词汇了 
	}
	Info.close();
	Input.close();
}
void readTest()
{
	first = true;
	int lines = 1;
	Input.open("knn_test_data.txt");//读取文件
	Info.open("EveryLine2.txt");
	while(getline(Input,lineString))
	{		
		if(first) {
			first = false;
			continue;
		} 
		stringstream ss;
		ss.clear(); 
		ss.str(lineString);
		for(int i = 1; i <= PRO_NUMS; i++)  
		{
			string temp;
			ss >> temp ;//读入每行的数据集内容的词汇
			int index = allData[temp];
			testData[lines][index] = 1; //这行样本的对应下表的矩阵中值为1 
			Info<< index <<" ";
		}
		Info <<endl;
		lines++;
		//读取完这行词汇了,测试集就没有这个label值了 
	}
	Info.close();
	Input.close();
}
void process()
{
	Info.open("Probability.txt");
	for(int i = 1; i <= TEST_LINES ; i++)
	{
		cout<< i <<" ";
		double dis_yes = 0, dis_no = 0;
		DIS min_disBetweenPoints[TRAIN_LINES + 1];
		for(int j = 1; j <= TRAIN_LINES ; j++)
		{
			double dis = 0;
			for(int x = 1; x <= PRO_NUMS; x++)
			{
				double distance_pow = (trainData[j][x] - testData[i][x]) * (trainData[j][x] - testData[i][x]);
				dis += sqrt(distance_pow);
			}	
			min_disBetweenPoints[j - 1].dis = dis;
			min_disBetweenPoints[j - 1].label = trainLabels[j];
		}
		sort(min_disBetweenPoints , min_disBetweenPoints + TRAIN_LINES, cmp);
		//找出K个最近的点！ 
		double num = 0;
		for(int j = 0 ; j < K ; j++) 
		{
			if(min_disBetweenPoints[j].label == 1)  num = num + 1;
		} 
		cout<<  num / K <<endl;
		Info << num / K <<endl;
	}
	Info.close();
}
int main()
{
	initTable();
	initArray();
	readTrain();
	readTest();
	process();
}

