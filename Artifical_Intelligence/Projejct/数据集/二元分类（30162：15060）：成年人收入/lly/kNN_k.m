

n1 = 23786;
n2 = 15858;
num = 58;
k = 5;

m = fopen('train.csv');
data_train = zeros(n1,num+1);%�õ��ö��ŷָ�����Զ�Ӧ��ֵ
for i = 1:n1+1
    line = fgetl(m);
    if i > 1
        s = textscan(line,'%s','delimiter',',');
        data = [];
        for j = 1:length(s{1})
            data_train(i-1,j) = str2num(s{1}{j});
        end
    end
end

m = fopen('test.csv');
data_test = zeros(n2,num);%�õ��ö��ŷָ�����Զ�Ӧ��ֵ
for i = 1:n2+1
    line = fgetl(m);
    if i > 1
        s = textscan(line,'%s','delimiter',',');
        data = [];
        for j = 1:length(s{1})-1
            data_test(i-1,j) = str2num(s{1}{j});
        end
    end
end

share = zeros(n2,k);%�õ���share�е�һ�еĲ���Ԥ��ı�ǩ
for i = 1:n2
    knn = [];
    for j = 1:n1
        d = 0;
        for n = 1:num
            d = d + (data_test(i,n)-data_train(j,n))^2;
        end
        knn = [knn;d];
    end
    [knn1,b] = sort(knn);%�����о����С��������,��Ϊknn1,��ʹ��b��¼ԭλ��
    for n = 1:k
        share(i,n) = data_train(b(n),num+1);
    end
    share(i,1) = mode(share(i,:));%������
end

fid=fopen('news.txt','w');
 m = length(share);
 for i = 1 : m
        fprintf(fid, '%f', share(i,1)); 
     fprintf(fid, '\r\n');
 end
fclose(fid);