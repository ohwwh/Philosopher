# Philosopher

# Summary
운영체제의 고전적인 문제인 식사하는 철학자 문제를 코드로 구현하고, 문제점을 해결해야 한다.
각각의 철학자는 스레드(or 프로세스)로 대표되며, 포크는 공유자원으로 대표된다. 식사를 하는 것은 cpu자원을 점유하는 것으로 표현된다. 과제에서 요구하는 것은 크게 세 가지이다.
1. 공유자원인 포크에 양 옆의 철학자가 동시에 접근할 수 없게 막아야 한다.
2. 각각의 철학자가 cpu를 점유하는 시간을 균등하게 배분할 수 있도록 스케쥴링해야 한다.
3. 모든 철학자가 동시에 하나의 포크를 집어 deadlock이 일어나는 상황을 방지해야 한다.  
  
    
	  
# Specifications  
(과제 pdf)  
실행 파일의 이름은 philo이다.  
전역변수는 사용할 수 없다.  
각 철학자는 thread여야 한다.  
포크는 각각의 철학자 사이에 놓여있으며, 철학자의 숫자만큼 존재한다.  
파일의 인자로, philosopher_num, time_to_eat, time_to_die, time_to_sleep을 받아야 한다. 각각 철학자의 숫자, 식사시간, 먹지 않으면 죽는 시간, 자는 시간이다. 여기에 추가로 must_eat 인자를 넣을 것인지 선택할 수 있다. 넣지 않으면 시뮬레이션은 철학자가 죽기 전까지 계속 돌아가며, 넣는다면 모든 철학자가 해당하는 횟수만큼 식사를 한 경우 종료된다.  
(Bonus)  
각 철학자는 process여야 한다.  
포크는 테이블의 가운데 철학자 숫자만큼 쌓여있다. 즉 madatory에서는 자기 양옆의 포크만 집을 수 있었지만, bonus에서는 아무 포크나 집을 수 있다.

# How to use  
make 실행
./philo philosopher_num time_to_die time_to_eat time_to_sleep
의 형태로 실행  
(bonus)  
make bonus 실행  
./philo philosopher_num time_to_die time_to_eat time_to_sleep

# What to learn?  
프로세스와 스레드의 개념  
프로세스와 스레드의 context switching  
CPU가 주어진 작업을 처리하는 방식  
멀티 프로세싱과 멀티 스레딩 작업에서 data race와 deadlock문제  
뮤텍스와 세마포어의 차이점, data race 및 deadlock 방지를 위한 뮤텍스와 세마포어 변수의 사용

## Features

