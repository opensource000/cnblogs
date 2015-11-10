#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <errno.h>  
#include <fcntl.h>
#include <sys/time.h>
#include <string>
#include <vector>
#include <stdint.h>

#define rdtscll_64(val) do {\
unsigned int __a,__d; \
__asm__ __volatile__("rdtsc" : "=a" (__a), "=d" (__d)); \
(val) = (((unsigned long long)__d)<<32) | (__a); \
} while(0);

class CTscStat
{
public:
    CTscStat(const std::string& sCallerName)
    : m_sCallerName(sCallerName)
    {
        rdtscll_64(m_start);
        rdtscll_64(m_lastcall);
    }

    ~CTscStat()
    {
        uint64_t end;
        rdtscll_64(end);
        uint64_t totalConsumeTsc = end - m_start;
        printf("TscStat---TOTAL:func=[%s] tsc_cost=[%lu]\n", m_sCallerName.c_str(), totalConsumeTsc);
    }

    void AddCall(const std::string& sCall)
    {
        AddCall(sCall, GetTscSub());
    }

private:
    void AddCall(const std::string& sCallerName, uint64_t consumeTsc)
    {
    	printf("TscStat---SubCall:func=[%s] sub_func=[%s] tsc_cost=[%lu]\n",
            m_sCallerName.c_str(), sCallerName.c_str(), consumeTsc);
        rdtscll_64(m_lastcall);
    }

    uint64_t GetTscSub()
    {
        uint64_t now;
        rdtscll_64(now);
        
        return now - m_lastcall;
    }

private:
    struct SCall
    {
        std::string sCallerName;
        uint64_t    consumeTsc;
    };

private:
    std::string         m_sCallerName;  // 统计接口
    std::vector<SCall>  m_vecCall;      // 请求列表

    uint64_t            m_start;        // 开始TSC
    uint64_t            m_lastcall;     // 上次TSC
};

#define TSC_START(sCn) CTscStat oTscS(sCn);
#define TSC_APICALL(API) \
        do { \
            oTscS.AddCall(API); \
        } while(0)

class CTimeStat
{
public:
    CTimeStat(const std::string& sCallerName)
    : m_sCallerName(sCallerName)
    {
        gettimeofday(&m_start, 0);
        gettimeofday(&m_lastcall, 0);
    }

    ~CTimeStat()
    {
        struct timeval end;
        struct timeval subresult;

        gettimeofday(&end, 0);
        timersub(&end, &m_start, &subresult);
        uint32_t dwTotalConsumeTime = subresult.tv_sec * 1000 + subresult.tv_usec / 1000;

        printf("TimeStat---TOTAL:func=[%s] time_cost=[%u]\n", m_sCallerName.c_str(), dwTotalConsumeTime);
    }

    void AddCall(const std::string& sCall)
    {
        AddCall(sCall, GetTimeSub());
    }

private:
    void AddCall(const std::string& sCallerName, uint32_t dwConsumeTime)
    {
    	printf("TimeStat---SubCall:func=[%s] sub_func=[%s] time_cost=[%u]\n",
            m_sCallerName.c_str(), sCallerName.c_str(), dwConsumeTime);
        gettimeofday(&m_lastcall, 0);
    }

    uint32_t GetTimeSub()
    {
        struct timeval now;
        struct timeval subresult;
        gettimeofday(&now, 0);

        timersub(&now, &m_lastcall, &subresult);

        return subresult.tv_sec * 1000 + subresult.tv_usec / 1000;
    }

private:
    struct SCall
    {
        std::string sCallerName;
        uint32_t    dwConsumeTime;
    };

private:
    std::string         m_sCallerName;  // 统计接口
    std::vector<SCall>  m_vecCall;      // 请求列表

    struct timeval      m_start;        // 开始时间
    struct timeval      m_lastcall;     // 上次请求时间
};

#define TS_START(sCn) CTimeStat oTimeS(sCn);
#define TS_APICALL(API) \
        do { \
            oTimeS.AddCall(API); \
        } while(0)

void funcA()
{
    usleep(1000); // 1ms
}

void funcB()
{
    usleep(100000); // 100ms
}

void funcC()
{
    sleep(1); // 1s
}

void TestTsc()
{
    TSC_START("TestTsc");
    funcA();
    TSC_APICALL("funcA");
    funcB();
    TSC_APICALL("funcB");
    funcC();
    TSC_APICALL("funcC");
}

void TestTime()
{
    TS_START("TestTsc");
    funcA();
    TS_APICALL("funcA");
    funcB();
    TS_APICALL("funcB");
    funcC();
    TS_APICALL("funcC");
}

int main(int argc, char** argv)  
{ 
    ////////// tsc ///////////
    TestTsc();
    
    ///////// time ///////////
    TestTime();
    
    return 0;
}  