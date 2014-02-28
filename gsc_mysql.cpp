#include "gsc_mysql.hpp"

#if COMPILE_MYSQL == 1

/*
	Had the problem, that a query failed but no mysql_errno() was set
	Reason: mysql_query() didnt even got executed, because the str was undefined
	So the function quittet with stackReturnInt(0)
	Now its undefined, and i shall test it every time
*/

/*
	100 == mysql_init()
	101 == mysql_real_connect(mysql, host, user, pass, db, port)
	102 == mysql_close(mysql)
	103 == mysql_query(mysql, query)
	104 == mysql_errno(mysql)
	105 == mysql_error(mysql)
	106 == mysql_affected_rows(mysql)
	107 == mysql_store_result(mysql)
	108 == mysql_num_rows(result)
	109 == mysql_num_fields(result)
	110 == mysql_field_seek(result, position)
	111 == mysql_fetch_field()
	112 == mysql_fetch_row(result)
	113 == mysql_free_result(result)
*/


#include <mysql/mysql.h>

int gsc_mysql_init()
{
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_init()\n");
	#endif
	MYSQL *my;
	my = mysql_init(NULL);
	int ret = (int) my;
	return stackReturnInt(ret);
}

int gsc_mysql_real_connect()
{
	int mysql;
	char *host;
	char *user;
	char *pass;
	char *db;
	int port;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql);
	helper += stackGetParamString(2, &host);
	helper += stackGetParamString(3, &user);
	helper += stackGetParamString(4, &pass);
	helper += stackGetParamString(5, &db);
	helper += stackGetParamInt(6, &port);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_real_connect(mysql=%d, host=\"%s\", user=\"%s\", pass=\"%s\", db=\"%s\", port=%d)\n", mysql, host, user, pass, db, port);
	#endif
	
	if (helper != 6)
	{
		printf_hide("scriptengine> wrongs args for mysql_real_connect(...);\n");
		return stackPushUndefined();
	}
	
	mysql = (int) mysql_real_connect((MYSQL *)mysql, host, user, pass, db, port, NULL, 0);
	
	return stackReturnInt(mysql);
}

int gsc_mysql_close()
{
	int mysql;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_close(%d)\n", mysql);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for mysql_close(mysql);\n");
		return stackPushUndefined();
	}
	
	mysql_close((MYSQL *)mysql);
	
	return stackReturnInt(0);
}

int gsc_mysql_query()
{
	int mysql;
	char *sql;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql);
	helper += stackGetParamString(2, &sql);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_query(%d, \"%s\")\n", mysql, sql);
	#endif
	
	if (helper != 2)
	{
		printf_hide("scriptengine> wrongs args for mysql_query(...);\n");
		return stackPushUndefined();
	}
	
	int ret = mysql_query((MYSQL *)mysql, sql);	
	return stackReturnInt(ret);
}

int gsc_mysql_errno()
{
	int mysql;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_errno(%d)\n", mysql);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for mysql_close(mysql);\n");
		return stackPushUndefined();
	}
	
	int ret = mysql_errno((MYSQL *)mysql);
	return stackReturnInt(ret);
}

int gsc_mysql_error()
{
	int mysql;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_error(%d)\n", mysql);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for mysql_close(mysql);\n");
		return stackPushUndefined();
	}
	
	char *ret = (char *)mysql_error((MYSQL *)mysql);
	return stackPushString(ret);
}

int gsc_mysql_affected_rows()
{
	int mysql;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_affected_rows(%d)\n", mysql);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for mysql_affected_rows(mysql);\n");
		return stackPushUndefined();
	}
	
	int ret = mysql_affected_rows((MYSQL *)mysql);
	return stackReturnInt(ret);
}

int gsc_mysql_store_result()
{
	int mysql;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_store_result(%d)\n", mysql);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for mysql_store_result(mysql);\n");
		return stackPushUndefined();
	}
		
	MYSQL_RES *result;
	result = mysql_store_result((MYSQL *)mysql);

	int ret = (int) result;
	return stackReturnInt(ret);
}

int gsc_mysql_num_rows()
{
	int result;
	
	int helper = 0;
	helper += stackGetParamInt(1, &result);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_num_rows(result=%d)\n", result);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for mysql_num_rows(result);\n");
		return stackPushUndefined();
	}

	int ret = mysql_num_rows((MYSQL_RES *)result);
	return stackReturnInt(ret);
}

int gsc_mysql_num_fields()
{
	int result;
	
	int helper = 0;
	helper += stackGetParamInt(1, &result);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_num_fields(result=%d)\n", result);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for mysql_num_fields(result);\n");
		return stackPushUndefined();
	}

	int ret = mysql_num_fields((MYSQL_RES *)result);
	return stackReturnInt(ret);
}

int gsc_mysql_field_seek()
{
	int result;
	int offset;
	
	int helper = 0;
	helper += stackGetParamInt(1, &result);
	helper += stackGetParamInt(2, &offset);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_field_seek(result=%d, offset=%d)\n", result, offset);
	#endif
	
	if (helper != 2)
	{
		printf_hide("scriptengine> wrongs args for mysql_field_seek(result, offset);\n");
		return stackPushUndefined();
	}

	int ret = mysql_field_seek((MYSQL_RES *)result, offset);
	return stackReturnInt(ret);
}

int gsc_mysql_fetch_field()
{
	int result;
	
	int helper = 0;
	helper += stackGetParamInt(1, &result);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_fetch_field(result=%d)\n", result);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for mysql_fetch_field(result);\n");
		return stackPushUndefined();
	}

	MYSQL_FIELD *field = mysql_fetch_field((MYSQL_RES *)result);
	if (field == NULL)
		return stackPushUndefined();
	char *ret = field->name;
	return stackPushString(ret);
}

int gsc_mysql_fetch_row()
{
	int result;
	
	int helper = 0;
	helper += stackGetParamInt(1, &result);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_fetch_row(result=%d)\n", result);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for mysql_fetch_row(result);\n");
		return stackPushUndefined();
	}

	MYSQL_ROW row = mysql_fetch_row((MYSQL_RES *)result);
	if (!row)
	{
		#if DEBUG_MYSQL
		printf_hide("row == NULL\n");
		#endif
		return stackPushUndefined();
	}

	int ret = alloc_object_and_push_to_array();
	
	int numfields = mysql_num_fields((MYSQL_RES *)result);
	for (int i=0; i<numfields; i++)
	{
		if (row[i] == NULL)
			stackPushUndefined();
		else
			stackPushString(row[i]);
		
		#if DEBUG_MYSQL
		printf_hide("row == \"%s\"\n", row[i]);
		#endif
		push_previous_var_in_array_sub();
	}

	return ret;
}

int gsc_mysql_free_result()
{
	int result;
	
	int helper = 0;
	helper += stackGetParamInt(1, &result);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_free_result(result=%d)\n", result);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for mysql_free_result(result);\n");
		return stackPushUndefined();
	}

	mysql_free_result((MYSQL_RES *)result);
	return stackPushUndefined();
}



int gsc_mysql_real_escape_string()
{
	int mysql;
	char *str;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql);
	helper += stackGetParamString(2, &str);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_real_escape_string(%d, \"%s\")\n", mysql, str);
	#endif
	
	if (helper != 2)
	{
		printf_hide("scriptengine> wrongs args for mysql_real_escape_string(...);\n");
		return stackPushUndefined();
	}
	
	char *to = (char *) malloc(strlen(str) * 2 + 1);
	int ret = mysql_real_escape_string((MYSQL *)mysql, to, str, strlen(str));	
	int retString = stackPushString(to);
	free(to);
	return retString;
}

/* FUNCTIONS OF PREPARED STATEMENTS */




int gsc_mysql_stmt_init()
{
	int mysql;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_stmt_init(mysql=%d)\n", mysql); // print as %d, cause i cant print it with hex in .gsc
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for gsc_mysql_stmt_init(mysql);\n");
		return stackReturnInt(0);
	}

	MYSQL_STMT *stmt;
	stmt = mysql_stmt_init((MYSQL*)mysql);
	
	int ret = (int) stmt;
	return stackReturnInt(ret);
}

int gsc_mysql_stmt_close()
{
	int mysql_stmt;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_stmt_close(mysql_stmt=%d)\n", mysql_stmt);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for gsc_mysql_stmt_close(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = (int) mysql_stmt_close((MYSQL_STMT*)mysql_stmt);
	return stackReturnInt(ret);
}

int gsc_mysql_stmt_get_stmt_id()
{
	int mysql_stmt;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_stmt_get_stmt_id(mysql_stmt=%d)\n", mysql_stmt);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for gsc_mysql_stmt_get_stmt_id(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = ((MYSQL_STMT*)mysql_stmt)->stmt_id;
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_get_prefetch_rows()
{
	int mysql_stmt;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_stmt_get_prefetch_rows(mysql_stmt=%d)\n", mysql_stmt);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for gsc_mysql_stmt_get_prefetch_rows(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = ((MYSQL_STMT*)mysql_stmt)->prefetch_rows;
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_get_param_count()
{
	int mysql_stmt;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_stmt_get_param_count(mysql_stmt=%d)\n", mysql_stmt);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for gsc_mysql_stmt_get_param_count(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = ((MYSQL_STMT*)mysql_stmt)->param_count;
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_get_field_count()
{
	int mysql_stmt;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_stmt_get_field_count(mysql_stmt=%d)\n", mysql_stmt);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for gsc_mysql_stmt_get_field_count(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = ((MYSQL_STMT*)mysql_stmt)->field_count;
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_prepare()
{
	int mysql_stmt;
	char *sql;
	int len;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);
	helper += stackGetParamString(2, &sql);
	helper += stackGetParamInt(3, &len);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_stmt_prepare(mysql_stmt=%d, sql=%s)\n", mysql_stmt, sql);
	#endif
	
	if (helper != 3)
	{
		printf_hide("scriptengine> wrongs args for gsc_mysql_stmt_prepare(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = mysql_stmt_prepare((MYSQL_STMT*)mysql_stmt, sql, len);
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_bind_param()
{
	int mysql_stmt;
	int param;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);
	helper += stackGetParamInt(2, &param);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_stmt_bind_param(mysql_stmt=%d, param=%d)\n", mysql_stmt, param);
	#endif
	
	if (helper != 2)
	{
		printf_hide("scriptengine> wrongs args for gsc_mysql_stmt_bind_param(mysql_stmt, param);\n");
		return stackReturnInt(0);
	}

	int ret = mysql_stmt_bind_param((MYSQL_STMT*)mysql_stmt, (MYSQL_BIND*)param);
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_bind_result()
{
	int mysql_stmt;
	int result;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);
	helper += stackGetParamInt(2, &result);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_stmt_bind_result(mysql_stmt=%d, result=%d)\n", mysql_stmt, result);
	#endif
	
	if (helper != 2)
	{
		printf_hide("scriptengine> wrongs args for gsc_mysql_stmt_bind_result(mysql_stmt, result);\n");
		return stackReturnInt(0);
	}

	int ret = mysql_stmt_bind_result((MYSQL_STMT*)mysql_stmt, (MYSQL_BIND*)result);
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_execute()
{
	int mysql_stmt;
	int result;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_stmt_execute(mysql_stmt=%d)\n", mysql_stmt);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for gsc_mysql_stmt_execute(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = mysql_stmt_execute((MYSQL_STMT*)mysql_stmt);
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_store_result()
{
	int mysql_stmt;
	int result;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_stmt_store_result(mysql_stmt=%d)\n", mysql_stmt);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for gsc_mysql_stmt_store_result(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = mysql_stmt_store_result((MYSQL_STMT*)mysql_stmt);
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_fetch()
{
	int mysql_stmt;
	int result;
	
	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);
	
	#if DEBUG_MYSQL
	printf_hide("gsc_mysql_stmt_fetch(mysql_stmt=%d)\n", mysql_stmt);
	#endif
	
	if (helper != 1)
	{
		printf_hide("scriptengine> wrongs args for gsc_mysql_stmt_fetch(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = mysql_stmt_fetch((MYSQL_STMT*)mysql_stmt);
	return stackReturnInt(ret);
}

// execute, store_result, fetch


/*

## ##
## ##
# # #
# # #
#   #

*/

// call this tests with:
// set closer 180
// set closer 181


#if COMPILE_MYSQL_TESTS == 1

int gsc_mysql_test_0()
{
	printf_hide("c-mysql 22.02.2012 by 123123231\n");
	printf_hide("modified to gsc 10.05.2012 by 123123231\n");
	MYSQL *my;
	my = mysql_init(NULL);
	if (my == NULL)
	{
		printf_hide("ERROR: mysql_init()\n");
		return stackReturnInt(0);
	}
	
	my = mysql_real_connect(
		my,
		"127.0.0.1",
		"kung",
		"zetatest",
		"kung_zeta",
		3306,
		NULL,
		0
	);
	
	if (my == NULL)
	{
		printf_hide("ERROR: mysql_real_connect(): %d->\"%s\"\n", mysql_errno(my), mysql_error(my));
		mysql_close(my);
		return stackReturnInt(0);
	}
	
	//int ret = mysql_query(my, "SELECT 1 as first,2 as second,3  as third UNION SELECT 11,22,33");
	int ret = mysql_query(my, "SELECT * FROM players");
	
	if (ret != 0)
	{
		printf_hide("ERROR: mysql_query(): %d->\"%s\"\n", mysql_errno(my), mysql_error(my));
		mysql_close(my);
		return stackReturnInt(0);
	}
	
	printf_hide("affected rows: %d\n", mysql_affected_rows(my));
	
	MYSQL_RES *query;
	query = mysql_store_result(my);
	
	if (mysql_errno(my) != 0) /* do not check query==NULL, because thats also the case for like INSERT */
	{
		printf_hide("ERROR: mysql_store_result(my): %d->\"%s\"\n", mysql_errno(my), mysql_error(my));
		mysql_close(my);
		return stackReturnInt(0);
	}
	
	printf_hide("query-num rows: %d\n", mysql_num_rows(query));
	
	printf_hide("spalten im query: %d\n", mysql_num_fields(query));
	
	
	
	int numfields = mysql_num_fields(query);
	
	
	MYSQL_FIELD *field;
	int i;
	mysql_field_seek(query, 0);
	for (i=0; i<numfields; i++)
	{
		field = mysql_fetch_field(query);
		printf_hide("%s(%s), ", field->name, field->table);
	}
	printf_hide("\n");
	

	MYSQL_ROW row;
	while (row = mysql_fetch_row(query))
	{
		int i;
		
		for (i=0; i<numfields; i++)
			printf_hide("%s, ", row[i]);
		printf_hide("\n");
	}
	
	
	
	
	mysql_free_result(query);
	
	
	mysql_close(my);
	
	return stackReturnInt(1);
}

int gsc_mysql_test_1()
{
	printf_hide("test 1 10.05.2012 ;D\n");
	
	MYSQL *my;
	my = mysql_init(NULL);
	if (my == NULL)
	{
		printf_hide("ERROR: mysql_init()\n");
		return stackReturnInt(0);
	}
	
	my = mysql_real_connect(
		my,
		"127.0.0.1",
		"kung",
		"zetatest",
		"kung_zeta",
		3306,
		NULL,
		0
	);
	
	if (my == NULL)
	{
		printf_hide("ERROR: mysql_real_connect(): %d->\"%s\"\n", mysql_errno(my), mysql_error(my));
		mysql_close(my);
		return stackReturnInt(0);
	}
	
	int id = 10;
	
	{
		const char *sql = "SELECT 1 + ?,1 UNION SELECT 2+?,1 UNION SELECT 3,2 UNION SELECT 4,3";
		int ret;
		
		MYSQL_STMT *stmt;
		stmt = mysql_stmt_init(my);
		
		printf_hide("stmt->stmt_id = %d\n", stmt->stmt_id);
		printf_hide("stmt->prefetch_rows = %d\n", stmt->prefetch_rows);
		printf_hide("stmt->param_count = %d\n", stmt->param_count);
		printf_hide("stmt->field_count = %d\n", stmt->field_count);
		
		if (stmt == NULL)
		{
			printf_hide("ERROR: mysql_stmt_init(my): %d->\"%s\"\n", mysql_errno(my), mysql_error(my));
			mysql_close(my);
			return stackReturnInt(0);
		}
		ret = mysql_stmt_prepare(stmt, sql, strlen(sql));
		if (ret != 0)
		{
			printf_hide("ERROR: mysql_stmt_prepare(stmt, sql, strlen(sql)): %d->\"%s\"\n", mysql_errno(my), mysql_error(my));
			mysql_close(my);
			return stackReturnInt(0);
		}
		
		// set by mysql_stmt_prepare, before they are just default-values (0,1,0,0)
		// 
		printf_hide("stmt->stmt_id = %d\n", stmt->stmt_id);
		printf_hide("stmt->prefetch_rows = %d\n", stmt->prefetch_rows); // i dont know
		printf_hide("stmt->param_count = %d\n", stmt->param_count); // "SELECT ?,?" param_count=2
		printf_hide("stmt->field_count = %d\n", stmt->field_count); // "SELECT 1,2,3" field_count=3
		
		MYSQL_BIND param[2], result[2];
		memset(param, 0, sizeof(param));
		memset(result, 0, sizeof(result));
		
		int myNumAddresses[2];
		int paramIntA;
		int paramIntB;
		int resultIntA;
		int resultIntB;
		my_bool is_null[2];
		
		
		// JUST TO GET THE INFOS FAST :)
		printf_hide("sizeof(MYSQL_BIND)=%d\n", sizeof(MYSQL_BIND));
		printf_hide("MYSQL_TYPE_LONG=%d\n", MYSQL_TYPE_LONG);
		printf_hide("offsetof(MYSQL_BIND, buffer_type)=%d\n", offsetof(MYSQL_BIND, buffer_type));
		printf_hide("offsetof(MYSQL_BIND, buffer)=%d\n", offsetof(MYSQL_BIND, buffer));
		printf_hide("offsetof(MYSQL_BIND, is_unsigned)=%d\n", offsetof(MYSQL_BIND, is_unsigned));
		printf_hide("offsetof(MYSQL_BIND, is_null)=%d\n", offsetof(MYSQL_BIND, is_null));
		printf_hide("offsetof(MYSQL_BIND, length)=%d\n", offsetof(MYSQL_BIND, length));
		
		// BIND PARAM
		
		param[0].buffer_type = MYSQL_TYPE_LONG;
		param[0].buffer = (void*) &paramIntA;
		param[0].is_unsigned = 0;
		param[0].is_null = 0;
		param[0].length = 0;
		
		param[1].buffer_type = MYSQL_TYPE_LONG;
		param[1].buffer = (void*) &paramIntB;
		param[1].is_unsigned = 0;
		param[1].is_null = 0;
		param[1].length = 0;
		
		ret = mysql_stmt_bind_param(stmt, param);
		if (ret != 0)
		{
			printf_hide("ERROR: mysql_stmt_bind_param(stmt, param): %d->\"%s\"\n", mysql_errno(my), mysql_error(my));
			mysql_close(my);
			return stackReturnInt(0);
		}
		
		// BIND RESULT
		
		result[0].buffer_type = MYSQL_TYPE_LONG;
		result[0].buffer = (void*) &resultIntA;
		result[0].is_unsigned = 0;
		result[0].is_null = 0; //&is_null[0];
		result[0].length = 0;
		
		result[1].buffer_type = MYSQL_TYPE_LONG;
		result[1].buffer = (void*) &resultIntB;
		result[1].is_unsigned = 0;
		result[1].is_null = 0; //&is_null[1];
		result[1].length = 0;
		
		ret = mysql_stmt_bind_result(stmt, result);
		if (ret != 0)
		{
			printf_hide("ERROR: mysql_stmt_bind_result(stmt, result): %d->\"%s\"\n", mysql_errno(my), mysql_error(my));
			mysql_close(my);
			return stackReturnInt(0);
		}
		
		{
			paramIntA = 10;
			paramIntB = 20;
			
			ret = mysql_stmt_execute(stmt);
			if (ret != 0)
			{
				printf_hide("ERROR: mysql_stmt_execute(stmt): %d->\"%s\"\n", mysql_errno(my), mysql_error(my));
				mysql_close(my);
				return stackReturnInt(0);
			}
			
			ret = mysql_stmt_store_result(stmt);
			if (ret != 0)
			{
				printf_hide("ERROR: mysql_stmt_store_result(stmt): %d->\"%s\"\n", mysql_errno(my), mysql_error(my));
				mysql_close(my);
				return stackReturnInt(0);
			}
			
			int i=0;
			while (mysql_stmt_fetch(stmt) == 0)
			{
				printf_hide("row[%d] resultIntA=%d resultIntB=%d\n", i, resultIntA, resultIntB);
				i++;
			}
			printf_hide("READED ROWS=%d\n", i);
			
			mysql_stmt_free_result(stmt);
		}
		
		#if 0
		{
			paramIntA = 100;
			paramIntB = 200;
			
			ret = mysql_stmt_execute(stmt);
			if (ret != 0)
			{
				printf_hide("ERROR: mysql_stmt_execute(stmt): %d->\"%s\"\n", mysql_errno(my), mysql_error(my));
				mysql_close(my);
				return stackReturnInt(0);
			}
			
			ret = mysql_stmt_store_result(stmt);
			if (ret != 0)
			{
				printf_hide("ERROR: mysql_stmt_store_result(stmt): %d->\"%s\"\n", mysql_errno(my), mysql_error(my));
				mysql_close(my);
				return stackReturnInt(0);
			}
			
			int i=0;
			while (mysql_stmt_fetch(stmt) == 0)
			{
				printf_hide("row[%d] numAddresses[0] = %d\n", i, myNumAddresses[0]);
				printf_hide("row[%d] numAddresses[1] = %d\n", i, myNumAddresses[1]);
				i++;
			}
			printf_hide("READED ROWS=%d\n", i);
			
			mysql_stmt_free_result(stmt);
		}
		#endif
		
		mysql_stmt_close(stmt);
		
		printf_hide("all went ok till here! :)\n");
	}
	
	
	
	
	//int ret = mysql_query(my, "SELECT 1 as first,2 as second,3  as third UNION SELECT 11,22,33");
	int ret = mysql_query(my, "SELECT * FROM players");
	
	if (ret != 0)
	{
		printf_hide("ERROR: mysql_query(): %d->\"%s\"\n", mysql_errno(my), mysql_error(my));
		mysql_close(my);
		return stackReturnInt(0);
	}
	
	printf_hide("affected rows: %d\n", mysql_affected_rows(my));
	
	MYSQL_RES *query;
	query = mysql_store_result(my);
	
	if (mysql_errno(my) != 0) /* do not check query==NULL, because thats also the case for like INSERT */
	{
		printf_hide("ERROR: mysql_store_result(my): %d->\"%s\"\n", mysql_errno(my), mysql_error(my));
		mysql_close(my);
		return stackReturnInt(0);
	}
	
	printf_hide("query-num rows: %d\n", mysql_num_rows(query));
	
	printf_hide("spalten im query: %d\n", mysql_num_fields(query));
	
	
	
	int numfields = mysql_num_fields(query);
	
	
	MYSQL_FIELD *field;
	int i;
	mysql_field_seek(query, 0);
	for (i=0; i<numfields; i++)
	{
		field = mysql_fetch_field(query);
		printf_hide("%s(%s), ", field->name, field->table);
	}
	printf_hide("\n");
	

	MYSQL_ROW row;
	while (row = mysql_fetch_row(query))
	{
		int i;
		
		for (i=0; i<numfields; i++)
			printf_hide("%s, ", row[i]);
		printf_hide("\n");
	}
	
	
	
	
	mysql_free_result(query);
	
	
	mysql_close(my);
	
	return stackReturnInt(1337);
}
#endif // compile mysql tests 

#endif // compile mysql
