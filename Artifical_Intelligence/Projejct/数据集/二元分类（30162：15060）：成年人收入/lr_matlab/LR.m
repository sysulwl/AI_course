 clc;clear;
n1 = 30162;%n1Ϊѵ����������
n2 = 15060;%n2Ϊ���Լ�������
num = 14;

display('begin!!!');
%�õ�ѵ������w��ÿ�����ݵĽ�������ɾ���
%m = csvread('train.csv');
[x_dict2,x_dict4,x_dict6,x_dict7,x_dict8,x_dict9,x_dict10,x_dict14,x_train,y_train] = readTrain(n1,num);
save myTrainnData x_dict2 x_dict4 x_dict6 x_dict7 x_dict8 x_dict9 x_dict10 x_dict14 x_train y_train
display('read train finished!!!');
%[x_train,y_train] = getmat(m);


%�ҵ�Ȩ��ϵ���͵�������
[w,times] = LogisticRegression(x_train,y_train);
%�õ����Լ���w��ÿ��������Ԥ�Ⲣ���ɾ���
display('find w finished!!!');

%m = csvread('test.csv');
[y0] = workInTest(x_dict2,x_dict4,x_dict6,x_dict7,x_dict8,x_dict9,x_dict10,x_dict14,w,n2,num);
% ���յõ����Լ��Ľ�� y0
display('test finished!!!');

fid=fopen('001_2.txt','w');
 m = length(y0);
 for i = 1 : m
     fprintf(fid, '%d', y0(1,i)); 
     fprintf(fid, '\r\n');
 end
fclose(fid);
%compare(y_test,y0);
