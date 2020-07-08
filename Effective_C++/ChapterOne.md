<h1>Index</h1>

---

[1. C++를 언어들의 연합체로 바라보는 안목은 필수](https://github.com/SkydevilK/Study/blob/master/Effective_C%2B%2B/ChapterOne.md#1-c%EB%A5%BC-%EC%96%B8%EC%96%B4%EB%93%A4%EC%9D%98-%EC%97%B0%ED%95%A9%EC%B2%B4%EB%A1%9C-%EB%B0%94%EB%9D%BC%EB%B3%B4%EB%8A%94-%EC%95%88%EB%AA%A9%EC%9D%80-%ED%95%84%EC%88%98)

[2. #define을 쓰려거든 const, enum, inline을 떠올리자](https://github.com/SkydevilK/Study/blob/master/Effective_C%2B%2B/ChapterOne.md#2-define%EC%9D%84-%EC%93%B0%EB%A0%A4%EA%B1%B0%EB%93%A0-const-enum-inline%EC%9D%84-%EB%96%A0%EC%98%AC%EB%A6%AC%EC%9E%90)

[3. 낌새만 보이면 const를 들이대 보자](https://github.com/SkydevilK/Study/blob/master/Effective_C%2B%2B/ChapterOne.md#3-%EB%82%8C%EC%83%88%EB%A7%8C-%EB%B3%B4%EC%9D%B4%EB%A9%B4-const%EB%A5%BC-%EB%93%A4%EC%9D%B4%EB%8C%80-%EB%B3%B4%EC%9E%90)

[4. 객체를 사용하기 전에 반드시 그 객체를 초기화 해야 한다.](https://github.com/SkydevilK/Study/blob/master/Effective_C%2B%2B/ChapterOne.md#4-%EA%B0%9D%EC%B2%B4%EB%A5%BC-%EC%82%AC%EC%9A%A9%ED%95%98%EA%B8%B0-%EC%A0%84%EC%97%90-%EB%B0%98%EB%93%9C%EC%8B%9C-%EA%B7%B8-%EA%B0%9D%EC%B2%B4%EB%A5%BC-%EC%B4%88%EA%B8%B0%ED%99%94-%ED%95%B4%EC%95%BC-%ED%95%9C%EB%8B%A4)

# 1. C++를 언어들의 연합체로 바라보는 안목은 필수

1. C
  - 데이터 타입, 배열, 포인터, 블록, 문장, 선행 처리자
2. 객체 지향 개념의 C++
  - 클래스, 상속, 다형형, 가상 함수, 캡슐화
3. 템플릿 C++
  - 일반화 프로그래밍 부분
4. STL
  - 템플릿 라이브러리

**C++를 사용한 효과적인 프로그래밍 규칙은 C++의 어떤 부분을 사용하느냐에 따라 달라진다.**

# 2. #define을 쓰려거든 const, enum, inline을 떠올리자
  
- #define을 사용하게 되면 컴파일러에게는 이름이 아닌 상수 값으로 보이기 때문에 오류를 찾을 때 문제가 생길 수 있다.

- #define을 상수로 교체할 때 주의점
  - 상수 포인터를 정의하는 경우
    - 포인터는 꼭 const로 선언해야 한다.
      ```
      const char* const name = "Skydevilk";
      ```
    - 문자열의 경우 string 객체를 사용하면 편하다.
      ```
      const std::string name = "Skydevilk";
      ```
  - 클래스 멤버로 상수를 정의하는 경우
    - 상수를 유일하게 만들고 싶으면 정적(static) 멤버로 만들어야 한다.
      ```
      class Samsung {
        private:
          static const String Device_Name = "GALAXY";
          string phoneBook[MAX_NUMBER];
       };
       ```
  - 매크로 함수를 정의하는 경우
    ```
    template<typename T>
    inline T MAX(const T& a, cont T& b)
       return a > b ? a : b;
     ```
 
 **1) 단순한 상수를 쓸 때는, #define보다 const 객체 혹은 enum을 우선 생각하자<br>**
 **2) 함수처럼 쓰이는 매크로를 만들려면, #define 매크로보다 인라인 함수를 우선 생각하자**

# 3. 낌새만 보이면 const를 들이대 보자

- 외부 변경을 불가능하게 하는 것을 소스 코드 수준에서 할 수 있다.
  1. 비상수 포인터, 비상수 데이터
    ```
    int a = 5;
    int* ptr = &a;
    *ptr = 3;
    ```
  2. 비상수 포인터, 상수 데이터
    ```
    int a = 5;
    const int * ptr = &a;
    *ptr = 3; // 변경 불가
    a = 3;    // 변경 가능
    ```
  3. 상수 포인터, 비상수 데이터
    ```
    int a = 5, b = 0;
    int * const ptr = *a;
    *ptr = 3; // 변경 가능
    ptr = &b; // 변경 불가
    ```
  4. 상수 포인터, 상수 데이터
    ```
    int a = 5, b = 5;
    const int * const ptr = &a;
    *ptr = 0; // 변경 불가
    ptr = &b; // 변경 불가
    ```
- 상수 멤버 함수
  - 해당 멤버 함수가 상수 객체에 대해 호출될 함수이다는 것을 알림
    ```
    class Samsung {
      public:
        const char& operator[] (std::size_t position) const {
          return text[position];
        }
        char& operator[] (std::size_t position) {
          return text[position];
        }
        
      private:
        std::string text;
    };
    
    Samsung samsung("Galaxy");
    samsung[0] = 'F';    // 변경 가능
    const Samsung cSamsung("Note");
    cSaumsung[0] = 'F';  // 변경 불가
    ```

**1) const를 붙여 선언하면 컴파일러가 사용상의 에러를 잡아내는 데 도움을 준다. const는 어떤 유효범위에 있는 객체나 함수 매개변수, 반환타입, 멤버함수에 붙을 수 있다.<br>**
**2) 컴파일러 쪽에서 보면 비트수준 상수성을 지켜야 하지만, 프로그래머는 개념적인(논리적인) 상수성을 사용해서 프로그래밍을 해야 한다.<br>**
**3) 상수 멤버 및 비상수 멤버 함수가 기능적으로 서로 똑같게 구현되어 있을 경우에는 코드 중복을 피하는 것이 좋다. 이때 비상수 버전이 상수 버전을 호출하도록 해라**

# 4. 객체를 사용하기 전에 반드시 그 객체를 초기화 해야 한다.

**1) 기본 데이터 타입의 객체는 직접 손으로 초기화한다.<br>**
**2) 생성자에서는 데이터 멤버에 대한 대입문을 생성자 본문 내부에 넣는 방법으로 멤버를 초기화하지 말고 멤버 초기화 리스트를 즐겨 사용하자. 그리고 초기화 리스트에 데이터 멤버를 나열할 때는 클래스에 각 데이터 멤버가 선언된 순서와 똑같이 나열하자.<br>**
```
class Samsung {
  private int number;
  private string deviceName;
  private int battery;
  Samsung(int _number, string _deviceName, int _battery):number(_number), deviceName(_deviceName), battery(_battery) {}
```
**3) 여러 번역 단위에 있는 비지역 정적 개게들의 초기화 순서는 무작위이다. 이를 해결하려면 비지역 정적 객체를 지역 정적 객체로 바꾸면 된다.**
