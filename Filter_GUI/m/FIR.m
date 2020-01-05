function [xhatError, PElements, NArr, MeasResidual] = FIR(SystemModel, SmoothingFlag, Nopt)
dt = SystemModel.dt;
F = SystemModel.F;
H = SystemModel.H;
QReal = SystemModel.QReal;
R = SystemModel.R;
x = SystemModel.x;
N = SystemModel.N;
nx = length(x); % number of states
ny = size(R, 1); % number of measurements
% The Nopt equation assumes a 2nd-order Newtonian system with Q(1,1)=0
if ~exist('Nopt', 'var') || isempty(Nopt)
    QFilter = SystemModel.QFilter;
    Nopt = round(sqrt(12*sqrt(R)/dt/sqrt(QFilter(2,2))));
end
if SmoothingFlag
    p = round(Nopt / 2); % smoothing lag
    iLowerLimit = max(Nopt + 1, Nopt + p - nx);
    iUpperLimit = min(N-1, N+Nopt-nx-1);
    NArr = iLowerLimit : N-p-1;
else
    p = 0; % filter
    iLowerLimit = Nopt + 2 - nx;
    iUpperLimit = min(N-1, N+Nopt-nx-1);
    NArr = Nopt+2-nx : iUpperLimit;
end
xArr = zeros(nx, N); % allocate memory for arrays
xhatArr = zeros(nx, N);
xhatError = zeros(nx, N);
PElements = zeros(nx, N);
yArr = zeros(ny, N);
FArr = zeros(nx, nx, N);
HArr = zeros(N, nx);
MeasResidual = zeros(ny, N);
Inx = eye(nx);
FExpMinusP = F^(-p);
for k = 1 : N
    % System simulation
    FArr(:, :, k) = F;
    HArr(k, :) = H;
    x = F * x + sqrt(QReal) * randn(2, 1);
    y = H * x + sqrt(R) * randn;
    % Save data in arrays
    xArr(:, k) = x;
    yArr(:, k) = y;
end
Ysm = zeros(1, nx*ny);
FsmT = zeros(nx, nx^2);
HsmBar = zeros(ny, nx^2);
for i = iLowerLimit : iUpperLimit % for example, if Nopt=100, p=50, and nx=2, then i starts at 148
    % FIR filter/smoother
    m = i - Nopt + 1;
    s = m + nx - 1;
    Yindex = nx * ny;
    for j = m : s
        Ysm(Yindex-ny+1 : Yindex) = yArr(:,j)';
        Yindex = Yindex - ny;
    end
    for j = 1 : nx
        temp = Inx;
        for iii = j-1 : nx-2
            temp = temp * FArr(:,:,s-iii);
        end
        FsmT(:, (j-1)*nx+1 : j*nx) = temp';
    end
    for iii = s : -1 : m
        HsmBar((s-iii)*ny+1 : (s-iii+1)*ny , (s-iii)*nx+1 : (s-iii+1)*nx) = HArr(s, :);
    end
    Hsm = HsmBar * FsmT';
    alpha = Inx;
    if p >= nx
        for iii = 1 : p-nx+1
            alpha = alpha / FArr(:,:,s-p+iii);
        end
    else
        for iii = 0 : nx-2-p
            alpha = alpha * FArr(:,:,s-p-iii);
        end
    end
    xhat = alpha / (Hsm' * Hsm) * Hsm' * Ysm';
    TempProd = Inx;
    for i1 = 0 : nx-2
        TempProd = TempProd * FArr(:,:,s-i1);
    end
    G = TempProd / (Hsm' * Hsm) * TempProd';
    % Compute gamma for el = i - Nopt + nx + 1
    gamma = Inx;
    for i1 = 0 : p
       gamma = gamma * FArr(:,:,i-Nopt+nx+1-i1); 
    end
    for el = i-Nopt+nx+1 : i
        G = Inx / (HArr(el,:)' * HArr(el,:) + Inx / (FArr(:,:,el) * G * FArr(:,:,el)'));
        K = FArr(:,:,el-p) / gamma * G * HArr(el,:)';
        xhat = FArr(:,:,el-p) * xhat + K * (yArr(:,el) - HArr(el,:) * gamma * xhat);
        if el < i
            % Compute gamma for the next value of el
            gamma = FArr(:,:,el+1) * gamma / FArr(:,:,el-p);
        end
    end
    xhatArr(:, i-p) = xhat;
    xhatError(:, i-p) = xArr(:, i-p) - xhat;
    Covariance = R * FExpMinusP * G * FExpMinusP';
    PElements(1, i-p) = Covariance(1, 1);
    PElements(2, i-p) = Covariance(2, 2);
    MeasResidual(:, i-p) = yArr(:, i-p) - HArr(i-p, :) * xhat;
end
return