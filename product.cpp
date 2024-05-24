#include "product.h"

Product::Product(const int id_p, const QString &name, const double price,
                 const int amount, const QString &add_date,
                 const QString &description, const QString& img_path) :
    id_p_(id_p), id_u_(-1), name_(name), price_(price), amount_(amount), add_date_(add_date),
    description_(description) {
    img_path_.push_back(img_path);
}


Product::Product(const int id_p, const QString &name, const double price,
                 const int amount, const QString &add_date,
                 const QString &description, const QVector<QString>& img_path) :
    id_p_(id_p), name_(name), price_(price), amount_(amount), add_date_(add_date),
    description_(description), img_path_(img_path) {}


Product::Product(const int id_p, QString&& name, const double price,
                 const int amount, QString&& add_date,
                 QString&& description, QString&& img_path) :
    id_p_(id_p), id_u_(-1), name_(name), price_(price), amount_(amount), add_date_(add_date),
    description_(description) {
    img_path_.push_back(img_path);
}


Product::Product(const int id_p, QString&& name, const double price,
        const int amount, QString&& add_date,
        QString&& description, QVector<QString>&& img_path) :
    id_p_(id_p), id_u_(-1), name_(name), price_(price), amount_(amount), add_date_(add_date),
    description_(description), img_path_(img_path) {}


Product::Product(const QString &name, const double price, const int amount,
                 const QString &add_date, const QString &description,
                 const QString &img_path) :
    name_(name), id_u_(-1), price_(price), amount_(amount), add_date_(add_date),
    description_(description) {
    img_path_.push_back(img_path);
}


Product::Product(const QString &name, const double price, const int amount,
                 const QString &add_date, const QString &description,
                 const QVector<QString>& img_path) :
    name_(name), id_u_(-1), price_(price), amount_(amount), add_date_(add_date),
    description_(description), img_path_(img_path) {}


Product::Product(QString &&name, const double price, const int amount,
                 QString &&add_date, QString &&description,
                 QString &&img_path) :
    name_(name), id_u_(-1), price_(price), amount_(amount), add_date_(add_date),
    description_(description) {
    img_path_.push_back(img_path);
}


Product::Product(QString&& name, const double price,
        const int amount, QString&& add_date,
        QString&& description, QVector<QString>&& img_path) :
    name_(name), id_u_(-1), price_(price), amount_(amount), add_date_(add_date),
    description_(description), img_path_(img_path) {}


Product::Product(const int id_p, const int id_u, const QString& name, const double price,
        const int amount, const QString& add_date,
        const QString& description, const QString& img_path) :
    id_p_(id_p), id_u_(id_u), name_(name), price_(price), amount_(amount), add_date_(add_date),
    description_(description) {
    img_path_.push_back(img_path);
}


Product::Product(const int id_p, const int id_u, const QString& name, const double price,
        const int amount, const QString& add_date,
        const QString& description, const QVector<QString>& img_path) :
    id_p_(id_p), id_u_(id_u), name_(name), price_(price), amount_(amount), add_date_(add_date),
    description_(description), img_path_(img_path) {}


Product::Product(const int id_p, const int id_u, QString&& name, const double price,
        const int amount, QString&& add_date,
        QString&& description, QString&& img_path) :
    id_p_(id_p), id_u_(id_u), name_(name), price_(price), amount_(amount), add_date_(add_date),
    description_(description) {
    img_path_.push_back(img_path);
}


Product::Product(const int id_p, const int id_u, QString&& name, const double price,
        const int amount, QString&& add_date,
        QString&& description, QVector<QString>&& img_path) :
    id_p_(id_p), id_u_(id_u), name_(name), price_(price), amount_(amount), add_date_(add_date),
    description_(description), img_path_(img_path) {}


Product::Product(const QString& name, const int id_u, const double price,
        const int amount, const QString& add_date,
        const QString& description, const QString& img_path) :
    name_(name), id_u_(id_u), price_(price), amount_(amount), add_date_(add_date),
    description_(description) {
    img_path_.push_back(img_path);
}


Product::Product(const QString& name, const int id_u, const double price,
        const int amount, const QString& add_date,
        const QString& description, const QVector<QString>& img_path) :
    name_(name), id_u_(id_u), price_(price), amount_(amount), add_date_(add_date),
    description_(description), img_path_(img_path) {}


Product::Product(QString&& name, const int id_u, const double price,
        const int amount, QString&& add_date,
        QString&& description, QString&& img_path) :
    name_(name), id_u_(-1), price_(price), amount_(amount), add_date_(add_date),
    description_(description) {
    img_path_.push_back(img_path);
}


Product::Product(QString&& name, const int id_u, const double price,
        const int amount, QString&& add_date,
        QString&& description, QVector<QString>&& img_path) :
    name_(name), id_u_(-1), price_(price), amount_(amount), add_date_(add_date),
    description_(description), img_path_(img_path) {}


Product::Product(QString&& name, const int id_u, const double price,
                 const int amount, QString&& description) :
    name_(name), id_u_(id_u), price_(price), amount_(amount),
    description_(description) {}


int Product::getId() const {
    return id_p_;
}


int Product::getIdU() const {
    return id_u_;
}


QString Product::getName() const {
    return name_;
}


double Product::getPrice() const {
    return price_;
}


int Product::getAmount() const {
    return amount_;
}


QString Product::getAddDate() const {
    return add_date_;
}


QString Product::getDescribtion() const {
    return description_;
}


QVector<QString> Product::getImgPath() const {
    return img_path_;
}


void Product::setId(int id) {
    id_p_ = id;
}


void Product::setName(const QString& name) {
    name_ = name;
}


void Product::setName(QString&& name) {
    name_ = name;
}


void Product::setPrice(double price) {
    price_ = price;
}


void Product::setAmount(int amount) {
    amount_ = amount;
}


void Product::setAddDate(const QString& add_date) {
    add_date_ = add_date;
}


void Product::setAddDate(QString&& add_date) {
    add_date_ = add_date;
}


void Product::setDescription(const QString& describtion) {
    description_ = describtion;
}


void Product::setDescription(QString&& describtion) {
    description_ = describtion;
}


void Product::setImgPath(const QString& img_path) {
    img_path_.push_back(img_path);
}


void Product::setImgPath(const QVector<QString>& img_path) {
    img_path_ = img_path;
}


void Product::setImgPath(QString&& img_path) {
    img_path_.push_back(img_path);
}

void Product::setImgPath(QVector<QString>&& img_path) {
    img_path_ = img_path;
}
