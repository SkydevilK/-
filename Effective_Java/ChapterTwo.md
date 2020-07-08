# 아이템 10. equals는 일반 규약을 지켜 재정의하라

**재정의를 하지 않아도 되는 경우**
- 각 인스턴스가 본질적으로 고유한 경우
  - 값이 아닌 동작하는 개체를 표현하는 클래스
    - 예) Thread
- 인스턴스의 '논리적 동치성'(logical equality)를 검사할 필요가 없을 경우
- 상위 클래스에서 재정의한 equals가 하위 클래스에도 동일한 동작을 할 경우
  - 예) Set, List, Map 구현체 등
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
```
public class Samsung {
  private String phoneNumber;
  private int battery;
  private String deviceName;
  @Override public boolean equals(Object o) {
    if (o==this)
      return true;
    if (!(o instanceof Samsung))
      return false;
    Samsung samsung = (Samsung)o;
    return o.phoneNumber.equals(phoneNumber) && o.battery == battery && deviceName.equals(deviceName);
  }  
}
```
**꼭 필요한 경우가 아니면 equals를 재정의하지 말자. 많은 경우에 Object의 equals가 프로그래머가 원하는 비교를 정확히 수행한다. 재정의해야 할 때는 그 클래스의 핵심 필드 모두를 빠짐없이, 다섯 가지 규약을 확실히 지켜가며 비교해야 한다.**

# 아이템 11. equals를 재정의하려거든 hashCode도 재정의하라.

**equals를 재정의한 클래스는 모두 hashCode도 재정의해야 한다.**
  - 논리적으로 같은 객체는 같은 해시코드를 반환해야 하기 때문이다.
  
**hashCode 만드는 방법**
1. int 변수 result를 선언 후 값 c로 초기화 한다. 이때 c는 해당 객체에서 첫 번째 equals 비교에 사용되는 필드를 2.a 방식으로 계산한 hashCode이다.
2. 해당 객체의 나머지 equals 비교에 사용되는 필드 f 각각에 대해 다음 작업을 수행한다.
  a. 해당 필드의 해시코드 c를 계산한다.
    i. 기본 타입 필드라면, Type.hashCode(f)를 수행한다. 여기서 Type은 해당 기본 타입의 박싱 클래스이다.
    ii. 참조 타입 필드면서 이 클래스의 equals 메서드가 이 필드의 equals를 재귀적으로 호출해 비교한다면, 이 필드의 hashCode를 재귀적으로 호출한다. 필드의 값이 null이면 0을 사용한다.
    iii. 필드가 배열이라면, 배열의 원소 각각을 별도 필드처럼 다룬다. 
  b. result = 31 * result + c;

- 전통적인 방법
```
@Override public int hashCode() {
  int result = String.hashCode(phoneNumber);
  result = 31 * result + Integer.hashCode(battery);
  result = 31 * result + String.hashCode(deviceName);
  return result;
}
```
- hashCode를 지연 초기화하는 hashCode 메서드 - 스레드 안정성을 고려해야 한다.
```
private int hashCode;
@Override public int hashCode() {
  int result = hashCode;
  if(result == 0) {
  result = String.hashCode(phoneNumber);
  result = 31 * result + Integer.hashCode(battery);
  result = 31 * result + String.hashCode(deviceName);
  hashCode = result;
  }
  return result;
```

# 아이템 12. toString을 항상 재정의하라

- 재정의를 하지 않을 경우 ObjectName@16진수로 표현한 hashCode를 반환한다.
- toString을 구현한 클래스는 사용하기 편하고, 특히 디버깅하기 편하다.
- toString이 반환한 값에 포함된 정보를 얻어올 수 있는 API를 제공하자.

**모든 클래스에서 Object의 toString을 재정의 해야 한다. 다만 상위 클래스에서 이미 재정의 했을 경우는 생략한다.**
**toString은 해당 객체에 관한 명확하고 유용한 정보를 읽기 좋은 형태로 제공해야 한다.**

# 아이템 13. clone 재정의는 주의해서 진행하라

**새로운 인터페이스를 만들 때는 절대 Cloneable을 확장해서는 안 되며, 새로운 클래스도 이를 구현해서는 안 된다.**
**final 클래스라면 Cloneable을 구현해도 위험이 없지만, 성능 최적화에 따라 허용 여부를 결정한다.**
**복제 기능은 생성자와 팩터리를 이용하는 게 가장 좋다.**
**예외적으로 배열은 clone 메서드 방식이 가장 깔끔하다.**
