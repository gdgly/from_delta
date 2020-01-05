function [xhatplusError, xhatSmoothError, PKalmanElements, PSmootherElements, MeasResidual, PminusArr] = Kalman(SystemModel)
F = SystemModel.F;
H = SystemModel.H;
QFilter = SystemModel.QFilter;
QReal = SystemModel.QReal;
R = SystemModel.R;
x = SystemModel.x;
N = SystemModel.N;
nx = length(x); % number of states
ny = size(R, 1); % number of measurements
Pplus = 1000 * eye(nx); % initial covariance
xhatplus = x + sqrt(diag(Pplus)); % initial state estimate
xArr = zeros(nx, N); % allocate memory for arrays
PplusArr = zeros(nx, nx, N);
PminusArr = zeros(nx, nx, N);
xhatminusArr = zeros(nx, N);
xhatplusArr = zeros(nx, N);
xhatplusError = zeros(nx, N);
PKalmanElements = zeros(nx, N);
JArr = zeros(nx, nx, N);
JInvArr = zeros(nx, nx, N);
KArr = zeros(nx, N);
yArr = zeros(ny, N);
FArr = zeros(nx, nx, N);
HArr = zeros(N, nx);
SArr = zeros(ny, N);
MeasResidual = zeros(ny, N);
Inx = eye(nx);
for k = 1 : N
    % System simulation
    FArr(:, :, k) = F;
    HArr(k, :) = H;
    x = F * x + sqrt(QReal) * randn(nx, 1);
    y = H * x + sqrt(R) * randn;
    % Standard forward Kalman filter
    Pminus = F * Pplus * F' + QFilter;
    K = Pminus * H' / (H * Pminus * H' + R);
    xhatminus = F * xhatplus;
    xhatplus = xhatminus + K * (y - H * xhatminus);
    Pplus = Pminus - K * H * Pminus;
    % Save data in arrays
    xArr(:, k) = x;
    yArr(:, k) = y;
    PminusArr(:, :, k) = Pminus;
    PplusArr(:, :, k) = Pplus;
    PKalmanElements(1, k) = Pplus(1, 1);
    PKalmanElements(2, k) = Pplus(2, 2);
    xhatminusArr(:, k) = xhatminus;
    xhatplusArr(:, k) = xhatplus;
    xhatplusError(:, k) = x - xhatplus;
    JArr(:, :, k) = Inx - K * H;
    JInvArr(:, :, k) = Inx / (Inx - K * H);
    KArr(:, k) = K;
    SArr(:, k) = H * Pminus * H' + R;
    MeasResidual(:, k) = y - H * xhatminus;
end
%Kalman smoother
xhatSmooth = xhatplus;
PSmooth = Pplus;
xhatSmoothArr = zeros(nx, N);
xhatSmoothError = zeros(nx, N);
xhatSmoothArr(:, N) = xhatSmooth;
xhatSmoothError(:, N) = xArr(:, N) - xhatSmooth;
KSmootherArr = zeros(nx, nx, N-1);
PSmootherElements = zeros(nx, N);
PSmootherElements(:, N) = PKalmanElements(:, N);
for k = N-1 : -1 : 1
    K = PplusArr(:, :, k) * F' / PminusArr(:, :, k+1);
    PSmooth = PplusArr(:, :, k) - K * (PminusArr(:, :, k+1) - PSmooth) * K';
    xhatSmooth = xhatplusArr(: ,k) + K * (xhatSmooth - xhatminusArr(:, k+1));
    % Save data in arrays
    xhatSmoothArr(: ,k) = xhatSmooth;
    xhatSmoothError(:, k) = xArr(:, k) - xhatSmooth;
    KSmootherArr(:, :, k) = K;
    PSmootherElements(1, k) = PSmooth(1, 1);
    PSmootherElements(2, k) = PSmooth(2, 2);
end
return