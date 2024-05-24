#include "user.h"


User::User(const int id_u, const QString& name, const QString& surname, const QString& email,
           const QString& passwd, const QString& province, const QString& p_code,
           const QString& city, const QString& address) :
    id_u_(id_u), name_(name), surname_(surname), email_(email), passwd_(passwd),
    province_(province), p_code_(p_code), city_(city), address_(address) {}


User::User(const int id_u, QString&& name, QString&& surname, QString&& email,
            QString&& passwd, QString&& province, QString&& p_code,
            QString&& city, QString&& address) :
    id_u_(id_u), name_(name), surname_(surname), email_(email), passwd_(passwd),
    province_(province), p_code_(p_code), city_(city), address_(address) {}


User::User(const QString& name, const QString& surname, const QString& email,
            const QString& passwd, const QString& province, const QString& p_code,
            const QString& city, const QString& address) :
    id_u_(-1), name_(name), surname_(surname), email_(email), passwd_(passwd),
    province_(province), p_code_(p_code), city_(city), address_(address) {}


User::User(QString&& name, QString&& surname, QString&& email,
            QString&& passwd, QString&& province, QString&& p_code,
            QString&& city, QString&& address) :
    id_u_(-1), name_(name), surname_(surname), email_(email), passwd_(passwd),
    province_(province), p_code_(p_code), city_(city), address_(address) {}


void User::setId(const int id) {
    id_u_ = id;
}

void User::setName(const QString& name) {
    name_ = name;
}


void User::setName(QString&& name) {
    name_ = name;
}

void User::setSurname(const QString& surname) {
    surname_ = surname;
}


void User::setSurname(QString&& surname) {
    surname_ = surname;
}


void User::setEmail(const QString& email) {
    email_ = email;
}

void User::setEmail(QString&& email) {
    email_ = email;
}


void User::setPasswd(const QString& passwd) {
    passwd_ = passwd;
}


void User::setPasswd(QString&& passwd) {
    passwd_ = passwd;
}


void User::setProvince(const QString& province) {
    province_ = province;
}


void User::setProvince(QString&& province) {
    province_ = province;
}


void User::setP_code(const QString& p_code) {
    p_code_ = p_code;
}


void User::setP_code(QString&& p_code) {
    p_code_ = p_code;
}

void User::setCity(const QString& city) {
    city_ = city;
}


void User::setCity(QString&& city) {
    city_ = city;
}


void User::setAddress(const QString& address) {
    address_ = address;
}


void User::setAddress(QString&& address) {
    address_ = address;
}


int User::getId() const {
    return id_u_;
}


QString User::getName() const {
    return name_;
}


QString User::getSurname() const {
    return surname_;
}


QString User::getEmail() const {
    return email_;
}


QString User::getPasswd() const {
    return passwd_;
}


QString User::getProvince() const {
    return province_;
}


QString User::getP_code() const {
    return p_code_;
}


QString User::getCity() const {
    return city_;
}


QString User::getAddress() const {
    return address_;
}

