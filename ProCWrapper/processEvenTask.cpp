
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
           char  filnam[19];
};
static const struct sqlcxp sqlfpn =
{
    18,
    "processEvenTask.pc"
};


static unsigned int sqlctx = 20773443;


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
            void  *sqhstv[2];
   unsigned int   sqhstl[2];
            int   sqhsts[2];
            void  *sqindv[2];
            int   sqinds[2];
   unsigned int   sqharm[2];
   unsigned int   *sqharc[2];
   unsigned short  sqadto[2];
   unsigned short  sqtdso[2];
} sqlstm = {12,2};

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
5,0,0,1,31,0,4,16,0,0,2,1,0,1,0,1,3,0,0,2,3,0,0,
};


#line 1 "processEvenTask.pc"
#define SQLCA_STORAGE_CLASS extern
#include <sqlca.h>
#include <stdio.h>


/* EXEC SQL INCLUDE proc_all.h;
 */ 
#line 1 "proc_all.h"
void processAll(int task, int thid, sql_context ctx);

void processEvenTask(int task, int thid, sql_context ctx);

void processOddTask(int task, int thid, sql_context ctx);
#line 7 "processEvenTask.pc"

void processEvenTask(int task, int thid, sql_context ctx)
{
	/* EXEC SQL CONTEXT USE : ctx; */ 
#line 10 "processEvenTask.pc"

	/* EXEC SQL BEGIN DECLARE SECTION; */ 
#line 11 "processEvenTask.pc"

	int cal = 0;
	int value = 0;
	/* EXEC SQL END DECLARE SECTION; */ 
#line 14 "processEvenTask.pc"

	cal = 2 * task;
	/* EXEC SQL SELECT : cal INTO : value FROM DUAL; */ 
#line 16 "processEvenTask.pc"

{
#line 16 "processEvenTask.pc"
 struct sqlexd sqlstm;
#line 16 "processEvenTask.pc"
 sqlstm.sqlvsn = 12;
#line 16 "processEvenTask.pc"
 sqlstm.arrsiz = 2;
#line 16 "processEvenTask.pc"
 sqlstm.sqladtp = &sqladt;
#line 16 "processEvenTask.pc"
 sqlstm.sqltdsp = &sqltds;
#line 16 "processEvenTask.pc"
 sqlstm.stmt = "select :b0 into :b1  from DUAL ";
#line 16 "processEvenTask.pc"
 sqlstm.iters = (unsigned int  )1;
#line 16 "processEvenTask.pc"
 sqlstm.offset = (unsigned int  )5;
#line 16 "processEvenTask.pc"
 sqlstm.selerr = (unsigned short)1;
#line 16 "processEvenTask.pc"
 sqlstm.cud = sqlcud0;
#line 16 "processEvenTask.pc"
 sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 16 "processEvenTask.pc"
 sqlstm.sqlety = (unsigned short)4352;
#line 16 "processEvenTask.pc"
 sqlstm.occurs = (unsigned int  )0;
#line 16 "processEvenTask.pc"
 sqlstm.sqhstv[0] = (         void  *)&cal;
#line 16 "processEvenTask.pc"
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
#line 16 "processEvenTask.pc"
 sqlstm.sqhsts[0] = (         int  )0;
#line 16 "processEvenTask.pc"
 sqlstm.sqindv[0] = (         void  *)0;
#line 16 "processEvenTask.pc"
 sqlstm.sqinds[0] = (         int  )0;
#line 16 "processEvenTask.pc"
 sqlstm.sqharm[0] = (unsigned int  )0;
#line 16 "processEvenTask.pc"
 sqlstm.sqadto[0] = (unsigned short )0;
#line 16 "processEvenTask.pc"
 sqlstm.sqtdso[0] = (unsigned short )0;
#line 16 "processEvenTask.pc"
 sqlstm.sqhstv[1] = (         void  *)&value;
#line 16 "processEvenTask.pc"
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
#line 16 "processEvenTask.pc"
 sqlstm.sqhsts[1] = (         int  )0;
#line 16 "processEvenTask.pc"
 sqlstm.sqindv[1] = (         void  *)0;
#line 16 "processEvenTask.pc"
 sqlstm.sqinds[1] = (         int  )0;
#line 16 "processEvenTask.pc"
 sqlstm.sqharm[1] = (unsigned int  )0;
#line 16 "processEvenTask.pc"
 sqlstm.sqadto[1] = (unsigned short )0;
#line 16 "processEvenTask.pc"
 sqlstm.sqtdso[1] = (unsigned short )0;
#line 16 "processEvenTask.pc"
 sqlstm.sqphsv = sqlstm.sqhstv;
#line 16 "processEvenTask.pc"
 sqlstm.sqphsl = sqlstm.sqhstl;
#line 16 "processEvenTask.pc"
 sqlstm.sqphss = sqlstm.sqhsts;
#line 16 "processEvenTask.pc"
 sqlstm.sqpind = sqlstm.sqindv;
#line 16 "processEvenTask.pc"
 sqlstm.sqpins = sqlstm.sqinds;
#line 16 "processEvenTask.pc"
 sqlstm.sqparm = sqlstm.sqharm;
#line 16 "processEvenTask.pc"
 sqlstm.sqparc = sqlstm.sqharc;
#line 16 "processEvenTask.pc"
 sqlstm.sqpadto = sqlstm.sqadto;
#line 16 "processEvenTask.pc"
 sqlstm.sqptdso = sqlstm.sqtdso;
#line 16 "processEvenTask.pc"
 sqlcxt(&ctx, &sqlctx, &sqlstm, &sqlfpn);
#line 16 "processEvenTask.pc"
}

#line 16 "processEvenTask.pc"

	printf("Thread[%d], %d * 2 = %d\n", thid, task, cal);
}
