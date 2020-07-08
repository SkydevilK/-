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
 
 **단순한 상수를 쓸 때는, #define보다 const 객체 혹은 enum을 우선 생각하자<br>**
 **함수처럼 쓰이는 매크로를 만들려면, #define 매크로보다 인라인 함수를 우선 생각하자**
