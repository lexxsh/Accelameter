import serial
import matplotlib.pyplot as plt
import numpy as np

# Connect to the Arduino through Serial (update 'COMX' with your port)
ser = serial.Serial('COM10', 115200)

# Initialize a list to store the received data
data = []


# Read data from Arduino
while True:
    try:
        
        
        ##readline 을 사용해서 serial의 글씨를 읽는다.
        ##쉼표를 split으로 잡고 parts안에 다가 넣게 된다.
        ##CC가 들어가야한다.
        ##mux1channel 변수엔 0번째 글씨를 집어넣고
        ##mux2channel 변수엔 1번째 글씨를 집어넣는다
        ##cap 변수엔 float 형식인 배열 3을 집어넣는다
        line = ser.readline()
        parts = line.strip().split(b',')
        if len(parts) == 3 and parts[0] == b'CC':
            Mux1Channel = int(parts[1])
            Mux2Channel = int(parts[2])
            capacitance = float(parts[3])
            data.append((Mux1Channel, Mux2Channel, capacitance))
            print("Mux1Channel:", Mux1Channel)
            print("Mux2Channel:", Mux2Channel)
            print("Capacitance:", capacitance)
    except KeyboardInterrupt:
        break

#시리얼과의 연결을 끊는다.
ser.close()

# 4X4의 히트맵을 그린다.
heatmap_data = np.zeros((4, 4))

# 히트맵의 데이터를 받아오는 mux값에 따라 값을 넣어준다.
# 그리고 전에 값은 그 값을 유지시켜야되고 새로운 값이 들어오게 되면 변화가 있게 해야된다.
for Mux1Channel, Mux2Channel, capacitance in data:
    heatmap_data[Mux1Channel][Mux2Channel] = capacitance

# 히트맵을 생성한다. cmap 즉 값의 크기가 높으면 색을 hot으로 표현시켜야한다.
# 히트맵의 label에는 Cap을 넣어준다
# plt.show를 통해 값들을 보여준다.
plt.imshow(heatmap_data, cmap='hot', interpolation='nearest')
plt.colorbar(label='Capacitance (pF)')
plt.xlabel('Mux2 Channel')
plt.ylabel('Mux1 Channel')
plt.title('Capacitance Heatmap')
plt.show()
