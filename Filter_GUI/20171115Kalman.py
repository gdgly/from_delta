# -*- coding: utf-8 -*-
"""
Created on Wed Nov 15 21:47:40 2017

@author: fanxu
"""

import numpy as np

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

def Kalman(systemModel):
    F=systemModel.F
    H=systemModel.H
    QFilter=systemModel.QFilter
    QReal=systemModel.QReal
    R = systemModel.R
    x = systemModel.x
    N = systemModel.N
    nx = max(x.shape)
    ny = min(H.shape)
    Pplus=1000 * np.mat(np.eye(nx))
    xhatplus=x+np.sqrt(np.diag(Pplus).reshape(2,1))
    xArr=np.mat(np.zeros((nx,N)))
    PplusArr=np.zeros((nx,nx,N))
    PminusArr = np.zeros((nx, nx, N))
    xhatminusArr = np.mat(np.zeros((nx, N)))
    xhatplusArr = np.mat(np.zeros((nx, N)))
    xhatplusError = np.mat(np.zeros((nx, N)))
    PKalmanElements = np.mat(np.zeros((nx, N)))
    JArr = np.zeros((nx, nx, N))
    JInvArr = np.zeros((nx, nx, N))
    KArr = np.mat(np.zeros((nx, N)))
    yArr = np.mat(np.zeros((ny, N)))
    FArr = np.zeros((nx, nx, N))
    HArr = np.mat(np.zeros((N, nx)))
    SArr = np.mat(np.zeros((ny, N)))
    MeasResidual = np.mat(np.zeros((ny, N)))
    Inx = np.mat(np.eye(nx))
    for k in range(0, N):
        FArr[:, :, k] = F
        HArr[k, :] = H
        x = F * x + np.sqrt(QReal) * np.random.randn(nx, 1)
        y = H * x + np.sqrt(R) * np.random.randn()
        #Kalman filter
        Pminus=F*Pplus*F.T+QFilter
        K=Pminus*H.T*(H * Pminus * H.T + R).I
        xhatminus = F * xhatplus
        xhatplus = xhatminus + K * (y - H * xhatminus)
        Pplus = Pminus - K * H * Pminus
        
        xArr[:, k] = x
        yArr[:, k] = y
        PminusArr[:, :, k] = Pminus
        PplusArr[:, :, k] = Pplus
        PKalmanElements[0, k] = Pplus[0, 0]
        PKalmanElements[1, k] = Pplus[1, 1]
        xhatminusArr[:, k] = xhatminus
        xhatplusArr[:, k] = xhatplus
        xhatplusError[:, k] = x - xhatplus
        JArr[:, :, k] = Inx - K * H
        JInvArr[:, :, k] =  (Inx - K * H).I
        KArr[:, k] = K
        SArr[:, k] = H * Pminus * H.T + R
        MeasResidual[:, k] = y - H * xhatminus
    
    #Kalman smoother
    xhatSmooth = xhatplus
    PSmooth = Pplus
    xhatSmoothArr = np.mat(np.zeros((nx, N)))
    xhatSmoothError = np.mat(np.zeros((nx, N)))
    xhatSmoothArr[:, N-1] = xhatSmooth
    xhatSmoothError[:, N-1] = xArr[:, N-1] - xhatSmooth
    KSmootherArr = np.zeros((nx, nx, N-1))
    PSmootherElements = np.mat(np.zeros((nx, N)))
    PSmootherElements[:, N-1] = PKalmanElements[:, N-1]
    for k in range(N-2 , 0 , -1):
        print(k)
        K = PplusArr[:, :, k] * F.T * np.mat(PminusArr[:, :, k+1]).I
        PSmooth = PplusArr[:, :, k] - K * (PminusArr[:, :, k+1] - PSmooth) * K.T
        xhatSmooth = xhatplusArr[: ,k] + K * (xhatSmooth - xhatminusArr[:, k+1])
        # Save data in arrays
        xhatSmoothArr[: ,k] = xhatSmooth
        xhatSmoothError[:, k] = xArr[:, k] - xhatSmooth
        KSmootherArr[:, :, k] = K
        PSmootherElements[0, k] = PSmooth[0, 0]
        PSmootherElements[1, k] = PSmooth[1, 1]
    return xhatplusError, xhatSmoothError, PKalmanElements, PSmootherElements, MeasResidual, PminusArr


QFactorArr = 1
Nopt = 12
dt = 0.1
F = np.mat([[1, dt], [0, 1]])
H = np.mat([1, 0]);
QReal = np.mat([[0, 0], [0, 1**2]])
QFilter = QReal * QFactorArr;
R = 0.833**2
x = np.mat([[1], [1]])
N = 100
systemModel = SystemModel(dt, F, H, QReal, QFilter, R, x, N)
result=Kalman(systemModel)
xhatplusError=result[0]