import numpy as np  
import matplotlib.pyplot as plt  
from matplotlib.animation import FuncAnimation  
from scipy.integrate import odeint  
  
# PID控制器类  
class PIDController:  
    # ...（省略构造函数和其他方法）...  
  
# 初始化PID控制器和目标值  
pid = PIDController(Kp=1.0, Ki=0.1, Kd=0.01)  
target_value = 10.0  
pid.setpoint = target_value  
  
# 初始化绘图和性能指标变量  
fig, ax = plt.subplots()  
xdata, ydata = [], []  
output_data = []  # 存储PID控制器的输出  
time_threshold = 0.01  # 设定一个阈值来判断调节时间  
max_overshoot = 0.0  # 用于存储最大超调量  
rise_time = np.inf  # 初始化为无穷大，表示还没有达到设定值  
  
ln, = plt.plot([], [], 'r-')  
plt.ylim(target_value - 5, target_value + 5)  
plt.xlabel('Time')  
plt.ylabel('Value')  
plt.title('PID Control Real-time Plot and Performance')  
plt.grid(True)  
plt.show(block=False)  
  
# 时间变量，用于模拟实时更新  
time = 0.0  
  
# 初始化性能指标函数  
def calculate_performance(feedback_data, output_data, target_value):  
    global max_overshoot, rise_time  
    max_value = np.max(feedback_data)  
    overshoot = max_value - target_value  
    if overshoot > max_overshoot:  
        max_overshoot = overshoot  
    rise_time = np.where(feedback_data >= target_value)[0][0] * 0.1 if feedback_data[0] < target_value else np.inf  
    settling_time = np.where(np.abs(np.array(feedback_data) - target_value) < time_threshold)[0][-1] * 0.1 if feedback_data else np.inf  
    return max_overshoot, rise_time, settling_time  
  
# 更新函数  
def update(frame):  
    global time  
    time += 0.1  # 假设数据更新间隔为0.1秒  
    feedback = get_data()  # 获取实时数据  
    output = pid.update(feedback)  # 使用PID控制器计算输出  
      
    xdata.append(time)  
    ydata.append(feedback)  
    output_data.append(output)  
    ln.set_data(xdata, ydata)  
      
    # 计算性能指标（每帧更新一次可能效率较低，实际中可以在特定时刻计算）  
    max_overshoot, rise_time, settling_time = calculate_performance(ydata, output_data, target_value)  
      
    # 显示性能指标  
    plt.text(0.1, target_value - 2, f'Max Overshoot: {max_overshoot:.2f}', fontsize=8)  
    plt.text(0.1, target_value - 3, f'Rise Time: {rise_time * 0.1:.2f}s', fontsize=8)  
    plt.text(0.1, target_value - 4, f'Settling Time: {settling_time * 0.1:.2f}s', fontsize=8)  
      
    return ln,  
  
# 创建动画  
ani = FuncAnimation(fig, update, frames=np.arange(0, 50, 1),  # 假设总共更新50次  
                    init_func=lambda: ln.set_data([], []), blit=True, interval=100)  
  
# 防止图形窗口自动关闭  
plt.ioff()  
plt.show()