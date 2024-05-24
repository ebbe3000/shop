#ifndef USER_H
#define USER_H

#include <QString>
#include <QChar>

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
    User() = default;

    User(const int id_u, const QString& name, const QString& surname, const QString& email,
         const QString& passwd, const QString& province, const QString& p_code,
         const QString& city, const QString& address);

    User(const int id_u, QString&& name, QString&& surname, QString&& email,
         QString&& passwd, QString&& province, QString&& p_code,
         QString&& city, QString&& address);

    User(const QString& name, const QString& surname, const QString& email,
         const QString& passwd, const QString& province, const QString& p_code,
         const QString& city, const QString& address);

    User(QString&& name, QString&& surname, QString&& email,
         QString&& passwd, QString&& province, QString&& p_code,
         QString&& city, QString&& address);

    void setId(const int id);
    void setName(const QString& name);
    void setName(QString&& name);
    void setSurname(const QString& surname);
    void setSurname(QString&& surname);
    void setEmail(const QString& email);
    void setEmail(QString&& email);
    void setPasswd(const QString& passwd);
    void setPasswd(QString&& passwd);
    void setProvince(const QString& province);
    void setProvince(QString&& province);
    void setP_code(const QString& p_code);
    void setP_code(QString&& p_code);
    void setCity(const QString& city);
    void setCity(QString&& city);
    void setAddress(const QString& address);
    void setAddress(QString&& address);

    int getId() const;
    QString getName() const;
    QString getSurname() const;
    QString getEmail() const;
    QString getPasswd() const;
    QString getProvince() const;
    QString getP_code() const;
    QString getCity() const;
    QString getAddress() const;

};

#endif // USER_H
