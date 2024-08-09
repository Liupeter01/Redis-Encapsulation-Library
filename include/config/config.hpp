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
          std::string MySQL_ip_addr;
          unsigned short MySQL_port;
          std::string MySQL_passwd;

private:
          ServerConfig(){
                m_ini.load(CONFIG_HOME"config.ini");
                MySQL_port = m_ini["MySQL"]["port"].as<unsigned short>();
                MySQL_ip_addr = m_ini["MySQL"]["host"].as<std::string>();
                MySQL_passwd = m_ini["MySQL"]["password"].as<std::string>();
          }

private:
          ini::IniFile m_ini;
};

#endif