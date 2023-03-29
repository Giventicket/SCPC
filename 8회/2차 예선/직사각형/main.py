import pickle
import numpy as np

f = open("data.txt", 'wb')

# 1부터 256*256까지의 수를 생성합니다.
numbers = np.arange(1, 256*256+1)

# log2 값을 계산합니다.
log2_values = np.log2(numbers)

# 결과를 출력합니다.
pickle.dump(log2_values, f)
