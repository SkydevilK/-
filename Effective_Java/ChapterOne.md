Index

---

[아이템 1.  생성자 대신 정적 팩터리 메서드를 고려하라](https://github.com/SkydevilK/Study/blob/master/Effective_Java/ChapterOne.md#%EC%95%84%EC%9D%B4%ED%85%9C-1--%EC%83%9D%EC%84%B1%EC%9E%90-%EB%8C%80%EC%8B%A0-%EC%A0%95%EC%A0%81-%ED%8C%A9%ED%84%B0%EB%A6%AC-%EB%A9%94%EC%84%9C%EB%93%9C%EB%A5%BC-%EA%B3%A0%EB%A0%A4%ED%95%98%EB%9D%BC)

[아이템 2. 생성자에 매개변수가 많다면 빌더를 고려하라](https://github.com/SkydevilK/Study/blob/master/Effective_Java/ChapterOne.md#%EC%95%84%EC%9D%B4%ED%85%9C-2-%EC%83%9D%EC%84%B1%EC%9E%90%EC%97%90-%EB%A7%A4%EA%B0%9C%EB%B3%80%EC%88%98%EA%B0%80-%EB%A7%8E%EB%8B%A4%EB%A9%B4-%EB%B9%8C%EB%8D%94%EB%A5%BC-%EA%B3%A0%EB%A0%A4%ED%95%98%EB%9D%BC)

[아이템 3. private 생성자나 열거 타입으로 싱글턴임을 보증하라](https://github.com/SkydevilK/Study/blob/master/Effective_Java/ChapterOne.md#%EC%95%84%EC%9D%B4%ED%85%9C-3-private-%EC%83%9D%EC%84%B1%EC%9E%90%EB%82%98-%EC%97%B4%EA%B1%B0-%ED%83%80%EC%9E%85%EC%9C%BC%EB%A1%9C-%EC%8B%B1%EA%B8%80%ED%84%B4%EC%9E%84%EC%9D%84-%EB%B3%B4%EC%A6%9D%ED%95%98%EB%9D%BC)

[아이템 4. 인스턴스화를 막으려거든 private 생성자를 사용하라](https://github.com/SkydevilK/Study/blob/master/Effective_Java/ChapterOne.md#%EC%95%84%EC%9D%B4%ED%85%9C-4-%EC%9D%B8%EC%8A%A4%ED%84%B4%EC%8A%A4%ED%99%94%EB%A5%BC-%EB%A7%89%EC%9C%BC%EB%A0%A4%EA%B1%B0%EB%93%A0-private-%EC%83%9D%EC%84%B1%EC%9E%90%EB%A5%BC-%EC%82%AC%EC%9A%A9%ED%95%98%EB%9D%BC)

[아이템 5. 자원을 직접 명시하지 말고 의존 객체 주입을 사용하라](https://github.com/SkydevilK/Study/blob/master/Effective_Java/ChapterOne.md#%EC%95%84%EC%9D%B4%ED%85%9C-5-%EC%9E%90%EC%9B%90%EC%9D%84-%EC%A7%81%EC%A0%91-%EB%AA%85%EC%8B%9C%ED%95%98%EC%A7%80-%EB%A7%90%EA%B3%A0-%EC%9D%98%EC%A1%B4-%EA%B0%9D%EC%B2%B4-%EC%A3%BC%EC%9E%85%EC%9D%84-%EC%82%AC%EC%9A%A9%ED%95%98%EB%9D%BC)

[아이템 6. 불필요한 객체 생성을 피하라](https://github.com/SkydevilK/Study/blob/master/Effective_Java/ChapterOne.md#%EC%95%84%EC%9D%B4%ED%85%9C-6-%EB%B6%88%ED%95%84%EC%9A%94%ED%95%9C-%EA%B0%9D%EC%B2%B4-%EC%83%9D%EC%84%B1%EC%9D%84-%ED%94%BC%ED%95%98%EB%9D%BC)

[아이템 7. 다 쓴 객체 참조를 해제하라](https://github.com/SkydevilK/Study/blob/master/Effective_Java/ChapterOne.md#%EC%95%84%EC%9D%B4%ED%85%9C-7-%EB%8B%A4-%EC%93%B4-%EA%B0%9D%EC%B2%B4-%EC%B0%B8%EC%A1%B0%EB%A5%BC-%ED%95%B4%EC%A0%9C%ED%95%98%EB%9D%BC)

[아이템 8. finalizer와 cleaner 사용을 피하라](https://github.com/SkydevilK/Study/blob/master/Effective_Java/ChapterOne.md#%EC%95%84%EC%9D%B4%ED%85%9C-8-finalizer%EC%99%80-cleaner-%EC%82%AC%EC%9A%A9%EC%9D%84-%ED%94%BC%ED%95%98%EB%9D%BC)

[아이템 9. try-finally보다는 try-with-resources를 사용하라](https://github.com/SkydevilK/Study/blob/master/Effective_Java/ChapterOne.md#%EC%95%84%EC%9D%B4%ED%85%9C-9-try-finally%EB%B3%B4%EB%8B%A4%EB%8A%94-try-with-resources%EB%A5%BC-%EC%82%AC%EC%9A%A9%ED%95%98%EB%9D%BC)


<h1>아이템 1.  생성자 대신 정적 팩터리 메서드를 고려하라</h1>

<h4>장점</h4>

- 이름을 가질 수 있다.
  - 하나의 클래스에 시그니처가 같은 생성자가 여러 개 필요할 것 같으면, 생성자를 정적 팩터리 메서드로 바꾸고 각각의 차이를 잘 드러내는 이름을 지어주면 된다.
- 호출될 때마다 인스턴스를 새로 생성하지 않아도 된다.
  - 인스턴스를 미리 만들어 놓거나 새로 생성한 인스턴스를 캐싱하여 재활용하는 방식
  - 싱글턴, 인스턴스화 불가, 불변 값 클래스 등의 활용된다.
- 반환 타입의 하위 타입 객체를 반환할 수 있는 능력이 있다.
- 입력 매개변수에 따라 매번 다른 클래스의 개게를 반환할 수 있다.
- 정적 팩터리 메서드를 작성하는 시점에는 반환할 객체의 클래스가 존재하지 않아도 된다.
  - 서비스 제공자 프레임워크(service provider framework)를 만드는 근간이 된다.

<h4>단점</h4>

- 상속을 하려면 public이나 protected 생성자가 필요하니 정적 팩터리 메서드만 제공하면 하위 클래스를 만들 수 없다.
  - 상속보다 컴포지션을 사용하도록 유도하고, 불변 타입으로 만들려면 이 제약을 지켜야 한다는 점에서 오히려 장점이 될 수 있다.
- 정적 팩터리 메서드는 프로그래머가 찾기 어렵다.
  - 생성자처럼 API 설명에 명확히 드러나지 않으니 사용자는 정적 팩터리 메서드 방식 클래스를 인스턴스화할 방법을 알아내야 한다.
  
<h1>아이템 2. 생성자에 매개변수가 많다면 빌더를 고려하라</h1>

- 정적 팩터리와 생성자에는 선택적 매개변수가 많을 때 적절히 대응하기 어렵다는 단점이 있다.
  - 점층적 생성자 패턴(telescoping constructor pattern)을 사용
    - 점층적 생성자 패턴도 쓸 수는 있지만, 매개변수 개수가 많아지면 클라이언트 코드를 작성하거나 읽기 어렵다.
  - 자바빈즈 패턴(JavaBeans pattern)을 사용
    - 매개변수가 없는 생성자로 객체를 만든 후, 세터(setter) 메서드들을 호출해 원하는 매개변수의 값을 설정하는 방식
    - 자바빈즈 패턴에서는 객체 하나를 만들려면 메서드를 여러 개 호출해야 하고, 객체가 완전히 생성되기 전까지는 일관성(consistency)이 무너진 생태에 놓이게 된다.
      - 클래스를 불변으로 만들 수 없고, 스레드 안전성을 위해 프로그래머가 추가 작업을 해줘야만 한다.
- 빌더 패턴(Builder pattern)
  - 점층적 생성자 패턴의 안전성과 자바빈즈 패턴의 가독성을 가짐
    1) 클라이언트는 필요한 객체를 직접 만드는 대신, 필수 매개변수만으로 생성자(혹은 정적 팩터리)를 호출해 빌더 객체를 얻는다.
    2) 빌더 객체가 제공하는 일종의 세터 메서드들로 원하는 선택 매개변수들을 설정한다.
    3) 매개변수가 없는 build 메서드를 호출해 객체를 얻는다.
  - 빌더 패턴은 명명된 선택적 매개변수(named optional parameters)를 흉내 낸 것이다.
  - 계층적으로 설계된 클래스와 함께 사용하기에 좋다.
  
<h1>아이템 3. private 생성자나 열거 타입으로 싱글턴임을 보증하라</h1>
  
- 싱글턴(Singleton)이란 인스턴스를 오직 하나만 생성할 수 있는 클래스를 만드는 패턴
  - 예제
    1) 함수와 같은 무상태(stateless) 객체
    2) 설계상 유일해야 하는 시스템 컴포넌트
- 클래스를 싱글턴으로 만들면 이를 사용하는 클라이언트를 테스트하기가 어려워지는 단점이 있다.
- public static final 필드 방식의 싱글턴
  ```
  public class Singleton {
    public static final Singleton INSTANCE = new Singleton();
    private Singleton(){}
    public void Something(){}
  }
  ```
  - private 생성자는 public static final 필드인 Singleton.INSTANCE를 초기화할 때 딱 한 번만 호출된다.
  - public이나 protected 생성자가 없으므로 Singleton 클래스가 초기화 될 때 만들어진 인스턴스가 전체 시스템에서 하나뿐임이 보장된다.
  - 권한이 있는 클라이언트는 리플렉션 API인 AccessibleObject.setAccessible을 사용해 private 생성자를 호출할 수 있다.
    - 생성자를 수정하여 두 번째 객체가 생성되려 할 때 예외를 던지게 하면 된다.
  
  <h4>장점</h4>
  
    1) 해당 클래스가 싱글턴임이 API에 명백히 드러난다
    2) 간결하다
    
- 정적 팩터리 방식의 싱글턴
  ```
  public class Singleton {
    private static final Singleton INSTANCE = new Singleton();
    private Singleton(){}
    public static Singleton getInstance(){
      return INSTANCE;
    }
    public void Something(){}
  }
  ```
  - Singleton.getInstance는 항상 같은 객체의 참조를 반환하므로 제 2의 Singleton 인스턴스란 결코 만들어지지 않는다.(리플렉션을 통한 예외는 똑같이 처리해야 한다.)
  
  <h4>장점</h4>
  
  1) API를 바꾸지 않고도 싱글턴이 아니게 변경할 수 있다
  2) 정적 팩터리를 제네릭 싱글턴 팩터리로 만들 수 있다
  3) 정적 팩터리의 메서드 참조를 공급자(supplier)로 사용할 수 있다.
  
- 위의 두가지 방식은 직렬화하면 모든 인스턴스 필드를 일시적(transient)라고 선언하고 readResolve 메서드를 제공해야 한다.
    - 이렇게 안하면 직렬화된 인스턴스를 역직렬화할 때마다 새로운 인스턴스가 만들어진다.
    ```
    private Object readResolve(){
      reurn INSTANCE;
    }
    
- 열거 타입 방식의 싱글턴
  ```
  public enum Singleton {
    INSTANCE;
    public void Something(){}
  }
  ```
  - public 필드 방식과 비슷하지만, 더 간결하고, 추가 노력 없이 직렬화 할 수 있다.
  - 대부분 상황에서는 원소가 하나뿐인 열거 타입이 싱글턴을 만드는 가장 좋은 방법이다.
  
  <h4>단점</h4>
  
  - 만들려는 싱글턴이 Enum 외의 클래스를 상속해야 한다면 이 방법은 사용할 수 없다.
    
<h1>아이템 4. 인스턴스화를 막으려거든 private 생성자를 사용하라</h1>
  
  - 생성자를 명시하지 않으면 컴파일러가 자동으로 기본 생성자를 만든다.
    - 매개변수를 받지 않는 public 생성자가 만들어지고, 사용자는 이 생성자가 자동 생성된 것인지 구분할 수 없다.
  - 추상 클래스로 만드는 것으로는 인스턴스화를 막을 수 없다.
    - 하위 클래스를 만들어 인스턴스화하면 되기 때문이다.
    - 사용자는 상속해서 쓰라는 뜻으로 오해할 수 있다.
  - private 생성자를 추가하면 클래스의 인스턴스화를 막을 수 있다.
    - 컴파일러가 기본 생성자를 만드는 경우는 오직 명시된 생성자가 없을 때뿐이기 때문이다.
    ```
    public class UtilityClass{
      // 기본 생성자가 만들어지는 것을 막는다.
      private UtilityClass(){
        throw new AssertionError();
      }
    }
    ```
    - 명시적 생성자가 private이니 클래스 바깥에서는 접근할 수 없다.
    - 상속을 불가능하게 하는 효과도 있다.
    
<h1>아이템 5. 자원을 직접 명시하지 말고 의존 객체 주입을 사용하라</h1>
  
  - 클래스가 내부적으로 하나 이상의 리소스에 의존하고, 그 리소스가 클래스 동작에 영향을 준다면 싱글턴과 정적 유틸리티 클래스는 사용하지 않는 것이 좋다.
  - 이 리소스들을 클래스가 직접 만들게 해서도 안 된다.
  - 인스턴스를 생성할 때 생성자에 필요한 자원을 넘겨주는 방식
  - 의존 객체 주입은 클래스의 유연성, 재사용성, 테스트 용이성을 개선한다.
  ```
  public class SamsungPay{
    private final Card card;
    public SamsungPay(Card card){
      this.card = card;
    }
    
    public void Payment(){
    }
  }
  ```
  - 불변을 보장하여 같은 리소스를 사용하여는 여러 클라이언트가 의존 객체들을 안심하고 공유할 수 있다.
  - 생성자, 정적 팩터리, 빌더 모두에 똑같이 응용할 수 있다.
  - 생성자에 리소스 팩터리를 넘겨주는 방법
    - 팩터리란 호출할 때마다 특정 타입의 인스턴스를 반복해서 만들어주는 객체
    - 팩터리 메서드 패턴(Factory Method pattern)을 구현한 것을 의미한다.

<h1>아이템 6. 불필요한 객체 생성을 피하라</h1>

- 똑같은 기능의 객체를 매번 생성하기보다는 객체 하나를 재사용하는 편이 비용 면에서 효과적이다.
- 불변 객체는 언제든 재사용할 수 있다.
- 생성자 대신 정적 팩터리 메서드를 제공하는 불변 클래스에서는 정적 팩터리 메서드를 사용해 불필요한 객체 생성을 피할 수 있다.
  - 생성자는 호출할 때마다 새로운 객체를 만들지만, 팩터리 메서드는 그렇지 않다.

<h1>아이템 7. 다 쓴 객체 참조를 해제하라</h1>

- 해당 참조를 다 썼을 때 null 처리(참조 해제)하면 된다.
  - 객체 참조를 null 처리하는 일은 예외적인 경우여야 한다.
- 참조를 담은 변수를 유효 범위(scope) 밖으로 밀어낸다.
- 자기 메모리를 직접 관리하는 클래스라면 프로그래머는 항시 메모리 누수에 주의해야 한다.
- 캐시 역시 메모리 누수를 일으키는 주범이다.
  - 캐시 외부에서 키(key)를 참조하는 동안만 엔트리가 살아 있는 캐시가 필요한 상황이면 WeakHashMap을 사용해 캐시를 만든다.
  - ScheduledThreadPoolExecutor와 같은 백그라운드 스레드를 활용한다.
  - 캐시에 새 엔트리를 추가할 때 부수 작업으로 수행한다.
- 리스너(listener) 혹은 콜백(callback)은 메모리 누수를 일으킨다.
  - 클라이언트가 콜백을 등록만 하고 해지하지 않는다면 계속 쌓여갈 것이다.
  - 콜백을 약한 참조(weak reference)로 저장하면 G.C가 즉시 수거해간다.

<h1>아이템 8. finalizer와 cleaner 사용을 피하라</h1>

- finalizer는 예측할 수 없고, 상황에 따라 위험할 수 있어 일반적으로 불필요하다.
  - 오동작, 낮은 성능, 이식성 문제의 원인이 된다.
  - 기본적으로는 '쓰지 말아야' 한다.
- cleaner는 finalizer보다는 덜 위험하지만, 여전히 예측할 수 없고, 느리고, 일반적으로 필요 없다.
- C++의 소멸자와 자바의 finalizer / cleaner 는 다른 개념이다.
  - C++의 소멸자는 특정 객체와 관련된 리소스를 회수하는 보편적인 방법이다.
  - 자바에서는 접근할 수 없게 된 객체를 회수하는 역할은 G.C가 담당하고 프로그래머에게 아무런 작업도 요구하지 않는다.
  - C++의 소멸자는 비메모리 리소스를 회수하는 용도로도 쓰인다.
  - 자바에서는 try-with-resources와 try-finally를 사용해 해결한다.
- finalizer와 cleaner는 즉시 수행된다는 보장이 없다.
  - 제때 실행되어야 하는 작업은 절대 할 수 없다.
- 상태를 영구적으로 수정하는 작업에서는 절대 finalizer나 cleaner에 의존해서는 안 된다.
  - 데이터베이스 같은 공유 자원의 영구 락(lock) 해제를 finalizer나 cleaner에 맡겨 놓으면 분산 시스템 전체가 멈출 것이다.
- System.gc나 System.runFinalization 메서드에 현혹되지 말자.
  - finalizer와 cleaner가 실행될 가능성을 높여줄 수는 있으나, 보장해주진 않는다.
- finalizer와 cleaner는 심각한 성능 문제를 동반한다.
- finalizer를 사용한 클래스는 finalizer 공격에 노출되어 심각한 보안 문제를 일으킬 수 있다.
  - final이 아닌 클래스를 finalizer 공격으로부터 방어하려면 아무 일도 하지 않는 finalize 메서드를 만들고 final로 선언하면 된다.
- AutoCloseable을 구현하고 close 메서드를 호출하면 된다.
- cleaner(Java 8까지는 finalizer)는 안전망 역할이나 중요하지 않은 네이티브 자원 회수용으로만 사용하는 것이 좋다.
  - 불확실성과 성능 저하에 주의해야 한다.

<h1>아이템 9. try-finally보다는 try-with-resources를 사용하라</h1>

- try-finally : 전통적인 방식
  ```
  static String firstLineOfFile(String path) throws IOException {
  BufferedReader br = new BufferedReader(new FileReader(path));
  try {
    return br.readLine();
  } finally {
    br.close();
  }
  ```
  - 리소스가 둘 이상이면 지저분해 진다.
  ```
  static void copy(String src, String dst) throws IOException {
    InputStream in = new FileInputStream(src);
    try {
      OutputStream out = new FileOutputStream(dst);
      try {
        byte[] buf = new byte[BUFFER_SIZE];
        int n;
        while ((n = in.read(buf)) >= 0)
          out.write(buf, 0, n);
      } finally {
        out.close();
      }
    } finally {
      in.close();
    }
  }
  ```
- try-with-resources : 지원을 회수하는 최선의 방법
  ```
  static String firstLineOfFile(String path) throws IOException {
    try (BufferedReader br = new BufferedReader(new FileReader(path))) {
      return br.readLine();
    }
  }
  ```
  ```
  static void copy(String src, String dst) throws IOException {
    try (InputStream in = new FileInputStream(src);
         OutputStream out = new FileOutputStream(dst)) {
         byte[] buf = new byte[BUFFER_SIZE];
         int n;
         while ((n = in.read(buf)) >= 0)
          out.write(buf, 0, n);
    }
  }
  ```
- try-with-resources와 catch
  ```
  static String firstLineOfFile(String path, String defaultVal) throws IOException {
    try (BufferedReader br = new BufferedReader(new FileReader(path))) {
      return br.readLine();
    } catch (IOException e) {
      return defaultVal;
    }
  }
  ```
- 꼭 회수해야 하는 자원을 다룰 때는 try-finall 말고, try-with-resources를 사용하자.
- 코드는 짧고 분명해지고, 만들어지는 예외 정보도 훨씬 유용하다.
