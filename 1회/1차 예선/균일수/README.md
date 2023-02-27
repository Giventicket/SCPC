## 균일수 insight sketch

<p align="center">
  <img src="https://user-images.githubusercontent.com/39179946/175776684-06ab8de9-35ff-4f48-937e-c807b345d38a.PNG"/>
</p>

a를 N의 약수로부터 얻을 수 있고 b 를 (N/a)-1의 약수로부터 얻을 수 있습니다. 이렇게 얻은 a, b로 N을 조합할 수 있는지 check up 해보는 과정으로 b의 candidate을 구할 수 있습니다. 이러한 b 중에서 가장 작은 b를 구하면 되고 가장 dominant 한 시간은 약수를 얻는 과정이라고 할 수 있겠습니다. 따라서 보수적으로 상수 k를 붙여 위와 같은 시간 복잡도로 알고리즘을 구상했습니다. 

<p align="center">
  <img src="https://user-images.githubusercontent.com/39179946/175776689-6cb61902-3f69-4a3b-8a67-805899fb880e.PNG"/>
</p>

위의 그림처럼 pseudocode를 구성해보았습니다. answer, div1, div2은 set 구조를 활용해서 중복하는 수들을 없애고 작은 수부터 차례로 정렬된 접근을 할 수 있도록 했습니다. worst case O(N^0.5) 알고리즘입니다.
