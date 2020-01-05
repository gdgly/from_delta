# -*- coding: utf-8 -*-
"""
Created on Mon Sep  4 16:55:23 2017

@author: fanxu
"""

import numpy as np
from pykalman import KalmanFilter
import matplotlib.pyplot as plt

kf = KalmanFilter(n_dim_obs=1,
n_dim_state=1,
initial_state_mean=23,
initial_state_covariance=5,
transition_matrices=[1],
observation_matrices=[1],
observation_covariance=4,
transition_covariance=np.eye(1),
transition_offsets=None)

actual = [23]*100
sim = actual + np.random.normal(0,1,100)
state_means, state_covariance = kf.filter(sim)
plt.plot(actual,'r-',label='ture value')
plt.plot(sim,'k-',label='measurement')
plt.plot(state_means,'g-',label='kalman')
plt.legend()
plt.show()

