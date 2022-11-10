# mandatory
![mandatory](./mandatory/flowchart.png)
1. 철학자 스레드는 sleeping, thinking, eating을 반복하며 언제 어떤 행동을 취하는지를 출력합니다.  
2. 철학자가 제한 시간을 넘어 굶어 죽거나 먹는 횟수를 채우면, philo->end 플래그를 1로 바꾼 후 스레드를 종료합니다.
3. 모니터링 스레드는, 반복문을 돌면서 모든 스레드의 philo->end가 1인지를 검사합니다. 
# bonus
![bonus](./bonus/flowchart.png)