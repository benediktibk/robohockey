rawData = readInLidarData('../testfiles/lidar_wall.txt');
lowPassFilterOne = [1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1];
lowPassFilterOne = lowPassFilterOne/sum(lowPassFilterOne);
dataLowPassOne = applyLinearFilter(rawData, lowPassFilterOne);
lowPassFilterTwo = [1 2 3 4 5 6 7 8 9 8 7 6 5 4 3 2 1];
lowPassFilterTwo = lowPassFilterTwo/sum(lowPassFilterTwo);
dataLowPassTwo = applyLinearFilter(rawData, lowPassFilterTwo);

highPassFilterOne = [-1 0 1];
highPassFilterOne = highPassFilterOne/sum(abs(highPassFilterOne));
dataHighPassOne = applyLinearFilter(rawData, highPassFilterOne);
slightLowPass = [1 16 81 256 81 16 1];
slightLowPass = slightLowPass/sum(abs(slightLowPass));
dataSlightLowPass = applyLinearFilter(rawData, slightLowPass);
dataHighPassComplete = applyLinearFilter(dataSlightLowPass, highPassFilterOne);

highPassFilterTwo = [-1 0 0 0 1];
highPassFilterTwo = highPassFilterTwo/sum(abs(highPassFilterTwo));
dataHighPassTwo = applyLinearFilter(rawData, highPassFilterTwo);

highPassFilterThree = [-1 -2 -3 -2 -1 0 1 2 3 2 1];
highPassFilterThree = highPassFilterThree/sum(abs(highPassFilterThree));
dataHighPassThree = applyLinearFilter(rawData, highPassFilterThree);

plot(rawData, 'b');
hold on;
plot(dataLowPassOne, 'g');
plot(dataLowPassTwo, 'r');
plot(dataHighPassOne, 'm');
plot(dataHighPassComplete, 'r');
plot(dataHighPassTwo, 'y');
plot(dataHighPassThree, 'g');

figure;
plot(rawData, 'b');
hold on;
plot(dataLowPassOne + dataHighPassThree, 'g');

