#include "QueryHandler.h"
#include <iostream>
#include <sstream>

#include "BinarySearch.cpp"

using namespace std;

QueryHandler::QueryHandler() {}

void QueryHandler::executeQuery(const string &query)
{
    parseQuery(query);
}

// void QueryHandler::parseQuery(const string &query)
// {
//     istringstream stream(query);
//     string command, field, table, whereClause;

//     // Extract the command (SELECT), field (e.g., ALL), and table (Doctors or Appointments)
//     stream >> command >> field >> table;
//     // Ensure the table is 'FROM' and handle the WHERE clause extraction
//     if (stream >> table)
//     {
//         // This assumes the 'FROM' keyword and that there's a space before WHERE
//         stream.ignore();              // Ignore the space between table name and WHERE clause
//         getline(stream, whereClause); // Capture the entire WHERE clause (the condition)
//     }

//     // Check if the command is SELECT and process it
//     if (command == "SELECT" && !table.empty())
//     {
//         handleSelect(table, field, whereClause);
//     }
//     else
//     {
//         cerr << "Invalid query format: " << query << endl;
//     }
// }

// void QueryHandler::handleSelect(const string &table, const string &field, const string &condition)
// {
//     BinarySearch searcher; // Instance of BinarySearch for index lookup
//     string conditionValue = extractConditionValue(condition);
//     cout << "Field: " << field << ", Table: " << table << endl;
//     if (table == "Doctors")
//     {
//         if (field == "ALL")
//         {
//             // Fetch all fields for matching Doctor ID
//             cout << "Results: " << searcher.searchByDocId(conditionValue) << endl;
//         }
//         else
//         {
//             // Fetch specific field for matching Doctor ID
//             cout << "Results: " << searcher.searchByDocName(conditionValue) << endl;
//         }
//     }
//     else if (table == "Appointments")
//     {
//         if (field == "ALL")
//         {
//             // Fetch all fields for matching Doctor ID
//             cout << "Results: " << searcher.searchByAppId(conditionValue) << endl;
//         }
//         else
//         {
//             // Fetch specific field for matching Doctor ID
//             cout << "Results: " << searcher.searchByDocName(conditionValue) << endl;
//         }
//     }
//     else
//     {
//         cerr << "Unsupported table: " << table << endl;
//     }
// }

void QueryHandler::parseQuery(const string &query)
{
    istringstream stream(query);
    string command, field, table, whereClause;

    // Extract SELECT, field, and table
    stream >> command >> field >> table;

    // Ensure 'FROM' is followed by table name
    if (stream >> table)
    {
        getline(stream, whereClause); // Capture everything after 'FROM'
    }

    if (command == "SELECT" && !table.empty())
    {
        string column, conditionValue;

        // Process WHERE clause
        if (!whereClause.empty() && whereClause.find("WHERE") != string::npos)
        {
            size_t wherePos = whereClause.find("WHERE") + 6; // Skip 'WHERE '
            string condition = whereClause.substr(wherePos);

            // Split condition into column and value
            size_t operatorPos = condition.find('='); // Assuming '=' for now
            if (operatorPos != string::npos)
            {
                column = condition.substr(0, operatorPos);          // Extract column name
                conditionValue = condition.substr(operatorPos + 1); // Extract value

                // Remove quotes from conditionValue
                conditionValue.erase(remove(conditionValue.begin(), conditionValue.end(), '\''), conditionValue.end());
            }
        }

        // Pass parsed details to handleSelect
        handleSelect(table, field, column, conditionValue);
    }
    else
    {
        cerr << "Invalid query format: " << query << endl;
    }
}

void QueryHandler::handleSelect(const string &table, const string &field, const string &column, const string &conditionValue)
{
    BinarySearch searcher; // Instance of BinarySearch for index lookup
    cout << "Field: " << field << ", Table: " << table << ", Column: " << column << ", Condition: " << conditionValue << endl;
    if (table == "Doctors")
    {
        if (column == "Doctor ID")
        {
            cout << "Results: " << searcher.searchByDocId(conditionValue) << endl;
        }
        else if (column == "Doctor Name")
        {
            cout << "Results: " << searcher.searchByDocName(conditionValue) << endl;
        }
    }
    else if (table == "Appointments")
    {
        if (column == "Doctor ID")
        {
            cout << "Results: " << searcher.searchAppByDocId(conditionValue) << endl;
        }
        else if (column == "Appointment ID")
        {
            cout << "Results: " << searcher.searchByAppId(conditionValue) << endl;
        }
    }
    else
    {
        cerr << "Unsupported table: " << table << endl;
    }
}

string QueryHandler::extractConditionValue(const string &condition)
{
    size_t start = condition.find('\'') + 1;
    size_t end = condition.rfind('\'');
    return condition.substr(start, end - start);
}
