function [x_dict2,x_dict4,x_dict6,x_dict7,x_dict8,x_dict9,x_dict10,x_dict14,x_train,y_train] = readTrain(n1,num);
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
for i = 1:n1 + 1
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
x_dict2(1,:) = [];
x_train(1,n+1) = 1;
sx = size(x_dict2);
while(1)    
    i = i+1;
    if i > sx(1)
        break;
    end
    flag = 0;
    for j = 1:i-1
        if(strcmp(strtrim(x_dict2(i,:)),strtrim(x_dict2(j,:))))
            flag = 1;
            x_dict2(i,:)=[];
            sx = size(x_dict2);
            x_train(i,n+1) = j;
            i = i-1;
        end
        if (flag ==  1)
            break;
        end
        if flag == 0
            x_train(i,n+1) = i;
        end
    end
end

i = 1;%删除重复的单词,删除空格
n = 4;
x_dict4(1,:) = [];
x_train(1,n+1) = 1;
sx = size(x_dict4);
while(1)    
    i = i+1;
    if i > sx(1)
        break;
    end
    flag = 0;
    for j = 1:i-1
        if(strcmp(strtrim(x_dict4(i,:)),strtrim(x_dict4(j,:))))
            flag = 1;
            x_dict4(i,:)=[];
            sx = size(x_dict4);
            x_train(i,n+1) = j;
            i = i-1;
        end
        if (flag ==  1)
            break;
        end
        if flag == 0
            x_train(i,n+1) = i;
        end
    end
end

i = 1;%删除重复的单词,删除空格
n = 6;
x_dict6(1,:) = [];
x_train(1,n+1) = 1;
sx = size(x_dict6);
while(1)    
    i = i+1;
    if i > sx(1)
        break;
    end
    flag = 0;
    for j = 1:i-1
        if(strcmp(strtrim(x_dict6(i,:)),strtrim(x_dict6(j,:))))
            flag = 1;
            x_dict6(i,:)=[];
            sx = size(x_dict6);
            x_train(i,n+1) = j;
            i = i-1;
        end
        if (flag ==  1)
            break;
        end
        if flag == 0
            x_train(i,n+1) = i;
        end
    end
end

i = 1;%删除重复的单词,删除空格
n = 7;
x_dict7(1,:) = [];
x_train(1,n+1) = 1;
sx = size(x_dict7);
while(1)    
    i = i+1;
    if i > sx(1)
        break;
    end
    flag = 0;
    for j = 1:i-1
        if(strcmp(strtrim(x_dict7(i,:)),strtrim(x_dict7(j,:))))
            flag = 1;
            x_dict7(i,:)=[];
            sx = size(x_dict7);
            x_train(i,n+1) = j;
            i = i-1;
        end
        if (flag ==  1)
            break;
        end
        if flag == 0
            x_train(i,n+1) = i;
        end
    end
end

i = 1;%删除重复的单词,删除空格
n = 8;
x_dict8(1,:) = [];
x_train(1,n+1) = 1;
sx = size(x_dict8);
while(1)    
    i = i+1;
    if i > sx(1)
        break;
    end
    flag = 0;
    for j = 1:i-1
        if(strcmp(strtrim(x_dict8(i,:)),strtrim(x_dict8(j,:))))
            flag = 1;
            x_dict8(i,:)=[];
            sx = size(x_dict8);
            x_train(i,n+1) = j;
            i = i-1;
        end
        if (flag ==  1)
            break;
        end
        if flag == 0
            x_train(i,n+1) = i;
        end
    end
end

i = 1;%删除重复的单词,删除空格
n = 9;
x_dict9(1,:) = [];
x_train(1,n+1) = 1;
sx = size(x_dict9);
while(1)    
    i = i+1;
    if i > sx(1)
        break;
    end
    flag = 0;
    for j = 1:i-1
        if(strcmp(strtrim(x_dict9(i,:)),strtrim(x_dict9(j,:))))
            flag = 1;
            x_dict9(i,:)=[];
            sx = size(x_dict9);
            x_train(i,n+1) = j;
            i = i-1;
        end
        if (flag ==  1)
            break;
        end
        if flag == 0
            x_train(i,n+1) = i;
        end
    end
end

i = 1;%删除重复的单词,删除空格
n = 10;
x_dict10(1,:) = [];
x_train(1,n+1) = 1;
sx = size(x_dict10);
while(1)    
    i = i+1;
    if i > sx(1)
        break;
    end
    flag = 0;
    for j = 1:i-1
        if(strcmp(strtrim(x_dict10(i,:)),strtrim(x_dict10(j,:))))
            flag = 1;
            x_dict10(i,:)=[];
            sx = size(x_dict10);
            x_train(i,n+1) = j;
            i = i-1;
        end
        if (flag ==  1)
            break;
        end
        if flag == 0
            x_train(i,n+1) = i;
        end
    end
end

i = 1;%删除重复的单词,删除空格
n = 14;
x_dict14(1,:) = [];
x_train(1,n+1) = 1;
sx = size(x_dict14);
while(1)    
    i = i+1;
    if i > sx(1)
        break;
    end
    flag = 0;
    for j = 1:i-1
        if(strcmp(strtrim(x_dict14(i,:)),strtrim(x_dict14(j,:))))
            flag = 1;
            x_dict14(i,:)=[];
            sx = size(x_dict14);
            x_train(i,n+1) = j;
            i = i-1;
        end
        if (flag ==  1)
            break;
        end
        if flag == 0
            x_train(i,n+1) = i;
        end
    end
end

end

