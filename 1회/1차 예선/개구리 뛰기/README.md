## 개구리 점프 insight sketch

<p align="center">
  <img src="https://user-images.githubusercontent.com/39179946/175761316-94503a03-a70a-4278-b124-2aba8e174688.PNG"/>
</p>

문제의 input을 생각해보면 1~2초 안에 실행 되기때문에 O(N) 혹은 O(NlogN) 알고리즘을 생각하고 접근을 했습니다.

<p align="center">
  <img src="https://user-images.githubusercontent.com/39179946/175761319-e884d1a7-9df8-4ad2-af72-0abfede5fd0e.PNG"/>
</p>

다음에 jump를 할 곳을 찾아내기 위해서 이분탐색을 활용한 라이브러리 upper_bound를 생각해봤습니다. 
upper_bound는 이분 탐색을 활용해서 주어진 input의 숫자보다 더 큰 value를 가진 최초의 iterator를 반환하기 때문에 이보다 한칸 더 작은 index를 활용해서 K에 의한 boundary 안에서 서칭할 수 있도록 했습니다.
