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

# 아이템 27. 비검사 경고를 제거하라

```
public <T> T[] toArray(T[] a) {
  if (a.length < size)
    return (T[]) Arrays.copyOf(elements, size, a.getClass()); // Error 발생
  System.arraycopy(elements, 0, a, 0, size);
  if(a.length > size)
    a[size] = null;
  return a;
}
```
```
public <T> T[] toArray(T[] a) {
  if (a.length < size) {
    // 생성한 배열과 매개변수로 받은 배열의 타입이 모두 T[]로 같으므로 올바른 형변환이다.
    @SuppressWarnings("unchecked") T[] result = (T[]) Arrays.copyOf(elements, size, a.getClass());
    return result;
  }
  System.arraycopy(elements, 0, a, 0, size);
  if(a.length > size)
    a[size] = null;
  return a;
}
```
- @SuppressWarning("unchecked") 어노테이션을 사용할 때면 그 경고를 무시해도 안전한 이유를 항상 주석으로 남겨놔야 한다.

**비검사 경고는 중요하니 무시하지말자<br>**
**모든 비검사 경고는 런타임에서 ClassCastException을 일으킬 수 있다.<br>**

# 아이템 28. 배열보다는 리스트를 사용하라

- 배열은 공변이다.
  - Sub가 Super의 하위타입이라면 Sub[]는 Super[]의 하위 타입이 된다.
- 제네릭은 불공변이다.
  - 즉, 서로 다른 Type1과 Type2가 있을 때, List<Type1>은 List<Type2>의 하위 타입도 아니고 상위 타입도 아니다.
- 런타임 에러
  ```
  Object[] objectArray = new Long[1];
  objectArray[0] = "몰라요"; // ArrayStoreException
  ```
- 컴파일 에러
  ```
  List<Object> list = new ArrayList<Long>();  // 호환되지 않는 타입이다.
  list.add("몰라요");
  ```

**리스트가 배열보다 성능 면에서는 안 좋지만, 코드 안전성 부분에서는 좋다.**
