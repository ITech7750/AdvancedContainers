import pandas as pd
import matplotlib.pyplot as plt

file_path = "test/loadTestResults/load_test_results.csv"
data = pd.read_csv(file_path)
unique_ptr_data = data[data['PointerType'] == 'UniquePtr']
raw_ptr_data = data[data['PointerType'] == 'RawPtr']
plt.figure(figsize=(10, 6))
#гафик для UniquePtr
plt.plot(unique_ptr_data['ElementCount'], unique_ptr_data['ExecutionTime'], marker='o', label='UniquePtr', color='blue')
#график для RawPtr
plt.plot(raw_ptr_data['ElementCount'], raw_ptr_data['ExecutionTime'], marker='o', label='RawPtr', color='red')

plt.title('Сравнение времени выполнения для UniquePtr и RawPtr')
plt.xlabel('Количество элементов (10^k)')
plt.ylabel('Время выполнения (секунды)')
plt.legend()

plt.grid(True)
plt.show()
