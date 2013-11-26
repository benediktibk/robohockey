function [ highPass, lowPass ] = finalFilter( rawData )

slightLowPassFilter = [1 16 81 256 81 16 1];
slightLowPassFilter = slightLowPassFilter/sum(abs(slightLowPassFilter));
highPassFilter = [-1 -2 -3 -2 -1 0 1 2 3 2 1];
highPassFilter = highPassFilter/sum(abs(highPassFilter));
lowPassFilter = [1 1 1 1 1];
lowPassFilter = lowPassFilter/sum(lowPassFilter);

dataSlightLowPass = applyLinearFilter(rawData, slightLowPassFilter);
lowPass = applyLinearFilter(dataSlightLowPass, lowPassFilter);
highPass = applyLinearFilter(dataSlightLowPass, highPassFilter);

end

