<h1>1. Redis 소개</h1>
- In-Memory Data Structure Store

- 오픈소스

- Support data structures
  - strings, set, sorted-set, hashes, list
  
- Only 1 Committer

- 파레토 법칙 2:8

- 전체 요청의 80%는 20%의 사용자가 만들어낸다.

- 캐시구조
  - Look aside Cache
    - 캐시에 있으면 리턴, 없으면 캐시에 저장하고 리턴
  - Write Back
    - 모든 데이터를 캐시에 저장, 특정 시점에만 캐시 데이터 DB에 저장
    - ex) 로그를 캐시에 쌓아두고, 특정 시점마다 DB로

<h1>2. 왜 Collection이 중요한가</h1>
- 개발의 편의성

- 개발의 난이도

- 랭킹 서버를 구현한다면?
  - 간단한 방법은 DB에 넣고 score로.
  - 유저가 많다면?
  - Redis Sorted Set을 이용하면 랭킹을 구현할 수 있음.
  - 덤으로 Replication도 가능
  
- 친구리스트를 key-value 형태로 저장해야 한다면?
  - 레디스의 경우 자료구조가 Atomic하기 때문에 Race Condition을 피할 수 있음.
  
- 외부의 Collections을 잘 이용하는 것으로 우리가 비즈니스 로직에 집중할 수 있음. 시간 단축, 문제를 줄여줌.

- Redis 사용처
  - Remote Data Store
    - A, B, C 에서 데이터를 공유하고 싶을때
  - 한대에서만 필요하다면, 전역 변수를 쓰면 되지 않을까?
    - Redis 자체가 Atomic을 보장해준다.(싱글 스레드라서)
  - 주로 많이 쓰이는 곳들
    - 인증 토큰 등을 저장
    - 랭킹
    - 유저 API limit
    - 좌표

<h1>3. Redis Collections</h1>
- 데이터 컬렉션을 잘못 선택해서 속도 차이가 날 수 있음.

- Strings
  - Key-value
  - Key를 어떻게 잡을 것인가가 중요하다.
    - 키를 어떻게 잡느냐에 따라서 분산이 바뀔 수 있다.

- List
  - Lpush, Rpush : 시작과 끝이 데이터 추가 가능
  - LPOP, RPOP : 마찬가지로 시작과 끝 꺼내기 가능.

- Set
  - 중복 제거, 순서 없음. find 빠름
  - SADD, SMEMBERS, SISMEMBERS
  - 특정 유저를 Follow 하는 목록을 저장해 둔다면

- Sorted Set
  - score를 포함한 순서가 있는 Set
  - ZADD <Key> <Score> <Value>
  - 범위를 대상으로 데이터 가져올 수 있음
    - zrange

- 유저 랭킹 보드로 사용할 수 있음

- (주의) Sorted set의 score는 double 타입이기 때문에 값이 정확하지 않을 수 있다.
  - score는 실수형이기 때문에 실수하기 쉽다.(?ㅎ)
  - 어떤 특정 정수는 실수에서 표현이 안된다.
  - 컴퓨터에서는 실수가 표현할 수 없는 정수값들이 존재한다.
  - 자바스크립트에서 유저 ID를 보낸다면 Long 정수형으로 보내면 안된다. String으로 보내야 정상적으로 동작한다.

- Hash
  - Key Value 안에 sub key value가 존재하는 형태

- Collection 주의 사항
  - 하나의 컬렉션에 너무 많은 아이템을 담으면 좋지 않다.
    - 1만개 이하로 유지하는게 좋음
  - Expire는 Collection의 아이템 개별로 걸리지 않고 전체 Collection에 대해서만 걸린다.

<h1>4. Redis 운영</h1>
<h3>메모리 관리를 잘하자</h3>

- Physical 메모리 이상을 사용하면 문제가 발생한다.
  - Swap이 있다면 Swap 사용으로 해당 메모리 Page 접근시 마다 늦어진다.
  - Swap 이 한번 발생하면 계속 발생한다. 디스크 사용으로 인해 느려진다.
  - Swap이 없다면? OOM으로 죽을 수 있다.
  - Maxmemory를 설정하더라도 이보다 더 사용할 가능성이 크다.
    - 레디스는 메모리 allocator에 의존하는데. jemaloc
    - 1바이트만 달라고해도 jemaloc는 페이지 단위에 의해서 메모리를 주므로 4096을 할당한다.
    - 메모리 파편화가 일어나면, 레디스 사용량과 jemaloc 할당량이 달라진다.

- RSS

- 많은 업체가 현재 메모리를 사용해서 Swap을 쓰고 있다는 것을 모를때가 많다.

- 큰 메모리를 사용하는 instance 하나보다는 적은 메모리를 사용하는 instance 여러개가 안전하다.
  - 레디스는 Fork를 하게 되는데, read만 하면 상관없지만, write를 하게되면 최대 2배 사용한다.
  - 예를 들면 4코어 24기가 한대가 2배 사용하면 48기가 사용하지만,
  - 8기가 3대에서 1대가 2배를 사용하게 되면, 32기가만 사용하게 된다.

- 레디스는 메모리 파편화가 발생할 수 있음. 4.x대 부터...

- 메모리가 부족할 때는?
  - Cache is Cach!!!
    - 좀 더 메모리 많은 장비로 마이그레이션. 시점은 75% 정도
    - 메모리가 빡빡하면 마이그레이션 중에 문제가 발생할 수도
  - 아니면, 데이터 줄이기..

- 메모리를 줄이기 위한 설정
  - 기본적으로 Collection 들은 아래와 같은 자료구조 사용
    - Hash -> HashTable 하나 더 사용
    - Sorted Set -> Skiplist 와 HashTable 사용
    - Set -> HashTable 사용
    - 해당 자료구조들은 메모리를 많이 사용함

- ziplist를 사용하자
  - 선형으로 저장한다.
  - 인메모리 특성상 적은 개수라면 선형 탐색을 하더라도 빠르다.
  - List, Hash, Sorted Set을 ziplist로 대체해서 처리하는 설정이 존재한다.
    - 30% 정도까지 적게 사용 가능하다.

<h3>O(N) 관련 명령어는 주의하자</h3>
- 레디스는 Sigle Threaded
  - 동시에 여러개의 명령을 처리할 수 있을까?
  - 참고로 단순한 get/set의 경우 초당 10만 TPS 이상 가능하다(CPU영향 가능)
  - 작업 하나가 1초 걸리면? 300ms 타임아웃 설정되어있으면 터진다.
  - Pocket으로 하나의 Command가 완성되면 processCommand로 처리함
  - 한번에 하나의 명령을 처리하므로 오래걸리는 명령을 수행하면 안된다.
  - 대표적인 O(N) 명령들
    - KEYS
    - FLUSHALL, FLUSHDB
    - Delete Collections
    - Get All Collections

- 대표적인 실수 사례
  - Key가 백만개 이상인데 확인을 위해 KEYS 명령을 사용하는 경우
    - 모니터링 스크립트가 1초에 한번씩 호출
  - 아이템이 몇만개든 hash, sorted set, set에서 데이터를 가져오는 경우
  - Spring security oath RedisTokenStore 이슈

- KEYS는 어떻게 대체할 것인가?
  - Scan 명령을 사용하는 것으로 하나의 긴 명령을 짧은 여러번의 명령으로 바꿀 수 있다.(cursor 방식)
  - 짧은 명령들 사이에 read 몇만개가 처리될 수 있다.

- Collection의 모든 아이템을 가져와야 할 때?
    - Collection의 일부만 가져오거나
    - 큰 Collections을 여러개의 Collection으로 나눠서 저장

- Spring security oath RedisTokenStore 이슈
  - Access Token의 저장을 List 자료구조를 통해서 이루어졌었음
  - 검색, 삭제시에 모든 item을 매번 찾아야함
  - 최신 버전에서는 Set(O(1))로 해결 함.
<h3>Replication</h3>

- Async Replication
  - Replication lag이 발생할 수 있다.
  - 리플리케이션 하는 틈 사이에 데이터가 바뀔 수 있다.

- 'Replicaof'(5.0.0 버전 이상) 명령으로 설정 가능
  - Replicaof hostname port

- DBMS로 보면 statement replication과 유사
  - DB에서 now는 1, 2가 다를 수 있음.

- Replication 설정 과정
  - Replicaof 명령 전달
  - Secondary는 Primary에 sync 명령 전달
  - Primary는 현재 메모리 상태 저장하기 위해 Fork

- 주의할 점
  - Replication 과정에서 Fork가 발생하므로 메모리 부족이 발생할 수 있다.
  - Redis-cli --rdb 명령은 현재 상태의 메모리 스냅샷을 가져오므로 문제를 발생시킴. 치명적
  - AWS나 클라우드의 Redis는 좀 다르게 구현되어서 해당 부분이 안정적
  - 많은 대수의 Redis 서버가 많은 Replica를 두고 있다면?
  - 네트웍 이슈나, 사람의 작업으로 동시에 replication이 재시도 되도록 하면 문제가 발생할 수 있다.

- 권장 설정 Tip
  - Maxclient 설정 50000
  - RDB/AOF 설정 off
    - 마스터에서는 무조건 off
  - 특정 commands disable
    - Keys
    - AWS의 ElasticCache는 이미 하고 있음
  - 전체 장애의 99%는 KEYS나 SAVE설정을 사용해서 발생
    - SAVE 주의.
  - 적절한 ziplist 설정
