function [ entropy ] = calEntropy( data )  
    [m,n] = size(data);  
      
    % 得到类别的项  
    label = data(:,n);  
      
    % 处理完的label  
    label_deal = unique(label);  
      
    numLabel = length(label_deal);  
    prob = zeros(numLabel,2);  
      
    % 统计标签  
    for i = 1:numLabel  
        prob(i,1) = label_deal(i,:);  
        for j = 1:m  
            if label(j,:) == label_deal(i,:)  
                prob(i,2) = prob(i,2)+1;  
            end  
        end  
    end  
      
    % 计算熵  
    prob(:,2) = prob(:,2)./m;  
    entropy = 0;  
    for i = 1:numLabel  
        entropy = entropy - prob(i,2) * log2(prob(i,2));  
    end  
end  