#include "pch.h"
#include <iostream>
#include <chrono>

#include <pqxx/pqxx>



pqxx::result insert(
		const unsigned int& speed, const unsigned int& length_1,
		const unsigned int& length_2, const std::string& event_image,
		const std::string& camera_timestamp, const std::string& logger_timestamp)
{
	pqxx::connection conn("dbname=APP_DB_NAME user=APP_DB_USER password=APP_DB_PASSWORD");

	pqxx::work txn{ conn };

	pqxx::result result = txn.exec(
		"INSERT INTO logger_event ("
			"speed, length_1, length_2,"
			"event_image, camera_timestamp, logger_timestamp"
		") VALUES ("
			"'" + std::to_string(speed) + "', '" + std::to_string(length_1) + "', '" + std::to_string(length_2) + "',"
			"'" + event_image + "', '" + camera_timestamp + "', '" + logger_timestamp + "'"
		");"
	);

	txn.commit();
	conn.disconnect();

	return result;
}

int main()
{
    std::cout << "Inserting ...\n";

	try
	{
		insert(99, 1004, 3005, "UUID.jpg", "2018-11-15 22:30:15", "2018-11-15 22:30:17");

		std::cout << "Done.\n";
	}
	catch (const pqxx::sql_error &e)
	{
		std::cerr << "SQL error: " << e.what() << std::endl;
		std::cerr << "Query was: " << e.query() << std::endl;
		return 2;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

}