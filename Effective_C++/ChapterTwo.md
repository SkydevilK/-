# 5. C++이 은근슬쩍 만들어 호출해 버리는 함수들에 촉각을 세우자.

- 클래스에서 컴파일러가 저절로 선언해 주는 것들
  - 기본 생성자(default constructor)
  - 복사 생성자(copy constructor)
  - 복사 대입 연산자(copy assignment operator)
  - 소멸자(destructor)
- 모두 public 멤버이며 inline 함수이다.

# 6. 컴파일러가 만들어낸 함수가 필요 없으면 확실히 이들의 사용을 금지해 버리자

- 클래스 복사를 못하게 함.
  ```
  // 링크 시점에서 확인 가능
  class Samsung {
  private : 
    Samsung(const Samsung&); // 선언만 함
    Samsung& operator=(const Samsung&); // 선언만 함
  }
  ```
  ```
  class Uncopyable {
    protected:
      Uncopyable() {}   // 생성자 허용
      ~Uncopyable() {}  // 소멸자 허용
    private:
      Uncopyable(const Uncopyable&);            //복사 생성자 금지
      Uncopyable& operator=(const Uncopyable&); //복사 대입 연산자 금지
  }
  ```
  - Uncopyable의 상속은 public일 필요가 없다. 
  - Uncopyable의 소멸자는 가상 소멸자가 아니어도 된다.
  - Uncopyable 클래스는 데이터 멤버가 전혀 없기 때문에 공백 기본 클래스 최적화 기법을 사용할 수도 있다.
    - 하지만, 다중 상속으로 갈 수 있다.
    - 다중 상속시에는 공백 기본 클래스 최적화가 돌아가지 못할 때가 있다.

**컴파일러에서 자동으로 제공하는 기능을 허용하지 않으려면 대응되는 멤버 함수를 private로 선언한 후에 구현하지 않으면 된다.**

