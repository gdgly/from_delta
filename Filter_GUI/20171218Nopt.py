import numpy as np
import matplotlib.pyplot as plt

class SystemModel:
    def __init__(self, dt, F, H, QReal, QFilter, R, x, N):
        self.dt = dt
        self.F = F
        self.H = H
        self.QReal = QReal
        self.QFilter = QFilter
        self.R = R
        self.x = x
        self.N = N

def fir(systemModel, smoothingFlag, nOpt):
    dt = systemModel.dt
    F = systemModel.F
    H = systemModel.H
    QReal = systemModel.QReal
    R = systemModel.R
    x = systemModel.x
    N = systemModel.N
    nx = max(x.shape)
    ny = min(H.shape)
    if smoothingFlag:
        p = int(nOpt / 2 + 0.5)
        iLowerLimit = max(nOpt + 1, nOpt + p - nx)
        iUpperLimit = min(N - 1, N + nOpt - nx - 1)
        NArr = np.arange(iLowerLimit, N - p, 1)
    else:
        p = 0
        iLowerLimit = nOpt + 2 - nx
        iUpperLimit = min(N - 1, N + nOpt - nx - 1)
        NArr = np.arange(nOpt + 2 - nx, iUpperLimit + 1, 1)
    xArr = np.mat(np.zeros((nx, N)))
    xhatArr = np.mat(np.zeros((nx, N)))
    xhatError = np.mat(np.zeros((nx, N)))
    PElements = np.mat(np.zeros((nx, N)))
    yArr = np.mat(np.zeros((ny, N)))
    FArr = np.zeros((nx, nx, N))
    HArr = np.mat(np.zeros((N, nx)))
    MeasResidual = np.mat(np.zeros((ny, N)))
    Inx = np.mat(np.eye(nx))
    FExpMinusP = F.I ** p
    for k in range(1, N + 1):
        FArr[:, :, k - 1] = F
        HArr[k - 1, :] = H
        x = F * x + np.sqrt(QReal) * np.random.randn(2, 1)
        y = H * x + np.sqrt(R) * np.random.randn()
        xArr[:, k - 1] = x
        yArr[:, k - 1] = y
    Ysm = np.mat(np.zeros((1, nx * ny)))
    FsmT = np.mat(np.zeros((nx, nx ** 2)))
    HsmBar = np.mat(np.zeros((nx * ny, nx ** 2)))
    for i in range(iLowerLimit, iUpperLimit + 1):
        m = i - nOpt + 1
        s = m + nx - 1
        Yindex = nx * ny
        for j in range(m, s + 1):
            Ysm[Yindex-ny+1-1 : Yindex] = yArr[:, j-1].T
            Yindex = Yindex - ny
        for j in range(1, nx + 1):
            temp = Inx
            for iii in range(j - 1, nx - 1):
                temp = temp * FArr[:, :, s - iii - 1]
            FsmT[:, (j - 1) * nx + 1-1 : j * nx] = temp.T
        for iii in range(s, m - 1, -1):
            HsmBar[(s-iii)*ny+1-1 : (s-iii+1)*ny, (s-iii)*nx+1-1 : (s-iii+1)*nx] = HArr[s, :]
        Hsm = HsmBar * FsmT.T
        alpha = Inx
        if p >= nx:
            for iii in range(1, p - nx):
                alpha = alpha * FArr[:, :, s-p+iii - 1].I
        else:
            for iii in range(0, nx - 1 - p):
                alpha = alpha * FArr[:, :, s-p-iii - 1]
        xhat = alpha * (Hsm.T * Hsm).I * Hsm.T * Ysm.T
        TempPord = Inx
        for i1 in range(0, nx - 1):
            TempPord = TempPord * FArr[:, : ,s-i1 - 1]
        G = TempPord * (Hsm.T * Hsm).I * TempPord.T
        gamma = Inx
        for i1 in range(0, p + 1):
            gamma = gamma *FArr[:, : ,i-nOpt+nx+1-i1 - 1]
        for el in range(i-nOpt+nx+1,i+1):
            G = (HArr[el-1,:].T * HArr[el-1,:] + (FArr[:,:,el - 1] * G * np.mat(FArr[:, :, el - 1]).T).I).I
            K = FArr[:,:,el-p - 1] * gamma.I * G * HArr[el-1,:].T
            xhat = FArr[:,:,el-p - 1] * xhat + K * (yArr[:,el-1] - HArr[el-1,:] * gamma * xhat)
            if el < i:
                gamma = FArr[:,:,el+1 - 1] * gamma * (np.mat(FArr[:,:,el-p - 1]).I)
        xhatArr[:, i-p-1] = xhat;
        xhatError[:, i-p-1] = xArr[:, i-p-1] - xhat;
        Covariance = R * FExpMinusP * G * FExpMinusP.T;
        PElements[0, i-p-1] = Covariance[0, 0];
        PElements[1, i-p-1] = Covariance[1, 1];
        MeasResidual[:, i-p-1] = yArr[:, i-p-1] - HArr[i-p-1, :] * xhat;
    return xhatError, PElements, NArr, MeasResidual

QFactorArr = 1
dt = 0.1
F = np.mat([[1, dt], [0, 1]])
H = np.mat([1, 0]);
QReal = np.mat([[0, 0], [0, 1**2]])
QFilter = QReal * QFactorArr;
R = 0.833**2
x = np.mat([[1], [1]])
N = 1000

NoptArr=arange(3,20+1)
RMSMeasResidual=np.mat(np.zeros((1,len(NoptArr))))
RMSEstError=np.mat(np.zeros((1,len(NoptArr))))
for i in range(0,len(NoptArr)):
    print(NoptArr[i])
    systemModel = SystemModel(dt, F, H, QReal, QFilter, R, x, N)
    resultF=fir(systemModel, False, NoptArr[i])
    xhatError=resultF[0]
    NArr=resultF[2]
    MeasResidual=resultF[3][:,NArr[0]:NArr[-1]]
    RMSMeasResidual[:,i]=np.sqrt(np.sum(np.multiply(MeasResidual,MeasResidual))/size(MeasResidual))
    RMSEstError[:,i]=np.sqrt(np.linalg.norm(xhatError,'fro')/(xhatError.size))
RMSMeasResDeriv=(RMSMeasResidual[:,-size(RMSMeasResidual)+2:]-RMSMeasResidual[:,0:-1-1])/2

b=np.array(RMSEstError)
a=np.array(RMSMeasResDeriv)
i=np.argmin(a)
Nopt=NoptArr[i+1]
print(Nopt)
plt.plot(NoptArr[1:-1],a[0,:],label='Derivative of V(N)')
plt.plot(NoptArr[1:-1],b[0,1:-1],label='RMS Estimation Error')
plt.legend(loc = 'upper right')
plt.grid()
plt.show()











    
