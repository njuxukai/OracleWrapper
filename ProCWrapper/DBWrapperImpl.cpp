
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
  struct sql_cursor
  {
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned int magic;
  };
  typedef struct sql_cursor sql_cursor;
  typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
  unsigned char *tvnvsn; 
  unsigned short tvnvsnl; 
  unsigned char *tvnnm;
  unsigned short tvnnml; 
  unsigned char *tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
  unsigned int adtvsn; 
  unsigned short adtmode; 
  unsigned short adtnum;  
  sqltvn adttvn[1];       
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
  1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss
{
  unsigned int tdsvsn; 
  unsigned short tdsnum; 
  unsigned char *tdsval[1]; 
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
{
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp
{
  unsigned short fillen;
           char  filnam[17];
};
static const struct sqlcxp sqlfpn =
{
    16,
    "DBWrapperImpl.pc"
};


static unsigned int sqlctx = 4651739;


static struct sqlexd {
   unsigned int   sqlvsn;
   unsigned int   arrsiz;
   unsigned int   iters;
   unsigned int   offset;
   unsigned short selerr;
   unsigned short sqlety;
   unsigned int   occurs;
      const short *cud;
   unsigned char  *sqlest;
      const char  *stmt;
   sqladts *sqladtp;
   sqltdss *sqltdsp;
            void  **sqphsv;
   unsigned int   *sqphsl;
            int   *sqphss;
            void  **sqpind;
            int   *sqpins;
   unsigned int   *sqparm;
   unsigned int   **sqparc;
   unsigned short  *sqpadto;
   unsigned short  *sqptdso;
   unsigned int   sqlcmax;
   unsigned int   sqlcmin;
   unsigned int   sqlcincr;
   unsigned int   sqlctimeout;
   unsigned int   sqlcnowait;
              int   sqfoff;
   unsigned int   sqcmod;
   unsigned int   sqfmod;
            void  *sqhstv[4];
   unsigned int   sqhstl[4];
            int   sqhsts[4];
            void  *sqindv[4];
            int   sqinds[4];
   unsigned int   sqharm[4];
   unsigned int   *sqharc[4];
   unsigned short  sqadto[4];
   unsigned short  sqtdso[4];
} sqlstm = {12,4};

// Prototypes
extern "C" {
  void sqlcxt (void **, unsigned int *,
               struct sqlexd *, const struct sqlcxp *);
  void sqlcx2t(void **, unsigned int *,
               struct sqlexd *, const struct sqlcxp *);
  void sqlbuft(void **, char *);
  void sqlgs2t(void **, char *);
  void sqlorat(void **, unsigned int *, void *);
}

// Forms Interface
static const int IAPSUCC = 0;
static const int IAPFAIL = 1403;
static const int IAPFTL  = 535;
extern "C" { void sqliem(unsigned char *, signed int *); }

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* cud (compilation unit data) array */
static const short sqlcud0[] =
{12,4130,1,0,0,
5,0,0,0,0,0,60,71,0,0,0,0,0,1,0,
20,0,0,0,0,0,58,75,0,0,1,1,0,1,0,3,109,0,0,
39,0,0,0,0,0,27,77,0,0,4,4,0,1,0,1,97,0,0,1,10,0,0,1,10,0,0,1,10,0,0,
70,0,0,2,0,0,30,100,0,0,0,0,0,1,0,
};


#line 1 "DBWrapperImpl.pc"
#include <iostream>

//#define SQLCA_STORAGE_CLASS extern
#include <sqlca.h>


/* EXEC SQL INCLUDE DBWrapperImpl.h;
 */ 
#line 1 "DBWrapperImpl.h"
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
	/* EXEC SQL BEGIN DECLARE SECTION; */ 
#line 41 "DBWrapperImpl.h"

	//VARCHAR m_connectString[CONN_LEN];
	sql_context* m_ctxes;
	
	/* EXEC SQL END DECLARE SECTION; */ 
#line 45 "DBWrapperImpl.h"

};

/* EXEC SQL INCLUDE proc_all.h;
 */ 
#line 1 "proc_all.h"
void processAll(int task, int thid, sql_context ctx);

void processEvenTask(int task, int thid, sql_context ctx);

void processOddTask(int task, int thid, sql_context ctx);
#line 9 "DBWrapperImpl.pc"


void err_report(const char* msg)
{
	if (sqlca.sqlcode != 0)
	{
		printf("%s[%d][%.*s]", msg, sqlca.sqlcode, sqlca.sqlerrm.sqlerrml, sqlca.sqlerrm.sqlerrmc);
		exit(0);
	}
}

DBWrapper::SPtr DBWrapper::CreateWrapper()
{
	return std::make_shared<DBWrapperImpl>();
}




void DBWrapperImpl::sworker(ThreadParameter* parameter)
{
	DBWrapperImpl* wrapper = (DBWrapperImpl*)parameter->wrapper;
	sql_context ctx = (sql_context)(*((sql_context*)parameter->pctx));
	int threadid = parameter->thid;
	wrapper->worker(threadid, ctx);

}


DBWrapperImpl::DBWrapperImpl() : m_done(false), m_threadCount(5), m_joiner(new JoinThreads(m_threads))
{
	initContexts();
	initThreads();
}

DBWrapperImpl::~DBWrapperImpl()
{
	m_done = true;
	if (m_joiner)
	{
		delete m_joiner;
		m_joiner = 0;
	}
	freeContexts();
}


void DBWrapperImpl::submit(int t)
{
	m_taskQueue.push(t);
}

void DBWrapperImpl::initContexts()
{
	m_ctxes = new sql_context[m_threadCount];
	

	/* EXEC SQL BEGIN DECLARE SECTION; */ 
#line 66 "DBWrapperImpl.pc"

	char connString[40];
	/* EXEC SQL END DECLARE SECTION; */ 
#line 68 "DBWrapperImpl.pc"

	strcpy_s(connString, CONN_STRING);

	/* EXEC SQL ENABLE THREADS; */ 
#line 71 "DBWrapperImpl.pc"

{
#line 71 "DBWrapperImpl.pc"
 struct sqlexd sqlstm;
#line 71 "DBWrapperImpl.pc"
 sqlstm.sqlvsn = 12;
#line 71 "DBWrapperImpl.pc"
 sqlstm.arrsiz = 0;
#line 71 "DBWrapperImpl.pc"
 sqlstm.sqladtp = &sqladt;
#line 71 "DBWrapperImpl.pc"
 sqlstm.sqltdsp = &sqltds;
#line 71 "DBWrapperImpl.pc"
 sqlstm.stmt = "";
#line 71 "DBWrapperImpl.pc"
 sqlstm.iters = (unsigned int  )1;
#line 71 "DBWrapperImpl.pc"
 sqlstm.offset = (unsigned int  )5;
#line 71 "DBWrapperImpl.pc"
 sqlstm.cud = sqlcud0;
#line 71 "DBWrapperImpl.pc"
 sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 71 "DBWrapperImpl.pc"
 sqlstm.sqlety = (unsigned short)4352;
#line 71 "DBWrapperImpl.pc"
 sqlstm.occurs = (unsigned int  )0;
#line 71 "DBWrapperImpl.pc"
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 71 "DBWrapperImpl.pc"
}

#line 71 "DBWrapperImpl.pc"

	
	for (int i = 0; i < m_threadCount; i++)
	{
		/* EXEC SQL CONTEXT ALLOCATE : m_ctxes[i]; */ 
#line 75 "DBWrapperImpl.pc"

{
#line 75 "DBWrapperImpl.pc"
  struct sqlexd sqlstm;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqlvsn = 12;
#line 75 "DBWrapperImpl.pc"
  sqlstm.arrsiz = 1;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqladtp = &sqladt;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqltdsp = &sqltds;
#line 75 "DBWrapperImpl.pc"
  sqlstm.stmt = "";
#line 75 "DBWrapperImpl.pc"
  sqlstm.iters = (unsigned int  )1;
#line 75 "DBWrapperImpl.pc"
  sqlstm.offset = (unsigned int  )20;
#line 75 "DBWrapperImpl.pc"
  sqlstm.cud = sqlcud0;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqlety = (unsigned short)4352;
#line 75 "DBWrapperImpl.pc"
  sqlstm.occurs = (unsigned int  )0;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqhstv[0] = (         void  *)&m_ctxes[i];
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqhstl[0] = (unsigned int  )sizeof(void *);
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqhsts[0] = (         int  )0;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqindv[0] = (         void  *)0;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqinds[0] = (         int  )0;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqharm[0] = (unsigned int  )0;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqadto[0] = (unsigned short )0;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqtdso[0] = (unsigned short )0;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqphsv = sqlstm.sqhstv;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqphsl = sqlstm.sqhstl;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqphss = sqlstm.sqhsts;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqpind = sqlstm.sqindv;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqpins = sqlstm.sqinds;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqparm = sqlstm.sqharm;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqparc = sqlstm.sqharc;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqpadto = sqlstm.sqadto;
#line 75 "DBWrapperImpl.pc"
  sqlstm.sqptdso = sqlstm.sqtdso;
#line 75 "DBWrapperImpl.pc"
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 75 "DBWrapperImpl.pc"
}

#line 75 "DBWrapperImpl.pc"

		/* EXEC SQL CONTEXT USE : m_ctxes[i]; */ 
#line 76 "DBWrapperImpl.pc"

		/* EXEC SQL CONNECT : connString; */ 
#line 77 "DBWrapperImpl.pc"

{
#line 77 "DBWrapperImpl.pc"
  struct sqlexd sqlstm;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqlvsn = 12;
#line 77 "DBWrapperImpl.pc"
  sqlstm.arrsiz = 4;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqladtp = &sqladt;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqltdsp = &sqltds;
#line 77 "DBWrapperImpl.pc"
  sqlstm.iters = (unsigned int  )10;
#line 77 "DBWrapperImpl.pc"
  sqlstm.offset = (unsigned int  )39;
#line 77 "DBWrapperImpl.pc"
  sqlstm.cud = sqlcud0;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqlety = (unsigned short)4352;
#line 77 "DBWrapperImpl.pc"
  sqlstm.occurs = (unsigned int  )0;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqhstv[0] = (         void  *)connString;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqhstl[0] = (unsigned int  )40;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqhsts[0] = (         int  )40;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqindv[0] = (         void  *)0;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqinds[0] = (         int  )0;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqharm[0] = (unsigned int  )0;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqadto[0] = (unsigned short )0;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqtdso[0] = (unsigned short )0;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqphsv = sqlstm.sqhstv;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqphsl = sqlstm.sqhstl;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqphss = sqlstm.sqhsts;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqpind = sqlstm.sqindv;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqpins = sqlstm.sqinds;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqparm = sqlstm.sqharm;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqparc = sqlstm.sqharc;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqpadto = sqlstm.sqadto;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqptdso = sqlstm.sqtdso;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqlcmax = (unsigned int )100;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqlcmin = (unsigned int )2;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqlcincr = (unsigned int )1;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqlctimeout = (unsigned int )0;
#line 77 "DBWrapperImpl.pc"
  sqlstm.sqlcnowait = (unsigned int )0;
#line 77 "DBWrapperImpl.pc"
  sqlcxt(&m_ctxes[i], &sqlctx, &sqlstm, &sqlfpn);
#line 77 "DBWrapperImpl.pc"
}

#line 77 "DBWrapperImpl.pc"

		if (sqlca.sqlcode == 0)
			printf("Logon succeed!\n");
	}

	m_threadParameters = new ThreadParameter[m_threadCount];
	for (int i = 0; i < m_threadCount; i++)
	{
		m_threadParameters[i].wrapper = (void*)this;
		m_threadParameters[i].pctx = (void*)&(m_ctxes[i]);
		m_threadParameters[i].thid = i;
	}

}

void DBWrapperImpl::freeContexts()
{
	if (m_ctxes)
	{
		for (int i = 0; i < m_threadCount; i++)
		{
			/* EXEC SQL WHENEVER SQLERROR DO err_report("RELEASE ERROR"); */ 
#line 98 "DBWrapperImpl.pc"

			/* EXEC SQL CONTEXT USE :m_ctxes[i]; */ 
#line 99 "DBWrapperImpl.pc"

			/* EXEC SQL COMMIT WORK RELEASE; */ 
#line 100 "DBWrapperImpl.pc"

{
#line 100 "DBWrapperImpl.pc"
   struct sqlexd sqlstm;
#line 100 "DBWrapperImpl.pc"
   sqlstm.sqlvsn = 12;
#line 100 "DBWrapperImpl.pc"
   sqlstm.arrsiz = 4;
#line 100 "DBWrapperImpl.pc"
   sqlstm.sqladtp = &sqladt;
#line 100 "DBWrapperImpl.pc"
   sqlstm.sqltdsp = &sqltds;
#line 100 "DBWrapperImpl.pc"
   sqlstm.iters = (unsigned int  )1;
#line 100 "DBWrapperImpl.pc"
   sqlstm.offset = (unsigned int  )70;
#line 100 "DBWrapperImpl.pc"
   sqlstm.cud = sqlcud0;
#line 100 "DBWrapperImpl.pc"
   sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 100 "DBWrapperImpl.pc"
   sqlstm.sqlety = (unsigned short)4352;
#line 100 "DBWrapperImpl.pc"
   sqlstm.occurs = (unsigned int  )0;
#line 100 "DBWrapperImpl.pc"
   sqlcxt(&m_ctxes[i], &sqlctx, &sqlstm, &sqlfpn);
#line 100 "DBWrapperImpl.pc"
   if (sqlca.sqlcode < 0) err_report("RELEASE ERROR");
#line 100 "DBWrapperImpl.pc"
}

#line 100 "DBWrapperImpl.pc"

			printf("Logged off!\n");
		}
		delete[] m_ctxes;
		m_ctxes = nullptr;
	}
	if (m_threadParameters)
	{
		delete[] m_threadParameters;
		m_threadParameters = nullptr;
	}
}

void DBWrapperImpl::initThreads()
{
	for (int i = 0; i < m_threadCount; i++)
	{
		m_threads.push_back(std::thread(&DBWrapperImpl::sworker, &m_threadParameters[i]));
	}
}


void DBWrapperImpl::worker(int thid, sql_context ctx)
{
	while (!m_done || !m_taskQueue.empty())
	{
		auto task = m_taskQueue.wait_and_pop(20);
		if (task.get())
		{
			processTask(*task, thid, ctx);
		}
	}
}

void DBWrapperImpl::processTask(int task, int thid, sql_context ctx)
{
	
		processAll(task, thid, ctx);
	
}