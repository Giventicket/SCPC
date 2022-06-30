## 캠퍼스와 도로(2) insight sketch

<p align="center">
  <img src="https://user-images.githubusercontent.com/39179946/176602579-d4f1042b-b2ec-4f67-b954-a6f71a2c414c.PNG"/>
</p>

dijkstra를 한번 활용하는데 걸리는 시간은 O(ElogV)이며 이를 전체 vertex에 대해서 두번씩 활용하므로 O(VElogV)만큼의 수행시간이 소요된다. 따라서 주어진 시간안에 문제를 풀 수 있다는 분석을 했다. 아래에 psuedo code를 첨부했다. 각 vertex에 대해서 "특별 권한"을 사용하더라도 통과하는 차량이 존재할 수 밖에 없는 대학을 찾았다.

<p align="center">
  <img src="https://user-images.githubusercontent.com/39179946/176603102-610e6324-f9c1-43df-9d56-66ba38cbd972.PNG"/>
</p>

<p align="center">
  <img src="https://user-images.githubusercontent.com/39179946/176602590-1e28b959-c02b-4c1a-ae69-b39412e43c28.PNG"/>
</p>
