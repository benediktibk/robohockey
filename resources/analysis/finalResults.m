rawData = readInLidarData('../testfiles/lidar_wall.txt');
[highPass, lowPass] = finalFilter(rawData);

plot(rawData, 'b');
hold on;
plot(highPass, 'g');
plot(lowPass, 'r');
legend('raw data', 'high pass part', 'low pass part');