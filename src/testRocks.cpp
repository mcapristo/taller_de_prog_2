#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "rocksdb/db.h"
#include "json/json.h"
#include <gtest/gtest.h>

#include "User.h"
#include "Database.h"
#include "Message.h"

using namespace std;
using namespace rocksdb;









int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
