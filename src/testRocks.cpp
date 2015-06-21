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
	int resTests = 0;
//	testing::InitGoogleTest(&argc, argv);
//	resTests = RUN_ALL_TESTS();

	Server* s = new Server();
	s->run();
	delete s;


	return resTests;
}
