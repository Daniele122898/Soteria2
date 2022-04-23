//
// Created by Daniele on 4/23/2022.
//

#ifndef SOTERIA_IOPTION_H
#define SOTERIA_IOPTION_H

#include <string>

namespace ArgParse {

    class IOption {
    public:
        IOption(std::string name, bool isRequired) :
         m_name{std::move(name)}, m_required{isRequired} {};

        virtual ~IOption() = default;
        virtual bool IsSet() = 0;
        virtual std::string_view GetName() {return m_name;}
        virtual bool IsRequired() {return m_required; }
        virtual bool TakesValue() = 0;
        virtual std::string_view GetValue() = 0;
        virtual void Set(std::string const& arg) = 0;
        virtual void Set() = 0;

    protected:
        std::string m_name;
        bool m_required;
    };

} // ArgParse

#endif //SOTERIA_IOPTION_H
