## 등차수열 insight sketch

가능한 d_i+1 - d_i를 계산하고 이들의 모두의 최대공약수를 구한 뒤, 그 숫자의 약수의 개수를 count up 하면 된다.
gcd가 0일때가 corner case인 것만 고려해주면 된다.
