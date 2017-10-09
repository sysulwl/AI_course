function [ ] = compare(y_test,y0);
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
end

