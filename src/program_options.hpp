#ifndef PROGAM_OPTIONS_H_
#define PROGAM_OPTIONS_H_

#include <vector>
#include <map>

class Program_options
{
public:
    /*****constructor*****/
    Program_options();

    /*****constants*****/
    static const int type_flag;
    static const int type_data;

    /*****core functions*****/
    void parse_args(int argc, char** argv);
    void add_option(std::string option, int type);
    void add_option(std::string option, std::string default_value, int type);
    bool is_set(std::string);
    template <typename T> T get_option(std::string option);
private:
    std::map<std::string, int> options;
    std::map<std::string, std::string> values;
};
#endif
