#include "DBWrapper.h"
#include "threadsafequeue.h"
#include  <atomic>

#define CONN_LEN 50
#define CONN_STRING "scott/TIGER@ORCL"

struct ThreadParameter;


class DBWrapperImpl : public DBWrapper
{
public:
	DBWrapperImpl();
	~DBWrapperImpl();

	void submit(int i);



private:
	void** m_parameters;
	static void sworker(ThreadParameter* parameter);
	void worker(int thid, sql_context ctx);
	static void processTask(int t, int thid, sql_context ctx);

private:
	std::atomic<bool> m_done;
	int m_threadCount;
	ThreadsafeQueue<int> m_taskQueue;
	JoinThreads* m_joiner;
	std::vector<std::thread> m_threads;

	ThreadParameter* m_threadParameters;
	void initContexts();
	void initThreads();
	void freeContexts();
	DBWrapperImpl(const DBWrapperImpl&) = delete;
	DBWrapperImpl& operator=(const DBWrapperImpl&) = delete;
private:
	EXEC SQL BEGIN DECLARE SECTION;
	//VARCHAR m_connectString[CONN_LEN];
	sql_context* m_ctxes;
	
	EXEC SQL END DECLARE SECTION;
};

