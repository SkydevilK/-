HTTP 요청 방식
-	Get : 데이터를 조회하기 위한 요청 뒤로가기 or 반복된 요청 문제 없음
-	Post : 데이터를 추가하거나 갱신하는데 사용 뒤로가기 or 반복된 요청 문제 발생
Servlet에서 요청(HttpServletRequest)와 응답(HttpServletResponce) 활용 방법
-	HttpServletRequest : 요청에 대한 정보(Input)
-	HttpServletResponse : 브라우저에서 정보를 표현하기 위해 사용(Output)
파일 전송을 위한 MultiPart
-	바이너리 데이터 전송을 위해 사용.
필터의 역할
-	전처리 작업을 위해 사용.
-	필터는 필터 인터페이스를 상속받아 생성.
-	Init(초기화), destory(소멸), doFilter(필터 기능 사용)
HTTP 프로토콜은 비상태(stateless) 프로토콜
-	클라이언트에서 상태 관리는 쿠키
-	서버에서 상태 관리는 세션

IoC (Inversion of Control)
-	프로그래머가 작성한 프로그램이 재사용 라이브러리의 흐름 제어를 받게 되는 소프트웨어 디자인 패턴을 말한다. IoC 패턴이 적용된 구조에서는 외부 라이브러리의 코드가 프로그래머가 작성한 코드를 호출한다. 설계 목적상 제어 반전의 목적은 다음과 같다
    -	작업을 구현하는 방식과 작업 수행 자체를 분리한다.
    -	모듈을 제작할 때, 모듈과 외부 프로그램의 결합에 대해 고민할 필요 없이 모듈의 목적에 집중할 수 있다.
    -	다른 시스템이 어떻게 동작할지에 대해 고민할 필요 없이, 미리 정해진 협약대로만 동작하게 하면 된다.
    -	모듈을 바꾸어도 다른 시스템에 부작용을 일으키지 않는다.

DI (Dependency Injection)
-	의존성 주입(Dependency Injection, DI)은 프로그래밍에서 구성요소간의 의존 관계가 소스코드 내부가 아닌 외부의 설정파일 등을 통해 정의되게 하는 디자인 패턴 중의 하나이다.
-	마틴 파울러는 다음과 같은 세 가지의 의존성 주입 패턴을 제시하였다.
    - 생성자 주입 : 필요한 의존성을 모두 포함하는 클래스의 생성자를 만들고 그 생성자를 통해 의존성을 주입한다.
    -	세터(Setter)를 통한 주입 : 의존성을 입력받는 세터(Setter) 메소드를 만들고 이를 통해 의존성을 주입한다.
    -	인터페이스(Interface)를 통한 주입 : 의존성을 주입하는 함수를 포함한 인터페이스를 작성하고 이 인터페이스를 구현하도록 함으로써 실행시에 이를 통하여 의존성을 주입한다.

스프링 MVC 요청 처리
1. 클라이언트에서 서버에 Request 요청 보냄
2. Dispatcher Servlet에서 요청을 받은 후, Handler Mapping에서 Handler 검색
3. Handler Mapping에서 Dispatcher Servlet으로 Handler Name 전달
4. Dispatcher Servlet에서 해당 Handler로 Request
5. Service 에 전달
6. Movel / View 이름을 Dispatcher Servlet로 보냄
7. Dispatcher Servlet에서 View Resover에 해당 View Name을 검색 요청
8. View Resover에서 Dispatcher Servlet로 해당 View 주소를 전달
9. Dispatcher Servlet에서 View에 Model 전달
10. View에서 Dispatcher Servlet로 Response 전달
11. Dispatcher Servlet에서 클라이언트에게 Response 전달.
![Spring MVC Image](https://user-images.githubusercontent.com/48668211/82980736-200a4700-a025-11ea-8101-df74c1cfa46c.png)


인터셉터란?
- 컨트롤러가 요청을 처리하기 전(pre) 후(post)에 대한 로직을 추가할 수 있다.
