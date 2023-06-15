#include <iostream>
#include <mdz_prg_service/application.h>
#include <mdz_hlp_functions/crypto.h>
#include "config.h"

#include <sys/types.h>

#ifndef WIN32
#include <pwd.h>
#endif

#include <dirent.h>
#include <unistd.h>

#include <sys/stat.h>

using namespace Mantids::Application;

class Main : public Application
{
public:

    void _shutdown()
    {
    }

    int _start(int , char *[], Arguments::GlobalArguments *globalArguments)
    {

        bool result = false;

        // not compatible in every system.
        std::string encryptedData = R"(ZA1gg5syrEa/NnOAeXOyj9pp0AoMC1hq41D0TZBnsEguECUS+cNSq6zBqw==)";

        std::cout << "Encrypting with v1 'Hello World' with key 123456: " << Mantids::Helpers::Crypto::AES256EncryptB64("Hello World", "123456", &result) << ", result = " << (result?1:0) << std::endl;
        std::cout << "Decrypting with v1 'Hello World' with key 123456: " << Mantids::Helpers::Crypto::AES256DecryptB64(encryptedData, "123456", &result) << ", result = " << (result?1:0) << std::endl;

        // broad compatibility:
        std::string encryptedDatav2 = R"(ZJQlqQqH46sKMMOzfuPken+TQq8WGvk4qpAoZufljFiU/29XhhGaPrM2jA==)";

        std::cout << "Encrypting with v2 'Hello World' with key 123456: " << Mantids::Helpers::Crypto::AES256EncryptB64v2("Hello World", "123456", &result) << ", result = " << (result?1:0) << std::endl;
        std::cout << "Decrypting with v2 'Hello World' with key 123456: " << Mantids::Helpers::Crypto::AES256DecryptB64v2(encryptedDatav2, "123456", &result) << ", result = " << (result?1:0) << std::endl;

        return 0;
    }

    void _initvars(int , char *[], Arguments::GlobalArguments * globalArguments)
    {
        // init variables (pre-config):
        globalArguments->setInifiniteWaitAtEnd(false);

        globalArguments->setAuthor("Aarón Mizrachi");
        globalArguments->setEmail("amizrachi@tekium.mx");
        globalArguments->setVersion(atoi(PROJECT_VER_MAJOR), atoi(PROJECT_VER_MINOR), atoi(PROJECT_VER_PATCH), "");
        globalArguments->setLicense("LGPLv3");
        globalArguments->setDescription(PROJECT_DESCRIPTION);
    }

    bool _config(int , char *argv[], Arguments::GlobalArguments * globalArguments)
    {
        // process config:
        return true;
    }
};

int main(int argc, char *argv[])
{
    Main * main = new Main;
    return StartApplication(argc,argv,main);
}

