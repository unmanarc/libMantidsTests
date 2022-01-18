#ifndef DB_H
#define DB_H

#include <atomic>
#include <utility>

#include <mdz_hlp_functions/json.h>
#include <mdz_auth/manager.h>
#include <mdz_auth/session.h>
#include <mdz_db_sqlite3/sqlconnector_sqlite3.h>

#include <mdz_hlp_functions/os.h>
#include <mdz_thr_mutex/mutex_shared.h>

class DB
{
public:
    static bool start(const std::string &dbPath);

    /**
     * @brief runRemoteRPCMethod Run Remote RPC Method
     * @param connectionKey Connection ID (this class can thread-safe handle multiple connections at time)
     * @param methodName Method Name
     * @param payload Function Payload
     * @param error Error Return
     * @return Answer, or Json::nullValue if answer is not received or if timed out.
     */
    static json runLocalRPCMethod(const std::string &methodName,  Mantids::Authentication::Manager *auth, Mantids::Authentication::Session *sess, const json &payload , json * error );

    ///////////////////
    static bool getStatusOK();

private:
    // WEB DISPLAY FUNCTIONS:
    static json getMessages(Mantids::Authentication::Manager *auth, Mantids::Authentication::Session *sess,const json &payload);
    static json getAdd1(Mantids::Authentication::Manager *auth, Mantids::Authentication::Session *sess,const json &payload);


    // NODE Manipulation:
    static json createMessage( Mantids::Authentication::Manager *auth, Mantids::Authentication::Session *sess,const json &payload );
    static json removeMessage( Mantids::Authentication::Manager *auth, Mantids::Authentication::Session *sess,const json &payload );

    static bool initSchema();

    static std::atomic<bool> statusOK;
    static std::string dbPath;
    static Mantids::Threads::Sync::Mutex_Shared mutex;

    static Mantids::Database::SQLConnector_SQLite3 db;
};


#endif // DB_H
