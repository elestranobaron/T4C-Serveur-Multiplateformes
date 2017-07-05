// en remplacement des registres windows
#include <map>
#include <string>
#include <sstream>

class Config
{
public:
   static Config& instance();

   bool initConfig(const char* cfgFilename);

   template <typename T> T lookupValue(const std::string& cfgID)
   {
      ConfigMap::const_iterator it = myConfig.find(cfgID);

      T rtn;

      if (it != myConfig.end())
      {
         std::stringstream iss(it->second);

         iss >> rtn;
      }

      return rtn;
   }

private:
   typedef std::map<std::string, std::string> ConfigMap;

   Config() {}

   // declared, but not implemented.
   Config(const Config& other);
   Config& operator=(const Config& other);

   // map for storing configuration items.
   ConfigMap myConfig;
};
