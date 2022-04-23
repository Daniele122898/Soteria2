//
// Created by Daniele on 4/23/2022.
//

#ifndef SOTERIA_BOOLOPTION_H
#define SOTERIA_BOOLOPTION_H

#include <utility>

#include "IOption.h"

namespace ArgParse {

    class BoolOption : public IOption {
    public:
        BoolOption(std::string name, bool isRequired) :
            IOption(std::move(name), isRequired) {}

        bool IsSet() override {return m_value; }
        bool TakesValue() override { return false; }
        std::string_view GetValue() override { return m_value ? "True" : "False" ; } // TODO: Find better way for this lmao
        void Set() override { m_value = true;}
        void Set([[maybe_unused]]std::string const& arg) override { m_value = true;}

    private:
        bool m_value = false;
    };

} // ArgParse

#endif //SOTERIA_BOOLOPTION_H
