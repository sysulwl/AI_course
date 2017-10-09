 clc;clear;
n1 = 30162;%n1为训练集样本数
n2 = 15060;%n2为测试集样本数
num = 14;

display('begin!!!');
%得到训练集的w和每个数据的结果并生成矩阵
%m = csvread('train.csv');
[x_dict2,x_dict4,x_dict6,x_dict7,x_dict8,x_dict9,x_dict10,x_dict14,x_train,y_train] = readTrain(n1,num);
save myTrainnData x_dict2 x_dict4 x_dict6 x_dict7 x_dict8 x_dict9 x_dict10 x_dict14 x_train y_train
display('read train finished!!!');
%[x_train,y_train] = getmat(m);


%找到权重系数和迭代次数
[w,times] = LogisticRegression(x_train,y_train);
%得到测试集的w和每个样本的预测并生成矩阵
display('find w finished!!!');

%m = csvread('test.csv');
[y0] = workInTest(x_dict2,x_dict4,x_dict6,x_dict7,x_dict8,x_dict9,x_dict10,x_dict14,w,n2,num);
% 最终得到测试集的结果 y0
display('test finished!!!');

fid=fopen('001_2.txt','w');
 m = length(y0);
 for i = 1 : m
     fprintf(fid, '%d', y0(1,i)); 
     fprintf(fid, '\r\n');
 end
fclose(fid);
%compare(y_test,y0);
