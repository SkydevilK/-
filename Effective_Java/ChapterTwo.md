# 아이템 10. equals는 일반 규약을 지켜 재정의하라

**재정의를 하지 않아도 되는 경우**
- 각 인스턴스가 본질적으로 고유한 경우
  - 값이 아닌 동작하는 개체를 표현하는 클래스
    - ex) Thread
- 인스턴스의 '논리적 동치성'(logical equality)를 검사할 필요가 없을 경우
- 상위 클래스에서 재정의한 equals가 하위 클래스에도 동일한 동작을 할 경우
  - ex) Set, List, Map 구현체 등
- 클래스가 private이거나 package-private이고 equals 메서드를 호출할 일이 없을 경우
  ```
  @Override public boolean equals(Object o) {
    throw new AssertionError(); // 호출 금지
  }
  ```
**equals 메서드를 재정의할 때 따라야 하는 규약**
- 반사성(reflexivity): null이 아닌 모든 참조 값 x에 대해, x.equals(x)는 true이다.
- 대칭성(symmetry): null이 아닌 모든 참조 값 x,y에 대해, x.equals(y)가 true이면 y.equals(x)도 true다.
- 추이성(transitivity): null이 아닌 모든 참조 값 x, y, z에 대해, x.equals(y)가 true이고 y.equals(z)도 true면 x.equals(z)도 true이다.
- 일관성(consistency): null이 아닌 모든 참조 값 x,y에 대해, x.equals(y)를 반복해서 호출하면 항상 true 혹은 false를 반환해야 한다.
- Not Null : null이 아닌 모든 참조 값 x에 대해, x.equals(null)은 false다.

**구현 방법**
1. == 연산자를 사용해 입력이 자기 자신의 참조인지 확인한다.
    - 단순한 성능 최적화용
2. instanceof 연산자로 입력이 올바른 타입인지 확인한다.
    - List, Map, Set 과 같은 인터페이스들 때문
3. 입력을 올바른 타입으로 형변환한다.
    - 2번이 성공하면 3번도 성공한다.
4. 입력 객체와 자기 자신의 대응되는 '핵심' 필드들이 모두 일치하는지 하나씩 검사한다.
    - float과 double을 제외한 기본 타입 필드는 == 연산자를 활용한다.
  - 참조 타입 필드는 각각의 equals 메서드를 활용한다.
  - float과 double은 각각 정적 메서드인 Float.compare(float, float)과 Double.compare(double, double)로 비교한다.
  
**꼭 필요한 경우가 아니면 equals를 재정의하지 말자. 많은 경우에 Object의 equals가 프로그래머가 원하는 비교를 정확히 수행한다. 재정의해야 할 때는 그 클래스의 핵심 필드 모두를 빠짐없이, 다섯 가지 규약을 확실히 지켜가며 비교해야 한다.**
