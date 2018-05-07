#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mysql_connect.h"
#include "unistd.h"

// ConnectionPool *pool = ConnectionPool::getInstance();
std::shared_ptr<ConnectionPool>pool(ConnectionPool::getInstance());

int main(int argc, char *argv[])
{
	std::shared_ptr<sql::Connection>con;

	//获得一个连接
	con = pool->getConnect();
	if (!con){
		std::cout << "get Connect failed!" << std::endl;
	}
	else{
		std::cout << "get Connect success!" << std::endl;
	}
	con->setSchema("testdb");
	//获得一个数据库连接对象
	std::shared_ptr<sql::Statement> state(con->createStatement());
	
	state->execute("drop table if exists tbl_test");
	state->execute("create table tbl_test(id int,name varchar(8))");
	state->execute("insert into tbl_test(id, name) values(1,'hou')");
	state->execute("insert into tbl_test(id, name) values(2,'liu')");

	std::shared_ptr < sql::PreparedStatement > prep_stmt(con->prepareStatement("INSERT INTO tbl_test(id, name) VALUES (?, ?)"));
	prep_stmt->setInt(1, 3);
	prep_stmt->setString(2, "a");
	prep_stmt->execute();

	prep_stmt->setInt(1, 4);
	prep_stmt->setString(2, "b");
	prep_stmt->execute();
	

	//查询语句
	std::shared_ptr<sql::ResultSet> result(state->executeQuery("select id,name from tbl_test;"));
	
	while (result->next()){
		int id = result->getInt(1);
		std::cout << "id=" << id << std::endl;
		
		std::string name = result->getString("name").c_str();
		std::cout << "name=" << name << std::endl;
	}
	pool->disConnect(con);
	std::cout << pool->getPoolSize() << std::endl;


	return EXIT_SUCCESS;
}