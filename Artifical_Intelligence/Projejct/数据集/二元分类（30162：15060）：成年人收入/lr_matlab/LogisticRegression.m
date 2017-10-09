function [w,times] = LogisticRegression(x,y)
%x为训练集中的特征向量，y为训练集的结果
%逻辑回归方法找出最终的权重系数
v = 0.00000000001;%学习速率
%v = 2;
max_time = 100;
sizex = size(x);
w0 = ones(1,sizex(2));%记录下一次迭代的权重
w = ones(1,sizex(2));%最终权重
flag = 0;%何时停止迭代
times = 0;%迭代次数
while (flag == 0)
    times
    %if times<=100
    %   v = 1/times;
    %end
    s = zeros(1,sizex(1));%初始化权重分数
    err = zeros(1,sizex(2));%初始化交叉熵误差的梯度
    nozeronum = 0;%梯度不为0的维度的个数
    times = times + 1;
    w1 = w0;%记录这一次迭代的权重
    for r = 1:sizex(1)%计算权重
        for c = 1:sizex(2)
            s(1,r) = s(1,r) + x(r,c)*w1(1,c);
        end
    end 
    for c = 1:sizex(2)%更新每一维的梯度
        for r = 1:sizex(1)
            err(1,c) = err(1,c)+(1/(1+exp(-s(1,r)))-y(r,1))*x(r,c);
        end      
        if (err(1,c) ~= 0)
            w0(1,c) = w1(1,c) - v * err(1,c);
            nozeronum = nozeronum + 1;
        end
    end
    if nozeronum == 0 || times == max_time
        w = w1;
        flag = 1;
    else
        w = w0;
    end
end
end

