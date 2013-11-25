function [ result ] = applyLinearFilter( data, filter )

filterSize = size(filter, 2);
dataSize = size(data, 2);
halfFilterSize = int32(ceil(filterSize/2));
iterationStart = halfFilterSize + 1;
iterationEnd = dataSize - halfFilterSize;
result = zeros(1, dataSize);

for i = iterationStart:iterationEnd
    dataStart = i - halfFilterSize;
    dataEnd = dataStart + filterSize - 1;
    dataPart = data(1, dataStart:dataEnd);
    result(i) = dataPart*filter';
end

end

