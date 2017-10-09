function [y0] = workInTest(x_dict2,x_dict4,x_dict6,x_dict7,x_dict8,x_dict9,x_dict10,x_dict14,w,n2,num)
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
        %y0(1,r)
        s0 = 1/(1+exp(-y0(1,r)));
        if (s0 >= 0.5)
            y0(1,r) = 1;
        else
            y0(1,r) = 0;
        end
end

end

