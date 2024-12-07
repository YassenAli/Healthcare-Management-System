// #ifndef QUERY_HANDLER_H
// #define QUERY_HANDLER_H

// #include <string>

// class QueryHandler
// {
// public:
//     QueryHandler();
//     void executeQuery(const std::string &query);

// private:
//     void parseQuery(const std::string &query);
//     void handleSelect(const std::string &table, const std::string &field, const std::string &condition);
//     std::string extractConditionValue(const std::string &condition);
// };

// #endif

#ifndef QUERY_HANDLER_H
#define QUERY_HANDLER_H

#include <string>

class QueryHandler
{
public:
    QueryHandler();
    void executeQuery(const std::string &query);

private:
    void parseQuery(const std::string &query);
    void handleSelect(const std::string &table, const std::string &field, const std::string &column, const std::string &conditionValue);
    std::string extractConditionValue(const std::string &condition);
};

#endif
