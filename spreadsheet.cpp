#include "spreadsheet.hpp"
#include "select.hpp"

#include <algorithm>
#include <iostream>

Spreadsheet::~Spreadsheet()
{
    delete select;
}

void Spreadsheet::set_selection(Select* new_select)
{
    delete select;
    select = new_select;
}

void Spreadsheet::print_selection(std::ostream &out) const
{
	if (select == nullptr) {
		for (int i = 0; i < data.size(); i++) {
		std::cout << this->cell_data(i, 0) << " " << this->cell_data(i, 1)
		<< " " << this->cell_data(i, 2) << " " << this->cell_data(i, 3) << "\n";
        	}
    		}
    		else {

        	for (int i = 0; i < data.size(); i++) {
            	if (select->select(this, i)) {

                std::cout << this->cell_data(i, 0) << " " << this->cell_data(i, 1)
                << " " << this->cell_data(i, 2) << " " << this->cell_data(i, 3) << "\n";
            }
        }
}
}

void Spreadsheet::clear()
{
    column_names.clear();
    data.clear();
    delete select;
    select = nullptr;
}

void Spreadsheet::set_column_names(const std::vector<std::string>& names)
{
    column_names=names;
}

void Spreadsheet::add_row(const std::vector<std::string>& row_data)
{
    data.push_back(row_data);
}

int Spreadsheet::get_column_by_name(const std::string& name) const
{
    for(int i=0; i<column_names.size(); i++)
        if(column_names.at(i) == name)
            return i;
    return -1;
}
