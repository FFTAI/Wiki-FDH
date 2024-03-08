import numpy as np  
import matplotlib.pyplot as plt  
from matplotlib.animation import FuncAnimation  
from scipy.integrate import odeint  
  
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
    # 这里应该替换为实际的数据获取代码  
    # 假设我们有一个简单的正弦波作为反馈数据  
    return 30*np.sin(0.1*time) + np.random.normal(0, 0.1)  # 添加一些噪声  
  
# 初始化PID控制器和目标值  
pid = PIDController(Kp=1.0, Ki=0.1, Kd=0.01)  
target_value = 10.0  
pid.setpoint = target_value  
  
# 初始化绘图  
fig, ax = plt.subplots()  
xdata, ydata = [], []  
ln, = plt.plot([], [], 'r-')  
plt.ylim(target_value, target_value + 15)  
plt.xlabel('Time')  
plt.ylabel('Value')  
plt.title('PID Control Real-time Plot')  
plt.grid(True)  
plt.show(block=False)  
  
# 时间变量，用于模拟实时更新  
time = 0.0  
  
def init():  
    # ax = plt.gca()
    ax.set_xlim(0, 100*np.pi)  
    ax.set_ylim(-50, 50)  
    return ln,  
  
def update(frame):  
    global time  
    time += 0.1  # 假设数据更新间隔为0.1秒  
    feedback = get_data()  # 获取实时数据  
    output = pid.update(feedback)  # 使用PID控制器计算输出  
    # print(output)
    xdata.append(time)  
    ydata.append(feedback)  
    ln.set_data(xdata, ydata)  
      
    # 可选：在图上显示PID控制器的输出  
    # plt.text(time, feedback, f'PID Output: {output:.2f}', fontsize=8)  
      
    return ln,  
  
# 创建动画  
ani = FuncAnimation(fig, update, frames=np.arange(0, 2*np.pi, 0.1),  
                    init_func=init, blit=True, interval=100)  
# 阻止图形窗口关闭，直到用户关闭它  
plt.ioff()  
plt.show()