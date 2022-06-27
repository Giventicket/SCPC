## 캠퍼스와 도로(1) insight sketch

<p align="center">
  <img src="https://user-images.githubusercontent.com/39179946/175953434-efd69552-2937-4ab7-9a23-b53594c512c0.PNG"/>
</p>

모든 vertex에 대해서 dijkstra algorithm을 활용해 intermediate vertex가 될 수 있는 vertex를 정답 배열에 넣습니다. 

dijkstra algorithm을 진행할 떄, 주의할 점은 다음과 같습니다.
(1) queue의 element는 어떤 path의 끝 vertex에서의 정보이다.
(2) queue에서 pop한 element의 dist보다 dist array에 저장된 value가 더 작을 경우 이는 shortest path와 무관하므로 이때의 path뿐만아니라 이 path를 pass하는 경로 또한 고려할 필요가 없다. 즉, 그대로 pop해준다.
(3) (2)의 검증을 통과한 element중 지나친 vertex가 3개 이상일 경우, 이 element의 parent value는 intermediate vertex가 될 수 있다.

(1), (2), (3)을 고려해서 작성한 pseudo code는 아래와 같습니다.

<p align="center">
  <img src="https://user-images.githubusercontent.com/39179946/175955275-8c0b7a3f-b00c-41e3-999f-907c84240f81.PNG"/>
</p>
