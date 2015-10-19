#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

time_t GetTodayZeroTime(time_t tNow)
{
    return ( ( (tNow - 57600)/86400 )*86400 + 57600 );
}

bool IsInSameDay(time_t tTm1, time_t tTm2)
{
    return ( (tTm1 - 57600) / 86400 == (tTm2 - 57600) / 86400 );
}

bool IsInSameWeek(time_t tTm1, time_t tTm2)
{
    return ( (tTm1 - 316022400) / 604800 == (tTm2 - 316022400) / 604800 );
}

time_t GetWeekBeginTime(time_t tNow)
{
    return ( (tNow - 316022400) / 604800 * 604800 + 316022400 );
}

time_t GetWeekEndTime(time_t tNow)
{
    return ( (tNow - 316022400) / 604800 * 604800 + 316627199 );    //316022400 + 604800 - 1 );
}

int main(int argc, char** argv)
{
    time_t currtime, one_hour_after, one_day_after, one_week_after;
    time(&currtime);
    one_hour_after = currtime + 3600; // 1小时之后
    one_day_after = currtime + 86400; // 1天之后
    one_week_after = currtime + 604800; // 1周之后

    printf("Today zero time ==> %d\n", GetTodayZeroTime(currtime));
    printf("Week begin time ==> %d\n", GetWeekBeginTime(currtime));
    printf("Week end time ==> %d\n", GetWeekEndTime(currtime));
    printf("Is in same day ==> (currtime|one_hour_after = %d), (currtime|one_day_after = %d)\n", 
            IsInSameDay(currtime, one_hour_after), IsInSameDay(currtime, one_day_after));
    printf("Is in same week ==> (currtime|one_week_after = %d), (one_day_after|one_week_after = %d)\n", 
            IsInSameWeek(currtime, one_week_after), IsInSameWeek(one_day_after, one_week_after));		

    return 0;
}
