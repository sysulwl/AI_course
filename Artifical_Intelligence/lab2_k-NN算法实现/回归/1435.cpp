//#include "stdafx.h"  
#include <iostream>   
#include <string>   
#include<fstream>  
#include<sstream> 
using namespace std;  
/*  ѧ���Ķ��� 
1.û�뵽�������� string(a, 1, a.length() )���ַ���ĺ����Լ�����ʹ�ù�
2.ԭ��C++���з������Զ�ȡcsv�ļ���Ӧ�û����Զ�ȡ�����ܶ����͵��ļ��� 
3.file.good() �ǰ�һ��һ����Ԫ������ȡ�ļ��� 
*/ 
int main(int argc, char* argv[])  
{  
   ifstream file ( "Dataset_train.csv" ); 
   ofstream file1("file1.txt");
   string value;  
   int i = 0;
  string line;
  while(getline(file,line)) {
  	stringstream ss;
	ss.clear();	
	ss.str(line);
  	string dict;
  	i++;
  	int j = 0;
  	while(ss>>dict)
  	{
  		j++;
  	    file1<<dict<<" ";
  	}
  	file1<<j<<endl<<i<<endl;
  }
}  
/* 
��ȡCSV�ļ�C#  
C# ��ȡCSV�ļ�2009��06��25�� ������ 19:03����һ�����ı����������Ѹ��ļ������ı��ļ���ȡ  
int intColCount = 0;   
bool blnFlag = true;   
DataTable mydt = new DataTable("myTableName");  
DataColumn mydc;   
DataRow mydr;  
string strpath = ""; //cvs�ļ�·��  
string strline;   
string [] aryline;  
System.IO.StreamReader mysr = new System.IO.StreamReader(strpath);  
while((strline = mysr.ReadLine()) != null)   
{   
	aryline = strline.Split(new char[]{','});  
	if (blnFlag)   
	{   
		blnFlag = false;   
		intColCount = aryline.Length;   
		for (int i = 0; i < aryline.Length; i++)   
		{   
			mydc = new DataColumn(aryline[i]);   
			mydt.Columns.Add(mydc);   
		}    
	}  
	mydr = mydt.NewRow();   
	for (int i = 0; i < intColCount; i++)   
	{   	 
		mydr[i] = aryline[i];   
	}   
mydt.Rows.Add(mydr);   
}    
  mydt.Rows.RemoveAt(0);  
            dataGridView1.DataSource = mydt.DefaultView;  
            dataGridView1.Columns[0].HeaderText = "���";  
 */ 
   
