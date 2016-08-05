%% Decision Tree  
% ID3  
clear all;clc;
global besttmp
global subtree
besttmp=[];
%导入数据  
featnum=2;
list_org=importdata('badges.org');
list=char(list_org);
[total_m,total_n]=size(list);
data=zeros(total_m,featnum+1);
badges=list(:,1);
names=list(:,3:total_n);
for i=1:total_m
    if list(i,1)=='+'
        data(i,featnum+1)=1;
    else
        data(i,featnum+1)=0;
    end
    if mod(double(names(i,1)),2) == 1 %%%如果首字母为A、C、E等奇数位的字母,则特征为1,否则特征为0
        data(i,1)=1;
    else
        data(i,1)=0;
    end
    if mod(double(names(i,2)),2) == 1 %%%如果第二位字母为a/c/e等奇数位的字母,则特征为1,否则特征为0
        data(i,2)=1;
    else
        data(i,2)=0;
    end
end
train_num=150;
test_num=total_m-train_num;
traindata=data(1:train_num,:);
testdata=data(train_num+1:end,:);

% 生成决策树  
createTree(traindata);
%test
e_y=testdata(:,2);
correct=sum(e_y==testdata(:,end))
corrate=correct/test_num