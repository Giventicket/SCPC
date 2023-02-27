## 최대 구간 중첩 insight sketch

O(NlogN)이하의 알고리즘을 생각하고 접근을 했습니다. LIS에서 vector에서 하나씩 넣어가면서 O(NlogN) 안에 max sequence length 를 구하는 방법에서 아이디어를 얻었습니다.

<p align="center">
  <img src="https://user-images.githubusercontent.com/39179946/176448844-c360c97f-395d-4595-b445-0a944acf4132.PNG"/>
</p>

pseudo code는 아래와 같습니다. vector 하나를 생성해서 규칙성 있게 정렬된 구간들을 push 하였습니다. 규칙은 다음과 같습니다.
<br />
1. 오른으로 갈수록 end value의 크기가 감소한다.
2. 왼쪽에서 오른쪽으로만 포함관계가 성립한다.
3. 최대 중첩 구간의 set size는 vector의 size와 동일하다.

<p align="center">
  <img src="https://user-images.githubusercontent.com/39179946/176448856-fe56e383-2b23-4ac6-b347-9409fff9265c.PNG"/>
</p>
