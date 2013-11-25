function [ data ] = readInLidarData( fileName )

file = fopen(fileName);
rawData = textscan(file, '%d: %f');
data = cell2mat(rawData(:, 2))';

end

