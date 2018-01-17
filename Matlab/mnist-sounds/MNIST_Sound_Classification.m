%  MNIST Sound Classification
% 
%  Data information:
% 
% We have a dataset of 8800 spoken digits, encoded as a timeseries of 13 Mel-frequency cepstral coefficients [1].
%
% Training set:
%   * Each block delimited by an empty line corresponds to one analysis frame which consist of 4-93 lines of 13 MEL coefficients
%   * The first of 330 samples are spoken by males, the next 330 are spoken by females
%   * Labeling is done by enumeration, block 1-660 corresponds to the digit 0, 61-1320 to the digit 1, etc.
%   * In summary we have 6600 training data samples
% 
% Test set:
%   * Same as the training set, with only 220 samples for each digit, the first 110 are spoken by males, the next 110 by females
%   * In summary we have 2200 test data samples
% 
% Data source [2]
% 
% [1] https://en.wikipedia.org/wiki/Mel-frequency_cepstrum
% [2] http://archive.ics.uci.edu/ml/datasets/Spoken+Arabic+Digit


%% read the text files with empty lines as delimiter
training_data_raw = from_text_file('Train_Arabic_Digits.txt');
test_data_raw = from_text_file('Test_Arabic_Digits.txt');
fprintf('> Read data...\n');
%% now we have 6600/2200 cells with [13xlines] matrices,
% with min(lines) = 4 and max(lines) = 93

% we pad every sample with zeros until it reaches length 93
training_data_raw = add_padding(training_data_raw);
test_data_raw = add_padding(test_data_raw);
fprintf('> Added padding...\n');
%% now we flatten the feature space so every cell has 13*93 features

training_data = flatten_dataset(training_data_raw);
test_data = flatten_dataset(test_data_raw);
fprintf('> Flattened dataset...\n');
%% now we have to create the class labels

training_data_targets = reshape([ repmat(0, 660, 1) ...
                                  repmat(1, 660, 1) ...
                                  repmat(2, 660, 1) ...
                                  repmat(3, 660, 1) ...
                                  repmat(4, 660, 1) ...
                                  repmat(5, 660, 1) ...
                                  repmat(6, 660, 1) ...
                                  repmat(7, 660, 1) ...
                                  repmat(8, 660, 1) ...
                                  repmat(9, 660, 1) ...
                                ], 660*10, 1);

test_data_targets = reshape([ repmat(0, 220, 1) ...
                              repmat(1, 220, 1) ...
                              repmat(2, 220, 1) ...
                              repmat(3, 220, 1) ...
                              repmat(4, 220, 1) ...
                              repmat(5, 220, 1) ...
                              repmat(6, 220, 1) ...
                              repmat(7, 220, 1) ...
                              repmat(8, 220, 1) ...
                              repmat(9, 220, 1) ...
                            ], 220*10, 1);
fprintf('> Created target labels...\n');
%% now we can start to classify with KNN
%                                                                K
classifier = fitcknn(training_data, training_data_targets, 'NumNeighbors', 10);
fprintf('> Initialized classifier, starting the prediction (this may take some time)\n');
prediction_labels = predict(classifier, test_data);
% 
% %% would love to use 'classperf', but it needs the Bioinformatic Toolbox
% % which I don't have - calculating accuracy by hand
accuracy = calculate_accuracy(test_data_targets, prediction_labels);
% 
fprintf('> KNN test model accuary: %f\n', accuracy);

fprintf('\n> Some examples from the test set:\n\n');

test_classifier_range(classifier, test_data, 1, 20, 0);
test_classifier_range(classifier, test_data, 240, 260, 1);
test_classifier_range(classifier, test_data, 460, 480, 2);
test_classifier_range(classifier, test_data, 690, 710, 3);
test_classifier_range(classifier, test_data, 900, 920, 4);
test_classifier_range(classifier, test_data, 1150, 1170, 5);
test_classifier_range(classifier, test_data, 1350, 1370, 6);
test_classifier_range(classifier, test_data, 1600, 1620, 7);
test_classifier_range(classifier, test_data, 1780, 1800, 8);
test_classifier_range(classifier, test_data, 1980, 2000, 9);

function dataset_raw = from_text_file(filepath)
    text_data = textread(filepath,'%s','delimiter','\n');
    if strcmp(filepath, 'Train_Arabic_Digits.txt') == 1
        dataset_raw = cell(6600,1);
    else 
        dataset_raw = cell(2200,1);
    end
    sample_ix = 1;
    for k=1:numel(text_data)
        line = sscanf(text_data{k},'%f');
        if isempty(line)
            sample_ix = sample_ix + 1;
        else
            dataset_raw{sample_ix} = [dataset_raw{sample_ix}, line];
        end
    end
end

function dataset = add_padding(dataset)

    padding = repmat(0., 13, 1);

    for i = 1:length(dataset)
        while length(dataset{i}) ~= 93
            dataset{i} = [dataset{i}, padding];
        end
    end

end

function non_cell_dataset = flatten_dataset(dataset)
    non_cell_dataset = zeros(length(dataset), 13*93);
    
    for i = 1:length(dataset)
        non_cell_dataset(i, :) = reshape(dataset{i}, 1, 13*93);
    end
    
end 

function accuracy = calculate_accuracy(truth, prediction)

    delta = truth - prediction;
    bad_prediction_count = 0.;
    for i = 1:numel(delta)
        if delta(i) ~= 0
            bad_prediction_count = bad_prediction_count + 1;
        end
    end
    fprintf('> Classified %d samples wrong out of %d\n', bad_prediction_count, length(delta));
    accuracy = 100. - bad_prediction_count / length(delta);
end

function [] = test_classifier_range(classifier, data, start, finish, should_be)
    
    misclassified = 0;
    for i = start:finish
        prediction = predict(classifier, data(i, :));
        if prediction == should_be
    %        fprintf('Correctly classified %d\n', prediction);
        else
            misclassified = misclassified + 1;
    %        fprintf('Misclassified %d, should be %d\n', prediction, shouldBe);
        end
    end
    
    fprintf('> Classified %d samples correctly out of %d for class %d\n', finish - start - misclassified, finish - start, should_be);
    
end
