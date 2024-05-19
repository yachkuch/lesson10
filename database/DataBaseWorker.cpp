#include "DataBaseWorker.h"
#include <format>
#include <iostream>
#include <boost/algorithm/string.hpp>

DataBaseWorker::DataBaseWorker() {}

DataBaseWorker::~DataBaseWorker()
{
  sqlite3_exec(db, "DROP TABLE user;", nullptr, nullptr, nullptr);
  sqlite_check(sqlite3_close(db));
}

void DataBaseWorker::operator()(std::string data) 
{
  std::vector<std::string> lines;
  boost::split(lines, data, boost::algorithm::is_space());
  if(!lines.empty() && (lines.size() == 3))
  {
    auto val = lines.front();
    if(val == "A")
    {
      add_mes(create_table_stmt,"A",lines);
    }
    else if(val == "B")
    {

    }
  }
}

void DataBaseWorker::add_mes( sqlite3_stmt  *stmt,std::string db_name,
 const std::vector<std::string>&mes)
{
  char* errmsg{};
  std::string sql{"INSERT INTO "};
  sql.append(db_name);
  sql.append(" VALUES (");
  sql.append(mes[1]);
  sql.append(", ");
  sql.append(mes[2]);
  sql.append(");");
  int res = sqlite3_exec(db, sql.data(),
                     nullptr, nullptr, &errmsg);
  sqlite_check(res, errmsg);
}

int DataBaseWorker::sqlite_check(int code, const char *msg, int expected)
{
  if (code != expected)
  {
    sqlite_throw(code, msg);
  }
  return code;
}

void DataBaseWorker::sqlite_throw(int code, const char *msg)
{
  throw std::runtime_error{
      std::format("SQL Method failed: {} {}", sqlite3_errstr(code), msg)};
}

void DataBaseWorker::start_db()
{
  sqlite_check(sqlite3_open("db", &db));
  {
    std::string_view sql{"CREATE TABLE IF NOT EXISTS A"
                         "(id INTEGER PRIMARY KEY,"
                         "name VARCHAR(255) NOT NULL);"};
    const char *stmt_tail;
    if (sqlite3_prepare_v2(db, sql.data(), sql.size(), &create_table_stmt,
                           &stmt_tail) != SQLITE_OK)
    {
      std::cerr << std::format("Error preparing statement: {}",
                               sqlite3_errmsg(db))
                << "\n";
    }

    int res = 0;
    do
    {
      res = sqlite3_step(create_table_stmt);
      if (res == SQLITE_ROW)
      {
      }
      else if (res == SQLITE_DONE)
      {
        // ok
      }
      else
      {
        sqlite_throw(res);
      }
    } while (res != SQLITE_DONE);

    sqlite_check(sqlite3_finalize(create_table_stmt));
  }

  std::string_view sqlb{"CREATE TABLE IF NOT EXISTS B"
                        "(id INTEGER PRIMARY KEY,"
                        "name VARCHAR(255) NOT NULL);"};
  const char *stmt_tailb;
  if (sqlite3_prepare_v2(db, sqlb.data(), sqlb.size(), &create_table_stmt2,
                         &stmt_tailb) != SQLITE_OK)
  {
    std::cerr << std::format("Error preparing statement: {}",
                             sqlite3_errmsg(db))
              << "\n";
  }

  int res = 0;
  do
  {
    res = sqlite3_step(create_table_stmt2);
    if (res == SQLITE_ROW)
    {
    }
    else if (res == SQLITE_DONE)
    {
      // ok
    }
    else
    {
      sqlite_throw(res);
    }
  } while (res != SQLITE_DONE);

  sqlite_check(sqlite3_finalize(create_table_stmt2));

  std::format("Data Base Open");
}