//
// Created by Daniele on 4/23/2022.
//

#ifndef SOTERIA_STRINGOPTION_H
#define SOTERIA_STRINGOPTION_H

#include "IOption.h"

namespace ArgParse {

    class StringOption : public IOption {
    public:
        explicit StringOption(std::string name, bool isRequired = false) :
        IOption(std::move(name), isRequired) {}

        bool IsSet() override {return m_isSet; }
        bool TakesValue() override { return true; }
        std::string_view GetValue() override { return m_value; }
        void Set(std::string const& arg) override { m_value = arg; m_isSet = true;}
        void Set() override { throw std::invalid_argument("StringOption requires a value to be passed: " + m_name);}

    private:
        std::string m_value;
        bool m_isSet = false;
    };

} // ArgParse

#endif //SOTERIA_STRINGOPTION_H
