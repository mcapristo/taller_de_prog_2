#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "rocksdb/db.h"
#include "json/json.h"
#include <gtest/gtest.h>

#include "Server.h"

using namespace std;
using namespace rocksdb;


int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

//	Server* s = new Server();
//	s->run();


	return 0;
}
