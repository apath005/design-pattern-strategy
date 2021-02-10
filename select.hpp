#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};

class Select_And : public Select_Column {
protected:
    const Spreadsheet* sheet;
    std::string name;
public:
    Select_And(const Spreadsheet* sheet, const std::string& name) : Select_Column(sheet, name) {
        this->sheet = sheet;
        this->name = name;
    }

    bool select(Select* lhs, Select* rhs) const {
        if (lhs->select(sheet, column) == true && rhs->select(sheet, column) == true) {
            return true;
        }
        else {
            return false;
        }
    }
};

class Select_Or : public Select_Column {
protected:
    const Spreadsheet* sheet;
    std::string name;
public:
    Select_Or(const Spreadsheet* sheet, const std::string& name) : Select_Column(sheet, name) {
        this->sheet = sheet;
        this->name = name;
    }
    bool select(Select* lhs, Select* rhs) const {
        if (lhs->select(sheet, column) == true || rhs->select(sheet, column) == true) {
            return true;
        }
        else {
            return false;
        }
    }
};


#endif //__SELECT_HPP__
