#pragma once


#define LOG_W_ALL 1
#define LOG_W_DOS 2
#define LOG_W_FILE 3
#define LOG_W_WARNING 4
#define LOG_W_ERROR 5
#define LOG_W_NOTHING 6


#define _LOG_DEBUG_1 0xD001 //轻量，关键流程信息打印
#define _LOG_DEBUG_2 0xD002 //中度，内部调用子接口调试；
#define _LOG_DEBUG_3 0xD003 //全部，接口进入，接口退出，等待，死锁；