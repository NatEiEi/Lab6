 #include <pthread.h>
 #include <stdio.h>
 #include <stdlib.h>

 int csum; // ประกาศเพื่อให้เป็น global
 void *childRunner(void *param);

 int main(int argc, char *argv[]) {
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    //thread child
    pthread_create(&tid, &attr, childRunner, argv[1]);
    
    //thread parent
    int msum = 0;
    for (int i = 1; i <= atoi(argv[1]); i++)
        msum +=i;

    pthread_join(tid, NULL);
    printf("csum - msum = %d\n", csum-msum);

    return 0;
 }

 void *childRunner(void *param) {
    int num = atoi(param);
    csum = 0;
    for (int i = 1; i <= num*2; i++)
        csum +=i;
    pthread_exit(0);
 }

// 2.5 หากไม่ join คำตอบที่ได้มีกี่แบบ อะไรบ้าง
// มี2 คำตอบ คือ 
// 1.กรณีที่แม่เสร็จก่อนลูก จะได้ = -msum
// 2.กรณีที่ลูกเสร็จก่อน จะได้ = csum - msum
