#include "spreadsheet.hpp"
#include "spreadsheet.cpp"
#include "select.hpp"
#include <sstream>
#include "gtest/gtest.h"
using namespace std;

TEST(test, Select_ContainsTest) {
    stringstream ss;
    Spreadsheet sheet;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});

    sheet.set_selection(new Select_Contains(&sheet,"Last","Dole"));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "Diane Dole 20 computer engineering\nDavid Dole 22 electrical engineering\nDominick Dole 22 communications");
}

TEST(test, Select_ContainsDoesNotContainTest) {
    stringstream ss;
    Spreadsheet sheet;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});

    sheet.set_selection(new Select_Contains(&sheet,"Last","Smith"));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "");
}

TEST(test, Select_NotTest) {
    stringstream ss;
    Spreadsheet sheet;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});

    sheet.set_selection(new Select_Contains(&sheet,"Last","Smith"));
    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "");
}

TEST(test, Select_AndTest) {
    stringstream ss;
    Spreadsheet sheet;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});

    sheet.print_selection(ss);

    EXPECT_EQ(ss.str(), "Sarah Summers 21 computer science");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
