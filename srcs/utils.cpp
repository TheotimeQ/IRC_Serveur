#include "../incs/utils.hpp"

int Send_Cmd(int client_sock, const std::string& message) 
{
    int bytes_sent = send(client_sock, message.c_str(), message.size(), 0);
    if (bytes_sent == -1) 
    {
        std::cout << ERROR_SEND_MSG << strerror(errno) << std::endl;
        return ERROR;
    }

	//DEBUG
	std::cout << "\033[38;5;182m";
    std::cout << "      <- Sent       : " << message << std::endl;
	std::cout << "\033[m";
	//DEBUG

    // std::cout << EVENT_NEW_MSG << message ;
    return GOOD;
}

std::string I_To_S(int num)
{
    std::stringstream ss;
    ss << num;
    return (ss.str());
}

int Check_Double(std::string NickName, std::string Args)
{
    std::stringstream Targets(Args); 
    std::string Target; 
    int nb = 0;

    while (std::getline(Targets, Target, ',')) 
    {
        if (NickName == Target)
            nb++;
    }
    if (nb > 1)
        return ERROR;
    return GOOD;
}

std::string Join_End(int start, std::vector<std::string> Args)
{
    std::vector<Client>::iterator it;
    std::string Joined = ""; 

    for (int i = start; i < (int)Args.size(); ++i)
        Joined += Args[i] + " ";

    if (!Joined.empty() && Joined[0] == ':') {
        Joined.erase(0, 1);
    }

    if (!Joined.empty() && Joined[Joined.length() - 1] == '\n') {
        Joined.erase(Joined.length() - 1);
    }

    return Joined;
}

int Is_Valide_Nick(const std::string& str) 
{

    if (str.length() > 9) {
        return ERROR;
    }

    const std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_{[]}\\`|";
    for (size_t i = 0; i < str.length(); ++i) {
        if (allowedChars.find(str[i]) == std::string::npos) {
            return ERROR;
        }
    }

    return GOOD;
}

std::string catVectString(std::vector<std::string> const &args, unsigned offset, std::string const &delim) {
	std::vector<std::string>::const_iterator	it;
	std::string									cat;

	if (offset > args.size() - 1)
		return "";
	it = args.begin() + offset;
		while (it != args.end()) {
			if (it != args.begin() + 2)
				cat += delim;
			cat += *it;
			++it;
		}
	return cat;
}