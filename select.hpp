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

class Select_Contains: public Select_Column
{
protected:
        const Spreadsheet* sheet = sheet;
        std::string name;
        std::string subString;
public:
        Select_Contains(const Spreadsheet* sheet, const std::string& name, const std::string& s) : Select_Column(sheet, name)
        {
        this->sheet = sheet;
        this->subString = subString;
        }
        virtual bool select(const Spreadsheet* spreadsheet, int row)  const {
        return spreadsheet->cell_data(row, column).find(subString) != std::string::npos;
        }
        virtual bool select(const std::string& s) const {
        return true;

        }
};

class Select_Not: public Select
{
protected:
    	Select* selectValue;

public:
    	Select_Not(Select* select)
    	{
        selectValue = select;
    	}

    	~Select_Not() {
        delete selectValue;
    	}
    	virtual bool select(const Spreadsheet* sheet, int row) const {
        return !selectValue->select(sheet, row);
    	}

};

class Select_And : public Select {
protected:
    Select* selectLHS;
    Select* selectRHS;
public:
    Select_And(Select* lhs, Select* rhs) {
         selectLHS = lhs;
         selectRHS = rhs;
    }

    ~Select_And() { delete selectLHS; delete selectRHS; }

    bool select(const Spreadsheet* sheet, int row) const {
        if (selectLHS->select(sheet, row) == true && selectRHS->select(sheet, row) == true) {
            return true;
        }
        else {
            return false;
        }
    }
};

class Select_Or : public Select {
protected:
    Select* selectLHS;
    Select* selectRHS;
public:
    Select_Or(Select* lhs, Select* rhs) {
        selectLHS = lhs;
        selectRHS = rhs;
    }
    bool select(const Spreadsheet* sheet, int row) const {
        if (selectLHS->select(sheet, row) == true || selectRHS->select(sheet, row) == true) {
            return true;
        }
        else {
            return false;
        }
    }
};

#endif //__SELECT_HPP__
