import numpy as np  
import matplotlib.pyplot as plt  
from matplotlib.animation import FuncAnimation  
from scipy.integrate import odeint  
import dh
import time
  
# PID控制器类  
class PIDController:  
    def __init__(self, Kp=1.0, Ki=0.0, Kd=0.0, dt=0.1):  
        self.Kp = Kp  
        self.Ki = Ki  
        self.Kd = Kd  
        self.dt = dt  
        self.clear()  
  
    def clear(self):  
        self.setpoint = 0.0  
        self.error = 0.0  
        self.integral = 0.0  
        self.last_error = 0.0  
  
    def update(self, feedback_value):  
        self.error = self.setpoint - feedback_value  
        self.integral += self.error * self.dt  
        derivative = (self.error - self.last_error) / self.dt  
        self.last_error = self.error  
          
        output = self.Kp * self.error + self.Ki * self.integral + self.Kd * derivative  
        return output  
  
# 模拟获取实时数据的函数  
def get_data():  
    angle = dh.get_current()
    return angle[finger_id]
    
  
# 初始化PID控制器和目标值  
pid = PIDController(Kp=1.0, Ki=0.1, Kd=0.01)  
# target_input = input("target: ") 
# target_value = int(target_input)
# pid.setpoint = target_value  

finger1 = [ 0,   400.0,  0.00,  0.0]     # 1  -800~0
finger2 = [ 0,   200.1,  0.61,  0.01]     #1 2   0~1100
finger3 = [ 0,   100.1,  0.5,  0.01]     # 3  0~1100  
finger4 = [ 0,   60.1,  0.21,  0.001]     # 4  0~1000 error
finger5 = [ 0,   200.1,  0.50,  0.01]     # 5 errror
finger6 = [ 0,   150.1,  0.5,  0.01]     # 6
hand = [finger1, finger2, finger3, finger4, finger5, finger6]
  
# 初始化绘图  
fig, ax = plt.subplots()  
xdata, ydata = [], []  
ln, = plt.plot([], [], 'r-')  
plt.ylim(-1, 1)  
plt.xlabel('Time')  
plt.ylabel('Value')  
plt.title('PID Control Real-time Plot')  
plt.grid(True)  
plt.show(block=False)  
  
# 时间变量，用于模拟实时更新  
time_stamp = 0.0  

# finger1 = [ -1100,   450.0,  0.6,  0.3]     # 1  -800~0
finger1 = [ -200,   450.0,  0.6,  0.3]     # 1  -800~0
finger2 = [ 0,   200.1,  0.61,  0.01]     #1 2   0~1100
finger3 = [ 0,   100.1,  0.5,  0.01]     # 3  0~1100  
finger4 = [ 0,   60.1,  0.21,  0.001]     # 4  0~1000 error
finger5 = [ 0,   200.1,  0.50,  0.01]     # 5 errror
finger6 = [ 0,   150.1,  0.5,  0.01]     # 6
hand = [finger1, finger2, finger3, finger4, finger5, finger6]

  
def init():  
    # ax = plt.gca()
    ax.set_xlim(0, 0.00025)
    if float(finger1[0]) == -900:
        ax.set_ylim(-920, -880) 
    if float(finger1[0]) == 0:
        ax.set_ylim(-20, 20) 
    return ln,  
  
def update(frame):  
    global time_stamp  
    global finger_id
    finger_id = 0
    time_stamp += 0.000001  # 假设数据更新间隔为0.1秒  
    feedback = get_data()  # 获取实时数据  
    # output = pid.update(feedback)  # 使用PID控制器计算输出  
    # print(output)
    xdata.append(time_stamp)  
    ydata.append(feedback)  
    ln.set_data(xdata, ydata)  
    dh.pid_param(hand[0], hand[1], hand[2], hand[3], hand[4], hand[5])
      
    # 可选：在图上显示PID控制器的输出  
    # plt.text(time_stamp, feedback, f'PID Output: {output:.2f}', fontsize=8)  
      
    return ln,  
  
# 创建动画  
ani = FuncAnimation(fig, update, frames=np.arange(0, 0.00025, 0.000001),  
                    init_func=init, blit=True, interval=1)  


# # 阻止图形窗口关闭，直到用户关闭它  
# plt.ioff()

plt.show()
plt.close()
  