clear
% Compare performance of Kalman and UFIR estimators for filtering and smoothing
if ~exist('QFactorArr', 'var') || isempty(QFactorArr)
    QFactorArr = 1; % Factors by which to change the modeled Q(2,2) from the true Q(2,2)
end
if ~exist('R', 'var') || isempty(R)
    R = 0.833^2; % measurement noise covariance
end
if ~exist('Nopt', 'var') || isempty(Nopt)
    Nopt = 12; % Length of UFIR measurement window - The actual default value of Nopt is 10, but let's use 12 to simulated uncertainty
end

close all
SystemModel.dt = 0.1; % time step size
SystemModel.F = [1 SystemModel.dt; 0 1]; % state transition matrix
SystemModel.H = [1 0]; % measurement matrix
SystemModel.QReal = [0 0; 0 1^2]; % process noise covariance
SystemModel.QFilter = QFactorArr * SystemModel.QReal;
SystemModel.R = R; % measurement noise covariance
SystemModel.x = [1; 1]; % initial state
SystemModel.N = 1000; % number of time steps
disp('Beginning filter simulations');
%Kalman
[xhatplusError, xhatSmoothError, PKalman, PSmoother] = Kalman(SystemModel);
% UFIR filter
[xhatFIRfilterError, PFIRFilter, NArrFIRFilter] = FIR(SystemModel, false, Nopt);
% FIR smoother
[xhatFIRsmootherError, PFIRSmoother, NArrFIRSmoother] = FIR(SystemModel, true, Nopt);





