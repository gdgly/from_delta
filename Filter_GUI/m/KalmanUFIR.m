clear
% Compare performance of Kalman and UFIR estimators for filtering and smoothing
if ~exist('nMonte', 'var') || isempty(nMonte)
    nMonte = 20; % Number of Monte Carlo simulations
end
if ~exist('QFactorArr', 'var') || isempty(QFactorArr)
    QFactorArr = 1; % Factors by which to change the modeled Q(2,2) from the true Q(2,2)
end
if ~exist('R', 'var') || isempty(R)
    R = 0.833^2; % measurement noise covariance
end
if ~exist('Nopt', 'var') || isempty(Nopt)
    Nopt = 12; % Length of UFIR measurement window - The actual default value of Nopt is 10, but let's use 12 to simulated uncertainty
end
if ~exist('RandSeed', 'var') || isempty(RandSeed)
    RandSeed = round(sum(100*clock)); % Initialize the random number generator
end
close all
SystemModel.dt = 0.1; % time step size
SystemModel.F = [1 SystemModel.dt; 0 1]; % state transition matrix
SystemModel.H = [1 0]; % measurement matrix
SystemModel.QReal = [0 0; 0 1^2]; % process noise covariance
SystemModel.R = R; % measurement noise covariance
SystemModel.x = [1; 1]; % initial state
SystemModel.N = 500; % number of time steps
% Get Kalman and FIR filter and smoother results
NumQFactors = length(QFactorArr);
KFilterRMS = zeros(2, NumQFactors);
KSmootherRMS = zeros(2, NumQFactors);
FIRFilterRMS = zeros(2);
FIRSmootherRMS = zeros(2);
disp('Beginning filter simulations'); 
SystemModel.QFilter = QFactorArr * SystemModel.QReal;

for i = 1 : nMonte
    [xhatplusError, xhatSmoothError, PKalman, PSmoother] = Kalman(SystemModel);
    ErrorFilter(i, :, :) = xhatplusError;
    ErrorSmoother(i, :, :) = xhatSmoothError;
end

% FIR filter
for i = 1 : nMonte
    [xhatFIRError, PFIRFilter, NArrFIRFilter] = FIRSmoother(SystemModel, false, Nopt);
    ErrorFIRFilter(i, :, :) = xhatFIRError;
end
% FIR smoother
for i = 1 : nMonte
    [xhatFIRError, PFIRSmoother, NArrFIRSmoother] = FIRSmoother(SystemModel, true, Nopt);
    ErrorFIRSmoother(i, :, :) = xhatFIRError;
end



