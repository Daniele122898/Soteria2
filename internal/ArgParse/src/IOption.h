//
// Created by Daniele on 4/23/2022.
//

#ifndef SOTERIA_IOPTION_H
#define SOTERIA_IOPTION_H

#include <string>
#include <vector>

namespace ArgParse {

    class IOption {
    public:
        IOption(std::string name, bool isRequired, std::vector<std::string> aliases = {}) :
         m_name{std::move(name)}, m_required{isRequired}, m_aliases{std::move(aliases)} {};

        virtual ~IOption() = default;
        virtual bool IsSet() = 0;
        virtual std::string_view GetName() {return m_name;};
        virtual std::vector<std::string> const& GetAliases() { return m_aliases;};
        virtual bool IsRequired() {return m_required; }
        virtual bool TakesValue() = 0;
        virtual std::string_view GetValue() = 0;
        virtual void Set(std::string const& arg) = 0;
        virtual void Set() = 0;

    protected:
        std::string m_name;
        std::vector<std::string> m_aliases;
        bool m_required;
    };

} // ArgParse

#endif //SOTERIA_IOPTION_H
