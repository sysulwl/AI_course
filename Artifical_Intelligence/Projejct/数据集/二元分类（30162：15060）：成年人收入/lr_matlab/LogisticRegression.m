function [w,times] = LogisticRegression(x,y)
%xΪѵ�����е�����������yΪѵ�����Ľ��
%�߼��ع鷽���ҳ����յ�Ȩ��ϵ��
v = 0.00000000001;%ѧϰ����
%v = 2;
max_time = 100;
sizex = size(x);
w0 = ones(1,sizex(2));%��¼��һ�ε�����Ȩ��
w = ones(1,sizex(2));%����Ȩ��
flag = 0;%��ʱֹͣ����
times = 0;%��������
while (flag == 0)
    times
    %if times<=100
    %   v = 1/times;
    %end
    s = zeros(1,sizex(1));%��ʼ��Ȩ�ط���
    err = zeros(1,sizex(2));%��ʼ�������������ݶ�
    nozeronum = 0;%�ݶȲ�Ϊ0��ά�ȵĸ���
    times = times + 1;
    w1 = w0;%��¼��һ�ε�����Ȩ��
    for r = 1:sizex(1)%����Ȩ��
        for c = 1:sizex(2)
            s(1,r) = s(1,r) + x(r,c)*w1(1,c);
        end
    end 
    for c = 1:sizex(2)%����ÿһά���ݶ�
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

