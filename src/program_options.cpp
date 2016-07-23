#include "program_options.hpp"

const int Program_options::type_flag = 0;
const int Program_options::type_data = 1;

Program_options::Program_options(){}

void Program_options::parse_args(int argc, char** argv)
{
    std::vector<std::string> args;
    for (int i=1; i<argc; i++)
        args.push_back(argv[i]);
    for (unsigned i=0; i<args.size(); i++)
    {
        if (options.find(args.at(i)) != options.end())
        {
            if (options[args.at(i)] == type_flag)
                values[args.at(i)]="true";
            else
                values[args.at(i)]=args.at(i+1);
        }
    }
}
void Program_options::add_option(std::string option,int type)
{
    this->options[option] = type;
}
void Program_options::add_option(std::string option, std::string default_value, int type)
{
    this->options[option] = type;
    this->values[option] = default_value;
}
bool Program_options::is_set(std::string option){
    if (options.find(option) != options.end())
    {
        return values.find(option) != values.end();
    }
    return false;
}
template <> double Program_options::get_option<double>(std::string option){
    if (is_set(option))
    {
        return atof(values[option].data());
    }
    return 0.0;
}
template <> int Program_options::get_option<int>(std::string option){
    if (is_set(option))
    {
        return atoi(values[option].data());
    }
    return 0;
}
template <> long Program_options::get_option<long>(std::string option){
    if (is_set(option))
    {
        return atol(values[option].data());
    }
    return 0.0;
}
template <> long long Program_options::get_option<long long>(std::string option){
    if (is_set(option))
    {
        return atoll(values[option].data());
    }
    return 0.0;
}
template <> float Program_options::get_option<float>(std::string option){
    if (is_set(option))
    {
        return atof(values[option].data());
    }
    return 0.0;
}
template <> std::string Program_options::get_option<std::string>(std::string option){
    if (is_set(option))
    {
        return values[option];
    }
    return "";
}
template <> bool Program_options::get_option<bool>(std::string option){
    if (is_set(option))
    {
        return true;
    }
    return false;
}
