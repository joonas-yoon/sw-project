#include <mysql.h>
#include <string.h>
#include <stdio.h>

#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "ws2_32.lib")


#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "1234"


int main(void)
{
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;

	int fields, i;

	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, DB_HOST, DB_USER, DB_PASS, NULL, 3306, (char *)NULL, 0)) {
		printf("%s\n", mysql_error(&mysql));
		exit(1);
	}
	printf("���������� ����Ǿ����ϴ�.\n");

	mysql_query(&mysql, "use imagehouse"); //test �� �����ͺ��̽� ��� //mysql_select_db() �� ���� ��Ȱ

	mysql_query(&mysql, "SELECT * FROM images"); // table �̶� ���̺��� ��� ���ڵ� ����

	res = mysql_store_result(&mysql);  // ��� ��� ����� �������� �ѹ��� �� �޾ƿ�(������ �������� �����϶�)

	fields = mysql_num_fields(res); // �ʵ� ���� ����

	while (row = mysql_fetch_row(res)) // �� ���� ����
	{
		for (i = 0; i< fields; i++)  // ��� �ʵ� ���� ���
		{
			printf("%s --", row[i]);
		}
		printf("\n");
	}


	printf("\n");
	//\ ǥ�ø� �ҷ��� \\\\4�� �־���ߵ�
	int query_stat;
	query_stat = mysql_query(&mysql, "INSERT INTO imagehouse.images(`name`, `extension`, `realpath`, `ip`) VALUES (\"1706101916012071\", UPPER(\"jpeg\"), \"127.0.0.1\\\\a\\\\abc.jpeg\", \"127.0.0.1\")");


	if (query_stat != 0) {//0�̸� success
		printf("\n INSERT ERROR!\n");
	}
	else {
		printf("\n INSERT SUCCESS!\n");
	}


	/*
	if (mysql_query(&mysql, "INSERT INTO images VALUES (\"1706101916012017\", UPPER(\"jpeg\"), \"127.0.0.1\\\\abc.jpeg\", \"127.0.0.1\")"))
	{
		mysql_error(&mysql);
	}
	*/

	/*
	if (mysql_query(&mysql, "INSERT INTO images VALUES (1706101916012069, UPPER(gif), 127.0.0.1\\hihi.jpeg, 127.0.0.1)"))
	{
		mysql_error(&mysql);
	}
	*/

	/*
	if (mysql_query(&mysql, "INSERT INTO images VALUES ('1706101916012069', UPPER(gif), '127.0.0.1\\hihi.jpeg', '127.0.0.1')"))
	{
		mysql_error(&mysql);
	}
	*/


	mysql_free_result(res);
	mysql_close(&mysql);


	return 0;
}
/*
INSERT INTO `imagehouse`.`images`
(`name`, `extension`, `realpath`, `ip`)
VALUES
("1706101916012009", UPPER("jpeg"), "127.0.0.1\\zzz.jpeg", "127.0.0.1");

*/
