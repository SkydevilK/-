# 13. 자원 관리에는 객체가 그만!

```
class Samsung(...);
Samsung * createSamsung();
```
```
void f()
{
  Samsung *pSamsung = createSamsung(); // 팩토리 함수 호출
  ...
  do Something
  ...
  delete pSamsung;  // 객체 소멸
}
```
- 문제점 (Memory Leak)
  - doSomething 부분에서 return 혹은 continue 등이 있을 경우 delete 문까지 도달 할 수 없다.
  - doSomething 부분에서 예외를 던질 경우 delete 문까지 도달 할 수 없다.
  
- 해결 방법
  - 스마트 포인터
    - 자원을 객체에 넣고 그 자원 해제를 소멸자가 맡도록 하며, 그 소멸자는 실행 제어가 블록 혹은 함수에서 떠날 때 호출되도록 한다.
  ```
  void f()
  {
    std::auto_ptr<Samsung> pSamsung(createSamsung());
    ...
    do Something
    ...
  } // auto_ptr의 소멸자를 통해 pSamsung을 소멸시킨다.
  ```
- 자원을 획득한 후 자원 관리 객체에 넘긴다.
  -  Resource Acquisition Is Initialization(RAII)
    - 자원 획득과 자원 관리 객체의 초기화가 한 문장에서 이루어 지는 것
- 자원 관리 객체는 자신의 소멸자를 사용해서 자원이 확실히 해제되도록 한다.
  - 소멸자는 어떤 객체가 소멸될 때(유효범위를 벗어나는 경우가 한 가지 예) 자동적으로 호출되기 때문에, 실행 제어가 어떤 경위로 블록을 떠나는가에 상관없이 자원 해제가 제대로 이루어지게 되는 것이다.

- auto_ptr
  - auto_ptr 객체를 복사하면 원본 객체는 null로 만든다.
    ```
    std::auto_ptr<Samsung> pSamsung(createSamsung());
    std::auto_ptr<Samsung> pSamsung2(pSamsung);   // pSamsung2는 객체를 가르키고 pSamsung은 null이 된다.
    pSamsung = pSamsung2;                         // pSamsung은 객체를 가르키고 pSamsung2는 null이 된다.
    ```
  - STL 컨테이너의 경우 원소들이 '정상적인' 복사 동작을 가져야 하기 때문에 auto_ptr을 사용할 수 없다.

- 참조 카운팅 방식 스마트 포인터(reference-counting smart pointer : RCSP)
  - 특정한 어떤 자원을 가르키는(참조하는) 외부 객체의 개수를 유지하고 있다가 그 개수가 0이 되면 해당 자원을 자동으로 삭제하는 스마트 포인터이다.
  - 참조 상태가 고리를 이루는 경우(다른 두 객체가 서로를 가르키는 경우 등)를 없앨 수 없다는 단점이 있다.
  ```
  void f()
  {
    std::tr1::shared_ptr<Samsung> pSamsung(createSamsung());
    std::tr1::shared_ptr<Samsung> pSamsung2(pSamsung);  // pSamsung과 pSamsung2는 동시에 해당 객체를 가르키고 있다.
    pSamsung = pSamsung2; // 변함없이 해당 객체를 가르키고 있다.
  } // pSamsung 과 pSamsung2는 소멸되며, 이드링 가르키고 있는 객체도 자동 소멸 된다.
  ```

- auto_ptr과 tr1::shared_ptr은 소멸자 내부에서 delete 연산을 사용한다.
  - 동적으로 할당한 배열에 대해 auto_ptr과 tr1::shared_ptr을 사용하면 안된다.
  
**자원 누출을 막기 위해, 생성자 안에서 자원을 획득하고 소멸자에서 그것을 해제하는 RAII 객체를 사용해야 한다.<br>**
**일반적으로 널리 쓰이는 RAII 클래스는 auto_ptr과 tr1::shared_ptr이다. tr1::shared_ptr이 복사 시의 동작이 직관적이기 때문에 대개 더 좋다. 반면, auto_ptr은 복사되는 객체(원본 객체)를 null로 만들어 버린다.<br>**

# 14. 자원 관리 클래스의 복사 동작에 대해 진지하게 고찰하자

```
class Lock {
  public:
    explicit Lock(Mutex *pm) : mutexPtr(pm)
    {
      lock(mutexPtr);
    }
    ~Lock()
    {
      unlock(mutexPtr);
    }
  private:
    Mutex *mutexPtr;
};
```
```
// 정상적으로 실행이 된다.
Mutex m;
{
  Lock m1(&m);
}
```
- Lock 객체가 복사 될 경우
```
Lock ml1(&m);
Lock ml2(ml1);
```
  - 복사를 금지한다.
    ```
    class Lock: private Uncopyable {
      public:
      ...
    };
    ```
  - 관리하고 있는 자원에 대해 참조 카운팅을 수행한다.
    - tr1::shared_ptr에 삭제자(deleter)를 지정한다.
      - deleter는 tr1::shared_ptr이 유지하는 참조 카운트가 0이 되었을 때 호출되는 함수 혹은 함수 객체를 말한다.
    ```
    class Lock {
      public:
        explicit Lock(Mutex *pm) : mutexPtr(pm, unlock) // 삭제자로 unlock 함수를 사용한다.
        {
          lock(mutexPtr.get());
        }
      private:
        std::tr1::shared_ptr<Mutex> mutexPtr; // 원시 포인터 대신에 shared_ptr을 사용한다.
    };
    ```
  - 관리하고 있는 자원을 진짜로 복사한다.
    - deep copy를 수행한다.
  - 관리하고 있는 자원의 소유권을 옮긴다.
    - auto_ptr의 복사 동작이다.

**RAII 객체의 복사는 그 객체가 관리하는 자원의 복사 문제를 안고 가기 때문에, 그 자원을 어떻게 복사하느냐에 따라 RAII 객체의 복사 동작이 결정된다.<br>**
**RAII 클래스에 구현하는 일반적인 복사 동작은 복사를 금지하거나 참조 카운팅을 해 주는 선으로 마루리 한다.<br>**

# 15. 자원 관리 클래스에서 관리되는 자원은 외부에서 접근할 수 있도록 하자

```
int battery(const Samsung *pSamsung);
int batteryLevel = battery(pSamsung); // 에러
```
- Samsung의 포인터를 원하는데 tr1::shared_ptr<Samsung> 타입의 객체를 반환하고 있어서 이다.

- 해결방법
  - 명시적 변환
    - tr1::shared_ptr과 auto_ptr은 get이라는 명시적 변환을 수행하는 멤버 함수가 있다.
    ```
    int batteryLevel = battery(pSamsung.get());
    ```
    
  - 암시적 변환
    ```
    class Samsung {
      public:
        bool isBatterySafe() const;
    };
    Samsung * createSamsung();
    std::tr1::shared_ptr<Samsung> pSamsung(createSamsung());
    bool check = !(pSamsung->isBatterySafe());
    std::auto_ptr<Samsung> pSamsung2(createSamsung());
    bool check2 = !((*pSamsung2).isBatterySafe());
    ```
  
**실제 자원을 직접 접근해야 하는 기존 API들도 많기 때문에, RAII 클래스를 만들 때는 그 클래스가 관리하는 자원을 얻을 수 있는 방법을 열어 주어야 한다.<br>**
**자원 접근은 명시적 변환 혹은 암시적 변환을 통해 가능하다. 안전성만 따지면 명시적 변환이 대체적으로 더 좋지만, 고객 편의성을 놓고 보면 암시적 변환이 괜찮다.<br>**
 
# 16. new 및 delete를 사용할 때는 형태를 반드시 맞추자

- **new 표현식에 []를 썻으면, 대응되는 delete 표헌식에도 []를 써야 한다.<br>**
- **new 표현식에 []를 안 썼으면, 대응되는 delete 표현식에도 []를 쓰지 말아야 한다.<br>**

# 17. new로 생성한 객체를 스마트 포인터에 저장하는 코드는 별도의 한 문장으로 만들자.

```
int priority();
void processWidget (std::tr1::shared_ptr<Widget> pw, int priority);
processWidget(new Widget, priority());
```
- 컴파일 에러가 발생한다. 
  - tr1::shared_ptr의 생성자는 explicit로 선언되어 있어서 new Widget 표현식에 의해 만들어진 포인터가 tr1::shared_ptr 타입의 객체로 바꾸는 암시적인 변환이 없다.
```
processWidget(std::tr1::shared_ptr<Widget>(new Widget), priority());
```
- 메모리 누수의 위험이 있다.
  - std::tr1::shared_ptr<Widget>(new Widget)
    - new Widget 표현식을 실행하는 부분
    - tr1::shared_ptr 생성자를 호출하는 부분
  - 컴파일러는 processWidget이 호출되기 전에 세 가지 연산을 위한 코드를 만들어야 한다.
    1. priority를 호출한다.
    2. new Widget을 실행한다.
    3. tr1::shared_ptr 생성자를 호출한다.
  - 연산 순서가 컴파일러마다 달라서 이런 식으로 호출될 수도 있다.
    1. new Widget을 실행한다.
    2. priority를 호출한다.
    3. tr1::shared_ptr 생성자를 호출한다.
    - 2번에서 예외가 발생 하면 new Widget으로 만들어졌던 포인터가 유실된다.

- 해결 방법
  ```
  std::tr1::shared_ptr<Widget> pw(new Widget);
  processWidget(pw, priority());
  ```

**new로 생성한 객체를 스마트 포인터로 넣는 코드는 별도의 한 문장으로 만들자. 이것이 안 되어 있으면, 예외가 발생 할 때 디버깅하기 힘든 메모리 릭이 발생할 수 있다.<br>**
