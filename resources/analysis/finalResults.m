rawData = readInLidarData('../testfiles/lidar_wall.txt');
[highPass, lowPass] = finalFilter(rawData);

rawDataShifted = zeros(1, 2 + size(rawData, 2));
rawDataShifted(3:2 + size(rawData, 2)) = rawData;

plot(rawDataShifted, 'b');
hold on;
plot(highPass, 'g');
plot(lowPass, 'r');
plot(highPass + lowPass, 'm');
legend('raw data', 'high pass part', 'low pass part', 'low and high pass parts added');