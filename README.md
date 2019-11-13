# 2019f_sogang_file_processing
Sogang univ. file processing project of 2019 fall by Jinhyeok Park


## 1. Record Types
  - 모든 레코드 타입은 Record라는 abstract class를 implement한다.
  - 레코드는 Member, NewsAgency, Subscription 총 세가지가 존재한다.
  - 각각의 레코드는 pack과 unpack 메소드를 갖는다.
    + pack과 unpack 메소드는 Buffer와 연관지어 사용된다.
    + pack은 Buffer에 레코드 내용을 저장하는 메소드다.(record ---pack---> buffer)
    + unpack은 Buffer로부터 레코드 내용을 가져오는 메소드다.(record <---unpack--- buffer)
  - 레코드의 필드 중 가변길이 레코드는 string 타입으로, 고정길이 레코드는 char 배열로 선언한다.

## 2. Project2 Issues
  - Member, NewsAgency와 Subscription의 file open 형식이 달라서인지, 혹은 새롭게 Delete 메소드를 Buffer 레벨에서 고쳐서 수행해서인지... 아주 많은 버그들이 발생한다...
  - 다음 프로젝트에서는 다시 top-down 방식으로 설계하여 자료구조를 갈아 엎어야 할듯 하다.
