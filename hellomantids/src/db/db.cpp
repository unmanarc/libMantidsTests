#include "db.h"

#include <mdz_thr_mutex/lock_shared.h>

#include <mdz_mem_vars/a_string.h>
#include <mdz_mem_vars/a_datetime.h>
#include <mdz_mem_vars/a_bool.h>
#include <mdz_mem_vars/a_int32.h>
#include <mdz_mem_vars/a_uint32.h>
#include <mdz_mem_vars/a_int64.h>
#include <mdz_mem_vars/a_uint16.h>

#include <mdz_mem_vars/a_var.h>
#include <arpa/inet.h>

#include "../globals.h"

using namespace Mantids::Memory;
using namespace Mantids::Database;
using namespace Mantids::Authentication;
using namespace Mantids::Application;

std::atomic<bool> DB::statusOK;
std::string DB::dbPath;
Mantids::Threads::Sync::Mutex_Shared DB::mutex;
Mantids::Database::SQLConnector_SQLite3 DB::db;

bool DB::start(const std::string &_dbPath)
{
    dbPath = _dbPath;

    statusOK = db.connect(dbPath) && initSchema();
    return statusOK;
}

bool DB::getStatusOK()
{
    return statusOK;
}

bool DB::initSchema()
{
    bool r = true;

    if (r && !db.dbTableExist("posts"))
    {
        if (! db.query("CREATE TABLE `posts` (\n"
                       "       `id`           INTEGER PRIMARY KEY AUTOINCREMENT,\n"
                       "       `message`           VARCHAR(1024)    NOT NULL,\n"
                       "       `createdBy`         VARCHAR(256)    DEFAULT NULL,\n"
                       "       `creationDate`      DATETIME        NOT NULL DEFAULT CURRENT_TIMESTAMP\n"
                       ");\n"))
            r=false;
    }

    return r;
}

json DB::runLocalRPCMethod(const std::string &methodName,  Manager *auth, Session *sess, const json &payload, json *error)
{
    json r;

    if (0==1) {}
    // MESSAGES:
    else if ( methodName == "stats.getAdd1" ) r = getAdd1(auth,sess,payload);
    else if ( methodName == "stats.getMessages" ) r = getMessages(auth,sess,payload);
    else if ( methodName == "control.createMessage" ) r = createMessage(auth,sess,payload);
    else if ( methodName == "control.removeMessage" ) r = removeMessage(auth,sess,payload);

    else
    {
        if (error)
        {
            (*error)["succeed"] = false;
            (*error)["errorId"] = 1;
            (*error)["errorMessage"] = "Method Not Found.";
        }
    }

    if (error)
    {
        (*error)["succeed"] = true;
        (*error)["errorId"] = 0;
        (*error)["errorMessage"] = "Execution OK.";
    }

    return r;
}

