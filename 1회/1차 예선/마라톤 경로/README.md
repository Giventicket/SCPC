## 마라톤 경로 insight sketch

200점 만점에 56점을 받은 풀이에 대한 insight sketch입니다. 혹시 논리적 허점을 찾는다면 comment 부탁드립니다.

<p align="center">
  <img src="https://user-images.githubusercontent.com/39179946/176223159-5795244b-fea3-471c-958e-a5b178ac81c9.PNG"/>
</p>

priority_queue에 <weight, bottleCnt, curX, curY>를 element type으로 assign하고 가능한 모든 path를 breadth first search로 탐색하는 과정을 pseudo code로 나타냈습니다. 한편, queue에서 pop 된 element의 weight이 주어진 [bottleCnt, curX, curY]에 대한 min weight보다 클 경우는 더 이상 생각할 필요 없는 path이므로 별다른 연산 없이 그대로 pop하여 시간 복잡도를 낮췄습니다. 이떄, 시간 복잡도는 dist 값을 모두 renew 하고 난 뒤에 while 문이 종료되므로 O(MAXN * MAXM * MAXK)임을 확인 수 있습니다. 
