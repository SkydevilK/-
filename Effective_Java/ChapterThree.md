# 아이템 15. 클래스와 멤버의 접근 권한을 최소화하라

**정보은닉**
- 모든 내부 구현을 완벽히 숨겨, 구현과 API를 깔끔히 분리하는 것
- 오직 API를 통해서만 다른 컴포넌트와 소통하며 서로의 내부 동작 방식은 별개로 한다.

- 장점
  - 시스템 개발 속도를 높인다.
  - 시스템 관리 비용을 낮춘다.
  - 정보 은닉 자체가 성능을 높여주지는 않지만, 성능 최적화에 도움을 준다.
  - 소프트웨어 재사용성을 높인다.
  - 큰 시스템을 제작하는 난이도를 낮춰준다.

- 자바의 접근 수준
  - private
    - 멤버를 선언한 클래스에서만 접근할 수 있다.
  - package-private(default)
    - 멤버가 소속된 패키지 안의 모든 클래스에서 접근할 수 있다. (클래스 멤버의 기본 접근 수준)
  - protected
    - 멤버를 선언한 클래스의 하위 클래스에서도 접근할 수 있다.
  - public
    - 모든 곳에서 접근할 수 있다. (인터페이스의 멤버 기본 접근 수준)
  - private ⊂ package-private(default) ⊂ protected ⊂ public
  
- public 클래스의 인스턴스 필드는 되도록 public이 아니여야 한다.
  - public 가변 필드를 갖는 클래스는 일반적으로 Thread-Safe 하지 않다.

- 클래스에서 public static final 배열 필드를 두거나 이 필드를 반환하는 접근자 메서드를 제공해서는 안된다.
  - 길이가 0이 아닌 배열은 모두 변경이 가능하다.
  ```
  public static final T[] VALUES = {...};
  ```
  - 해결방법 1) public 불변 리스트를 추가한다.
    ```
    private static final T[] PRIVATE_VALUES = {...};
    public static final List<T> VALUES = Collections.unmodifiableList(Arrays.asList(PRIVATE_VALUES));
    ```
  - 해결방법 2) 복사본을 반환하는 public 메서드를 추가한다. (방어적 복사)
    ```
    private static final T[] PRIVATE_VALUES = {...};
    public static final T[] values() {
      return PRIVATE_VALUES.clone();
    }
    ```
    
**프로그램 요소의 접근은 가능한 최소화 하자<br>**
**최소한의 public API를 설계하자<br>**
**public 클래스는 상수용 public static final 필드 외에는 어떠한 public 필드를 가져서는 안 된다<br>**
**public static final 필드가 참조하는 객체가 불변인지 확인하자<br>**
    
# 아이템 16. public 클래스에서는 public 필드가 아닌 접근자 메서드를 사용하라

- 데이터 필드에 직접 접근할 수 있으니 캡슐화의 이점을 제공하지 못한다.
```
class Point {
  public double x;
  public double y;
}
```
- 필드를 모두 private로 바꾸고 public 접근자(getter / setter)를 추가한다.
```
class Point {
  private double x;
  private double y;
  
  public Point(double x, double y) {
    this.x = x;
    this.y = y;
  }
  
  public double getX() { return x; }
  public double getY() { return y; }
  public void setX(double x) { this.x = x; }
  public void setY(double y) { this.y = y; }
}
```
- public 클래스라면 접근자를 제공해야 하지만, pakage-private 클래스 혹은 private 중첨 클래스라면 데이터 필드를 노출한다 해도 문제가 없다.

**public 클래스는 절대 가변 필드를 직접 노출해서는 안 된다<br>**
**불변 필드라면 노출해도 덜 위험하지만 완전히 안심할 수는 없다<br>**
**package-private 클래스나 private 중첩 클래스에서는 종종 (불변이든 가변이든) 필드를 노출하는 편이 나을 때도 있다**

# 아이템 17. 변경 가능성을 최소화하라

- 불변 클래스
  - 인스턴스의 내부 값을 수정할 수 없는 클래스를 지칭함
- 클래스를 불변으로 만드는 법
  - 객체의 상태를 변경하는 메서드를 제공하지 않는다.
  - 클래스를 확장할 수 없도록 한다.
  - 모든 필드를 final로 선언한다.
  - 모든 필드를 private로 선언한다.
  - 자신 외에는 내부의 가변 컴포넌트에 접근할 수 없도록 한다.
```
public final class Calc {
  private final double realNumber;
  private final double imaginaryNumber;
  
  public Clac(double realNumber, double imaginaryNumber) {
    this.realNumber = readNumber;
    this.imaginaryNumber = imaginaryNumber;
  }
  
  public double realNumberPart() {
    return this.realNumber;
  }
  
  public double imaginaryPart() {
    return this.imaginaryNumber;
  }
  
  public Calc plus(Calc c) {
    return new Calc(this.realNumber + c.realNumber, this.imaginaryNumber + c.imaginaryNumber);
  }
  
  public Calc minus(Calc c) {
    return new Calc(this.realNumber - c.realNumber, this.imaginaryNumber - c.imaginaryNumber);
  }
  
  public Calc times(Calc c) {
    return new Calc(this.realNumber * c.realNumber - this.imaginaryNumber * c.imaginaryNumber, this.realNumber * c.imaginaryNumber + this.imaginaryNumber * c.realNumber);
  }
  
  public Calc divided(Calc c) {
    double temp = c.realNumber * c.realNumber + c.imaginaryNumber * c.imaginaryNumber;
    return new Calc((this.realNumber * c.realNumber - this.imaginaryNumber * c.imaginaryNumber) / temp , (this.realNumber * c.imaginaryNumber + this.imaginaryNumber * c.realNumber) / temp);
  }
  
  @Override public boolean equals(Object o) { 
    if(o==this)
      reutrn true;
    if (!(o instanceof Calc))
      return false;
    Calc c = (Calc) o;
    return Double.compare(realNumber, c.realNumber) == 0 ** Double.compare(imaginaryNumber, c.imaginaryNumber) == 0
  }
  
  @Override public int hashCode() {
    return 31 * Double.hashCode(realNumber) + Double.hashCode(imaginaryNumber);
  }
  
  @Override public String toString() {
    reutrn "(" + realNumber + " + " + imaginaryNumber + "i)";
  }
  ```
  - 불변 객체는 근본적으로 Thread-Safe 하여 따로 동기화할 필요가 없다.
  - 불변 객체는 안심하고 공유할 수 있다.
  - 불변 객체는 실패 원자성을 제공한다.
    - 메서드에서 예외가 발생한 후에도 그 객체는 여전히 유효한 상태
  - 값이 다르면 반드시 독립된 객체로 만들어야 한다는 단점이 있다.
  
# 아이템 18. 상속보다는 컴포지션을 사용하라

- 메서드 호출과 달리 상속은 캡슐화를 깨뜨린다.
  - 상위 클래스가 어떻게 구현되느냐에 따라 하위 클래스의 동작에 이상이 생길 수 있다.
  - 메서드 오버라이팅이 원인이다.
- 기존 클래스를 확장하는 대신, 새로운 클래스를 만들고 private 필드로 기존 클래스의 인스턴스를 참조하게 하면 된다.
- Composition
  - 기존 클래스가 새로운 클래스의 구성요소로 쓰인다는 의미
- Forwarding
  - 새 클래스의 인스턴스 메서드들은 기존 클래스의 대응하는 메서드를 호출해 그 결과를 반환한다.

**상속은 강력하지만 캡슐화를 해친다는 문제가 있다.<br>**
**상속은 상위 클래스와 하위 클래스가 순수한 is-a 관계일 때만 사용해야 한다.<br>**
**하위클래스의 패키지가 상위 클래스와 다르고, 상위 클래스가 확장을 고려해 설계되지 않으면 문제가 된다.<br>**
**상속의 취약점을 피하려면 상속 대신 컴포지션과 전달을 사용하자.<br>**
**특히 래퍼 클래스로 구현할 적당한 인터페이스가 있다면 꼭 사용하자.<br>**

# 아이템 19. 상속을 고려해 설계하고 문서화하라. 그러지 않았다면 상속을 금지하라

- 상속용 클래스는 오버라이팅 할 수 있는 메서드들을 내부적으로 어떻게 이용하는지 문서로 남겨야 한다.
  - public과 protected 메서드 중 final이 아닌 모든 메서드
- API 문서의 메서드 설명 중 "Implementation Requirements"로 시작하는 설명은 메서드의 내부 동작 방식을 설명 하는 곳이다.
- 클래스의 내부 동작 과정 중간에 끼어들 수 있는 훅(hook)을 잘 선별하여 protected 메서드 형태로 공개해야 할 수도 있다.
- 상속용 클래스를 시험하는 방법은 직접 하위 클래스를 만드는 것이 유일한 방법이다.
- 상속용으로 설계한 클래스는 배포 전 반드시 하위클래스를 만들어 검증해야 한다.
- 상속용 클래스의 생성자는 오버라이팅 가능 메서드를 호출해서는 안 된다.
- clone과 readObject 모두 오버라이팅 가능 메서드를 호출해서는 안 된다.
- 상속용으로 설계하지 않은 클래스는 상속을 금지해야 한다.
  - 클래스를 final로 선언하면 된다.
  - 모든 생성자를 private나 package-private로 선언하고 public 정적 팩터리를 만들어주는 방법이다.
