#ifndef _INIREADER_HPP_
#define _INIREADER_HPP_
#include<memory>
#include<inicpp.h>
#include<singleton/singleton.hpp>

struct ServerConfig : public Singleton< ServerConfig>
{
          friend class Singleton< ServerConfig>;

public:
          ~ServerConfig() = default;
          std::string Redis_ip_addr;
          unsigned short Redis_port;
          std::string Redis_passwd;

private:
          ServerConfig(){
                m_ini.load(CONFIG_HOME"config.ini");
                Redis_port = m_ini["Redis"]["port"].as<unsigned short>();
                Redis_ip_addr = m_ini["Redis"]["host"].as<std::string>();
                Redis_passwd = m_ini["Redis"]["password"].as<std::string>();
          }

private:
          ini::IniFile m_ini;
};

#endif