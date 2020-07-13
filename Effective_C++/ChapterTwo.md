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
  };
  ```
  ```
  class Uncopyable {
    protected:
      Uncopyable() {}   // 생성자 허용
      ~Uncopyable() {}  // 소멸자 허용
    private:
      Uncopyable(const Uncopyable&);            //복사 생성자 금지
      Uncopyable& operator=(const Uncopyable&); //복사 대입 연산자 금지
  };
  ```
  - Uncopyable의 상속은 public일 필요가 없다. 
  - Uncopyable의 소멸자는 가상 소멸자가 아니어도 된다.
  - Uncopyable 클래스는 데이터 멤버가 전혀 없기 때문에 공백 기본 클래스 최적화 기법을 사용할 수도 있다.
    - 하지만, 다중 상속으로 갈 수 있다.
    - 다중 상속시에는 공백 기본 클래스 최적화가 돌아가지 못할 때가 있다.

**컴파일러에서 자동으로 제공하는 기능을 허용하지 않으려면 대응되는 멤버 함수를 private로 선언한 후에 구현하지 않으면 된다.**

# 7. 다형성을 가진 기본 클래스에서는 소멸자를 반드시 가상 소멸자로 선언하자

```
class Samsung {
  public:
    Samsung();
    ~Samsung();
};

class GalaxyPhone: public Samsung {};
class GalaxyNode : public Samsung {};
```
- 팩토리 함수 (Factory function)
  - 새로 생성된 파생 클래스 객체에 대한 기본 클래스 포인터를 반환하는 함수
  ```
  Samsung* getSamsung();
  ```
- 메모리 누수
  ```
  Samsung * samsung = getSamsung();
  delete samsung;
  ```
  - 해당 코드의 문제점
    - getSamsung 함수가 반환하는 포인터가 파생 클래스 객체에 대한 포인터라는 점
    - 포인터가 가르키는 객체가 삭제될 때는 기본 클래스 포인터(Samsung * 포인터)를 통해 삭제되는 점
    - 기본 클래스에 들어 있는 소멸자가 비가상 소멸자 (non-virtual destructor)라는 점
  - C++ 규정에 따르면, 기본 클래스 포인터를 통해 파생 클래스 객체가 삭제될 때 해당 기본 클래스에 비가상 소멸자가 있으면 프로그램 동작은 미정의 사항이다.
  - 해결법
    ```
    class Samsung {
      public:
        Samsung();
        virtual ~Samsung();
    };
    Samsung * samsung = getSamsung();
    delete samsung;
    ```
- 상속되지 않는 클래스에 가상 소멸자를 적용하면 메모리 낭비가 생긴다.
  - vptr이 생긴다.

**다형성을 가진 기본 클래스에는 반드시 가상 소멸자를 선언해야 한다. 즉, 어떤 클래스가 가상 함수를 하나라도 갖고 있으면, 이 클래스의 소멸자도 가상 소멸자여야 한다.<br>**
**기본 클래스로 설계되지 않았거나 다형성을 갖도록 설계되지 않은 클래스에는 가상 소멸자를 선언하지 않아야 한다.<br>**

# 8. 예외가 소멸자를 떠나지 못하도록 붙들어 놓자

```
class DBConn {
  public:
    void close()
    {
      db.close();
      closed = true;
    }
    ~DBConn() {
      if (!closed)
      try {
        db.close();
      }
      catch(exception e) {
        //close 호출이 실패했다는 로그 작성
      }
    }
  private :
    DBConnection db;
    bool closed;
}
```
- close 호출의 책임을 DBConn의 소멸자에서 DBConn의 사용자로 떠넘긴다.
  - DBConn의 소멸자엔 사용자가 안할 경우 다시 호출하는 코드 작성
- 동작이 예외를 일으키면서 실패할 가능성이 있고 또 그 예외를 처리해야 할 필요가 있다면, 그 예외는 소멸자가 아닌 다른 함수에서 비롯되어야 한다.

**소멸자에서는 예외가 빠져나가면 안 된다. 만약 소멸자 안에서 호출된 함수가 예외를 던질 가능성이 있다면, 어떤 예외이든지 소멸자에서 모두 받아낸 후에 삼켜 버리든지 프로그램을 끝내든지 해야한다.<br>**
**어떤 클래스의 연산이 진행되다가 던진 예외에 대해 사용자가 반응해야 할 필요가 있다면, 해당 연산을 제공하는 함수는 반드시 보통의 함수(즉, 소멸자가 아닌 함수)이어야 한다.<br>**
