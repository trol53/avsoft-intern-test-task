#include <iostream>
#include <unistd.h>

#define READER_COUNT 10
#define WRITER_COUNT 1
#define DELAY 3
#define REPEAT_COUNT 2

int read_count = 0;
pthread_mutex_t r_mutex;
pthread_mutex_t w_mutex;

char* common_buffer;

void* reader(void* args){
    sleep(DELAY);
    pthread_mutex_lock(&r_mutex);
    read_count++;
    if (read_count == 1)
        pthread_mutex_lock(&w_mutex);
    pthread_mutex_unlock(&r_mutex);
    std::cout << "Read in thread: " << pthread_self() << '\n';
    printf("%s%ld", common_buffer);
    std::cout << '\n';
    pthread_mutex_lock(&r_mutex);
    read_count--;
    if (read_count == 0)
        pthread_mutex_unlock(&w_mutex);
    pthread_mutex_unlock(&r_mutex);
    return NULL;
}

void* writer(void* args){
    sleep(DELAY);
    pthread_mutex_lock(&w_mutex);
    sprintf(common_buffer, "%s%ld", "write: ", pthread_self());
    std::cout << "write complete\n";
    pthread_mutex_unlock(&w_mutex);
    return NULL;
}

void Run(){
    for (int i = 0; i < REPEAT_COUNT; i++){
        pthread_t readers[READER_COUNT];
        pthread_t writers[WRITER_COUNT];
        int status_r[READER_COUNT];
        int status_w[WRITER_COUNT];

        for (int j = 0; j < READER_COUNT; j++){
            status_r[j] = pthread_create(&readers[j], NULL, reader, NULL);
        }

        for (int j = 0; j < WRITER_COUNT; j++){
            status_w[j] = pthread_create(&writers[j], NULL, writer, NULL);
        }

        for (int j = 0; j < READER_COUNT; j++){
            status_r[j] = pthread_join(readers[j], NULL);
        }

        for (int j = 0; j < WRITER_COUNT; j++){
            status_w[j] = pthread_join(writers[j], NULL);
        }


    }
}

int main() {
    pthread_mutex_init(&r_mutex, NULL);
    pthread_mutex_init(&w_mutex, NULL);
    common_buffer = new char[16];
    void* tmp = writer(NULL);
    Run();

    return 0;
}
