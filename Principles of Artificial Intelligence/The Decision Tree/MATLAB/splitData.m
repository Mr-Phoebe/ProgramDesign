function [ subSet ] = splitData( data, axis, value )  
    [m,n] = size(data);%得到待划分数据的大小  
      
    subSet = data;  
    subSet(:,axis) = [];  
    k = 0;  
    for i = 1:m  
        if data(i,axis) ~= value  
            subSet(i-k,:) = [];  
            k = k+1;  
        end  
    end     
end  