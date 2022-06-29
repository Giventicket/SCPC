## 방속의 거울 insight sketch

<p align="center">
  <img src="https://user-images.githubusercontent.com/39179946/175763448-572a13f0-a1af-4227-b9b1-edd29964d7f3.PNG"/>
</p>

O(N^2)이하의 알고리즘을 생각하고 접근을 했습니다.

<p align="center">
  <img src="https://user-images.githubusercontent.com/39179946/175763450-5cede784-2b4c-44bb-8713-dd71096f2179.PNG"/>
</p>

loop-up table을 위의 그림과 같이 구사해서 dir, pos(x, y)을 갱신하며 거울의 갯수를 계산했습니다. worst case O(N^2) 알고리즘입니다.
