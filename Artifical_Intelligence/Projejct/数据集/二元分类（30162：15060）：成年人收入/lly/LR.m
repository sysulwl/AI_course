 clc;clear;
n1 = 30162;%n1为训练集样本数
n2 = 15060;%n2为测试集样本数
num = 14;
%得到训练集的w和每个数据的结果并生成矩阵
%m = csvread('train.csv');

m = fopen('train.csv');
x_train = zeros(n1,num+1);%得到用逗号分割的属性对应的值
y_train = zeros(n1,1);
x_dict2 = [];
x_dict4 = [];
x_dict6 = [];
x_dict7 = [];
x_dict8 = [];
x_dict9 = [];
x_dict10 = [];
x_dict14 = [];
x_train(:,1) = ones(n1,1);
for i = 1:n1+1
    line = fgetl(m);
    if i > 1
        s = textscan(line,'%s','delimiter',',');
        data = [];
        for j = 1:length(s{1})
            if j == 1 || j == 3 ||j == 5 || j == 11 ||j == 12 ||j == 13
                x_train(i-1,j+1) = str2num(s{1}{j});
            elseif j == 2
                x_dict2 = str2mat(x_dict2,s{1}{j});
            elseif j == 4
                x_dict4 = str2mat(x_dict4,s{1}{j});
            elseif j == 6
                x_dict6 = str2mat(x_dict6,s{1}{j});
            elseif j == 7
                x_dict7 = str2mat(x_dict7,s{1}{j});
            elseif j == 8
                x_dict8 = str2mat(x_dict8,s{1}{j});
            elseif j == 9
                x_dict9 = str2mat(x_dict9,s{1}{j});
            elseif j == 10
                x_dict10 = str2mat(x_dict10,s{1}{j});
            elseif j == 14
                x_dict14 = str2mat(x_dict14,s{1}{j});
            else
                y_train(i-1,1) = str2num(s{1}{j});
            end
        end
    end
end

i = 1;%删除重复的单词,删除空格
n = 2;
d = 1;
x_dict2(1,:) = [];
x_train(1,n+1) = 1;
sx = size(x_dict2);
while(1)    
    i = i+1;
    d = d+1;
    if i > sx(1)
        break;
    end
    flag = 0;
    for j = 1:i-1
        if(strcmp(strtrim(x_dict2(i,:)),strtrim(x_dict2(j,:))))
            flag = 1;
            x_dict2(i,:)=[];
            sx = size(x_dict2);
            x_train(d,n+1) = j;
            i = i-1;
        end
        if (flag ==  1)
            break;
        end
        if flag == 0
            x_train(d,n+1) = i;
        end
    end
end

i = 1;%删除重复的单词,删除空格
n = 4;
d = 1;
x_dict4(1,:) = [];
x_train(1,n+1) = 1;
sx = size(x_dict4);
while(1)    
    i = i+1;
    d = d+1;
    if i > sx(1)
        break;
    end
    flag = 0;
    for j = 1:i-1
        if(strcmp(strtrim(x_dict4(i,:)),strtrim(x_dict4(j,:))))
            flag = 1;
            x_dict4(i,:)=[];
            sx = size(x_dict4);
            x_train(d,n+1) = j;
            i = i-1;
        end
        if (flag ==  1)
            break;
        end
        if flag == 0
            x_train(d,n+1) = i;
        end
    end
end

i = 1;%删除重复的单词,删除空格
n = 6;
d = 1;
x_dict6(1,:) = [];
x_train(1,n+1) = 1;
sx = size(x_dict6);
while(1)    
    i = i+1;
    d = d+1;
    if i > sx(1)
        break;
    end
    flag = 0;
    for j = 1:i-1
        if(strcmp(strtrim(x_dict6(i,:)),strtrim(x_dict6(j,:))))
            flag = 1;
            x_dict6(i,:)=[];
            sx = size(x_dict6);
            x_train(d,n+1) = j;
            i = i-1;
        end
        if (flag ==  1)
            break;
        end
        if flag == 0
            x_train(d,n+1) = i;
        end
    end
end

i = 1;%删除重复的单词,删除空格
n = 7;
d = 1;
x_dict7(1,:) = [];
x_train(1,n+1) = 1;
sx = size(x_dict7);
while(1)    
    i = i+1;
    d = d+1;
    if i > sx(1)
        break;
    end
    flag = 0;
    for j = 1:i-1
        if(strcmp(strtrim(x_dict7(i,:)),strtrim(x_dict7(j,:))))
            flag = 1;
            x_dict7(i,:)=[];
            sx = size(x_dict7);
            x_train(d,n+1) = j;
            i = i-1;
        end
        if (flag ==  1)
            break;
        end
        if flag == 0
            x_train(d,n+1) = i;
        end
    end
end

i = 1;%删除重复的单词,删除空格
n = 8;
d = 1;
x_dict8(1,:) = [];
x_train(1,n+1) = 1;
sx = size(x_dict8);
while(1)    
    i = i+1;
    d = d+1;
    if i > sx(1)
        break;
    end
    flag = 0;
    for j = 1:i-1
        if(strcmp(strtrim(x_dict8(i,:)),strtrim(x_dict8(j,:))))
            flag = 1;
            x_dict8(i,:)=[];
            sx = size(x_dict8);
            x_train(d,n+1) = j;
            i = i-1;
        end
        if (flag ==  1)
            break;
        end
        if flag == 0
            x_train(d,n+1) = i;
        end
    end
end

i = 1;%删除重复的单词,删除空格
n = 9;
d = 1;
x_dict9(1,:) = [];
x_train(1,n+1) = 1;
sx = size(x_dict9);
while(1)    
    i = i+1;
    d = d+1;
    if i > sx(1)
        break;
    end
    flag = 0;
    for j = 1:i-1
        if(strcmp(strtrim(x_dict9(i,:)),strtrim(x_dict9(j,:))))
            flag = 1;
            x_dict9(i,:)=[];
            sx = size(x_dict9);
            x_train(d,n+1) = j;
            i = i-1;
        end
        if (flag ==  1)
            break;
        end
        if flag == 0
            x_train(d,n+1) = i;
        end
    end
end

i = 1;%删除重复的单词,删除空格
n = 10;
d = 1;
x_dict10(1,:) = [];
x_train(1,n+1) = 1;
sx = size(x_dict10);
while(1)    
    i = i+1;
    d = d+1;
    if i > sx(1)
        break;
    end
    flag = 0;
    for j = 1:i-1
        if(strcmp(strtrim(x_dict10(i,:)),strtrim(x_dict10(j,:))))
            flag = 1;
            x_dict10(i,:)=[];
            sx = size(x_dict10);
            x_train(d,n+1) = j;
            i = i-1;
        end
        if (flag ==  1)
            break;
        end
        if flag == 0
            x_train(d,n+1) = i;
        end
    end
end

i = 1;%删除重复的单词,删除空格
n = 14;
d = 1;
x_dict14(1,:) = [];
x_train(1,n+1) = 1;
sx = size(x_dict14);
while(1)    
    i = i+1;
    d = d+1;
    if i > sx(1)
        break;
    end
    flag = 0;
    for j = 1:i-1
        if(strcmp(strtrim(x_dict14(i,:)),strtrim(x_dict14(j,:))))
            flag = 1;
            x_dict14(i,:)=[];
            sx = size(x_dict14);
            x_train(d,n+1) = j;
            i = i-1;
        end
        if (flag ==  1)
            break;
        end
        if flag == 0
            x_train(d,n+1) = i;
        end
    end
end


%[x_train,y_train] = getmat(m);
%找到权重系数和迭代次数
[w,times] = LogisticRegression(x_train,y_train);
%得到测试集的w和每个样本的预测并生成矩阵
%m = csvread('test.csv');
m = fopen('test.csv');
x_test = zeros(n2,num+1);%得到用逗号分割的属性对应的值
x_test(:,1) = ones(n2,1);
for i = 1:n2+1
    line = fgetl(m);
    if i > 1
        data = [];
        s = textscan(line,'%s','delimiter',',');
        for j = 1:length(s{1})
            if j == 1 || j == 3 ||j == 5 || j == 11 ||j == 12 ||j == 13
                x_test(i-1,j+1) = str2num(s{1}{j});
            elseif j == 2
                sx = size(x_dict2);
                flag = 0;
                for k = 1:sx(1)
                    if strcmp(strtrim(x_dict2(k,:)),s{1}{j})
                        x_test(i-1,j+1) = k;
                        flag = 1;
                    end
                end
                if flag == 0
                    x_test(i-1,j+1) = 0;
                end
            elseif j == 4
                sx = size(x_dict4);
                flag = 0;
                for k = 1:sx(1)
                    if strcmp(strtrim(x_dict4(k,:)),s{1}{j})
                        x_test(i-1,j+1) = k;
                        flag = 1;
                    end
                end
                if flag == 0
                    x_test(i-1,j+1) = 0;
                end
            elseif j == 6
                sx = size(x_dict6);
                flag = 0;
                for k = 1:sx(1)
                    if strcmp(strtrim(x_dict6(k,:)),s{1}{j})
                        x_test(i-1,j+1) = k;
                        flag = 1;
                    end
                end
                if flag == 0
                    x_test(i-1,j+1) = 0;
                end
            elseif j == 7
                sx = size(x_dict7);
                flag = 0;
                for k = 1:sx(1)
                    if strcmp(strtrim(x_dict7(k,:)),s{1}{j})
                        x_test(i-1,j+1) = k;
                        flag = 1;
                    end
                end
                if flag == 0
                    x_test(i-1,j+1) = 0;
                end
            elseif j == 8
                sx = size(x_dict8);
                flag = 0;
                for k = 1:sx(1)
                    if strcmp(strtrim(x_dict8(k,:)),s{1}{j})
                        x_test(i-1,j+1) = k;
                        flag = 1;
                    end
                end
                if flag == 0
                    x_test(i-1,j+1) = 0;
                end
            elseif j == 9
                sx = size(x_dict9);
                flag = 0;
                for k = 1:sx(1)
                    if strcmp(strtrim(x_dict9(k,:)),s{1}{j})
                        x_test(i-1,j+1) = k;
                        flag = 1;
                    end
                end
                if flag == 0
                    x_test(i-1,j+1) = 0;
                end
            elseif j == 10
                sx = size(x_dict10);
                flag = 0;
                for k = 1:sx(1)
                    if strcmp(strtrim(x_dict10(k,:)),s{1}{j})
                        x_test(i-1,j+1) = k;
                        flag = 1;
                    end
                end
                if flag == 0
                    x_test(i-1,j+1) = 0;
                end
            elseif j == 14
                sx = size(x_dict14);
                flag = 0;
                for k = 1:sx(1)
                    if strcmp(strtrim(x_dict14(k,:)),s{1}{j})
                        x_test(i-1,j+1) = k;
                        flag = 1;
                    end
                end
                if flag == 0
                    x_test(i-1,j+1) = 0;
                end
            end
        end
    end
end
%x_test(:,2:sizex0(2)+1) = m;
sizex = size(x_test);
%得到测试集的结果
y0 = zeros(1,sizex(1));
%s0 = zeros(1,sizex(1));
for r = 1:sizex(1)
    for c = 1:sizex(2)
        y0(1,r) = y0(1,r)+ w(1,c)*x_test(r,c);
    end
        s0 = 1/(1+exp(-y0(1,r)));
        if (s0 >= 0.5)
            y0(1,r) = 1;
        else
            y0(1,r) = 0;
        end
end

fid=fopen('001_2.txt','w');
 m = length(y0);
 for i = 1 : m
        fprintf(fid, '%d', y0(1,i)); 
     fprintf(fid, '\r\n');
 end
fclose(fid);
%比较预测结果和实际结果
%TP=0;
%TN=0;
%FN=0;
%FP=0;
%for r = 1:sizex(1)
%    if y0(1,r)==1
%        if y_test(r,1)==1
%            TP = TP+1;
%        else
%            FP = FP+1;
%        end
%    else
%        if y_test(r,1) == 1  
%            FN = FN+1;
%        else
%            TN = TN+1;
%        end
%    end
%end
%Acc = (TP+TN)/(TP+FN+FP+TN);
%Pre = TP/(TP+FP);
%Rec = TP/(TP+FN);
%F1 = Pre*Rec*2/(Pre+Rec);
%fprintf('TP=%d\n',TP);
%fprintf('TN=%d\n',TN);
%fprintf('FN=%d\n',FN);
%fprintf('FP=%d\n',FP);
%fprintf('times=%d\n',times);
%fprintf('Accuracy=%d\n',Acc);
%fprintf('Precision=%d\n',Pre);
%fprintf('Recall=%d\n',Rec);
%fprintf('F1=%d\n',F1);