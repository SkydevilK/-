# 아이템 26. 로 타입은 사용하지 말라

- Generic Class / Generic Interface
  - 클래스와 인터페이스 선언에 타입 매개변수가 쓰이는 것
  - Generic type 이라고 함
- Raw Type
  - Generic type에서 type parameter를 전혀 사용하지 않을 때
  ```
  List list;
  private final Collection timeStamps;
  ```
  - 아무 타입이나 들어가고 훗날 런타임 오류가 나온다.
- Raw Type을 사용하면 Generic이 안겨주는 안전성과 표현력을 모두 읽게 된다.
- List<Object> 같은 매개변수화 타입을 사용할 때와 달리 List 같은 로 타입을 사용하면 타입 안전성을 잃게 된다.
- unbounded wildcard type
  - 실제 타입 매개변수가 무엇인지 모를때 사용
  ```
  List<?> list
  ```
  - null 외의 어떤 원소도 넣을 수 없다.
- class 리터럴에서는 Raw Type을 써야 한다.
  - List.class, String[].class, int.class ...
- instanceof 연산자
  - 비한정적 와일드 카입 타입 이외의 매개변수화 타입에는 적용할 수 없다.
  ```
  if(o instanceof Set) {
    Set<?> set = (Set<?>) o;
  }
  ```
**Raw Type을 사용하면 런타임에 예외가 일어날 수 있으니 사용하면 안 된다.<br>**
**Raw Type은 Generic이 도입되기 이전 코드와의 호환성을 위해 제공될 뿐이다.<br>**
