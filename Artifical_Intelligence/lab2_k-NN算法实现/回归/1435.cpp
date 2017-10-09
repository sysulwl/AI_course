//#include "stdafx.h"  
#include <iostream>   
#include <string>   
#include<fstream>  
#include<sstream> 
using namespace std;  
/*  学到的东西 
1.没想到还有形如 string(a, 1, a.length() )这种方便的函数自己从来使用过
2.原来C++还有方法可以读取csv文件，应该还可以读取其他很多类型的文件。 
3.file.good() 是按一个一个单元格来读取文件的 
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
读取CSV文件C#  
C# 读取CSV文件2009年06月25日 星期四 19:03方法一，纯文本方法，即把该文件当做文本文件读取  
int intColCount = 0;   
bool blnFlag = true;   
DataTable mydt = new DataTable("myTableName");  
DataColumn mydc;   
DataRow mydr;  
string strpath = ""; //cvs文件路径  
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
            dataGridView1.Columns[0].HeaderText = "编号";  
 */ 
   
