#ifndef USER_H
#define USER_H

#include <QString>
#include <QChar>

/// Class which stores information about user
class User
{
    int id_u_;
    QString name_;
    QString surname_;
    QString email_;
    QString passwd_;
    QString province_;
    QString p_code_;
    QString city_;
    QString address_;


public:
    /// Default constructor
    User() = default;

    /// Constructor to initializte user when user id is known
    ///
    /// @param id_u users' id
    /// @param name users' name
    /// @param surname users' surname
    /// @param email users' email
    /// @param passwd users' password
    /// @param province users' province
    /// @param P_code users' postal code / zip code
    /// @param city users' city
    /// @param address users' address
    User(const int id_u, const QString& name, const QString& surname, const QString& email,
         const QString& passwd, const QString& province, const QString& p_code,
         const QString& city, const QString& address);

    /// Constructor to initializte user when user id is known
    ///
    /// @param id_u users' id
    /// @param name users' name
    /// @param surname users' surname
    /// @param email users' email
    /// @param passwd users' password
    /// @param province users' province
    /// @param P_code users' postal code / zip code
    /// @param city users' city
    /// @param address users' address
    User(const int id_u, QString&& name, QString&& surname, QString&& email,
         QString&& passwd, QString&& province, QString&& p_code,
         QString&& city, QString&& address);

    /// Constructor to initializte user when user id is not known
    ///
    /// @param name users' name
    /// @param surname users' surname
    /// @param email users' email
    /// @param passwd users' password
    /// @param province users' province
    /// @param P_code users' postal code / zip code
    /// @param city users' city
    /// @param address users' address
    User(const QString& name, const QString& surname, const QString& email,
         const QString& passwd, const QString& province, const QString& p_code,
         const QString& city, const QString& address);

    /// Constructor to initializte user when user id is not known
    ///
    /// @param name users' name
    /// @param surname users' surname
    /// @param email users' email
    /// @param passwd users' password
    /// @param province users' province
    /// @param P_code users' postal code / zip code
    /// @param city users' city
    /// @param address users' address
    User(QString&& name, QString&& surname, QString&& email,
         QString&& passwd, QString&& province, QString&& p_code,
         QString&& city, QString&& address);


    /// Method to set users' id
    ///
    /// @param id users' id
    /// @return void
    void setId(const int id);

    /// Method to set users' name
    ///
    /// @param name users' name
    /// @return void
    void setName(const QString& name);

    /// Method to set users' name
    ///
    /// @param name users' name
    /// @return void
    void setName(QString&& name);

    /// Method to set users' surname
    ///
    /// @param surname users' surname
    /// @return void
    void setSurname(const QString& surname);

    /// Method to set users' surname
    ///
    /// @param surname users' surname
    /// @return void
    void setSurname(QString&& surname);

    /// Method to set users' email
    ///
    /// @param email users' email
    /// @return void
    void setEmail(const QString& email);

    /// Method to set users' email
    ///
    /// @param email users' email
    /// @return void
    void setEmail(QString&& email);

    /// Method to set users' password
    ///
    /// @param passwd users' password
    /// @return void
    void setPasswd(const QString& passwd);

    /// Method to set users' password
    ///
    /// @param passwd users' password
    /// @return void
    void setPasswd(QString&& passwd);

    /// Method to set users' province
    ///
    /// @param province users' province
    /// @return void
    void setProvince(const QString& province);

    /// Method to set users' province
    ///
    /// @param province users' province
    /// @return void
    void setProvince(QString&& province);

    /// Method to set users' postal/zip code
    ///
    /// @param p_code users' postal/zip code
    /// @return void
    void setP_code(const QString& p_code);

    /// Method to set users' postal/zip code
    ///
    /// @param p_code users' postal/zip code
    /// @return void
    void setP_code(QString&& p_code);

    /// Method to set users' city
    ///
    /// @param city users' city
    /// @return void
    void setCity(const QString& city);

    /// Method to set users' city
    ///
    /// @param city users' city
    /// @return void
    void setCity(QString&& city);

    /// Method to set users' address
    ///
    /// @param city users' city
    /// @return void
    void setAddress(const QString& address);

    /// Method to set users' address
    ///
    /// @param city users' city
    /// @return void
    void setAddress(QString&& address);


    /// Method gets users' id
    ///
    /// @return int users' id
    int getId() const;

    /// Method gets users' name
    ///
    /// @return QString users' name
    QString getName() const;

    /// Method gets users' surname
    ///
    /// @return QString users' surname
    QString getSurname() const;

    /// Method gets users' email
    ///
    /// @return QString users' email
    QString getEmail() const;

    /// Method gets users' passwd
    ///
    /// @return QString users' passwd
    QString getPasswd() const;

    /// Method gets users' province
    ///
    /// @return QString users' province
    QString getProvince() const;

    /// Method gets users' postal/zip code
    ///
    /// @return QString users' postal/zip code
    QString getP_code() const;

    /// Method gets users' city
    ///
    /// @return QString users' city
    QString getCity() const;

    /// Method gets users' address
    ///
    /// @return QString users' address
    QString getAddress() const;

};

#endif // USER_H
