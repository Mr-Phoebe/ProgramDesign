%% 选择信息增益最大的特征  
function [ bestFeature ] = chooseBestFeature( data )  
global bestFeat
    [m,n] = size(data);% 得到数据集的大小  
      
    % 统计特征的个数  
    numOfFeatures = n-1;%最后一列是类别  
    % 原始的熵  
    baseEntropy = calEntropy(data);  
      
    bestInfoGain = 0;%初始化信息增益  
    bestFeature = 0;% 初始化最佳的特征位  
      
    % 挑选最佳的特征位  
    for j = 1:numOfFeatures  
        featureTemp = unique(data(:,j));  
        numF = length(featureTemp);%属性的个数  
        newEntropy = 0;%划分之后的熵  
        for i = 1:numF  
            subSet = splitData(data, j, featureTemp(i,:));  
            [m_1, n_1] = size(subSet);  
            prob = m_1./m;  
            newEntropy = newEntropy + prob * calEntropy(subSet);  
        end  
          
        %计算增益  
        infoGain = baseEntropy - newEntropy;  
          
        if infoGain > bestInfoGain  
            bestInfoGain = infoGain;  
            bestFeature = j;  
        end  
    end  
end  