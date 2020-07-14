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

# 아이템 29. 이왕이면 제네릭 타입으로 만들라

- 클라이언트에서 직접 형변환해야 하는 타입보다 제네릭 타입이 더 안전하고 쓰기 편하다.
- 새로운 타입을 설계할 때는 형변환 없이도 사용할 수 있도록 하자.

# 아이템 30. 이왕이면 제네릭 메서드로 만들라

- 제네릭 타입과 마찬가지로, 클라이언트에서 입력 매개변수와 반환값을 명시적으로 형변환해야 하는 메서드보다 제네릭 메서드가 더 안전하며 사용하기도 쉽다.
- 타입과 마찬가지로, 메서드도 형변환 없이 사용할 수 있는 편이 좋으며, 많은 경우 그렇게 하려면 제네릭 메서드가 되어야 한다.

# 아이템 31. 한정적 와일드카드를 사용해 API 유연성을 높이라

**PECS(producer-extends, consumer-super**

- 매개변수화 타입 T
  - 생산자 <? extends T>
  - 소비자 <? super T>
  ```
  public Chooser(Collection<T> choices)
  public Chooser(Collection<? extends T> choices)
  ```
  ```
  public static <E> Set<E> union(Set<E> s1, Set<E> s2)
  public static <E> Set<E> union(Set<? extends E> s1, Set<? extends E> s2>)
  ```
  - 반환 타입이 Set<E>인 이유는 반환 타입에는 한정적 와일드카드 타입을 사용하면 안된다.
    - 유연성을 높여주기는 커녕 클라이언트 코드에서도 와일드카드 타입을 사용해야 하기 때문이다.
- 클래스 사용자가 와일드카드 타입을 신경 써야 한다면 그 API에 무슨 문제가 있을 가능성이 크다.

```
public static <E extends Comparable<E>> E max(List<E> list)
public static <E extends Comparable<? super E>> E max(List<? extends E> list)
```
- 입력 매개변수에서는 E 인스턴스를 생산하므로 원래의 List<E>를 List<? extends E>로 수정했다.
- Comparable은 언제나 소비자이므로, 일반적으로 Comparable<E> 보다는 Comparable<? super E>를 사용하는 편이 낫다.
- COmparator도 마찬가지로 Comparator<E> 보다는 Comparator<? super E>를 사용하는 편이 낫다.

- 메서드 선언에 타입 매개변수가 한 번만 나오면 와일드 카드로 대체하라.
```
public static <E> void swap(List<E> list, int i, int j);
public static void swap(List<?> list, int i, int j);   // 해당 방식 사용

public static void swap(List<?> list, int i, int j) {
  list.set(i, list.set(j, list.get(i));     // 컴파일 에러 (List<?>에는 null값 밖에 들어가지 않음)
}

public static void swap(List<?> list, int i, int j) {
  swapHelper(list, i, j);
}
private static <E> void swapHelper(List<E> list, int i, int j) {
  list.set(i, list.set(j, list.get(i));
}
```

**조금 복잡하더라도 와일드카드 타입을 적용하면 API가 훨씬 유연해진다.<br>**
**PECS 공식을 기억하자.<br>**

# 아이템 32. 제네릭과 가변인수를 함께 쓸 때는 신중하라**

- 가변인수와 제네릭은 궁합이 좋지 않다.
  - 가변인수 기능은 배열을 노출하여 추상화가 완벽하지 못하고, 배열과 제네릭의 타입 규칙이 서로 다르기 때문이다.
- 제네릭 varargs 매개변수는 type-safe 하지 않지만 허용이 된다.
- 메서드에 제네릭 (혹은 매개변수화된) varargs 매개면수를 사용하고자 한다면, 먼저 그 메서드의 type-safe를 확인한 다음 @SafeVarargs 어노테이션을 달아 에러를 없애야 한다.

# 아이템 33. 타입 안전 이종 컨테이너를 고려하라

**타입 안전 이종 컨테이너 패턴(type safe heterogeneous container pattern)**

- 컨테이너 대신 Key를 매개변수화한 다음, 컨테이너에 값을 넣거나 뺄 때 매개변수화한 Key를 함께 제공하는 것
- 제네릭 타입 시스템이 값의 타입이 키와 같음을 보장해 줌

- 타입별로 즐겨 찾는 인스턴스를 저장하고 검색할 수 있는 클래스
```
public class Favorites {
  public <T> void putFavorite(Class<T> type, T instance);
  public <T> T getFavorite(Class<T> type);
}
```
- 클라이언트
```
public static void main(String[] args) {
  Favorites f = new Favorites();
  
  f.putFavorite(String.class, "Java");
  f.putFavorite(Integer.class, 0xcafebabe);
  f.putFavorite(Class.class, Favorites.class);
  
  String favoriteString = f.getFavorite(String.class);
  int favoriteInteger = f.getFavorite(Integer.class);
  Class<?> favoriteClass = f.getFavorite(Class.class);
  
  System.out.printf("%s %x %s\n", favoriteString, favoriteInteger, favoriteClass.getName());
  // Java cafebabe Favorites
}
```
- Favorites 인스턴스는 안전하다. 따라서, 타입 안전 이종 컨테이너라 할 만 하다.
```
public class Favorites {
  private Map<Class<?>, Object> favorites = new HashMap<>();
  
  public <T> void putFavorite(Class<T> type, T instance) {
    favorites.put(Objects.requireNonNUll(type), instance);
  }
  
  public <T> T getFavorite(Class<T> type) {
    return type.cast(favorites.get(type));
  }
}
```
- favorites는 비한정적 와일드카드 타입이라 null밖에 넣을 수 없다고 생각할 수 있지만, 와일드카드 타입이 중첩되어 있어 넣을 수 있다.
  - 맵이 아니라 Key가 와일드카드 타입인 것이다.
  - 모든 Key가 서로 다른 매개변수화 타입일 수 있다는 뜻으로, 첫 번째는 Class<String>, 두 번째는 Class<Integer> 식으로 될 수 있다.
- favorites 맵의 value 타입은 단순히 Object이다.
  - favorites는 Key와 Value 사이의 타입 관계를 보증하지 않는다는 뜻이다.
- getFavorite에서 cast 연산을 해준다.
  - 객체 참조를 Class 객체가 가르키는 타입으로 동적 형변환한다.

- 제약 사항
  - 악의적인 클라이언트가 Class 객체를 (Generic이 아닌) Raw Type으로 넘기면 Favorites 인스턴스의 Type-Safe가 쉽게 깨진다.
  ```
  f.putFacorite((Class)Integer.class, "String 값이다.");
  int favoriteInteger = f.getFavorite(Interger.class); // ClassCastException 에러 발생
  ```
  - 실체화 불가 타입에는 사용할 수 없다.
    - String이나 String[]은 저장할 수 있어도 List<String>은 저장할 수 없다.
      - super type token을 이용해 해결할 수 있다.
      ```
      Favorites f = new Favorites();
      List<String> pets = Arrays.asList("Dog", "Cat", "Bird");
      f.putFavorite(new TypeRef<List<String>>(){}, pets);
      List<String> listofStrings = f.getFavorite(new TypeRef<List<String>>(){});
      ```
**컬렉션 API로 대표되는 일반적인 제네릭 형태에서는 한 컨테이너가 다룰 수 있는 타입 매개변수의 수가 고정되어 있다.<br>**
**하지만 컨테이너 자체가 아닌 Key를 타입 매개변수로 바꾸면 이런 제약이 없는 타입 안전 이종 컨테이너를 만들 수 있다.<br>**
**타입 안전 이종 컨테이너는 Class를 Key로 쓰며, 이런 식으로 쓰이는 Class 객체를 타입 토큰이라 한다.<br>**
