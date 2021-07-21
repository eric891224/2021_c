# 2021_c

# pthread 筆記

    #include <stdio.h>
    #include <pthread.h>
    #include <stdlib.h>
    #include <unistd.h>

    //-------------------------------------------------------------------------------------------
    //pthread_create
    /*
    定義：int pthread_create(pthread_t *tid , const pthread_attr_t *attr , void *(*function)(void *) , void *argument)
    1)  pthread_t *tid為pthread的指標，在使用Thread之前必須要先宣告一個pthread_t的變數
    2)  const pthread_attr_t *attr為該Thread的屬性，預設是NULL，如果沒有其他特殊的需求直接填入NULL即可
    3)  void *(*function)(void *)為Function pointer，這邊要放入你要執行的Function
    4)  void *argument為Function pointer所要帶的參數，若無需求填入NULL
    回傳值: 如果執行成功則回傳0，如果執行失敗則回傳錯誤代碼
    */
    //-------------------------------------------------------------------------------------------
    //pthread_exit
    /*
    定義：void pthread_exit(void *value_ptr) 作用：關閉一個Thread，附帶有一個參數
    1)  void *value_ptr用來設定執行成功時該Thread會回傳的值，這個值可由pthread_join()這個Function來取得
    回傳值: 不會回傳任何值

    EX：pthread_exit(NULL);
    */
    //-------------------------------------------------------------------------------------------
    //pthread_cancel
    /*
    定義：int pthread_cancel(pthread_t thread) 作用：關閉一個指定的Thread，附帶有一個參數
    1)  pthread_t thread為要關閉的Thread
    回傳值: 如果執行成功則回傳0，如果執行失敗則回傳錯誤代碼

    EX：pthread_cancel(thread1);
    */
    //-------------------------------------------------------------------------------------------
    //pthread_join
    /*
    作用：暫停目前執行pthread_join的Thread，等到目標Thread執行完畢之後，
          目前執行pthread_join的Thread才會繼續執行，附帶有2個參數

    定義：int pthread_join(pthread_t thread, void **value_ptr)
    1)  pthread_t thread為要等待的目標Thread
    2)  void **value_ptr用來取得目標Thread的回傳值
    回傳值: 如果執行成功則回傳0，如果執行失敗則回傳錯誤代碼
    */
    //-------------------------------------------------------------------------------------------

    //Thread函式
    void *thread_Fcn(void *parm){
        /*
            你的Thread要執行的程式寫在這裡
        */
        int j=0;
        while (j<30){
            printf("thread\n");
            j++;
        }

        //如果Thread內容都跑完了，就呼叫這個函式結束這個Thread
        pthread_exit(NULL);
    }

    int main(int argc, char **argv)
    {
        pthread_t thread_1;
        int rc1=0;

        //建立一個 thread
        rc1=pthread_create(&thread_1,NULL,thread_Fcn,NULL);
        if(rc1)
        {
            //進行檢測，要確定Thread有被正確建立
            printf("ERROR thread create!");
        }
        int i=0;
        while (i<30){
            printf("main\n");
            i++;
        }
        //等待thread執行結束，否則就一直等著
        rc1=pthread_join(thread_1,NULL);

        return 0;
    }

###
# GCC編譯指令
一c檔案hello.c如下  

    // hello.c
    #include <stdio.h>
    int main() {
      printf("Hello, world!\n");
      return 0;
    }
    
### 以GCC直接編譯(output為a.out)

    gcc hello.c >> a.out
    ./a.out >> Hello, world!

### 輸出特定檔名

    gcc -o hello hello.c >> hello
    hello >> Hello, world!
    
若要編譯c++檔案，以g++代替gcc

### 除錯用參數(-Wall)；使用gdb除錯(-g)

    # 顯示警告訊息、加入除錯資訊
    g++ -Wall -g -o hello hello.cpp
    
### 定義聚集Macro(待補)

### 只編譯不連結(-c)

    # 僅編譯、不連結，建立 obj 檔案
    gcc -c hello.c

若要進行連結(-o)

    # 連結產生執行檔
    gcc -o hello hello.o
    
例子

    # 編譯個別 C 檔案
    gcc -c a.c
    gcc -c b.c
    gcc -c c.c

    # 連結
    gcc -o myapp a.o b.o c.o
    
### CPU最佳化
根據 CPU 的架構，進行最佳化處理，編譯出效能更好的執行檔
-O(跟-O1 相同)、-O2 與 -O3，數字越高代表最佳化的程度越高

    # 進行最佳化
    gcc -O2 -o hello hello.c
    
### 連結標頭檔
若有額外的標頭檔路徑，用-I增加路徑

    # 新增標頭檔搜尋路徑
    gcc -I/home/gtwang/include -o hello hello.c
    
### 連結函式庫
若有一個libsum.a 函式庫放在 /home/gtwang/lib 目錄下
#### 1. 將函式庫當作一般檔案進行處理

    gcc -o hello hello.c /home/gtwang/lib/libsum.a
    
#### 2. 以-L搜索函式庫路徑；-l為函式庫檔名(去掉lib)

    gcc -o hello -L/home/gtwang/lib -lsum hello.c
